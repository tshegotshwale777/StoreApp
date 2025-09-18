// Tshegofatso Tshwale  24355224

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>

class customer{

    private:
        QString cName;

    public:
        customer(const QString &cName); // constructor
        QString getCname() const; // getter

};

#endif // CUSTOMER_H
