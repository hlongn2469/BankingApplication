// BankManager.cpp
// CSS342 program5
// Implemented by Kray Nguyen on 9/12/2020

#include "BankManager.h"

BankManager::BankManager() {

}

BankManager::~BankManager() {

}
    
// Takes in everyline and push every line of transaction description to the queue of
// transaction objects
void BankManager::processFile(ifstream & fileName) {

    // check file exist or not
    if (!fileName) {
        cerr << "Could not read file" << endl;
        return;
    }

    // use to set transaction later in loop
    Transaction * ptrTransaction = nullptr;

    // read every line in files
    while (!fileName.eof()) {

        // create temporaty transaction
        ptrTransaction = new Transaction();

        // check transaction is valid transaction or not
        // valid transaction then process transaction
        if (ptrTransaction->setData(fileName) == true) {

            // put in queue
            collectionTransactions.push(*ptrTransaction);
        }

        // delete transaction
        delete ptrTransaction;
    }
    
    // close files
    fileName.close();
}

// While the queue is not empty, pop one transaction out and process 
void BankManager::queueProcess(){
    while(!collectionTransactions.empty()){
        
        // process transcation
        collectionTransactions.front().process(collectionClients);
        
        // delete transaction
        collectionTransactions.pop();
    }
}

// show report of all open account in the BST
void BankManager::report() {

    // read all file from bst
    cout << "Processing Done. Final Balances" << endl;
    cout << collectionClients << endl;
}
