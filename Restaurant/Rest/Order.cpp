#include "Order.h"
#include "..\Rest\Restaurant.h"


Order::Order(int id, ORD_TYPE r_Type)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	status = WAIT;
}

Order::Order(int id, ORD_TYPE r_Type, int size, double tMoney,int ATime)
{
	ID = (id > 0 && id < 1000) ? id : 0;	//1<ID<999
	type = r_Type;
	status = WAIT;
	Size = size;
	totalMoney = tMoney;
	ArrTime = ATime;
//	FinishTime = 20;
	WaitingTime = 0; // initially the order's waiting time is equal to zero

}


Order::~Order()
{
}

int Order::GetID()
{
	return ID;
}


ORD_TYPE Order::GetType() const
{
	return type;
}


void Order::SetDistance(int d)
{
	Distance = d>0?d:0;
}

int Order::GetDistance() const
{
	return Distance;
}


void Order::setStatus(ORD_STATUS s)
{
	status = s;
}

ORD_STATUS Order::getStatus() const
{
	return status;
}

void Order::setType(ORD_TYPE t)
{
	type = t;
}

void Order::SetServTime(int time)
{
	ServTime = time;
}


int Order::GetServTime()
{
	return ServTime;
}
void Order::setSize(int s)
{
	if (s > 0)
	{
		Size = s;
	}
}
int Order::getSize() const
{
	return Size;
}

void Order::settotalmoney(double m)
{
	if (m > 0)
	{
		totalMoney = m;
	}
}
double Order::gettotalmoney() const
{
	return totalMoney;
}

void Order::setArrTime(int time)
{
	if (time > 0)
	{
		ArrTime = time;
    }
}
int Order::getArrTime() const
{
	return ArrTime;
}

void Order::CalcFinishTime()
{
	
	FinishTime = ArrTime + WaitingTime + ServTime;
	
}
int Order::getFinishTime() const
{
	return FinishTime;
}

void Order::setWaitingTime(int time)
{
	//WaitingTime = FinishTime - ArrTime - ServTime;
	if (time >= 0)
	{
		WaitingTime = time;
	}
}

int Order::getWaitingTime()
{
	return WaitingTime;
}

int Order::Calculate_Priority()
{
	// (totalmoney/size)* arrivaltime
	int priority;
	priority = (totalMoney / Size)*ArrTime;
	return priority;
}