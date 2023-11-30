#include "Parser.h"
#include"Rest/Restaurant.h"
Parser::Parser()
{

}


void Parser::setFileName(string fn)
{
	fileName = fn;
}

bool Parser::OpenFile(GUI* pGUI)
{
	pGUI->PrintMessage("Please enter File name you want to open = ");
	
	fileName = pGUI->GetString()+".txt";
	
	InFile.open(fileName, ios::in);
	if (InFile.is_open())
	{
		return true;
	}
	pGUI->PrintMessage("Cannot open the file..");
	return false;

}




void Parser::ReadFile(int& nN, int& nG, int& nV, int& sN_min,int& sN_max, int& sG_min,int& sG_max,int& sV_min,int& sV_max,int& bo, int& bN_min,int& bN_max, int& bG_min, int& bG_max,int& bV_min,int& bV_max,double & Inj_Prob, int & Rest_Prd, int& AutoP,int &VIP_WT, int& M, Restaurant* pRest)
{
	InFile >> nN >> nG >> nV; // number of normal/ vegan/ VIP cooks
	InFile >> sN_min >> sN_max >> sG_min>> sG_max>> sV_min>> sV_max; // speed of normal/ vegan/ VIP cooks
	InFile >> bo >> bN_min >> bN_max >> bG_min>> bG_max>> bV_min>>bV_max; // number of dishes before taking break/ break of normal/ vegan/ VIP cooks
	InFile >> Inj_Prob >> Rest_Prd;
	InFile >> AutoP>> VIP_WT; // limit for autopromotion
	InFile >> M; // number of events
	char evtype_line[25]; // event type whole line read once and then transformed into integers to be use as wrapper parameters
	//string evtype_line_str[10];
	int TS; //time step
	int id; // order id
	int money; // order paid money
	int size; // order size
	ORD_TYPE OT; //order type .. (enum)..parameter of arrival_event_constructor
	int check = 0;
	string type_ord;


	for (int i = 0; i < M; i++)// calls wrapper function of pRest which by its turn calls the events_constructors
	{
		InFile >> type_ord;
		if (type_ord == "R")
		{
			string evtype_line_str[10];
			 SplitString(evtype_line_str);
			
			if (evtype_line_str[0] == "N")
			{
				OT = TYPE_NRM;
			}
			else if (evtype_line_str[0] == "V")
			{
				OT = TYPE_VIP;
			}
			else if (evtype_line_str[0] == "G")
			{
				OT = TYPE_VGAN;
			}
			TS = stoi(evtype_line_str[1]); 
			id = stoi(evtype_line_str[2]);
			size = stoi(evtype_line_str[3]);
			money = stoi(evtype_line_str[4]);
			pRest->Wrapper_Arrival(OT, TS, id, size, money);

		}
		else if (type_ord == "P")
		{
			string evtype_line_str[10];
			SplitString(evtype_line_str);
			
			TS = stoi(evtype_line_str[0]);
			id = stoi(evtype_line_str[1]);
			money = stoi(evtype_line_str[2]);
			pRest->Wrapper_Promote(TS, id, money);

		}
		else if (type_ord == "X")
		{
			string evtype_line_str[10];
			SplitString(evtype_line_str);
			
			TS = stoi(evtype_line_str[0]);
			id = stoi(evtype_line_str[1]);
			pRest->Wrapper_Cancelation(TS, id);

		}
		
		
		
		
		
		
		
		
		
	}
	InFile.close();
}
void Parser::SplitString(string evtype_line_str[10])
{
	char evtype_line[25];
	//string evtype_line_str[10];
	int cnt = -1;
	InFile.getline(evtype_line, 25, '\n');
	for (int i = 0; i < strlen(evtype_line); i++)
	{
		if (evtype_line[i] != ' ' && evtype_line[i] != '\t')
		{
			evtype_line_str[cnt] += evtype_line[i];
		}
		else
		{
			cnt++;
		}

	}
	//return evtype_line_str;
}

//to output in File//
bool Parser::WriteFile(Order** finishorder, int count, int CookNCount, int CookVCount, int CookGCount, int NInjured, int NUrgent, int NAPromote, int TNOrder)
{
	string OName="Output-";
	OName.append(fileName);
	OName.append(".txt");

	OutFile.open(OName, ios::out);
	int NCount = 0, VCount = 0, GCount = 0;
	int TWaiting=0, TService=0;
	ORD_TYPE OType;
	if (OutFile.is_open())
	{
		OutFile << "FT	ID	AT	WT	ST " << endl;
		for (int i = 0; i < count; i++)
		{
			OutFile << finishorder[i]->getFinishTime() << '\t' << finishorder[i]->GetID() << '\t' << finishorder[i]->getArrTime() << '\t' << finishorder[i]->getWaitingTime() << '\t' << finishorder[i]->GetServTime()<<endl;
			OType = finishorder[i]->GetType();
			TWaiting = TWaiting + finishorder[i]->getWaitingTime();
			TService += finishorder[i]->GetServTime();

			switch (OType)
			{
			case TYPE_NRM :
				NCount++;
				break;
			case TYPE_VGAN:
				GCount++;
				break;
			case TYPE_VIP:
				VCount++;
				break;
			default:
				break;
			}
		}
		int TOrder = NCount + GCount + VCount;
		int TCook = CookNCount + CookVCount + CookGCount;
		float AvgService = (float)((float)TService / (float)TOrder);
		float AvgWaiting = (float)((float)TWaiting / (float)TOrder);
		float PercentAPromote = 0;
		if (TNOrder!=0)
			PercentAPromote = (float)((float)NAPromote / (float)TNOrder) * 100;
		
		PercentAPromote = (PercentAPromote == 0) ? 0: PercentAPromote;
		OutFile << "Orders: " << TOrder << "[Norm:" << NCount << ", Veg:" << GCount << ", VIP:" << VCount << "]" << endl;
		OutFile << "cooks: " << TCook << "[Norm:" << CookNCount << ", Veg:" << CookGCount << ", VIP:" << CookVCount <<", injured:" << NInjured << "]" << endl;
		OutFile << "Avg Wait = " << AvgWaiting  << ", Avg Serv = " << AvgService << endl;
		OutFile << "Urgent orders: " << NUrgent << ", Auto-promoted: " << PercentAPromote<< "%" << endl;
	
	}
	else
		return false;

	OutFile.close();


}
