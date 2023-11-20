namespace EngineSimulation
{
    abstract internal class Engine
    {
        protected double _T;
        protected double _workingTime;
        protected double _TOverheat;
        protected bool _isWorking = false;

        public abstract double T { get; }
        public abstract double TOverheat { get; }
        public abstract double WorkingTime { get; }
        public abstract bool IsWorking { get; }

        public abstract void Start(object tEnvironment);
        public abstract void Stop();
    }
}
