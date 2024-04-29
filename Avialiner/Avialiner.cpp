// Avialiner.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

using namespace std;

#include "Class.h"
#include "Pattern.h"
#include <string>


Avialiner::Avialiner() // конструктор родительского класса
{
    if ((rand() % (100 - 0 + 1) + 0) < 87)
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
    LinerPark[avialinerCount] = NewLiner;
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

wstring PrintAviaCompany(const aviacompany company) //функция для определения компаниии производителя
{
    switch (company)
    {
    case aviacompany::Аэрофлот: return  L"Аэрофлот";
    case aviacompany::S7: return  L"S7";
    case aviacompany::Победа: return  L"Победа";
    default: return L"неизвестный";
    }
};

void ViewManufCompany(Iterator<LinerPtr> * it) // функция для вывода компании производителя
{
    int i = 0;
     
    for (it->First(); !it->IsDone(); it->Next())
    {
        
        const LinerPtr currentLiner = it->GetCurrent();
        i++;
        wcout << i << L" (" << PrintManufCompany(currentLiner->GetManufCompany()) << L")" << endl;
        
    
    }

}

void ViewCharacteristics(Iterator<LinerPtr>* it) // функция для вывода зарактеристик
{
    int i = 0;

    for (it->First(); !it->IsDone(); it->Next())
    {
        i++;
        const LinerPtr currentLiner = it->GetCurrent();

        wcout << i << L" (" << PrintManufCompany(currentLiner->GetManufCompany()) << L") ";
        wcout << L" (" << PrintAviaCompany(currentLiner->GetCompany()) << L") ";
        wcout << L" в баке (" << currentLiner->AmountOfFuel() << L") литров топлива ";
        if (currentLiner->IsNeedRepair() == 0)
        {
            wcout << L" (" << L"Ремонт не нужен" << L")" << endl;
        }
        else
        {
            wcout << L" (" << L"Ремонт нужен" << L")" << endl;
        }
       

    }
}

// Фабричный метод
Avialiner* CreateLiner(aviacompany company, LinerType type, int takeoffSpeed, ManufacturedCompany manufCompany) 
{
    switch (manufCompany)
    {
    case ManufacturedCompany::Airbus: return  new AirbusA320(company, type, takeoffSpeed);
    case ManufacturedCompany::Boeing: return  new Boeing737(company, type,  takeoffSpeed);
    case ManufacturedCompany::Сухой: return new Superjet100(company, type, takeoffSpeed);
    default: return NULL;
    }
}

Avialiner* Avialiner::Create(aviacompany company, LinerType type, int takeoffSpeed, ManufacturedCompany manufCompany)
{
    return CreateLiner(company, type, takeoffSpeed, manufCompany);
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int liner1 = rand() % (20 - 0 + 1) + 0;
    int liner2 = rand() % (20 - 0 + 1) + 0;
    int liner3 = rand() % (20 - 0 + 1) + 0;
    int liner4 = rand() % (20 - 0 + 1) + 0;

    Airport airportPark(liner1 + liner2 + liner3 + liner4); // создание контейнера первого типа

    //BigAirport airportPark; // создание контейнера вторго типа


    // добавление в контейнер самолетов
    for (int i = 0; i < liner1; i++)
    {
        //airportPark.AddPlane(new Boeing737(aviacompany::Аэрофлот, LinerType::пассажирский, 260)); 
        airportPark.AddPlane(CreateLiner(aviacompany::Аэрофлот, LinerType::пассажирский, 260, ManufacturedCompany::Boeing));
    }

    for (int i = 0; i < liner2; i++) // добавление в контейнер самолетов
    {
        //airportPark.AddPlane(new Boeing737(aviacompany::S7, LinerType::пассажирский, 260)); //создание объекта через его добавление
        airportPark.AddPlane(CreateLiner(aviacompany::S7, LinerType::пассажирский, 260, ManufacturedCompany::Boeing)); // создание объекта через фабричный метод

    }
    for (int i = 0; i < liner3; i++) // добавление в контейнер самолетов
    {
       // airportPark.AddPlane(new AirbusA320(aviacompany::S7, LinerType::пассажирский, 270));
        airportPark.AddPlane(CreateLiner(aviacompany::S7, LinerType::пассажирский, 270, ManufacturedCompany::Airbus));
    }
    for (int i = 0; i < liner4; i++) // добавление в контейнер самолетов
    {
        // airportPark.AddPlane(new Superjet100(aviacompany::Аэрофлот, LinerType::пассажирский, 270));
        airportPark.AddPlane(CreateLiner(aviacompany::Аэрофлот, LinerType::пассажирский, 230, ManufacturedCompany::Сухой));
    }

    
 
    
    Iterator<LinerPtr>* it = airportPark.GetIterator(); // создание итератора

    //wcout << L"Вывод компаний производителей самолетов" << endl;
   // ViewManufCompany(it);
    //wcout << endl << endl;
    wcout <<  L"Вывод всех лайнеров c их характеристиками" << endl;
    ViewCharacteristics(it);
    wcout << endl << endl;

    wcout << L"Вывод всех лайнеров компании S7, не нуждающиеся в ремонте и не в полете, с использованием декораторов" << endl;
    Iterator<LinerPtr>* decorIterator = new LinerNeedRepairIteratorDecorator(new LinerNotInFlyIteratorDecorator(new LinerCompany(airportPark.GetIterator(), aviacompany::S7), false), false);
    ViewCharacteristics(decorIterator);

    // удаление итераторов
    delete it;
    delete decorIterator;
    return 0;

    //wcout << L"да" << endl; // инструмент отладки

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
