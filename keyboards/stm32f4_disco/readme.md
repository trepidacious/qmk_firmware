# stm32f4_disco

Simple direct-scan keyboard using stm32f4_disco. Connect switches to PA2 and PA3 (each switch is between a pin and ground). This will type `0` and `1`.

## Generating board files

To generate a new STM32F4xx board file from the Chibios XML configuration:

1. Copy the `STM32F4_DISCO` dir and rename to your new board name.
2. In the `cfg` directory of your new board directory, edit `board.chcfg`
   * Change the `board_id` to match the board directory.
   * Change the `board_name`
   * Change the `subtype` - note if you are moving to a non-F4 processor, you will need the notes below.
3. Run `fmpp -C board.fmpp`. You will need [fmpp](http://fmpp.sourceforge.net/manual.html) installed, on macOS the version in brew worked (`FMPP version 0.9.16, build 2018-09-03T21:47:30Z` at time of writing).
4. Check that you have updated `board.c`, `board.h` and `board.mk` files in the main board directory (i.e. one up from `cfg`).
5. Specify the new board name in `rules.mk`, `BOARD` define.

### Notes on board file generation

When ChibiOS version is updated, hopefully it will hit a version of ChibiOS that actually has the correct FTL templates in the expected location under `tools/ftl/processors/boards/` - this seems to be the case for trunk, and the v18 and v19 stable development branches, but not for v17. At this point it should be possible to reference the templates in `$(CHIBIOS)` rather than having a copy in the keyboard's dir, and use the `board.chcfg` from a demo project as a basis.

To support a new family (other than F4 that has been done), you will need to dig out the templates from the `v18.2.x` branch of ChibiOS. You may need to use the [OSDN SVN](http://svn.osdn.net/svnroot/chibios/) rather than the git mirror. They templates should be at `tools/ftl/processors/boards/FAMILY/templates/board.X.ftl`, where `FAMILY` is something like `stm32f4xx` and `X` is `c`, `h` and `mk`. Put the `.ftl` files under the `boards/templates/FAMILY` dir in the keyboard directory. You should now be able to reference them in the `.fmpp` file in your board's `cfg` dir, as `sourceRoot`. You can now run the generation as described above, and compare the output to a ChibiOS v17 board file for the same family (e.g. for the F4, I checked the output against the 407 disco board file in ChibiOS). Look for any non-cosmetic differences and then modify the FTL template it so that the output matches .This may consist mostly of making the checks against HAL version 4.0.x actually check against 3.0.x, which should be the version specified in your `board.chcfg`. You may get some cosmetic differences in output that can be ignored, but you need to end up with the same or compatible contents in the .c, .h and .mk files generated.
