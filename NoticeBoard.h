//
// Created by Nicola on 06/06/2018.
//

#ifndef PROGETTO_NOTICEBOARD_H
#define PROGETTO_NOTICEBOARD_H

#include <iostream>
#include <string>
#include <vector>
#include "Date.h"
#include <fstream>
using namespace std;

struct newsStruct {
    string _text;
    string _id;
    Date _date;
    long _like;
    vector<string> _userlike;
    long _dislike;
    vector<string> _userdislike;
};

class NoticeBoard
{
public:
    NoticeBoard();
    void setText(string);
    void setDate(Date d=Date());
    void setLike(string);
    void setDislike(string);
    string getText();
    Date getDate();
    void getLike();
    void getDislike();
    void searchpost(int);
    void savepost();
    void printall();
    int printpart(int);
    bool pickupfromFile(string);
    void printFile(string);
private:

    newsStruct _post;
    vector<newsStruct> _board;
    int _postnumber;
};

#endif //PROGETTO_NOTICEBOARD_H
