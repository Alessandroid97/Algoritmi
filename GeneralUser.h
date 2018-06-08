//
// Created by aless on 05/06/2018.
//

#ifndef PROGETTOALGORITMI2018_GENERALUSER_H
#define PROGETTOALGORITMI2018_GENERALUSER_H
#include <iostream>
#include "Date.h"
#include "NoticeBoard.h"
using namespace std;

class GeneralUser {                          //Classe astratta, base per le diverse tipologie di utente.
public:
    GeneralUser();

    virtual string printOnFile() const =0 ;        //Stampa tutte le info di un utente in ordine come formato per file,
                                            //essendo pure virtual necessita l'overloading in tutte le classi derivate
                                            //e non richiede una implementazione qui.
    virtual void printInfo() const =0;            //Stampa le informazioni dell'utente a schermo.

    void setID(string);
    void setBirth(string);                  //Setters.

    string getID() const;                   //Getters.
    Date getBirth() const;
    short getType() const;

    virtual int getNumberRelations(const string&) const =0; //Da definire in ogni diversa tipologia di utente, restituisce il numero
                                                      //del tipo di relazioni specificato come parametro(es: amici, conoscenti, dipendenti,componenti ...).

private:
    short _type;                            // 1-simple, 2-company, 3-group.
    string _id;                             //Identificativo univoco
    Date _birth;                            //Data di nascita dell'utente o di fondazione
    NoticeBoard _showcase;                  //Oggetto bacheca per la gestione delle notizioe dell'utente

};


#endif //PROGETTOALGORITMI2018_GENERALUSER_H
