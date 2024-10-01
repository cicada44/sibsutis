#include <mpi.h>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
    int rank, size, n = 100; // Количество итераций
    double start, end, total_time = 0.0;

    if (argc > 2) {
        std::cout << "Usage: " << argv[0] << ' ' << "<message_size>\n";
        return 0;
    }
    int message_size = std::stoi(argv[1]) * 1024 * 1024; // Размер сообщения в байтах

    MPI_Init(&argc, &argv);               // Инициализация MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Определение номера текущего процесса
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Определение общего количества процессов

    if (size < 2) {
        std::cerr << "Необходимо минимум 2 процесса" << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // Создание вектора для хранения сообщения
    std::vector<char> message(message_size);
    MPI_Request request;
    MPI_Status status;

    for (int i = 0; i < n; i++) {
        start = MPI_Wtime(); // Начало измерения времени

        if (rank == 0) {
            // Процесс 0 отправляет и принимает сообщение
            MPI_Isend(message.data(), message_size, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &request);
            MPI_Irecv(message.data(), message_size, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &request);
        } else if (rank == 1) {
            // Процесс 1 принимает и отправляет сообщение
            MPI_Irecv(message.data(), message_size, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &request);
            MPI_Isend(message.data(), message_size, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &request);
        }

        // Ожидание завершения всех операций обмена
        MPI_Wait(&request, &status);
        end = MPI_Wtime();  // Окончание измерения времени
        total_time += (end - start);
    }

    // Вывод результатов
    if (rank == 0) {
        std::cout << "size = " << argv[1] << " MB, avg_time = " << total_time / n << " s\n";
    }

    MPI_Finalize(); // Завершение работы MPI
    return 0;
}
