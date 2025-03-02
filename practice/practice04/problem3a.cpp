//
// Created by msullivan on 2/26/25.
//

#include "Input.h"
#include <iostream>
#include <list>

struct Task {
    std::string title;
    std::string description;
};

class Application {
    bool m_Running {false};
    std::list<Task> m_Tasks;

public:
    Application() = default;
    ~Application() = default;

    int exec()
    {
        std::cout << "Simple Task Manager by M. Sullivan\n";

        m_Running = true;
        while (m_Running)
        {
            std::string prompt = "1: Add task\n2: Remove task\n3: View tasks\n4: Exit\nWhich one?";
            handleAction(Input::numberPrompt(prompt, 1, 3, false));
        }
        return 0;
    }

private:
    void handleAction(const int action)
    {
        switch (action)
        {
            case 1: addTask(); break;
            case 2: removeTask(); break;
            case 3: showTasks(true); break;
            case 4: stop(); break;
            default:
                std::cout << "Invalid selection\n"; break;
        }
    }

    void addTask()
    {
        Task newTask;
        newTask.title = Input::textPrompt("Title", 0, 64, true);
        newTask.description = Input::textPrompt("Description", 0, 500, true);
        m_Tasks.emplace_back(newTask);
    }

    void removeTask()
    {
        showTasks(false);

        std::string prompt {"Select which one to remove (-1 to cancel)"};
        const int selection = Input::numberPrompt(prompt, -1, static_cast<int>(m_Tasks.size()), true);

        // Entering -1 cancels the operation
        if (selection < 0) return;

        // Remove an item
        auto it = m_Tasks.begin();
        std::advance(it, selection);
        m_Tasks.erase(it);
        std::cout << "Removed task " << std::to_string(selection) << '\n';
    }

    void showTasks(const bool withDescription)
    {
        static int i = 1;
        for (const auto &[title, description] : m_Tasks)
        {
            std::cout << std::to_string(i) << ": \"" << title << "\"\n";
            if (withDescription) std::cout << "\t- " << description << '\n';
            ++i;
        }
    }

    void stop()
    {
        m_Running = false;
    }
};

int main()
{
    Application app;
    return app.exec();
}