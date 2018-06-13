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
                if(_relations[to][j].ptr->getID()==fromID){
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
    return nullptr;
}

long Graph::getPosUser(const string &objID) const {
    for (unsigned long s = 0; s < _users_vector.size(); s++) {
        if (_users_vector[s]->getID() == objID) {
            return s;
        }
    }
    return -1;
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

void Graph::searchGenealogicalTree(const string & rootID) {
    long n=getPosUser(rootID);                                                    //Assegno ad n la posizione (indice del vector) dell'utente da cui partire per l'albero
    long s_pos;
    if(n>-1){
        _color.resize(_users_vector.size());                                      //Preparo il vector di controllo colori e la queue.
        fill(_color.begin(), _color.end(), 'W');
        _color[n]='G';
        _Q.push(n);

        while(!_Q.empty()){                                                       //Inizio a visitare i nodi(utenti) presenti nella queue.
            n=_Q.front();
            _Q.pop();
            _pos_user_tree.push_back(n);                                          //Inserisco l'indice dell'utente che visito nel vector degli utenti per l'albero
            _sons_tree.resize(_sons_tree.size()+1);                               //e incremento di 1 la dimensione del vector di vector per i figli.

            for(long v=0; v<_relations[n].size(); v++){                           //Visito tutti i figli dell'utente.
                if(_relations[n][v].link == "figlio"){
                    s_pos=getPosUser(_relations[n][v].ptr->getID());
                    if(_color[s_pos]=='W'){
                        _color[s_pos]='G';
                        _sons_tree[_sons_tree.size()-1].push_back(s_pos);         //Inserisco la posizione del figlio nel vector di figli relativo all'utente.
                        _Q.push(s_pos);                                           //Inserisco il figlio dell'utente nella queue.
                    }
                }
            }
            _color[n] = 'B';
        }
    }
}



