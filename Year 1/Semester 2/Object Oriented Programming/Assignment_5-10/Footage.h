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
	/*
	 * Default constructor
	 */
	Date();

	/*
	 * Constructor
	 */
	Date(int day, int month, int year);
	/*
	 * Function that gets the day of the date
	 * Input:
	 * Output:
	 * int - current day
	 */
	[[nodiscard]] int getDay() const;

	/*
	 * Function that gets the month of the date
	 * Input:
	 * Output:
	 * int - current month
	 */
	[[nodiscard]] int getMonth() const;

	/*
	 * Function that gets the year of the date
	 * Input:
	 * Output:
	 * int - current year
	 */
	[[nodiscard]] int getYear() const;

	/*
	 * Operator < for comparing dates
	 * Input:
	 * compareDate1, compareDate2 - const Date&
	 * Output: bool
	 * true if compareDate1 < compareDate2
	 * false otherwise
	 */
	friend bool operator<(const Date& compareDate1, const Date& compareDate2);

	/*
	 * Returns the string for a class
	 * Input:
	 * Output:
	 * std::string
	 */
	[[nodiscard]] std::string toString() const;

	friend std::istream& operator>>(std::istream& inputStream, Date& date);

	friend std::ostream& operator<<(std::ostream& outputStream, const Date& date);
};

class Footage {
	friend class ValidatorFootage;
private:
	std::string title;
	std::string type;
	Date date;
	int numberAccessed;
	std::string link;
public:
	/*
	 * Default constructor
	 */
	Footage();

	/*
	 * Constructor
	 */
	Footage(std::string title, std::string type, Date date, int numberAccessed, std::string link);

	/*
	 * Function that changes type of footage
	 * Input:
	 * newType - std::string
	 */
	void changeType(std::string newType);

	/*
	 * Function that changes date of footage
	 * Input:
	 * newDate - Date
	 */
	void changeDate(Date newDate);

	/*
	 * Function that changes the access count of footage
	 * Input:
	 * newAccessCount - int
	 */
	void changeAccessCount(int newAccessCount);

	/*
	 * Function that changes the link of the footage
	 * Input:
	 * link - std::string
	 */
	void changeLink(std::string link);

	/*
	 * Function that gets the title of the Footage
	 * Input:
	 * Output:
	 * title - std::string
	 */
	[[nodiscard]] std::string getTitle() const;

	/*
	* Function that gets the type of the Footage
	* Input:
	* Output:
	* type - std::string
	*/
	[[nodiscard]] std::string getType() const;

	/*
	 * Function that gets the date of the Footage
	 * Input:
	 * Output:
	 * date - Date
	 */
	[[nodiscard]] Date getDate() const;

	/*
	 * Function that gets the access count of the Footage
	 * Input:
	 * Output:
	 * access count - int
	 */
	[[nodiscard]] int getAccessCount() const;

	/*
	 * Function that gets the link of the Footage
	 * Input:
	 * Output:
	 * link - std::string
	 */
	[[nodiscard]] std::string getLink() const;

	/*
	 * Returns a string regarding the footage
	 * Input:
	 * Ouput: std::string
	 */
	[[nodiscard]] std::string toString() const;

	/*
	 * Reads a whole footage from the stream
	 * Input:
	 *  std::istream - input stream
	 *  Footage& - footage to be read
	 * Output:
	 *  std::istream
	 */
	friend std::istream& operator>>(std::istream& inputStream, Footage& footage);
	/*
	 * Writes a footage to the stream
	 * Input:
	 *  std::ostream& - output stream
	 *  const Footage& - footage to be written
	 * Output:
	 *  std::ostream&
	 */
	friend std::ostream& operator<<(std::ostream& outputStream, const Footage& footage);
};

#endif //ASSIGNMENT_5_6_FOOTAGE_H
