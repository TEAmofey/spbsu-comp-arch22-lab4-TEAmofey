#include <iostream>
#include <string>
#include <cstdio>
#include <ctime>
#include <cstddef>
#include <omp.h>
#include <cassert>

using namespace std;

int main(int argc, char **argv) {
    if (argc != 4) {
        cerr << "incorrect arg count\n";
        return 1;
    }
    double r;
    long long N;

    FILE *input = fopen(argv[2], "rt");
    if (!input) {
        cerr << "can't open input file\n";
        return 1;
    }
    if (fscanf(input, "%lf %lld\n", &r, &N) != 2 || !feof(input)) {
        cerr << "incorrect format\n";
        return 1;
    }
    assert(r > 0);
    assert(N > 0);

    int threads = atoi(argv[1]);
    long long sum_hit = 0;
    double time_start;
    if (threads > 0 && threads <= omp_get_max_threads()) {
        omp_set_num_threads(threads);
        time_start = omp_get_wtime();
#pragma omp parallel
        {
            unsigned int rnd = (time(NULL) * 1103515245 + omp_get_thread_num() * 12345);
            long long hit = 0;
            double x;
            double y;
#pragma omp for schedule(static)
            for (long long i = 0; i < N; i++) {
                rnd = rnd * 1103515245 + 12345;
                x = (2 * (double) (rnd) / (double) 4294967295 - 1) * r;
                rnd = rnd * 1103515245 + 12345;
                y = (2 * (double) (rnd) / (double) 4294967295 - 1) * r;
                hit += x * x + y * y < r * r;
            }
#pragma omp atomic
            sum_hit += hit;
        }
    } else if (threads == 0) {
        time_start = omp_get_wtime();
#pragma omp parallel
        {
            unsigned int rnd = (time(NULL) * 1103515245);
            long long hit = 0;
            double x;
            double y;
#pragma omp for
            for (long long i = 0; i < N; i++) {
                rnd = rnd * 1103515245 + 12345;
                x = (2 * (double) (rnd) / (double) 4294967295 - 1) * r;
                rnd = rnd * 1103515245 + 12345;
                y = (2 * (double) (rnd) / (double) 4294967295 - 1) * r;
                hit += x * x + y * y < r * r;
            }
#pragma omp atomic
            sum_hit += hit;
        }
    } else if (threads == -1) {
        time_start = omp_get_wtime();
        unsigned int rnd = (time(NULL) * 1103515245);
        long long hit = 0;
        double x;
        double y;
        for (long long i = 0; i < N; i++) {
            rnd = rnd * 1103515245 + 12345;
            x = (2 * (double) (rnd) / (double) 4294967295 - 1) * r;
            rnd = rnd * 1103515245 + 12345;
            y = (2 * (double) (rnd) / (double) 4294967295 - 1) * r;
            hit += x * x + y * y < r * r;
        }
        sum_hit += hit;
    } else {
        cerr << "incorrect param threads (argv[1])\n";
        return 1;
    }
    double time = omp_get_wtime() - time_start;
    FILE *output = fopen(argv[3], "wt");
    if (!output) {
        cerr << "can't open output file\n";
        return 1;
    }
    fprintf(output, "%lf\n", 4 * r * r * (double) sum_hit / (double) N);
    fclose(output);
    printf("Time (%i thread(s)): %g ms\n", threads, 1000 * time);
    return 0;
}
