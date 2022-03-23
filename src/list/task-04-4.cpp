#include <iostream>
#include <iomanip>
#include <list>
#include <algorithm>
#include <numeric>

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
    Account& operator*=(float factor);
    Account& operator* (float factor);
    int get_id(void) const { return id; }
    float get_balance(void) const { return balance; }
};

typedef std::list<Account> Container;


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

Account& Account::operator*=(float factor)
{
    balance *= factor;
    return *this;
}

Account& Account::operator*(float factor)
{
    balance *= factor;
    return *this;
}

Container::iterator find_account(Container& accounts)
{
    std::string input;
    std::cout << "Enter the ID of the account to find: ";
    getline(std::cin, input);
    int id = stoi(input);
    Container::iterator it;
    for (it = accounts.begin(); it != accounts.end(); ++it)
    {
        if (it->get_id() == id)
        {
            std::cout << "Found account: " << *it;
            break;
        }
    }
    if (it == accounts.end())
        std::cout << "Account not found.\n";

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
        std::cout << "6. Remove account\n";
        std::cout << "7. Show total balance for all accounts\n";
        std::cout << "8. Add a dividend to all accounts\n";
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
            std::for_each(accounts.begin(), accounts.end(), [](auto& it) { std::cout << it; });
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
                *it += deposit;
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
                *it -= withdrawal;
            }
            break;
        }

        case 4:
        {
            Account acc;
            acc.enter_information();
            accounts.push_back(acc);
            break;
        }

        case 5:
        {
            find_account(accounts);
            break;
        }

        case 6:
        {
            std::cout << "Enter account ID to remove: ";
            getline(std::cin, input);
            int id = stoi(input);
            auto new_end = std::remove_if(accounts.begin(), accounts.end(), [id](auto &it) { return it.get_id() == id; });
            if (new_end != accounts.end())
                accounts.erase(new_end, accounts.end());
            break;
        }

        case 7:
        {
            float total = std::accumulate(accounts.begin(), accounts.end(), 0.0f, [](auto acc, auto &it) { return acc + it.get_balance(); });
            std::cout << "Total in all accounts: $" << std::setprecision(2) << std::fixed << total << "\n";
            break;
        }

        case 8:
        {
            std::cout << "Enter the dividend as a percentage: ";
            getline(std::cin, input);
            float factor = 1.0 + (std::stof(input) / 100.0);
            //std::for_each(accounts.begin(), accounts.end(), [factor](auto &it){ it *= factor; });
            auto new_end = std::transform(accounts.begin(), accounts.end(), accounts.begin(), [factor](auto &it){ return it * factor; });
            if (new_end != accounts.end())
                accounts.erase(new_end, accounts.end());
            break;
        }

        default:
            std::cout << "Sorry, that option is not available.\n";
            break;
        }

    } while (choice != 0);
    
    return 0;
}
