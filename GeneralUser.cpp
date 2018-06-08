#include "GeneralUser.h"

GeneralUser::GeneralUser() {
    _type = 0 ;                            // 1-simple, 2-company, 3-group.
    _id   = 0 ;
}

string GeneralUser::getID() const {
    return _id;
}

Date GeneralUser::getBirth() const {
    return _birth;
}
short GeneralUser::getType() const {
    return _type;
}

bool GeneralUser::setType(const short& type) {
    if (type >= 1 && type <=3 )
        _type = type;
    else return false;

    return true;
}

bool GeneralUser::setBirth(const string &str) {
    return _birth.stringToDate(str);
}

bool GeneralUser::setID(const string &str) {
    if (str.length() <= 20)
        _id = str;
    else return false;

    return true;
}