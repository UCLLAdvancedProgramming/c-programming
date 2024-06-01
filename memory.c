#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool read_number(long* i) {
    char* line = NULL;
    size_t length = 0;
    // getline allocates an array of chars
    ssize_t result = getline(&line, &length, stdin);
    if (result == -1) {
        // Fix memory leak
        free(line);
        // Could not get line
        return false;
    } else {
        char *end = NULL;
        *i = strtol(line, &end, 10);
        if (*end == '\n') {
            // Fix memory leak
            free(line);
            return true;
        } else {
            // Fix memory leak
            free(line);
            return false;
        }
    }
}

void read_numbers(long* numbers, long nb_numbers) {
    for (long i = 0; i < nb_numbers;) {
        printf("i%ld: ", i + 1);
        long n = 0;
        if (read_number(&n)) {
            numbers[i] = n;
            ++i;
        } else {
            puts("Please enter a valid number!");
        }
    }
}

long sum(long* numbers, long nb_numbers) {
    long result = 0;
    // Fix array out of bounds access
    // for (long i = 0; i <= nb_numbers; ++i) {
    for (long i = 0; i < nb_numbers; ++i) {
        result += numbers[i];
    }
    return result;
}

int main(void) {
    // Disable output buffering
    setbuf(stdout, NULL);

    puts("How many numbers do you want to add up?");
    long nb_numbers = 0;
    if (!read_number(&nb_numbers)) {
        fprintf(stderr, "Failed to read number, exiting...");
        return -1;
    }

    // If we want to create an array of longs, then we need
    // to calculate how many bytes we need: the size of a long
    // times the amount of numbers we want to allocate.
    long* numbers = malloc(nb_numbers * sizeof(long));

    read_numbers(numbers, nb_numbers);

    printf("Sum: %ld\n", sum(numbers, nb_numbers));

    free(numbers);
    // Fixes double free
    // free(numbers);
}
