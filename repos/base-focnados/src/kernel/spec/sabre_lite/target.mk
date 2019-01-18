REQUIRES       = sabre_lite
FIASCO_DIR    := $(call select_from_ports,focnados)/src/kernel/foc/kernel/fiasco
KERNEL_CONFIG  = $(REP_DIR)/config/sabre_lite.kernel

-include $(PRG_DIR)/../../target.inc
