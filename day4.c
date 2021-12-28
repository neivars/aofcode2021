#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* finput;

    char numline[512];
    short* nums = (short*) malloc(0);
    size_t numslen = 0;

    finput = fopen("day4.input", "r");

    // first line parsed into a (dynamic!) array of shorts
    fscanf(finput, "%s", numline);
    char* num = strtok(numline, ",");
    while (num != NULL) {
        numslen++;
        nums = (short*) realloc(nums, sizeof(short) * numslen);
        nums[numslen - 1] = (short) atoi(num);
        num = strtok(NULL, ",");
    }

    printf("NUMS ARRAY\t(%p)\tLEN :\t%zu\n", nums, numslen);
    for (int i = 0; i < numslen; i ++) {
        printf("\t> [%03d] %2d\n", i, nums[i]);
    }
    printf("\n");
    
    // TODO: parse the bingo boards

    fclose(finput);
}