#include <iostream>
#include <iomanip>
#include <map>

class Account
{
protected:
    int id;
    std::string name;
    float balance;
    static int next_id;

public:
    Account(void);
    Account(const Account& source);
    ~Account(void);
    void enter_information(void);
    std::ostream& output(std::ostream& os) const;
    Account& operator+=(float deposit);
    Account& operator-=(float withdrawal);
    int get_id(void) const { return id; }
};

typedef std::map<int, Account> Container;


std::ostream& operator<<(std::ostream& os, const Account& acc)
{
    return acc.output(os);
}

int Account::next_id = 0;

Account::Account(void) : id(0), balance(0)
{
}

Account::Account(const Account& source) : id(source.id), name(source.name), balance(source.balance) 
{
}

Account::~Account(void)
{
}

void Account::enter_information(void)
{
    id = next_id++;
    std::cout << "Enter the name: ";
    std::getline(std::cin, name);
    std::string input;
    std::cout << "Enter the balance: ";
    std::getline(std::cin, input);
    balance = std::stof(input);
}

std::ostream& Account::output(std::ostream &os) const
{
    os << "Account ID: " << id << "  Name: " << name << "  Balance: $" << std::fixed << std::setprecision(2) << balance << std::endl;
    return os;
}

Account& Account::operator+=(float deposit)
{
    balance += deposit;
    return *this;
}

Account& Account::operator-=(float withdrawal)
{
    balance -= withdrawal;
    return *this;
}

Container::iterator find_account(Container& accounts)
{
    std::string input;
    std::cout << "Enter the ID of the account to find: ";
    getline(std::cin, input);
    int id = stoi(input);
    auto it = accounts.find(id);
    if (it == accounts.end())
        std::cout << "Account not found.\n";
    else
        std::cout << "Found account: " << it->second;
    return it;
}


int main(int argc, char **argv)
{
    Container accounts;

    int choice = 0;
    do {
        std::cout << "\n";
        std::cout << "Account Menu:\n";
        std::cout << "0. Quit Program\n";
        std::cout << "1. Display Account Information\n";
        std::cout << "2. Add a deposit to an account\n";
        std::cout << "3. Withdraw from an account\n";
        std::cout << "4. Add new account\n";
        std::cout << "5. Find account by ID\n";
        std::cout << "Your choice: ";
        std::string input;
        getline(std::cin, input);
        choice = std::stoi(input);
        switch(choice)
        {
        case 0:
            break;

        case 1:
        {
            for (auto it = accounts.begin(); it != accounts.end(); ++it)
            {
                std::cout << it->second;
            }
            break;
        }

        case 2:
        {
            auto it = find_account(accounts);
            if (it != accounts.end())
            {
                std::cout << "Amount to deposit: ";
                getline(std::cin, input);
                float deposit = std::stof(input);
                it->second += deposit;
            }
            break;
        }
        
        case 3:
        {
            auto it = find_account(accounts);
            if (it != accounts.end())
            {
                std::cout << "Amount to withdraw: ";
                getline(std::cin, input);
                float withdrawal = std::stof(input);
                it->second -= withdrawal;
            }
            break;
        }

        case 4:
        {
            Account acc;
            acc.enter_information();
            accounts[acc.get_id()] = acc;
            break;
        }

        case 5:
        {
            find_account(accounts);
            break;
        }

        default:
            std::cout << "Sorry, that option is not available.\n";
            break;
        }

    } while (choice != 0);
    
    return 0;
}
