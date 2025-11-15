# 3D Solar System (C++ / OpenGL)

A minimal experiment that renders a sun and an earth mesh with OpenGL and GLFW.

## Building

```bash
cmake -S . -B build
cmake --build build
```

The executable is emitted to `build/` (or wherever your generator writes binaries).

Every push and pull request is automatically built on GitHub Actions (see [`.github/workflows/cmake.yml`](.github/workflows/cmake.yml)) to ensure
the project continues to compile with the packaged toolchain.

## Assets

Texture lookups in `src/main.cpp` assume two files exist:

- `assets/sun.jpg`
- `assets/Earth (A).jpg`

See `assets/README.md` for details on preparing those placeholder textures.
