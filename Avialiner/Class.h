#pragma once
#ifndef ClassH
#define ClassH

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

class Avialiner
{
protected:
	bool NeedRepair;
	bool InFly;
	int Fuel;
	int maxFuel;
	aviacompany Company;
	LinerType Type;

	Avialiner();

public:
	bool IsNeedRepair() const {return NeedRepair;  }
	bool IsInFly() const { return InFly;  }
	int AmountOfFuel() { return Fuel;  }
	int MaxAmountOfFuel() { return maxFuel; }
	LinerType GetType() const { return Type; }
	aviacompany GetCompany() const { return Company;  }
	virtual void Takeoff() = 0;


};

class Airbus : public Avialiner
{
public:
	Airbus(aviacompany company, LinerType type) : Avialiner() { Company = company; Type = type; }
	void Takeoff() { wcout << "������� �������" << endl; };
};

class Boeing : public Avialiner
{
public:
	Boeing(aviacompany company, LinerType type) : Avialiner() { Company = company; Type = type; }
	void Takeoff() { wcout << "������� �������" << endl; };
};

class MC_21 : public Avialiner
{
public:
	MC_21(aviacompany company, LinerType type) : Avialiner() { Company = company; Type = type; }
	void Takeoff() { wcout << "������� �������" << endl; };
};






#endif //ClassH