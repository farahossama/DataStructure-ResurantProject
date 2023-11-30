#pragma once

#include "..\Defs.h"
#include"Order.h"
#pragma once
class Cook
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding type (VIP, Normal, Vegan)
	int Speed;		//dishes it can prepare in one clock tick (in one timestep)
	int Dishes_break;     // number of orders that he must finish before break
	//int To_break;  // an indicator that indicates the nuber of dishes left to have a break // we do not need it
	int Inbreak;     // break period in timesteps
	int Not_Available; // number of timesteps after which the cook will be available

	Order* pOrd;   // pointer to the order assigned to this cook
	bool Injured;  //to indicate the condition of the cook
	int Restperiod; // time needed for the injured cook to take rest
public:
	Cook();

	Cook(int id, ORD_TYPE tp, int spd, int dsh_brk, int inbrk,int rest_prd);
	
	virtual ~Cook();
	int GetID() const;
	ORD_TYPE GetType() const;
	void setID(int);
	void setType(ORD_TYPE) ;
	
	void setSpeed(int s);
	void setDishes_break(int db);
	void setInbreak(int ib);
	//void setTo_break(int tobrk);

	//int GetTo_break();
	int GetSpeed();
	int GetDishes_break();
	int GetInbreak();

	void setNot_Available(int nav); // will be used in phase 2 to be an indicator whether the cook is available or not
	int getNot_Available();

	void setOrd(Order* po);
	Order* getOrd();

	void setInjured(bool inj);
	bool isInjured();
	
	void setRest(int r);
	int getRest();
	
	int Calculate_Priority();
};
