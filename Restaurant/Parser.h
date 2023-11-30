

#pragma once
#include"GUI/GUI.h"
//#include"Rest/Restaurant.h"
#include"Defs.h"
#include <fstream>
#include"Events/Event.h"
#include<string>
//// The main purpose of this class is to maintain program modularity and maintainability
//// If we change the input way , this is the only class to be modified
//// As the restaurant class will be based on a single type of inputs
class Restaurant;
class Parser
{
private:
	ifstream InFile;
	ofstream OutFile;
	string fileName;

public:
	Parser();
	void setFileName(string fn);
	bool OpenFile(GUI* pGUI);
	void ReadFile(int& nN, int& nG, int& nV, int& sN_min, int& sN_max, int& sG_min, int& sG_max, int& sV_min, int& sV_max, int& bo, int& bN_min, int& bN_max, int& bG_min, int& bG_max, int& bV_min, int& bV_max, double& Inj_Prob, int& Rest_Prd, int& AutoP, int& VIP_WT, int& M, Restaurant* pRest);
	void SplitString(string arr[10]);
	bool WriteFile(Order** finishorder,int count,int CookNCount,int CookVCount,int CookGCount,int NInjured, int NUrgent, int NAPromote,int TNOrder);
};

