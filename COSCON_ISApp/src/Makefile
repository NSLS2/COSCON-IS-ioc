TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = COSCON_IS
# COSCON_IS.dbd will be created and installed
DBD += COSCON_IS.dbd

# COSCON_IS.dbd will be made up from these files:
COSCON_IS_DBD += base.dbd

COSCON_IS_DBD += calc.dbd
COSCON_IS_DBD += stream.dbd
COSCON_IS_DBD += asyn.dbd
COSCON_IS_DBD += drvAsynIPPort.dbd
COSCON_IS_DBD += aSubRecord.dbd
COSCON_IS_DBD += system.dbd

COSCON_IS_DBD += asSupport.dbd
COSCON_IS_DBD += devIocStats.dbd
COSCON_IS_DBD += reccaster.dbd

COSCON_IS_DBD += status.dbd

# Include dbd files from all support applications:
#COSCON_IS_DBD += xxx.dbd

# Add all the support libraries needed by this IOC
#COSCON_IS_LIBS += xxx

# COSCON_IS_registerRecordDeviceDriver.cpp derives from COSCON_IS.dbd
COSCON_IS_SRCS += COSCON_IS_registerRecordDeviceDriver.cpp
COSCON_IS_SRCS += status.c

# Build the main IOC entry point on workstation OSs.
COSCON_IS_SRCS_DEFAULT += COSCON_IS_Main.cpp
COSCON_IS_SRCS_vxWorks += -nil-


# Add support from base/src/vxWorks if needed
#COSCON_IS_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
COSCON_IS_LIBS += $(EPICS_BASE_IOC_LIBS)

COSCON_IS_LIBS += asyn calc stream

COSCON_IS_LIBS += autosave
COSCON_IS_LIBS += devIocStats
COSCON_IS_LIBS += reccaster

# Link QSRV (pvAccess Server) if available
ifdef EPICS_QSRV_MAJOR_VERSION
    COSCON_IS_LIBS += qsrv
    COSCON_IS_LIBS += $(EPICS_BASE_PVA_CORE_LIBS)
    COSCON_IS_DBD += PVAServerRegister.dbd
    COSCON_IS_DBD += qsrv.dbd
endif


#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

