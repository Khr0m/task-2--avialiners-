// Avialiner.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

using namespace std;

#include "Class.h""
#include "Pattern.h"
#include <string>

Avialiner::Avialiner()
{
    if ((rand() % (100 - 0 + 1) + 100) < 87)
        NeedRepair = false;
    else NeedRepair = true;
   InFly = false;
    Fuel = 0;
    Company = aviacompany::Unknown;
    Type = LinerType::Unknown;
}

Airport::Airport(int maxSize)
{
    LinerPark = new Liner[maxSize];
    for (int i = 0; i < maxSize; i++)
    {
        LinerPark[i] = NULL;
    }
    avialinerCount = 0;
    MaxSize = maxSize;
}

Airport::~Airport()
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

void Airport::AddPlane(Liner NewLiner)
{
    LinerPark[avialinerCount++] = NewLiner;
    avialinerCount++;
}

wstring PrintManufCompany(const ManufacturedCompany company)
{
    switch (company)
    {
    case ManufacturedCompany::Airbus: return  L"Airbus";
    case ManufacturedCompany::Boeing: return  L"Boeing";
    case ManufacturedCompany::Сухой: return  L"Сухой";
    default: return L"неизвестный";
    }
};

void vivod(Iterator<Liner> * it)
{
    
    for (it->First(); !it->IsDone(); it->Next())
    {
        
        const Liner currentLiner = it->GetCurrent();
        wcout << L" (" << PrintManufCompany(currentLiner->GetManufCompany()) << L")" << endl;
    
    }

}


int main()
{
    setlocale(LC_ALL, "Russian");

    Airport airportPark(5);

    for (int i = 0; i < 5; i++)
    {
        airportPark.AddPlane(new Boeing737(aviacompany::Аэрофлот, LinerType::пассажирский, 260));
        
        //const Liner currentLiner = airportPark.GetByIndex(i);
        //wcout << currentLiner->MaxAmountOfFuel() << endl;
    }
    
 
    
    Iterator<Liner>* it = airportPark.GetIterator();
    vivod(it);
    //wcout << L"да" << endl;

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
