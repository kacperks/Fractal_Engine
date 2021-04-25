# Fractal Game Engine!
<p align="left">
  <img src="res/Icons/Graphics/Logo.png" width="350" height="350">
</p>
Fractal Engine its 3D Game Engine

Not Finished yet

Features:
* Editor
* Loading 3D models
* Fully Featured ECS(Entity-Component-System)
* Scene System
* Prototype of C# Scripting
* Tools like (Move,Rotate,Scale)

Features to do:

* Collision system
* Launcher
* Bulid system
* Lua Scripting
* Cmake Bulid
* Asset Browser

# Screen Shot

<p align="left">
  <img src="res/Icons/ScreenShot.png" width="683" height="371">
</p>

# Docs

* Documentation Coming Soon

# Buliding C# Scripts

You must have Mono to build a C# script.

The command to build:
```sh
csc YourScript.cs -target:library -r:Fractal.dll
```

<a href = "https://www.mono-project.com/docs/getting-started/mono-basics/"> More</a>
# Bulid

To bulid you need :

* GLM
* Glew
* GLFW
* ASSIMP
* TinyXML
* Mono

and Cmake or Visual Studio

To install this libaries on Ubuntu/Debian type
```sh
$ sh lib/lib.sh
```
