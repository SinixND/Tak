#!/usr/bin/env bash
set -e

# -----------------------
# Configuration
# -----------------------
PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
RAYLIB_SRC="/usr/local/lib/raylib/src"  # Raylib source folder
BUILD_ROOT="$PROJECT_ROOT/build/raylib" # temp build folder

PLATFORMS=("desktop" "web")            # Platforms to build
BUILD_MODES=("Debug" "Release")        # Build types

# Destination folder
DEST_ROOT="$PROJECT_ROOT/libs/raylib"

# Detect system platform for desktop builds
SYSTEM_PLATFORM=$(uname | tr '[:upper:]' '[:lower:]')-x64

# -----------------------
# Functions
# -----------------------

build_raylib() {
    local platform=$1
    local build_mode=$2

    echo "=== Building Raylib for $platform / $build_mode ==="

    # Set build folder
    local build_dir="$BUILD_ROOT/${platform}_${build_mode}"
    mkdir -p "$build_dir"
    cd "$build_dir"

    # Configure CMake
    cmake "$RAYLIB_SRC" \
        -DCMAKE_BUILD_TYPE=$build_mode \
        -DBUILD_SHARED_LIBS=OFF \
        $( [ "$platform" == "web" ] && echo "-DCMAKE_TOOLCHAIN_FILE=$EMSCRIPTEN/cmake/Modules/Platform/Emscripten.cmake" )

    # Build
    cmake --build . --config $build_mode

    # Copy static library to project libs folder
    local dest_dir="$DEST_ROOT/$platform/$build_mode"
    mkdir -p "$dest_dir"

    # Locate libraylib.a (CMake puts it in build folder)
    if [ "$platform" == "web" ]; then
        cp "libraylib.a" "$dest_dir/"
    else
        # Desktop builds may have Debug/Release subfolders
        if [ -f "$build_dir/libraylib.a" ]; then
            cp "$build_dir/libraylib.a" "$dest_dir/"
        elif [ -f "$build_dir/$build_mode/libraylib.a" ]; then
            cp "$build_dir/$build_mode/libraylib.a" "$dest_dir/"
        else
            echo "Error: libraylib.a not found in $build_dir"
            exit 1
        fi
    fi

    echo "Copied libraylib.a -> $dest_dir/libraylib.a"
    cd "$PROJECT_ROOT"
}

# -----------------------
# Main Script
# -----------------------

# Optional: EMSDK path for web builds
EMSCRIPTEN=${EMSCRIPTEN:-/path/to/emsdk/upstream/emscripten}

echo "Setting up Raylib..."
echo "Project root: $PROJECT_ROOT"
echo "Raylib source: $RAYLIB_SRC"
echo "Temp build folder: $BUILD_ROOT"

for platform in "${PLATFORMS[@]}"; do
    for mode in "${BUILD_MODES[@]}"; do
        build_raylib $platform $mode
    done
done

echo "Raylib setup complete!"
