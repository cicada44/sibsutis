#include <mpi.h>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
    int rank, size, n = 100;  // Количество итераций
    double start, end, total_time = 0.0;

    if (argc > 2) {
        std::cout << "Usage: " << argv[0] << " <message_size>\n";
        return 0;
    }

    int message_size = std::stoi(argv[1]) * 1024 * 1024; // Размер сообщения в байтах

    MPI_Init(&argc, &argv);                // Инициализация MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Определение номера текущего процесса
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Определение общего количества процессов

    if (size != 8) {
        std::cerr << "Необходимо 8 процессов для выполнения программы" << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // Создание вектора для хранения сообщения
    std::vector<char> message(message_size);
    MPI_Request request;
    MPI_Status status;

    // Определяем, какие процессы будут обмениваться сообщениями
    // Процессы 0-3 общаются с процессами 4-7
    int target = -1;
    if (rank < 4) {
        target = rank + 4;
    } else if (rank >= 4) {
        target = rank - 4;
    }

    for (int i = 0; i < n; i++) {
        start = MPI_Wtime();  // Начало измерения времени

        // Взаимный обмен между процессами
        MPI_Isend(message.data(), message_size, MPI_CHAR, target, 0, MPI_COMM_WORLD, &request);
        MPI_Irecv(message.data(), message_size, MPI_CHAR, target, 0, MPI_COMM_WORLD, &request);

        // Ожидание завершения всех операций обмена
        MPI_Wait(&request, &status);

        end = MPI_Wtime();  // Окончание измерения времени
        total_time += (end - start);
    }

    // Вывод среднего времени выполнения для каждого процесса
    std::cout << "rank " << rank << ": size = " << argv[1] << " M, avg_time = " << total_time / n << " s\n";

    MPI_Finalize();
}
