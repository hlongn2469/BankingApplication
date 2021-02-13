// Client.cpp
// CSS342 program5
// Implemented by Kray Nguyen on 9/12/2020
#include "Client.h"
#include "Transaction.h"

// Constructor
Client::Client() {
    first_name = "NONE";
    last_name = "NONE";
    this -> first_account = -1;
    this -> second_account = -1;
}

// constructor
Client::Client(string last_name, string first_name, int id1, int id2) {
    this -> first_name = last_name;
    this -> last_name = first_name;
    this -> first_account = -1;
    this -> first_account = id1;
    this -> second_account = id2;
}

// Default constructor
Client::~Client() {
    
}

// Get first account
int Client::getFirstAccount() const {
    return this->first_account;
}

// Get second account
int Client::getSecondAccount() const {
    return this->second_account;
}

// get client first name
string Client::getFirstName() const {
    return this->first_name;
}

// Get client last name
string Client::getLastName() const {
    return this->last_name;
}

// Get amount fund
int Client::getAmountFund(int account) const {
    int lastDigit = account % 10;
    return type[lastDigit].getAmount();
}

// Add fund
bool Client::addFund(int account, int amount) {
    if(amount < 0){
        return false;
    }
    int lastDigit = account % 10;

    // check account in bounce
    if (lastDigit <= 9 && lastDigit >= 0) {

        // add amount successfully
        if (type[lastDigit].addFund(amount)) {
            return true;
        }

        // false to add amount
        else {
            return false;
        }
    }

    // out of bounce of 10 accounts
    else {
        return false;
    }
}

// Reduce fund for important operations around W and T
bool Client::reduceFund(int account, int amount) {
    if(amount < 0){
        return false;
    }

    int lastDigit = account % 10;

    // check account in bounce
    if (lastDigit <= 9 && lastDigit >= 0) {
        
        // reduce amount successfully
        if (type[lastDigit].reduceFund(amount)) {
            return true;
        }

        // false to reduce amount, not enough fund
        else {

            // Implement the exception of 2 linked account (0,1)
            if(lastDigit == 0 ){
                int total = type[lastDigit].getAmount() + type[1].getAmount();
                
                // not enough amount from two account
                if(total < amount){
                    return false;
                }

                // enough amount from two account
                else {
                    int balance = type[lastDigit].getAmount() - amount;
                    int check_balance = type[1].getAmount() + balance;
                    if(check_balance > 0){
                        type[lastDigit].setFund(0);
                        type[1].reduceFund(balance *-1);

                        // add history
                        return true;
                    } else {
                        return false;
                    }
                }

            // Implement the exception of 2 linked account (0,1)
            } else if(lastDigit == 1 ){
                int total = type[lastDigit].getAmount() + type[0].getAmount();

                // not enough amount from two account
                if(total < amount){
                    return false;
                }
                
                // enough amount from two account
                else {
                    int balance = type[lastDigit].getAmount() - amount;
                    int check_balance = type[0].getAmount() + balance;
                    if(check_balance > 0){
                        type[lastDigit].setFund(0);
                        type[0].reduceFund(balance *-1);
                        return true;
                    } else {
                        return false;
                    }
                }
            
            // Implement the exception of 2 linked account (2,3)
            } else if(lastDigit == 2 ){
                
                int total = type[lastDigit].getAmount() + type[3].getAmount();
                
                // not enough amount from two account
                if(total < amount){
                    return false;
                }  
                
                // enough amount from two account
                else {
                    int balance = type[lastDigit].getAmount() - amount;
                    int check_balance = type[3].getAmount() + balance;
                    if(check_balance > 0){
                        type[lastDigit].setFund(0);
                        type[3].reduceFund(balance *-1);
                        return true;
                    } else {
                        return false;
                    }
                }

            // Implement the exception of 2 linked account (2,3)
            } else if (lastDigit == 3){
                int total = type[lastDigit].getAmount() + type[2].getAmount();
                
                // not enough amount from two account
                if(total < amount){
                    return false;
                }  
                
                // enough amount from two account
                else {
                    int balance = type[lastDigit].getAmount() - amount;
                    int check_balance = type[2].getAmount() + balance;
                    if(check_balance > 0){
                        type[lastDigit].setFund(0);
                        type[2].reduceFund(balance *-1);
                        return true;
                    } else {
                        return false;
                    }
                }
            }
            return false;
        }
    }

    // out of bounce of 10 accounts
    else {
        return false;
    }
}

// Add history
void Client::addHistory(Transaction aTransaction) {

    // find last digit
    int lastDigit = aTransaction.getFirstAccount() % 10;

    // check boundaries 
    if (lastDigit <= 9 && lastDigit >= 0) {

        // add history to correct fund type
        type[lastDigit].addHistoryFund(aTransaction);
    }
}

// Add history linked fund
// This function is for special case linked funds
void Client::addHistoryLinkedFund(Transaction aTransaction, int account, int initialAmount) {

    int lastDigit = account % 10;
    if (lastDigit == 0) {
        type[0].addHistoryFund(Transaction('W', account, initialAmount));
        type[1].addHistoryFund(Transaction('W', account+1, aTransaction.getAmount() - initialAmount));
    }

    else if (lastDigit == 1) {
        type[1].addHistoryFund(Transaction('W', account, initialAmount));
        type[0].addHistoryFund(Transaction('W', account+1, aTransaction.getAmount() - initialAmount));
    } 

    else if (lastDigit == 2) {
        type[2].addHistoryFund(Transaction('W', account, initialAmount));
        type[3].addHistoryFund(Transaction('W', account+1, aTransaction.getAmount() - initialAmount));
    }
           
    else if (lastDigit == 3) {
        type[3].addHistoryFund(Transaction('W', account, initialAmount));
        type[2].addHistoryFund(Transaction('W', account+1, aTransaction.getAmount() - initialAmount));
    }

    else {
        return;
    }
}

// Diplay fund based on 5 digits and 4 digits
void Client::displayFund(int digit) {

    // 5 digit
    if (digit / 10 > 1000) {

        // display specific
        int lastDigit = digit % 10;

        cout << "Transaction History for " << this->first_name << " " << this->last_name
        << " " << Funds_Name::Name[lastDigit] << ": $"
        << type[lastDigit].getAmount();
        cout << endl;

        // print out fund's histories
        type[lastDigit].displayHistories();

    }

    // 4 digit
    else {

        // display all
        cout << "Transaction History for " << this->first_name<< " " << this -> last_name
        << " by fund." << endl;

        // print out all funds history if exist history
        for(int i = 0; i < MAX_FUND; i++){

            // only print out funds have histories 
            if (type[i].isHistory()) {
                cout << Funds_Name::Name[i] << ": $" << type[i].getAmount() << endl;
                type[i].displayHistories();
            }
        }
    }
}

// operator less than
bool Client::operator<(const Client& other) const {
    return first_account < other.first_account;
}

// operator greater
bool Client::operator>(const Client& other) const {
    return first_account > other.first_account;
}

// operator equal
bool Client::operator==(const Client& other) const {
    return first_account == other.first_account;
}

// operator not equal
bool Client::operator!=(const Client & other) const {
    return first_account != other.first_account;
}

// ostream
ostream& operator<<(ostream& out, const Client& client) {

    // Infor
    out << client.first_name << " " 
    << client.last_name << " " 
    << "Account ID: " << client.first_account 
    << '\n';

    // Type account
    for (int i = 0; i < MAX_FUND; i++) {
        out << "   " << Funds_Name::Name[i] << ": $" << client.type[i].getAmount() << endl;
    }
    return out;
}
