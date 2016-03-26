# *********************************************************************
#
#  $Id: makefile 20312 2015-05-12 08:20:11Z seb $
#
#  makefile for command line tools library
#  - - - - - - - - - License information: - - - - - - - - -
#
#  Copyright (C) 2011 and beyond by Yoctopuce Sarl, Switzerland.
#
#  1) If you have obtained this file from www.yoctopuce.com using
#     a valid customer account established in your proper name,
#     Yoctopuce Sarl (hereafter Licensor) licenses to you (hereafter
#     Licensee) the right to use, modify, copy, and integrate this
#     source file into your own solution for the sole purpose of
#     interfacing a Yoctopuce product integrated into Licensee's
#     solution.
#
#     You should refer to the license agreement accompanying this
#     Software for additional information regarding your rights
#     and obligations.
#
#     THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
#     WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING
#     WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS
#     FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO
#     EVENT SHALL LICENSOR BE LIABLE FOR ANY INCIDENTAL, SPECIAL,
#     INDIRECT OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
#     COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR
#     SERVICES, ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT
#     LIMITED TO ANY DEFENSE THEREOF), ANY CLAIMS FOR INDEMNITY OR
#     CONTRIBUTION, OR OTHER SIMILAR COSTS, WHETHER ASSERTED ON THE
#     BASIS OF CONTRACT, TORT (INCLUDING NEGLIGENCE), BREACH OF
#     WARRANTY, OR OTHERWISE.
#
#  2) If you have obtained this file from any other source, you
#     are not entitled to use it, read it or create any derived
#     material. You should delete this file immediately.
#
# ********************************************************************
.SILENT:

WINDOWS_SDK_32 = $(WINDOWSSDKDIR)

CC32 = "$(VCINSTALLDIR)\bin\cl"

LINKER32 = "$(VCINSTALLDIR)\bin\link"

LINKWITH32 =  /LIBPATH:"$(VCINSTALLDIR)lib" /LIBPATH:"$(VCINSTALLDIR)atlmfc\lib" /LIBPATH:"$(WINDOWS_SDK_32)lib"

!IF !EXISTS(c:\Program Files\Microsoft SDKs\Windows\v7.1\)
WINDOWS_SDK_64 = $(WINDOWSSDKDIR)
CC64 = "$(VCINSTALLDIR)bin\x86_amd64\cl"
LINKER64 = "$(VCINSTALLDIR)bin\x86_amd64\link"
LINKWITH64 =  /LIBPATH:"$(VCINSTALLDIR)lib\amd64" /LIBPATH:"$(VCINSTALLDIR)atlmfc\lib\amd64" /LIBPATH:"$(WINDOWS_SDK_64)lib\winv6.3\um\x64"
!ELSE
WINDOWS_SDK_64 = c:\Program Files\Microsoft SDKs\Windows\v7.1
CC64 = "$(VCINSTALLDIR)bin\amd64\cl"
LINKER64 = "$(VCINSTALLDIR)bin\amd64\link"
LINKWITH64 =  /LIBPATH:"$(VCINSTALLDIR)lib\amd64" /LIBPATH:"$(VCINSTALLDIR)atlmfc\lib\amd64" /LIBPATH:"$(WINDOWS_SDK_64)\lib\x64"
!ENDIF

OUTDIR32 = windows

OBJDIR32 = $(OUTDIR32)\obj_dir

OUTDIR64 = windows\amd64

OBJDIR64 = $(OUTDIR64)\obj_dir

OD = arch_tag

CMD_SRC_DIR = ..\Sources

CMD_OBJS = $(OD)\YAccelerometer.obj $(OD)\YAltitude.obj $(OD)\YAnButton.obj $(OD)\YCarbonDioxide.obj $(OD)\YColorLed.obj $(OD)\YCompass.obj $(OD)\YCurrent.obj \
	$(OD)\YDataLogger.obj $(OD)\YDigitalIO.obj $(OD)\YDisplay.obj $(OD)\YDualPower.obj $(OD)\YFiles.obj $(OD)\YGenericSensor.obj $(OD)\YGyro.obj \
	$(OD)\YHubPort.obj $(OD)\YHumidity.obj $(OD)\YLed.obj $(OD)\YLightSensor.obj $(OD)\YMagnetometer.obj $(OD)\YModule.obj $(OD)\YMotor.obj $(OD)\YNetwork.obj $(OD)\YPower.obj $(OD)\YPressure.obj \
	$(OD)\YPwmOutput.obj $(OD)\YPwmPowerSource.obj $(OD)\YRealTimeClock.obj $(OD)\YRefFrame.obj $(OD)\YRelay.obj $(OD)\YSensor.obj  $(OD)\YSerialPort.obj $(OD)\YServo.obj \
	$(OD)\YTemperature.obj $(OD)\YTilt.obj $(OD)\YVoc.obj $(OD)\YVoltage.obj $(OD)\YWakeUpMonitor.obj $(OD)\YWakeUpSchedule.obj $(OD)\YWatchdog.obj \
	$(OD)\YWireless.obj $(OD)\YPwmInput.obj $(OD)\YSegmentedDisplay.obj  $(OD)\YBuzzer.obj $(OD)\YGps.obj $(OD)\YCellular.obj $(OD)\YGroundSpeed.obj $(OD)\YLatitude.obj $(OD)\YLongitude.obj \
 	$(OD)\YPowerOutput.obj

YOCTO_API_DIR = ..\Sources\cpplib

YOCTO_API_OBJS = $(OD)\yocto_api.obj $(OD)\yocto_anbutton.obj $(OD)\yocto_carbondioxide.obj $(OD)\yocto_colorled.obj $(OD)\yocto_current.obj $(OD)\yocto_datalogger.obj $(OD)\yocto_display.obj \
	$(OD)\yocto_dualpower.obj $(OD)\yocto_files.obj $(OD)\yocto_genericsensor.obj $(OD)\yocto_hubport.obj $(OD)\yocto_humidity.obj $(OD)\yocto_led.obj $(OD)\yocto_lightsensor.obj \
	$(OD)\yocto_network.obj $(OD)\yocto_oscontrol.obj $(OD)\yocto_power.obj $(OD)\yocto_pressure.obj $(OD)\yocto_realtimeclock.obj $(OD)\yocto_relay.obj $(OD)\yocto_servo.obj \
	$(OD)\yocto_temperature.obj $(OD)\yocto_voc.obj $(OD)\yocto_voltage.obj $(OD)\yocto_wakeupmonitor.obj $(OD)\yocto_wakeupschedule.obj $(OD)\yocto_watchdog.obj \
	$(OD)\yocto_wireless.obj $(OD)\yocto_digitalio.obj $(OD)\yocto_accelerometer.obj $(OD)\yocto_magnetometer.obj $(OD)\yocto_refframe.obj $(OD)\yocto_tilt.obj \
	$(OD)\yocto_compass.obj $(OD)\yocto_gyro.obj $(OD)\yocto_pwmoutput.obj $(OD)\yocto_pwmpowersource.obj  $(OD)\yocto_altitude.obj $(OD)\yocto_motor.obj \
	$(OD)\yocto_serialport.obj $(OD)\yocto_pwminput.obj $(OD)\yocto_segmenteddisplay.obj  $(OD)\yocto_buzzer.obj $(OD)\yocto_gps.obj $(OD)\yocto_cellular.obj $(OD)\yocto_groundspeed.obj \
	$(OD)\yocto_latitude.obj $(OD)\yocto_longitude.obj $(OD)\yocto_poweroutput.obj

YAPI_DIR    = $(YOCTO_API_DIR)\yapi\

YAPI_OBJS = $(OD)\yapi.obj $(OD)\ystream.obj $(OD)\yprog.obj $(OD)\ypkt_lin.obj $(OD)\ypkt_win.obj $(OD)\ypkt_osx.obj $(OD)\yfifo.obj $(OD)\ykey.obj $(OD)\yhash.obj $(OD)\yjson.obj $(OD)\ytcp.obj $(OD)\ymemory.obj $(OD)\ythread.obj

ALL_OBJS_STAT		= $(YOCTO_API_OBJS) $(YAPI_OBJS)


#create a new definitions for each platform using macro
ALL_OBJS_STAT_32    = $(ALL_OBJS_STAT:arch_tag=windows\obj_dir)
ALL_OBJS_STAT_64    = $(ALL_OBJS_STAT:arch_tag=windows\amd64\obj_dir)
ALL_OBJS_STAT_bb    = $(ALL_OBJS_STAT:arch_tag=windows\obj_dir)

CMD_OBJS_STAT_32    = $(CMD_OBJS:arch_tag=windows\obj_dir)
CMD_OBJS_STAT_64    = $(CMD_OBJS:arch_tag=windows\amd64\obj_dir)


#define all tragets
EXE_NAMES     = $(CMD_OBJS:.obj=.exe)
TARGETS_32    = $(EXE_NAMES:arch_tag=windows)
TARGETS_64    = $(EXE_NAMES:arch_tag=windows\amd64)

INCLUDES_OPTIONS = /I $(YAPI_DIR) /I $(YOCTO_API_DIR) /I $(CMD_SRC_DIR)

CFLAGS_DEBUG = /nologo /O2 /Oi /Oy- /Zi /GL /EHsc /MT /GS /fp:precise $(INCLUDES_OPTIONS)

CFLAGS = /nologo /O2 /Oi /Oy- /GL /EHsc /MT /GS /fp:precise $(INCLUDES_OPTIONS)

{$(YAPI_DIR)\}.c{$(OBJDIR32)\}.obj:
	$(CC32) $(CFLAGS) /Fo$@ /c $<

{$(YOCTO_API_DIR)\}.cpp{$(OBJDIR32)\}.obj:
	$(CC32) $(CFLAGS) /Fo$@ /c $<

{$(CMD_SRC_DIR)\}.cpp{$(OBJDIR32)\}.obj:
	$(CC32) $(CFLAGS) /Fo$@ /c $<


{$(YAPI_DIR)\}.c{$(OBJDIR64)\}.obj:
	$(CC64) $(CFLAGS) /Fo$@ /c $<

{$(CMD_SRC_DIR)\}.cpp{$(OBJDIR64)\}.obj:
	$(CC64) $(CFLAGS) /Fo$@ /c $<

{$(YOCTO_API_DIR)\}.cpp{$(OBJDIR64)\}.obj:
	$(CC64) $(CFLAGS) /Fo$@ /c $<



TARGET = $(OBJDIR)\cmdline_common.obj $(CMD_OBJS) $(CMD_EXES)

all:  b32 b64

b32_objs: $(OUTDIR32) $(OBJDIR32) $(ALL_OBJS_STAT_32) $(OBJDIR32)\cmdline_common.obj
	echo $*
	echo $(ALL_OBJS_STAT_32)

b32: b32_objs $(TARGETS_32)
	echo $*

b64_objs: $(OUTDIR64) $(OBJDIR64) $(ALL_OBJS_STAT_64) $(OBJDIR64)\cmdline_common.obj
	echo $*
	echo $(ALL_OBJS_STAT_64)

b64: b64_objs $(TARGETS_64)
	echo $*

all_objs:  b32_objs b64_objs


release :  all clean_objs

$(TARGETS_32) : $(ALL_OBJS_STAT_32) $(OBJDIR32)\cmdline_common.obj $(CMD_OBJS_STAT_32)
	echo build $@
	$(CC32) $(CFLAGS) /Fe$@  $(OBJDIR32)\$(@B).obj $(OBJDIR32)\cmdline_common.obj $(ALL_OBJS_STAT_32)

$(TARGETS_64) : $(ALL_OBJS_STAT_64) $(OBJDIR64)\cmdline_common.obj $(CMD_OBJS_STAT_64)
	echo build $@
	$(CC64) $(CFLAGS) /Fe$@  $(OBJDIR64)\$(@B).obj $(OBJDIR64)\cmdline_common.obj $(ALL_OBJS_STAT_64) /link $(LINKWITH64)


$(OUTDIR32) $(OBJDIR32) $(OUTDIR64) $(OBJDIR64):
	IF NOT EXIST $@ mkdir $@

clean: clean32 clean64

clean_objs: clean_obj32  clean_obj64

clean32: clean_obj32
	-del /Q /F $(OUTDIR32)

clean_obj32:
	-del /Q /F $(OBJDIR32)
	-rmdir $(OBJDIR32)

clean64: clean_obj64
	-del /Q /F $(OUTDIR64)

clean_obj64:
	-del /Q /F $(OBJDIR64)
	-rmdir $(OBJDIR64)
