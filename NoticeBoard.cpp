//
// Created by Nicola on 06/06/2018.
//

#include "NoticeBoard.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Date.h"
using namespace std;

//Il costruttore inizializza un post fittizio ai valori di controllo
NoticeBoard::NoticeBoard()
{
    _post._text="Empty";
    _post._like=0;
    _post._dislike=0;
    _postnumber=0;
}

//Setters
void NoticeBoard::setText(string text)
{
    _post._text=text;
}
void NoticeBoard::setDate(Date date)
{
    _post._date=date;
}
void NoticeBoard::setLike(string id)
{
    _post._userlike[_post._like]=id;
    _post._like++;
}
void NoticeBoard::setDislike(string id)
{
    _post._userdislike[_post._dislike]=id;
    _post._dislike++;
}

//Getters
string NoticeBoard::getText()
{
    return _post._text;
}
Date NoticeBoard::getDate()
{
    return _post._date;
}
void NoticeBoard::getLike()
{
    cout<<"Totale numero di like per questo post: "<<_post._like<<"\nUtenti che hanno messo mi piace:"<<endl;
    for (int i=0;i<_post._like;i++)
    {
        cout<<_post._userlike[i]<<endl;
    }
}
void NoticeBoard::getDislike()
{
    cout<<"Totale numero di dislike per questo post: "<<_post._dislike<<"\nUtenti che hanno messo non mi piace:"<<endl;
    for(int i=0;i<_post._dislike;i++)
    {
        cout<<_post._userdislike[i]<<endl;
    }
}

//Interazione like degli utenti verso un post selezionato
bool NoticeBoard::insertremoveLike(const string id,const int n,const int c)
{
    bool k=false;
    if(c==1)                       //Se c=1 allora inserisco un like
    {
        for (long i = 0; i < _board[n]._dislike; i++) //Constrollo se l'utente aveva messo dislike
        {                                             //al post selezionato
            if (_board[n]._userdislike[i] == id)
            {
                _board[n]._userdislike[i].erase();
                _board[n]._dislike--;
            }
        }
        for (long i = 0; i < _board[n]._like; i++)    //Controllo se l'utente aveva messo like
        {                                             //al post selezionato
            if (_board[n]._userlike[i] == id)
            {
                k=true;
            }
        }
        if(!k)                                        //Se k falso aggiungo il like
        {
            _board[n]._like++;
            _board[n]._userlike.push_back(id);
            cout<<"Mi piace aggiunto con successo"<<endl;
            return true;
        }
        else                                          //Altrimenti segnalo la presenza
        {
            cerr<<"Hai già messo mi piace a questo post"<<endl;
            return false;
        }
    }
    else if(c==2)                    //Se c=2 elimino un like
    {
        for (long i = 0; i < _board[n]._like; i++)                //Controllo dove potrebbe essere
        {                                                         //il like
            if (_board[n]._userlike[i] == id) {
                _board[n]._userlike[i].erase();
                _board[n]._like--;
                i = _board[n]._like + 1;
                k = true;
            }
        }
        if (k)
        {
            cout << "Mi piace rimosso con successo" << endl;
            return true;
        } else {
            cerr << "L'utente selezionato non ha il tuo mi piace" << endl;
            return false;
        }
    }
    else
    {
        cerr<<"Errore: comando non riconosciuto"<<endl;
        return false;
    }
}

//Interazione dislike degli utenti verso un post selezionato
bool NoticeBoard::insertremoveDislike(const string id,const int n,const int c)
{
    bool k=false;
    if(c==1)                    //Se c=1 Aggiungo dislike
    {
        for (long i = 0; i < _board[n]._like; i++)
        {
            if (_board[n]._userlike[i] == id)
            {
                _board[n]._userlike[i].erase();
                _board[n]._like--;
            }
        }
        for (long i = 0; i < _board[n]._dislike; i++)
        {
            if (_board[n]._userdislike[i] == id)
            {
                k=true;
            }
        }
        if(k)
        {
            _board[n]._dislike++;
            _board[n]._userdislike.push_back(id);
            cout<<"Non mi piace aggiunto con successo"<<endl;
            return true;
        }
        else
        {
            cerr<<"Hai già messo non mi piace a questo post"<<endl;
            return false;
        }
    }
    else if(c==2)                           //Se c=2 rimuovo il dislike
    {
        for (long i = 0; i < _board[n]._dislike; i++) {
            if (_board[n]._userdislike[i] == id) {
                _board[n]._userdislike[i].erase();
                _board[n]._dislike--;
                i = _board[n]._dislike + 1;
                k = true;
            }
        }
        if (k) {
            cout << "Mi piace rimosso con successo" << endl;
            return true;
        } else {
            cerr << "L'utente selezionato non ha il tuo mi piace" << endl;
            return false;
        }
    }
}
//Salvo il post sotto lavorazione e resetto post per uno nuovo;
bool NoticeBoard::savepost()
{
    NoticeBoard post;
    if(_post._text!="Empty")
    {
        _board.insert(_board.begin(), _post);
        _postnumber++;
        _post=post._post;
        return true;
    } else
    {
        cerr<<"Post non valido, impossibile salvare"<<endl;
        _post=post._post;
        return false;
    }
}
//Creazione nuovo post
bool NoticeBoard::insertPost(const string id,const string text)
{
    _post._id=id;
    _post._text=text;
    _post._date=Date();
    if(savepost())
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool NoticeBoard::modifypost(const string id,const string text, postStruct &post)
{
     if(post._id==id)
     {
         post._text=text;
         return true;
     } else
     {
         return false;
     }
}
//Cerca e seleziona post
postStruct NoticeBoard::searchpost(int i)
{
    i--;
    if(i<=_postnumber) {
        cout<<"Post selezionato correttamente"<<endl;
        return _board[i];
    } else
    {
        cerr<<"Numero post inserito non valido"<<endl;
    }
}


int NoticeBoard::printpart(int j)
{
    int i;
    for(i=j;i<j+5;i++)
    {
        cout<<"("<<i+1<<") "<<_post._id<<
            "\n"<<_post._text<<"\nPubblicato in data: "<<
            _post._date.str()<<"\nLike: "<<
            _post._like<<"\nDislike: "<<_post._dislike<<endl;
    }
    return i;
}


void NoticeBoard::printall()
{
    for(int i=0;i<_postnumber;i++)
    {
        cout<<"("<<i+1<<") "<<_post._id<<
            "\n"<<_post._text<<"\nPubblicato in data: "<<
            _post._date.str()<<"\nLike: "<<
            _post._like<<"\nDislike: "<<_post._dislike<<endl;
    }
}

//Carico bacheca da file
bool NoticeBoard::pickupfromFile(string filename)
{
    ifstream file(filename);                      //Apro il file
    if(file.is_open())                            //Controllo che sia aperto
    {
        string text;
        int i=0,v=0;
        char c;
        while(!file.eof())                        //Lo leggo
        {
            file>>c;
            if(c!=','&&i<=100)                    //Controllo virgole e caratteri di lunghezza massima
            {
                text[i]=c;
                i++;
            }
            else if(i>100)
            {
                cerr<<"Numero caratteri superato, impossibile caricare il file"<<endl;
                return false;
            }
            else
            {
                if(v==0)                    //Utilizzo v come contatore per i campi del file
                {                           //v=0 per id,1 per testo,2 per data,3 like,4 dislike
                    _post._id=text;
                    text.erase();
                    i=0;
                    v++;
                }
                else if(v==1)
                {
                    _post._text=text;
                    text.erase();
                    i=0;
                    v++;
                }
                else if(v==2)
                {
                    _post._date.stringToDate(text);
                    text.erase();
                    i=0;
                    v++;
                }
                else if(v==3)
                {
                    text.erase();
                    for(int j=0;j<=5;j++)
                    {
                        file>>text[j];
                        if(text!="like:{")
                        {
                            return false;
                        }
                    }
                    text.erase();
                    i=0;
                    while(c!='}')
                    {
                        file>>c;
                        if(c!=',')
                        {
                            text[i]=c;
                            i++;
                        }
                        else
                        {
                            _post._userlike.push_back(text);
                            text.erase();
                            i=0;
                        }
                    }
                    if(c=='}')
                    {
                        _post._like=_post._userlike.size();
                        v++;
                    }
                }
                else if(v==4)
                {
                    for(int j=0;j<8;j++)
                    {
                        file>>text[j];
                    }
                    if(text!="dislike:{")
                    {
                        return false;
                    }
                    text.erase();
                    i=0;
                    while(c!='}') {
                        file >> c;
                        if (c != ',') {
                            text[i] = c;
                            i++;
                        } else {
                            _post._userdislike.push_back(text);
                        }
                    }
                    if(c=='}')
                    {
                        _post._dislike=_post._userdislike.size();
                        v=0;
                        i=0;
                        _board.insert(_board.begin(),_post);
                    }
                }
            }
        }
        file.close();
        cout<<"Database bacheca caricato con successo"<<endl;
        return true;
    }
    else
    {
        cerr<<"Errore nell'apertura del file"<<endl;
        return false;
    }
}

//Stampo su file
void NoticeBoard::printFile(string filename)
{
    ofstream file(filename);
    if(file.is_open())
    {
        for (int i=0;i<_postnumber;i++)
        {
            file<<_board[i]._id<<","<<_board[i]._text<<","<<_board[i]._date.str()<<",Like:{";
            for(int j=0;j<_board[i]._like;j++)
            {
                if(j!=_board[i]._like-1)
                {
                    file << _board[i]._userlike[j] << ",";
                } else
                {
                    file<<_board[i]._userlike[j]<<"},Dislike:{";
                }
            }
            for(int j=0;j<_board[i]._dislike;j++)
            {
                if(j!=_board[i]._dislike-1)
                {
                    file << _board[i]._userdislike[j] << ",";
                } else
                {
                    file<<_board[i]._userdislike[j]<<"}";
                }
            }
        }
        file.close();
    }
    else
    {
        cerr<<"Errore nella stampa del file"<<endl;
    }
}

