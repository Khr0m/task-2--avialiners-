// Avialiner.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

using namespace std;

#include "Class.h""
#include "Pattern.h"
#include <string>

Avialiner::Avialiner() // конструктор родительского класса
{
    if ((rand() % (100 - 0 + 1) + 100) < 87)
        NeedRepair = false;
    else NeedRepair = true;
   InFly = false;
    Fuel = 0;
    Company = aviacompany::Unknown;
    Type = LinerType::Unknown;
}

Airport::Airport(int maxSize) // конструктор контейнера
{
    LinerPark = new LinerPtr[maxSize];
    for (int i = 0; i < maxSize; i++)
    {
        LinerPark[i] = NULL;
    }
    avialinerCount = 0;
    MaxSize = maxSize;
}

Airport::~Airport() // деструктор контейнера
{
    for (int i = 0; i < MaxSize; i++)
    {
        if (LinerPark[i] != NULL)
        {
            delete LinerPark[i];
            LinerPark[i] = NULL;
        }
    }
    delete[] LinerPark;
}

void Airport::AddPlane(LinerPtr NewLiner) // добавление лайнера в контейнер
{
    LinerPark[avialinerCount++] = NewLiner;
    avialinerCount++;
}

wstring PrintManufCompany(const ManufacturedCompany company) //функция для определения компаниии производителя
{
    switch (company)
    {
    case ManufacturedCompany::Airbus: return  L"Airbus";
    case ManufacturedCompany::Boeing: return  L"Boeing";
    case ManufacturedCompany::Сухой: return  L"Сухой";
    default: return L"неизвестный";
    }
};

void vivod(Iterator<LinerPtr> * it) // функция для вывода компании производителя
{
     
    for (it->First(); !it->IsDone(); it->Next())
    {
        
        const LinerPtr currentLiner = it->GetCurrent();
        wcout << L" (" << PrintManufCompany(currentLiner->GetManufCompany()) << L")" << endl;// ошибка памяти, при использовании 1 контейнера
    
    }

}


int main()
{
    setlocale(LC_ALL, "Russian");

    Airport airportPark(7); // создание первого контейнера

    //BigAirport airportPark;

    for (int i = 0; i < 5; i++) // добавление в контейнер самолетов
    {
        airportPark.AddPlane(new Boeing737(aviacompany::Аэрофлот, LinerType::пассажирский, 260)); 
       
        
        //const Liner currentLiner = airportPark.GetByIndex(i);
        //wcout << currentLiner->MaxAmountOfFuel() << endl;
    }

    for (int i = 0; i < 2; i++) // добавление в контейнер самолетов
    {
        airportPark.AddPlane(new Boeing737(aviacompany::S7, LinerType::пассажирский, 260));

    }
    
 
    
    Iterator<LinerPtr>* it = airportPark.GetIterator(); // создание итератора
    vivod(it);// пытаюсь вывести компанию производитель, не работает
    //wcout << L"да" << endl;

    delete it;
    return 0;

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
