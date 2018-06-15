REQUIRES = arm_v7 jetson_tk1

TARGET   = nic_drv
LIBS     = base lx_kit_setjmp r8169_nic_include
#SRC_CC   = main.cc
INC_DIR += $(PRG_DIR)

# lx_kit
#SRC_CC  += env.cc malloc.cc scheduler.cc timer.cc work.cc pci.cc
SRC_CC += pci.cc
INC_DIR += $(REP_DIR)/src/include
INC_DIR += $(REP_DIR)/src/include/spec/arm
INC_DIR += $(REP_DIR)/src/include/spec/arm_v7
INC_DIR += $(REP_DIR)/src/lib/usb/include/spec/arm

# contrib code
LX_CONTRIB_DIR := $(call select_from_ports,dde_linux)/src/drivers/nic/r8169
SRC_C          += $(notdir $(wildcard $(LX_CONTRIB_DIR)/drivers/net/ethernet/realtek/r8169.c))
INC_DIR        += $(LX_CONTRIB_DIR)/include

#
# Linux sources are C89 with GNU extensions
#
CC_C_OPT += -std=gnu89

vpath %.c  $(LX_CONTRIB_DIR)/drivers/net/ethernet/realtek
vpath %.cc $(PRG_DIR)
vpath %.cc $(REP_DIR)/src/lx_kit

CC_CXX_WARN_STRICT =
