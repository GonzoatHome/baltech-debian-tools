# BALTECH Debian Tools

Native Linux command-line and Qt tools for BALTECH RFID readers. This repository contains only the tools, their SDK build dependencies, and a Debian udev rule; it does not include prebuilt binaries, appnotes, or the legacy wrapper.

## Build

On Debian or Ubuntu, install the CLI dependencies and build the command-line tools:

```sh
sudo apt install build-essential cmake libssl-dev libudev-dev libxml2-dev
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --target baltech_id_engine_explorer baltech_firmware_uploader -j
```

The executables are written to `build/bin`. `libxml2-dev` enables legacy `.bec` support. To build the optional Qt 6 desktop applications, install `qt6-base-dev` and build `baltech_id_engine_explorer_gui` and `baltech_firmware_uploader_gui` as well.

The Explorer CLI opens an interactive BRP prompt. Its `help` command lists safe examples and common command families. Raw BRP commands can change reader state or configuration; check the BALTECH command reference before sending them.

The Firmware Uploader supports wired uploads of `.bec`, BEC2, and BF3 files. Wireless upload is not implemented. The desktop Uploader requires Qt 6; it does not provide ConfigCard creation.

## Reader Access

Install the included udev rule to allow members of the `baltech` group to access BALTECH USB/HID readers:

```sh
sudo groupadd --system baltech
sudo usermod -aG baltech "$USER"
sudo install -m 0644 tools/desktop/99-baltech-reader.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules
sudo udevadm trigger
```

Log out and back in for the new group membership to take effect.

## Licensing

The repository's existing top-level `LICENSE` is retained. BALTECH SDK source files are provided under their MIT license; see [`licenses/BALTECH-SDK-MIT.txt`](licenses/BALTECH-SDK-MIT.txt). Third-party notices remain alongside their source code.