//
// Created by aless on 05/06/2018.
//

#ifndef PROGETTOALGORITMI2018_GRAPH_H
#define PROGETTOALGORITMI2018_GRAPH_H


#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "Date.h"
#include "GroupUser.h"

using namespace std;

typedef struct relationsStruct{
    GeneralUser **ptr;                   //SOLO UNA PRIMA IDEA - Puntatore a un puntatore, punta al puntatore del
                                         //vector _users_vector che a sua volta punta all'oggetto.
    string link;                         //Indica il tipo di relazione.
}relationsStruct;

class Graph {
public:
    Graph() ;

    template <typename T>                           //T indica il tipo di uno dei 3 possibili utenti.
    void setUser(T&);                               //Aggiunge al vector l'oggetto passato come parametro.

    bool setRelation(string&, string&, string&);     //Aggiunge la relazione fra 2 oggetti , vengono passati come parametri
                                                     //gli identificativi univoci dei 2 oggetti interessati e il tipo di relazione.

    GeneralUser* getUser(const string&) const;              //Restituisce l'oggetto relativo all'identificativo passato come parametro.

    long numberOfUsers(const string&) const;               //Restituisce il numero totale degli utenti del tipo specificato
                                                     //come parametro("tutti","semplice","azienda","gruppo").
    unsigned long nUsersAfterDate(const Date&) const;               //Restituisce il numero di utenti nati dopo una certa data passata come parametro.
    string companyMoreEmployees(const string&) const;               //Restituisce il nome dell'azienda con maggior numero di dipendenti diretti/totali e il numero
                                                     //in questione. Diretti/totali viene specificato come parametro.
    void userMoreRelations(string) const;                //Stampa l'utente con il maggior numero di amici/conoscenze(spec. da parametro)
                                                    //e il relativo numero.
    float averageAgeSimpleUsers() const;            //Restituisce l'età media degli utenti semplici.

private:

    void invertRelation(const long&,const long&,const string&,const string&);


    vector < GeneralUser* > _users_vector;          //Vector di puntatori della classe base, ai quali è possibile associare ognuno dei 3 tipi
                                                    //di utenti , così da poter contenere ogni oggetto utente in un solo vector e gestire gli
                                                    //utenti utilizzando i puntatori(polimorfismo).

    vector < vector <relationsStruct> > _relations; //Vector di vector per la gestione delle relazioni fra utenti,
                                                    //al vector esterno è associato un iteratore per scorrere il vettore (ogni indice di casella corrisponde ad un utente)
                                                    //mentre il vettore interno conterrà struct contenenti a loro volta la relazione e puntatore all'utente
                                                    //verso cui si esprime la relazione.
    relationsStruct _empty_rel;
    relationsStruct _temporary_rel;
    vector<char> _color;

    unsigned long _n_simple, _n_company, _n_group;
};




#endif //PROGETTOALGORITMI2018_GRAPH_H
