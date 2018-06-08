// Created by Domenico Galdiero on 08/06/18.


#ifndef SIMPLEUSER_H
#define SIMPLEUSER_H

#include "iostream"
#include "GeneralUser.h"

#define MAX_STRING 30

using namespace std;

class SimpleUser: public GeneralUser
{
public:
    bool setName(const string& name);           //devo controllare il nome, deve essere una stringa letterale di MAX car.
    bool setSurname(const string& surname);
    bool setAddress(const string& address);
    void increaseRelatives();                   //>=0 si devono incrementare
    void increaseFriends();
    void increaseKnown();

    string getName() const;
    string getSurname() const;
    string getAddress() const;
    int getNRelatives() const;
    int getNKnown() const;
    int getNFriends() const;

    virtual int getNumberRelations(const string&) const;
    virtual string printOnFile() const;
    virtual void printInfo() const;

private:
    bool checkAlpha(const string& );

    string _name;
    string _surname;
    string _address;
    int _n_friends;
    int _n_relatives;
    int _n_known;
};


#endif //SIMPLEUSER_H
