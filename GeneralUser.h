#ifndef GENERALUSER_H
#define GENERALUSER_H

#include <iostream>
#include "Date.h"
#include "NoticeBoard.h"

using namespace std;

class GeneralUser {                                 //Classe astratta, base per le diverse tipologie di utente.
public:
    GeneralUser();

    virtual string printOnFile() const =0 ;                     //Stampa tutte le info di un utente in ordine come formato per file, pure virtual.
    virtual void printInfo() const =0;                          //Stampa le informazioni dell'utente a schermo. Pure Virtual
    virtual int getNumberRelations(const string&) const =0;     //Da definire in ogni diversa tipologia di utente, restituisce il numero
                                                                //del tipo di relazioni specificato come parametro(es: amici, conoscenti, dipendenti,componenti ...).
    virtual bool setInformations(const string&, const string&) =0;

    bool setID(const string& );
    bool setBirth(const string& );                //Setters.
    bool setType(const short& );
    void setPrivatePost(postStruct*);

    string getID() const;                         //Getters.
    Date getBirth() const;
    short getType() const;

private:
    short _type;                            // 1-simple, 2-company, 3-group.
    string _id;                             //Identificativo univoco
    Date _birth;                            //Data di nascita dell'utente o di fondazione
    NoticeBoard _showcase;                  //Oggetto bacheca per la gestione delle notizioe dell'utente
    vector<postStruct*> _private_post;
};


#endif //GENERALUSER_H
