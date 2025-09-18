// Tshegofatso Tshwale  24355224

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QDateTime>
#include <QList>
#include "customer.h"
#include "itemtransaction.h"

class transaction{
    private:
        QList<itemTransaction*> items;
        QDateTime timeNdate;
        customer *c;

    public:
        transaction(customer *c); // constructor

        void addItem(item *i, int qty);
        QList<itemTransaction*> getItems() const;
        QDateTime getTimeNdate() const;
        customer *getCustomer() const;

};

#endif // TRANSACTION_H
