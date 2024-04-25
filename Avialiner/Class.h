#pragma once
#ifndef ClassH
#define ClassH

#include <list>
#include "Pattern.h"
#include <string>

enum class LinerType : int // ��� �������
{
	��������,
	������������,
	Unknown = -1
};

enum class aviacompany : int // �������� �������� ��������
{
	��������,
	S7,
	������,
	Unknown = -1
};

enum class ManufacturedCompany : int // �������� �������������
{
	Airbus,
	Boeing,
	�����,
	Unknown = -1
};

//��������� ��������

class Avialiner // �������� ������������ �����
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

typedef Avialiner * LinerPtr; // ������ �� ������������ �����

// ����������� ������

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


// �������� ��� ������� ���������� 
class AirportIterator : public Iterator<LinerPtr> //�������� ��� ������� ����������
{
private:
	const LinerPtr* LinerPark;
	int Pos;
	int Count;
public:
	AirportIterator(const LinerPtr* linerPark, int count)
	{
		LinerPark = linerPark;
		Count = count;
		Pos = 0;
	}

	void First() { Pos = 0; }
	void Next() { Pos++; }
	bool IsDone() const { return Pos == Count; }
	LinerPtr GetCurrent() const { return LinerPark[Pos]; }
};

// ������ ���������(������ ������)

class Airport // ������ ���������
{
private:
	int avialinerCount;
	int MaxSize;
	LinerPtr* LinerPark;

public:
	Airport(int size);
	virtual ~Airport();
	void AddPlane(LinerPtr newLiner);
	int GetCount() const { return avialinerCount; }
	LinerPtr GetByIndex(int index) const { return LinerPark[index]; }

	Iterator<LinerPtr>* GetIterator()
	{
		return new AirportIterator(LinerPark, avialinerCount);
	}

};

// �������� ��� ������� ����������

class BigAirportIterator : public Iterator<LinerPtr>
{
private: 
	const list<LinerPtr>* LinerPark;
	list<LinerPtr>::const_iterator it;

public:
	BigAirportIterator(const list<LinerPtr>* linerPark)
	{
		LinerPark = linerPark;
		it = LinerPark->begin();
	}
	void First() { it = LinerPark->begin(); }
	void Next() { it++; }
	bool IsDone() const { return it == LinerPark->end(); }
	LinerPtr GetCurrent() const { return *it; }
};



//������ ���������(list), ���� �������� + �������� � ����

class BigAirport // ������ ���������
{
private:
	list<LinerPtr> LinerPark;

public:
	void AddPlane(LinerPtr newLiner) { LinerPark.push_back(newLiner); }
	int GetCount() const { return LinerPark.size(); }

	Iterator<LinerPtr>* GetIterator()
	{
		return new BigAirportIterator(&LinerPark);
	};
};


//����������

class AirportDecorator : public IteratorDecorator<LinerPtr>
{
private:

public:
	
};



#endif //ClassH