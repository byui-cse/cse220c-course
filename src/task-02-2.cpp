#include <iostream>
#include <iomanip>

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
};

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


int main(int argc, char **argv)
{
    Account acc;
    acc.enter_information();
    std::cout << acc;

    return 0;
}
