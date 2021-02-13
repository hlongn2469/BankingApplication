#include <iostream>
#include <fstream>
#include <ostream>
#include "BankManager.h"

using namespace std;

int main () {

    // create bank object
    BankManager bank;

    // read files, then process
    ifstream bankTransInFile("BankTransIn.txt");
    bank.processFile(bankTransInFile);

    // process transaction from queue
    bank.queueProcess();

    // report of the day
    cout << endl;
    bank.report();
    return 0;
}