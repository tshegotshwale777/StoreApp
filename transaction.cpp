// Tshegofatso Tshwale  24355224

#include "transaction.h"

using namespace std;

transaction :: transaction(customer *c) : c(c), timeNdate(QDateTime :: currentDateTime()) {} // constructor

void transaction :: addItem(item *i, int qty){
    items.append(new itemTransaction(i, qty));
}

QList<itemTransaction*> transaction :: getItems() const{
    return items;
}

customer* transaction :: getCustomer() const{
    return c;
}

QDateTime transaction :: getTimeNdate() const{
    return timeNdate;
}
