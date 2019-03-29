#
# \brief  Build-system configurations specifically for the ARM Cortex A7
# \author Alexander Weidinger
# \date   2019-03-29
#

# denote wich specs are also fullfilled by this spec
SPECS += arm_v7a

# add repository relative include paths
REP_INC_DIR += include/spec/cortex_a7

# configure compiler
CC_MARCH += -march=armv7ve -mcpu=cortex-a7

# include implied specs
include $(call select_from_repositories,mk/spec/arm_v7a.mk)
