#include <stdio.h>

int mainpart1() {
    FILE* input;
    int measure;
    int prvmeas;
    int measinc = 0;

    input = fopen("day1.input", "r");

    fscanf(input, "%d\n", &prvmeas);

    while (fscanf(input, "%d\n", &measure) != EOF) {
        if (measure > prvmeas) {
            measinc++;
        }
        prvmeas = measure;
    }

    fclose(input);

    printf("NUMBER OF MEASUREMENT INCREASES: %d\n", measinc);

    return 0;
}

int main() {
    FILE* input;
    int measure;

    int awindow = 0;
    int acount = 0;

    int bwindow = 0;
    int bcount = -1;

    int cwindow = 0;
    int ccount = -2;

    int dwindow = 0;
    int dcount = -3;

    int measureinc = 0;

    int firstpass = 1;

    input = fopen("day1.input", "r");

    while (fscanf(input, "%d\n", &measure) != EOF) {
        if (dcount >= 2) {
            if (dwindow > cwindow) {
                measureinc++;
            }
            dcount = -1;
        } else {
            dcount++;
        }

        if (ccount >= 2) {
            if (cwindow > bwindow) {
                measureinc++;
            }
            ccount = -1;
        } else {
            ccount++;
        }

        if (bcount >= 2) {
            if (bwindow > awindow) {
                measureinc++;
            }
            bcount = -1;
            firstpass = 0; // we can now use WINDOW A to compare to WINDOW D
        } else {
            bcount++;
        }

        if (acount >= 2) {
            if (awindow > dwindow && !firstpass) {
                measureinc++;
            }
            acount = -1;
        } else {
            acount++;
        }

        if (acount == 0) {
            awindow = measure;
        } else if (acount > 0) {
            awindow += measure;
        }

        if (bcount == 0) {
            bwindow = measure;
        } else if (bcount > 0) {
            bwindow += measure;
        }

        if (ccount == 0) {
            cwindow = measure;
        } else if (ccount > 0) {
            cwindow += measure;
        }

        if (dcount == 0) {
            dwindow = measure;
        } else if (dcount > 0) {
            dwindow += measure;
        }
    }

    fclose(input);

    printf("NUMBER OF MEASUREMENT INCREASES: %d\n", measureinc);

    return 0;
}