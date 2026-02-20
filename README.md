# librec-static-demo

This repo provides a minimal Windows MSVC **static-link** build pipeline via GitHub Actions. It is designed to produce many statically linked binaries so you can collect Ghidra decompilations of library functions for model fine-tuning.

## What it builds

- A small C++ executable (`librec_static_demo`) that links several popular libraries via **vcpkg**.
- Uses the MSVC static CRT (`/MT` or `/MTd`) through modern CMake settings.
- GitHub Actions workflow builds on `windows-latest` using `x64-windows-static` triplet.

## Project structure

```
.
├── CMakeLists.txt
├── CMakePresets.json
├── vcpkg.json
├── src/
│   └── main.cpp
└── .github/
    └── workflows/
        └── windows-msvc-static.yml
```

## Build locally (Windows)

Prerequisites:
- Visual Studio 2022 (MSVC)
- CMake 3.20+
- vcpkg (in the repo root as `vcpkg/`)

```powershell
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat
cd ..

cmake --preset windows-static
cmake --build --preset windows-static-release
```

## GitHub Actions

The workflow `windows-msvc-static.yml`:

- Checks out the repo
- Sets vcpkg triplet to `x64-windows-static`
- Uses `lukka/run-vcpkg@v11` for vcpkg setup and manifest install
- Configures and builds with MSVC static CRT

## Extending with more libraries

1. Add dependencies in `vcpkg.json`
2. Add `find_package(...)` and `target_link_libraries(...)` entries in `CMakeLists.txt`
3. Add corresponding include/use in `src/main.cpp`

## Notes

- `x64-windows-static` produces static libraries; CRT static linking is controlled by `CMAKE_MSVC_RUNTIME_LIBRARY`.
- If you want a different triplet or a custom one, adjust `VCPKG_DEFAULT_TRIPLET` in the workflow and presets.
