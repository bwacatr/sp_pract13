// Process.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <string>

bool CheckPrimeNum(int num)
{
    
    if (num < 2)
    {
        return false;
    }

    for (int i = 2; i <= num/i; i++)
    {
        if (num % i == 0)
        {
            return false;
        }
    }

    return true;
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");

    LARGE_INTEGER start, end, frequency;
    int elapsed_ms;

    int count = 0;

    QueryPerformanceFrequency(&frequency);

    QueryPerformanceCounter(&start);


    if (argc < 3)
    {
        return -1;
    }

    int a = 0;
    int b = 500000000;

    try
    {
        a = std::stoi(argv[1]);
        b = std::stoi(argv[2]);
    }
    catch (const std::exception&)
    {
        std::cout << "Ошибка: были введены не целые числа";
    }


    int num1 = min(a, b);
    int num2 = max(a, b);

    for (int i = num1; i <= num2; i++)
    {
        if (CheckPrimeNum(i))
        {
            count++;
            std::cout << i << " -> " << count << std::endl;
            
        }
    }

    QueryPerformanceCounter(&end);

    elapsed_ms = (end.QuadPart - start.QuadPart) * 1000 / frequency.QuadPart;

    std::cout << "Время в миллисекундах: " << elapsed_ms;

    return elapsed_ms; //должен выйти в exitCode


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
