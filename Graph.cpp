//
// Created by aless on 05/06/2018.
//

#include "Graph.h"
#define S 1
#define A 2
#define G 3

Graph::Graph() {
        _users_vector.resize(1);
        _relations.resize(1);
        _empty_rel.ptr=_temporary_rel.ptr= nullptr;
        _n_company=_n_group=_n_simple=0;
}

template<typename T>
void Graph::setUser(T &obj) {
    _users_vector.insert(_users_vector.begin(), new T);      //Aggiungo un puntatore in testa al vector degli utenti e ci associo un utente di tipo T
    _users_vector[0] = obj;                                  //che successivamente eguaglio all'utente passato come parametro.
    _relations[0].insert(_relations[0].begin(), _empty_rel); //Aggiungo in testa al vector relazioni una struct relazioni vuota.
    if(obj.getType()==S) _n_simple++;
    else if(obj.getType()==A) _n_company++;                  //Incremento il contatore del tipo utente interessato.
         else if(obj.getType()==G) _n_group++;
}

bool Graph::setRelation(string & fromID, string &toID, string &rel) {
    long from=-1, to=-1;
    string inv_rel;
    for(unsigned long s=0; s<_users_vector.size(); s++) {
        if (_users_vector[s]->getID() == fromID) {                    //I primi 2 if trovano l'indice dei due utenti.
            from = s;
        }
        if (_users_vector[s]->getID() == toID) {
            to = s;
        }
        if (from > -1 && to > -1 && from!=to) {
            if (rel == "figlio") {
                inv_rel="genitore";
                invertRelation(from, to, rel, inv_rel);
                return true;
            } else {
                if (rel == "genitore") {
                    inv_rel="figlio";
                    invertRelation(from, to, rel, inv_rel );
                    return true;
                } else {
                    if (rel == "coniuge" || rel == "amico" || rel == "conoscente") {
                        invertRelation(from, to, rel, rel);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void Graph::invertRelation(const long &from , const long &to, const string &rel, const string &inv_rel) {
    _temporary_rel.link = rel;
    *_temporary_rel.ptr = _users_vector[to];
    _relations[from].insert(_relations[from].begin(), _temporary_rel);
    *_temporary_rel.ptr = _users_vector[from];
    _temporary_rel.link = inv_rel;
    _relations[to].insert(_relations[to].begin(), _temporary_rel);
}

GeneralUser *Graph::getUser(const string& objID) const {
    for (unsigned long s = 0; s < _users_vector.size(); s++) {
        if (_users_vector[s]->getID() == objID) {
            return _users_vector[s];
        }
    }
}

long Graph::numberOfUsers(const string &type) const {
    if (type == "tutti") {
        return _users_vector.size();
    }
    if (type == "semplice") {
        return _n_simple;
    }
    if (type == "azienda") {
        return _n_company;
    }
    if (type == "gruppo") {
        return _n_group;
    }
    return -1;
}

unsigned long Graph::nUsersAfterDate(const Date& date1) const {
    unsigned long num=0;
    for (unsigned long s = 0; s < _users_vector.size(); s++) {
        if (_users_vector[s]->getType() == S && _users_vector[s]->getBirth()>date1) {
            num++;
        }
    }
    return num;
}

string Graph::companyMoreEmployees(const string &type) const {
    int max=0;
    string company_max;
    for (unsigned long s = 0; s < _users_vector.size(); s++) {
        if (_users_vector[s]->getType()==A) {
            if(_users_vector[s]->getNumberRelations(type)>max){
                max=_users_vector[s]->getNumberRelations(type);
                company_max=_users_vector[s]->getID();
            }else{
                if(_users_vector[s]->getNumberRelations(type)==max){
                    company_max += ", " + _users_vector[s]->getID();
                }
            }
        }
    }
    return "L' azienda/e con il maggior numero di dipendenti("
           + type + ") è/sono: " + company_max + ".";
}

float Graph::averageAgeSimpleUsers() const {
    float total=0;
    for (unsigned long s = 0; s < _users_vector.size(); s++){
        if(_users_vector[s]->getType()==S){
            total+=_users_vector[s]->getBirth().yearsFrom();
        }
    }
    return total/_n_simple;
}
