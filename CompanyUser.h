// Created by Nicola on 05/06/2018.


#ifndef COMPANY_H
#define COMPANY_H

#include <iostream>
#include <string>
#include "Date.h"
#include "GeneralUser.h"

using namespace std;

class CompanyUser:public GeneralUser {
public:
    CompanyUser();

    //Setters
    bool setTaxOffice(string);
    bool setOperationalHeadquarters(string);
    bool setProductType(string);
    void setIncrementSubsidiaries();
    void setIncrementEmployee();

    //Getters
    string getTaxOfficeAdress() const;
    string getOperationaHeadquartersAdress() const;
    string getProductType() const;
    int getSubsidiaries() const;
    int getEmployee() const;

    //Virtual
    virtual int getNumberRelations(const string&) const;
    virtual string printOnFile() const;
    virtual void printInfo() const;
    virtual bool setInformations(const string&, const string&);

private:
    string _tax_office_adress;
    string _operational_headquarters_adress;
    string _product_type;
    int _number_of_subsidiaries;
    int _number_of_employee;
};


#endif //PROGETTO_COMPANY_H
