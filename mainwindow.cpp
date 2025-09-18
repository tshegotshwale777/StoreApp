// Tshegofatso Tshwale  24355224

#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QLabel>
#include <QInputDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamreader>
#include <QDebug>
#include <QStandardPaths>
#include<QDir>
#include <QCloseEvent>
#include "mainwindow.h"
#include "transinterface.h"

using namespace std;


MainWindow :: MainWindow(QWidget *parent) : QMainWindow(parent){ // constructor

    setupUi();

    // for the xml
    QString path = QStandardPaths :: writableLocation((QStandardPaths :: AppDataLocation));
    QDir().mkpath(path); // ensure it exists
    loadFrmXML(path + "/store_data.xml");

    //updateUI();
}

MainWindow :: ~MainWindow(){ // destructor
    // clean up memory

    qDeleteAll(customers);
    customers.clear();

    qDeleteAll(items);
    items.clear();
}

// setting up the UI
void MainWindow :: setupUi(){

    // variables
    QAction *addCustomer, *addItem, *nuTransaction; // when this button is clicked? LOOK!!!
    QToolBar *tB;
    QMenu *fMenu, *cMenu, *iMenu, *hMenu, *tMenu; // the menu options

    // the window setup
    setWindowTitle("Store Manager");
    resize(800, 600);

    // menu options
    fMenu = menuBar()->addMenu("File"); // this is the files menu
    cMenu = menuBar()->addMenu("Customer"); // this is the customers menu
    iMenu = menuBar()->addMenu("Items"); // this is the items menu
    hMenu = menuBar()->addMenu("Help"); // this is the help menu
    tMenu = menuBar()->addMenu("Transaction");

    // the toolbar
    tB = addToolBar("Main"); // this is for the main toolbar
    addCustomer = tB->addAction("Add a customer"); // prompt to add a customer
    addItem = new QAction("Add an item", this);
    tB->addAction(addItem); // prompt to add an item
    iMenu->addAction(addItem); // gives us the item options
    nuTransaction = new QAction("New transaction", this);
    tMenu->addAction(nuTransaction);

    // connect buttons to their slots
    connect(addCustomer, &QAction :: triggered, this, &MainWindow :: addCustomer); // connect customer button
    connect(addItem, &QAction :: triggered, this, &MainWindow :: addItem); // connect item button
    connect(nuTransaction, &QAction :: triggered, this, &MainWindow :: nuTransaction);


    // the status bar
    statusBar()->showMessage("Ready!");

    // adding the tree viewer
    transView = new QTreeWidget(this);
    transView->setColumnCount(1);
    transView->setHeaderLabel("Transaction history");

    // create the tree layout
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(transView);

    // create the main widget to hold the layout
    QWidget *mainWidget = new QWidget(this);
    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);

}

// adding a customer
void MainWindow :: addCustomer(){

    QString cName; // variable to store name
    bool done = true; // this is when a customer is successfully added

    cName = QInputDialog :: getText(this, "Please add a customer", "Customer name: ", QLineEdit :: Normal, "", &done);

    // check for duplicates
    if(!cName.trimmed().isEmpty() && done){
        for(customer *c : customers){
            if(c->getCname().compare(cName, Qt :: CaseInsensitive) == 0){
                QMessageBox :: warning(this, "Duplicate!", "This customer already exists!");
                return;
            }
        }

        customers.append(new customer(cName));
        statusBar()->showMessage("Customer: " + cName + " is added.", 3000);
    }
    else  if(done){ // if done is clicked but nothing is entered

        QMessageBox :: warning(this, "Error!", "Customer name cannot be empty!");
    }

}

// adding an item
void MainWindow :: addItem(){

    QString iName, selected; // this is the item variable
    QStringList types {"Book", "Magazine"};
    bool done = true;

    // get the name of the item
    iName = QInputDialog :: getText(this, "Please add an item", "Item name: ", QLineEdit :: Normal, "", &done);

    if(!done){
        return; // the user cancelled
    }

    iName = iName.trimmed();
    if(iName.isEmpty()){ // if nothing is entered
        QMessageBox :: warning(this, "Error!", "Item name cannot be empty!");
        return;
    }

    // determine what type of item it is
    selected = QInputDialog :: getItem(this, "Item type", "Select the item type: ", types, 0, false, &done);

    if(!done){
        return; // the user cancelled
    }

    // menu selection can use switch for it
    item :: iType type = (selected == "Book") ? item :: iType :: Book : item :: iType :: Magazine;

    // check for duplicates
    for(item *i : items){
        if(i->getType() == type && i->getIname().compare(iName, Qt :: CaseInsensitive) == 0){
            QMessageBox :: warning(this, "Duplicate!", "That item already exists!");
            return;
        }
    }

    // adding the items
    items.append(new item(iName, type));
    statusBar()->showMessage("Added " + selected + ": " + iName, 3000);
}

// adding a new transaction
void MainWindow :: nuTransaction(){
    QString selected;
    bool done = true;

    if(customers.isEmpty()){
        QMessageBox :: warning(this, "No customers!", "Please add a customer before proceeding!");
        return;
    }

    if(items.isEmpty()){
        QMessageBox :: warning(this, "No items!", "Please add items before proceeding!");
        return;
    }

    // choose a customer
    QStringList cNames;
    for(customer *c : customers){
        cNames << c->getCname();
    }

    selected = QInputDialog :: getItem(this, "Please select a customer!", "Customer:", cNames, 0, false, &done);
    if(!done){
        return; // user cancelled
    }

    customer *cus = nullptr;
    for(customer *c : customers){
        if(c->getCname() == selected){
            cus = c;
            break;
        }
    }

    // deal with the transaction interface
    transInterface dialog(items, this);
    if(dialog.exec() == QDialog :: Accepted){
        transaction *nuT = new transaction(cus); // link the transaction with the customer
        for(itemTransaction* tItem : dialog.getItems()){
            nuT->addItem(tItem->getItem(), tItem->getQuantity());
        }

        transactions.append(nuT);
        statusBar()->showMessage("Transaction has been recorded for " + cus->getCname());
        refreshTransView();
    }

}

// showing the tree view of all the transactions
void MainWindow :: refreshTransView(){
    transView->clear();

    for(customer *c : customers){
        QTreeWidgetItem *cusItem = new QTreeWidgetItem(transView);
        cusItem->setText(0, c->getCname());

        for(transaction *t : transactions){
            if(t->getCustomer() == c){
                QTreeWidgetItem *transItem = new QTreeWidgetItem(cusItem);
                transItem->setText(0, t->getTimeNdate().toString("yyyy-mm-dd hh:mm:ss"));

                for(itemTransaction *iT : t->getItems()){
                    QString deets = iT->getItem()->getIname() + " x" + QString :: number(iT->getQuantity());
                    QTreeWidgetItem *iEntry = new QTreeWidgetItem(transItem);
                    iEntry->setText(0, deets);
                }
            }
        }
    }

    transView->expandAll();
}

// saving to XML
void MainWindow :: saveToXML(const QString &fName){
    QFile file(fName);
    if(!file.open(QIODevice :: WriteOnly)){
        qWarning() << "The file is unable to be opened for writing: " << fName;
        return;
    }

    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();

    xml.writeStartElement("Store");

    xml.writeStartElement("Customers");
    for(const QString &cus : cList){
        xml.writeTextElement("Customer", cus);
    }

    xml.writeStartElement("purchaseHistory");
    for(const pHistory &pH : pList){
        xml.writeStartElement("pHistory");
        xml.writeTextElement("customerName", pH.cName);
        xml.writeTextElement("Item", pH.iName);
        xml.writeTextElement("Quantity", QString :: number(pH.q));
        xml.writeEndElement();
    }

    xml.writeEndElement(); // for the purchases
    xml.writeEndElement(); // for the store
    xml.writeEndDocument();

    file.close();
}

// loading from the XML
void MainWindow :: loadFrmXML(const QString &fName){
    QFile file(fName);
    if(!file.open(QIODevice :: ReadOnly)){
        qWarning() << "The file is unable to be opened for writing: " << fName;
        return;
    }

    QXmlStreamReader xml(&file);

    cList.clear();
    pList.clear();

    while(!xml.atEnd() && !xml.hasError()){
        QXmlStreamReader :: TokenType token = xml.readNext();

        if(token == QXmlStreamReader :: StartElement){
            if(xml.name() == "customerName:"){
                cList.append(xml.readElementText());
            }
            else if(xml.name() == "purchaseHistory"){
                pHistory p;
                while(!(xml.tokenType() == QXmlStreamReader :: EndElement && xml.name() == "purchaseHistory")){
                    xml.readNext();
                    if(xml.tokenType() == QXmlStreamReader :: StartElement){
                        if(xml.name() == "customerName"){
                            p.cName = xml.readElementText();
                        }
                        else if(xml.name() == "Item"){
                            p.iName = xml.readElementText();
                        }
                        else if(xml.name() == "Quantity"){
                            p.q = xml.readElementText().toInt();
                        }
                    }
                }

                pList.append(p);
            }
        }
    }

    if(xml.hasError()){
        qWarning() << "XML Error: " << xml.errorString();
    }

    file.close();
}

void MainWindow :: closeEvent(QCloseEvent *event){
    QString path = QStandardPaths :: writableLocation((QStandardPaths :: AppDataLocation));
    QDir().mkpath(path); // ensure it exists
    saveToXML(path + "/store_data.xml");
}
