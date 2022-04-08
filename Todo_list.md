# Meiosis Engine

## Supported Compiler

* Tested on Windows using MinGW GCC

## Required Tools

1. cmake
2. Conan package manager
3. cpp_check (optional)
4. clang-tidy (optional)

## How to use

Meiosis is built as a static library and linked against the game application. The executable, example is Sandbox, needs to include a function CreateApplication() which returns a pointer to a derived Application class where the game operation is defined.

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

### TODO

1. Assert
2. Texture
3. Material
4. Timestep
5. Renderer
   1. Batch Rendering
   2. Primitive Objects
      1. Triangle
      2. Rectangle
      3. Cube
   3. Frame Buffer
   4. Shader optimization
6. ECS
7. Scene
8. Physics
