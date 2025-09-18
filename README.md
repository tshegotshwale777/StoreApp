# StoreApp
Implement an application that tracks items bought from a store.

Use CMake to set up the projects and use QMainWindow instances for the user interfaces so that you can implement the functionality provided by a QMainWindow (such as menus, a toolbar, and a status bar) to meet the requirements of the scenario given below. Please note that you must not use Qt Designer, and you are expected to manually set up GUIs to ensure that you properly handle memory using Qt’s parent-child functionality.

The store keeps a list of customers so that when something is purchased from the store, it is recorded against that customer’s name. Only the customer’s name is required.

Only two items are currently sold in the store currently – books and magazines, and only the name of the item is required. Clearly, a list of such items is needed, and the user should be able to add items to the list. When an item is added, the application should automatically make a backup in memory in case something goes wrong when the application is being used. Provision should thus be made to restore this list when necessary.

Clearly, for the sake of data integrity, you do not want the user to create multiple copies of these lists.
When a customer purchases items, a transaction is recorded. The date/time of the purchase is noted, as is the name, type, and quantity of each item purchased as part of the transaction. Use an appropriate widget to indicate which items have already been added as part of this transaction.

All transactions should be displayed on the main GUI. A tree model (and appropriate view) should be used so that a user can see a customer’s transactions grouped together.
