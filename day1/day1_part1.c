#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int compare(const void *p, const void *q) {
    // Compare function returns:
    // negative value if p < q
    // positive value if p > q
    // zero if p and q are equal

    // Cast and dereference p and q
    int x = *(int*) p;
    int y = *(int*) q;

    if(x < y)
        return -1;
    if(x > y)
        return 1;
    return 0;
}

int main() {
    const char *inputfile = "day1_input.txt";
    FILE *file = fopen(inputfile, "r"); 

    file = fopen(inputfile, "r");
    if(file == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Count number of lines in the file, needed to create arrays of correct length
    int lines = 0;

    char c;
    for(c = getc(file); c != EOF; c = getc(file)) // Read each char in file
        if(c == '\n') // Only count newlines
            lines++;

    int first_col[lines], second_col[lines];
    rewind(file); // Rewind back to beginning

    // Read two values (int) for each row in file, save to arrays
    for(int i = 0; i <= lines; i++){
        int ret = fscanf(file, "%d %d", &first_col[i], &second_col[i]);
        if(ret != 5){ // We expect to get two numbers from each row
            printf("Read failed\n");
            return 1;

        }
    }
    fclose(file); // Close the file pointer!

    // Sort both arrays
    qsort(first_col, lines + 1, sizeof(int), compare);
    qsort(second_col, lines + 1, sizeof(int), compare);

    // Add the difference between each pair of values
    int diff_sum = 0;
    for(int i = 0; i <= lines; i++){
        diff_sum += abs(first_col[i] - second_col[i]);
    }
    printf("Difference: %d\n", diff_sum);
}