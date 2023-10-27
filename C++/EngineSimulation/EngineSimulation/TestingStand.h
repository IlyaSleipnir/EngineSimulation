#pragma once
#include "Engine.h"
class TestingStand
{
public:
	TestingStand();
	TestingStand(Engine& engine);
	double StartTesting(double T_environment);
	void Watch_T();
	~TestingStand();

private:
	Engine* _engine;
};
