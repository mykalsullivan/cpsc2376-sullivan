//
// Created by msullivan on 1/29/25.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <memory>
#include <optional>

/*  Instructions:
    * Store the balance in a file named account_balance.txt.
    * On program startup:
    * If account_balance.txt does not exist, create it and set the initial balance to $100.00.
    * If the file exists, read the balance from the file.
    * Allow the user to perform the following actions:
        - Check the balance.
        - Deposit money (must be a positive amount).
        - Withdraw money (cannot exceed the balance or be negative).
        - Update account_balance.txt immediately after every transaction.

    Requirements:
    * Ensure file operations are handled securely and gracefully. For example:
        - If the file cannot be opened, display an appropriate error message and exit.
        - Validate all user inputs
            - Deposits must be positive values.
            - Withdrawals must not exceed the balance and must be positive values.
    * The program should be interactive, displaying a menu for the user to choose operations.
*/

class IOManager {
    std::fstream m_File;
    bool m_Initialized;

public:
    IOManager() : m_Initialized(false) {}

    ~IOManager()
    {
        if (m_File.is_open()) m_File.close();
    }

    // Initializes file input/output for account_balance.txt
    bool init()
    {
        m_File.open("account_balance.txt", std::ios::in | std::ios::out);
        if (!m_File) return false;

        // Set initialized flag
        m_Initialized = true;
        return true;
    }

    // Reads data from account_balance.txt
    std::optional<std::string> read()
    {
        if (!m_Initialized || !m_File.is_open() || m_File.fail()) [[unlikely]] return std::nullopt;
        std::string data;
        std::getline(m_File, data);
        return data;
    }

    // Writes data to account_balance.txt
    bool write(const std::string &data)
    {
        if (!m_Initialized || !m_File.is_open() || m_File.fail()) [[unlikely]] return false;
        m_File << data;
        return true;
    }

    // Truncates the contents of account_balance.txt (in case of errors)
    bool truncate()
    {
        if (!m_Initialized || !m_File.is_open() || m_File.fail()) [[unlikely]] return false;

        // Moving the pointer to the beginning of the file and closing it immediately clears the file contents
        m_File.seekp(0, std::ios::beg);
        m_File.close();

        // Open the file back up again.
        m_File.open("account_balance.txt", std::ios::in | std::ios::out);
        return true;
    }
};

class Account {
    float m_Balance;
    IOManager &m_IOManager;

public:
    explicit Account(IOManager &io) : m_Balance(100.0f), m_IOManager(io) {}
    ~Account() = default;

    bool deposit(const float amount)
    {
        m_Balance += amount;
        if (m_IOManager.write(std::to_string(amount))) [[likely]] return true;
        return false;
    }

    bool withdraw(const float amount)
    {
        m_Balance -= amount;
        if (m_IOManager.write(std::to_string(amount))) [[likely]] return true;
        return false;
    }

    [[nodiscard]] float balance() const { return m_Balance; }

    void setBalance(const float balance)
    {
        m_Balance = balance;
    }
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
        std::cout << "*** Persistent Bank Account : by Mykal Sullivan ***\n";

        // Set up the I/O manager
        {
            // Exit prematurely if the IO manager fails to initialize
            if (const int ioInitResult = m_IOManager->init(); !ioInitResult)
            {
                std::cout << "Error: Account balance file failed to initialize\n"
                             "Check file/directory permissions, then try again\n";
                return -1;
            }
            else
            {
                float fileBalance {};
                if (const auto fileBalanceStr = m_IOManager->read(); fileBalanceStr != std::nullopt)
                {
                    try
                    {
                        fileBalance = std::stof(fileBalanceStr.value());
                    }
                    catch (const std::invalid_argument &e)
                    {
                        std::cout << "Error: Failed to read account_balance.txt and must reset it\n";
                        fileBalance = 100.0f;
                        m_IOManager->truncate();
                    }
                }
                else
                {
                    fileBalance = 100.0f;
                    m_IOManager->write(std::to_string(fileBalance));
                }
                m_Account->setBalance(fileBalance);
            }
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
                    std::cout << "Invalid selection\n";
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
    void depositBalance() const
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

        // Deposit balance to account
        if (shouldDeposit)
        {
            if (m_Account->deposit(input))
            {
                printFormattedCurrency("Deposited", input);
                printFormattedCurrency("New balance", m_Account->balance());
            }
            else
            {

            }
        }
    }

    void withdrawBalance() const
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
            if (input > m_Account->balance())
            {
                shouldWithdraw = false;
                overWithdrawalCount++;
                std::cout << "Attempted to withdraw more than account balance.\n";
                if (overWithdrawalCount > 2)
                    throw std::runtime_error("Just because you're poor doesn't mean you can steal from this financial institution.");
            }
        }

        // Withdraw balance from account
        if (shouldWithdraw)
        {
            if (m_Account->withdraw(input))
            {
                printFormattedCurrency("Withdrew", input);
                printFormattedCurrency("New balance", m_Account->balance());
            }
            else
            {

            }
        }
    }

    void checkBalance() const
    {
        // Retrieve and display balance
        printFormattedCurrency("Balance", m_Account->balance());
    }

    void exit()
    {
        m_Running = false;
    }

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