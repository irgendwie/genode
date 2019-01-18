SPECS += focnados_arm sabre_lite

include $(call select_from_repositories,mk/spec/imx6.mk)
include $(call select_from_repositories,mk/spec/focnados_arm.mk)
