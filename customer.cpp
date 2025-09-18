// Tshegofatso Tshwale  24355224

#include "customer.h"

using namespace std;

customer :: customer(const QString &cName) : cName(cName) {} // constructor

QString customer :: getCname() const{
    return cName;
}
