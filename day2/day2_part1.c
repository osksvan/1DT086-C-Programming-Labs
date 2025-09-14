#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>


int num_digits(int n) {
    int count = 0;
    if (n == 0)  // Zero is one digit
        return 1;
    while (n != 0) { // Remove each digit while counting
        n = n/10;
        count++;
    }
    return count;
}

int main() {
    const char *inputfile = "day2_input.txt";
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

    int matrix[lines+1][8];
    rewind(file); // Rewind back to beginning

    char line[100]; // Each row seems to be less than 100 chars

    int line_index = 0;

    while(fgets(line, sizeof(line), file)){
        int skip = 0; // Number of chars to skip into line
        for(int i = 0; i < 8; i++){
            if(sscanf(line+skip, "%d", &matrix[line_index][i]) != 1){ // Try to read a number
                // If reading fails, fill in the rest of the matrix columns with MAX_INT as "EOL"
                for(int j = i; j < 8; j++)
                    matrix[line_index][j] = INT_MAX;
                break;
            }
            skip += num_digits(matrix[line_index][i]) + 1; // Offset the read characters (digits + space)
        }
        line_index++;
    }
    int num_ok = 0;
    for(int i = 0; i <= lines; i++){
        bool ok = true;
        bool inc = matrix[i][0] < matrix[i][1]; // Determine if values should be increasing or decreasing
        
        // Compare each pair of values (starting at 1 because we check previous value)
        for(int j = 1; j < 8; j++){
            int fst = matrix[i][j-1];
            int snd = matrix[i][j];
            if(snd == INT_MAX) // Ignore "EOL" value inserted previously
                break;
            if(fst == snd) // Values cannot be the same
                ok = false;
            if(inc && (snd < fst || snd > fst + 3)) // If increasing, require snd to be fst < x < fst+3
                ok = false;
            else if(!inc && (snd > fst || snd < fst - 3)) // If decreasing, require snd to be fst-3 < x < fst
                ok = false;
            
        }
        if(ok)
            num_ok++;
    }
    printf("Safe reports: %d\n", num_ok);
}