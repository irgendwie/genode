SPECS += focnados_arm wand_quad imx6

include $(call select_from_repositories,mk/spec/imx6.mk)
include $(call select_from_repositories,mk/spec/focnados_arm.mk)
