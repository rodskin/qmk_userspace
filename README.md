# v3lmx QMK Userspace

original readme: [github](https://github.com/qmk/qmk_userspace/blob/main/README.md)

userspace manual: [qmk docs](https://docs.qmk.fm/newbs_external_userspace)

## Layouts

### mimi

This is a layout based on [miryoku](https://github.com/manna-harbour/miryoku), without the more advanced features (eg. alternative layers, most tap dance buttons).
It also includes 4 extra keys for the extra keys on the (name tbd).
The goal of essentially forking miryoku is to have a simpler base to start modifications (namely french accented keys and symbols).

### mimi_qwerty

Same as `mimi` with a QWERTY base layer. Set up for Linux (`us altgr-intl`
xkb layout, which the accent macros rely on: AltGr + `'` / `` ` `` / `"` /
`6` dead keys):

- NAV copy/paste/undo/redo send Ctrl+C/V/X/Z/Y;
- Raw HID reports the active layer and modifiers to the host (Waybar
  indicator). The keyboard only sends after the host polled it in the last
  3 s (`{0x4C}`), so it never stalls when nothing reads it. Message:
  `{0x4C, layer, get_mods(), 0…}` (32 bytes).

## Build and flash (Fedora Atomic)

The keyboard (`cornifi`, RP2040) is in the official
[qmk_firmware](https://github.com/qmk/qmk_firmware). Building happens in a
`qmk` toolbox; on my machine the `cornifi` script (chezmoi dotfiles) wraps it:

```sh
cornifi setup   # toolbox + qmk CLI + ARM compiler, clones qmk_firmware and this repo
cornifi edit    # edit keyboards/cornifi/keymaps/mimi_qwerty/keymap.c
cornifi build   # -> cornifi_mimi_qwerty.uf2
cornifi flash   # double-tap reset on each half, the .uf2 is copied to the RPI-RP2 drive
```

By hand:

```sh
toolbox create --distro fedora --release 44 qmk
toolbox enter qmk
sudo dnf install git make python3-pip arm-none-eabi-gcc-cs arm-none-eabi-gcc-cs-c++ arm-none-eabi-newlib
sudo pip install qmk
qmk setup -y -H ~/qmk_firmware
git clone git@github.com:rodskin/qmk_userspace.git ~/qmk_userspace
qmk config user.overlay_dir="$HOME/qmk_userspace"
qmk compile -kb cornifi -km mimi_qwerty
```

Flash: double-tap the reset button of a half (or hold a layer key and
double-tap the outer top key), copy `cornifi_mimi_qwerty.uf2` onto the
`RPI-RP2` drive. Do both halves; the USB cable goes into the left half.
