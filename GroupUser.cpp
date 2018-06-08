// Created by aless on 05/06/2018.

#include "GroupUser.h"

GroupUser::GroupUser() {
    _member_number=0;
}

int GroupUser::getMemberNumber() const {
    return _member_number;
}

string GroupUser::getRegisteredOffice() const {
    return _registered_office;
}

string GroupUser::getActivityKind() const {
    return _activity_Kind;
}

void GroupUser::increaseMemberNumber() {
    _member_number++;
}

void GroupUser::setActivityKind(string str) {   //Si potrebbe usare una #define N 30 ma genera warning
    if(str.size()>30){
        cout<<endl<<"Numero massimo di caratteri superato, inserimento annullato. Rieffettuare l'operazione.";
    }else{
        _activity_Kind=str;
    }
}

void GroupUser::setRegisteredOffice(string str) {   //Si potrebbe usare una #define N 30 ma genera warning
    if(str.size()>30){
        cout<<endl<<"Numero massimo di caratteri superato, inserimento annullato. Rieffettuare l'operazione.";
    }else{
        _registered_office=str;
    }
}

void GroupUser::printInfo() const {
    cout<<endl<<"Nome gruppo: "<<getID()
        <<endl<<"Data fondazione: "<<getBirth().str()
        <<endl<<"Sede legale: "<<getRegisteredOffice()
        <<endl<<"Tipologia di attività: "<<getActivityKind()
        <<endl<<"Numero di membri: "<<getMemberNumber();
}

string GroupUser::printOnFile() const {
    return getID() + ",gruppo,{data_fondazione:" + getBirth().str() + ",sede_legale:" + getRegisteredOffice()
            + ",tipo_attività:" + getActivityKind() + "}";
}

int GroupUser::getNumberRelations(const string &type) const {
    if(type == "membri") return _member_number;
    else return -1;
}




