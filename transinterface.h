// Tshegofatso Tshwale  24355224

#ifndef TRANSINTERFACE_H
#define TRANSINTERFACE_H

#include <QDialog>
#include <QList>
#include "item.h"
#include "itemtransaction.h"

// generic classes
class QListWidget;
class QPushButton;
class QComboBox;
class QSpinBox;

class transInterface : public QDialog{
    Q_OBJECT

    private:
        QList<item*> allItems;
        QList<itemTransaction*> selectedItems;

        QComboBox* itemCombo;
        QSpinBox* qSpin;
        QPushButton* addButton;
        QListWidget* cart;
        QPushButton* doneButton;

    private slots:
        void addItem();

    public:
        transInterface(QList<item*> i, QWidget* parent = nullptr);
        QList<itemTransaction*> getItems() const;
};

#endif // TRANSINTERFACE_H
