#!../../bin/linux-x86_64/matsusada_R4K

<xf31id1-lab3-ioc1-netsetup.cmd

epicsEnvSet("ENGINEER",  "C. Engineer")
epicsEnvSet("LOCATION",  "LAB3")

epicsEnvSet("IOCNAME",   "r4k")
epicsEnvSet("SYS",       "XF:31ID1-BI")
epicsEnvSet("DEV",       "{PW:1}")
epicsEnvSet("IOC_SYS",   "XF:31ID1-CT")
epicsEnvSet("IOC_DEV",   "{IOC:$(IOCNAME)}")
epicsEnvSet("MODEL", "R4K_80")
epicsEnvSet("CHAN", 0)

epicsEnvSet("PORT","matsu-px")
epicsEnvSet("HOST","10.69.57.80:10001")

epicsEnvSet("IOC_PREFIX", "$(IOC_SYS)$(IOC_DEV)")

< envPaths

cd "${TOP}"

## Register all support components
dbLoadDatabase("dbd/matsusada_R4K.dbd")
matsusada_R4K_registerRecordDeviceDriver pdbbase

## Streamdevice Protocol Path
epicsEnvSet ("STREAM_PROTOCOL_PATH", "${TOP}/protocols")


drvAsynIPPortConfigure("$(PORT)", "$(HOST)")

## Load record instances
dbLoadRecords("db/${MODEL}.db", "Sys=${SYS},Dev=${DEV},Chan=${CHAN},PORT=${PORT}")
dbLoadRecords("db/asynRecord.db","P=$(IOC_SYS),R=$(IOC_DEV)Asyn,PORT=$(PORT),ADDR=0,IMAX=256,OMAX=256")

dbLoadRecords("$(DEVIOCSTATS)/db/iocAdminSoft.db", "IOC=${IOC_PREFIX}")
dbLoadRecords("$(AUTOSAVE)/db/save_restoreStatus.db", "P=${IOC_PREFIX}")
dbLoadRecords("${RECCASTER}/db/reccaster.db", "P=${IOC_PREFIX}RecSync")

#- Set this to see messages from mySub
#var mySubDebug 1

#- Run this to trace the stages of iocInit
#traceIocInit

set_savefile_path("$(TOP)/as/save")
set_requestfile_path("$(TOP)/as/req")

set_pass0_restoreFile("info_positions.sav")
set_pass0_restoreFile("info_settings.sav")
set_pass1_restoreFile("info_settings.sav")

iocInit

makeAutosaveFileFromDbInfo("$(TOP)/as/req/info_settings.req", "autosaveFields")
makeAutosaveFileFromDbInfo("$(TOP)/as/req/info_positions.req", "autosaveFields_pass0")

create_monitor_set("info_positions.req", 5 , "")
create_monitor_set("info_settings.req", 15 , "")

# Set terminators for ASYN record
dbpf $(IOC_SYS)$(IOC_DEV)Asyn.OEOS "\r"
dbpf $(IOC_SYS)$(IOC_DEV)Asyn.IEOS "\r"

#cd ${TOP}
dbl > ./records.dbl

