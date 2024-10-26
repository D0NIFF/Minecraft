# Minecraft

## Dependencies
- OpenGL
- GLFW
- GLEW
- ZLIB

## Installation
> [!NOTE]
> Require **[CMake](https://cmake.org/), [vcpkg](https://vcpkg.io/en/)**

### Windows
1. Download and install [CMake](https://cmake.org/download/)
2. Install [vcpkg](https://learn.microsoft.com/en-us/vcpkg/get_started/overview)
3. Change path in `VCPKG_DIR` (CMakeLists.txt) to your vcpkg installation dir
4. Install project dependencies
    - `vckpg install glfw3` <br>
    - `vckpg install glew` <br>
    - `vckpg install glm` <br>
    - `vckpg install zlib` <br>
