#include <iostream>
#include <fstream>
#include "GeneralUser.h"
#include "GroupUser.h"
#include "SimpleUser.h"
#include "CompanyUser.h"
#include "Graph.h"

using namespace std;

int main(int argc, char *argv[])
{
      Graph mainGraph;
      GeneralUser* objPtr=nullptr;
      SimpleUser simple;
      CompanyUser company;
      GroupUser group;

      ifstream fileUsers;
      fileUsers.open(argv[1]);
      if(!fileUsers.is_open()){
          cerr<<"\r\nErrore nell'apertura del file utenti. Il nome del file potrebbe non essere corretto.";
          return -1;
      }else{
          string id1, type, info, val, line;
          size_t from,frominfo, to;
          short control;

          while(getline(fileUsers, line)){
              from=to=0;
              control=0;
              to=line.find(",",from);
              id1=line.substr(from, to-from);
              from=to+1;
              to=line.find(',', from);
              type=line.substr(from, to-from);
              from=to+2;
              frominfo=to+1;

              if(type=="semplice" && line[frominfo]=='{') *objPtr=simple;
              else if(type=="azienda" && line[frominfo]=='{') *objPtr=company;
              else if(type=="gruppo" && line[frominfo]=='{') *objPtr=group;
              else {
                cerr<<"\r\nErrore! Problema con il tipo di utente.";
                return -1;
              }
              objPtr->setID(id1);
                  while(control==0){
                      to=line.find_first_of(":}",from);
                      if(line[to]=='}'){
                          control=1;
                      }else {
                          info = line.substr(from, to - from);
                          from = to + 1;
                          to = line.find(',', from);
                          val = line.substr(from, to - from);
                          if (!objPtr->setInformations(info, val)) {
                              cerr << "\r\nErrore! Potrebbe esserci un problema con il formato file utenti.";
                              return -1;
                          }
                      }
                  }
              if(type=="semplice" && line[frominfo]=='{') mainGraph.setUser(simple);
              else if(type=="azienda" && line[frominfo]=='{') mainGraph.setUser(company);
              else if(type=="gruppo" && line[frominfo]=='{') mainGraph.setUser(group);
          }
      }




return 0;
}
