#include <stdio.h>
#include <string.h>

int main() {
    FILE *finput;
    char dir[8];
    int value;

    int hpos = 0;
    int depth = 0;
    int aim = 0;

    finput = fopen("day2.input", "r");

    while (fscanf(finput, "%s %d\n", dir, &value) != EOF) {
        if (strcmp(dir, "forward") == 0) {
            hpos += value;
            depth += aim * value;
        } else if (strcmp(dir, "up") == 0) {
            aim -= value;
        } else if (strcmp(dir, "down") == 0) {
            aim += value;
        }
    }
    
    fclose(finput);

    printf("FINAL POSITION: %d\n", hpos * depth);
    
    return 0;
}