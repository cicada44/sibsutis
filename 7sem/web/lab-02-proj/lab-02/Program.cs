using System;
using System.IO;
using System.Xml.Serialization;
using System.Xml.Linq;

public class Program
{
    public class Effect
    {
        public string Target { get; set; }
        public int Value { get; set; }

        public Effect(string target, int value)
        {
            Target = target;
            Value = value;
        }
    }


    public static Dictionary<string, List<Effect>> actionEffects = new Dictionary<string, List<Effect>>();

    private static void LoadStats()
    {
        string xmlFileName = "stats.xml";
        XDocument xdoc = XDocument.Load(xmlFileName);

        var actions = xdoc.Descendants("Action");
        foreach (var action in actions)
        {
            string actionName = action.Attribute("name").Value;
            var effects = action.Element("Effects").Elements("Effect");
            List<Effect> effectList = new List<Effect>();

            foreach (var effect in effects)
            {
                string target = effect.Attribute("target").Value;
                int value = int.Parse(effect.Attribute("value").Value);
                effectList.Add(new Effect(target, value));
            }

            actionEffects[actionName] = effectList;
        }
    }

    public static void Main(string[] args)
    {
        LoadStats();
        Game game = new Game();
        game.Run();
    }
}


struct GoToWorkStats { static public int Health, Mana, Cheerfulness, Fatigue, Money; }
struct ContemplateNatureStats { static public int Health, Mana, Cheerfulness, Fatigue, Money; }
struct DrinkWineAndWatchSeriesStats { static public int Health, Mana, Cheerfulness, Fatigue, Money; }
struct GoToBarStats { static public int Health, Mana, Cheerfulness, Fatigue, Money; }
struct DrinkWithMarginalFiguresStats { static public int Health, Mana, Cheerfulness, Fatigue, Money; }
struct SingInMetroStats { static public int Health, Mana, Cheerfulness, Fatigue, Money; }
struct SleepStats { static public int Health, Mana, Cheerfulness, Fatigue, Money; }

public class Valera
{
    public int Health { get; set; }
    public int Mana { get; set; }
    public int Cheerfulness { get; set; }
    public int Fatigue { get; set; }
    public decimal Money { get; set; }

    private void UpgradeHealth(int value)
    {
        if (value != 100)
            Health += value;
    }

    private void UpgradeMana(int value)
    {
        if (value == 100)
            Mana += value;
    }

    private void DowngradeMana(int value)
    {
        if (value == 100)
            Mana -= value;
    }

    private void UpgradeCh(int value)
    {
        if (value == 100)
            Cheerfulness += value;
    }

    private void UpgradeFatigue(int value)
    {
        if (value == 100)
            Fatigue += value;
    }

    private void DowngradeFatigue(int value)
    {
        if (value == 100)
            Fatigue -= value;
    }

    private void DowngradeCh(int value)
    {
        if (value == 100)
            Cheerfulness -= value;
    }

    private void Die()
    {
        Console.WriteLine("R.I.P Valera :-(");
        Environment.Exit(0);
    }

    public Valera()
    {
        Health = 100;
        Mana = 50;
        Cheerfulness = 0;
        Fatigue = 0;
        Money = 0;
    }

    public void GoToWork()
    {
        if (Mana < 50 && Fatigue < 10)
        {
            DowngradeCh(5);
            DowngradeMana(30);
            Money += 100;
            UpgradeFatigue(70);
        }
    }

    public void ContemplateNature()
    {
        UpgradeCh(1);
        DowngradeMana(10);
        UpgradeFatigue(10);
    }

    public void DrinkWineAndWatchSeries()
    {
        DowngradeCh(1);
        UpgradeMana(30);
        UpgradeFatigue(10);
        Health -= 5;
        if (Health <= 0)
            Die();
        Money -= 20;
    }

    public void GoToBar()
    {
        UpgradeCh(1);
        UpgradeMana(60);
        UpgradeFatigue(40);
        Health -= 10;
        if (Health <= 0)
            Die();
        Money -= 100;
    }

    public void DrinkWithMarginalFigures()
    {
        UpgradeCh(5);
        Health -= 80;
        if (Health <= 0)
            Die();
        UpgradeMana(90);
        UpgradeFatigue(80);
        Money -= 150;
    }

    public void SingInMetro()
    {
        UpgradeCh(1);
        UpgradeMana(10);
        UpgradeFatigue(20);
        Money += 10;
        if (Mana > 40 && Mana < 70)
            Money += 50;
    }

    public void Sleep()
    {
        if (Mana < 30)
        {
            UpgradeHealth(90);
        }
        else if (Mana > 70)
        {
            UpgradeCh(3);
        }

        Health -= 50;
        if (Health <= 0)
            Die();
        DowngradeFatigue(70);
    }

    public void ApplyEffects(List<Program.Effect> effects)
    {
        foreach (var effect in effects)
        {
            switch (effect.Target)
            {
                case "Health":
                    Health += effect.Value;
                    break;
                case "Mana":
                    Mana += effect.Value;
                    break;
                case "Cheerfulness":
                    Cheerfulness += effect.Value;
                    break;
                case "Fatigue":
                    Fatigue += effect.Value;
                    break;
                case "Money":
                    Money += effect.Value;
                    break;
            }
    
            // Проверка на превышение или снижение до нуля здоровья
            if (Health <= 0)
            {
                Die();
            }
    
            // Проверка на границы допустимых значений (например, чтобы усталость не стала меньше 0 или больше 100)
            Fatigue = Math.Clamp(Fatigue, 0, 100);
            Mana = Math.Clamp(Mana, 0, 100);
            Cheerfulness = Math.Clamp(Cheerfulness, -10, 10);
            Health = Math.Clamp(Health, 0, 100);
        }
    }


    public void Save(string filePath)
    {
        try
        {
            XmlSerializer serializer = new XmlSerializer(typeof(Valera));
            using (TextWriter writer = new StreamWriter(filePath))
            {
                serializer.Serialize(writer, this);
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при сохранении в файл: {ex.Message}");
        }
    }

    // Статический метод для загрузки объекта из XML файла
    public static Valera Load(string filePath)
    {
        if (File.Exists(filePath))
        {
            try
            {
                XmlSerializer serializer = new XmlSerializer(typeof(Valera));
                using (TextReader reader = new StreamReader(filePath))
                {
                    return (Valera)serializer.Deserialize(reader);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Ошибка при загрузке из файла: {ex.Message}");
            }
        }
        return new Valera(); // Возвращаем новый объект, если файл не найден или произошла ошибка
    }
}

public class Game
{
    private Valera valera;

    public Game()
    {
        valera = Valera.Load("valera.xml");
    }

    public void Run()
    {
        while (true)
        {
            DisplayStats();
            ShowMenu();
            var choice = Console.ReadLine();
            HandleChoice(choice);
        }
    }

    private void DisplayStats()
    {
        Console.WriteLine($"Здоровье: {valera.Health}");
        Console.WriteLine($"Алкоголь: {valera.Mana}");
        Console.WriteLine($"Жизнерадостность: {valera.Cheerfulness}");
        Console.WriteLine($"Усталость: {valera.Fatigue}");
        Console.WriteLine($"Деньги: {valera.Money}");
    }

    private void ShowMenu()
    {
        Console.WriteLine("Выберите действие:");
        Console.WriteLine("1 - Пойти на работу");
        Console.WriteLine("2 - Созерцать природу");
        Console.WriteLine("3 - Пить вино и смотреть сериал");
        Console.WriteLine("4 - Сходить в бар");
        Console.WriteLine("5 - Выпить с маргинальными личностями");
        Console.WriteLine("6 - Петь в метро");
        Console.WriteLine("7 - Спать");
        Console.WriteLine("8 - Почитать книгу");
        Console.WriteLine("0 - Сохранить и выйти");
    }

    private void HandleChoice(string choice)
    {
        string? actionName = choice switch
        {
            "1" => "Пойти на работу",
            "2" => "Созерцать природу",
            "3" => "Пить вино и смотреть сериал",
            "4" => "Сходить в бар",
            "5" => "Выпить с маргинальными личностями",
            "6" => "Петь в метро",
            "7" => "Спать",
            "8" => "Почитать книгу",
            "0" => "Сохранить и выйти",
            _ => null
        };

        if (actionName == "Сохранить и выйти")
        {
            valera.Save("valera.xml");
            Environment.Exit(0);
        }
        else if (actionName != null && Program.actionEffects.ContainsKey(actionName))
        {
            valera.ApplyEffects(Program.actionEffects[actionName]);
        }
        else
        {
            Console.WriteLine("Неверный выбор, попробуйте снова.");
        }
    }
}
