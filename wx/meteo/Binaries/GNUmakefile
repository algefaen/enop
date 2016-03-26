# *********************************************************************
#
#  $Id: GNUmakefile 19412 2015-02-19 11:06:34Z seb $
#
#  GNU Makefile for linux and Mac OS X
#
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

UNAME := $(shell uname)
ARCH  := $(shell uname -m| sed -e s/i.86/i386/ -e s/arm.*/arm/)

MIPS_TARGET_ROOT = $(STAGING_DIR)/target-mips_34kc_uClibc-0.9.33.2/


.SECONDARY:

#ALL directory definitions
DIR_I386 	= linux/32bits/
DIR_X64 	= linux/64bits/
DIR_ARMEL 	= linux/armel/
DIR_ARMHF 	= linux/armhf/
DIR_MIPS 	= linux/mips/
DIR_OSX 	= osx/

OBJDIR_I386 	= $(DIR_I386)obj/
OBJDIR_X64 		= $(DIR_X64)obj/
OBJDIR_ARMEL 	= $(DIR_ARMEL)obj/
OBJDIR_ARMHF 	= $(DIR_ARMHF)obj/
OBJDIR_MIPS 	= $(DIR_MIPS)obj/
OBJDIR_OSX 		= $(DIR_OSX)obj/


CMD_SRC = ../Sources/

CMD_OBJS = YAccelerometer.o YAltitude.o YAnButton.o YCarbonDioxide.o YColorLed.o YCompass.o YCurrent.o \
	YDataLogger.o YDigitalIO.o YDisplay.o YDualPower.o YFiles.o YGenericSensor.o YGyro.o \
	YHubPort.o YHumidity.o YLed.o YLightSensor.o YMagnetometer.o YModule.o YMotor.o YNetwork.o YPower.o YPressure.o \
	YPwmOutput.o YPwmPowerSource.o YRealTimeClock.o YRefFrame.o YRelay.o YSensor.o YSerialPort.o YServo.o \
	YTemperature.o YTilt.o YVoc.o YVoltage.o YWakeUpMonitor.o YWakeUpSchedule.o YWatchdog.o \
	YWireless.o YSegmentedDisplay.o YPwmInput.o YBuzzer.o YGps.o YCellular.o YGroundSpeed.o YLatitude.o YLongitude.o \
	YPowerOutput.o


YOCTO_SRC = ../Sources/cpplib/

YOCTO_OBJS = yocto_api.o yocto_anbutton.o yocto_carbondioxide.o yocto_colorled.o yocto_current.o yocto_datalogger.o yocto_display.o \
	yocto_dualpower.o yocto_files.o yocto_genericsensor.o yocto_hubport.o yocto_humidity.o yocto_led.o yocto_lightsensor.o \
	yocto_network.o yocto_oscontrol.o yocto_power.o yocto_pressure.o yocto_realtimeclock.o yocto_relay.o yocto_servo.o \
	yocto_temperature.o yocto_voc.o yocto_voltage.o yocto_wakeupmonitor.o yocto_wakeupschedule.o yocto_watchdog.o \
	yocto_wireless.o yocto_digitalio.o yocto_accelerometer.o yocto_magnetometer.o yocto_refframe.o yocto_tilt.o \
	yocto_compass.o yocto_gyro.o yocto_pwmoutput.o yocto_pwmpowersource.o yocto_altitude.o yocto_motor.o \
	yocto_serialport.o yocto_pwminput.o yocto_segmenteddisplay.o yocto_buzzer.o yocto_gps.o yocto_cellular.o \
	yocto_groundspeed.o yocto_latitude.o yocto_longitude.o yocto_poweroutput.o

YAPI_SRC    = $(YOCTO_SRC)yapi/

YAPI_OBJS = yapi.o ystream.o yprog.o ypkt_lin.o ypkt_win.o ypkt_osx.o yfifo.o ykey.o yhash.o yjson.o ytcp.o ymemory.o ythread.o

VPATH 		= $(YAPI_SRC) $(CMD_SRC) $(YOCTO_SRC)
ALL_H		= $(wildcard $(patsubst %,%*.h,$(subst :, ,$(YAPI_SRC) $(YOCTO_SRC) $(CMD_SRC))))

COMMON_OBJS		= $(YOCTO_OBJS) $(YAPI_OBJS)

#create a new definitions for each platform using macro
COMMON_OBJS_I386  = $(patsubst %.o, $(OBJDIR_I386)%.o, $(COMMON_OBJS))
COMMON_OBJS_X64   = $(patsubst %.o, $(OBJDIR_X64)%.o, $(COMMON_OBJS))
COMMON_OBJS_ARMEL = $(patsubst %.o, $(OBJDIR_ARMEL)%.o, $(COMMON_OBJS))
COMMON_OBJS_ARMHF = $(patsubst %.o, $(OBJDIR_ARMHF)%.o, $(COMMON_OBJS))
COMMON_OBJS_MIPS  = $(patsubst %.o, $(OBJDIR_MIPS)%.o, $(COMMON_OBJS))
COMMON_OBJS_OSX   = $(patsubst %.o, $(OBJDIR_OSX)%.o, $(COMMON_OBJS))

#define all tragets
TARGETS_I386  = $(patsubst %.o, $(DIR_I386)%, $(CMD_OBJS))
TARGETS_X64   = $(patsubst %.o, $(DIR_X64)%, $(CMD_OBJS))
TARGETS_ARMEL = $(patsubst %.o, $(DIR_ARMEL)%, $(CMD_OBJS))
TARGETS_ARMHF = $(patsubst %.o, $(DIR_ARMHF)%, $(CMD_OBJS))
TARGETS_MIPS  = $(patsubst %.o, $(DIR_MIPS)%, $(CMD_OBJS))
TARGETS_OSX   = $(patsubst %.o, $(DIR_OSX)%, $(CMD_OBJS))

#CC compiler for each arch
CC_I386 = gcc
CC_X64 = gcc
ifdef TOOLCHAIN_QARM
CC_ARMEL = $(TOOLCHAIN_QARM)/bin/arm-none-linux-gnueabi-gcc
else
CC_ARMEL = gcc
endif
ifdef TOOLCHAIN_ARMHF
CC_ARMHF = $(TOOLCHAIN_ARMHF)/bin/arm-linux-gnueabihf-gcc
else
CC_ARMHF = gcc
endif
CC_MIPS = mips-openwrt-linux-gcc
CC_OSX = gcc


#CPP compiler for each arch
CPP_I386 = g++
CPP_X64 = g++
ifdef TOOLCHAIN_QARM
CPP_ARMEL = $(TOOLCHAIN_QARM)/bin/arm-none-linux-gnueabi-g++
else
CPP_ARMEL = g++
endif
ifdef TOOLCHAIN_ARMHF
CPP_ARMHF = $(TOOLCHAIN_ARMHF)/bin/arm-linux-gnueabihf-g++
else
CPP_ARMHF = g++
endif
CPP_MIPS = mips-openwrt-linux-g++
CPP_OSX = g++


#CPP compiler for each arch
STRIP_I386 = strip
STRIP_X64 = strip
ifdef TOOLCHAIN_QARM
STRIP_ARMEL = $(TOOLCHAIN_QARM)/bin/arm-none-linux-gnueabi-strip
else
STRIP_ARMEL = strip
endif
ifdef TOOLCHAIN_ARMHF
STRIP_ARMHF = $(TOOLCHAIN_ARMHF)/bin/arm-linux-gnueabihf-strip
else
STRIP_ARMHF = strip
endif
STRIP_MIPS = mips-openwrt-linux-strip
STRIP_OSX = strip


GLOBAL_OPT = -Wall
OPTS_I386 = -O2 -m32 -march=i586
OPTS_X64 = -O2 -m64
OPTS_ARMEL = -I$(STAGING_QARM)/usr/include/ -O2 -mfloat-abi=soft -march=armv5 -marm -DBUILD_ARMEL
OPTS_ARMHF = -I$(STAGING_ARMHF)/usr/include/ -O2 -mfloat-abi=hard -march=armv6 -marm -DBUILD_ARMHF
OPTS_MIPS = -DCPU_BIG_ENDIAN -I$(MIPS_TARGET_ROOT)/usr/include/
OPTS_OSX = -O1 -m64



#link optionsfor each arch
LINK_I386 = -lm -lpthread -lusb-1.0
LINK_X64 = -lm -lpthread -lusb-1.0
LINK_ARMEL = -L$(STAGING_QARM)/usr/lib/ -lm -lpthread -lusb-1.0
LINK_ARMHF = -L$(STAGING_ARMHF)/usr/lib/ -lm -lpthread -lusb-1.0
LINK_MIPS = -L$(MIPS_TARGET_ROOT)/usr/lib/ -lm -lpthread -lusb-1.0
LINK_OSX = -lstdc++ -framework IOKit -framework CoreFoundation


fwd: default

#generic compilation rules
$(OBJDIR_X64)%.o: %.c $(ALL_H)
	@echo compiling $@
	@$(CC_X64) $(OPTS_X64) $(GLOBAL_OPT) -I$(YOCTO_SRC) -c $< -o $@

$(OBJDIR_X64)%.o: %.cpp $(ALL_H)
	@echo compiling $@
	@$(CPP_X64) $(OPTS_X64) $(GLOBAL_OPT) -I$(YOCTO_SRC) -c $< -o $@

$(DIR_X64)%: $(OBJDIR_X64) $(COMMON_OBJS_X64) $(ALL_H) $(CMD_SRC)cmdline_common.h
	@echo compiling cmdline $@
	@$(CPP_X64) $(OPTS_X64) $(GLOBAL_OPT) -I$(YOCTO_SRC) $(CMD_SRC)$*.cpp $(CMD_SRC)cmdline_common.cpp $(COMMON_OBJS_X64) -o $@ $(LINK_X64)

$(OBJDIR_I386)%.o: %.c $(ALL_H)
	@echo compiling $@
	@$(CC_I386) $(OPTS_I386) $(GLOBAL_OPT) -I$(YOCTO_SRC) -c $< -o $@

$(OBJDIR_I386)%.o: %.cpp $(ALL_H)
	@echo compiling $@
	@$(CPP_I386) $(OPTS_I386) $(GLOBAL_OPT) -I$(YOCTO_SRC) -c $< -o $@

$(DIR_I386)%: $(OBJDIR_I386) $(COMMON_OBJS_I386) $(ALL_H) $(CMD_SRC)cmdline_common.h
	@echo compiling cmdline $@
	@$(CPP_I386) $(OPTS_I386) $(GLOBAL_OPT) -I$(YOCTO_SRC) $(CMD_SRC)$*.cpp $(CMD_SRC)cmdline_common.cpp $(COMMON_OBJS_I386) -o $@ $(LINK_I386)

$(OBJDIR_ARMEL)%.o: %.c $(ALL_H)
	@echo compiling $@
	@$(CC_ARMEL) $(OPTS_ARMEL) $(GLOBAL_OPT) -I$(YOCTO_SRC) -c $< -o $@

$(OBJDIR_ARMEL)%.o: %.cpp $(ALL_H)
	@echo compiling $@
	@$(CPP_ARMEL) $(OPTS_ARMEL) $(GLOBAL_OPT) -I$(YOCTO_SRC) -c $< -o $@

$(DIR_ARMEL)%: $(OBJDIR_ARMEL) $(COMMON_OBJS_ARMEL) $(ALL_H) $(CMD_SRC)cmdline_common.h
	@echo compiling cmdline $@
	@$(CPP_ARMEL) $(OPTS_ARMEL) $(GLOBAL_OPT) -I$(YOCTO_SRC) $(CMD_SRC)$*.cpp $(CMD_SRC)cmdline_common.cpp $(COMMON_OBJS_ARMEL) -o $@ $(LINK_ARMEL)

$(OBJDIR_ARMHF)%.o: %.c $(ALL_H)
	@echo compiling $@
	@$(CC_ARMHF) $(OPTS_ARMHF) $(GLOBAL_OPT) -I$(YOCTO_SRC) -c $< -o $@

$(OBJDIR_ARMHF)%.o: %.cpp $(ALL_H)
	@echo compiling $@
	@$(CPP_ARMHF) $(OPTS_ARMHF) $(GLOBAL_OPT) -I$(YOCTO_SRC) -c $< -o $@

$(DIR_ARMHF)%: $(OBJDIR_ARMHF) $(COMMON_OBJS_ARMHF) $(ALL_H) $(CMD_SRC)cmdline_common.h
	@echo compiling cmdline $@
	@$(CPP_ARMHF) $(OPTS_ARMHF) $(GLOBAL_OPT) -I$(YOCTO_SRC) $(CMD_SRC)$*.cpp $(CMD_SRC)cmdline_common.cpp $(COMMON_OBJS_ARMHF) -o $@ $(LINK_ARMHF)

$(OBJDIR_MIPS)%.o: %.c $(ALL_H)
	@echo compiling $@
	@$(CC_MIPS) $(OPTS_MIPS) $(GLOBAL_OPT) -I$(YOCTO_SRC) -c $< -o $@

$(OBJDIR_MIPS)%.o: %.cpp $(ALL_H)
	@echo compiling $@
	@$(CPP_MIPS) $(OPTS_MIPS) $(GLOBAL_OPT) -I$(YOCTO_SRC) -c $< -o $@

$(DIR_MIPS)%: $(OBJDIR_MIPS) $(COMMON_OBJS_MIPS) $(ALL_H) $(CMD_SRC)cmdline_common.h
	@echo compiling cmdline $@
	@$(CPP_MIPS) $(OPTS_MIPS) $(GLOBAL_OPT) -I$(YOCTO_SRC) $(CMD_SRC)$*.cpp $(CMD_SRC)cmdline_common.cpp $(COMMON_OBJS_MIPS) -o $@ $(LINK_MIPS)

$(OBJDIR_OSX)%.o: %.c $(ALL_H)
	@echo compiling $@
	@$(CC_OSX) $(OPTS_OSX) $(GLOBAL_OPT) -I$(YOCTO_SRC) -c $< -o $@

$(OBJDIR_OSX)%.o: %.cpp $(ALL_H)
	@echo compiling $@
	@$(CPP_OSX) $(OPTS_OSX) $(GLOBAL_OPT) -I$(YOCTO_SRC) -c $< -o $@

$(DIR_OSX)%: $(OBJDIR_OSX) $(COMMON_OBJS_OSX) $(ALL_H) $(CMD_SRC)cmdline_common.h
	@echo compiling cmdline $@
	@$(CPP_OSX) $(OPTS_OSX) $(GLOBAL_OPT) -I$(YOCTO_SRC) $(CMD_SRC)$*.cpp $(CMD_SRC)cmdline_common.cpp $(COMMON_OBJS_OSX) -o $@ $(LINK_OSX)


i386: $(TARGETS_I386)

release_i386: $(TARGETS_I386) clean_obj_i386
	@$(STRIP_I386) $(TARGETS_I386)

x64: $(TARGETS_X64)

release_x64: $(TARGETS_X64) clean_obj_x64
	@$(STRIP_X64) $(TARGETS_X64)

armel: $(TARGETS_ARMEL)

release_armel: $(TARGETS_ARMEL) clean_obj_armel
	@$(STRIP_ARMEL) $(TARGETS_ARMEL)

armhf: $(TARGETS_ARMHF)

release_armhf: $(TARGETS_ARMHF) clean_obj_armhf
	@$(STRIP_ARMHF) $(TARGETS_ARMHF)

mips: $(TARGETS_MIPS)
	@$(STRIP_MIPS) $(TARGETS_MIPS)

release_mips: $(TARGETS_MIPS) clean_obj_mips

osx: $(TARGETS_OSX)

release_osx: $(TARGETS_OSX) clean_obj_osx
	@$(STRIP_OSX) $(TARGETS_OSX)

ifeq ($(UNAME), Linux)
#linux
ifeq ($(ARCH), x86_64)
default: x64

release: release_x64 release_i386 release_mips

else
ifeq ($(ARCH),i386)
default: i386

release: release_i386

else
#$(warning $(ARM_BUILD_TYPE))
ifeq ($(ARM_BUILD_TYPE), hf)
default: armhf

release: release_armhf

else
default: armel

release: release_armel

endif
endif
endif
else
#mac os
default: osx

release: release_osx

endif

$(DIR_I386) $(DIR_X64) $(DIR_ARMEL) $(DIR_ARMHF) $(DIR_MIPS) $(DIR_OSX) \
$(OBJDIR_I386) $(OBJDIR_X64) $(OBJDIR_ARMEL) $(OBJDIR_ARMHF) $(OBJDIR_MIPS) $(OBJDIR_OSX):
	@mkdir -p $@

clean_obj_i386:
	@rm -rf $(OBJDIR_I386)

clean_obj_x64:
	@rm -rf $(OBJDIR_X64)

clean_obj_armel:
	@rm -rf $(OBJDIR_ARMEL)

clean_obj_armhf:
	@rm -rf $(OBJDIR_ARMHF)

clean_obj_mips:
	@rm -rf $(OBJDIR_MIPS)

clean_obj_osx:
	@rm -rf $(OBJDIR_OSX)

clean_i386: clean_obj_i386
	@rm -rf $(DIR_I386)

clean_x64: clean_obj_x64
	@rm -rf $(DIR_X64)

clean_armel: clean_obj_armel
	@rm -rf $(DIR_ARMEL)

clean_armhf: clean_obj_armhf
	@rm -rf $(DIR_ARMHF)

clean_mips: clean_obj_mips
	@rm -rf $(DIR_MIPS)

clean_osx: clean_obj_osx
	@rm -rf $(DIR_OSX)

clean: clean_i386 clean_x64 clean_armel clean_armhf clean_mips clean_osx
