// BankManager.h
// CSS342 program5
// Implemented by Kray Nguyen on 9/12/2020

#ifndef _BANK_MANAGER_
#define _BANK_MANAGER_

// #include "Transaction.h"
#include "Bst.h"
#include "Client.h"
#include "Transaction.h"
#include <queue>
#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

// This class models the bank manager to process the file, process data 
// within the queue, and show the report of all open account in the bank
class BankManager {
public:

    // constructor
    BankManager();
    ~BankManager();
    
    // build file
    void processFile(ifstream & fileName);

    void queueProcess();

    // show report
    void report();
private:
    Bst collectionClients;
    queue<Transaction> collectionTransactions;
};

#endif //!_BANK_MANAGER_