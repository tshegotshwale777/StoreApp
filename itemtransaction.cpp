// Tshegofatso Tshwale  24355224

#include "itemtransaction.h"

itemTransaction::itemTransaction(item *i, int quantity) : i(i), quantity(quantity) {} // constructor

item *itemTransaction :: getItem() const{
    return i;
}

int itemTransaction :: getQuantity() const{
    return quantity;
}
