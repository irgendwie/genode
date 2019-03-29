#
# \brief  Build-system configurations for Allwinner A83T
# \author Alexander Weidinger
# \date   2019-03-29
#

# denote which spec are also fullfilled by this spec
SPECS += cortex_a7 sunxi_a83t sunxi

# add repository relative include paths
REP_INC_DIR += include/spec/sunxi_a83t
REP_INC_DIR += include/spec/sunxi

# include implied specs
include $(call select_from_repositories,mk/spec/cortex_a7.mk)