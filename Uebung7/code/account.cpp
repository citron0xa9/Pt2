#include <iostream>
#include <cassert>
#include <list>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

//global helper function
string toString(double d)
{
  ostringstream s;
  s << d;
  return s.str();
}


class Account {
public:
    Account(long accountNo, double balance, double limit, bool locked); 
    virtual ~Account();

    long accountNo() const { return accountNo_; } 

    virtual void setLimit(double limit) { limit_ = limit; } 
    double getLimit() const { return limit_; }

    virtual bool credit(double amount); 
    virtual bool debit(double amount); 
    double balance() const { return balance_; } 

    void setLock(bool locked) { locked_ = locked; } 
    bool getLock() const { return locked_; }

private: 
    long accountNo_; 
    double balance_; 
    double limit_; 
    bool locked_;
};

Account::Account(long accountNo, double balance, double limit, bool locked) : 
    accountNo_{accountNo}, 
    balance_{balance}, 
    limit_{limit}, 
    locked_{locked} { 
}

Account::~Account() { 
}

bool Account::credit(double amount) {
    assert(amount>=0.0); 

    // cannot use locked account
    if(locked_) return false; 

    balance_ = balance_ + amount; 
    return true; 
}

bool Account::debit(double amount) {
    assert(amount>=0.0); 

    // cannot use locked account
    if(locked_) return false; 
    
    // check if limit is hit
    if(balance_-amount<limit_) return false; 

    // change balance
    balance_ = balance_ - amount; 
    return true; 
}

class LoggedAccount : public Account{

public:


  LoggedAccount(long accountNo, double balance, double limit, bool locked):Account(accountNo, balance, limit, locked){
    transactions_.push_back("initial balance: " + toString(balance));
    transactions_.push_back("current balance: " + toString(balance));
  }
  virtual ~LoggedAccount();

  virtual void setLimit(double limit) { Account::setLimit(limit); addTransaction("limit change to: " + toString(limit));}
  virtual bool credit(double amount); 
  virtual bool debit(double amount); 
  virtual vector<string> getProtocol(void) const;
private:
  void addTransaction(string desc);
  vector<string> transactions_;
};

void LoggedAccount::addTransaction(string desc)
{
  transactions_.pop_back();
  transactions_.push_back(desc);
  transactions_.push_back("current balance: " + toString(balance()));
}

vector<string> LoggedAccount::getProtocol(void) const
{
  return transactions_;
}

LoggedAccount::~LoggedAccount(){
}

bool LoggedAccount::credit(double amount){
  Account::credit(amount);
  addTransaction("credit, amount: " + toString(amount));
}

bool LoggedAccount::debit(double amount){
  Account::debit(amount);
  addTransaction("debit, amount: " + toString(amount));
}

int main(int argc, char** argv) {
  Account A1(19920, 0.0, -1000.0, false); 
  LoggedAccount A2(20020, 0.0, -1000.0, false);

  A1.credit(500.0);
  A2.credit(500.0);
  A2.debit(100.0);
  A2.setLimit(-2000.0);

  for (auto & x : A2.getProtocol()) {
    cout << x << endl;
  }
  return 0; 
}

