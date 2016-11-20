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
typedef enum { D, B, G } T_DepartmentTypes;

class Transaction {
   private:
      int count_;
   protected:
      string transaction_date_;
      int transaction_id_;
      double transaction_amount_;
   public:
      Transaction();
      Transaction(string t_date, int t_id, double t_amount);
      virtual ~Transaction();

      //getters/setters
      string get_transaction_date() const;
      void set_transaction_date(string date);

      int get_transaction_id() const;
      void set_transaction_id(int id);

      double get_transaction_amount() const;
      void set_transaction_amount(double amount);

      int get_total_count() const;
      void set_total_count();

      //member functions
      virtual void Display() const = 0;
      virtual void EarnPoints() = 0;
};

class DepartmentStoreTransaction : public Transaction {
   private:
      string department_name_;
      int return_policy_;
   public:
      DepartmentStoreTransaction();
      DepartmentStoreTransaction(string name, int policy, string t_date, int t_id, double t_amount);
      ~DepartmentStoreTransaction();
      
      //getters/setters
      string get_department_name() const;
      void set_department_name();
   
      int get_return_policy() const;
      void set_return_policy();

      //member functions
      virtual void Display();
      virtual void EarnPoints(); 
};

class BankingTransaction : public Transaction {
   private:
      string type_;
      double fee_;
   public:
      BankingTransaction();
      BankingTransaction(string type, double fee, string t_date, int t_id, double t_amount);
      ~BankingTransaction();
   
      string get_type() const;
      void set_type(string type);

      double get_fee() const;
      void set_fee();

      virtual void Display();
      virtual void EarnPoints();
};

class GroceryTransaction : public Transaction {
   private:
      string store_name_;
   public:
      GroceryTransaction();
      GroceryTransaction(string name, string t_date, int t_id, double t_amount);
      ~GroceryTransaction();

      string get_store_name() const;
      void set_store_name(string name);

      virtual void Display();
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

int main() {
   return 1;
}
