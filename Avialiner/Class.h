#pragma once
#ifndef ClassH
#define ClassH

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
	void Repairing() { NeedRepair = false; }
	virtual void Takeoff() = 0;


};

typedef Avialiner* Liner;

class Airbus : public Avialiner
{
public:
	Airbus(aviacompany company, LinerType type) : Avialiner() { Company = company; Type = type; }
	void Takeoff() { wcout << "Самолет взлетел" << endl; };
};

class Boeing : public Avialiner
{
public:
	Boeing(aviacompany company, LinerType type) : Avialiner() { Company = company; Type = type; }
	void Takeoff() { wcout << "Самолет взлетел" << endl; };
};

class MC_21 : public Avialiner
{
public:
	MC_21(aviacompany company, LinerType type) : Avialiner() { Company = company; Type = type; }
	void Takeoff() { wcout << "Самолет взлетел" << endl; };
};

class Airport
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
	Liner GetByindex(int index) const { return LinerPark[index]; }

};




#endif //ClassH