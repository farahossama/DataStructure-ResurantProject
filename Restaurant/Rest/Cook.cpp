#include "Cook.h"


Cook::Cook()
{
}


Cook::~Cook()
{
}


int Cook::GetID() const
{
	return ID;
}


ORD_TYPE Cook::GetType() const
{
	return type;
}


void Cook::setID(int id)
{
	ID = id;
}

void Cook::setType(ORD_TYPE t)
{
	type = t;
}
void Cook::setDishes_break(int db) // dishes break can be a negative value if the cook had finished the required amount of orders but taken from his break/ rest due to urgent orders
{
	
		Dishes_break = db;
	
}
int Cook::GetDishes_break()
{
	return Dishes_break;
}
void Cook::setSpeed(int s)
{
	if (s > 0)
	{
		Speed = s;
	}
}
int Cook::GetSpeed()
{
	return Speed;
}
void Cook::setInbreak(int ib)
{
	if (ib > 0)
	{
		Inbreak = ib;
	}
}
int Cook::GetInbreak()
{
	return Inbreak;
}
Cook::Cook(int id, ORD_TYPE tp, int spd, int dsh_brk, int inbrk, int rest_prd)
{
	setID(id);
	setType(tp);
	setSpeed(spd);
	setDishes_break(dsh_brk);
	setInbreak(inbrk);
	setRest(rest_prd);
	Not_Available = 0; // a cook should be initially available
	pOrd = nullptr; // initially an order is not assigned yet
	Injured = false; // initially a cook is not injured
	//setTo_break(dsh_brk);// initially the to_break is equal to dish_break because the cook did not work yet
}
void Cook::setNot_Available(int nav)
{
	if (nav >= 0)
	{
		Not_Available = nav;
	}
}
int Cook::getNot_Available()
{
	return Not_Available;
}
void Cook::setOrd(Order* po)
{
	pOrd = po;
}
Order* Cook::getOrd()
{
	return pOrd;
}
void Cook::setInjured(bool inj)
{
	Injured = inj;
}
bool Cook::isInjured()
{
	return Injured;
}
void Cook::setRest(int r)
{
	if (r > 0)
	{
		Restperiod = r;
	}
}
int Cook::getRest()
{
	return Restperiod;
}
int Cook::Calculate_Priority()
{
	// speed multiplied by 10 to maximize its load in setting the priority then we substract from it the break period
	int priority;
	priority=(Speed * 10) - Inbreak;
	return priority;
}
/*void Cook::setTo_break(int tobrk)
{
	if (tobrk > 0)
	{
		To_break = tobrk;
	}
}

int Cook::GetTo_break()
{
	return To_break;
}*/