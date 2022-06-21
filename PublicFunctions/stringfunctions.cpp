#include "stringfunctions.h"

StringFunctions::StringFunctions()
{

}

QString StringFunctions::canonicalString(QString from)
{
   QString an = "";
   for(int i = 0; i < from.count(); i++){
       if(from[i] == '\r' || from[i] == '\n'){
           from[i] = ' ';
       }
       if(i == 0 || from[i] != ' ' || an[an.count() - 1] != ' '){
           an += from[i];
       }
   }
   return an;
}

QString StringFunctions::removeLastSpaces(QString from)
{
    while(from.count() > 0 && from[from.count() - 1] == ' '){
        from.remove(from.count() - 1, 1);
    }
    return from;
}
