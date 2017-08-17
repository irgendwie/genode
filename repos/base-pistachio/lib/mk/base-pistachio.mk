include $(BASE_DIR)/lib/mk/base.inc

LIBS   += base-pistachio-common syscall-pistachio cxx timeout

SRC_CC += thread_start.cc
SRC_CC += cache.cc
SRC_CC += capability_space.cc
SRC_CC += signal_transmitter.cc
SRC_CC += signal.cc