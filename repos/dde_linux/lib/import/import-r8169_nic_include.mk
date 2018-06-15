LX_CONTRIB_DIR := $(call select_from_ports,dde_linux)/src/drivers/nic/r8169
SRC_DIR        := $(REP_DIR)/src/drivers/nic/r8169
INC_DIR        += $(LX_CONTRIB_DIR)/drivers/net/ethernet/realtek
INC_DIR        += $(LIB_CACHE_DIR)/r8169_nic_include/include/include/include
CC_OPT         += -U__linux__ -D__KERNEL__
