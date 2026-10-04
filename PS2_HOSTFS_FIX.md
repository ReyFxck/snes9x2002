# PS2 HostFS fix (RetroArch 1.22.2)

This branch carries the source patches used for the PS2 test build with the
Snes9x 2002 core statically linked.

## Problem

On some NetherSX2/PCSX2 HostFS implementations, regular files are returned with
`dirent.d_type == DT_DIR`. RetroArch then shows ROMs, ZIP files and ELF files
as `[DIR]`, and selecting an uncompressed ROM ends with
`Directory Not Found`.

## Fix

The first patch verifies suspicious `host:` entries with `opendir()` before
treating them as directories. The workaround is limited to PS2 HostFS and does
not change USB, memory-card or HDD browsing.

The second patch updates RetroArch 1.22.2 for the current PS2DEV USB-driver and
gsKit callback APIs.

## Apply

Apply both files under `patches/retroarch-v1.22.2/`, in numeric order, to the
RetroArch `v1.22.2` tag.

The test build was compiled with `snes9x2002_libretro_ps2.a` from this
repository and the official PS2DEV prebuilt toolchain.

## Device test

Start with an uncompressed `.sfc` or `.smc` file on `host:`. ZIP loading
should be tested separately after direct ROM loading is confirmed.
