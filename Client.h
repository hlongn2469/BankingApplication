// Client.h
// CSS342 program5
// Implemented by Kray Nguyen on 9/12/2020
#ifndef _Client_
#define _Client_
#include <iostream>
#include <string>
#include "Fund.h"

// This class models a client account with critical client information for the transaction
const int MAX_FUND = 10;
using namespace std;

class Client {
    friend ostream& operator<<(ostream& out, const Client& client);
public:

    // constructor
    Client();
    Client(string last_name, string first_name, int id1, int id2);
    ~Client();

    // account id in case of O,W,H,D
    int getFirstAccount() const;

    // account id in case of second account of T
    int getSecondAccount() const;

    int getAmountFund(int account) const;
    // Basic information
    string getFirstName() const;
    string getLastName() const;

    // Fund operations. These operations will call the actual operation in fund class
    bool addFund(int account, int amount);
    bool reduceFund(int account, int amount);
    void addHistory(Transaction);
    void displayFund(int digit);
    void addHistoryLinkedFund(Transaction aTransaction, int account, int initialAmount);
    bool operator<(const Client& other) const;
    bool operator>(const Client& other) const;
    bool operator==(const Client& other) const;
    bool operator!=(const Client& other) const;
    
private:
    string last_name;
    string first_name;
    int first_account;
    int second_account;
    int amount;

    // array holding 10 fund types 
    Fund type[MAX_FUND];

    // Fund object used for access fund history later
    Fund history;

    bool withDrawSucess = false;
};
#endif