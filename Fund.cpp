// Fund.cpp
// CSS342 program5
// Implemented by Kray Nguyen on 9/12/2020

#include "Fund.h"
#include "Transaction.h"

// Constructor
Fund::Fund() {
    this -> amount = 0;
}

// Deconstructor
Fund::~Fund() {
}

// Add fund
bool Fund::addFund(int amount){
    this -> amount += amount;
    return true;
}

// Reduce fund
bool Fund::reduceFund(int amount){
    this -> amount -= amount;
    if(this-> amount < 0){
        this -> amount += amount;
        return false;
    }
    return true;
}

// Add history to fund
void Fund::addHistoryFund(Transaction aTransaction){
    this -> histories.push_back(aTransaction);
}

// Display fund history
void Fund::displayHistories() {
    for (int i = 0; i < histories.size(); i++) {
        cout << "  " << histories.at(i).getFullCommand() << endl;
    }
}

// Check if there is history
bool Fund::isHistory() const {
    return histories.size() > 0;
}

// Get amount of fund
int Fund::getAmount() const {
    return this->amount;
}

// Initialize fund
void Fund::setFund(int amount){
    this -> amount = amount;
}
