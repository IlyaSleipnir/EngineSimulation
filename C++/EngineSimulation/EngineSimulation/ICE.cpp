#include <fstream>
#include <sstream>
#include "ICE.h"

std::vector<double> read_vector_double(std::ifstream& file)
{
	std::string str;
	std::vector<double> res;

	std::getline(file, str);

	std::stringstream ss(str);
	std::string num;

	while (ss >> num)
	{
		res.push_back(std::stod(num));
	}

	return res;
}

ICE::ICE()
{

}

ICE::ICE(std::string path)
{
	std::string line;
	std::ifstream file;

	file.open(path);

	if (file.is_open())
	{
			std::getline(file, line);
			_I = std::stod(line);

			_M = read_vector_double(file);
			_V = read_vector_double(file);

			std::getline(file, line);
			_T_overheat = std::stod(line);

			std::getline(file, line);
			_H_m = std::stod(line);

			std::getline(file, line);
			_H_v = std::stod(line);

			std::getline(file, line);
			_C = std::stod(line);
	}
	else
	{
		throw std::string{ "Error opening file" };
	}
	
	file.close();
}

ICE::ICE(double I,
	std::vector<double> M,
	std::vector<double> V,
	double T_overheat,
	double H_m,
	double H_v,
	double C)
{
	_I = I;
	_M = M;
	_V = V;
	_T_overheat = T_overheat;
	_H_m = H_m;
	_H_v = H_v;
	_C = C;
}

void ICE::Start(double T_environment)
{
	double a;					// ���������
	double V_h;					// �������� �������
	double V_c;					// �������� ����������
	double V;					// ������� �������� ��������
	double M;					// ������� �������� ������
	double precision = 1000;	// ��������, ������� ���������� ������� � 1 �������
	double time_limit = 1000;	// ����������� ������� ������

	_is_working = true;

	_T = T_environment;

	for (int i = 0; i < _M.size() - 1; i++)
	{
		V = _V[i];
		M = _M[i];

		while (V < _V[i + 1])
		{
			a = M / _I;
			V_h = M * _H_m + V * V * _H_v;
			V_c = _C * (_T - T_environment);

			// ���� ������� � ����������
			_T = _T + V_h - V_c;
			// ���������� ��������� �� ������� ���������� �������
			V += a / precision;
			// ���������� ������� �� ���������� ����������� ��������� ������� �� ��������
			M = (V - _V[i]) * (_M[i + 1] - _M[i]) / (_V[i + 1] - _V[i]) + _M[i];

			// ����������� ������� ������� �� ������� ���������� ������� � ������ ��������
			_working_time += 1. / precision;

			// ��������� ������ ��� ������� ����������
			if (!_is_working)
				return;

			if (_working_time >= time_limit)
			{
				_is_working = false;
				return;
			}
		}
	}

}

void ICE::Stop()
{
	// ������ ����������
	_is_working = false;
}

double ICE::Get_T() const
{
	return _T;
}

double ICE::Get_T_overheat() const
{
	return _T_overheat;
}

double ICE::Get_working_time() const
{
	return _working_time;
}

bool ICE::Is_working() const
{
	return _is_working;
}

ICE::~ICE()
{

}