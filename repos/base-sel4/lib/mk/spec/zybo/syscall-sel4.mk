PLAT := zynq7000
ARCH := arm

SEL4_ARCH := aarch32
PLAT_BOARD := /zybo
SEL4_WORDBITS := 32

include $(REP_DIR)/lib/mk/syscall-sel4.inc
