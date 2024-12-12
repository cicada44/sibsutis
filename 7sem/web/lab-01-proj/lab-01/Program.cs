using System.Security.Cryptography;
using System.Xml.XPath;

namespace UtilityApp
{
    class Program
    {

        static string ReadUnit()
        {
            string unitFrom;
            while (true)
            {
                try
                {
                    unitFrom = Console.ReadLine();
                    return unitFrom;
                }
                catch (System.FormatException)
                {
                    Console.WriteLine("Wrong Unit!");
                }
            }
        }

        static double ReadDouble()
        {
            double value;
            while (true)
            {
                try
                {
                    value = double.Parse(Console.ReadLine());
                    return value;
                }
                catch (System.FormatException)
                {
                    Console.WriteLine("Wrong value!");
                }
            }
        }

        static double Convert(double value, string unitFrom, string unitTo)
        {
            double resultCelsius = unitFrom switch {
                "C" => value,
                "K" => value - 273.15,
                "F" => (value - 32) * 5 / 9,
                _   => throw new ArgumentException("Unknown unit")
            };

            return unitTo switch {
                "C" => resultCelsius,
                "K" => resultCelsius + 273.15,
                "F" => resultCelsius * 9 / 5 + 32,
                _   => throw new ArgumentException("Unknown unit")
            };
        }

        static string ReadString()
        {
            string value;
            while (true)
            {
                try
                {
                    value = Console.ReadLine();
                    value = value.Replace(",", "");
                    value = value.Replace(" ", "");
                    return value;
                }
                catch (System.FormatException)
                {
                    Console.WriteLine("Wrong value!");
                }
            }
        }

        static void ConverterInterface()
        {
            Console.Write("From: C, K, F ---> ");
            string unitFrom = ReadUnit();
            Console.Write("To: C, K, F ---> ");
            string unitTo = ReadUnit();
            Console.Write("Value ---> ");
            double value = ReadDouble();
            double result = Convert(value, unitFrom, unitTo);
            Console.WriteLine($"{value}{unitFrom} ---> {unitTo} = {result}");
        }

        static void IsPalindrome()
        {
            Console.Write("---> ");
            string word = ReadString().ToLower();
            bool isPalindromeFlag = true;
            for (int i = 0, j = word.Length - 1; i <= j; i++, j--)
                if (word.ElementAt(i) != word.ElementAt(j))
                    isPalindromeFlag = false;
            if (isPalindromeFlag)
                Console.Write("Yes\n");
            else
                Console.Write("No\n");
        }

        static void Fib()
        {
            Console.Write("Months: ");
            int months = int.Parse(Console.ReadLine());
            if (months == 1 || months == 0)
                Console.WriteLine("Result: 2");
            int curr = 1, prev = 0;
            for (int i = 2; i <= months; i++)
            {
                int tmp = curr;
                curr += prev;
                prev = tmp;
            }
            Console.WriteLine($"Result: {curr}");
        }

        static void CsvProcessing()
        {
            var lines = File.ReadAllLines("data.csv");
            var data = lines.Skip(1).Select(line => double.Parse(line.Split(',')[1])).ToList();
            Console.Write("1. Maximum\n2. Minimum\n3. Average value\n4. Dispersion\n---> ");
            int choice = int.Parse(Console.ReadLine());
            double result = choice switch {
                1 => data.Max(),
                2 => data.Min(),
                3 => data.Average(),
                4 => data.Sum(x => Math.Pow(x - data.Average(), 2)) / (data.Count - 1),
                _ => throw new ArgumentException("Unknown option")
            };
            Console.WriteLine($"Result: {result}");
        }

        static void Main(string[] args)
        {
            byte choice = 0;
            while (choice < 5)
            {
                Console.Write("1. Conversion\n2. Palindrome\n3. Rabbits\n4. CSV Parsing\n---> ");
                try
                {
                    choice = byte.Parse(Console.ReadLine());
                }
                catch (System.FormatException)
                {
                    Console.WriteLine("Try again!");
                    continue;
                }
                if (choice == 1)
                    ConverterInterface();
                if (choice == 2)
                    IsPalindrome();
                if (choice == 3)
                    Fib();
                if (choice == 4)
                    CsvProcessing();
            }

        }
    }
}
