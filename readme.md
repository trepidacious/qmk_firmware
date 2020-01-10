# Great Mountain Lizard

Development of GML keyboards.
1. If you clone this without cloning submodules (e.g. using Github Desktop) then you need to run `make git-submodule` before making anything else.
2. To pull from upstream, see [Syncing a fork](https://help.github.com/en/github/collaborating-with-issues-and-pull-requests/syncing-a-fork). If Github desktop was used to clone, upstream is already configured. Essentially, use:
   ```
   git fetch upstream
   git checkout master
   git merge upstream/master
   ```
   Then push the commit that has been created to update the fork to upstream.
3. You just need the arm stuff from install instructions, plus openocd to flash:
   ```
   brew tap osx-cross/avr
   brew tap PX4/homebrew-px4
   brew update
   brew install gcc-arm-none-eabi
   brew install openocd
   ```
4. `make gml1`
5. To flash with openocd, use the `.elf` file in `.build` dir in root of project, with `openocd -f ~/Documents/GitHub/brew/share/openocd/scripts/board/stm32f4discovery.cfg -c "program .build/gml1_default.elf verify reset exit"`
6. Update `.vscode/c_cpp_properies.json` with your brew installation path if necessary.

If you make changes to a submodule, e/g/ `lib/chibios`, you can revert these when finished with:
```bash
git submodule deinit -f .
git submodule update --init
```

To flash two boards with dfu, distinguish by serial - find this with `dfu-util --list` and then something like 
```
dfu-util -a 0 -S 207F36A9424D --dfuse-address 0x08000000 -D .build/gml1_default.bin; dfu-util -a 0 -S 2073368F424D --dfuse-address 0x08000000 -D .build/gml1_default.bin
```

# Quantum Mechanical Keyboard Firmware

[![Current Version](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![Build Status](https://travis-ci.org/qmk/qmk_firmware.svg?branch=master)](https://travis-ci.org/qmk/qmk_firmware)
[![Discord](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/Uq7gcHh)
[![Docs Status](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![GitHub contributors](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![GitHub forks](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

This is a keyboard firmware based on the [tmk\_keyboard firmware](https://github.com/tmk/tmk_keyboard) with some useful features for Atmel AVR and ARM controllers, and more specifically, the [OLKB product line](https://olkb.com), the [ErgoDox EZ](https://ergodox-ez.com) keyboard, and the [Clueboard product line](https://clueboard.co).

## Documentation

* [See the official documentation on docs.qmk.fm](https://docs.qmk.fm)

The docs are powered by [Docsify](https://docsify.js.org/) and hosted on [GitHub](/docs/). They are also viewable offline; see [Previewing the Documentation](https://docs.qmk.fm/#/contributing?id=previewing-the-documentation) for more details.

You can request changes by making a fork and opening a [pull request](https://github.com/qmk/qmk_firmware/pulls), or by clicking the "Edit this page" link at the bottom of any page.

## Supported Keyboards

* [Planck](/keyboards/planck/)
* [Preonic](/keyboards/preonic/)
* [ErgoDox EZ](/keyboards/ergodox_ez/)
* [Clueboard](/keyboards/clueboard/)
* [Cluepad](/keyboards/clueboard/17/)
* [Atreus](/keyboards/atreus/)

The project also includes community support for [lots of other keyboards](/keyboards/).

## Maintainers

QMK is developed and maintained by Jack Humbert of OLKB with contributions from the community, and of course, [Hasu](https://github.com/tmk). The OLKB product firmwares are maintained by [Jack Humbert](https://github.com/jackhumbert), the Ergodox EZ by [ZSA Technology Labs](https://github.com/zsa), the Clueboard by [Zach White](https://github.com/skullydazed), and the Atreus by [Phil Hagelberg](https://github.com/technomancy).

## Official Website

[qmk.fm](https://qmk.fm) is the official website of QMK, where you can find links to this page, the documentation, and the keyboards supported by QMK.
