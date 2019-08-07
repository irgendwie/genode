L4_CONFIG := $(call select_from_repositories,config/bpi_m3.user)

L4_BIN_DIR := $(LIB_CACHE_DIR)/syscall-foc/bpi_m3-build/bin/arm_armv7

include $(REP_DIR)/lib/mk/spec/arm/syscall-foc.inc
