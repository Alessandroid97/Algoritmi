//
// Created by aless on 05/06/2018.
//

#ifndef PROGETTOALGORITMI2018_GRAPH_H
#define PROGETTOALGORITMI2018_GRAPH_H


#include <iostream>
#include <vector>
#include <queue>
#include "Date.h"
#include "GroupUser.h"

#define S 1
#define A 2
#define G 3

using namespace std;
typedef struct sympathystruct{
    string name;
    float rate;
}sympathystruct;
typedef struct relationsStruct{
    GeneralUser *ptr;                   //SOLO UNA PRIMA IDEA - Puntatore a un puntatore, punta al puntatore del
                                         //vector _users_vector che a sua volta punta all'oggetto.
    string link;                         //Indica il tipo di relazione.
}relationsStruct;

class Graph {
public:
    Graph() ;

    bool readFileRelations(const string);

    template <typename T>                           //T indica il tipo di uno dei 3 possibili utenti.
    void setUser(T&);                               //Aggiunge al vector l'oggetto passato come parametro.

    void removeUser(const string&);                 //Rimuove un utente dal vector _users_vector (l'ID è passato da parametro)

    bool setRelation(string&, string&, string&);     //Aggiunge la relazione fra 2 oggetti , vengono passati come parametri
                                                     //gli identificativi univoci dei 2 oggetti interessati e il tipo di relazione.
    bool removeRelation(const string&, const string&);     //Rimuove la relazione fra 2 utenti.

    GeneralUser* getUser(const string&) const;              //Restituisce l'oggetto relativo all'identificativo passato come parametro.
    long getPosUser(const string&) const;                   //Restituisce la posizione(indice del vector) dell'oggetto;

    void searchGenealogicalTree(const string&);

    long numberOfUsers(const string&) const;               //Restituisce il numero totale degli utenti del tipo specificato
                                                     //come parametro("tutti","semplice","azienda","gruppo").
    unsigned long nUsersAfterDate(const Date&) const;               //Restituisce il numero di utenti nati dopo una certa data passata come parametro.

    string userMoreRelations(const short&, const string&) const;           //Stampa l'utente con il maggior numero di relazioni(spec. da parametro)
                                                             //il tipo dell'utente è mandato come parametro(1-2-3).
    float averageAgeSimpleUsers() const;            //Restituisce l'età media degli utenti semplici.

    bool searchLoneWolf(int, int, short, bool);    //Parametri per la ricerca, in ordine: soglia num relazioni, soglia num news, appartenenza gruppi, dipendente azienda.

    bool searchSympathy(const int, bool);
private:

    void invertRelation(vector < vector <relationsStruct> >& ,const long&,const long&,const string&,const string&);


    vector < GeneralUser* > _users_vector;          //Vector di puntatori della classe base, ai quali è possibile associare ognuno dei 3 tipi
                                                    //di utenti , così da poter contenere ogni oggetto utente in un solo vector e gestire gli
                                                    //utenti utilizzando i puntatori(polimorfismo).

    vector < vector <relationsStruct> > _relations; //Vector di vector per la gestione delle relazioni fra utenti,
                                                    //al vector esterno è associato un iteratore per scorrere il vettore (ogni indice di casella corrisponde ad un utente)
                                                    //mentre il vettore interno conterrà struct contenenti a loro volta la relazione e puntatore all'utente
                                                    //verso cui si esprime la relazione.

    vector < long > _pos_user_tree;                 //Vector delle posizioni(indici del vector) dei componenti dell'albero genealogico.
    vector < vector <relationsStruct> >_relations_tree;           //Vector di vector per le posizioni dei figli dei componenti dell'albero genealogico.
    queue <long> _Q;
    vector<char> _color;
    //vector<int> _levels;

    vector <long> _searchList;             //Può essere sostituito dal vector _pos_user_tree già esistente.

    relationsStruct _empty_rel;
    relationsStruct _temporary_rel;

    unsigned long _n_simple, _n_company, _n_group;
};


template<typename T>
void Graph::setUser(T &obj) {
    _users_vector.push_back(new T);                                                              //Aggiungo un puntatore in coda al vector degli utenti e ci associo un utente di tipo T
    *_users_vector[_users_vector.size()-1] = obj;                                                //che successivamente eguaglio all'utente passato come parametro.

    _relations.resize(_relations.size()+1);
    _relations[_relations.size()-1].insert(_relations[_relations.size()-1].begin(), _empty_rel); //Aggiungo in testa al vector relazioni una struct relazioni vuota.
    if(obj.getType()==S) _n_simple++;
    else if(obj.getType()==A) _n_company++;                                                      //Incremento il contatore del tipo utente interessato.
    else if(obj.getType()==G) _n_group++;
}

#endif //PROGETTOALGORITMI2018_GRAPH_H
