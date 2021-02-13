// Transaction.cpp
// CSS342 program5
// Implemented by Kray Nguyen on 9/12/2020
#include "Transaction.h"

Transaction::Transaction() {
}

Transaction::Transaction(char type, int accountFund, int amount) {
    this->type = type;
    this->firstAccount = accountFund;
    this->amount = amount;

    // set full command
    this->fullCommand += type;
    this->fullCommand += " ";
    this->fullCommand += to_string(firstAccount);
    this->fullCommand += " ";
    this->fullCommand += to_string(amount);
}

// copy full commands in case later use
Transaction::Transaction(const Transaction & other) {
    string fullCommand;
    this->type = other.type;
    this->amount = other.amount;
    this->last_name = other.last_name;
    this->first_name = other.first_name;
    this->firstAccount = other.firstAccount;
    this->secondAccount = other.secondAccount;
    this->fullCommand = other.fullCommand;
}

Transaction::~Transaction() {

}

// returns whether setting data from a line of transaction succeeded
bool Transaction::setData(ifstream & fileName) {
    string description;
    if(fileName.is_open()){
        while(getline(fileName,description)){

            // set full comand
            fullCommand = description;

            // first char at the line
            char *token = strtok((char*) description.c_str(), " ");

            // if first char is O
            // read until the end of line follow by first char
            if(description.at(0) == 'O') {
                type = 'O';                         // check type
                token = strtok(nullptr, " ");
                last_name = token;                  // set last name
                token = strtok(nullptr, " ");
                first_name = token;                 // set last name
                token = strtok(nullptr, " ");
                firstAccount = stoi(token);         // set id
                tempAccount = firstAccount;
                return true;

            // similar check for D
            } else if(description.at(0) == 'D') {
                type = 'D';                         // check type
                token = strtok(nullptr," ");
                firstAccount = stoi(token);         // set id
                token = strtok(nullptr," ");
                amount = stoi(token);               // set amount

                // invalid deposit amount
                if(firstAccount < 10000){
                    return false;
                } 

                // check if same with open account

                if(firstAccount/10 != tempAccount){
                    return false;
                }
                return true;
            
            // similar check for W
            } else if(description.at(0) == 'W') {
                type = 'W';
                token = strtok(nullptr," ");
                firstAccount = stoi(token);
                token = strtok(nullptr," ");
                amount = stoi(token);

                // invalid withdraw amount
                if(firstAccount < 10000){
                    return false;
                } 

                // check if same with open account
                if(firstAccount/10 != tempAccount){
                    return false;
                }
                return true;

            // similar check for T
            } else if (description.at(0) == 'T') {
                type = 'T';
                token = strtok(nullptr," ");
                firstAccount = stoi(token);
                token = strtok(nullptr," ");
                amount = stoi(token);
                token = strtok(nullptr," ");
                secondAccount = stoi(token);
                
                // if 2 transfer share the same account AND same type
                if(firstAccount == secondAccount){
                    return false;
                }

                // invalid amount plus invalid account id
                if(firstAccount < 10000 || secondAccount < 10000){
                    return false;
                } 

                // check if same with open account
                if(firstAccount/10 != tempAccount){
                    return false;
                }
                return true;
            
            // similar check for H
            } else if (description.at(0) == 'H'){
                type = 'H';
                token = strtok(nullptr," ");
                firstAccount = stoi(token);
                if(firstAccount/10 != tempAccount){
                    return false;
                }
                return true;
            // in case for invalid transaction
            } else {
                return false;
            }
        }
    }
    return true;
}

string Transaction::getFullCommand() const {
    return this->fullCommand;
}

void Transaction::setCommand(string command){
    this -> fullCommand = command;
}

int Transaction::getFirstAccount() const {
    return this->firstAccount;
}

int Transaction::getSecondAccount() const {
    return this->secondAccount;
}

int Transaction::getAmount() const {
    return this->amount;
}

void Transaction::setAmount(int amount){
    this -> amount = amount;
}

// general process then process specific type of transaction
void Transaction::process(Bst & clientCollection) {
    if (type == TRANSACTION_OPEN) {
        processOpen(clientCollection);
    }

    if (type == TRANSACTION_DEPOSIT) {
        processDeposit(clientCollection);
    }

    if (type == TRANSACTION_WITHDRAW) {
        processWithDraw(clientCollection);
    }

    if (type == TRANSACTION_TRANSFER) {
        processTransfer(clientCollection);
    }

    if (type == TRANSACTION_HISTORY) {
        processHistory(clientCollection);
    }
}

// Open the client account and insert it into the client BST
void Transaction::processOpen(Bst & clientCollection) {

    // new account
    Client * account = new Client(last_name, first_name, firstAccount, -1); 

    // insert
    if(!clientCollection.Insert(account)) {
        cerr << "ERROR: Account " 
        << firstAccount
        << " is already open. Transaction refused." << endl;

        delete account;
    }
}

// Deposit process includes retreiveing the client account from the bst then 
// add fund and history into that client account
void Transaction::processDeposit(Bst & clientCollection) {
    Client* retriever; // client pointer to add fund
    int fourDigit = firstAccount / 10; // get four digit

    // account found
    if(clientCollection.Retrieve(fourDigit, retriever)){
        if(retriever != nullptr) {
            if(!retriever->addFund(firstAccount, amount)){
                // for display purposes
                string temp;
                temp += this->type;
                temp += " ";
                temp += to_string(firstAccount);
                temp += " ";
                temp += to_string(amount);
                temp += " ";
                temp += "(Failed)";
                this->fullCommand = temp;

                // even fail, add to history
                //retriever->addHistory(*this);
            }
            retriever->addHistory(*this);
            retriever = nullptr;
        }
    }

    // account not found
    else {
        cerr << "ERROR: Account "
        << fourDigit
        << " not found. Deposit refused." << endl;

    }
}

// Withdraw process includes retrieving the account from the BST
// then reduce fund and add history into that client account
void Transaction::processWithDraw(Bst & clientCollection) {

    Client *retriever; // client pointer to add fund
    int fourDigit = firstAccount / 10; // get four digit
    int lastDigit = firstAccount % 10; // get last digit
    
    // account found
    if(clientCollection.Retrieve(fourDigit, retriever)){

        int initialAmount = retriever->getAmountFund(firstAccount);

        // account reduces fund unsucessfully
        // if reduce fund succesfully, internally add history, otherwise add history here
        if(!retriever->reduceFund(firstAccount, amount)) {
            cerr << "ERROR: Not enough funds to withdraw "
            << amount << " from " << retriever->getFirstName()
            << " " << retriever->getLastName()
            << " " << Funds_Name::Name[lastDigit] << endl;

            // for display purposes
            string temp;
            temp += this->type;
            temp += " ";
            temp += to_string(firstAccount);
            temp += " ";
            temp += to_string(amount);
            temp += " ";
            temp += "(Failed)";
            this->fullCommand = temp;

            // even fail, add to history
            retriever->addHistory(*this);
        }
        
        // Successfully withdraw
        // Need to check special linked funds or other funds
        else {

            // This is for linked funds
            // Already withdraw from other, but need to add history for both funds because
            // overdrawn, only for 0,1,2,3 funds
            if (initialAmount < amount) {
                retriever->addHistoryLinkedFund(*this, firstAccount, initialAmount);
            }
            
            // This is for other funds
            else {
                retriever->addHistory(*this);
            }
        }
        retriever = nullptr;
    }

    // account not found
    else {
        cerr << "ERROR: Account "
        << fourDigit
        << " not found. Withdraw refused." << endl;
    }
}

// Transfer process includes retrieving both accounts involved in the transaction
// reduce fund from first account and deposit fund to second account
void Transaction::processTransfer(Bst & clientCollection) {
    Client *retriever1; // for client account1
    Client *retriever2; // for client account2
    int fourDigitFirst = firstAccount / 10; // get four digit
    int fourDigitSecond = secondAccount / 10; // get four digit

    // Both account found
    if(clientCollection.Retrieve(fourDigitFirst, retriever1) 
    && clientCollection.Retrieve(fourDigitSecond,retriever2)){

        // if reduce fund sucessfully from first account 
        if (retriever1->reduceFund(firstAccount, amount)) {

            // add fund to second account
            retriever2->addFund(secondAccount, amount);

            // add history to first account
            retriever1->addHistory(*this);

            // add history to destination
            // critical: need this to set transfer
            // add history only look for first account,
            // then change first as second
            this->firstAccount = this->secondAccount;

            // add history to second account;
            retriever2->addHistory(*this);
        }

        // if reduce fund unsucesfully from first account
        else {
            cerr << "ERROR: Not enough funds to withdraw "
            << amount
            << " Transferal refused." << endl;
        }
    } 
    
    // if both acccount or one of the accounts are not found 
    else {
        if (retriever1 == nullptr) {
            cerr << "ERROR: Account "
            << fourDigitFirst
            << " not found. Transferal refused." << endl;
        }

        else if (retriever2 == nullptr) {
            cerr << "ERROR: Account "
            << fourDigitSecond
            << " not found. Transferal refused." << endl;
        }

        else if (retriever1 == nullptr && retriever2 == nullptr) {
            cerr << "ERROR: Account "
            << firstAccount << " " << secondAccount
            << " not found. Transferal refused." << endl;
        }
    }
    retriever1 = retriever2 = nullptr;
}

// Process history includes retrieving the account from the BST
// only display history of 4 digit account
void Transaction::processHistory(Bst & clientCollection) {
    Client *retriever; // client pointer

    int fourDigit = firstAccount;

    // if the account id has 5 digits reduce to 4 degits
    if (fourDigit >= 10000) {
        fourDigit /= 10;
    }

    // account found
    if(clientCollection.Retrieve(fourDigit, retriever)){
        retriever->displayFund(firstAccount);
    }

    // account not found
    else {
        cerr << "ERROR: Account "
        << firstAccount
        << " not found. History refused." << endl;
    }
}

// Overload operator ostream
// use to print out transaction information
ostream& operator<<(ostream & out, const Transaction & aTran) {
    out << aTran.getFullCommand();
    return out;
}
