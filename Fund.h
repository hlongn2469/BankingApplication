#ifndef _FUND_
#define _FUND_
#include <string>
#include <queue>
#include <stdio.h>

// Fund.h
// CSS342 program5
// Implemented by Kray Nguyen on 9/12/2020
using namespace std;

// Namespace for access fund's name
namespace Funds_Name {
    const char Name[10][25] = {
        "Money Market",
        "Prime Money Market", 
        "Long-Term Bond",
        "Short-Term Bond",
        "500 Index Fund", 
        "Capital Value Fund",
        "Growth Equity Fund",
        "Growth Index Fund", 
        "Value Fund",
        "Value Stock Index"
    };
}

// this class models operations in each fund type (0-9)
class Transaction;
class Fund {
    public:
        Fund();
        ~Fund();
        bool addFund(int amount);
        bool reduceFund(int amount);
        void setFund(int amount);
        void addHistoryFund(Transaction aTransaction);
        void displayHistories();
        bool isHistory() const;
        int getAmount() const;
    private:
    int amount;

    // hold transaction history
    vector<Transaction> histories;
};
#endif
