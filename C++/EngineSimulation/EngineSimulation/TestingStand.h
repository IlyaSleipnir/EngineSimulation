#pragma once
#include "Engine.h"
class TestingStand
{
public:
	TestingStand();
	TestingStand(Engine& engine);
	double StartTesting(double T_environment);
	~TestingStand();

private:
	Engine* _engine;
};
