# Fractal Game Engine!
<p align="left">
  <img src="bin/Resource/Icons/Logo.png" width="350" height="350">
</p>
Fractal Engine its 3D Game Engine

Not Finished yet

Features:
* ImGui Editor
* Loading 3D models with ASSIMP
* Fully Featured ECS(Entity-Component-System)
* Scene System
* Prototype of C# Scripting
* Tools like (Move,Rotate,Scale)

Features to do:

* Collision system
* Loading models using GUI
* Launcher
* Bulid system
* Custom Scripting Language
* 2D Version

[![Discord](https://img.shields.io/badge/Fractal%20Server--blue.svg?style=social&logo=Discord)](https://discord.gg/3gkZWNXhK3)

# Screen Shot

<p align="left">
  <img src="bin/Resource/Icons/ScreenShot.png" width="683" height="371">
</p>

# Docs

* Documentation Coming Soon

# Scripting

### C#

You must have Mono to build a C# script.

The command to build:
```sh
csc YourScript.cs -target:library -r:Fractal.dll
```

<a href = "https://www.mono-project.com/docs/getting-started/mono-basics/"> More</a>

### FR Script

FR Script Comming Soon

# Bulid

### Dependencies

To bulid you need :

* GLM https://github.com/g-truc/glm
* Glew https://github.com/nigels-com/glew
* GLFW https://github.com/glfw/glfw
* ASSIMP https://github.com/assimp/assimp
* TinyXML https://github.com/leethomason/tinyxml2
* Mono https://github.com/mono/mono
** (Optional , if your compiler cannot use mono or if you are using linux Delete line 25 from src/Core.h File and 42,43 line from premake5.lua file)

and premake

To install this libaries on Ubuntu/Debian type
```sh
$ sh lib/lib.sh
```

# Similar projects

## Fractal Engine was inspired by these projects

### Rootex
<a href = "https://github.com/sdslabs/Rootex"> Github page </a>

Rootex is an advanced C++ 3D game engine powering an in-production game yet to be announced. The game will finally ship on Windows and use DirectX 11.

### NovelRT

<a href = "https://github.com/novelrt/NovelRT"> Github page </a>

NovelRT is a cross-platform, flexible Visual Novel and 2D game engine

# Contributors    

<a href = "https://github.com/kacperks"> kacperks </a>
<br>
<a href = "https://github.com/lubek-dc"> lubek-dc </a>
<br>
<a href = "https://github.com/BoomerDev"> BoomerDev </a>

The people listed above have landed more than 2 commits in the project
