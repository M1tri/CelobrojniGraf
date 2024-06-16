#include <iostream>
#include "GraphInt.h"

//#define POSSIBLE
//#define CYCLIC

//#define SEP2022

int main(int argc, char* argv[])
{
	GraphAsListsInt graf;

#ifdef SEP2022

	graf.insertNode(1, false, 3);
	graf.insertNode(2, false, 3);
	graf.insertNode(3, true, 100);
	graf.insertNode(6, false, 7);
	graf.insertNode(4, false, 5);
	graf.insertNode(5, false, 2);

	graf.insertEdge(1, 2);
	graf.insertEdge(2, 3);
	graf.insertEdge(2, 4);
	graf.insertEdge(4, 5);
	graf.insertEdge(6, 4);

	LinkedNodeInt* node = graf.findNode(12);
	if (node)
		node->visit();
#endif

	graf.insertNode(1);
	graf.insertNode(2);
	graf.insertNode(3);
	graf.insertNode(4);
	graf.insertNode(5);
	graf.insertNode(6);
	graf.insertNode(7);
	graf.insertNode(8);

	graf.insertEdge(1, 2);
	graf.insertEdge(2, 3);

	graf.insertEdge(4, 5);

	graf.insertEdge(6, 7);
	graf.insertEdge(7, 8);


	int k = graf.subGraphCnt(4);

	if (graf.doesConnectedComponentExist(3))
	{
		std::cout << "Postoji podgraf sa 3 cvora\n";
	}
	else
	{
		std::cout << "Ne postoji podgraf sa 3 cvora\n";
	}

	if (graf.doesConnectedComponentExist(6))
	{
		std::cout << "Postoji podgraf sa 6 cvora\n";
	}
	else
	{
		std::cout << "Ne postoji podgraf sa 6 cvora\n";
	}


#ifdef POSSIBLE
	graf.insertNode(1);
	graf.insertNode(2);
	graf.insertNode(3);
	graf.insertNode(4);
	graf.insertNode(5);
	graf.insertNode(6);
	graf.insertNode(7);
	graf.insertNode(8);
	graf.insertNode(9);

	graf.insertEdge(1, 2);
	graf.insertEdge(2, 5);
	graf.insertEdge(5, 7);
	graf.insertEdge(7, 3);
	graf.insertEdge(3, 6);
	graf.insertEdge(1, 4);
	graf.insertEdge(3, 4);
	graf.insertEdge(4, 7);

	if (graf.arePathsPossible(1, 4, 6, 5))
	{
		std::cout << "Put postoji nigercino!\n";
	}
	else
	{
		std::cout << "Jebiga ne moze\n";
	}
#endif

#ifdef CYCLIC
	graf.insertNode(1);
	graf.insertNode(2);
	graf.insertNode(3);
	graf.insertNode(4);
	graf.insertNode(5);
	
	graf.insertEdge(1, 2);
	graf.insertEdge(2, 3);
	graf.insertEdge(2, 4);
	graf.insertEdge(3, 5);
	graf.insertEdge(4, 5);
	graf.insertEdge(5, 3);
	
	if (graf.isCyclic())
	{
		std::cout << "Ciklican graf\n";
	}
	else
	{
		std::cout << "Graf ne sadrzi cikluse\n";
	}
#endif

	graf.insertNode(1);
	graf.insertNode(2);
	graf.insertNode(3);
	graf.insertNode(4);
	graf.insertNode(5);
	
	graf.insertEdge(1, 4);
	graf.insertEdge(4, 5);

	graf.insertEdge(1, 2);
	graf.insertEdge(2, 3);
	graf.insertEdge(3, 4);
	
	if (graf.canReach(1, 5, 3))
	{
		std::cout << "Moze\n";
	}
	else
	{
		std::cout << "Ne moze\n";
	}

	int nHoops = graf.reachableInNHoops(1, 2);



	/*if (graf.cycleThroughTwoNodes(1, 6, put, &lPut))
	{
		std::cout << put[0] << " -> ";
		for (int i = lPut - 1; i > 0; i--)
		{
			std::cout << put[i] << " -> ";
		}
		std::cout << put[0] << '\n';
	}*/

	return 0;
}

