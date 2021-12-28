#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int mainpart1() {
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

#include "list.c"

char commonbit(struct listnode* list, int bitidx, int* len) {
    struct listnode* lp = list;
    int bitsum = 0;
    float flen = 0.0;

    *len = 0;

    while (lp != NULL) {
        if (lp->data[bitidx] == '1') {
            bitsum++;
        }
        lp = lp->next;
        (*len)++;
    }

    flen = *len;

    printf("COMMONBIT\tBITSUM\t%d\tTHRESH\t%.1f\tLEN\t%d\n", bitsum, flen / 2, (*len));

    if (bitsum > flen / 2) {
        return '1';
    } else if (bitsum < flen / 2) {
        return '0';
    } else {
        return 'S';
    }
}

int main() {
    clock_t startt = clock();
    FILE* finput;       // input file
    char bin[13];       // binary word read from file
    int bitidx = 0;
    char* end = NULL;

    struct listnode* oxygen = NULL;
    int oxylen = 0;
    struct listnode* co2scrub = NULL;
    int co2len = 0;

    finput = fopen("day3.input", "r");

    while (fscanf(finput, "%s\n", bin) != EOF) {
        listpush(&oxygen, bin);
        listpush(&co2scrub, bin);
    }

    do {
        printf("==============================\n\n");
        listprint(oxygen, "OXYGEN RATING LIST");
        char oxycbit = commonbit(oxygen, bitidx, &oxylen);

        struct listnode* cursor = oxygen;
        struct listnode* prev = NULL;

        oxycbit = oxycbit == 'S' ? '1' : oxycbit;

        printf("OXY\t\tBIT\t%c\tCOL\t%d\tLEN\t%d\n", oxycbit, bitidx, oxylen);

        while (cursor != NULL && oxylen > 1) {
            if (prev == NULL) {
                // head is to be removed, shift it to the right
                if (cursor->data[bitidx] != oxycbit) {
                    struct listnode* next = cursor->next;
                    free(cursor);
                    cursor = next;
                    oxygen = next;
                    continue;
                } else {
                    prev = cursor;
                }
            } else {
                if (cursor->data[bitidx] != oxycbit) {
                    prev->next = cursor->next;
                    free(cursor);
                } else {
                    prev = cursor;
                }
            }

            cursor = prev->next;
        }

        printf("\n");

        listprint(co2scrub, "CO2 SCRUBBER LIST");
        char co2cbit = commonbit(co2scrub, bitidx, &co2len);

        cursor = co2scrub;
        prev = NULL;

        co2cbit = co2cbit == 'S' ? '1' : co2cbit;

        printf("CO2\t\tBIT\t%c\tCOL\t%d\tLEN\t%d\n", co2cbit, bitidx, co2len);

        while (cursor != NULL && co2len > 1) {
            if (prev == NULL) {
                // head is to be removed, shift it to the right
                if (cursor->data[bitidx] == co2cbit) {
                    struct listnode* next = cursor->next;
                    free(cursor);
                    cursor = next;
                    co2scrub = next;
                    continue;
                } else {
                    prev = cursor;
                }
            } else {
                if (cursor->data[bitidx] == co2cbit) {
                    prev->next = cursor->next;
                    free(cursor);
                } else {
                    prev = cursor;
                }
            }

            cursor = prev->next;
        }

        bitidx++;
    } while ((oxylen > 1 || co2len > 1) && bitidx < 12);

    long oxygenrat = strtol(oxygen->data, &end, 2);
    long co2scrrat = strtol(co2scrub->data, &end, 2);

    printf("==============================\n");
    printf("==============================\n\n");

    printf("OXYGEN GENERATOR RATING: (%s) %ld \n", oxygen->data, oxygenrat);
    printf("CO2 SCRUBBER RATING: (%s) %ld \n", co2scrub->data, co2scrrat);
    printf("LIFE SUPPORT RATING: %ld\n", oxygenrat * co2scrrat);

    printf("Time to calculate: %fs\n", (double) (clock() - startt) / CLOCKS_PER_SEC);

    return 0;
}