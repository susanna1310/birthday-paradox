#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#include "LUT_method.h"
#include "taylor.h"
#include "Heron.h"
void select_method(int imp, int bench, unsigned long n)
{
    if (bench == 0)
    {
        switch (imp)
        {
        case 0:
            printf("k=%f\n", birthday_eq(n));
            break;
        case 1:
            construct_table();
            printf("k=%f\n", birthday_eq_V1(n));
            break;
        case 2:
            printf("k=%f\n", birthday_eq_V2(n));
            break;
        }
    }
    else
    {
        double time;
        struct timespec start0;
        struct timespec end0;
        struct timespec start1;
        struct timespec end1;
        struct timespec start2;
        struct timespec end2;
        float k = 0;
        switch (imp)
        {
        case 0:

            clock_gettime(CLOCK_MONOTONIC, &start0);
            for (int i = 0; i < bench; i++)
                k = birthday_eq(n);

            clock_gettime(CLOCK_MONOTONIC, &end0);
            time = end0.tv_sec - start0.tv_sec + 1e-9 * (end0.tv_nsec - start0.tv_nsec);
            printf("done after %f\n", time);
            printf("k=%f\n", k);
            break;
        case 1:
            construct_table();
            clock_gettime(CLOCK_MONOTONIC, &start1);
            for (int i = 0; i < bench; i++)
                k = birthday_eq_V1(n);

            clock_gettime(CLOCK_MONOTONIC, &end1);
            time = end1.tv_sec - start1.tv_sec + 1e-9 * (end1.tv_nsec - start1.tv_nsec);
            printf("done after %f\n", time);
            printf("k=%f\n", k);
            break;
        case 2:

            clock_gettime(CLOCK_MONOTONIC, &start2);
            for (int i = 0; i < bench; i++)
                k = birthday_eq_V2(n);

            clock_gettime(CLOCK_MONOTONIC, &end2);
            time = end2.tv_sec - start2.tv_sec + 1e-9 * (end2.tv_nsec - start2.tv_nsec);
            printf("done after %f\n", time);
            printf("k=%f\n", k);
            break;
        }
    }
}
int run_tests(int imp, int bench)
{
    unsigned long x = 1;
    printf("for n =%lu\n", x);
    select_method(imp, bench, x);
    printf("expected_k=%f\n", birthday_eq(x));
    x = 365;
    printf("for n =%lu\n", x);
    select_method(imp, bench, x);
    printf("expected_k=%f\n", birthday_eq(x));
    x = 100000;
    printf("for n =%lu\n", x);
    select_method(imp, bench, x);
    printf("expected_k=%f\n", birthday_eq(x));
    x = 10000000000;
    printf("for n =%lu\n", x);
    select_method(imp, bench, x);
    printf("expected_k=%f\n", birthday_eq(x));
    x = 1000000000000000;
    printf("for n =%lu\n", x);
    select_method(imp, bench, x);
    printf("expected_k=%f\n", birthday_eq(x));

    x = ULONG_MAX;
    printf("for n =%lu\n", x);
    select_method(imp, bench, x);
    printf("expected_k=%f\n", birthday_eq(x));

    return 0;
}
int print_user_manual(char *path)
{
    FILE *user_man = fopen(path, "r");
    char c;
    while ((c = fgetc(user_man)) != EOF)
        putchar(c);
    fclose(user_man);
    return 0;
}
// main program
int main(int argc, char **argv)
{
    int test_flag = 0;
    int help_flag = 0;
    int n_flag = 0;
    int w = 0;
    int imp = 0;
    int option = 0;
    unsigned long n = 0;
    int option_index = 'h';
    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'}};
    while ((option = getopt_long(argc, argv, "TV:B:n:h", long_options, &option_index)) != -1)

    {
        switch (option)
        {
        case 'T':
            test_flag = 1;
            break;

        case 'V':
            if (optarg != NULL)
            {
                if (*(optarg + 1) != 0 || (*optarg != 48 && *optarg != 50 && *optarg != 49))
                {
                    fprintf(stderr, "after V should be either 0 or 1 or 2!\n ");
                    return -1;
                }
                else
                {
                    imp = strtoul(optarg, NULL, 0);
                }
            }
            break;
        case 'B':
            if (optarg != NULL)
            {
                if (*optarg == 45)
                {
                    fprintf(stderr, "Number of repetitions should not be negative!\n");
                    return -1;
                }
                int i = 0;
                while (*(optarg + i) >= 48 && *(optarg + i) <= 57 && *(optarg + i) != 0)
                {
                    i++;
                }
                w = strtoul(optarg, NULL, 0);
                if (*(optarg + i) != 0)
                {
                    fprintf(stderr, "the number of repetitions should be an integer !\n");
                    return -1;
                }
                else if (i > 10 || (i == 10 && (w < 0 || *(optarg) > '2')))
                {
                    fprintf(stderr, "the number of repetitions should not be greater than 2147483647(=INT_MAX)! \n");
                    return -1;
                }
            }
            break;
        case 'n':
            if (optarg != NULL)
            {
                if (*optarg == 45)
                {
                    fprintf(stderr, "the size of the base set should be positive!\n");
                    return -1;
                }
                int i = 0;
                while (*(optarg + i) >= 48 && *(optarg + i) <= 57 && *(optarg + i) != 0)
                {
                    i++;
                }
                n = strtoul(optarg, NULL, 0);
                if (*(optarg + i) != 0)
                {
                    fprintf(stderr, "the size of the base set should be unsigned long!\n");
                    return -1;
                }
                else if (i > 20)
                {
                    fprintf(stderr, "the size of the base set should not be larger than 18446744073709551615(=ULONG_MAX)! \n");
                    return -1;
                }
                else if (i == 20 && n == ULONG_MAX)
                {
                    char arr[20] = {'1', '8', '4', '4', '6', '7', '4', '4', '0', '7', '3', '7', '0', '9', '5', '5', '1', '6', '1', '5'};
                    i--;
                    while (i >= 0 && *(optarg + i) == arr[i])
                    {
                        i--;
                    }
                    if (i >= 0)
                    {
                        fprintf(stderr, "the size of the base set should not be larger than 18446744073709551615(=ULONG_MAX)! \n");
                        return -1;
                    }
                }
                n_flag = 1;
            }
            break;
        case 'h':
            help_flag = 1;
            break;

        default:
            fprintf(stderr, "use %s -h for user manual\n", argv[0]);
            return 1;
        }
    }
    if (test_flag)
    {
        run_tests(imp, w);
        return 0;
    }

    if (help_flag)
    {
        if (print_user_manual("README_Benutzerhandbuch.txt"))
            return -1;
        return 0;
    }
    if (n_flag == 0)
    {
        fprintf(stderr, "Enter the size of the base set \nType -h or --help to get more information\n");
        return -1;
    }
    select_method(imp, w, n);
    return 0;
}