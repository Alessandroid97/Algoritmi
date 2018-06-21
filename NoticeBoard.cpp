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
bool NoticeBoard::setText(string text)
{
    if(text.length()<100) {
        _post._text = text;
        return true;
    } else
    {
        return false;
    }
}
void NoticeBoard::setDate(Date date)
{
    _post._date=date;
}
bool NoticeBoard::setLike(string id)
{
    if(id.length()<30) {
        _post._userlike[_post._like] = id;
        _post._like++;
        return true;
    } else
    {
        return false;
    }
}
bool NoticeBoard::setDislike(string id)
{
    if(id.length()<30) {
        _post._userdislike[_post._dislike] = id;
        _post._dislike++;
        return true;
    } else
    {
        return false;
    }
}
bool NoticeBoard::setID(const string id)
{
    if(id.length()<30)
    {
        _post._id=id;
        return true;
    } else
    {
        return false;
    }
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
    return savepost();
}
bool NoticeBoard::deletePost(int i,string id)
{
    if(_board[i]._id==id)
    {
        delete _board[i];
        order();
        return true;
    }
    return false;
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
bool NoticeBoard::pickupfromFile(string filename,Graph &graph)
{
    string id,text,like,dislike,line;
    Date date;
    GeneralUser *ptr;
    size_t to,from;
    short control=0;
    ifstream file(filename);                    //Apro il file
    if(file.is_open())                          //Controllo se il file è aperto
    {
        while(getline(file,line))
        {
            to=from=0;
            to=line.find(',',from);
            id=line.substr(from,to-from);
            ptr=graph.getUser(id);              //Utilizzo grafo (dove sono contenuti
                                                // gli oggetti utente) per controllare se l'utente del post
                                                //esiste
            if(ptr== nullptr)
            {
                return false;
            }
            to=line.find('{',from);
            to-=6;
            from=to-10;
            date.stringToDate(line.substr(from,to-from));
            to=from-1;
            from=0;
            from=line.find(',',from);
            text=line.substr(from+1,to-from+1);
            from=to+18;
            while(control!=1)
            {
                to=line.find_first_of(",}",from);
                if(line[to]==',')
                {
                    if(setLike(line.substr(from,to-from))) {
                        from = to + 1;
                    } else
                    {
                        return false;
                    }
                }
                else if(line[to]=='}')
                {
                    control=1;
                }
            }
            control=0;
            from=to+11;
            while(control!=1)
            {
                to=line.find_first_of(",}",from);
                if(line[to]==',')
                {
                    if(setDislike(line.substr(from,to-from))) {
                        from = to + 1;
                    }
                    else
                    {
                        return false;
                    }
                }
                else if(line[to]=='}')
                {
                    control=1;
                }
            }
            if(setID(id)&&setText(text))
            {
                savepost();
                ptr->setPrivatePost(&_board[0]);         //Utilizzo il puntatore salvato per richiamare
                                                         //la funzione nella classe general user
                                                         //per puntare i post che appartengono agli utenti
            } else
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }
    file.close();
    return true;
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

void NoticeBoard::order()
{
    postStruct p;
    int k;
    for(int i=0; i<_postnumber-1; i++)
    {
        k=i;
        for(int j=i+1; j<_postnumber; j++)
            if(_board[j]._date.yearsFrom() > _board[k]._date.yearsFrom())
            {
                k=j;
            }
        p=_board[k];
        _board[k]=_board[i];
        _board[i]=p;
    }
}

void NoticeBoard::printNicest()
{
    long like=0;
    int position=0;
    for(int i=0;i<_postnumber;i++)
    {
        if(_board[i]._like>like)
        {
            like=_board[i]._like;
            position=i;
        }
    }
    cout<<_board[position]._id<<"\n"<<_board[position]._text<<"\n"<<_board[position]._date.str()
        <<"\nLike: "<<_board[position]._like<<"  Dislike: "<<_board[position]._dislike<<endl;
}

void NoticeBoard::printWorst()
{
    long dislike=0;
    int position=0;
    for(int i=0;i<_postnumber;i++)
    {
        if(_board[i]._dislike>dislike)
        {
            dislike=_board[i]._dislike;
            position=i;
        }
    }
    cout<<_board[position]._id<<"\n"<<_board[position]._text<<"\n"<<_board[position]._date.str()
        <<"\nLike: "<<_board[position]._like<<"  Dislike: "<<_board[position]._dislike<<endl;
}

void NoticeBoard::searchPostbyDate(string date)
{
    Date data;
    data.stringToDate(date);
    cout<<"Selezionare il post dalla sezione dedicata con il numero che gli è stato assegnato"<<endl;
    for(int i=0;i<_postnumber;i++)
    {
        if(data.yearsFrom()==_board[i]._date.yearsFrom())
        {
            cout<<"\n("<<i+1<<")"<<"\n"<<_board[i]._id<<"\n"<<_board[i]._text<<"\n"<<_board[i]._date.str()
                <<"\nLike: "<<_board[i]._like<<" Dislike: "<<_board[i]._dislike<<endl;
        }
    }
}