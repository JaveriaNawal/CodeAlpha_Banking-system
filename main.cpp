#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

// Class to handle transactions
class Transaction {
private:
    string type;
    double amount;

public:
    Transaction(const string& t, double amt) : type(t), amount(amt) {}

    void showTransaction() const {
        cout << "Transaction: " << type << " | Amount: " << amount << endl;
    }
};

// Class to manage individual accounts
class Account {
private:
    string accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(const string& accNum, double initialBalance)
        : accountNumber(accNum), balance(initialBalance) {}

    string getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    void setAccountNumber(const string& newAccNum) {
        accountNumber = newAccNum;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            throw invalid_argument("Deposit amount must be greater than zero.");
        }
        balance += amount;
        transactions.emplace_back("Deposit", amount);
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            throw invalid_argument("Withdrawal amount must be greater than zero.");
        }
        if (amount > balance) {
            throw runtime_error("Insufficient balance.");
        }
        balance -= amount;
        transactions.emplace_back("Withdrawal", amount);
    }

    void showTransactions() const {
        cout << "Transactions for Account: " << accountNumber << endl;
        for (const auto& transaction : transactions) {
            transaction.showTransaction();
        }
    }
};

// Class to handle customer data and accounts
class Customer {
private:
    string name;
    string customerID;
    vector<Account> accounts;

public:
    Customer(const string& custName, const string& custID)
        : name(custName), customerID(custID) {}

    string getCustomerID() const {
        return customerID;
    }

    string getName() const {
        return name;
    }

    void setName(const string& newName) {
        name = newName;
    }

    void addAccount(const string& accNum, double initialBalance) {
        accounts.emplace_back(accNum, initialBalance);
        cout << "Account " << accNum << " created successfully!" << endl;
    }

    Account* findAccount(const string& accNum) {
        for (auto& account : accounts) {
            if (account.getAccountNumber() == accNum) {
                return &account;
            }
        }
        throw runtime_error("Account not found.");
    }

    void showAccounts() const {
        cout << "Customer: " << name << " | Customer ID: " << customerID << endl;
        for (const auto& account : accounts) {
            cout << "Account Number: " << account.getAccountNumber() << " | Balance: " << account.getBalance() << endl;
        }
    }

    void changeAccountNumber(const string& oldAccNum, const string& newAccNum) {
        Account* account = findAccount(oldAccNum);
        account->setAccountNumber(newAccNum);
        cout << "Account number updated successfully!" << endl;
    }
};

// Class to manage the overall banking service
class BankingService {
private:
    vector<Customer> customers;

public:
    void addCustomer(const string& custName, const string& custID) {
        customers.emplace_back(custName, custID);
        cout << "Customer " << custName << " added successfully!" << endl;
    }

    Customer* findCustomer(const string& custID) {
        for (auto& customer : customers) {
            if (customer.getCustomerID() == custID) {
                return &customer;
            }
        }
        throw runtime_error("Customer not found.");
    }

    void depositToAccount(const string& custID, const string& accNum, double amount) {
        Customer* customer = findCustomer(custID);
        Account* account = customer->findAccount(accNum);
        account->deposit(amount);
        cout << "Deposit successful!" << endl;
    }

    void withdrawFromAccount(const string& custID, const string& accNum, double amount) {
        Customer* customer = findCustomer(custID);
        Account* account = customer->findAccount(accNum);
        account->withdraw(amount);
        cout << "Withdrawal successful!" << endl;
    }

    void showCustomerAccounts(const string& custID) {
        Customer* customer = findCustomer(custID);
        customer->showAccounts();
    }

    void showAccountTransactions(const string& custID, const string& accNum) {
        Customer* customer = findCustomer(custID);
        Account* account = customer->findAccount(accNum);
        account->showTransactions();
    }

    void updateCustomerName(const string& custID, const string& newName) {
        Customer* customer = findCustomer(custID);
        customer->setName(newName);
        cout << "Customer name updated successfully!" << endl;
    }

    void updateAccountNumber(const string& custID, const string& oldAccNum, const string& newAccNum) {
        Customer* customer = findCustomer(custID);
        customer->changeAccountNumber(oldAccNum, newAccNum);
    }

    void run() {
        int choice;
        do {
            cout << "\n--- Banking System Menu ---\n";
            cout << "________________________________\n";
            cout << "1. Add Customer\n";
            cout << "2. Create Account\n";
            cout << "3. Deposit\n";
            cout << "4. Withdraw\n";
            cout << "5. Display Accounts\n";
            cout << "6. Display Transactions\n";
            cout << "7. Exit\n";
            cout << "________________________________\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    string custName, custID;
                    cout << "Enter customer name: ";
                    cin.ignore();
                    getline(cin, custName);
                    cout << "Enter customer ID: ";
                    getline(cin, custID);
                    addCustomer(custName, custID);
                    break;
                }
                case 2: {
                    string custID, accNum;
                    double initialBalance;
                    cout << "Enter customer ID: ";
                    cin.ignore();
                    getline(cin, custID);
                    cout << "Enter account number: ";
                    getline(cin, accNum);
                    cout << "Enter initial balance: ";
                    cin >> initialBalance;
                    findCustomer(custID)->addAccount(accNum, initialBalance);
                    break;
                }
                case 3: {
                    string custID, accNum;
                    double amount;
                    cout << "Enter customer ID: ";
                    cin.ignore();
                    getline(cin, custID);
                    cout << "Enter account number: ";
                    getline(cin, accNum);
                    cout << "Enter deposit amount: ";
                    cin >> amount;
                    depositToAccount(custID, accNum, amount);
                    break;
                }
                case 4: {
                    string custID, accNum;
                    double amount;
                    cout << "Enter customer ID: ";
                    cin.ignore();
                    getline(cin, custID);
                    cout << "Enter account number: ";
                    getline(cin, accNum);
                    cout << "Enter withdrawal amount: ";
                    cin >> amount;
                    withdrawFromAccount(custID, accNum, amount);
                    break;
                }
                case 5: {
                    string custID;
                    cout << "Enter customer ID: ";
                    cin.ignore();
                    getline(cin, custID);
                    showCustomerAccounts(custID);
                    break;
                }
                case 6: {
                    string custID, accNum;
                    cout << "Enter customer ID: ";
                    cin.ignore();
                    getline(cin, custID);
                    cout << "Enter account number: ";
                    getline(cin, accNum);
                    showAccountTransactions(custID, accNum);
                    break;
                }
                case 7:
                    cout << "Exiting system. Goodbye!" << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 9);
    }
};

int main() {
    BankingService bankService;
    bankService.run();
    return 0;
}
