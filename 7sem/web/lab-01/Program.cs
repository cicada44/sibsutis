using System;
using System.Linq;
using System.IO;

namespace UtilityApp
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length == 0)
            {
                Console.WriteLine("Введите команду: tempconvert, palindrome, rabbits, или csv.");
                return;
            }

            switch (args[0].ToLower())
            {
                case "tempconvert":
                    RunTemperatureConverter();
                    break;

                case "palindrome":
                    RunPalindromeChecker();
                    break;

                case "rabbits":
                    RunRabbitBreeding();
                    break;

                case "csv":
                    RunCSVAnalyzer();
                    break;

                default:
                    Console.WriteLine("Неизвестная команда. Доступные команды: tempconvert, palindrome, rabbits, csv.");
                    break;
            }
        }

        static void RunTemperatureConverter()
        {
            Console.WriteLine("Введите значение градусов:");
            double value = double.Parse(Console.ReadLine());

            Console.WriteLine("Введите исходную шкалу (C, K, F):");
            string fromScale = Console.ReadLine().ToUpper();

            Console.WriteLine("Введите целевую шкалу (C, K, F):");
            string toScale = Console.ReadLine().ToUpper();

            double result = ConvertTemperature(value, fromScale, toScale);
            Console.WriteLine($"Результат: {result}");
        }

        static double ConvertTemperature(double value, string fromScale, string toScale)
        {
            double celsius = fromScale switch
            {
                "C" => value,
                "K" => value - 273.15,
                "F" => (value - 32) * 5 / 9,
                _ => throw new ArgumentException("Неизвестная шкала")
            };

            return toScale switch
            {
                "C" => celsius,
                "K" => celsius + 273.15,
                "F" => celsius * 9 / 5 + 32,
                _ => throw new ArgumentException("Неизвестная шкала")
            };
        }

        static void RunPalindromeChecker()
        {
            Console.WriteLine("Введите слово:");
            string word = Console.ReadLine();

            if (IsPalindrome(word))
                Console.WriteLine("Слово является палиндромом");
            else
                Console.WriteLine("Слово не является палиндромом");
        }

        static bool IsPalindrome(string word)
        {
            word = word.ToLower();
            int i = 0, j = word.Length - 1;
            while (i < j)
            {
                if (word[i] != word[j])
                    return false;
                i++;
                j--;
            }
            return true;
        }

        static void RunRabbitBreeding()
        {
            Console.WriteLine("Введите количество месяцев:");
            int months = int.Parse(Console.ReadLine());

            int result = CalculateRabbits(months);
            Console.WriteLine($"Количество пар кроликов: {result}");
        }

        static int CalculateRabbits(int months)
        {
            if (months == 0) return 0;
            if (months == 1) return 1;

            int a = 0, b = 1, temp;
            for (int i = 2; i <= months; i++)
            {
                temp = a + b;
                a = b;
                b = temp;
            }
            return b;
        }

        static void RunCSVAnalyzer()
        {
            Console.WriteLine("Введите путь к CSV файлу:");
            string filePath = Console.ReadLine();

            var lines = File.ReadAllLines(filePath);
            var data = lines.Skip(1).Select(line => double.Parse(line.Split(',')[1])).ToList();

            Console.WriteLine("Выберите операцию (max, min, avg, variance):");
            string operation = Console.ReadLine().ToLower();

            double result = operation switch
            {
                "max" => data.Max(),
                "min" => data.Min(),
                "avg" => data.Average(),
                "variance" => Variance(data),
                _ => throw new ArgumentException("Неизвестная операция")
            };

            Console.WriteLine($"Результат: {result}");
        }

        static double Variance(System.Collections.Generic.List<double> values)
        {
            double avg = values.Average();
            return values.Sum(x => Math.Pow(x - avg, 2)) / (values.Count - 1);
        }
    }
}
