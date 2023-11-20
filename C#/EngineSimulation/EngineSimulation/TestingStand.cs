using System.Threading;

namespace EngineSimulation
{
    internal class TestingStand
    {
        Engine _engine;
        double _eps = 0.001;

        public double Eps { get { return _eps; } set { _eps = value; } }
        void WatchT()
        {
            while (true)
            {
                if ( _engine.T - _engine.TOverheat >= _eps)
                {
                    _engine.Stop();
                    return;
                }
                if (_engine.WorkingTime > 0 && !_engine.IsWorking)
                    return;
            }
        }

        public TestingStand(Engine engine)
        {
            _engine = engine;
        }

        public double StartTesting(double TEnviroment)
        {
            var engineThread = new Thread(_engine.Start);
            var watchThread = new Thread(WatchT);
            engineThread.Start(TEnviroment);
            watchThread.Start();
            watchThread.Join();
            engineThread.Join();

            return _engine.WorkingTime;
        }

    }
}
