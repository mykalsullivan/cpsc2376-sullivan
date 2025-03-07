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
            handleAction(Input::numberPrompt(prompt, 1, 4, false));
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
                std::cout << "Invalid selection.\n"; break;
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
        // Return if the task list is empty
        if (m_Tasks.empty())
        {
            std::cout << "No tasks.\n";
            return;
        }

        // Display short list of tasks on the list
        showTasks(false);

        const std::string prompt {"Select which one to remove (0 to cancel)"};
        const int selection = Input::numberPrompt(prompt, 0, static_cast<int>(m_Tasks.size()), true);

        // Entering 0 cancels the operation
        if (selection == 0) return;

        if (selection > static_cast<int>(m_Tasks.size()))
        {
            std::cout << "Invalid selection.\n";
            return;
        }

        // Remove an item
        const auto it = std::next(m_Tasks.begin(), selection - 1);
        m_Tasks.erase(it);
        std::cout << "Removed task " << selection << ".\n";
    }

    void showTasks(const bool withDescription)
    {
        // Return if the task list is empty
        if (m_Tasks.empty())
        {
            std::cout << "No tasks.\n";
            return;
        }

        int i = 1;
        for (const auto &[title, description] : m_Tasks)
        {
            std::cout << i << ": \"" << title << "\"\n";
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