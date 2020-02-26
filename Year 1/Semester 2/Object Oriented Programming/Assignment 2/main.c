#include <stdio.h>
#include <string.h>

int main() {
    int days[100], months[100], years[100], currentDays = 0, currentElement = 0;
    char message[100];
    while(1) {
        scanf("%s", message);
        if (strcmp(message, "exit") == 0) {
            break;
        }
        days[currentElement] = (message[0] - '0') * 10 + message[1] - '0';
        months[currentElement] = (message[3] - '0') * 10 + message[4] - '0';
        years[currentElement] = (message[6] - '0') * 1000 + (message[7] - '0') * 100 + (message[8] - '0') * 10 + message[9] - '0';
        currentElement++;
    }
    for (int c = 0; c < currentElement; ++c) {
        currentDays = 0;
        for (int i = 1; i <= months[c]; ++i) {
            if (i == months[c]) {
                currentDays += days[c];
            } else {
                if (i == 2) {
                    currentDays += 28;
                    if ((years[c] % 4 == 0 && years[c] % 100 != 0) || years[c] % 400 == 0) {
                        currentDays++;
                    }
                } else {
                    if (i % 2 == 1) {
                        currentDays += 31;
                    } else {
                        currentDays += 30;
                    }
                }
            }
        }
        printf("%d ", currentDays);
    }
    return 0;
}
