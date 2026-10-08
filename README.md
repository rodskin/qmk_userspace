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

### keychron/k3_pro/ansi/rgb: hrm

Keychron K3 Pro (ANSI, RGB, USB `3434:0230`), stock Keychron layout plus the
same home row mods as `mimi_qwerty`, on both the Mac and Win base layers
(the side switch picks one):

- `A S D F` = GUI / Alt / Shift / Ctrl, `J K L ;` = Ctrl / Shift / Alt / GUI
  (200 ms, `QUICK_TAP_TERM 0`);
- Caps Lock: tap = Esc, hold = Ctrl (100 ms, like the kanata config of the
  laptop's built-in keyboard);
- both Shifts together = Caps Word (there is no Caps Lock anymore);
- LEDs default to solid white (`RGB_MATRIX_SOLID_COLOR`, saturation 0).
  Defaults only apply when the EEPROM is reset (Keychron factory reset:
  Fn + J + Z for 3 s, which also forgets Bluetooth pairings); otherwise the
  saved setting wins (Fn + Q/A effect, Fn + R/F saturation, Fn + W/S
  brightness, Fn + Tab on/off);
- on the Fn layers J is a plain `KC_J`: the factory reset combo looks for
  `KC_J` and would not see the `LCTL_T(KC_J)` home row mod;
- Fn layers (RGB, Bluetooth, media) unchanged. VIA is disabled, so a keymap
  saved earlier with Keychron Launcher cannot override this one.
- Raw HID reports the active layer and modifiers to the host, same protocol
  as `mimi_qwerty` (Waybar indicator). Keychron's `k3_pro.c` already defines
  `raw_hid_receive` (factory test, Bluetooth module DFU): `rules.mk` renames
  it to `raw_hid_receive_k3pro` when compiling that one file, and the keymap's
  `raw_hid_receive` forwards every other message to it. Layer numbers:
  0 MAC_BASE, 1 MAC_FN, 2 WIN_BASE, 3 WIN_FN.

## Cornifi: build and flash (Fedora Atomic)

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

## Keychron K3 Pro: build and flash (Fedora Atomic)

The K3 Pro is **not** in the official qmk_firmware: it needs Keychron's fork
(branch `wireless_playground`), cloned next to the official one in
`~/qmk_keychron`. The keymap still lives in this repo, under
`keyboards/keychron/k3_pro/ansi/rgb/keymaps/hrm`. Same `qmk` toolbox as the
Cornifi, plus `dfu-util` (the MCU is an STM32, flashed over DFU, not UF2).

One-time setup:

```sh
git clone --depth 1 -b wireless_playground https://github.com/Keychron/qmk_firmware ~/qmk_keychron
cd ~/qmk_keychron && git submodule update --init --depth 1 lib/chibios lib/chibios-contrib lib/printf
toolbox run -c qmk sudo pip install -r ~/qmk_keychron/requirements.txt
toolbox run -c qmk sudo dnf install -y dfu-util
# let the user (and the toolbox) talk to the STM32 bootloader without root
echo 'SUBSYSTEMS=="usb", ATTRS{idVendor}=="0483", ATTRS{idProduct}=="df11", TAG+="uaccess"' \
    | sudo tee /etc/udev/rules.d/50-stm32-dfu.rules
sudo udevadm control --reload-rules
```

Build: the fork's `qmk` CLI predates `qmk.json` version 1.1, so
`qmk compile` cannot see this repo; call `make` with `QMK_USERSPACE`
instead (`lib/lvgl` is cloned automatically on the first build):

```sh
toolbox run -c qmk sh -c 'cd ~/qmk_keychron && make keychron/k3_pro/ansi/rgb:hrm QMK_USERSPACE=$HOME/qmk_userspace'
# -> ~/qmk_userspace/keychron_k3_pro_ansi_rgb_hrm.bin
```

Flash:

1. USB cable plugged in, side switch on **Off**;
2. hold **Esc** (or the reset button under the space bar), switch to
   **Cable**, release: the keyboard shows up as `0483:df11` (`lsusb`);
3. ```sh
   toolbox run -c qmk dfu-util -a 0 -d 0483:df11 -s 0x08000000:leave \
       -D ~/qmk_userspace/keychron_k3_pro_ansi_rgb_hrm.bin
   ```

Updating the fork: `cd ~/qmk_keychron && git pull && git submodule update --init --depth 1 lib/chibios lib/chibios-contrib lib/printf`.

## Which keyboard, which QMK

| Keyboard | QMK tree | Keymap in this repo | Build | Flash |
|---|---|---|---|---|
| Cornifi (RP2040) | `~/qmk_firmware` (official) | `keyboards/cornifi/keymaps/mimi_qwerty` | `cornifi build` / `qmk compile` | `cornifi flash` (UF2) |
| Keychron K3 Pro (STM32) | `~/qmk_keychron` (Keychron fork) | `keyboards/keychron/k3_pro/ansi/rgb/keymaps/hrm` | `make … QMK_USERSPACE=…` | `dfu-util` |

The laptop's built-in keyboard has no QMK: kanata (`~/.config/kanata/kanata.kbd`)
gives it the same home row mods and Caps Lock, and only grabs that device, so
external QMK keyboards are never remapped twice.
