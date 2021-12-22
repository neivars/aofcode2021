#include <stdlib.h>
#include <stdio.h>

// struct Bin {
//     char *binword[13]
// }

int main() {
    FILE *finput;       // input file
    char bin[13];       // binary word read from file
    char *end;

    char gamma[13];     // gamma rating as binary word
    char epsilon[13];   // epsilon rating as binary word

    finput = fopen("day3.input", "r");

    for (int bitidx = 0; bitidx < 12; bitidx++) {
        int binidx = 0;     // index of current binary word
        int bitsum = 0;     // sum of current column in binary word
        
        rewind(finput);

        while (fscanf(finput, "%s\n", bin) != EOF) {
            if (bin[bitidx] == '1') {
                bitsum++;
            }
            binidx++;
        }

        // figure out which value was most common (1 vs 0)
        if (bitsum > binidx / 2) {
            gamma[bitidx] = '1';
            epsilon[bitidx] = '0';
        } else {
            gamma[bitidx] = '0';
            epsilon[bitidx] = '1';
        }
    }

    gamma[12] = '\0';
    epsilon[12] = '\0';

    printf("POWER CONSUMPTION: %ld\n", strtol(gamma, &end, 2) * strtol(epsilon, &end, 2));

    fclose(finput);

    return 0;
}