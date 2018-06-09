//
// Created by aless on 05/06/2018.
//

#include "Graph.h"
#include <fstream>
#define S 1
#define A 2
#define G 3

Graph::Graph() {
        _users_vector.resize(1);
        _relations.resize(1);
        _empty_rel.ptr=_temporary_rel.ptr= nullptr;
        _n_company=_n_group=_n_simple=0;
}

bool Graph::readFileRelations(const string name_file) {
    string id1, id2, relation, line;
    size_t from, to;

    ifstream file;
    file.open(name_file);

    if(!file.is_open()){
        return false;
    }else{
        while(getline(file, line)){
            from=to=0;
            to=line.find(',', from);
            id1=line.substr(from, to-from);
            from=to+1;
            to=line.find(',', from);
            id2=line.substr(from, to-from);
            from=to+1;
            relation=line.substr(from, line.size()-from);
            if(setRelation(id1, id2, relation)){
            }
            else {
                return false;
            }
        }
        return true;
    }
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

void Graph::removeUser(const string & userID) {
    for (unsigned long s = 0; s < _users_vector.size(); s++) {
        if (_users_vector[s]->getID() == userID) {
            if(_users_vector[s]->getType()==S) _n_simple--;
            else if(_users_vector[s]->getType()==A) _n_company--;
            else if(_users_vector[s]->getType()==G) _n_group--;

            delete _users_vector[s];
             _users_vector.erase(_users_vector.begin()+s);
             _relations.erase(_relations.begin()+s);
        }
    }
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
                    if (rel == "coniuge" || rel == "amico") {
                        invertRelation(from, to, rel, rel);
                        return true;
                    } else{
                        if(rel == "conoscente" || rel == "membro" || rel == "dipendente"){
                            _temporary_rel.link = rel;
                            _temporary_rel.ptr = _users_vector[to];
                            _relations[from].insert(_relations[from].begin(), _temporary_rel);
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool Graph::removeRelation(const string &fromID, const string &toID) {
    long from = -1, to = -1;
    for (unsigned long s = 0; s < _users_vector.size(); s++) {
        if (_users_vector[s]->getID() == fromID) {
            from = s;
        }
        if (_users_vector[s]->getID() == toID) {
            to = s;
        }
    }
    for(int r=0; r<_relations[from].size(); r++){
        if(_relations[from][r].ptr->getID()==toID){
            _relations[from].erase(_relations[from].begin()+r);
            for(int j=0; j<_relations[to].size(); j++){
                if(_relations[to][j].ptr->getID()==toID){
                    _relations[to].erase(_relations[to].begin()+j);
                    return true;
                }
            }
        }
    }
    return false;
}


void Graph::invertRelation(const long &from , const long &to, const string &rel, const string &inv_rel) {
    _temporary_rel.link = rel;
    _temporary_rel.ptr = _users_vector[to];
    _relations[from].insert(_relations[from].begin(), _temporary_rel);
    _temporary_rel.ptr = _users_vector[from];
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

float Graph::averageAgeSimpleUsers() const {
    float total=0;
    for (unsigned long s = 0; s < _users_vector.size(); s++){
        if(_users_vector[s]->getType()==S){
            total+=_users_vector[s]->getBirth().yearsFrom();
        }
    }
    return total/_n_simple;
}

string Graph::userMoreRelations(const short& type_user, const string& type) const {
    int max=0;
    string user_max;
    for (unsigned long s = 0; s < _users_vector.size(); s++) {
        if (_users_vector[s]->getType()==type_user) {
            if(_users_vector[s]->getNumberRelations(type)>max){
                max=_users_vector[s]->getNumberRelations(type);
                user_max=_users_vector[s]->getID();
            }else{
                if(_users_vector[s]->getNumberRelations(type)==max){
                    user_max += ", " + _users_vector[s]->getID();
                }
            }
        }
    }
    return user_max;
}



