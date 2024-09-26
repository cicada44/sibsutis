using System.Security.Cryptography;
using System.Xml.XPath;

static double converter(double value, string unitFrom, string unitTo)
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

static void converterInterface()
{
    Console.Write("From: C, K, F ---> ");
    string unitFrom = Console.ReadLine();
    Console.Write("To: C, K, F ---> ");
    string unitTo = Console.ReadLine();
    Console.Write("Value ---> ");
    double value = double.Parse(Console.ReadLine());
    double result = converter(value, unitFrom, unitTo);
    Console.WriteLine($"{value}{unitFrom} ---> {unitTo} = {result}");

}

static void isPalindrome()
{
    Console.Write("---> ");
    string word = Console.ReadLine();
    bool isPalindromeFlag = true;
    for (int i = 0, j = word.Length - 1; i <= j; i++, j--)
        if (word.ElementAt(i) != word.ElementAt(j))
            isPalindromeFlag = false;
    if (isPalindromeFlag)
        Console.Write("Yes");
    else
        Console.Write("No");
}

static void Fib()
{
    Console.Write("Months: ");
    int months = int.Parse(Console.ReadLine());
    if (months == 1 || months == 0)
        Console.Write("Reuslt: 2");
    int curr = 1, prev = 0;
    for (int i = 2; i <= months; i++)
    {
        int tmp = curr;
        curr += prev;
        prev = tmp;
    }
    Console.Write($"Result: {curr}");
}

static void csvProcessing()
{
    var lines = File.ReadAllLines("data.csv");
    var data = lines.Skip(1).Select(line => double.Parse(line.Split(',')[1])).ToList();
    Console.Write("1. Maximum\n2. Minimum\n3. Average value\n4. Dispersion\n---> ");
    int choice = int.Parse(Console.ReadLine());
    double result = choice switch{
        1 => data.Max(),
        2 => data.Min(),
        3 => data.Average(),
        4 => data.Sum(x => Math.Pow(x - data.Average(), 2)) / (data.Count - 1),
        _ => throw new ArgumentException("Unknown option")
    };
    Console.Write($"Result: {result}");
}

byte choice = 0;
while (choice < 5)
{
    Console.Write("1. Conversion\n2. Palindrome\n3. Rabbits\n4. CSV Parsing\n---> ");
    choice = byte.Parse(Console.ReadLine());
    if (choice == 1)
        converterInterface();
    if (choice == 2)
        isPalindrome();
    if (choice == 3)
        Fib();
    if (choice == 4)
        csvProcessing();
}
