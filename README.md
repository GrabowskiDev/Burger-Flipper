# Burger-Flipper  
An small game made in Godot entirely with C++ using GDExtensions.

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
