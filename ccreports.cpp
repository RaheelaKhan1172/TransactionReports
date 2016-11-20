#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <locale>
#include <fstream>
#include <iomanip>
using namespace std;

static const int g_tSize = 16;
static const int g_defaultRewardPoints = 1000;
typedef enum { D, B, G } T_TransactionType;

//abstract class
class Transaction {
   private:
      string t_type_;
   protected:
      string transaction_date_;
      int transaction_id_;
      double transaction_amount_;
   public:
      Transaction();
      Transaction(string t_date, int t_id, double t_amount,T_TransactionType t_type);
      bool operator==(const Transaction & transaction_to_compare) const;
      virtual ~Transaction();

      //getters/setters
      string get_transaction_date() const;
      void set_transaction_date(string date);

      int get_transaction_id() const;
      void set_transaction_id(int id);
      
      double get_transaction_amount() const;
      void set_transaction_amount(double amount);

      string get_transaction_type() const;
      void set_transaction_type(T_TransactionType type);

      //member functions
      virtual void Display() const = 0;
      virtual void DisplaySummary() const = 0;
      virtual void EarnPoints() = 0;
};

class DepartmentStoreTransaction : public Transaction {
   private:
      static int total_count_;
      static double total_amount_;
      string department_name_;
      int return_policy_;
   public:
      DepartmentStoreTransaction();
      DepartmentStoreTransaction(string name, int policy, string t_date, int t_id, double t_amount,T_TransactionType t_type);
      virtual ~DepartmentStoreTransaction();
      
      //getters/setters
      string get_department_name() const;
      void set_department_name(string name);
   
      int get_return_policy() const;
      void set_return_policy(int days);
      
      void increment_total_count();
      int get_total_count() const;

      void increment_total_amount(double amount);
      double get_total_amount() const;

      //member functions
      virtual void Display() const;
      virtual void DisplaySummary() const;
      virtual void EarnPoints(); 
};

//derived classes from abstract class Transaction
class BankingTransaction : public Transaction {
   private:
      static int total_count_;
      static double total_amount_;
      string type_;
      double fee_;
   public:
      BankingTransaction();
      BankingTransaction(string type, double fee, string t_date, int t_id, double t_amount,T_TransactionType t_type);
      virtual ~BankingTransaction();
   
      string get_type() const;
      void set_type(string type);

      double get_fee() const;
      void set_fee(double fee);
      
      void increment_total_count();
      int get_total_count() const;

      void increment_total_amount(double amount);
      double get_total_amount() const;

      virtual void Display() const; 
      virtual void DisplaySummary() const;
      virtual void EarnPoints();
};

class GroceryTransaction : public Transaction {
   private:
      static int total_count_;
      static double total_amount_;
      string store_name_;
   public:
      GroceryTransaction();
      GroceryTransaction(string name, string t_date, int t_id, double t_amount,T_TransactionType t_type);
      virtual ~GroceryTransaction();

      string get_store_name() const;
      void set_store_name(string name);
      
      void increment_total_count();
      int get_total_count() const;

      void increment_total_amount(double amount);
      double get_total_amount() const;

      virtual void Display() const;
      virtual void DisplaySummary() const;
      virtual void EarnPoints();
};

class Customer {
   private: 
      string customer_name_;
      string credit_card_number_;
      double balance_;
      int reward_points_;
      Transaction * p_transaction[g_tSize];
   public:
      Customer();
      Customer(string name, string cc_number);
      ~Customer();
      
      void ReadTransactions();
      void ReportAllTransactions();
      void ReportRewardSummary(); 
};
int BankingTransaction::total_count_ = 0;
double BankingTransaction::total_amount_ = 0.0;
int DepartmentStoreTransaction::total_count_ = 0;
double DepartmentStoreTransaction::total_amount_ = 0.0;
int GroceryTransaction::total_count_ = 0;
double GroceryTransaction::total_amount_ = 0.0;

int main() {
   return 1;
}

/* class definitions */

//abstract class Transaction
Transaction::Transaction():transaction_date_(""), transaction_id_(0), transaction_amount_(0.0) {}
Transaction::Transaction(string t_date, int t_id, double t_amount,T_TransactionType t_type) : 
                        transaction_date_(t_date), transaction_id_(t_id), transaction_amount_(t_amount) {
                           set_transaction_type(t_type);
                        }
Transaction::~Transaction() { cout << "Transaction " << get_transaction_id() << " destroyed!" << endl; }

string Transaction::get_transaction_date() const {
   return transaction_date_;
}

void Transaction::set_transaction_date(string date) {
   transaction_date_ = date;
}

int Transaction::get_transaction_id() const {
   return transaction_id_;
}

void Transaction::set_transaction_id(int id) {
   transaction_id_ = id;
}

double Transaction::get_transaction_amount() const {
   return transaction_amount_;
}

void Transaction::set_transaction_amount(double amount) {
   transaction_amount_ = amount;
}

void Transaction::set_transaction_type(T_TransactionType type) {
   switch(type) {
      case D:
         t_type_ = "Department Store";
         break;
      case B:
         t_type_ = "Banking";
         break;
      case G:
         t_type_ = "Grocery Store";
         break;
      default:
         cout << "Invalid transaction type";
         break;
   }
}

string Transaction::get_transaction_type() const {
   return t_type_;
} 


//DepartmentStore derived class
DepartmentStoreTransaction::DepartmentStoreTransaction() : Transaction(), department_name_(""), return_policy_(0) {}
DepartmentStoreTransaction::DepartmentStoreTransaction(string name, int policy, string t_date,int t_id, double t_amount,T_TransactionType t_type) : 
                            Transaction(t_date,t_id,t_amount,t_type) {
                              set_department_name(name);
                              set_return_policy(policy);
                              increment_total_count();
                              increment_total_amount(t_amount);
                            }

DepartmentStoreTransaction::~DepartmentStoreTransaction() {}

string DepartmentStoreTransaction::get_department_name() const {
   return department_name_;
}

void DepartmentStoreTransaction::set_department_name(string name) {
   department_name_ = name;
}

int DepartmentStoreTransaction::get_return_policy() const {
   return return_policy_;
}

void DepartmentStoreTransaction::increment_total_count() {
   total_count_++;
}

int DepartmentStoreTransaction::get_total_count() const {
   return total_count_;
}

void DepartmentStoreTransaction::increment_total_amount(double amount) {
   total_amount_ += amount;
}

double DepartmentStoreTransaction::get_total_amount() const {
   return total_amount_;
}

void DepartmentStoreTransaction::set_return_policy(int days) {
   return_policy_ = days;
}

void DepartmentStoreTransaction::Display() const {
   cout << get_transaction_date() << get_transaction_type() << get_department_name() << get_return_policy() << get_transaction_amount() << endl; 
}

void DepartmentStoreTransaction::EarnPoints() {
  //add code later 
}

void DepartmentStoreTransaction::DisplaySummary()const  {
 //not sure if i'm keeping this method
}

//bank
BankingTransaction::BankingTransaction() : Transaction(), type_(""), fee_(0.0) {}
BankingTransaction::BankingTransaction(string type, double fee, string t_date, int t_id, double t_amount,T_TransactionType t_type) :
                    Transaction(t_date,t_id,t_amount,t_type) {
                      set_type(type);
                      set_fee(fee);
                      increment_total_count();
                      increment_total_amount(t_amount);
                    }
BankingTransaction::~BankingTransaction() {}

void BankingTransaction::set_type(string type) {
   type_ = type;
}

string BankingTransaction::get_type() const {
   return type_;
}  

void BankingTransaction::set_fee(double fee) {
   fee_ = fee;
}

double BankingTransaction::get_fee() const {
   return fee_;
}

void BankingTransaction::increment_total_count() {
   total_count_++;
}

int BankingTransaction::get_total_count() const {
   return total_count_;
}

void BankingTransaction::increment_total_amount(double amount) {
   total_amount_ += amount;
}

double BankingTransaction::get_total_amount() const {
   return total_amount_;
}

void BankingTransaction::Display() const{

}

void BankingTransaction::EarnPoints() {

}

void BankingTransaction::DisplaySummary() const {

}

//grocery
GroceryTransaction::GroceryTransaction() : Transaction(), store_name_("") {}
GroceryTransaction::GroceryTransaction(string name,string t_date, int t_id, double t_amount,T_TransactionType t_type) : 
                    Transaction(t_date,t_id,t_amount,t_type) {
                      set_store_name(name);
                      increment_total_count();
                      increment_total_amount(t_amount);
                    }
GroceryTransaction::~GroceryTransaction() {}

void GroceryTransaction::set_store_name(string name) {
   store_name_ = name;
}

string GroceryTransaction::get_store_name() const {
   return store_name_;
}  

void GroceryTransaction::increment_total_count() {
   total_count_++;
}

int GroceryTransaction::get_total_count() const {
   return total_count_;
}

void GroceryTransaction::increment_total_amount(double amount) {
   total_amount_ += amount;
}

double GroceryTransaction::get_total_amount() const {
   return total_amount_;
}

void GroceryTransaction::Display() const {

}

void GroceryTransaction::EarnPoints() {

}

void GroceryTransaction::DisplaySummary() const {

}
