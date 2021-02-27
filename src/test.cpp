#include "fractal.hpp"

struct TestComp1 : public ECS::BaseComponent {
	int A = 5;
};

struct TestComp2 : public ECS::BaseComponent {
	int A = 5;
};

struct TestSystem1 : public ECS::BaseSystem {
	TestSystem1() {
		AddComponentSignature<TestComp1>();
	}
};

struct TestSystem2 : public ECS::BaseSystem {
	TestSystem2() {
		AddComponentSignature<TestComp2>();
	}
};

struct TestSystem3 : public ECS::BaseSystem {
	TestSystem3() {
		AddComponentSignature<TestComp1>();
		AddComponentSignature<TestComp2>();
		AddComponentSignature<tr::Transform>();
	}
};


int main(int argc, char** argv) {

	ECS::EntityManager mgr;


	mgr.RegisterSystem<TestSystem1>();
	mgr.RegisterSystem<TestSystem2>();
	mgr.RegisterSystem<TestSystem3>();

	auto entity1 = mgr.AddNewEntity();
	ECS::Entity ent(entity1, &mgr);

	ent.AddComponent<TestComp1>();
	ent.AddComponent<tr::Transform>();
	ent.Transform.position.x = 0.0f;

	auto entity2 = mgr.AddNewEntity();
	mgr.AddComponent<TestComp2>(entity2);

	auto entity3 = mgr.AddNewEntity();
	mgr.AddComponent<TestComp1>(entity3);
	mgr.AddComponent<TestComp2>(entity3);

	mgr.Update();

	fr::Core.Initialize();
	fr::Timer.Initialize();
	fr::Event.Initialiaze();

	while (fr::Core.Run()) {
		fr::Timer.Tick();
		fr::Event.Poll();
		fr::Core.Update();
	}

	return EXIT_SUCCESS;
}
