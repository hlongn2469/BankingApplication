# BankingApplication

Develop a banking system that allows the user to open/deposit/transfer/withdraw/display history between accounts. From the bottom up, there are classes:

• BST - Binary search tree to store and retrieve client account

• Fund – Low level class processing to add/reduce/process money to correct fund type

• Client – High level processing class, store client information, and manage transaction request. 

• Transaction – High level class processing requested transaction 

• BankManager – a single class that does all the real work. Process the requested transaction from the file and put each transaction into a queue, execute each transaction in the queue, and report/display all open client accounts.

Implemented Binary search tree to store and retrieve client account.
Implemented Queues to effectively execute transaction request once at a time.

![Class Diagram](/BankSystem.png?raw=true "Title")
