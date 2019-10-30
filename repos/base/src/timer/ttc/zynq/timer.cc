/*
 * \brief  Time source that uses the Triple Timer Counter (Zynq7000)
 * \author Alexander Weidinger
 * \date   2019-10-27
 */

#include <time_source.h>

using namespace Genode;

enum {
	MMIO_BASE = 0xF8001000,  // ttc0: 0xF8001000; ttc1: 0xF8002000
	MMIO_SIZE = 0x1000,
	IRQ       = 42,          // ttc0: 44:42; ttc1: 71:69
};


Timer::Time_source::Time_source(Env &env)
: Attached_mmio(env, MMIO_BASE, MMIO_SIZE),
  Signalled_time_source(env),
  _timer_irq(env, IRQ), _env(env) { _initialize(); }
