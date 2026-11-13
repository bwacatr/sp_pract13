#include <iostream>
#include <locale>
#include <string>
#include <exception>
#include <Windows.h>
#include <cwchar>
#include <algorithm>
#include <conio.h>


struct Process
{
    PROCESS_INFORMATION piApp;
    DWORD priorityClass;
    DWORD exitCode;
    double seconds;

    std::string state = "Работает";
    std::string priorityName = "";
};

class ProcessRace
{
    int size = 0;

public:
    Process* processArray = nullptr;
    HANDLE* processHandles = nullptr;

    void UpdateState(bool isSuspended)
    {
        for (int i = 0; i < size; i++)
        {


            GetExitCodeProcess(processArray[i].piApp.hProcess, &processArray[i].exitCode);


            if (isSuspended)
            {
                processArray[i].state = "Ожидает запуска";
            }
            else if (processArray[i].exitCode == STILL_ACTIVE)
            {
                processArray[i].state = "Работает";

            }
            else
            {
                processArray[i].state = "Завершен";

            }
        }
    }

    void Info(bool isSuspended)
    {
        UpdatePriorityName();
        UpdateState(isSuspended);

        for (int i = 0; i < size; i++)
        {
            GetExitCodeProcess(processArray[i].piApp.hProcess, &processArray[i].exitCode);

            std::cout << i << " | ProcessID: " << processArray[i].piApp.dwProcessId << " | " << processArray[i].state << " | " << processArray[i].priorityName << " | " << processArray[i].exitCode << std::endl;

        }
    }

    void TimeInfo()
    {
        for (int i = 0; i < size; i++)
        {

            GetExitCodeProcess(processArray[i].piApp.hProcess, &processArray[i].exitCode);

            UpdatePriorityName();
            std::cout << i << " | ProcessID: " << processArray[i].piApp.dwProcessId << " | " << processArray[i].state << " | " << processArray[i].priorityName << " | Время в секундах: " << processArray[i].seconds << std::endl;

        }
    }

    void UpdatePriorityName()
    {
        if (processArray == nullptr) return;

        for (int i = 0; i < size; i++)
        {
            if (processArray[i].priorityClass == IDLE_PRIORITY_CLASS) processArray[i].priorityName = "IDLE";
            else if (processArray[i].priorityClass == BELOW_NORMAL_PRIORITY_CLASS) processArray[i].priorityName = "BELOW NORMAL";
            else if (processArray[i].priorityClass == NORMAL_PRIORITY_CLASS) processArray[i].priorityName = "NORMAL";
            else if (processArray[i].priorityClass == ABOVE_NORMAL_PRIORITY_CLASS) processArray[i].priorityName = "ABOVE NORMAL";
            else if (processArray[i].priorityClass == HIGH_PRIORITY_CLASS) processArray[i].priorityName = "HIGH";
        }
        
    }

    void AddProcess(Process& process)
    {
        if (processArray == nullptr)
        {
            processArray = new Process[1];
            processArray[0] = process;

            processHandles = new HANDLE[1];
            processHandles[0] = process.piApp.hProcess;


        }
        else 
        {
            Process* newArray = new Process[size + 1];
            HANDLE* newProcessHandles = new HANDLE[size + 1];

            for (int i = 0; i < size; i++)
            {
                newArray[i] = processArray[i];
                newProcessHandles[i] = processHandles[i];
            }

            newArray[size] = process;
            newProcessHandles[size] = process.piApp.hProcess;

            delete[] processArray;
            processArray = newArray;

            delete[] processHandles;
            processHandles = newProcessHandles;

        }
        size++;
    }

    ProcessRace()
    {

    }

    ~ProcessRace()
    {
        for (int i = 0; i < size; i++)
        {
            CloseHandle(processHandles[i]);
            CloseHandle(processArray[i].piApp.hThread);
        }

        delete[] processArray;
        delete[] processHandles;
    }

    void ChangePriority(int index)
    {

        if (index < 0 || index >= size)
        {
            return;
        }
        
            std::cout << "1 - IDLE_PRIORITY_CLASS\n2 - BELOW_NORMAL_PRIORITY_CLASS\n3 - NORMAL_PRIORITY_CLASS\n4 - ABOVE_NORMAL_PRIORITY_CLASS\n5 - HIGH_PRIORITY_CLASS\n" << std::endl;
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
                return;
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


            default:
                
                break;
            }

        

    }

    void Race()
    {

    }
};

int main()
{
    try
    {

   
        setlocale(LC_ALL, "Russian");
        std::wcout.imbue(std::locale(""));

        std::wstring executableName = L"Process.exe";
    

        Process process;
        ProcessRace race;

        std::cout << "Введите кол-во процессов от 2 до 5\n" << std::endl;

        std::string str;
        std::cin >> str;

        int processAmount;
        try
        {
            processAmount = std::stoi(str);
            if (processAmount < 2)
            {
                processAmount = 2;
            }
            else if (processAmount > 5)
            {
                processAmount = 5;
            }
        }
        catch (const std::exception&)
        {
            throw std::invalid_argument("Введен некорректный тип данных");
        }

        std::string params = "";

        std::cout << "Введите параметры через пробел \n(Пример: 0 405000)" << std::endl;
        std::cin.ignore();
        std::getline(std::cin, params);







        if (params.empty() == false)
        {
            std::wstring sParams(params.begin(), params.end());
            executableName += L" " + sParams;
        }

        std::wstring lpCL = executableName;

        for (int i = 0; i < processAmount; i++)
        {



            STARTUPINFO startUpInfo;
            PROCESS_INFORMATION piApp;
            ZeroMemory(&startUpInfo, sizeof(STARTUPINFO));
            startUpInfo.cb = sizeof(STARTUPINFO);

            


            if (CreateProcess(NULL, &lpCL[0], NULL, NULL, FALSE, CREATE_SUSPENDED | CREATE_NEW_CONSOLE, NULL, NULL, &startUpInfo, &piApp) == false)
            {
                throw std::runtime_error("Ошибка запуска процесса: " + std::to_string(GetLastError()));
            }

            SetProcessAffinityMask(piApp.hProcess, 1);

            
            process = { piApp, GetPriorityClass(piApp.hProcess)};
            race.AddProcess(process);

            
        }


        bool isSuspended = true;
        int index = 0;
        bool skip = false;
        while (skip == false)
        {
            Sleep(200);
            system("cls");


            if (race.processArray == nullptr)
            {
                std::cout << "\n\nПустой список" << std::endl;
            }
            else
            {
                race.Info(isSuspended);

            }


            std::cout << "\nВведите индекс процесса" << std::endl;
            if (isSuspended)
            {
                std::cout << "\nВведите 'r', чтобы запустить процессы" << std::endl;
            }

            int charCode;

            if (_kbhit())
            {
                charCode = _getch();

                if (charCode == 27 /*27 = ESC*/)
                {
                    skip = true;
                }
                else if (charCode >= '0' && charCode < '0' + processAmount)
                {
                    index = charCode - '0';
                    race.ChangePriority(index);
                }
                else if (charCode == 'r' || charCode == 'к')
                {
                    isSuspended = false;
                    for (int i = 0; i < processAmount; i++)
                    {
                        ResumeThread(race.processArray[i].piApp.hThread);
                    }
                }
            

                
            }

        

        

        
        }


        WaitForMultipleObjects(processAmount, race.processHandles, true, INFINITE);

        std::sort(race.processArray, race.processArray + processAmount, [](Process& a, Process& b) {return a.exitCode < b.exitCode; });

        for (int i = 0; i < processAmount; i++)
        {
            if (race.processArray[i].exitCode != 259)
            {
                double seconds = race.processArray[i].exitCode / 1000.0;
                race.processArray[i].seconds = seconds;
            }
            
        }

        race.TimeInfo();
        


     }
     catch (const std::exception& e)
     {
         std::cout << "\n\n" << e.what() << std::endl;
     }
}