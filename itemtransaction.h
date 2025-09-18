// Tshegofatso Tshwale  24355224

#ifndef ITEMTRANSACTION_H
#define ITEMTRANSACTION_H

#include "item.h"

class itemTransaction{
    private:
        item *i;
        int quantity;

    public:
        itemTransaction(item *i, int quantity); // constructor

        item *getItem() const; // getter
        int getQuantity() const; // getter
};

#endif // ITEMTRANSACTION_H
