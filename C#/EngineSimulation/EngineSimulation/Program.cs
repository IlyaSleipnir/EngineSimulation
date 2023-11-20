using System;
using System.Globalization;

namespace EngineSimulation
{
    internal class Program
    {
        static void Main(string[] args)
        {
            try
            {
                var ice = new ICE("config.txt");
                var stand = new TestingStand(ice);

                Console.WriteLine("Введите температуру окружающей среды в градусах Цельсия:");

                var TEinvironment = double.Parse(Console.ReadLine().Replace(',', '.'), CultureInfo.InvariantCulture);
                var workingTime = stand.StartTesting(TEinvironment);

                Console.WriteLine($"Время работы = {workingTime}");
                Console.WriteLine($"Температура двигателя = {ice.T}");

                if (ice.T < ice.TOverheat)
                    Console.WriteLine("Остановка двигателя по таймауту");
            }
            catch (Exception ex) 
            { 
                Console.WriteLine(ex.Message);
            }
        }
    }
}
