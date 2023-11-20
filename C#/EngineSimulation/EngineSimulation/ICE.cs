using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;

namespace EngineSimulation
{
    internal class ICE : Engine
    {
        double _I;
        double _Hm;
        double _Hv;
        double _C;
        List<double> _M;
        List<double> _V;

        public ICE(string path)
        {
            string line;

            using (var file = new StreamReader(path))
            {
                line = file.ReadLine().Replace(',', '.');
                _I = double.Parse(line, CultureInfo.InvariantCulture);

                line = file.ReadLine().Replace(',', '.');
                _M = line.Split().Select(x => double.Parse(x, CultureInfo.InvariantCulture)).ToList();

                line = file.ReadLine().Replace(',', '.');
                _V = line.Split().Select(x => double.Parse(x, CultureInfo.InvariantCulture)).ToList();

                line = file.ReadLine().Replace(',', '.');
                _TOverheat = double.Parse(line, CultureInfo.InvariantCulture);

                line = file.ReadLine().Replace(',', '.');
                _Hm = double.Parse(line, CultureInfo.InvariantCulture);

                line = file.ReadLine().Replace(',', '.');
                _Hv = double.Parse(line, CultureInfo.InvariantCulture);

                line = file.ReadLine().Replace(',', '.');
                _C = double.Parse(line, CultureInfo.InvariantCulture);
            }

        }

        public ICE(double i, double hm, double hv, double c, double tOverheat, List<double> m, List<double> v)
        {
            _I = i;
            _Hm = hm;
            _Hv = hv;
            _C = c;
            _M = m;
            _V = v;
            _TOverheat = tOverheat;
        }

        public override double T { get { return _T; } }
        public override double TOverheat { get { return _TOverheat; } }
        public override double WorkingTime { get { return _workingTime; } }
        public override bool IsWorking { get { return _isWorking; } }

        public override void Start(object tEnvironment)
        {
            if (!(tEnvironment is double))
                throw new Exception("Неверный формат папрматра в методе Start. Ожидается double");

            double TEnvironment = (double)tEnvironment;
            double a;
            double Vh;
            double Vc;
            double V;
            double M;
            const double precision = 1000;
            const double timeLimit = 1000;

            _isWorking = true;
            _T = TEnvironment;

            for (int i = 0; i < _M.Count; i++)
            {
                V = _V[i];
                M = _M[i];

                while (V < _V[i + 1])
                {
                    a = M / _I;
                    Vh = M * _Hm + V * V * _Hv;
                    Vc = _C * (_T - TEnvironment);

                    _T = _T + Vh - Vc;
                    V += a / precision;
                    M = (V - _V[i]) * (_M[i + 1] - _M[i]) / (_V[i + 1] - _V[i]) + _M[i];

                    _workingTime += 1.0 / precision;

                    if (!_isWorking)
                        return;

                    if (_workingTime >= timeLimit)
                    {
                        _isWorking = false;
                        return;
                    }
                }
            }
        }
        public override void Stop()
        {
            _isWorking = false;
        }
    }
}
