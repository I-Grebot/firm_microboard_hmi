#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/microBoard_hmi.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/microBoard_hmi.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/ff.c ../src/xprintf.c ../src/mmc_pic33e.c ../src/option/unicode.c ../../common/fifo/src/fifo.c ../src/microBoard_hmi.c ../src/oscillator.c ../src/spi1.c ../src/nav.c ../src/ssd1306.c ../src/ssd1306_const.c ../src/led.c ../src/pwm.c ../src/uart_pic33e.c ../src/fatfs.c ../src/nav_menu.c ../src/buzzer.c ../src/ctrl_if.c ../src/ssd1306_widgets.c ../src/sd_card.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1360937237/ff.o ${OBJECTDIR}/_ext/1360937237/xprintf.o ${OBJECTDIR}/_ext/1360937237/mmc_pic33e.o ${OBJECTDIR}/_ext/49367377/unicode.o ${OBJECTDIR}/_ext/327233499/fifo.o ${OBJECTDIR}/_ext/1360937237/microBoard_hmi.o ${OBJECTDIR}/_ext/1360937237/oscillator.o ${OBJECTDIR}/_ext/1360937237/spi1.o ${OBJECTDIR}/_ext/1360937237/nav.o ${OBJECTDIR}/_ext/1360937237/ssd1306.o ${OBJECTDIR}/_ext/1360937237/ssd1306_const.o ${OBJECTDIR}/_ext/1360937237/led.o ${OBJECTDIR}/_ext/1360937237/pwm.o ${OBJECTDIR}/_ext/1360937237/uart_pic33e.o ${OBJECTDIR}/_ext/1360937237/fatfs.o ${OBJECTDIR}/_ext/1360937237/nav_menu.o ${OBJECTDIR}/_ext/1360937237/buzzer.o ${OBJECTDIR}/_ext/1360937237/ctrl_if.o ${OBJECTDIR}/_ext/1360937237/ssd1306_widgets.o ${OBJECTDIR}/_ext/1360937237/sd_card.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1360937237/ff.o.d ${OBJECTDIR}/_ext/1360937237/xprintf.o.d ${OBJECTDIR}/_ext/1360937237/mmc_pic33e.o.d ${OBJECTDIR}/_ext/49367377/unicode.o.d ${OBJECTDIR}/_ext/327233499/fifo.o.d ${OBJECTDIR}/_ext/1360937237/microBoard_hmi.o.d ${OBJECTDIR}/_ext/1360937237/oscillator.o.d ${OBJECTDIR}/_ext/1360937237/spi1.o.d ${OBJECTDIR}/_ext/1360937237/nav.o.d ${OBJECTDIR}/_ext/1360937237/ssd1306.o.d ${OBJECTDIR}/_ext/1360937237/ssd1306_const.o.d ${OBJECTDIR}/_ext/1360937237/led.o.d ${OBJECTDIR}/_ext/1360937237/pwm.o.d ${OBJECTDIR}/_ext/1360937237/uart_pic33e.o.d ${OBJECTDIR}/_ext/1360937237/fatfs.o.d ${OBJECTDIR}/_ext/1360937237/nav_menu.o.d ${OBJECTDIR}/_ext/1360937237/buzzer.o.d ${OBJECTDIR}/_ext/1360937237/ctrl_if.o.d ${OBJECTDIR}/_ext/1360937237/ssd1306_widgets.o.d ${OBJECTDIR}/_ext/1360937237/sd_card.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1360937237/ff.o ${OBJECTDIR}/_ext/1360937237/xprintf.o ${OBJECTDIR}/_ext/1360937237/mmc_pic33e.o ${OBJECTDIR}/_ext/49367377/unicode.o ${OBJECTDIR}/_ext/327233499/fifo.o ${OBJECTDIR}/_ext/1360937237/microBoard_hmi.o ${OBJECTDIR}/_ext/1360937237/oscillator.o ${OBJECTDIR}/_ext/1360937237/spi1.o ${OBJECTDIR}/_ext/1360937237/nav.o ${OBJECTDIR}/_ext/1360937237/ssd1306.o ${OBJECTDIR}/_ext/1360937237/ssd1306_const.o ${OBJECTDIR}/_ext/1360937237/led.o ${OBJECTDIR}/_ext/1360937237/pwm.o ${OBJECTDIR}/_ext/1360937237/uart_pic33e.o ${OBJECTDIR}/_ext/1360937237/fatfs.o ${OBJECTDIR}/_ext/1360937237/nav_menu.o ${OBJECTDIR}/_ext/1360937237/buzzer.o ${OBJECTDIR}/_ext/1360937237/ctrl_if.o ${OBJECTDIR}/_ext/1360937237/ssd1306_widgets.o ${OBJECTDIR}/_ext/1360937237/sd_card.o

# Source Files
SOURCEFILES=../src/ff.c ../src/xprintf.c ../src/mmc_pic33e.c ../src/option/unicode.c ../../common/fifo/src/fifo.c ../src/microBoard_hmi.c ../src/oscillator.c ../src/spi1.c ../src/nav.c ../src/ssd1306.c ../src/ssd1306_const.c ../src/led.c ../src/pwm.c ../src/uart_pic33e.c ../src/fatfs.c ../src/nav_menu.c ../src/buzzer.c ../src/ctrl_if.c ../src/ssd1306_widgets.c ../src/sd_card.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/microBoard_hmi.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP512GM604
MP_LINKER_FILE_OPTION=,--script=p33EP512GM604.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1360937237/ff.o: ../src/ff.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ff.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ff.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/ff.c  -o ${OBJECTDIR}/_ext/1360937237/ff.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/ff.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ff.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/xprintf.o: ../src/xprintf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/xprintf.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/xprintf.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/xprintf.c  -o ${OBJECTDIR}/_ext/1360937237/xprintf.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/xprintf.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/xprintf.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/mmc_pic33e.o: ../src/mmc_pic33e.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mmc_pic33e.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mmc_pic33e.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/mmc_pic33e.c  -o ${OBJECTDIR}/_ext/1360937237/mmc_pic33e.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/mmc_pic33e.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/mmc_pic33e.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/49367377/unicode.o: ../src/option/unicode.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/49367377 
	@${RM} ${OBJECTDIR}/_ext/49367377/unicode.o.d 
	@${RM} ${OBJECTDIR}/_ext/49367377/unicode.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/option/unicode.c  -o ${OBJECTDIR}/_ext/49367377/unicode.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/49367377/unicode.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/49367377/unicode.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/327233499/fifo.o: ../../common/fifo/src/fifo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/327233499 
	@${RM} ${OBJECTDIR}/_ext/327233499/fifo.o.d 
	@${RM} ${OBJECTDIR}/_ext/327233499/fifo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../common/fifo/src/fifo.c  -o ${OBJECTDIR}/_ext/327233499/fifo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/327233499/fifo.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/327233499/fifo.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/microBoard_hmi.o: ../src/microBoard_hmi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/microBoard_hmi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/microBoard_hmi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/microBoard_hmi.c  -o ${OBJECTDIR}/_ext/1360937237/microBoard_hmi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/microBoard_hmi.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/microBoard_hmi.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/oscillator.o: ../src/oscillator.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/oscillator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/oscillator.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/oscillator.c  -o ${OBJECTDIR}/_ext/1360937237/oscillator.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/oscillator.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/oscillator.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/spi1.o: ../src/spi1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/spi1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/spi1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/spi1.c  -o ${OBJECTDIR}/_ext/1360937237/spi1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/spi1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/spi1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/nav.o: ../src/nav.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/nav.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/nav.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/nav.c  -o ${OBJECTDIR}/_ext/1360937237/nav.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/nav.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/nav.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/ssd1306.o: ../src/ssd1306.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ssd1306.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ssd1306.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/ssd1306.c  -o ${OBJECTDIR}/_ext/1360937237/ssd1306.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/ssd1306.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ssd1306.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/ssd1306_const.o: ../src/ssd1306_const.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ssd1306_const.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ssd1306_const.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/ssd1306_const.c  -o ${OBJECTDIR}/_ext/1360937237/ssd1306_const.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/ssd1306_const.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ssd1306_const.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/led.o: ../src/led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/led.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/led.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/led.c  -o ${OBJECTDIR}/_ext/1360937237/led.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/led.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/led.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/pwm.o: ../src/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/pwm.c  -o ${OBJECTDIR}/_ext/1360937237/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/pwm.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/pwm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/uart_pic33e.o: ../src/uart_pic33e.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/uart_pic33e.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/uart_pic33e.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/uart_pic33e.c  -o ${OBJECTDIR}/_ext/1360937237/uart_pic33e.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/uart_pic33e.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/uart_pic33e.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/fatfs.o: ../src/fatfs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/fatfs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/fatfs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/fatfs.c  -o ${OBJECTDIR}/_ext/1360937237/fatfs.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/fatfs.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/fatfs.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/nav_menu.o: ../src/nav_menu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/nav_menu.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/nav_menu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/nav_menu.c  -o ${OBJECTDIR}/_ext/1360937237/nav_menu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/nav_menu.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/nav_menu.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/buzzer.o: ../src/buzzer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/buzzer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/buzzer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/buzzer.c  -o ${OBJECTDIR}/_ext/1360937237/buzzer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/buzzer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/buzzer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/ctrl_if.o: ../src/ctrl_if.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ctrl_if.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ctrl_if.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/ctrl_if.c  -o ${OBJECTDIR}/_ext/1360937237/ctrl_if.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/ctrl_if.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ctrl_if.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/ssd1306_widgets.o: ../src/ssd1306_widgets.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ssd1306_widgets.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ssd1306_widgets.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/ssd1306_widgets.c  -o ${OBJECTDIR}/_ext/1360937237/ssd1306_widgets.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/ssd1306_widgets.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ssd1306_widgets.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/sd_card.o: ../src/sd_card.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/sd_card.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/sd_card.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/sd_card.c  -o ${OBJECTDIR}/_ext/1360937237/sd_card.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/sd_card.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/sd_card.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1360937237/ff.o: ../src/ff.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ff.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ff.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/ff.c  -o ${OBJECTDIR}/_ext/1360937237/ff.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/ff.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ff.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/xprintf.o: ../src/xprintf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/xprintf.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/xprintf.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/xprintf.c  -o ${OBJECTDIR}/_ext/1360937237/xprintf.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/xprintf.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/xprintf.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/mmc_pic33e.o: ../src/mmc_pic33e.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mmc_pic33e.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mmc_pic33e.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/mmc_pic33e.c  -o ${OBJECTDIR}/_ext/1360937237/mmc_pic33e.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/mmc_pic33e.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/mmc_pic33e.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/49367377/unicode.o: ../src/option/unicode.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/49367377 
	@${RM} ${OBJECTDIR}/_ext/49367377/unicode.o.d 
	@${RM} ${OBJECTDIR}/_ext/49367377/unicode.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/option/unicode.c  -o ${OBJECTDIR}/_ext/49367377/unicode.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/49367377/unicode.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/49367377/unicode.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/327233499/fifo.o: ../../common/fifo/src/fifo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/327233499 
	@${RM} ${OBJECTDIR}/_ext/327233499/fifo.o.d 
	@${RM} ${OBJECTDIR}/_ext/327233499/fifo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../common/fifo/src/fifo.c  -o ${OBJECTDIR}/_ext/327233499/fifo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/327233499/fifo.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/327233499/fifo.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/microBoard_hmi.o: ../src/microBoard_hmi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/microBoard_hmi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/microBoard_hmi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/microBoard_hmi.c  -o ${OBJECTDIR}/_ext/1360937237/microBoard_hmi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/microBoard_hmi.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/microBoard_hmi.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/oscillator.o: ../src/oscillator.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/oscillator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/oscillator.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/oscillator.c  -o ${OBJECTDIR}/_ext/1360937237/oscillator.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/oscillator.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/oscillator.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/spi1.o: ../src/spi1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/spi1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/spi1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/spi1.c  -o ${OBJECTDIR}/_ext/1360937237/spi1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/spi1.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/spi1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/nav.o: ../src/nav.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/nav.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/nav.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/nav.c  -o ${OBJECTDIR}/_ext/1360937237/nav.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/nav.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/nav.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/ssd1306.o: ../src/ssd1306.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ssd1306.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ssd1306.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/ssd1306.c  -o ${OBJECTDIR}/_ext/1360937237/ssd1306.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/ssd1306.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ssd1306.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/ssd1306_const.o: ../src/ssd1306_const.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ssd1306_const.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ssd1306_const.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/ssd1306_const.c  -o ${OBJECTDIR}/_ext/1360937237/ssd1306_const.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/ssd1306_const.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ssd1306_const.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/led.o: ../src/led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/led.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/led.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/led.c  -o ${OBJECTDIR}/_ext/1360937237/led.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/led.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/led.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/pwm.o: ../src/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/pwm.c  -o ${OBJECTDIR}/_ext/1360937237/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/pwm.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/pwm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/uart_pic33e.o: ../src/uart_pic33e.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/uart_pic33e.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/uart_pic33e.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/uart_pic33e.c  -o ${OBJECTDIR}/_ext/1360937237/uart_pic33e.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/uart_pic33e.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/uart_pic33e.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/fatfs.o: ../src/fatfs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/fatfs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/fatfs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/fatfs.c  -o ${OBJECTDIR}/_ext/1360937237/fatfs.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/fatfs.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/fatfs.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/nav_menu.o: ../src/nav_menu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/nav_menu.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/nav_menu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/nav_menu.c  -o ${OBJECTDIR}/_ext/1360937237/nav_menu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/nav_menu.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/nav_menu.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/buzzer.o: ../src/buzzer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/buzzer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/buzzer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/buzzer.c  -o ${OBJECTDIR}/_ext/1360937237/buzzer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/buzzer.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/buzzer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/ctrl_if.o: ../src/ctrl_if.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ctrl_if.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ctrl_if.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/ctrl_if.c  -o ${OBJECTDIR}/_ext/1360937237/ctrl_if.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/ctrl_if.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ctrl_if.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/ssd1306_widgets.o: ../src/ssd1306_widgets.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ssd1306_widgets.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ssd1306_widgets.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/ssd1306_widgets.c  -o ${OBJECTDIR}/_ext/1360937237/ssd1306_widgets.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/ssd1306_widgets.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ssd1306_widgets.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/sd_card.o: ../src/sd_card.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/sd_card.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/sd_card.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/sd_card.c  -o ${OBJECTDIR}/_ext/1360937237/sd_card.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/sd_card.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -O0 -I"../src" -I"../../common/fifo/src" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/sd_card.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/microBoard_hmi.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/microBoard_hmi.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf  -mreserve=data@0x1000:0x101B -mreserve=data@0x101C:0x101D -mreserve=data@0x101E:0x101F -mreserve=data@0x1020:0x1021 -mreserve=data@0x1022:0x1023 -mreserve=data@0x1024:0x1027 -mreserve=data@0x1028:0x104F   -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--heap=8192,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/microBoard_hmi.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/microBoard_hmi.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--heap=8192,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/microBoard_hmi.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
