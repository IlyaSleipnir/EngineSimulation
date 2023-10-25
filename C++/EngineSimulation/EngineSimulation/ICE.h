#include <string>
#include <vector>
#include "Engine.h"
#pragma once
class ICE : public Engine
{
public:
	ICE();
	ICE(std::string path);
	ICE(double I,
		std::vector<double> M,
		std::vector<double> V,
		double T_overheat,
		double H_m,
		double H_v,
		double C);
	~ICE();

	void Start(double T_environment) override;
	void Stop() override;

	double Get_T() const override;
	double Get_T_overheat() const override;
	double Get_working_time() const override;
	bool Is_working() const override;

private:
	double _I;
	std::vector<double> _M;
	std::vector<double> _V;
	double _H_m;
	double _H_v;
	double _C;
};