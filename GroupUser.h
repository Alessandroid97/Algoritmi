//
// Created by aless on 05/06/2018.
//

#ifndef PROGETTOALGORITMI2018_GROUPUSER_H
#define PROGETTOALGORITMI2018_GROUPUSER_H


#include "GeneralUser.h"

class GroupUser: public GeneralUser {
public:
    GroupUser();

    virtual void printInfo() const;                 //Funzioni virtuali, overloading delle pure virtual nella classe base.
    virtual string printOnFile() const;

    void setRegisteredOffice(string);               //Setters delle variabili.
    void setActivityKind(string);
    void increaseMemberNumber();

    int getMemberNumber() const;                    //Getters delle variabili.
    string getRegisteredOffice() const;
    string getActivityKind() const;

private:
    int _member_number;                             //Numero di membri del gruppo.

    string _registered_office;                      //Sede legale del gruppo.
    string _activity_Kind;                          //Tipo di attività.
};


#endif //PROGETTOALGORITMI2018_GROUPUSER_H
