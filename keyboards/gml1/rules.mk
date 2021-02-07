# project specific files
# SRC =	matrix.c \
# 	    led.c

## chip/board settings
# the next two should match the directories in
#  <chibios>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
MCU_FAMILY = STM32
MCU_SERIES = STM32F4xx
# linker script to use
# it should exist either in <chibios>/os/common/startup/ARMCMx/compilers/GCC/ld
#  or <this_dir>/ld/
MCU_LDSCRIPT = STM32F405xG
# startup code to use
# is should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
MCU_STARTUP = stm32f4xx
# it should exist either in <chibios>/os/hal/boards/
#  or <this_dir>/boards
BOARD = ADAFRUIT_FEATHER_EXPRESS
# Cortex version
# Teensy LC is cortex-m0; Teensy 3.x are cortex-m4
MCU  = cortex-m4
# ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
ARMV = 7
# If you want to be able to jump to bootloader from firmware on STM32 MCUs,
# set the correct BOOTLOADER_ADDRESS. Either set it here, or define it in
# ./bootloader_defs.h or in ./boards/<FOO>/bootloader_defs.h (if you have
# a custom board definition that you plan to reuse).
# If you're not setting it here, leave it commented out.
# It is chip dependent, the correct number can be looked up here (page 175):
# http://www.st.com/web/en/resource/technical/document/application_note/CD00167594.pdf
# This also requires a patch to chibios:
#   <tmk_dir>/tmk_core/tool/chibios/ch-bootloader-jump.patch
#STM32_BOOTLOADER_ADDRESS = 0x1FFF0000

# Build Options

# BOOTMAGIC_ENABLE = yes      # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes	    # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE = no            # USB Nkey Rollover

# RGBLIGHT_ENABLE = yes

NO_USB_STARTUP_CHECK = yes

# NO_USB_STARTUP_CHECK = no   # Wait for USB before startup
# WAIT_FOR_USB = no

# Disable for ARM
LINK_TIME_OPTIMIZATION_ENABLE = no

CUSTOM_MATRIX = no # No custom matrix file

DEFAULT_FOLDER = gml1

WPM_ENABLE = yes

# We don't use any features that use i2c so we need to add it ourselves
SRC += i2c_master.c
