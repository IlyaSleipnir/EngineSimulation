#include <thread>
#include "TestingStand.h"

void watch_T(Engine* engine)
{
	double eps = 0.001;
	while (engine->Is_working())
	{
		if (engine->Get_T() - engine->Get_T_overheat() >= eps)
		{
			engine->Stop();
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
	std::thread watch_thread(watch_T, _engine);
	//engine_thread.detach();

	//_engine->Start(T_environment);
	
	watch_thread.join();
	//std::cout << watch_thread.get_id() << " DONE" << std::endl;
	engine_thread.join();

	return _engine->Get_working_time();

}

TestingStand::~TestingStand()
{

}