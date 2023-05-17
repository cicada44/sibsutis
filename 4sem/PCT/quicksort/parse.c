#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_LINE_LEN 256

int main()
{
    FILE* input_file = fopen("data.dat", "r");
    if (input_file == NULL) {
        printf("Unable to open input file\n");
        return 1;
    }

    char line[MAX_LINE_LEN];
    char threads_str[MAX_LINE_LEN], threshold_str[MAX_LINE_LEN], n_str[MAX_LINE_LEN], file_str[MAX_LINE_LEN], time_str[MAX_LINE_LEN];
    int threads, threshold, n;
    float time;
    char* token;

    while (fgets(line, MAX_LINE_LEN, input_file) != NULL) {
        time = -10;
        token = strtok(line, " ");
        while (token != NULL) {
            if (strcmp(token, "Threads") == 0) {
                token = strtok(NULL, " ");
                token = strtok(NULL, " ");
                strcpy(threads_str, token);
                threads = atoi(threads_str);
            } else if (strcmp(token, "Threshold") == 0) {
                token = strtok(NULL, " ");
                token = strtok(NULL, " ");
                strcpy(threshold_str, token);
                threshold = atoi(threshold_str);
            } else if (strcmp(token, "N") == 0) {
                token = strtok(NULL, " ");
                token = strtok(NULL, " ");
                strcpy(n_str, token);
                n = atoi(n_str);
            } else if (strcmp(token, "File:") == 0) {
                token = strtok(NULL, " ");
                strcpy(file_str, token);
            } else if (strcmp(token, "Time:") == 0) {
                token = strtok(NULL, " ");
                strcpy(time_str, token);
                time = atof(time_str);
            } else {
                token = strtok(NULL, " ");
            }
        }

        if (!(time < 0)) {
            char threshold_folder[MAX_LINE_LEN];
            sprintf(threshold_folder, "%d", threshold);
            mkdir(threshold_folder, 0777);
            char file_name[MAX_LINE_LEN];
            sprintf(file_name, "%d.txt", n);

            char full_file_name[MAX_LINE_LEN];
            snprintf(full_file_name, sizeof(full_file_name), "%s/%s", threshold_folder, file_name);

            FILE* output_file = fopen(full_file_name, "a");
            if (output_file == NULL) {
                printf("Unable to open output file\n");
                return 1;
            }

            fprintf(output_file, "%d %f\n", threads, time);

            fclose(output_file);
        }
    }

    fclose(input_file);

    return 0;
}
