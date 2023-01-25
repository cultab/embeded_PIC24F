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
ifeq "$(wildcard nbproject/Makefile-local-LCD.mk)" "nbproject/Makefile-local-LCD.mk"
include nbproject/Makefile-local-LCD.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=LCD
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/embeded_PIC24F.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/embeded_PIC24F.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=main.c src/adc.c src/button.c src/led.c src/timer.c src/lcd.c src/lcd_printf.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/src/adc.o ${OBJECTDIR}/src/button.o ${OBJECTDIR}/src/led.o ${OBJECTDIR}/src/timer.o ${OBJECTDIR}/src/lcd.o ${OBJECTDIR}/src/lcd_printf.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/src/adc.o.d ${OBJECTDIR}/src/button.o.d ${OBJECTDIR}/src/led.o.d ${OBJECTDIR}/src/timer.o.d ${OBJECTDIR}/src/lcd.o.d ${OBJECTDIR}/src/lcd_printf.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/src/adc.o ${OBJECTDIR}/src/button.o ${OBJECTDIR}/src/led.o ${OBJECTDIR}/src/timer.o ${OBJECTDIR}/src/lcd.o ${OBJECTDIR}/src/lcd_printf.o

# Source Files
SOURCEFILES=main.c src/adc.c src/button.c src/led.c src/timer.c src/lcd.c src/lcd_printf.c



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
	${MAKE}  -f nbproject/Makefile-LCD.mk ${DISTDIR}/embeded_PIC24F.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ1024GB610
MP_LINKER_FILE_OPTION=,--script=p24FJ1024GB610.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.o: main.c  .generated_files/flags/LCD/f63dafbc5d885dce5518bb5cf9c29af235803a34 .generated_files/flags/LCD/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_LCD=$(CND_CONF)    $(COMPARISON_BUILD)  -msmall-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/adc.o: src/adc.c  .generated_files/flags/LCD/81701c033fddf1b4ee9c85945c533215584aa819 .generated_files/flags/LCD/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/adc.o.d 
	@${RM} ${OBJECTDIR}/src/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/adc.c  -o ${OBJECTDIR}/src/adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/adc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_LCD=$(CND_CONF)    $(COMPARISON_BUILD)  -msmall-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/button.o: src/button.c  .generated_files/flags/LCD/12fa4e2caadaf1b88034bf61f1d060e0b437ed89 .generated_files/flags/LCD/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/button.o.d 
	@${RM} ${OBJECTDIR}/src/button.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/button.c  -o ${OBJECTDIR}/src/button.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/button.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_LCD=$(CND_CONF)    $(COMPARISON_BUILD)  -msmall-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/led.o: src/led.c  .generated_files/flags/LCD/3e45400c34d5a23864736c72931b397975ee046f .generated_files/flags/LCD/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/led.o.d 
	@${RM} ${OBJECTDIR}/src/led.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/led.c  -o ${OBJECTDIR}/src/led.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/led.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_LCD=$(CND_CONF)    $(COMPARISON_BUILD)  -msmall-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/timer.o: src/timer.c  .generated_files/flags/LCD/168c018c59443093a023a216796e1e97356a15bb .generated_files/flags/LCD/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/timer.o.d 
	@${RM} ${OBJECTDIR}/src/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/timer.c  -o ${OBJECTDIR}/src/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/timer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_LCD=$(CND_CONF)    $(COMPARISON_BUILD)  -msmall-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/lcd.o: src/lcd.c  .generated_files/flags/LCD/15770f9fedef4bde8eb7c2c4b90f27ecd3246a1f .generated_files/flags/LCD/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/lcd.o.d 
	@${RM} ${OBJECTDIR}/src/lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/lcd.c  -o ${OBJECTDIR}/src/lcd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/lcd.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_LCD=$(CND_CONF)    $(COMPARISON_BUILD)  -msmall-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/lcd_printf.o: src/lcd_printf.c  .generated_files/flags/LCD/a4a3485cf6f66f74130c550920c4b70cfbe072af .generated_files/flags/LCD/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/lcd_printf.o.d 
	@${RM} ${OBJECTDIR}/src/lcd_printf.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/lcd_printf.c  -o ${OBJECTDIR}/src/lcd_printf.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/lcd_printf.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_LCD=$(CND_CONF)    $(COMPARISON_BUILD)  -msmall-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/main.o: main.c  .generated_files/flags/LCD/3b0376a66672bc8beec0f224be0ea2f65bad918e .generated_files/flags/LCD/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_LCD=$(CND_CONF)    $(COMPARISON_BUILD)  -msmall-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/adc.o: src/adc.c  .generated_files/flags/LCD/1c388e1193b2d57165924f58c442afe57261a6f6 .generated_files/flags/LCD/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/adc.o.d 
	@${RM} ${OBJECTDIR}/src/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/adc.c  -o ${OBJECTDIR}/src/adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/adc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_LCD=$(CND_CONF)    $(COMPARISON_BUILD)  -msmall-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/button.o: src/button.c  .generated_files/flags/LCD/dd8a5c46fe3609445a6bff94681670979ff9fbcf .generated_files/flags/LCD/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/button.o.d 
	@${RM} ${OBJECTDIR}/src/button.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/button.c  -o ${OBJECTDIR}/src/button.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/button.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_LCD=$(CND_CONF)    $(COMPARISON_BUILD)  -msmall-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/led.o: src/led.c  .generated_files/flags/LCD/fbdce9f67c5a6ee8bfd1423418c484e3d0f67640 .generated_files/flags/LCD/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/led.o.d 
	@${RM} ${OBJECTDIR}/src/led.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/led.c  -o ${OBJECTDIR}/src/led.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/led.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_LCD=$(CND_CONF)    $(COMPARISON_BUILD)  -msmall-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/timer.o: src/timer.c  .generated_files/flags/LCD/6a218d9ab98fd596cb46b2a7efd4ded4e00c7f12 .generated_files/flags/LCD/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/timer.o.d 
	@${RM} ${OBJECTDIR}/src/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/timer.c  -o ${OBJECTDIR}/src/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/timer.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_LCD=$(CND_CONF)    $(COMPARISON_BUILD)  -msmall-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/lcd.o: src/lcd.c  .generated_files/flags/LCD/bb6b9fbab8221c725c84915477de4449034f8a20 .generated_files/flags/LCD/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/lcd.o.d 
	@${RM} ${OBJECTDIR}/src/lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/lcd.c  -o ${OBJECTDIR}/src/lcd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/lcd.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_LCD=$(CND_CONF)    $(COMPARISON_BUILD)  -msmall-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/src/lcd_printf.o: src/lcd_printf.c  .generated_files/flags/LCD/601c9c4ea29a48b26d167365ee13632582d52d92 .generated_files/flags/LCD/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/lcd_printf.o.d 
	@${RM} ${OBJECTDIR}/src/lcd_printf.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/lcd_printf.c  -o ${OBJECTDIR}/src/lcd_printf.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/lcd_printf.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_LCD=$(CND_CONF)    $(COMPARISON_BUILD)  -msmall-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
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
${DISTDIR}/embeded_PIC24F.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/embeded_PIC24F.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_LCD=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81B -mreserve=data@0x81C:0x81D -mreserve=data@0x81E:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x827 -mreserve=data@0x82A:0x84F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/embeded_PIC24F.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/embeded_PIC24F.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_LCD=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}/xc16-bin2hex ${DISTDIR}/embeded_PIC24F.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}
