/*
 * \brief  Time source that uses the Triple Timer Counter (Zynq7000)
 * \author Alexander Weidinger
 * \date   2019-10-27
 */

/* local includes */
#include <time_source.h>

using namespace Genode;

void Timer::Time_source::schedule_timeout(Genode::Microseconds  duration,
                                          Timeout_handler      &handler)
{
	_handler = &handler;

	unsigned short const ticks = Genode::max((unsigned short)1, (duration.value * TICKS_PER_MS) / 1000);
	_timer_irq.ack_irq();
	_cleared_ticks = 0;

	/* stop timer */
	write<CNT_CNTRL::DIS>(1);

	/* clear interrupts */
	if (read<ISR>()) {
		_timer_irq.ack_irq();
	}

	/* set new timeout */
	write<MATCH_0>(COUNT_VALUE::MAX - ticks);
	write<IER::IXR_MATCH_0>(1);

	/* counter restart */
	write<CNT_CNTRL::DIS>(0);
}


unsigned long timer_ticks_to_us(unsigned short const ticks, unsigned short const ticks_per_ms) {
	enum {
		HALF_WIDTH = (sizeof(unsigned short) << 2),
		MSB_MASK  = ((unsigned short)~0) << HALF_WIDTH,
		LSB_MASK  = ((unsigned short)~0) >> HALF_WIDTH,
		MSB_RSHIFT = 6, // FIXME currently don't understand this value
		LSB_LSHIFT = HALF_WIDTH - MSB_RSHIFT,
	};
	unsigned short const msb = ((((ticks & MSB_MASK) >> MSB_RSHIFT)
	                             * 1000) / ticks_per_ms) << MSB_RSHIFT;
	unsigned short const lsb = ((((ticks & LSB_MASK) << LSB_LSHIFT)
	                             * 1000) / ticks_per_ms) >> LSB_LSHIFT;
	return msb + lsb;
}


Duration Timer::Time_source::curr_time()
{
	unsigned short const uncleared_ticks = COUNT_VALUE::MAX - read<COUNT_VALUE>() - _cleared_ticks;
	unsigned long const uncleared_us     = timer_ticks_to_us(uncleared_ticks, (unsigned short)TICKS_PER_MS);

	/* update time only on IRQs and if rate is under 1000 per second */
	if (_irq || uncleared_us > 1000) {
		_curr_time.add(Genode::Microseconds(uncleared_us));
		_cleared_ticks += uncleared_ticks;
	}
	return _curr_time;
}


Genode::Microseconds Timer::Time_source::max_timeout() const
{
	static unsigned long max = timer_ticks_to_us((unsigned long)COUNT_VALUE::MAX, TICKS_PER_MS);
	return Genode::Microseconds(max);
}


void Timer::Time_source::_initialize()
{
	_timer_irq.sigh(_signal_handler);

	// disable ttc
	write<CNT_CNTRL::DIS>(1);

	// select clock source and set prescaler value FIXME?
	// default clk should be 133 MHz (QEMU) or 150 MHz
	// count/2^(N+1); N = prescale value
	write<CLK_CNTRL::SRC>(0);
	write<CLK_CNTRL::PS_VAL>(0x7);
	write<CLK_CNTRL::PS_EN>(1);

	// set interval value
	write<INT_VAL>(COUNT_VALUE::MAX);

	// disable waveform
	write<CNT_CNTRL::EN_WAVE>(1); // active low
	// enable matching
	write<CNT_CNTRL::MATCH>(1);
	// set counting up
	write<CNT_CNTRL::DECR>(0);
	// disable interval mode
	write<CNT_CNTRL::INT>(0);
	// mask interrupts
	write<IER>(0x0);

	// clear interrupts
	read<ISR>();
}
