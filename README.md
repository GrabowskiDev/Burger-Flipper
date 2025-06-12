# Burger-Flipper  

Burger-Flipper is a game built in the Godot engine using C++ and GDExtension. All game logic and interactions are implemented in C++ for high performance and flexibility. The project uses the GDExtension system, allowing native C++ libraries to be integrated with Godot without recompiling the engine.

The source code is located in the `src/` directory and is organized into classes responsible for different aspects of the game, such as the player, burger ingredients, and menu logic. Communication between Godot and the C++ code is handled through method and property bindings, making it possible to use C++ classes directly in the Godot editor. The file `src/register_types.cpp` is responsible for making the classes appear as nodes in godot editor, using `GDREGISTER_RUNTIME_CLASS(ClassName);`.

The project uses the `godot-cpp` submodule to generate API bindings and SCons as the build system. After building, the `.so` library is loaded by Godot as a GDExtension. The entire build and integration process is described in the sections below.

## Cloning
To clone the project, you must also clone the godot-cpp submodule
```
git clone --recurse-submodules https://github.com/GrabowskiDev/Burger-Flipper.git
```
or
```
git clone --recurse-submodules git@github.com:GrabowskiDev/Burger-Flipper.git
```

or in case you already cloned the repo
```
git submodule update --init --recursive
```

## Setting up the development
After cloning the project, you need to build the C++ bindings!
First, run a command
```
godot --dump-extension-api
```
That'll create a `extension_api.json` file. After that run
```
cd godot-cpp
scons platform=<platform> custom_api_file=<PATH_TO_EXTENSION_API_FILE>
cd ..
```

## Building the game  
To compile a project into a gdextension and then launch it in godot editor:
```
scons platform=<platform>
```
And to build gdextension for exporting the game into a binary:
```
scons target=template_release platform=<platform>
```
and then export the game from the godot editor.
