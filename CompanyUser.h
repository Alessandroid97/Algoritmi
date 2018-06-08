//
// Created by Nicola on 05/06/2018.
//

#ifndef PROGETTO_COMPANY_H
#define PROGETTO_COMPANY_H

#include <iostream>
#include <string>
#include "Date.h"
#include "GeneralUser.h"

using namespace std;

class CompanyUser:public GeneralUser {
public:
                                            /*Costruttore*/
    CompanyUser();
                                            /*Setters*/
    void setTaxOffice(string);
    void setOperationalHeadquarters(string);
    void setProductType(string);
    void setIncrementSubsidiaries();
    void setIncrementEmployee();

                                                 /*Getters*/
    string getTaxOfficeAdress() const;
    string getOperationaHeadquartersAdress() const;
    string getProductType() const;
    int getSubsidiaries() const;
    int getEmployee() const;
    virtual int getNumberRelations(const string&) const;

    virtual string printOnFile() const;

    private:
    string _tax_office_adress;
    string _operational_headquarters_adress;
    string _product_type;
    int _number_of_subsidiaries;
    int _number_of_employee;
};


#endif //PROGETTO_COMPANY_H