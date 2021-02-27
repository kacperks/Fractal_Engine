<p align="left">
  <img src="res/Graphics/Logo.png" width="350" height="350">
</p>

Fractal Engine its 3D Game Engine with Editor

Not Finished

Features to do:

* Editor
* Launcher
* C# and Lua Support
* loading 3D models

Done :
* Component System
* Entities System

# exemple

```cpp
#include "fractal.hpp"

struct TestComp1 : public ECS::BaseComponent {
	int A = 5;
};

struct TestComp2 : public ECS::BaseComponent {
	int A = 5;
};

struct TestSystem1 : public ECS::BaseSystem {
	TestSystem3() {
		AddComponentSignature<Transform>();
		AddComponentSignature<TestComp2>();
		AddComponentSignature<TestComp1>();
	}
};

int main(int argc, char** argv) {

	ECS::EntityManager mgr;
	mgr.RegisterSystem<TestSystem1>();

	auto entity1 = mgr.AddNewEntity();
	ECS::Entity ent(entity1, &mgr);

	ent.AddComponent<Transform>();
	ent.Transform.position.x = 1;
	mgr.Update();

	fr::Core.Initialize();
	fr::Timer.Initialize();
	fr::Events.Initialiaze();

	while (fr::Core.Run()) {
		fr::Timer.Tick();
		fr::Events.Poll();
		fr::Core.Update();
	}

	return EXIT_SUCCESS;
}
```
# Bulid

To bulid you need :

* GLM
* SFML
* Glew
* GLFW
* Cmake or visual studio 2019

To install this libaries on linux type

        sh lib.sh
