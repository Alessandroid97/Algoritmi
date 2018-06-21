// Created by Domenico Galdiero on 08/06/18

#include "SimpleUser.h"

void SimpleUser::increaseFriends() {
    _n_friends++;
}
void SimpleUser::increaseKnown() {
    _n_known++;
}
void SimpleUser::increaseRelatives() {
    _n_relatives++;
}
//Getters
string SimpleUser::getSurname() const {
    return _surname;
}
string SimpleUser::getName() const {
    return _name;
}
string SimpleUser::getAddress() const {
    return _address;
}
int SimpleUser::getNFriends() const {
    return _n_friends;
}
int SimpleUser::getNKnown() const {
    return _n_known;
}
int SimpleUser::getNRelatives() const {
    return _n_relatives;
}
bool SimpleUser::getIsEmployed() const {
    return _is_employed;
}

int SimpleUser::getNumberRelations(const string & type) const {
    if(type=="amici") return getNFriends();
    if(type=="conoscenti") return getNKnown();
    if(type=="parenti") return getNRelatives();
    if(type=="gruppi") return _n_groups;
    if(type=="tutti") return getNRelatives() + getNFriends() + getNKnown() + _n_groups;
}
//Setters
bool SimpleUser::setAddress(const string &addr) {
    if (addr.length() <= MAX_STRING)
        _address = addr;
    else return false;

    return true;
}
bool SimpleUser::setName(const string &name) {
    if (name.length() <= MAX_STRING && checkAlpha(name))
        _name = name;
    else return false;

    return true;
}
bool SimpleUser::setSurname(const string &surname) {
    if (surname.length() <= MAX_STRING && checkAlpha(surname))
        _surname = surname;
    else return false;

    return true;
}

//Print
void SimpleUser::printInfo() const {
    cout<<endl<<"Nome utente: "<<getID()
        <<endl<<"Nome: "<<getName()
        <<endl<<"Cognome: "<<getSurname()
        <<endl<<"Data di nascita: " << getBirth().str()
        <<endl<<"Indirizzo di domicilio: " << getAddress();
}

string SimpleUser::printOnFile() const {
    cout<<getID() + "," "utente semplice" + "," + "Nome:" + getName() + "," + "Cognome:" + getSurname()
       + "," + "Data di nascita:" + getBirth().str() + "," + "Indirizzo di domicilio: " + getAddress() <<endl;
}

//Private Methods
bool SimpleUser::checkAlpha(const string & str) {
    for (int i=0; i<str.length(); i++)
    {
        if (!isalpha(str[i])) return false;
    }
    return true;
}

bool SimpleUser::setInformations(const string & info, const string & val) {
    if (info == "nome") {
        return setName(val);
    } else {
        if (info == "cognome") {
            return setSurname(val);
        } else {
            if(info == "residenza"){
                return setAddress(val);
            }
        }
    }
    return false;

}

