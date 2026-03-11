TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = matsusada_R4K
# matsusada_R4K.dbd will be created and installed
DBD += matsusada_R4K.dbd

# matsusada_R4K.dbd will be made up from these files:
matsusada_R4K_DBD += base.dbd

matsusada_R4K_DBD += calc.dbd
matsusada_R4K_DBD += stream.dbd
matsusada_R4K_DBD += asyn.dbd
matsusada_R4K_DBD += drvAsynIPPort.dbd
matsusada_R4K_DBD += aSubRecord.dbd
matsusada_R4K_DBD += system.dbd

matsusada_R4K_DBD += asSupport.dbd
matsusada_R4K_DBD += devIocStats.dbd
matsusada_R4K_DBD += reccaster.dbd

matsusada_R4K_DBD += status.dbd

# Include dbd files from all support applications:
#matsusada_R4K_DBD += xxx.dbd

# Add all the support libraries needed by this IOC
#matsusada_R4K_LIBS += xxx

# matsusada_R4K_registerRecordDeviceDriver.cpp derives from matsusada_R4K.dbd
matsusada_R4K_SRCS += matsusada_R4K_registerRecordDeviceDriver.cpp
matsusada_R4K_SRCS += status.c

# Build the main IOC entry point on workstation OSs.
matsusada_R4K_SRCS_DEFAULT += matsusada_R4KMain.cpp
matsusada_R4K_SRCS_vxWorks += -nil-


# Add support from base/src/vxWorks if needed
#matsusada_R4K_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
matsusada_R4K_LIBS += $(EPICS_BASE_IOC_LIBS)

matsusada_R4K_LIBS += asyn calc stream

matsusada_R4K_LIBS += autosave
matsusada_R4K_LIBS += devIocStats
matsusada_R4K_LIBS += reccaster

# Link QSRV (pvAccess Server) if available
ifdef EPICS_QSRV_MAJOR_VERSION
    matsusada_R4K_LIBS += qsrv
    matsusada_R4K_LIBS += $(EPICS_BASE_PVA_CORE_LIBS)
    matsusada_R4K_DBD += PVAServerRegister.dbd
    matsusada_R4K_DBD += qsrv.dbd
endif


#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

