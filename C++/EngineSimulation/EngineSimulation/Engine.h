#pragma once
class Engine
{
public:
	virtual void Start(const double T_environment) = 0;
	virtual void Stop() = 0;
	virtual double Get_T() const = 0;
	virtual double Get_T_overheat() const = 0;
	virtual double Get_working_time() const = 0;
	virtual bool Is_working() const = 0;

protected:
	double _T;
	double _working_time;
	double _T_overheat;
	bool _is_working = false;
};