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
* Launcher
* Bulid system
* Custom Scripting Language

# Screen Shot

<p align="left">
  <img src="bin/Resource/Icons/ScreenShot.png" width="683" height="371">
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
* Mono (Optional , if your compiler cannot use mono or if you are using linux Delete line 25 from src/Core.h File)

and premake

To install this libaries on Ubuntu/Debian type
```sh
$ sh lib/lib.sh
```

# Contributors    

<a href = "https://github.com/kacperks"> kacperks </a>
<br>
<a href = "https://github.com/lubek-dc"> lubek-dc </a>
<br>
<a href = "https://github.com/BoomerDev"> BoomerDev </a>

The people listed above have landed more than 2 commits in the project
