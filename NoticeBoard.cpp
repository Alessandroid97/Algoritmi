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

NoticeBoard::NoticeBoard()
{
    _post._text="Empty";
    _post._like=0;
    _post._dislike=0;
    _postnumber=0;
}
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
void NoticeBoard::savepost()
{
    _board.insert(_board.begin(),_post);
    _postnumber++;
}
void NoticeBoard::searchpost(int i)
{
    i--;
    if(i<=_postnumber) {
        _post = _board[i];
        cout<<"Post selezionato correttamente"<<endl;
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
bool NoticeBoard::pickupfromFile(string filename)
{
    ifstream file(filename);
    if(file.is_open())
    {
        string text;
        Date date;
        int i=0,v=0,like=0,dislike=0;
        char c;
        while(!file.eof())
        {
            file>>c;
            if(c!=','&&i<=100)
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
                if(v==0)
                {
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
                    //_post._date.funzione(text);
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