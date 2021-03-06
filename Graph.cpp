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
            if(setRelation(id1, id2, relation)) {
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
                invertRelation(_relations, from, to, rel, inv_rel);
                return true;
            } else {
                if (rel == "genitore") {
                    inv_rel="figlio";
                    invertRelation(_relations ,from, to, rel, inv_rel );
                    return true;
                } else {
                    if (rel == "coniuge" || rel == "amico" || rel == "dipendente" || rel == "membro") {
                        invertRelation(_relations ,from, to, rel, rel);
                        return true;
                    } else{
                        if(rel == "conoscente" || rel == "consociata"){
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


void Graph::invertRelation(vector < vector <relationsStruct> > &Rvector, const long &from , const long &to, const string &rel, const string &inv_rel) {
    _temporary_rel.link = rel;
    _temporary_rel.ptr = _users_vector[to];
    Rvector[from].insert(Rvector[from].begin(), _temporary_rel);
    _temporary_rel.ptr = _users_vector[from];
    _temporary_rel.link = inv_rel;
    Rvector[to].insert(Rvector[to].begin(), _temporary_rel);
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
            _relations_tree.resize(_relations_tree.size()+1);                               //e incremento di 1 la dimensione del vector di vector per i parenti.

            for(long v=0; v<_relations[n].size(); v++){                           //Visito tutti i parenti dell'utente.
                if(_relations[n][v].link == "figlio"){
                    s_pos=getPosUser(_relations[n][v].ptr->getID());
                    if(_color[s_pos]=='W'){
                        _color[s_pos]='G';
                        invertRelation(_relations_tree, _relations_tree.size()-1, s_pos, "figlio", "genitore");         //Inserisco le relazioni nel vector _relations_tree.
                        _Q.push(s_pos);                                                                                 //Inserisco il figlio dell'utente nella queue.
                    }
                }else{
                    if(_relations[n][v].link == "genitore") {
                        s_pos = getPosUser(_relations[n][v].ptr->getID());
                        if (_color[s_pos] == 'W') {
                            _color[s_pos] = 'G';
                            invertRelation(_relations_tree, _relations_tree.size() - 1, s_pos, "genitore", "figlio");         //Inserisco le relazioni nel vector _relations_tree.
                            _Q.push(s_pos);                                                                                   //Inserisco il genirote dell'utente nella queue.
                        }
                    }
                }
            }
            _color[n] = 'B';
        }
    }else{
        cerr<<"\r\nErrore, utente non trovato.";
    }
}

bool Graph::searchLoneWolf(const int rel, const int news, const short group, bool employee) {
    _searchList.clear();
    short check;
    for (unsigned long s = 0; s < _users_vector.size(); s++) {
        check=0;
        if(_users_vector[s]->getType()==S){
            if(rel>0){
                if(_users_vector[s]->getNumberRelations("tutti")>rel) check = -1 ;
            }
            if(news>0){
                if(_users_vector[s]->getNumberNews()>news) check = -1;
            }
            if(group>0){
                if(_users_vector[s]->getNumberRelations("gruppi")>employee) check = -1;
            }
            if(employee>0){
                if(_users_vector[s]->getNumberRelations("dipendenti")>employee) check = -1;
            }
            if(check==0){
                _searchList.push_back(getPosUser(_users_vector[s]->getID()));
            }
        }
    }
}

bool Graph::searchSympathy(const int rate, bool subs)
{
    vector<postStruct*> post;
    vector<sympathystruct> sympathy;
    sympathystruct company;
    short check;
    for(unsigned long i=0;i<_users_vector.size();i++)
    {
        check=0;
        if(_users_vector[i]->getType()==A) {
            company.name=_users_vector[i]->getID();
            post=_users_vector[i]->getPrivatePost();
            long like=0;
            long dislike=0;
            for(unsigned long j=0;j<post.size();j++)
            {
                like=like+post[j]->_like;
                dislike=dislike+post[j]->_dislike;
            }
            if(dislike!=0&&(like/dislike)>=rate) {
                company.rate=like/dislike;
                sympathy.push_back(company);
            }
            else if(like>rate)
            {
                company.rate=like;
                sympathy.push_back(company);
            }
        }
    }
    if(!sympathy.empty()) {
        sympathystruct s;
        int k;
        for(unsigned int i=0;i<sympathy.size()-1;i++)
        {
            k=i;
            for(int j=i+1; j<sympathy.size(); j++)
                    if(sympathy[i].rate > sympathy[k].rate)
                    {
                        k=j;
                    }
                s=sympathy[k];
                sympathy[k]=sympathy[i];
                sympathy[i]=s;
            }
        }
        else{
        return false;
    }
    for(unsigned int i=0;i<sympathy.size();i++)
    {
        cout<<"["<<i<<"]\n"<<sympathy[i].name<<"\nCon rateo di : "<<sympathy[i].rate<<endl;
    }
    return true;
    }