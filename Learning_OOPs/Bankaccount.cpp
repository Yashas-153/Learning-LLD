#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <set>
#include <string> 
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
    double getBalance() const {
        return balance;
    }

    string getName() const {
        return name;
    }

    long long getAccountNo() const {
        return account_no;
    }

    bool withdraw(double amount){
        if(amount <=0 || amount > balance) return false;
        balance -= amount;
        return true;
    }

    bool deposit(double amount){
        if(amount <= 0) return false;
        balance += amount;
        return true;
    }
};
long long BankAccount::AccountNumber = 100000;
int main(){
    BankAccount sb_ac = BankAccount("Monalisa");
    sb_ac.deposit(100);
    double account_balance = sb_ac.getBalance();
    cout<<"Account Balance is "<<account_balance<<endl;
    return 0;
}