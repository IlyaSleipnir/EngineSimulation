#include <iostream>
#include "Engine.h"
#include "ICE.h"
#include "TestingStand.h"

int main()
{
	double I = 10;
	std::vector<double> M{ 20, 75, 100, 105, 75, 0 };
	std::vector<double> V{ 0, 75, 150, 200, 250, 300 };
	double T_overheat = 110;
	double H_m = 0.01;
	double H_v = 0.0001;
	double C = 0.1;

	ICE ice(I, M, V, T_overheat, H_m, H_v, C);

	//ICE ice("config.txt");
	TestingStand stand(ice);

	std::cout << "Enter the environment temperature value: " << std::endl;

	double T_environment;
	std::cin >> T_environment;

	std::cout << "========\tENGINE START\t========" << std::endl << std::endl;

	double working_time = stand.StartTesting(T_environment);

	std::cout << "========\tENGINE STOP\t========" << std::endl << std::endl;

	std::cout << "Working time = " << working_time << std::endl;
	std::cout << "Engine's T = " << ice.Get_T() << std::endl;
	
	if (ice.Get_T() < ice.Get_T_overheat())
		std::cout << std::endl << "Stopping on timeout" << std::endl;
}
