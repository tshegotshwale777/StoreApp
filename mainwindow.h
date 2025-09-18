// Tshegofatso Tshwale  24355224

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QTreeWidget>
#include <QStringList>
#include "customer.h"
#include "item.h"
#include "transaction.h"

// add a structure that will be used for the XML view
struct pHistory{
    QString cName; // customer names
    QString iName; // item names
    int q; // quantity
};

class MainWindow : public QMainWindow{

    Q_OBJECT

    private:
        QStringList cList; // save the customer names
        QList<pHistory> pList; // save the transaction purchases
        QList<customer*> customers; // pointer variable list that holds the list of customers
        QList<item*> items; // pointer variable list that holds the list of items
        QList<transaction*> transactions; // pointer variable list that holds the list of transactions
        QTreeWidget *transView; // tree view


        void setupUi();
        void addCustomer(); // slot - this is the button to add customers
        void addItem(); // slot - this is the button to add items
        void nuTransaction(); // slot - this is the button to add transactions
        void refreshTransView();
        void closeEvent(QCloseEvent *event) override;

    public:
        explicit MainWindow(QWidget *parent = nullptr); // constructor
        ~MainWindow(); //destructor

        // for the XML viewer
        void saveToXML(const QString &fName); // file name
        void loadFrmXML(const QString &fName);


};

#endif // MAINWINDOW_H
