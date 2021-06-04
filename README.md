<p align="center">
  <img src="bin/Resource/Icons/Logo.png" width="350" height="350">
</p>

<p align="center">
Fractal Engine its 3D and 2D Game Engine
</p>

<p align="center">
<img src="https://img.shields.io/github/last-commit/kacperks/Fractal_Engine?label=Last%20Commit"/>
<img src="https://img.shields.io/github/license/kacperks/Fractal_Engine?label=License" />
<img src="https://img.shields.io/github/downloads/kacperks/Fractal_Engine/total?label=Downloads" />
<img src="https://img.shields.io/github/languages/code-size/kacperks/Fractal_Engine?label=Code%20Size" />
<img src="https://img.shields.io/github/stars/kacperks/Fractal_Engine?label=Stars&logo=github" />

Features:
* ImGui Editor
* Loading 3D models with ASSIMP
* Loading 2D textures with stbimage
* Fully Featured ECS(Entity-Component-System)
* Scene System (XML)
* Prototype of C# Scripting
* Gizmos

Features to do:

* Collision system
* Physics Engine
* Custom Scripting Language (FR Script)
* Python or Lua Scripting
  
# Screen Shot

<p align="left">
  <img src="ScreenShot.png" width="683" height="371">
</p>

# Building

### Dependencies

* GLM https://github.com/g-truc/glm
* GLEW https://github.com/nigels-com/glew
* GLFW https://github.com/glfw/glfw
* ASSIMP https://github.com/assimp/assimp
* TinyXML https://github.com/leethomason/tinyxml2
* Mono https://github.com/mono/mono (Optional)
* ImGui https://github.com/ocornut/imgui
* stb https://github.com/nothings/stb
* ImGuizmo https://github.com/CedricGuillemet/ImGuizmo
* Scons https://github.com/SCons/scons

## Setup

First you need to Clone Repo

```sh
git clone https://github.com/kacperks/Fractal_Engine.git
```

#### Installing these libraries on Linux

* Debian/Ubuntu
```sh
sudo apt install -y libglm-dev libglew-dev libglfw3-dev libassimp-dev assimp-utils libxmu-dev libxi-dev libtinyxml-dev
```
* Fedora
```sh
sudo dnf install glew-devel glm-devel assimp-devel glfw-devel tinyxml2-devel
```

## Building

First you need to install scons:

```sh
pip install scons
```

Then just type:

```sh
scons
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

* <a href = "https://github.com/kacperks"> kacperks </a>
* <a href = "https://github.com/lubek-dc"> lubek-dc </a>
* <a href = "https://github.com/BoomerDev"> BoomerDev </a>

The people listed above have landed more than 2 commits in the project
