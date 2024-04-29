#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

void factorial(mpz_t result, long n)
{
    mpz_init_set_si(result, 1);
    for (long i = 1; i <= n; ++i) {
        mpz_mul_si(result, result, i);
    }
}

void print_usage()
{
    fprintf(stderr, "Usage: factorial N, where N is the number you want to get the factorial of.\n");
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        print_usage();
        return 1;
    }
    char* end = NULL;
    long n = strtol(argv[1], &end, 10);
    if (*end != '\0') {
        print_usage();
        return 1;
    }
    mpz_t result;
    factorial(result, n);
    gmp_printf("factorial(%d) = %Zd\n", n, result);
    mpz_clear(result);
}
