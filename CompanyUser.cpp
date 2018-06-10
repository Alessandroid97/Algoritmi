// Created by Nicola on 05/06/2018.

#include "CompanyUser.h"
//Costruttore
CompanyUser::CompanyUser() {
    _number_of_employee=0;
    _number_of_subsidiaries=0;
}
//Setters
bool CompanyUser::setTaxOffice(string adress)
{
    _tax_office_adress=adress;
    return true;
}
bool CompanyUser::setOperationalHeadquarters(string adress)
{
    _operational_headquarters_adress=adress;
    return true;
}
bool CompanyUser::setProductType(string section)
{
    _product_type=section;
    return true;
}
void CompanyUser::setIncrementEmployee()
{
    _number_of_employee++;
}
void CompanyUser::setIncrementSubsidiaries()
{
    _number_of_subsidiaries++;
}
//Getters
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
    else if(type=="diretti") return getEmployee();
         else if(type=="tutti") return getEmployee() + getSubsidiaries();
              else return -1;
}

bool CompanyUser::setInformations(const string & info, const string & val) {
    if (info == "sede legale") {
        return setTaxOffice(val);
    } else {
        if (info == "sede operativa") {
            return setOperationalHeadquarters(val);
        } else {
            if(info == "tipologia prodotti"){
                return setProductType(val);
            }
        }
    }
    return false;
}

void CompanyUser::printInfo() const {
        cout<<endl<<"Nome azienda: "<<getID()
            <<endl<<"Data fondazione: "<<getBirth().str()
            <<endl<<"Sede legale: "<<getTaxOfficeAdress()
            <<endl<<"Sede operativa: "<<getOperationaHeadquartersAdress()
            <<endl<<"Tipologia di prodotti: "<<getProductType();
}
