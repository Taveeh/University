//
// Created by Octavian Custura on 18/03/2020.
//

#ifndef ASSIGNMENT_5_6_FOOTAGE_H
#define ASSIGNMENT_5_6_FOOTAGE_H

#include <string>
class Date {
private:
    int day, month, year;
public:
    Date(int day, int month, int year);
    [[nodiscard]] int getDay() const;
    [[nodiscard]] int getMonth() const;
    [[nodiscard]] int getYear() const;
    friend bool operator<=(const Date& compareDate1, const Date& compareDate2);
};

class Footage {
private:
    std::string title;
    std::string type;
    Date date;
    int numberAccessed;
    std::string link;

public:
    Footage(std::string title, std::string type, Date date, int numberAccessed, std::string link);

    void changeType(std::string newType);

    void changeDate(Date newDate);

    void changeAccessCount(int newAccessCount);

    void changeLink(std::string link);

    std::string getTitle() const;

    std::string getType();

    Date getDate();

    int getAccessCount();

    std::string getLink();
};


#endif //ASSIGNMENT_5_6_FOOTAGE_H
