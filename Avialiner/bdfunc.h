#pragma once
#ifndef bdfuncH
#define bdfuncH

#include <string>
#include "Class.h"
#include "sqlite3.h"

// описание всех функций для контейнера и итератора под бд

BDAirport::BDAirport()
{
    sqlite3* LinerPark;
	int openResult = sqlite3_open16(L"C:\\Users\\khrom\\Desktop\\языки\\Avialiner\\Avialiner\\avialinerbd.db", &LinerPark);
    if (openResult != SQLITE_OK){wcout << L"Ошибка открытия бд" << endl;}

    char* errmsg;
    int createBD = sqlite3_exec(LinerPark, "DROP TABLE IF EXISTS avialiners; CREATE TABLE avialiners (ManufCompany int, Company int, Type int, TakeoffSpeed int); DELETE FROM avialiners", NULL, NULL, &errmsg); 
    if (createBD != SQLITE_OK){wcout << errmsg << endl; wcout << L"Ошибка создания бд" << endl;}

}

BDAirport::~BDAirport()
{
    sqlite3* LinerPark;
    int openResult = sqlite3_open16(L"C:\\Users\\khrom\\Desktop\\языки\\Avialiner\\Avialiner\\avialinerbd.db", &LinerPark);
    if (openResult != SQLITE_OK) { wcout << L"Ошибка открытия бд при удалении данных" << endl; }


    char* errmsg;
    int deleteBD = sqlite3_exec(LinerPark, "DROP TABLE IF EXISTS avialiners;", NULL, NULL, &errmsg);
    //wcout << L"да" << endl;
    if (deleteBD != SQLITE_OK) { wcout << errmsg << endl; wcout << L"Ошибка удаления бд" << endl; }
    sqlite3_close(LinerPark);
}

void BDAirport::AddPlane(LinerPtr newLiner)
{
    sqlite3* LinerPark;
    int openResult = sqlite3_open16(L"C:\\Users\\khrom\\Desktop\\языки\\Avialiner\\Avialiner\\avialinerbd.db", &LinerPark);
    if (openResult != SQLITE_OK) { wcout << L"Ошибка открытия бд при добавлении самолета" << endl; }

    char* errmsg;
    int addPlane = sqlite3_exec( LinerPark, string("INSERT INTO avialiners (ManufCompany, Company, Type, TakeoffSpeed) VALUES (" + to_string(static_cast<int> (newLiner->GetManufCompany())) + string(", ")\
        + to_string(static_cast<int>(newLiner->GetCompany())) + string(", ") + to_string(static_cast<int>(newLiner->GetType())) + string(", ") + to_string(newLiner->WhichTakeoffSpeed())\
        + string(")")).c_str(), NULL, NULL, &errmsg); 

    if (addPlane != SQLITE_OK) { wcout << errmsg << endl; wcout << L"Ошибка добавления записи" << endl; }

}

int BDAirport::GetCount() const
{
    sqlite3* LinerPark;
    int openResult = sqlite3_open16(L"C:\\Users\\khrom\\Desktop\\языки\\Avialiner\\Avialiner\\avialinerbd.db", &LinerPark);
    if (openResult != SQLITE_OK) { wcout << L"Ошибка открытия бд при подсчете количества" << endl; }

    int count = 0;
    sqlite3_stmt* pStatement;
    int createGetCount = sqlite3_prepare_v2(LinerPark, "SELECT COUNT (*) FROM avialiners", -1, &pStatement, NULL);
    if(createGetCount != SQLITE_OK)
    { 
        const char* errmsg = sqlite3_errmsg(LinerPark);
        wcout << errmsg << endl; 
        wcout << L"Ошибка подсчета количества" << endl;
    }

    int getCount = sqlite3_step(pStatement);
    if (getCount == SQLITE_ROW)
    {
        count = sqlite3_column_int(pStatement, 0);
        
    }
    else
    {
        const char* errmsg = sqlite3_errmsg(LinerPark);
        wcout <<  errmsg << endl;  
        wcout << L"Ошибка подсчета количества 2" << endl;
    }
    sqlite3_finalize(pStatement);
    return count;
}

bool BDAirporttIterator::IsDone() const
{
    sqlite3* LinerPark;
    int openResult = sqlite3_open16(L"C:\\Users\\khrom\\Desktop\\языки\\Avialiner\\Avialiner\\avialinerbd.db", &LinerPark);
    if (openResult != SQLITE_OK) { wcout << L"Ошибка открытия бд при проверке конца выполнения" << endl; }

    sqlite3_stmt* pStatement;
    int createGetCount = sqlite3_prepare_v2(LinerPark, "SELECT COUNT(*) FROM avialiners;", -1, &pStatement, NULL);
    if (createGetCount != SQLITE_OK)
    {
        wcout << L"Ошибка проверки конца выполнения" << endl;
        const char* errmsg2 = sqlite3_errmsg(LinerPark);
        wcout << errmsg2 << endl;
        
    }

    int planeCount = 0;
    int getCount = sqlite3_step(pStatement);
    if (getCount == SQLITE_ROW)
    {
        planeCount = sqlite3_column_int(pStatement, 0);
    }
    else
    {
        wcout << L"Ошибка проверки конца выполнения 2" << endl;
        const char* errmsg1 = sqlite3_errmsg(LinerPark);
        wcout << errmsg1 << endl;
        
    }

    sqlite3_finalize(pStatement);
    return Pos == planeCount;
}


LinerPtr BDAirporttIterator::GetCurrent() const
{
    sqlite3* LinerPark;
    int openResult = sqlite3_open16(L"C:\\Users\\khrom\\Desktop\\языки\\Avialiner\\Avialiner\\avialinerbd.db", &LinerPark);
    if (openResult != SQLITE_OK) { wcout << L"Ошибка открытия бд при выборке текущего самолета" << endl; }


    sqlite3_stmt* pStatement;
    //int prep1 = sqlite3_prepar
    int prep = sqlite3_prepare(LinerPark, string("SELECT ManufCompany, Company, Type, TakeoffSpeed, rowid FROM avialiners WHERE rowid = " + to_string(Pos)).c_str(), -1, &pStatement, NULL);
    //cout << string("SELECT ManufCompany, Company, Type, TakeoffSpeed FROM avialiners WHERE rowid = " + to_string(Pos)).c_str();
    if (prep != SQLITE_OK)
    {
        wcout << L"Ошибка позиционирования" << endl;
        string err = sqlite3_errstr(prep);
        cout << err << endl;
        //int err1 = sqlite3_errcode(LinerPark);
       // cout << err1 << endl;
        const char* errmsg = sqlite3_errmsg(LinerPark);
        wcout << errmsg << endl;
        
    }

    int stepRes = SQLITE_DONE;
    while (true)
    {
        int stepRes = sqlite3_step(pStatement);
        if (stepRes != SQLITE_ROW) { sqlite3_finalize(pStatement); break; }
        //sqlite3_finalize(pStatement);

        ManufacturedCompany manufCompany = ManufacturedCompany(sqlite3_column_int(pStatement, 0));
        //sqlite3_finalize(pStatement);

        aviacompany company = aviacompany(sqlite3_column_int(pStatement, 1));
        LinerType type = LinerType(sqlite3_column_int(pStatement, 2));
        int takeoffspeed = sqlite3_column_int(pStatement, 3);

        sqlite3_finalize(pStatement);

        switch (manufCompany)
        {
        case ManufacturedCompany::Airbus: return new AirbusA320(company, type, takeoffspeed);
        case ManufacturedCompany::Boeing: return new Boeing737(company, type, takeoffspeed);
        case ManufacturedCompany::Сухой: return new Superjet100(company, type, takeoffspeed);
        }

        //sqlite3_finalize(pStatement);
    }
    //sqlite3_finalize(pStatement);

}


#endif //bd functions