// Tshegofatso Tshwale  24355224

#include "item.h"

using namespace std;

item :: item(const QString &cName, iType type) : iName(cName), type(type) {} // constructor

QString item :: getIname() const{
    return iName;
}

item :: iType item :: getType() const{
    return type;
}

QString item :: itemType() const{
    return (type == iType :: Book ? "Book" : "Magazine");
}
