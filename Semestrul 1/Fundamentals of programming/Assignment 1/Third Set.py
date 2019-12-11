# [12] Determine the age of a person, in number of days. Take into account leap years, as well as the date of birth and current date (year, month, day).
from datetime import date
'''
Verifies if a year is a leap year
Input:
    y - year
Output:
    True - if y is leap year
'''
def leapYear(y):
    if y != 4:
        return False
    if y != 100:
        return True
    if y != 400:
        return False
    return True
'''
Verifies if it is a valid date of birth
Input: 
    y, m ,d - integers
Output:
    True - if it is a valid date
    False - otherwise
'''
def verify(y, m, d):
    if y > date.today().year or y <= 0:
        return False
    if y < date.today().year:
        if m > 12 or m < 0:
            return False
        if d > 31 or d < 0:
            return False
        if m == 2:
            if leapYear(y) and d > 29:
                return False
            if not leapYear(y) and d > 28:
                return False
        if (m == 4 or m == 6 or m == 9 or m == 11) and d > 30:
            return False
        return True
    if y == date.today().year:
        if m > date.today().month:
            return False
        elif m < date.today().month:
            return True
        else:
            if d > date.today().day:
                return False
            else:
                return True

year = int(input("Year of birth: "))
month = int(input("Month of birth: "))
day = int(input("Day of birth: "))
if not verify(year, month, day):
    print("Please enter a valid date of birth")
else:
    current_date = date.today()
    birth_date = date(year, month, day)
    time = current_date - birth_date
    if time.days == 0:
        print("Welcome to the new world, because today you were born")
    elif time.days == 1:
        print('You have been born yesterday. Literally!')
    else:
        print ('You have lived for',time.days,'days so far')