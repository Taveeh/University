#include <stdio.h>
#include <string.h>

int main() {
    int days[100], months[100], years[100], currentDays = 0, currentIndex = 0;
    char dateInput[100];
    while(1) {
        scanf("%s", dateInput);
        if (strcmp(dateInput, "exit") == 0) {
            break;
        }
        days[currentIndex] = (dateInput[0] - '0') * 10 + dateInput[1] - '0';
        months[currentIndex] = (dateInput[3] - '0') * 10 + dateInput[4] - '0';
        years[currentIndex] = (dateInput[6] - '0') * 1000 + (dateInput[7] - '0') * 100 + (dateInput[8] - '0') * 10 + dateInput[9] - '0';
        currentIndex++;
    }
    int numberOfDates = currentIndex;
    for (int currentDate = 0; currentDate < numberOfDates; ++currentDate) {
        currentDays = 0;
        for (int i = 1; i <= months[currentDate]; ++i) {
            if (i == months[currentDate]) {
                currentDays += days[currentDate];
            } else {
                if (i == 2) {
                    currentDays += 28;
                    if ((years[currentDate] % 4 == 0 && years[currentDate] % 100 != 0) || years[currentDate] % 400 == 0) {
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
