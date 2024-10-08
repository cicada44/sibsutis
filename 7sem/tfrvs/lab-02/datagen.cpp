#include <iostream>
#include <random>

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cout << "Usage:\n\t" << argv[0] << " <n> <m>\n";
        return -1;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis_rank(1, std::atoi(argv[1]));
    std::uniform_int_distribution<> dis_time(1, 100);

    for (int i = 0; i != std::atoi(argv[2]); ++i)
        std::cout << dis_rank(gen) << ' ' << dis_time(gen) << '\n';
}
