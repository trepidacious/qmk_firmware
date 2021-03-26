# List of all the board related files.
BOARDSRC = $(BOARD_PATH)/boards/ADAFRUIT_FEATHER_EXPRESS/board.c

# Required include directories
BOARDINC = $(BOARD_PATH)/boards/ADAFRUIT_FEATHER_EXPRESS

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
