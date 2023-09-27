//cpu intensive program
#include <stdio.h>
#include <stdbool.h>

bool is_prime(int n) {
    if (n <= 1) {
        return false;
    } else if (n <= 3) {
        return true;
    } else if (n % 2 == 0 || n % 3 == 0) {
        return false;
    } else {
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) {
                return false;
            }
        }
        return true;
    }
}

void cpu_intensive_task() {
    int start_number = 1;
    int end_number = 300000000;

    printf("Calculating prime numbers between %d and %d...\n", start_number, end_number);

    for (int num = start_number; num < end_number; num++) {
        if (is_prime(num)) {
            // Do nothing, just calculate
        }
    }

    printf("CPU-intensive task completed.\n");
}

int main() {
    cpu_intensive_task();
    return 0;
}

