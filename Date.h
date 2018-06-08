//
// Created by Nicola on 19/04/2018.
//

#ifndef LAB5_ES1_DATE_H
#define LAB5_ES1_DATE_H

#include <iostream>
#include <string>
using namespace std;


class Date {
public:

    Date();
    Date(int d, int m, int y);
    Date(const Date & to_copy);

    bool stringToDate(string);                            //'Trasforma' la stringa passata da parametro in un oggetto data


    int year() const;
    int month() const;
    int day() const;

    float yearsFrom(Date d = Date()) const;
    bool _isValid() const;
    string str() const;


    friend ostream& operator << (ostream& stream , const Date& d);
    friend bool operator < (Date d1,Date d2);
    friend bool operator > (Date d1,Date d2);
    friend bool operator == (Date d1,Date d2);

private:
    int _year;
    int _month;
    int _day;
};


#endif //LAB5_ES1_DATE_H
