//
// Created by msullivan on 1/29/25.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <memory>

/*  Instructions:
    * Store the balance in a file named account_balance.txt.
    * On program startup:
    * If account_balance.txt does not exist, create it and set the initial balance to $100.00.
    * If the file exists, read the current balance from the file.
    * Allow the user to perform the following actions:
        - Check the balance.
        - Deposit money (must be a positive amount).
        - Withdraw money (cannot exceed the current balance or be negative).
        - Update account_balance.txt immediately after every transaction.

    Requirements:
    * Ensure file operations are handled securely and gracefully. For example:
        - If the file cannot be opened, display an appropriate error message and exit.
        - Validate all user inputs
            - Deposits must be positive values.
            - Withdrawals must not exceed the current balance and must be positive values.
    * The program should be interactive, displaying a menu for the user to choose operations.
*/

class IOManager {
    std::fstream m_File;

public:
    IOManager()
    {
        m_File.open("account_balance.txt");
    }

    ~IOManager()
    {
        if (m_File.is_open()) m_File.close();
    }

    int read()
    {
        if (!m_File.is_open() || m_File.fail()) [[unlikely]] return 1;

        return 0;
    }

    int write()
    {
        if (!m_File.is_open() || m_File.fail()) [[unlikely]] return 1;

        return 0;
    }
};

class Account {
    float m_Balance;
    IOManager &m_IOManager;

public:
    explicit Account(IOManager &io) : m_Balance(100.0f), m_IOManager(io) {}
    ~Account() = default;

    int deposit(const float amount)
    {
        m_Balance += amount;

        return 0;
    }

    int withdraw(const float amount)
    {
        m_Balance -= amount;

        return 0;
    }

    [[nodiscard]] float balance() const { return m_Balance; }
};

class Application final {
    bool m_Running;
    std::unique_ptr<IOManager> m_IOManager;
    std::unique_ptr<Account> m_Account;

public:
    Application() : m_Running(true),
                    m_IOManager(std::make_unique<IOManager>()),
                    m_Account(std::make_unique<Account>(*m_IOManager))
    {}

    ~Application() = default;

    int exec()
    {
        std::cout << "### Persistent Bank Account : by Mykal Sullivan ###\n";

        while (m_Running)
        {
            // 1. Display menu
            std::cout << "Options:\n";
            std::cout << "- 1:" << std::setw(32) << std::setfill('.') << std::right << "Deposit\n"
                      << "- 2:" << std::setw(32) << std::setfill('.') << std::right << "Withdraw\n"
                      << "- 3:" << std::setw(32) << std::setfill('.') << std::right << "Balance\n"
                      << "- 0:" << std::setw(32) << std::setfill('.') << std::right << "Exit\n";

            // 2. Gather input
            int input {};
            bool flag {true}; // Loop continues until user enters valid selection
            while (flag)
            {
                flag = false;

                std::cout << "-> ";
                try
                {
                    std::cin >> input;
                    std::cin.get();
                }
                catch (const std::exception &e)
                {
                    flag = true;
                    std::cout << "Please enter an integral value.\n";
                    continue;
                }

                if (input > 3 || input < 0)
                {
                    flag = true;
                    std::cout << "Invalid option.\n";
                }
            }

            // 3. Process input
            try
            {
                switch (input)
                {
                    case 0: exit(); break;
                    case 1: depositBalance(); break;
                    case 2: withdrawBalance(); break;
                    case 3: checkBalance(); break;
                    default: break;
                }
            }
            catch (const std::exception &e)
            {
                std::cout << "Oops: " << e.what() << "\n"
                             "Exiting.\n";
                return 1;
            }
        }
        return 0;
    }

private:
    void depositBalance()
    {
        // 0. Retrieve and display balance


        // 1. Prompt input


        // 2. Gather input


        // 3. Validate input


        // 4. Deposit balance to account


    }

    void withdrawBalance()
    {
        // 0. Retrieve and display balance


        // 1. Prompt input


        // 2. Gather input


        // 3. Validate input


        // 4. Withdraw balance from account
    }

    void checkBalance()
    {
        // Retrieve and display balance


    }

    void exit()
    {
        m_Running = false;
    }
};

int main()
{
    Application app;
    return app.exec();
}