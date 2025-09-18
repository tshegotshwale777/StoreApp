// Tshegofatso Tshwale  24355224

#ifndef ITEM_H
#define ITEM_H

#include<QString>

class item{
    public:
        enum class iType {Book, Magazine};
        item(const QString &iName, iType type); // constructor

        QString getIname() const; // getter
        iType getType() const; // getter
        QString itemType() const;

    private:
        QString iName;
        iType type; // this is the type of item we have
};

#endif // ITEM_H
