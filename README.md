# v3lmx QMK Userspace

original readme: [github](https://github.com/qmk/qmk_userspace/blob/main/README.md)

userspace manual: [qmk docs](https://docs.qmk.fm/newbs_external_userspace)

## Layouts

### mimi

This is a layout based on [miryoku](https://github.com/manna-harbour/miryoku), without the more advanced features (eg. alternative layers, most tap dance buttons).
It also includes 4 extra keys for the extra keys on the (name tbd).
The goal of essentially forking miryoku is to have a simpler base to start modifications (namely french accented keys and symbols).

```
brew install qmk/qmk/qmk
git clone https://github.com/v3lmx/qmk_firmware.git
qmk setup
git clone https://github.com/v3lmx/qmk_userspace.git
qmk config user.overlay_dir="~/qmk_userspace"
qmk compile -kb cornifi -km mimi
```
