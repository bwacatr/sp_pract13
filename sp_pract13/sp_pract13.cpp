// sp_pract13.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <locale>
#include <string>
#include <exception>
#include <Windows.h>
#include <cwchar>

struct Process
{
    PROCESS_INFORMATION piApp;
    DWORD priorityClass;
    DWORD exitCode;
};

class ProcessRace
{
    int size = 0;

public:
    Process* processArray = new Process[1];

    ProcessRace(int num)
    {
        size = num;

        delete[] processArray;
        processArray = new Process[size];
    }

    void ChangePriority(int index)
    {
        bool skip = false;
        while (skip = false)
        {
            std::cout << "1 - IDLE_PRIORITY_CLASS\n2 - BELOW_NORMAL_PRIORITY_CLASS\n3 - NORMAL_PRIORITY_CLASS\n4 - ABOVE_NORMAL_PRIORITY_CLASS\n5 - HIGH_PRIORITY_CLASS\n6 - REALTIME_PRIORITY_CLASS" << std::endl;
            std::string str;
            std::cin >> str;

            int choice;
            try
            {
                choice = std::stoi(str);
            }
            catch (const std::exception&)
            {
                throw std::invalid_argument("Введен некорректный тип данных");
            }


            switch (choice)
            {
            case 1:
                SetPriorityClass(processArray[index].piApp.hProcess, IDLE_PRIORITY_CLASS);
                processArray[index].priorityClass = IDLE_PRIORITY_CLASS;
                break;
            case 2:
                SetPriorityClass(processArray[index].piApp.hProcess, BELOW_NORMAL_PRIORITY_CLASS);
                processArray[index].priorityClass = BELOW_NORMAL_PRIORITY_CLASS;
                break;
            case 3:
                SetPriorityClass(processArray[index].piApp.hProcess, NORMAL_PRIORITY_CLASS);
                processArray[index].priorityClass = NORMAL_PRIORITY_CLASS;
                break;
            case 4:
                SetPriorityClass(processArray[index].piApp.hProcess, ABOVE_NORMAL_PRIORITY_CLASS);
                processArray[index].priorityClass = ABOVE_NORMAL_PRIORITY_CLASS;
                break;
            case 5:
                SetPriorityClass(processArray[index].piApp.hProcess, HIGH_PRIORITY_CLASS);
                processArray[index].priorityClass = HIGH_PRIORITY_CLASS;
                break;
            case 6:
                SetPriorityClass(processArray[index].piApp.hProcess, REALTIME_PRIORITY_CLASS);
                processArray[index].priorityClass = REALTIME_PRIORITY_CLASS;
                break;

            default:
                skip = true;
                break;
            }
            
        }
        
    }

    void Race()
    {

    }
};

int main()
{
    std::cout << "Hello World!\n";
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
