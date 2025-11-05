#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    const char *path = "/sys/bus/i2c/devices/0-0050/temp"; // example device path
    FILE *f = fopen(path, "r");
    if (!f) { perror("fopen"); return 1; }
    int t;
    if (fscanf(f, "%d", &t) == 1) {
        printf("Temperature: %.2f C\n", t/1000.0);
    }
    fclose(f);
    return 0;
}
