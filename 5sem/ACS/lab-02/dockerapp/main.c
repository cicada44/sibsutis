#include <cstdlib>
#include <csignal>

#include <string>
#include <iostream>

void signal_handler(int signum)
{
    std::cout << "SIGNAL HANDLER SIGNUM: " << signum << '\n';
    std::terminate();
}

int main(int argc, char *argv[])
{
    signal(SIGINT, signal_handler);

    if (argc > 1)
    {
        std::cerr << argc << '\n';
    }
    else
    {
        std::cout << getenv("${HOME}") << '\n';
    }
}
