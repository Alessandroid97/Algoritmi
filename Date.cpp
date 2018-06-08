//
// Created by Nicola on 19/04/2018.
//

#include "date.h"
#include <iostream>
#include <ctime>
#include <string>
using namespace std;


Date::Date()
{
    time_t timer;
    struct tm* timeinfo;
    time(&timer);
    timeinfo= localtime(&timer);
    _day=timeinfo->tm_mday;
    _month=timeinfo->tm_mon+1;
    _year=timeinfo->tm_year+1900;
}
void Date::setAll(int d, int m, int y) {
    _day=d;
    _month=m;
    _year=y;
}
Date::Date(const Date &to_copy)
{
    _day=to_copy._day;
    _month=to_copy._month;
    _year=to_copy._year;
}

bool Date::stringToDate(const string d_str) {
    string number;
    int d, m, y;
    if(d_str[2]=='/' && d_str[5]=='/') {
        number=d_str.substr(0,2);
        d = stoi(number);
        number=d_str.substr(3,2);
        m = stoi(number);
        number=d_str.substr(6,4);
        y = stoi(number);
        if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) {
            if (d <= 31 && d >= 1 && y >= 0) {
                setAll(d,m,y);
                return true;
            }else{return false;}
        }else{
            if (m == 4 || m == 6 || m == 9 || m == 11) {
                if (d <= 30 && d >= 1 && y >= 0) {
                    setAll(d,m,y);
                    return true;
                }else{return false;}
            }else{
                if(m==2 && d<=29 && d>=1 && y>0){
                    setAll(d,m,y);
                    return true;
                }else{return false;}
            }
        }
    }else{return false;}
}


bool Date::_isValid() const
{
    if(day()<=31&&day()>=1&&month()<=12&&month()>=1)
    {
            return true;
    }
    return false;
}
int Date::year() const
{
    return _year;
}
int Date::month() const
{
    return _month;
}
int Date::day() const
{
    return _day;
}
float Date::yearsFrom(Date d ) const
{
    float years = year() + (month() / 12) + (day() / 365);
    float yearsnow = d.year() + (d.month() / 12) + (d.day() / 365);
    return yearsnow - years;
}
string Date::str() const
{
    return to_string(day())+"/"+to_string(month())+"/"+to_string(year());
}
ostream& operator << (ostream &stream, const Date &d)
{
    stream<<d.str();
    return stream;
}
bool operator < (Date d1, Date d2)
{
    if(d1.year()<d2.year())
    {
        return true;
    }
    else if(d1.year()==d2.year()&&d1.month()<d2.month())
    {
        return true;
    }
    else if(d1.year()==d2.year()&&d1.month()==d2.month()&&d1.day()<d2.day())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator > (Date d1, Date d2)
{
    if(d1.year()>d2.year())
    {
        return true;
    }
    else if(d1.year()==d2.year()&&d1.month()>d2.month())
    {
        return true;
    }
    else if(d1.year()==d2.year()&&d1.month()==d2.month()&&d1.day()>d2.day())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator == (Date d1,Date d2)
{
    if(d1.year()==d1.year()&&d1.month()==d2.month()&&d1.day()==d2.day())
    {
        return true;
    }
    return false;
}







