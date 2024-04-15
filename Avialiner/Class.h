#pragma once
#ifndef ClassH
#define ClassH

#include <list>
#include "Pattern.h"
#include <string>

enum class LinerType : int
{
	грузовой,
	пассажирский,
	Unknown = -1
};

enum class aviacompany : int
{
	Аэрофлот,
	S7,
	Победа,
	Unknown = -1
};

enum class ManufacturedCompany : int
{
	Airbus,
	Boeing,
	Сухой,
	Unknown = -1
};

//семейство объектов

class Avialiner
{
protected:
	bool NeedRepair; // нужел ди ремонт?
	bool InFly; // находится ли лайнер в полете
	int Fuel; // топливо
	int maxFuel; // максимальное топливо
	aviacompany Company;// компания владелец
	LinerType Type; // тип лайнера 
	int TakeoffSpeed; //скорость взлета

	Avialiner();

public:
	bool IsNeedRepair() const {return NeedRepair;  }
	bool IsInFly() const { return InFly;  }
	int AmountOfFuel() const { return Fuel;  }
	int MaxAmountOfFuel() const { return maxFuel; }
	int WhichTakeoffSpeed() const { return TakeoffSpeed; }
	LinerType GetType() const { return Type; }
	aviacompany GetCompany() const { return Company;  }
	void Repairing() { NeedRepair = false; wcout << L"Самолет починен" << endl;}
	void FillUp(int fuel) { Fuel = fuel;  wcout << L"Самолет заправлен на " << Fuel << L" литров" << endl; };
	virtual void Takeoff(int Speed) = 0;
	virtual  ManufacturedCompany GetManufCompany() const = 0;


};

typedef Avialiner * Liner;

class AirbusA320 : public Avialiner
{
public:
	AirbusA320(aviacompany company, LinerType type, int takeoffSpeed) : Avialiner() { Company = company; Type = type; TakeoffSpeed = takeoffSpeed;  }
	void Takeoff(int speed) { 
		if((AmountOfFuel() >= 0.8 * maxFuel) and (speed = TakeoffSpeed) and (IsNeedRepair()))
			wcout << "Самолет взлетел" << endl; 
		else wcout << "Самолет не может взлететь" << endl;
	};
	ManufacturedCompany GetManufCompany() const { return  ManufacturedCompany::Airbus; }
};

class Boeing737 : public Avialiner
{
public:
	Boeing737(aviacompany company, LinerType type, int takeoffSpeed) : Avialiner() { Company = company; Type = type; TakeoffSpeed = takeoffSpeed; }
	void Takeoff(int speed) {
		if ((AmountOfFuel() >= 0.8 * maxFuel) and (speed = TakeoffSpeed) and (IsNeedRepair()))
			wcout << "Самолет взлетел" << endl;
		else wcout << "Самолет не может взлететь" << endl;
	};
	ManufacturedCompany GetManufCompany() const { return  ManufacturedCompany::Boeing; }
};

class Superjet100 : public Avialiner
{
public:
	Superjet100(aviacompany company, LinerType type, int takeoffSpeed) : Avialiner() { Company = company; Type = type; TakeoffSpeed = takeoffSpeed; }
	void Takeoff(int speed) {
		if ((AmountOfFuel() >= 0.8 * maxFuel) and (speed = TakeoffSpeed) and (IsNeedRepair()))
			wcout << "Самолет взлетел" << endl;
		else wcout << "Самолет не может взлететь" << endl;
	};
	ManufacturedCompany GetManufCompany() const { return  ManufacturedCompany::Сухой; }
};



class AirportIterator : public Iterator<Liner> //Итератор для первого контейнера
{
private:
	const Liner* LinerPark;
	int Pos;
	int Count;
public:
	AirportIterator(const Liner* linerPark, int count)
	{
		LinerPark = linerPark;
		Count = count;
		Pos = 0;
	}

	void First() { Pos = 0; }
	void Next() { Pos++; }
	bool IsDone() const { return Pos != Count; }
	Liner GetCurrent() const { return LinerPark[Pos]; }
};



class Airport // первый контейнер
{
private:
	int avialinerCount;
	int MaxSize;
	Liner* LinerPark;

public:
	Airport(int size);
	virtual ~Airport();
	void AddPlane(Liner NewLiner);
	int GetCount() const { return avialinerCount; }
	Liner GetByIndex(int index) const { return LinerPark[index]; }

	Iterator<Liner>* GetIterator()
	{
		return new AirportIterator(LinerPark, avialinerCount);
	}

};

/*
class BigAirport // второй контейнер
{
private:
	list<Liner> LinerPark;

public:
	void AddPlane(Liner NewLiner) { LinerPark.push_back(NewLiner); }
	int GetCount() const { return LinerPark.size(); }

	Iterator<Liner>* GetIterator()
	{
		//return new BigAirport(&LinerPark);
	};
};

*/


#endif //ClassH