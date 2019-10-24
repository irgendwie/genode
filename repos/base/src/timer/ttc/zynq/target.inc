TARGET   = zynq_timer_drv
REQUIRES = zybo
GEN_DIR := $(BASE_DIR)/src/timer
INC_DIR += $(GEN_DIR)/ttc
SRC_CC  += ttc/time_source.cc ttc/zynq/timer.cc

include $(GEN_DIR)/target.inc

vpath %.cc $(GEN_DIR)
