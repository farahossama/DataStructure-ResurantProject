#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;
#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include "..\Events\CancelEvent.h"
#include"..\Events\PromotionEvent.h"
#include"..\Parser.h"


Restaurant::Restaurant() 
{
	pGUI = NULL;
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		//Simple_Interactive_Simulator();
		Modes_Simulator(MODE_INTR);
		break;
	case MODE_STEP:
		Modes_Simulator(MODE_STEP);
		break;
	case MODE_SLNT:
		Modes_Simulator(MODE_SLNT);
		break;
	case MODE_DEMO:
		Just_A_Demo();

	};

}



//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current timestep
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}


//Wrapper function for arrival event
void Restaurant::Wrapper_Arrival(ORD_TYPE& r_Type, int& TS, int& id, int& size, int& mony)
{
	Event* pE;
	pE = new ArrivalEvent(TS, id, r_Type, mony, size);
	EventsQueue.enqueue(pE);
}

// Wrapper function for cancel event
void Restaurant::Wrapper_Cancelation(int& TS, int& id)
{
	Event* pE;
	pE = new CancelEvent(TS, id);
	EventsQueue.enqueue(pE);
}

// Wrapper function promotion event
void Restaurant::Wrapper_Promote(int& TS, int& id, int& exmony)
{
	Event* pE;
	pE = new PromotionEvent(TS,id,exmony);
	EventsQueue.enqueue(pE);
}



Restaurant::~Restaurant()
{
		if (pGUI)
			delete pGUI;
}

void Restaurant::FillDrawingList()
{
	//This function should be implemented in phase1
	//It should add ALL orders and Cooks to the drawing list
	//It should get orders from orders lists/queues/stacks/whatever (same for Cooks)
	//To add orders it should call function  void GUI::AddToDrawingList(Order* pOrd);
	//To add Cooks it should call function  void GUI::AddToDrawingList(Cook* pCc);
	int size = 0;
	Cook** pCook;

	pCook= Cook_V_Q.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pGUI->AddToDrawingList(pCook[i]);
	}
	
	pCook = Cook_N_Q.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pGUI->AddToDrawingList(pCook[i]);
	}
	pCook = Cook_G_Q.toArray(size); // inside the "toArray" fn it initiates size =0 by itself
	                                       // no need to make another counter to avoid problems in array dimension
	for (int i = 0; i < size; i++)
	{
		pGUI->AddToDrawingList(pCook[i]);
	}
	
	
	//// it loops on each array look for the available cooks and draw them..
	//// all cooks in those arrays are not busy (cooks from the queues are the available ones )
	//// all busy cooks(in break or have orders) are stored in the linked bag .

	Order** pOrder;

	pOrder= VIPOrder_Q.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pGUI->AddToDrawingList(pOrder[i]);
	}

	/*pOrder = Waiting_VIP_L.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pGUI->AddToDrawingList(pOrder[i]);
	}*/
    
	pOrder = VeganOrder_Q.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pGUI->AddToDrawingList(pOrder[i]);
	}

	/*pOrder = Waiting_Vegan_L.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pGUI->AddToDrawingList(pOrder[i]);
	}*/
	
	pOrder = NormalOrder_L.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pGUI->AddToDrawingList(pOrder[i]);
	}
	/*pOrder = Waiting_Normal_L.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pGUI->AddToDrawingList(pOrder[i]);
	}*/
	pOrder = In_Service_Orders_B.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pGUI->AddToDrawingList(pOrder[i]);
	}

	pOrder = Finished_Orders_L.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pGUI->AddToDrawingList(pOrder[i]);
	}
}

 
//to delete any order  will technically do the same in each type
bool Restaurant::DeleteOrder(int ID)
{
	Order* pOrder = NormalOrder_L.GetOrderFromID(ID);     //to look for the Order to be deleted
	if (pOrder)
	{
		ORD_STATUS status = pOrder->getStatus();

		if (status == WAIT)
			return NormalOrder_L.DeleteNode(pOrder); // To delete the Order (esm funny keda)

	}
	return false;
}


//Adding order to a queue
void Restaurant::AddtoQueue(Order* pOrder)
{
	ORD_TYPE type = pOrder->GetType();
	

	switch (type)
	{
	case TYPE_NRM:

		NormalOrder_L.InsertEnd(pOrder);

		break;

	case TYPE_VGAN:

		VeganOrder_Q.enqueue(pOrder);

		break;

	case TYPE_VIP:
		    
			VIPOrder_Q.enqueue(pOrder);
	
		break;

	default:

		return ;

	}
	
}


void Restaurant:: PromoteOrder(int ID)
{
	Order* pOrder = NormalOrder_L.GetOrderFromID(ID);
	if (pOrder)
	{
		Order* TempOrder = pOrder;
		pOrder->setType(TYPE_VIP);
		AddtoQueue(pOrder);
		bool deleted = NormalOrder_L.DeleteNode(TempOrder);

	}
		
		
	
	                  
}


//////////////////////////////////////////////////////////////////////////////////////////////
/// ==> 
///  DEMO-related functions. Should be removed in phases 1&2

//Begin of DEMO-related functions

//This is just a demo function for project introductory phase
//It should be removed starting phase 1
void Restaurant::Just_A_Demo()
{
	
	//
	// THIS IS JUST A DEMO FUNCTION
	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2
	
	int EventCnt;	
	Order* pOrd;
	Event* pEv;
	srand(time(NULL));

	pGUI->PrintMessage("Just a Demo. Enter EVENTS Count(next phases should read I/P filename):");
	EventCnt = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer

	pGUI->PrintMessage("Generating Events randomly... In next phases, Events should be loaded from a file...CLICK to continue");
	pGUI->waitForClick();
		
	//Just for sake of demo, generate some cooks and add them to the drawing list
	//In next phases, Cooks info should be loaded from input file
	int C_count = 12;	
	Cook *pC = new Cook[C_count];
	int cID = 1;

	for(int i=0; i<C_count; i++)
	{
		cID+= (rand()%15+1);	
		pC[i].setID(cID);
		pC[i].setType((ORD_TYPE)(rand()%TYPE_CNT));
	}	

		
	int EvTime = 0;

	int O_id = 1;
	
	//Create Random events and fill them into EventsQueue
	//All generated event will be "ArrivalEvents" for the demo
	for(int i=0; i<EventCnt; i++)
	{
		O_id += (rand()%4+1);		
		int OType = rand()%TYPE_CNT;	//Randomize order type		
		EvTime += (rand()%5+1);			//Randomize event time
		pEv = new ArrivalEvent(EvTime,O_id,(ORD_TYPE)OType);
		EventsQueue.enqueue(pEv);

	}	

	// --->   In next phases, no random generation is done
	// --->       EventsQueue should be filled from actual events loaded from input file

	
	
	
	
	//Now We have filled EventsQueue (randomly)
	int CurrentTimeStep = 1;
	

	//as long as events queue is not empty yet
	while(!EventsQueue.isEmpty())
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep,timestep,10);	
		pGUI->PrintMessage(timestep);


		//The next line may add new orders to the DEMO_Queue
		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
		

/////////////////////////////////////////////////////////////////////////////////////////
		/// The next code section should be done through function "FillDrawingList()" once you
		/// decide the appropriate list type for Orders and Cooks
		
		//Let's add ALL randomly generated Cooks to GUI::DrawingList
		for(int i=0; i<C_count; i++)
			pGUI->AddToDrawingList(&pC[i]);
		
		//Let's add ALL randomly generated Ordes to GUI::DrawingList
		int size = 0;
		Order** Demo_Orders_Array = DEMO_Queue.toArray(size);
		
		for(int i=0; i<size; i++)
		{
			pOrd = Demo_Orders_Array[i];
			pGUI->AddToDrawingList(pOrd);
		}
/////////////////////////////////////////////////////////////////////////////////////////

		pGUI->UpdateInterface();
		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
		pGUI->ResetDrawingList();
	}

	delete []pC;


	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();

	
}
////////////////

void Restaurant::AddtoDemoQueue(Order *pOrd)
{
	DEMO_Queue.enqueue(pOrd);
}

/// ==> end of DEMO-related function


/// ==================== Functions used in different modes ======================================

void Restaurant::Hire_A_Cook(ORD_TYPE type, int& cID, int nCooks, int BO, int Smax, int Smin, int Bmax, int Bmin, int rest_p)
{
	

	Cook* pCook;
	for (int i = 0; i < nCooks; i++)
	{
		srand(time(NULL));
		int cSpd = Smin + rand() % static_cast<int>(Smax - Smin + 1);
		int cBrk = Bmin + rand() % static_cast<int>(Bmax - Bmin + 1);

		switch (type)
		{
		case TYPE_NRM:
			cID++;
			pCook = new Cook(cID, type, cSpd, BO, cBrk, rest_p);
			Cook_N_Q.enqueue(pCook);
				break;

		case TYPE_VGAN:
			cID++;
			pCook = new Cook(cID, type, cSpd, BO, cBrk, rest_p);
			Cook_G_Q.enqueue(pCook);
			break;

		case TYPE_VIP:
			cID++;
			pCook = new Cook(cID, type, cSpd, BO, cBrk, rest_p);
			Cook_V_Q.enqueue(pCook);
			break;

		default:
			break;
		}

	}
}
void Restaurant::Get_Injury(double InjProb, int& n_injured)
{
	//static_cast<float>(rand()) / );
	float rand_inj = static_cast<float>( rand()/ static_cast<float>(RAND_MAX/(1-0)) );
	Cook* pCook;
	if (rand_inj <= InjProb)
	{
		if (Busy_Cooks_B.ViewfirstNode(pCook))
		{
			if (pCook->isInjured()==false)
			{
				pCook->setInjured(true);// to mark the injured cook so he can take a break immediately after he finishes his order no matter he had finished the amount of brk_ord or not
				n_injured++;// to indicate the overall number of injured cooks

				int remaining = pCook->getNot_Available();
				pCook->setNot_Available(remaining * 2); // the remaining time for the cook to stay in the busy list will be doubled as its speed decreased to its half
				int old_Srv_Time = pCook->getOrd()->GetServTime();
				int new_Srv_Time = old_Srv_Time - remaining + (pCook->getNot_Available()); // we should update the service time of the order the cook was busy working on it
				pCook->getOrd()->SetServTime(new_Srv_Time); ///we substract the old remaining time from the service time and add the updated remaining time after injury
				//Busy_Cooks_B.AddNode(pCook);
			}
		}

	}
	return;
}
void Restaurant::Assign_Ord_to_Cook(Order* pOrd, Cook* pCook, PROG_MODE mode, string& GUI_msg)
{
	pCook->setOrd(pOrd);
	int needed_duration=0;
	if (pOrd->GetType() == TYPE_NRM || pOrd->GetType() == TYPE_VGAN || (pOrd->GetType() == TYPE_VIP && !(pCook->isInjured())))
	{
		needed_duration = ceil((double)((double)pOrd->getSize() /(double)pCook->GetSpeed())); // we need the quotient to be approximated to the ceil ..so it representes the time needed to finish completely all the dishes
	}
	else if (pOrd->GetType() == TYPE_VIP && pCook->isInjured()) // then this VIP order is urgent and the cook taken from its rest
	{
		needed_duration = ceil((double)((double)(2*pOrd->getSize()) / (double)pCook->GetSpeed())); // as the cook was initially in a break and this is an urgent order so its speedwill decease to its half which is equivalent to increase the amount of dishes to the double
	}
	pCook->setNot_Available(needed_duration);
	pOrd->SetServTime(needed_duration);
	pOrd->setStatus(SRV);
	pCook->setDishes_break(pCook->GetDishes_break() - 1);// an order is just assigned to this cook , then the amount of orders he need to finish before taking rest must be updated
	In_Service_Orders_B.AddNode(pOrd);
	Busy_Cooks_B.AddNode(pCook);

	if (mode == MODE_INTR || mode == MODE_STEP)
	{
		///// to construct the string that will be printed on the GUI interface at each timestep declaring which order was assigned to which cook and so on
		///// following the example "N6(V3)"
		Type_GUI_msg(pCook->GetType(), GUI_msg); // first we print the letter indicating the cook type 
		GUI_msg.append(to_string(pCook->GetID())); // second we print the cook ID
		GUI_msg.append("(");
		Type_GUI_msg(pOrd->GetType(), GUI_msg);// between brackets we print the data of the order (type and id)
		GUI_msg.append(to_string(pOrd->GetID()));
		GUI_msg.append(")    ");
	}
	
}
void Restaurant::Type_GUI_msg(ORD_TYPE c_o_Type,string& GUI_msg) // to print the letter(N/V/G) on the GUI interface based on cook/order type
{
	switch (c_o_Type)
	{
	case TYPE_VIP:
		GUI_msg.append("V");
		break;
	case TYPE_NRM:
		GUI_msg.append("N");
		break;
	case TYPE_VGAN:
		GUI_msg.append("G");
		break;
	default:
		break;
	}
}

Cook* Restaurant::Search_for_cook(Order* pOrd, int P_limit, int U_limit, int& n_autoPromote, int & n_urgent) /// parameters are ( order* pOrd, int Autop_limit,int& n_autopromoted ,int VIP_WT_limit, int & n_Urgent)
{
	Cook* pCook;
	ORD_TYPE Type_O = pOrd->GetType();
	switch (Type_O)
	{
	case TYPE_NRM:
		if (!Cook_N_Q.isEmpty())
		{
			Cook_N_Q.dequeue(pCook);
			NormalOrder_L.GetfirstNode(pOrd);
		}
		else if (!Cook_V_Q.isEmpty())
		{
			Cook_V_Q.dequeue(pCook);
			NormalOrder_L.GetfirstNode(pOrd);
		}
		else
			pCook = nullptr;
		if (pOrd->getWaitingTime() >= P_limit)  //then execute promotion event to this order and increment  n_autopromoted++ (an integer declared in the mai mode fn and sent to this fn by reference)
		{
			PromoteOrder(pOrd->GetID());
			n_autoPromote++;
		}
			
		return pCook;
		break;
	case TYPE_VGAN:
		if (!Cook_G_Q.isEmpty())
		{
			Cook_G_Q.dequeue(pCook);
			VeganOrder_Q.dequeue(pOrd);
		}
		else
			pCook = nullptr;
		return pCook;
		break;
	case TYPE_VIP:           
		if (!Cook_V_Q.isEmpty())
		{
			Cook_V_Q.dequeue(pCook);
			VIPOrder_Q.dequeue(pOrd);
		}
		else if (!Cook_N_Q.isEmpty())
		{
			Cook_N_Q.dequeue(pCook);
			VIPOrder_Q.dequeue(pOrd);
		}
		else if (!Cook_G_Q.isEmpty())
		{
			Cook_G_Q.dequeue(pCook);
			VIPOrder_Q.dequeue(pOrd);
		}
		else      //////////////////////// check if pOrd-> getwaiting() == U_limit .. search in the in break then in the in rest lists .. and increment  n_Urgent ++ (which is an integer declared in the main mode fn and sent by reference to this fn)
			pCook = nullptr;
		if (pOrd->getWaitingTime() >= U_limit)
		{ 
			
			if (!InBreak_Cooks_B.IsEmpty())
			{
				InBreak_Cooks_B.GetfirstNode(pCook);
				VIPOrder_Q.dequeue(pOrd);
				n_urgent++;
			}
			else if (!InRest_Cooks_B.IsEmpty())
			{
				InRest_Cooks_B.GetfirstNode(pCook);
				VIPOrder_Q.dequeue(pOrd);
				n_urgent++;
			}
			else
			{
				pCook = nullptr;

			}
			/*n_urgent++;*/
			
		}
		
		return pCook;
		break;
	default:
		break;
	}
}


void Restaurant::Take_Break_Rest(Cook* pCook,int bo) //this function does not check if the cook had finished the order or not .. because it is up to the manager to make the cook enter a break no matter what .. but in the mode simulator function we call this function only if the cook had finished the order 
                                              //to increase program maintainability for future updates
{
	if (pCook->GetDishes_break() <= 0 && !(pCook->isInjured())) // he had finished the amount of dishes and not injured .. he deserves a break
	{
		InBreak_Cooks_B.AddNode(pCook);
		Busy_Cooks_B.RemoveNode(pCook);
		pCook->setDishes_break(bo);
		pCook->setNot_Available(pCook->GetInbreak());
	}
	
	else if (pCook->isInjured()) // If he is injured he should take rest no matter he had finished the amount of dishes left to his break ..
		                        //As kind restaurant managers if he is injured and had finished the current order then he will take a rest
	{
		InRest_Cooks_B.AddNode(pCook);
		Busy_Cooks_B.RemoveNode(pCook);
		pCook->setDishes_break(bo);
		pCook->setNot_Available(pCook->getRest());
	}
		
	
}

void Restaurant::Update_Busy_Cooks(int bo )
{
	
	if (Busy_Cooks_B.IsEmpty())
	{
		return;
	}
	else
	{
		Cook** arrcook;
		int count;
		arrcook=Busy_Cooks_B.toArray(count); // arrcook is an array of pointers to cook pointers
		                                     // then changing data using this array will also change the data to the object to which the arrcook[i]is pointing
		                                     // so every change will be also recorded (hopefully) in the cook object so in the bag of cooks that contains it too.
		for (int i = 0; i < count; i++)
		{
			if (arrcook[i]->getNot_Available() > 0)
			{
				arrcook[i]->setNot_Available(arrcook[i]->getNot_Available() - 1);
				//int newdishes_brk;// the new value of dishes_break after which the cook will have his break 
				//if (!(arrcook[i]->isInjured())) // if he is not injured then he will work by its normal speed
				//{
				//	newdishes_brk = (arrcook[i]->GetDishes_break()) - (arrcook[i]->GetSpeed());// each timestep the cook will finish a number of dishes equal to its speed .. hence, the dishes_break must decrease by the cook's speed each timestep
				//}
				//else // the cook is injured then his speed will decrease to its half then the amount of dishes finished in one timestep will also decrease to its half 
				//{
				//	newdishes_brk = (arrcook[i]->GetDishes_break()) - ((arrcook[i]->GetSpeed())/2);
				//}
				//arrcook[i]->setDishes_break(newdishes_brk);
            }
			else if (arrcook[i]->getNot_Available() == 0) // he has finished the assigned order (update his order's data) and check if its time to take break/rest 
			{
				/// Update order's data
				arrcook[i]->getOrd()->setStatus(DONE);
				In_Service_Orders_B.RemoveNode(arrcook[i]->getOrd());
				arrcook[i]->getOrd()->CalcFinishTime();
				Finished_Orders_L.InsertEnd(arrcook[i]->getOrd());

				/// Check if it is time to take break/ rest
				if (arrcook[i]->GetDishes_break() <= 0 || (arrcook[i]->getNot_Available() == 0 && arrcook[i]->isInjured()))
				{
					Take_Break_Rest(arrcook[i],bo);
				
				}
				else // he has not finish the required amount of orders to enter a break but he is not busy now.. so we return him to the available cooks queues
				{
					Busy_Cooks_B.RemoveNode(arrcook[i]);
				
					switch (arrcook[i]->GetType())
					{
					case TYPE_NRM:
						Cook_N_Q.enqueue(arrcook[i]);
						break;

					case TYPE_VGAN:
						Cook_G_Q.enqueue(arrcook[i]);
						break;

					case TYPE_VIP:
						Cook_V_Q.enqueue(arrcook[i]);
						break;

					default:
						break;
					}

				}

			}
		}
	}



}

void Restaurant::Update_InBreak_Cooks()
{

	if (InBreak_Cooks_B.IsEmpty())
	{
		return;
	}
	else
	{
		Cook** arrcook;
		int count;
		arrcook = InBreak_Cooks_B.toArray(count); 
											 
											 
		for (int i = 0; i < count; i++)
		{
			if (arrcook[i]->getNot_Available() > 0) //cook is still in his break
			{
				arrcook[i]->setNot_Available(arrcook[i]->getNot_Available() - 1);
				
			}
			else if (arrcook[i]->getNot_Available() == 0) //cook has finished his break
			{
				    //arrcook[i]->setDishes_break(bo);
					InBreak_Cooks_B.RemoveNode(arrcook[i]);

					switch (arrcook[i]->GetType())
					{
					case TYPE_NRM:
						Cook_N_Q.enqueue(arrcook[i]);
						break;

					case TYPE_VGAN:
						Cook_G_Q.enqueue(arrcook[i]);
						break;

					case TYPE_VIP:
						Cook_V_Q.enqueue(arrcook[i]);
						break;

					default:
						break;
					}

			}
		}
	}



}

void Restaurant::Update_InRest_Cooks()
{

	if (InRest_Cooks_B.IsEmpty())
	{
		return;
	}
	else
	{
		Cook** arrcook;
		int count;
		arrcook = InRest_Cooks_B.toArray(count);


		for (int i = 0; i < count; i++)
		{
			if (arrcook[i]->getNot_Available() > 0) //cook is still in his rest
			{
				arrcook[i]->setNot_Available(arrcook[i]->getNot_Available() - 1);

			}
			else if (arrcook[i]->getNot_Available() == 0) // cook has finished his rest 
			{
				//arrcook[i]->setDishes_break(bo);
				arrcook[i]->setInjured(false);
				InRest_Cooks_B.RemoveNode(arrcook[i]);

				switch (arrcook[i]->GetType())
				{
				case TYPE_NRM:
					Cook_N_Q.enqueue(arrcook[i]);
					break;

				case TYPE_VGAN:
					Cook_G_Q.enqueue(arrcook[i]);
					break;

				case TYPE_VIP:
					Cook_V_Q.enqueue(arrcook[i]);
					break;

				default:
					break;
				}

			}
		}
	}



}

LinkedList<Order*> Restaurant::GetFinishOrder()
{

	return Finished_Orders_L;
}

//////////////////////////////////////////////////////////////////////////////////////////////
////////////////////Interactive mode function////////////////////////////////////

void Restaurant::Simple_Interactive_Simulator()
{
	//Restaurant* pRest = ;
	pGUI->PrintMessage("Welcome to the Interactive Mode !!...");
	
	Prsr = new Parser();
	int nNormal = 0;
	int nVegan = 0;
	int nVIP = 0; // Number of normal , vegan , vip cooks
	int spd_Nrm_min,spd_Nrm_max, spd_Vgn_min,spd_Vgn_max, spd_VIP_min,spd_VIP_max; //Speed of each type of cooks
	int brk_o; // Number of dishes that a cook must finish before break
	int brk_Nrm_min,brk_Nrm_max, brk_Vgn_min,brk_Vgn_max, brk_VIP_min,brk_VIP_max;  // break period in timesteps
	double InjProb; // probability that a busy cook get injured
	int Rest_period; // needed period for the injured cook to take rest
	int Autopromo; // limit for autopromotion
	int VIP_WT; // waiting time limit after which the VIP order become Urgent
	int nEvnt;// number of events

	
	//Event* pEv = nullptr;
	Order* pOrder;
	Cook* pCook;

	int cook_count; // number of all cooks in the restaurant
	cook_count = nNormal + nVegan + nVIP;
	int cID = 0;
	
	if (Prsr->OpenFile(pGUI))
	{
		Prsr->ReadFile(nNormal, nVegan, nVIP, spd_Nrm_min, spd_Nrm_max, spd_Vgn_min, spd_Vgn_max, spd_VIP_min, spd_VIP_max, brk_o, brk_Nrm_min, brk_Nrm_max, brk_Vgn_min, brk_Vgn_max, brk_VIP_min, brk_VIP_max, InjProb, Rest_period, Autopromo, nEvnt, VIP_WT, this);
	}
	//// Ids will not be repeated , as VIP are the most important we will assign to them the first set of Ids 
	for (int i = 0; i < nVIP; i++)
	{
		cID++;
		pCook = new Cook(cID,TYPE_VIP,spd_VIP_min,brk_o, brk_VIP_min,1);
		Cook_V_Q.enqueue(pCook);
	}

	for (int i = 0; i < nNormal; i++)
	{
		cID++;
		pCook = new Cook(cID, TYPE_NRM, spd_Nrm_min, brk_o, brk_Nrm_min,1);
		Cook_N_Q.enqueue(pCook);

	}
	for (int i = 0; i < nVegan; i++)
	{
		cID++;
		pCook = new Cook(cID, TYPE_VGAN, spd_Vgn_min, brk_o, brk_Vgn_min,1);
		Cook_G_Q.enqueue(pCook);
	}

	

	int CurrentTime = 1;

	

	while (!EventsQueue.isEmpty() || !In_Service_Orders_B.IsEmpty()) // we cannot check by (IsEmpty()) fn
																	 // as the bag will also contain finished orders
																	 // so we made another list for finished orders to solve this 
																	 //problem and it's better for complexity to make another list
	{
		//itoa(CurrentTime, timestep, 10);
		string TSmsg = "Current TS = ";
		/*TSmsg += timestep;*/
		pGUI->PrintMessage(TSmsg+ to_string(CurrentTime));
		

		ExecuteEvents(CurrentTime);



		//FillDrawingList();   filldrawinglist fn does not draw items ..
		// it just fills the "drawing list" by items to be drawn when calling the "update interface fn"
		// then no need to call it more than once in a loop
		// or we can think another way.. fill the drawing list by orders just arrived before picking and blabla
		// then update the interface .. then reset drawinglist and fill it another time after picking 
		// but this way it will be called twice .. 


		//b) Pick one order from each order type and move it to In service  List
		Order* VIPOrder_picked;
		Order* NormalOrder_picked;
		Order* VeganOrder_picked;

		bool VIPorder = VIPOrder_Q.dequeue(VIPOrder_picked);
		bool Normalorder = NormalOrder_L.GetfirstNode(NormalOrder_picked);
		bool Veganorder = VeganOrder_Q.dequeue(VeganOrder_picked);

		if (VIPorder)
		{
			VIPOrder_picked->setStatus(SRV);
			In_Service_Orders_B.AddNode(VIPOrder_picked); // we added the order to the in service list
			VIPOrder_picked->SetServTime(CurrentTime);    // we set the servTime to the cuurent time 
		}
		if (Normalorder)
		{
			NormalOrder_picked->setStatus(SRV);
			In_Service_Orders_B.AddNode(NormalOrder_picked); // we added the order to the in service list
			NormalOrder_picked->SetServTime(CurrentTime);   // we set the servTime to the cuurent time 
		}
		if (Veganorder)
		{
			VeganOrder_picked->setStatus(SRV);
			In_Service_Orders_B.AddNode(VeganOrder_picked);   // we added the order to the in service list
			VeganOrder_picked->SetServTime(CurrentTime);      // we set the servTime to the cuurent time 
		}

		


		
		Order** arr_ord;
		int count = 0;
		if (!In_Service_Orders_B.IsEmpty())
		{
			arr_ord=In_Service_Orders_B.toArray(count);
			for (int i = 0; i < count; i++)
			{
				if (CurrentTime == arr_ord[i]->GetServTime() + 5)
				{
					arr_ord[i]->setStatus(DONE);
					Finished_Orders_L.InsertEnd(arr_ord[i]);
					In_Service_Orders_B.RemoveNode(arr_ord[i]);
				}
			}
		}
		
		FillDrawingList();
		pGUI->UpdateInterface();

		//char FromIntToChar[4], FromIntToCharV[4], FromIntToCharG[4], FromIntToCharN[4];
		Order** arr_Vord,** arr_Gord, **arr_Nord;
		int Count_O_V=0, Count_O_G=0, Count_O_N=0;
		arr_Vord =VIPOrder_Q.toArray(Count_O_V);
		arr_Gord = VeganOrder_Q.toArray(Count_O_G);
		arr_Nord = NormalOrder_L.toArray(Count_O_N);

		string Waiting_Orders_msg = "Waiting VIP Orders = ";
		Waiting_Orders_msg.append(to_string(Count_O_V));

		Waiting_Orders_msg.append(", Waiting Vegan Orders = ");
		Waiting_Orders_msg.append(to_string(Count_O_G));

		Waiting_Orders_msg.append(", Waiting Normal Orders = ");
		Waiting_Orders_msg.append(to_string(Count_O_N));

		pGUI->PrintMessage(Waiting_Orders_msg);

		string Available_cooks_msg = "Available VIP cooks = ";
		Available_cooks_msg.append(to_string(nVIP));

		Available_cooks_msg.append(", Available Vegan cooks = ");
		Available_cooks_msg.append(to_string(nVegan));

		Available_cooks_msg.append(", Available Normal cooks = ");
		Available_cooks_msg.append(to_string(nNormal));

		pGUI->PrintMessage(Available_cooks_msg );

		

		pGUI->PrintMessage("Please click to continue..");
		pGUI->PrintMessage("-->");
		pGUI->waitForClick();
		CurrentTime++;
		pGUI->ResetDrawingList(); // to reset the drawing list and then update it with the following loop data
	
	}

	


}


void Restaurant::Modes_Simulator(PROG_MODE mode)
{
	switch (mode)
	{
	case MODE_INTR:
		pGUI->PrintMessage("Welcome to the Interactive Mode !!...");
		break;
	case MODE_STEP:
		pGUI->PrintMessage("Welcome to the Step_by_Step Mode !!...");
		break;
	case MODE_SLNT:
		pGUI->PrintMessage("Welcome to the Silent Mode !!...");
		break;
	default:
		break;
	}
	Prsr = new Parser();

	if (Prsr->OpenFile(pGUI)) // if he cannot open the file he will return
	{
		///////////////////////////////////////Infos that will be taken from the input file
		int nNormal = 0;
		int nVegan = 0;
		int nVIP = 0; // Number of normal , vegan , vip cooks
		int spd_Nrm_min, spd_Nrm_max, spd_Vgn_min, spd_Vgn_max, spd_VIP_min, spd_VIP_max; //Speed of each type of cooks
		int brk_o; // Number of dishes that a cook must finish before break
		int brk_Nrm_min, brk_Nrm_max, brk_Vgn_min, brk_Vgn_max, brk_VIP_min, brk_VIP_max;  // break period in timesteps
		double InjProb; // probability that a busy cook get injured
		int Rest_period; // needed period for the injured cook to take rest
		int Autopromo; // limit for autopromotion
		int VIP_WT; // waiting time limit after which the VIP order become Urgent
		int nEvnt;// number of events

		

		Order* pOrder;
		Cook* pCook;

		//////////////////////////////////////////Infos needed for the output fn
		int cook_count; // number of all cooks in the restaurant
		cook_count = nNormal + nVegan + nVIP;
		int cID = 0;
		int nInjured = 0; // number of injured cooks
		int nUrgent_ord = 0;// number of urgent orders
		int n_Autopromoted = 0; // number of autopromoted orders to calculate the percentage
		int TNOrders = 0; //Cal total N Orders entered

		int CurrentTime = 1;


		Prsr->ReadFile(nNormal, nVegan, nVIP, spd_Nrm_min, spd_Nrm_max, spd_Vgn_min, spd_Vgn_max, spd_VIP_min, spd_VIP_max, brk_o, brk_Nrm_min, brk_Nrm_max, brk_Vgn_min, brk_Vgn_max, brk_VIP_min, brk_VIP_max, InjProb, Rest_period, Autopromo, nEvnt, VIP_WT, this);

		Hire_A_Cook(TYPE_VIP, cID, nVIP, brk_o, spd_VIP_max, spd_VIP_min, brk_VIP_max, brk_VIP_min, Rest_period);
		Hire_A_Cook(TYPE_NRM, cID, nNormal, brk_o, spd_Nrm_max, spd_Nrm_min, brk_Nrm_max, brk_Nrm_min, Rest_period);
		Hire_A_Cook(TYPE_VGAN, cID, nVegan, brk_o, spd_Vgn_max, spd_Vgn_min, brk_Vgn_max, brk_Vgn_min, Rest_period);


		while (!EventsQueue.isEmpty() || !In_Service_Orders_B.IsEmpty()||!VIPOrder_Q.isEmpty()||!VeganOrder_Q.isEmpty()||!NormalOrder_L.IsEmpty() || !InBreak_Cooks_B.IsEmpty() || !InRest_Cooks_B.IsEmpty())
		{

			if (mode == MODE_INTR || mode == MODE_STEP)
			{
				string TSmsg = "Current TS = ";
				pGUI->PrintMessage(TSmsg + to_string(CurrentTime));

			}

			ExecuteEvents(CurrentTime);

			Order* VIPOrder_picked;
			Order* NormalOrder_picked;
			Order* VeganOrder_picked;
			 // we will just have a ptr to the first node in these lists/ queues .. we will dequeue only if we found a suitable cook (dequeing/deleting first node operation will be done in the "Search for cook " fn)
			bool VIPorder = VIPOrder_Q.peekFront(VIPOrder_picked);
			bool Normalorder = NormalOrder_L.ViewfirstNode(NormalOrder_picked);
			bool Veganorder = VeganOrder_Q.peekFront(VeganOrder_picked);
			 
			bool waiting_indicator = false; // indicator that the front pointer is not a waiting order for which we hadn't pick a suitable cook in this time step
			string GUI_msg="";

			Order** arrWaitOrd;
			int sizeWait;
			 
			// first we check for VIP orders then for Vegan then for Normal ...

			while(VIPOrder_Q.peekFront(VIPOrder_picked) && !waiting_indicator)
			{
				pCook = Search_for_cook(VIPOrder_picked, Autopromo, VIP_WT, n_Autopromoted, nUrgent_ord);
				if (pCook)
				{
					Assign_Ord_to_Cook(VIPOrder_picked, pCook, mode,GUI_msg);

				}
				
					//VIPOrder_picked->setWaitingTime(VIPOrder_picked->getWaitingTime() + 1);
				else
				{
					//we increment the waiting time for all remaining orders in the queue .. as they had arrived  but not assigned to a cook yet
					arrWaitOrd = VIPOrder_Q.toArray(sizeWait);
					for (int i = 0; i < sizeWait; i++)
					{
						arrWaitOrd[i]->setWaitingTime(arrWaitOrd[i]->getWaitingTime() + 1);
					}
					waiting_indicator = true;
				}
			}

			waiting_indicator = false;
			while (VeganOrder_Q.peekFront(VeganOrder_picked)&& !waiting_indicator)
			{
				pCook = Search_for_cook(VeganOrder_picked, Autopromo, VIP_WT, n_Autopromoted, nUrgent_ord);
				if (pCook)
				{
					Assign_Ord_to_Cook(VeganOrder_picked, pCook, mode, GUI_msg);
				}
				
					//VeganOrder_picked->setWaitingTime(VeganOrder_picked->getWaitingTime() + 1);
				else
				{
					//we increment the waiting time for all remaining orders in the queue .. as they had arrived  but not assigned to a cook yet
					arrWaitOrd = VeganOrder_Q.toArray(sizeWait);
					for (int i = 0; i < sizeWait; i++)
					{
						arrWaitOrd[i]->setWaitingTime(arrWaitOrd[i]->getWaitingTime() + 1);
					}
					waiting_indicator = true;
				}
			}
			waiting_indicator = false;
			while(NormalOrder_L.ViewfirstNode(NormalOrder_picked)&& !waiting_indicator)
			{
				TNOrders++;
				pCook = Search_for_cook(NormalOrder_picked, Autopromo, VIP_WT, n_Autopromoted, nUrgent_ord);
				if (pCook)
				{
					Assign_Ord_to_Cook(NormalOrder_picked, pCook,mode,GUI_msg);
				}
				
					//NormalOrder_picked->setWaitingTime(NormalOrder_picked->getWaitingTime() + 1);
				else
				{
					//we increment the waiting time for all remaining orders in the queue .. as they had arrived  but not assigned to a cook yet
					arrWaitOrd = NormalOrder_L.toArray(sizeWait);

					for (int i = 0; i < sizeWait; i++)
					{
						arrWaitOrd[i]->setWaitingTime(arrWaitOrd[i]->getWaitingTime() + 1);
					}
					waiting_indicator = true;
				}
				

			}

			

			Get_Injury(InjProb, nInjured);

			Update_Busy_Cooks(brk_o);
			Update_InBreak_Cooks();
			Update_InRest_Cooks();

			if (mode == MODE_INTR || mode == MODE_STEP)
			{
				FillDrawingList();
				pGUI->UpdateInterface();

				/// to print the number of waiting orders in each type
				Order** arr_Vord, ** arr_Gord, ** arr_Nord;
				int Count_O_V = 0, Count_O_G = 0, Count_O_N = 0;
				arr_Vord = VIPOrder_Q.toArray(Count_O_V);
				arr_Gord = VeganOrder_Q.toArray(Count_O_G);
				arr_Nord = NormalOrder_L.toArray(Count_O_N);

				string Waiting_Orders_msg = "Waiting VIP Orders = ";
				Waiting_Orders_msg.append(to_string(Count_O_V));

				Waiting_Orders_msg.append(", Waiting Vegan Orders = ");
				Waiting_Orders_msg.append(to_string(Count_O_G));

				Waiting_Orders_msg.append(", Waiting Normal Orders = ");
				Waiting_Orders_msg.append(to_string(Count_O_N));

				pGUI->PrintMessage(Waiting_Orders_msg);

				/// to print the number of available cooks in each type
				Cook** arr_Vcook, ** arr_Gcook, ** arr_Ncook; // now the number of available cooks varies with timestep
				int Count_C_V = 0, Count_C_G = 0, Count_C_N = 0;
				arr_Vcook = Cook_V_Q.toArray(Count_C_V);
				arr_Gcook = Cook_G_Q.toArray(Count_C_G);
				arr_Ncook = Cook_N_Q.toArray(Count_C_N);

				string Available_cooks_msg = "Available VIP cooks = ";
				Available_cooks_msg.append(to_string(Count_C_V));

				Available_cooks_msg.append(", Available Vegan cooks = ");
				Available_cooks_msg.append(to_string(Count_C_G));

				Available_cooks_msg.append(", Available Normal cooks = ");
				Available_cooks_msg.append(to_string(Count_C_N));

				pGUI->PrintMessage(Available_cooks_msg);

				/// to print the type and IDs of cooks and orders assigned in this last timestep 
				pGUI->PrintMessage(GUI_msg);


				///to print the number of finished orders 
				Order** arr_Serv_ord;
				int Count_Serv_ord = 0;
				arr_Serv_ord = Finished_Orders_L.toArray(Count_Serv_ord);
				string Finished_orders_msg = "Finished orders = ";
				Finished_orders_msg.append(to_string(Count_Serv_ord));

				pGUI->PrintMessage(Finished_orders_msg);

				if (mode == MODE_INTR)
				{
					pGUI->waitForClick();
				}
				else if (mode == MODE_STEP)
				{
					Sleep(1000);
				}

			}

				/*if (mode == MODE_SLNT) // no need for this message as the program does not take a significant time 
				{
					pGUI->PrintMessage(" Please wait for seconds .. The program will execute the file and print the output..");
				}*/

			CurrentTime++;

			if (mode==MODE_INTR||mode==MODE_STEP)
			{
				pGUI->ResetDrawingList(); // to reset the drawing list and then update it with the following loop data
			}
					

			
			int FinishCount;
			Finished_Orders_L.SortFinishTime();
			Finished_Orders_L.SortServicetime();
			Order** FinishOrder = Finished_Orders_L.toArray(FinishCount);
			Prsr->WriteFile(FinishOrder,FinishCount,nNormal,nVIP,nVegan, nInjured, nUrgent_ord, n_Autopromoted, TNOrders);

		}

	}
	else // the parser cannot open the file
	{
	return;
    }
}