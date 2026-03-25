#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <set>
using namespace std;

class BankAccount {
private:
    double balance;
    long long account_no;
    string name;
    static long long AccountNumber;

public:
    BankAccount(string name): name(name), balance(0){
        account_no = AccountNumber++;
    }
    double getBalance(){
        return balance;
    }

    string getName(){
        return name;
    }

    long long getAccountNo(){
        return account_no;
    }

    bool withdraw(double amount){
        if(amount <=0 or amount > balance) return false;
        balance -= amount;
        return true;
    }

    bool deposit(double amount){
        if(amount <= 0) return false;
        balance += amount;
        return true;
    }
};