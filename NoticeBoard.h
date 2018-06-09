//
// Created by Nicola on 06/06/2018.
//

#ifndef PROGETTO_NOTICEBOARD_H
#define PROGETTO_NOTICEBOARD_H

#include <iostream>
#include <string>
#include <vector>
#include "Date.h"
#include <fstream>
using namespace std;

struct postStruct {
    string _text;
    string _id;
    Date _date;
    long _like;
    vector<string> _userlike;
    long _dislike;
    vector<string> _userdislike;
};

class NoticeBoard
{
public:
    NoticeBoard();                          //Costruttore

    void setText(string);                   //Setter
    void setDate(Date d=Date());
    void setLike(string);
    void setDislike(string);

    string getText();                       //Getter
    Date getDate();
    void getLike();
    void getDislike();

    //Funzione inserisci/rimuovi like per utenti
    bool insertremoveLike(const string ,const int,const int);

    //Funsione inserisci/rimuovi dislike per utenti
    bool insertremoveDislike(const string,const int,const int);

    //Funzione creazione nuovo post
    bool insertPost(const string,const string);

    //Funzione modifica post
    bool modifypost(const string,const string,postStruct&);
    //Cerca e seleziona post per modifiche
    postStruct searchpost(int);

    //Salva post in lavorazione
    bool savepost();

    //Stampa tutta la bacheca
    void printall();

    //Stampa a 5 a 5 la bacheca
    int printpart(int);

    //Carica bacheca da file
    bool pickupfromFile(string);

    //Stampa e salva bacheca su file
    void printFile(string);

private:

    postStruct _post;
    vector<postStruct> _board;
    int _postnumber;
};

#endif //PROGETTO_NOTICEBOARD_H
