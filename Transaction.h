// Transaction.h
// CSS342 program5
// Implemented by Kray Nguyen on 9/12/2020
#ifndef _TRANS_
#define _TRANS_
#include <fstream>
#include <string.h>
#include "Client.h"
#include "Bst.h"

using namespace std;

const int MAX_SIZE = 10;
const char TRANSACTION_OPEN = 'O';
const char TRANSACTION_DEPOSIT = 'D';
const char TRANSACTION_WITHDRAW = 'W';
const char TRANSACTION_TRANSFER = 'T';
const char TRANSACTION_HISTORY = 'H';

// This class models transaction process, serves as high level code compared 
class Transaction {

    friend ostream& operator<<(ostream & out, const Transaction & aTran);

    public:
    Transaction();
    Transaction(const Transaction& other);
    Transaction(char type, int accountFund, int amount);
    ~Transaction();
    bool setData(ifstream & infile);
    string getFullCommand() const;
    void setAmount(int amount);
    void setCommand(string command);
    int getFirstAccount() const;
    int getSecondAccount() const;
    int getAmount() const;
    void process(Bst & collections);
    private:

    // subfunction open for process
    void processOpen(Bst&);

    // subfunction deposit for process
    void processDeposit(Bst&);

    // subfunction withdraw for process
    void processWithDraw(Bst&);

    // subfunction transfer for process
    void processTransfer(Bst&);

    // subfunction history for process
    void processHistory(Bst&);

    // transaction type
    char type;
    
    // money amount
    int amount;

    // use for case: open
    string last_name;
    string first_name;

    // use for case: open, deposit, withdraw, history
    int firstAccount;

    // use in case transfer
    int secondAccount;

    // to check operations on the same open account or not
    int tempAccount;

    // full commands in case later use
    string fullCommand;
};
#endif
