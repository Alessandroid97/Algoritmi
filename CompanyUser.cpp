//
// Created by Nicola on 05/06/2018.
//

#include "CompanyUser.h"
/*Costruttore*/
CompanyUser::CompanyUser() {
    _number_of_employee=0;
    _number_of_subsidiaries=0;
}
/*Setters*/
void CompanyUser::setTaxOffice(string adress)
{
    _tax_office_adress=adress;
}
void CompanyUser::setOperationalHeadquarters(string adress)
{
    _operational_headquarters_adress=adress;
}
void CompanyUser::setProductType(string section)
{
    _product_type=section;
}
void CompanyUser::setIncrementEmployee()
{
    _number_of_employee++;
}
void CompanyUser::setIncrementSubsidiaries()
{
    _number_of_subsidiaries++;
}
/*Getters*/
string CompanyUser::getTaxOfficeAdress() const
{
    return _tax_office_adress;
}
string CompanyUser::getOperationaHeadquartersAdress() const
{
    return _operational_headquarters_adress;
}
string CompanyUser::getProductType() const
{
    return _product_type;
}

int CompanyUser::getEmployee() const
{
    return _number_of_employee;
}
int CompanyUser::getSubsidiaries() const
{
    return _number_of_subsidiaries;
}
string CompanyUser::printOnFile() const   /*Overloading funzione pure virtual della classe generale*/
{
    return getID() + ",Azienda,{indirizzo_sede_fiscale:" + getTaxOfficeAdress()
           + ",indirizzo_sede_operativa:" + getOperationaHeadquartersAdress()
           + ",data_di_fondazione:" + getBirth().str()
           + ",tipologia_attività:" + getProductType() + "}";
}

int CompanyUser::getNumberRelations(const string &type) const {
    if(type=="consociati") return getSubsidiaries();
    if(type=="diretti") return getEmployee();
    if(type=="tutti") return getEmployee() + getSubsidiaries();
}
