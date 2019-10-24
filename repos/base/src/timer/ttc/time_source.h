/*
 * \brief  Time source that uses the Triple Timer Counter (Zynq7000)
 * \author Alexander Weidinger
 * \date   2019-10-27
 */

#ifndef _TIME_SOURCE_H_
#define _TIME_SOURCE_H_

/* Genode includes */
#include <irq_session/connection.h>
#include <os/attached_mmio.h>
#include <drivers/timer/util.h>

/* local includes */
#include <signalled_time_source.h>

namespace Timer { class Time_source; }


class Timer::Time_source : private Genode::Attached_mmio,
                           public  Genode::Signalled_time_source
{
	private:

		enum { TICKS_PER_MS = 519 };

		struct CNT_CNTRL : Register<0xc, 8> {
			struct POL_WAVE : Bitfield<6, 1> { };
			struct EN_WAVE  : Bitfield<5, 1> { };
			struct RST      : Bitfield<4, 1> { };
			struct MATCH    : Bitfield<3, 1> { };
			struct DECR     : Bitfield<2, 1> { };
			struct INT      : Bitfield<1, 1> { };
			struct DIS      : Bitfield<0, 1> { };
		};

		struct CLK_CNTRL : Register<0x0, 8> {
			struct EXT_EDGE : Bitfield<6, 1> { };
			struct SRC      : Bitfield<5, 1> { };
			struct PS_VAL   : Bitfield<1, 4> { };
			struct PS_EN    : Bitfield<0, 1> { };
		};

		struct INT_VAL : Register<0x24, 16> { };

		struct COUNT_VALUE : Register<0x18, 16> { enum { MAX = ~(access_t)0 }; };

		struct ISR : Register<0x54, 8> { };

		struct IER : Register<0x60, 8> {
			struct Ev           : Bitfield<5, 1> { };
			struct IXR_CNT_OVR  : Bitfield<4, 1> { };
			struct IXR_MATCH_2  : Bitfield<3, 1> { };
			struct IXR_MATCH_1  : Bitfield<2, 1> { };
			struct IXR_MATCH_0  : Bitfield<1, 1> { };
			struct IXR_INTERVAL : Bitfield<0, 1> { };
		};

		struct MATCH_0 : Register<0x30, 16> { };

		Genode::uint16_t _cleared_ticks { 0 };

		Genode::Irq_connection     _timer_irq;
		Genode::Duration           _curr_time   { Genode::Microseconds(0) };

		void _initialize();

	public:

		Time_source(Genode::Env &env);


		/*************************
		 ** Genode::Time_source **
		 *************************/

		Genode::Duration curr_time() override;
		void schedule_timeout(Genode::Microseconds duration, Timeout_handler &handler) override;
		Genode::Microseconds max_timeout() const override;
};

#endif /* _TIME_SOURCE_H_ */
