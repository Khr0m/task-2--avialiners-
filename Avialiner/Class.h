#pragma once
#ifndef ClassH
#define ClassH

#include <list>
#include "Pattern.h"
#include <string>

enum class LinerType : int
{
	��������,
	������������,
	Unknown = -1
};

enum class aviacompany : int
{
	��������,
	S7,
	������,
	Unknown = -1
};

enum class ManufacturedCompany : int
{
	Airbus,
	Boeing,
	�����,
	Unknown = -1
};

//��������� ��������

class Avialiner
{
protected:
	bool NeedRepair; // ����� �� ������?
	bool InFly; // ��������� �� ������ � ������
	int Fuel; // �������
	int maxFuel; // ������������ �������
	aviacompany Company;// �������� ��������
	LinerType Type; // ��� ������� 
	int TakeoffSpeed; //�������� ������

	Avialiner();

public:
	bool IsNeedRepair() const {return NeedRepair;  }
	bool IsInFly() const { return InFly;  }
	int AmountOfFuel() const { return Fuel;  }
	int MaxAmountOfFuel() const { return maxFuel; }
	int WhichTakeoffSpeed() const { return TakeoffSpeed; }
	LinerType GetType() const { return Type; }
	aviacompany GetCompany() const { return Company;  }
	void Repairing() { NeedRepair = false; wcout << L"������� �������" << endl;}
	void FillUp(int fuel) { Fuel = fuel;  wcout << L"������� ��������� �� " << Fuel << L" ������" << endl; };
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
			wcout << "������� �������" << endl; 
		else wcout << "������� �� ����� ��������" << endl;
	};
	ManufacturedCompany GetManufCompany() const { return  ManufacturedCompany::Airbus; }
};

class Boeing737 : public Avialiner
{
public:
	Boeing737(aviacompany company, LinerType type, int takeoffSpeed) : Avialiner() { Company = company; Type = type; TakeoffSpeed = takeoffSpeed; }
	void Takeoff(int speed) {
		if ((AmountOfFuel() >= 0.8 * maxFuel) and (speed = TakeoffSpeed) and (IsNeedRepair()))
			wcout << "������� �������" << endl;
		else wcout << "������� �� ����� ��������" << endl;
	};
	ManufacturedCompany GetManufCompany() const { return  ManufacturedCompany::Boeing; }
};

class Superjet100 : public Avialiner
{
public:
	Superjet100(aviacompany company, LinerType type, int takeoffSpeed) : Avialiner() { Company = company; Type = type; TakeoffSpeed = takeoffSpeed; }
	void Takeoff(int speed) {
		if ((AmountOfFuel() >= 0.8 * maxFuel) and (speed = TakeoffSpeed) and (IsNeedRepair()))
			wcout << "������� �������" << endl;
		else wcout << "������� �� ����� ��������" << endl;
	};
	ManufacturedCompany GetManufCompany() const { return  ManufacturedCompany::�����; }
};



class AirportIterator : public Iterator<Liner> //�������� ��� ������� ����������
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



class Airport // ������ ���������
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
class BigAirport // ������ ���������
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