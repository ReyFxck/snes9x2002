# PS2 HostFS fix (RetroArch 1.22.2)

This branch carries the source patches used for the PS2 test build with the
Snes9x 2002 core statically linked.

## Problems fixed

1. Some NetherSX2/PCSX2 HostFS implementations return regular files with
   `dirent.d_type == DT_DIR`. RetroArch then shows ROMs, ZIP files and ELF
   files as `[DIR]`.
2. RetroArch 1.22.2 uses older PS2DEV USB-driver and gsKit callback APIs.
3. After selecting a ROM, the PS2 static build opens `Suggested Cores` and
   reports `No Cores Available`, even though Snes9x 2002 is linked.
4. NetherSX2 can reject `host:/file` as an absolute path outside the ELF
   directory, producing `Could not read content from file`.

## Patches

- `0001` verifies suspicious `host:` entries with `opendir()`.
- `0002` updates RetroArch 1.22.2 for the current PS2DEV APIs.
- `0003` enables `LOAD_WITHOUT_CORE_INFO` so content loads directly with the
  linked Snes9x 2002 core.
- `0004` normalizes PS2 HostFS file and stat paths from `host:/path` to
  `host:path`, the relative form accepted by NetherSX2.

The HostFS workarounds are limited to PS2 `host:` and do not change USB,
memory-card or HDD browsing.

## Apply

Apply all files under `patches/retroarch-v1.22.2/`, in numeric order, to the
RetroArch `v1.22.2` tag.

The test build was compiled with `snes9x2002_libretro_ps2.a` from this
repository and the official PS2DEV prebuilt toolchain.

## Device test

Start with an uncompressed `.sfc` or `.smc` file on `host:`. The ROM
should load directly without opening the Suggested Cores screen or showing
`Could not read content from file`. Test ZIP loading separately after direct
ROM loading is confirmed.
