# Meiosis Engine

## Supported Compilers

* Tested on Windows using MinGW GCC, Windows using MSVC
* Extensions should be made using cmake presets, an example for a debug build on Windows using MinGW GCC is:

```json
{
   "name": "dev",
   "binaryDir": "${sourceDir}/build/dev",
   "inherits": [
         "dev-mode",
         "conan-gcc-win",
         "ci-gcc-windows",
         "cppcheck"
   ],
   "cacheVariables": {
         "CMAKE_BUILD_TYPE": "Debug",
         "CMAKE_RUNTIME_OUTPUT_DIRECTORY": "${sourceDir}/build/Debug-bin"
   }
}
```

## Required Tools

1. cmake
2. Conan package manager
3. cpp_check (optional)
4. clang-tidy (optional)

## How to use

Meiosis is built as a static library and linked against the game application. The executable, example is Sandbox, needs to include a function CreateApplication() which returns a pointer to a derived Application class where the game operation is defined.

The conan package manager is used to integrate third party libraries. Depending on your system, use: (see [scripts](scripts\conan_install.py) as an example for automation)

`conan install .. -if ${OUTPUT_FOLDER} --profile ${CONAN_PROFILE} -pr:b ${CONAN_PROFILE} --build missing`

 `OUTPUT_FOLDER` is dependent on your system and cmake preset variable `CMAKE_TOOLCHAIN_FILE` (see [CMakePresets.json](CmakePresets.json)). for an example). Conan package manager has the optional use of profiles to make working with multiple compilers easier, please see their documentation for more information.

## Warnings

* Does not support pre-compiled headers when using clang-tidy

## Items

### Completed

1. Core
   1. Entrypoint
   2. Logging
   3. Rendering
      1. Window
      2. Context
      3. Shader
      4. Vertex Buffer
      5. Vertex Array
      6. Index buffer
   4. Event system
      1. Binding
      2. Event handler
   5. imgui
   6. Application
   7. Textures
   8. Timestep

### TODO

1. Assert
2. Material
3. Renderer
   1. Batch Rendering
   2. Primitive Objects
      1. Triangle
      2. Rectangle
      3. Cube
   3. Frame Buffer
4. ECS
   1. IP
   2. Allow MeshComponent to take in Materials
   3. Allow MeshComponent to take in Shader source strings rather than filenames
5. Scene
   1. IP
   2. Set up camera system
6. Physics
