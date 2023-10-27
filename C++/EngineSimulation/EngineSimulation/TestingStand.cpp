#include <thread>
#include "TestingStand.h"

void TestingStand::Watch_T()
{
	double eps = 0.001;
	while (_engine->Is_working())
	{
		if (_engine->Get_T() - _engine->Get_T_overheat() >= eps)
		{
			_engine->Stop();
			break;
		}
	}
}

TestingStand::TestingStand()
{

}

TestingStand::TestingStand(Engine& engine)
{
	_engine = &engine;
}

double TestingStand::StartTesting(double T_environment)
{
	std::thread engine_thread(&Engine::Start, _engine, T_environment);
	std::thread watch_thread(&TestingStand::Watch_T, this);
	
	watch_thread.join();
	engine_thread.join();

	return _engine->Get_working_time();

}

TestingStand::~TestingStand()
{

}