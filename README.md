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
* C# Scripting
* Tools like (Move,Rotate,Scale)

Features to do:

* Launcher
* Bulid system
* 2D version
* Lua Scripting
* Cmake Bulid

# Exemples
Exemple C# script

```cpp
using Fractal;
using System;

public class CamSpinSpin : FractalScript
{
    public float Speed;
    
    public void Start()
    {
        Speed = 10;
    }

    public void Update(float deltatime, ref Transform transform)
    {
        transform.Rotation.Y += Speed * deltatime;
        transform.Rotation.X += Speed * deltatime;
    }
}
```

Exemple C++ Component

```cpp
#pragma once

#include "ECS/Base/BaseComponent.h"

struct Player : public ECS::BaseComponent
{
    std::string Name;
    float Level;
};
```
* To create your own component you need the source code of the Fractal engine!

# Buliding C# Scripts


You must have Mono to build a C# script.

The command to build:
```sh
csc YourScript.cs -target:library -r:Fractal.dll
```
# Bulid

To bulid you need :

* GLM
* SFML
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
