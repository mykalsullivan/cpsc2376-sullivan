//
// Created by msullivan on 1/29/25.
//

#include <iostream>
#include <iomanip>
#include <fstream>

// Used to store the account balance and file I/O operations. I was originally going to separate I/O ops into its own
// class (and that would've been the better design choice), but I felt like being lazy.
class Account {
    float m_Balance;
    std::fstream m_File;
    bool m_Initialized;

public:
    explicit Account() : m_Balance(100.0f), m_Initialized(false)
    {}

    ~Account()
    {
        if (m_File.is_open()) m_File.close();
    }

    // Initializes the account; must be ran before operations can be performed
    bool init()
    {
        // Attempt to open account_balance.txt
        m_File.open("account_balance.txt", std::ios::in);

        if (m_File.is_open()) // Attempt to read balance from file
        {
            m_File >> m_Balance;

            if (m_File.fail())
            {
                std::cout << "Failed to read from 'account_balance.txt'\n";
                return false;
            }
            m_File.close();
        }
        else // File doesn't exist, so create with initial balance
        {
            m_File.open("account_balance.txt", std::ios::out);
            if (!m_File.is_open())
            {
                std::cout << "Failed to create 'account_balance.txt'\n";
                return false;
            }
            m_File << std::fixed << std::setprecision(2) << m_Balance;
            m_File.close();
        }

        // Open file for both reading and writing
        m_File.open("account_balance.txt", std::ios::in | std::ios::out);
        if (!m_File.is_open())
        {
            std::cout << "Failed to open 'account_balance.txt'\n";
            return false;
        }

        m_Initialized = true;
        return true;
    }

    // Adds an arbitrary amount to the account balance
    bool deposit(const float amount)
    {
        if (!m_Initialized || !m_File.is_open()) return false;

        m_Balance += amount;

        // Overwrite file with updated balance
        m_File.seekp(0);
        m_File << std::fixed << std::setprecision(2) << m_Balance;
        m_File.flush();

        m_File.close();
        return true;
    }

    // Removes an arbitrary amount from the account balance
    bool withdraw(const float amount)
    {
        if (!m_Initialized || !m_File.is_open()) return false;

        m_Balance -= amount;

        // Overwrite file with updated balance
        m_File.seekp(0);
        m_File << std::fixed << std::setprecision(2) << m_Balance;
        m_File.flush();

        return true;
    }

    // Retrieve current account balance in memory
    [[nodiscard]] float balance() const { return m_Balance; }

    // Set account balance to an arbitrary amount
    void setBalance(const float balance)
    {
        m_Balance = balance;
    }
};

class Application final {
    bool m_Running;
    Account m_Account;

public:
    Application() : m_Running(true)
    {}

    ~Application() = default;

    // Main program loop
    int exec()
    {
        std::cout << "*** Persistent Bank Account : by Mykal Sullivan ***\n";

        // Initialize account
        if (!m_Account.init())
        {
            std::cout << "Failed to initialize. Check file/directory permissions, then try again.\n";
            return -1;
        }

        // Main run loop
        while (m_Running)
        {
            // 1. Display menu
            std::cout << "Bank Menu\n";
            printFormattedLine("1", "Deposit");
            printFormattedLine("2", "Withdraw");
            printFormattedLine("3", "Balance");
            printFormattedLine("0", "Exit");

            // 2. Gather input
            int input {};
            bool flag {true};
            while (flag)
            {
                flag = false;

                // Prompt and validate input
                std::cout << ":: ";
                std::cin >> input;
                if (std::cin.fail() || input > 3 || input < 0)
                {
                    flag = true;
                    std::cin.clear();
                    std::cin.ignore();
                    std::cout << "Invalid selection.\n";
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
                std::cout << "Error: " << e.what() << '\n';
                return 1;
            }
            std::cout << std::endl;
        }
        return 0;
    }

private:
    void depositBalance()
    {
        // Retrieve and display balance
        checkBalance();

        float input {};
        bool flag {true};
        bool shouldDeposit {true};
        while (flag)
        {
            flag = false;

            // Gather and validate input
            std::cout << "Deposit amount [enter number less than 0 to cancel]: ";
            std::cin >> input;
            if (std::cin.fail())
            {
                flag = true;
                std::cin.clear();
                std::cin.ignore();
                std::cout << "Please enter a numeric value\n";
                continue;
            }

            // Check for cancelled transaction
            if (input < 0)
            {
                shouldDeposit = false;
                std::cout << "Transaction cancelled\n";
            }

            // Check for empty deposit
            if (input == 0)
            {
                shouldDeposit = false;
                std::cout << "Attempted to make an empty deposit\n";
            }
        }

        if (shouldDeposit)
        {
            if (m_Account.deposit(input))
            {
                printFormattedCurrency("Deposited", input);
                printFormattedCurrency("New balance", m_Account.balance());
            }
            else
            {
                std::cout << "Unknown deposit failure occurred.\n";
            }
        }
    }

    void withdrawBalance()
    {
        // Retrieve and display balance
        checkBalance();

        float input {};
        bool flag {true};
        bool shouldWithdraw {true};
        while (flag)
        {
            flag = false;

            // Gather and validate input
            std::cout << "Withdrawal amount [enter number less than 0 to cancel]: ";
            std::cin >> input;
            if (std::cin.fail())
            {
                flag = true;
                std::cin.clear();
                std::cin.ignore();
                std::cout << "Please enter a numeric value\n";
                continue;
            }

            // Check for cancelled transaction
            if (input < 0)
            {
                shouldWithdraw = false;
                std::cout << "Transaction cancelled.\n";
            }

            // Check for empty withdrawal
            if (input == 0)
            {
                shouldWithdraw = false;
                std::cout << "Attempted to make empty withdrawal.\n";
            }

            // Check for overwithdrawal
            static int overWithdrawalCount {0};
            if (input > m_Account.balance())
            {
                shouldWithdraw = false;
                overWithdrawalCount++;
                std::cout << "Attempted to withdraw more than account balance.\n";
                if (overWithdrawalCount > 2)
                    throw std::runtime_error("Just because you're poor doesn't mean you can steal from this financial institution.");
            }
        }

        if (shouldWithdraw)
        {
            if (m_Account.withdraw(input))
            {
                printFormattedCurrency("Withdrew", input);
                printFormattedCurrency("New balance", m_Account.balance());
            }
            else
            {
                std::cout << "Unknown withdrawal failure occurred.\n";
            }
        }
    }

    // Displays account balance
    void checkBalance() const
    {
        // Retrieve and display balance
        printFormattedCurrency("Balance", m_Account.balance());
    }

    // Ends run loop
    void exit()
    {
        m_Running = false;
    }

    // Prints a formatted line
    static void printFormattedLine(const std::string &beginText, const std::string &endText)
    {
        // Calculate dot fill width
        constexpr int totalDotWidth {64};
        const int dotsWidth = totalDotWidth - (static_cast<int>(beginText.length()) + static_cast<int>(endText.length()));

        // Print message
        std::cout << beginText << " :"
                  << std::setfill('.') << std::setw(dotsWidth + static_cast<int>(endText.length()))
                  << endText << '\n';
    }

    // Prints a formatted line (for currency)
    static void printFormattedCurrency(const std::string &text, const float balance)
    {
        std::stringstream ss;
        ss << '$' << std::fixed << std::setprecision(2) << balance;
        const std::string balanceStr = ss.str();

        // Calculate dot fill width
        constexpr int totalDotWidth {64};
        const int dotsWidth = totalDotWidth - (static_cast<int>(text.length()) + static_cast<int>(balanceStr.length()));

        // Print message
        std::cout << text << " :"
                  << std::setfill('.') << std::setw(dotsWidth + static_cast<int>(balanceStr.length()))
                  << balanceStr << '\n';
    }
};

int main()
{
    Application app;
    return app.exec();
}