// Tshegofatso Tshwale  24355224

#include <QMessageBox>
#include <QSpinBox>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>

#include "transinterface.h"

using namespace std;

// constructor for the transaction interface dialog box
transInterface::transInterface(QList<item*> i, QWidget *parent) : QDialog(parent), allItems(i) {

    // setting up the window dimensions
    setWindowTitle("Please add selected items to the transaction");
    resize(400, 300);

    itemCombo = new QComboBox(this);
    for(item* i : allItems){
        itemCombo->addItem(i->getIname() + " (" + i->itemType() + ") ");
    }

    // setting up the spin boxes
    qSpin = new QSpinBox(this);
    qSpin->setRange(1, 100);
    qSpin->setValue(1);

    // setting up butttons
    addButton = new QPushButton("Add to cart", this);
    connect(addButton, &QPushButton :: clicked, this, &transInterface :: addItem);

    // setting up the box layout and widgets
    QHBoxLayout* inLayout = new QHBoxLayout();
    inLayout->addWidget(itemCombo);
    inLayout->addWidget(qSpin);
    inLayout->addWidget(addButton);

    cart = new QListWidget(this); // add to cart widget

    doneButton = new QPushButton("Done", this);
    connect(doneButton, &QPushButton :: clicked, this, &QDialog :: accept);

    QVBoxLayout *mLayout = new QVBoxLayout(this);
    mLayout->addLayout(inLayout);
    mLayout->addWidget(cart);
    mLayout->addWidget(doneButton);

    setLayout(mLayout);

}

void transInterface :: addItem(){
    //variables
    int index, qty;
    item* selected;

    index = itemCombo->currentIndex();
    if(index >= allItems.size() || index < 0){
        return;
    }

    selected = allItems.at(index);
    qty = qSpin->value();

    selectedItems.append(new itemTransaction(selected, qty));
    cart->addItem(selected->getIname() + " x" + QString :: number(qty));

}

QList<itemTransaction*> transInterface :: getItems() const{
    return selectedItems;
}
