# List of all the board related files.
BOARDSRC = $(BOARD_PATH)/boards/STM32F4_DISCO/board.c

# Required include directories
BOARDINC = $(BOARD_PATH)/boards/STM32F4_DISCO

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
