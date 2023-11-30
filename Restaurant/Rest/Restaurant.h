#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Generic_DS\PriorityQueue.h"
#include "..\Events\Event.h"
#include "..\Generic_DS\LinkedList.h"
#include"..\Generic_DS\ListBag.h"

#include "Order.h"
class Parser;  //forward declaration to class Parser
// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Parser* Prsr; ///parser pointer to call it to open and read the file
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file

	
	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	Queue<Order*> DEMO_Queue;	//Important: This is just for demo
	/// ==>
	
	
	
	//
	// TODO: Add More Data Members As Needed
	//

	PriorityQueue <Order*> VIPOrder_Q;  //Queue for VIP orders

	LinkedList <Order*> NormalOrder_L;  //List for Normal orders

	Queue <Order*> VeganOrder_Q;  //Queue for Vegan orders

	ListBag<Order*> In_Service_Orders_B; // linked bag for all orders in service

	LinkedList<Order*> Finished_Orders_L; // Queue for all finished orders

	//LinkedList<Order*> Waiting_VIP_L; // linked list for waiting vip orders

	//LinkedList<Order*> Waiting_Vegan_L; // linked list for waiting vegan orders
	//
	//LinkedList<Order*> Waiting_Normal_L; // linked list for waiting normal orders

	//Queue<Cook*> Cook_V_Q;  //Queue for VIP cooks

	//Queue<Cook*> Cook_N_Q;  //Queue for Normal cooks

	//Queue<Cook*> Cook_G_Q;  //Queue for Vegan cooks

	///// As cooks from the same type will have different speeds and breaks 
	///// then to maximize the output of our restaurant and minimize the waiting time of the orders 
	///// we will order the cooks in a priority queue where the most performing will be always at the front

	PriorityQueue<Cook*> Cook_V_Q;//Priority Queue for VIP cooks

	PriorityQueue<Cook*> Cook_N_Q;//Priority Queue for Normal cooks

	PriorityQueue<Cook*> Cook_G_Q;//Priority Queue for Vegan cooks

	//// all unavailable cooks are in basgs because we need to loop on them all each time step in order to update their data 
	ListBag<Cook*> InBreak_Cooks_B; // linked bag for all cooks taking break

	ListBag<Cook*> Busy_Cooks_B; // linked bag for all busy cooks 
	// we seperated the busy and inbreak cooks in order to perfom the Get_Injury(..) fn on the busy cooks only without looping on the entire bag of unavailable cooks to look for a busy one
	
	ListBag<Cook*> InRest_Cooks_B; // linked bag for all injured cooks taking rest 

	

	void Type_GUI_msg(ORD_TYPE c_o_Type, string& GUI_msg); // utility function
public:
	
	Restaurant();
	~Restaurant();
	
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();

	


	void FillDrawingList();

	//
	// TODO: Add More Member Functions As Needed
	//



	////////////////////////////////////////////////
	//// Function Wrapper is a function that will be called in the Parser class 
	//// The purpose of this function is to get usage of the input taken from the file processing operation
	//// Espcially for the lines defining the events ,without breaking the classes responsabilities,
	//// As the restaurant class will be the responsible of taking any precautions before calling the event_constructors
	////////////////////////////////////////////////

	void Wrapper_Arrival(ORD_TYPE& r_Type, int& TS, int& id, int& size, int& mony);
	void Wrapper_Cancelation(int& TS, int& id);
	void Wrapper_Promote(int &TS, int& id, int& exmony);
	


	bool DeleteOrder(int ID); //to Delete an order
	void AddtoQueue(Order* pOrder); //to add order to queue

	void PromoteOrder(int ID); // to promote a normal order 



/// ===================    DEMO-related functions. Should be removed in phases 1&2   ================= 

	void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	void AddtoDemoQueue(Order* po);	//adds an order to the demo queue

/// ==================== Functions used in different modes ======================================

	void Hire_A_Cook(ORD_TYPE type, int &cID, int nCooks, int BO, int Smax, int Smin, int Bmax, int Bmin, int rest_p);
	void Get_Injury(double Injprob, int & n_injured);
	void Assign_Ord_to_Cook(Order* pOrd, Cook* pCook, PROG_MODE mode,string & GUI_msg);
	Cook* Search_for_cook(Order* pOrd, int P_limit, int U_limit, int& n_autoPromote, int& n_urgent);
	void Take_Break_Rest( Cook* pCook, int bo);
	void Update_Busy_Cooks(int bo);
	void Update_InBreak_Cooks();
	void Update_InRest_Cooks();
	LinkedList<Order*> GetFinishOrder();
/// ================================================================================================== 
///==================== Interactive Mode function
	void Simple_Interactive_Simulator();
	
///==================== Modes function
	void Modes_Simulator(PROG_MODE mode);
};

#endif