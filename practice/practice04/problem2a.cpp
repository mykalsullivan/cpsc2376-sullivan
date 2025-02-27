//
// Created by msullivan on 2/26/25.
//

class Application {
    bool m_Running {false};

public:
    Application() = default;
    ~Application() = default;

    int exec()
    {

    }

    void stop()
    {
        m_Running = false;
    }
};

int main()
{

    return 0;
}