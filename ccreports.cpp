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
      Transaction(string t_date, int t_id, double t_amount,string t_type);
      virtual bool operator==(const Transaction & transaction_to_compare) const;
      virtual ~Transaction();

      //getters/setters
      string get_transaction_date() const;
      void set_transaction_date(string date);

      int get_transaction_id() const;
      void set_transaction_id(int id);
      
      double get_transaction_amount() const;
      void set_transaction_amount(double amount);

      string get_transaction_type() const;
      void set_transaction_type(string type);

      //member functions
      virtual void Display() const = 0;
      virtual void DisplaySummary() const = 0;
      virtual int EarnPoints() = 0;
};

class DepartmentStoreTransaction : public Transaction {
   private:
      static int total_count_;
      static double total_amount_;
      string department_name_;
      int return_policy_;
   public:
      DepartmentStoreTransaction();
      DepartmentStoreTransaction(string name, int policy, string t_date, int t_id, double t_amount,string t_type);
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
      virtual int EarnPoints(); 
};

//derived classes from abstract class Transaction
class BankingTransaction : public Transaction {
   private:
      static int total_count_;
      static double total_amount_;
      static double total_fee_;
      string type_;
      double fee_;
   public:
      BankingTransaction();
      BankingTransaction(string type, double fee, string t_date, int t_id, double t_amount,string t_type);
      virtual ~BankingTransaction();
   
      string get_type() const;
      void set_type(string type);

      double get_fee() const;
      void set_fee(double fee);
      
      void increment_total_count();
      int get_total_count() const;

      void increment_total_amount(double amount);
      double get_total_amount() const;

      void increment_total_fee();
      double get_total_fee() const;

      virtual void Display() const; 
      virtual void DisplaySummary() const;
      virtual int EarnPoints();
};

class GroceryTransaction : public Transaction {
   private:
      static int total_count_;
      static double total_amount_;
      string store_name_;
   public:
      GroceryTransaction();
      GroceryTransaction(string name, string t_date, int t_id, double t_amount,string t_type);
      virtual ~GroceryTransaction();

      string get_store_name() const;
      void set_store_name(string name);
      
      void increment_total_count();
      int get_total_count() const;

      void increment_total_amount(double amount);
      double get_total_amount() const;

      virtual void Display() const;
      virtual void DisplaySummary() const;
      virtual int EarnPoints();
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
      
      string get_customer_name();
      void set_customer_name(string name);
      
      string get_customer_cnumber();
      void set_customer_cnumber(string creditnumber);
      
      double get_customer_balance();
      void set_customer_balance(double balance);
      
      int get_customer_points();
      void increment_customer_points(int value);
      
      void OutputRepeats();  
      void ReadTransactions();
      void ReportAllTransactions();
      void ReportRewardSummary(); 
};

int BankingTransaction::total_count_ = 0;
double BankingTransaction::total_amount_ = 0.0;
double BankingTransaction::total_fee_ = 0.0;
int DepartmentStoreTransaction::total_count_ = 0;
double DepartmentStoreTransaction::total_amount_ = 0.0;
int GroceryTransaction::total_count_ = 0;
double GroceryTransaction::total_amount_ = 0.0;

int main() {
   Customer * p_customer = new Customer("Lisa Kudrow", "3212123456781234");
   p_customer->ReadTransactions();
   p_customer->ReportAllTransactions();
   p_customer->ReportRewardSummary();
   //overloader test
   p_customer->OutputRepeats(); 
   delete p_customer;
   return 1;
}

/* class definitions */

//abstract class Transaction
Transaction::Transaction():transaction_date_(""), transaction_id_(0), transaction_amount_(0.0) {}
Transaction::Transaction(string t_date, int t_id, double t_amount,string t_type) : 
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

void Transaction::set_transaction_type(string type) {
   t_type_ = type;
}

string Transaction::get_transaction_type() const {
   return t_type_;
} 

bool Transaction::operator==(const Transaction & transaction_to_compare) const {
   return (get_transaction_date() == transaction_to_compare.get_transaction_date() && get_transaction_id() == transaction_to_compare.get_transaction_id());
}

//DepartmentStore derived class
DepartmentStoreTransaction::DepartmentStoreTransaction() : Transaction(), department_name_(""), return_policy_(0) {}
DepartmentStoreTransaction::DepartmentStoreTransaction(string name, int policy, string t_date,int t_id, double t_amount,string t_type) : 
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
   cout << get_transaction_date() << get_transaction_type() << get_department_name();
   cout << "Return in " <<  get_return_policy() << "days " << get_transaction_amount() << endl; 
}

int DepartmentStoreTransaction::EarnPoints() {
   const double department_points = 1.5;
   return total_amount_ * department_points;
}

void DepartmentStoreTransaction::DisplaySummary()const  {
 //not sure if i'm keeping this method
   cout << get_transaction_type() << setw(20) << get_total_count() << setw(20) << get_total_amount() << endl;
}

//bank
BankingTransaction::BankingTransaction() : Transaction(), type_(""), fee_(0.0) {}
BankingTransaction::BankingTransaction(string type, double fee, string t_date, int t_id, double t_amount,string t_type) :
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
   increment_total_fee();
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

void BankingTransaction::increment_total_fee() {
   total_fee_ += fee_;
}

double BankingTransaction::get_total_fee() const {
   return total_fee_;
}  

double BankingTransaction::get_total_amount() const {
   return total_amount_;
}

void BankingTransaction::Display() const{
   cout << get_transaction_date() << get_transaction_type() << get_type() << get_transaction_amount() << endl;
}

int BankingTransaction::EarnPoints() {
   return 0;
}

void BankingTransaction::DisplaySummary() const {
   cout << get_transaction_type() << setw(20) << get_total_count() << setw(20) << get_total_amount() << endl;
}

//grocery
GroceryTransaction::GroceryTransaction() : Transaction(), store_name_("") {}
GroceryTransaction::GroceryTransaction(string name,string t_date, int t_id, double t_amount,string t_type) : 
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
   cout << get_transaction_date() << get_transaction_type() << get_store_name()  << get_transaction_amount() << endl;
}

int GroceryTransaction::EarnPoints() {
   const double grocery_points = 2.5;
   return grocery_points * total_amount_;
}

void GroceryTransaction::DisplaySummary() const {
   cout << get_transaction_type() << setw(20) << get_total_count() << setw(20) << get_total_amount() << endl;
}

//Customer
Customer::Customer() : customer_name_(""), credit_card_number_(""), balance_(0.0), reward_points_(g_defaultRewardPoints),p_transaction() {}
Customer::Customer(string name, string ccnumber) : customer_name_(name), credit_card_number_(ccnumber), balance_(0.0), reward_points_(g_defaultRewardPoints), p_transaction() {}

Customer::~Customer(){
   for (int i = 0; i < g_tSize;i++) {
      if (p_transaction[i] != NULL) {
         delete p_transaction[i];
      }
   }
}

string Customer::get_customer_name() {
   return customer_name_;
}

void Customer::set_customer_name(string name) {
   customer_name_ = name;
}

string Customer::get_customer_cnumber() {
   return credit_card_number_;
}

void Customer::set_customer_cnumber(string creditnumber) {
   credit_card_number_ = creditnumber;
}

double Customer::get_customer_balance() {
   return balance_;
}

void Customer::set_customer_balance(double balance) {
   balance_ = balance;
}

int Customer::get_customer_points() {
   return reward_points_;
}

void Customer::increment_customer_points(int value) {

}

void Customer::ReadTransactions() {
   ifstream fin("transactions.txt");
   if (!fin) {
      cout << "Error: failed to open input file.\n";
      exit(-1);
   }
   //string t_date, int t_id, double t_amount,T_TransactionType t_type
   string date;
   int transaction_id;
   double transaction_amount;
   char type;
   int rpolicy;
   string name;
   double fee;
   string tType;
   string buffer;
   int i = 0;
   
   while (getline(fin,buffer,'~')) {
      type = buffer[0];
      getline(fin,buffer,'~');
      date = buffer;
      getline(fin,buffer,'~');
      transaction_id = atoi(buffer.c_str());
      getline(fin,buffer,'~');
      transaction_amount = atof(buffer.c_str());
      switch(type) {
         case 'D':
            getline(fin,buffer,'~');
            name = buffer;
            tType = "Department Store Transaction";
            getline(fin,buffer,'\n');
            rpolicy = atoi(buffer.c_str());
            p_transaction[i] = new DepartmentStoreTransaction(name,rpolicy,date,transaction_id,transaction_amount,tType);
            break;
         case 'B':
            getline(fin,buffer,'~');
            name = buffer;
            tType = "Banking Transaction";
            getline(fin,buffer,'\n');
            fee = atof(buffer.c_str());
            p_transaction[i] = new BankingTransaction(name,fee,date,transaction_id,transaction_amount,tType);
            break;
         default:
            getline(fin,buffer,'\n');
            name = buffer;
            tType = "Grocery Transaction";
            p_transaction[i] = new GroceryTransaction(name,date,transaction_id,transaction_amount,tType);
            break;
      }
      i++;
   } 
   fin.close();
}

void Customer::ReportAllTransactions() {
   BankingTransaction * p_bank = NULL;
   DepartmentStoreTransaction * p_department = NULL;
   GroceryTransaction * p_grocery = NULL;

   cout << setw(40) << "Transaction Listings" << endl;
   for (int i = 0; i < g_tSize; i++) {
      p_transaction[i]->Display();
      
      if (p_bank == NULL) {
         p_bank = dynamic_cast<BankingTransaction *>(p_transaction[i]);
      }

      if (p_department == NULL) {
         p_department = dynamic_cast<DepartmentStoreTransaction *>(p_transaction[i]);
      }
      
      if (p_grocery == NULL) {
         p_grocery = dynamic_cast<GroceryTransaction *>(p_transaction[i]);
      }
   }
   cout << "................................................................................................................................" << endl;
   double total_fee = p_bank->get_total_fee();
   cout << "Total fee charge from banking transactions: $" << total_fee << endl;
   double total = p_department->get_total_amount() + p_grocery->get_total_amount();
   double original_total = total;   
   total += total_fee;
   cout << "Total balance due (minus ATM withdrawals):   $" << total << endl; 
   cout << setw(40) << "Transaction Summary" << endl;
   cout << "Transaction Type" << setw(34) << "Transaction Count" << setw(20) << "Total Amount" << endl;
   cout << p_department->get_transaction_type() << setw(11) << p_department->get_total_count() << setw(25) << p_department->get_total_amount() << endl;
   cout << p_bank->get_transaction_type() << setw(20) << p_bank->get_total_count() << setw(25) << p_bank->get_total_amount() << endl;
   cout << p_grocery->get_transaction_type() << setw(20) << p_grocery->get_total_count() << setw(25) << p_grocery->get_total_amount() << endl;
   cout << "......................................................................................" << endl;
   cout << setw(40) << "$" << p_grocery->get_total_amount() + p_department->get_total_amount() + p_bank->get_total_amount() << endl;
}

void Customer::ReportRewardSummary() {
   DepartmentStoreTransaction transaction = DepartmentStoreTransaction();
   GroceryTransaction gtransaction =  GroceryTransaction();
   cout << "Rewards Summary for " << get_customer_name() << setw(20) << get_customer_cnumber() << endl;
   cout << setw(10) << "Previous points balance " << setw(20) << get_customer_points() << endl;
   cout << setw(10) << " + Department Store Purchaches: " << transaction.EarnPoints() << endl; 
   cout << setw(10) << " + Grocery Purchases: " << gtransaction.EarnPoints() << endl;
   cout <<"----------------------------------------------------------------------------------" << endl;
   cout << " = Total points for redemption \n";
   cout << get_customer_points() + gtransaction.EarnPoints() + transaction.EarnPoints() << endl;
}

void Customer::OutputRepeats() {
   for (int i = 0;i < g_tSize;i++) {
      for (int j = i+1; j < g_tSize;j++) {
         if (p_transaction[i] == p_transaction[j]) {
            cout << p_transaction[i]->get_transaction_date() << " " << p_transaction[i]->get_transaction_id() << endl;
            cout << "Repeat" << endl;
            cout << p_transaction[j]->get_transaction_date() << " " << p_transaction[j]->get_transaction_id() << endl;
         }
      }
   }
}

