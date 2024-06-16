#pragma once

//#include "LinkedEdgeInt.h"
#include "LinkedNodeInt.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include "QueueAsArrayInt.h"

//#define PRINT

class GraphAsListsInt
{
protected:
	LinkedNodeInt* start;
	long nodeNum;
public:
	GraphAsListsInt();
	~GraphAsListsInt();

	LinkedNodeInt* findNode(const int& data) const;
	LinkedEdgeInt* findEdge(const int& dataSrc, const int& dataDest) const;

	void insertNode(const int& data);
	void insertNode(const int& data, bool isMracna, int napitak)
	{
		start = new LinkedNodeInt(data, nullptr, start);
		nodeNum++;

		start->isMracna = isMracna;
		start->napitak = napitak;
	}
	bool insertEdge(const int& dataSrc, const int& dataDest, const double& weight = 0);

private:
	void deleteEdgeToNode(const LinkedNodeInt* pDest);
public:
	bool deleteEdge(const int& dataSrc, const int& dataDest);
	bool deleteNode(const int& data);


	void toUndirected()
	{
		LinkedNodeInt* ptr = start;

		while (ptr)
		{
			LinkedEdgeInt* edging = ptr->adj;

			while (edging)
			{
				LinkedEdgeInt* potezi = edging->dest->adj;

				while (potezi && potezi->dest->node != ptr->node)
				{
					potezi = potezi->link;
				}

				if (potezi == nullptr)
				{
					insertEdge(edging->dest->node, ptr->node);
				}
				edging = edging->link;
			}
			ptr = ptr->next;
		}
	}
	int cudanBFS(int data)
	{
		LinkedNodeInt* str = start;

		while (str)
		{
			if (str->node == data)
				break;

			str = str->next;
		}

		if (!str)
			return -1;

		return cudanBFS(str);
	}

	void connectMaxAndMin()
	{
		toUndirected();
		LinkedNodeInt* ptr = start;
		int max, min;
		LinkedNodeInt* maxStart = nullptr;
		LinkedNodeInt* minStart = nullptr;
		setStatusForAllNodes(1);

		max = min = cudanBFS(ptr);
		maxStart = minStart = ptr;
		ptr = ptr->next;

		while (ptr)
		{
			if (ptr->status == 1)
			{
				std::cout << '\n';
				int count = cudanBFS(ptr);
					
				if (count > max)
				{
					max = count;
					maxStart = ptr;
				}

				if (count < min)
				{
					min = count;
					minStart = ptr;
				}
			}
			ptr = ptr->next;
		}

		std::cout << "\nMaks: "; 
		maxStart->visit();
		std::cout << "Min: ";
		minStart->visit();

		insertEdge(maxStart->node, minStart->node);

		setStatusForAllNodes(1);
		std::cout << '\n';
		cudanBFS(maxStart->node);
	}

private:
	int cudanBFS(LinkedNodeInt* ptr)
	{
		int num = 0;
		QueueAsArrayLinkedNodeInt red(100);
		
		red.enqueue(ptr);
		ptr->status = 2;

		while (!red.isEmpty())
		{
			LinkedNodeInt* pom = red.dequeue();
			num++;
			pom->status = 3;
			pom->visit();

			LinkedEdgeInt* pot = pom->adj;

			while (pot)
			{
				if (pot->dest->status == 1)
				{
					pot->dest->status = 2;
					red.enqueue(pot->dest);
				}
				
				pot = pot->link;
			}

		}

		return num;
	}
public:
	int myLongestCycle()
	{
		int max = 0;
		int path[100] = { 0 };
		int pathIndex = 0;

		LinkedNodeInt* ptr = start;

		while (ptr)
		{
			setStatusForAllNodes(0);
			myDfs(ptr, ptr, 0, max, path, pathIndex);

			ptr = ptr->next;
		}

		return max;
	}

	void ShortestPath(int startNode, int endNode)
	{
		LinkedNodeInt* ptr = start;
		LinkedNodeInt* startPtr = nullptr;
		LinkedNodeInt* endPtr = nullptr;

		while (ptr)
		{
			if (!startPtr && ptr->node == startNode)
				startPtr = ptr;

			if (!endPtr && ptr->node == endNode)
				endPtr = ptr;

			if (startPtr && endPtr)
				break;

			ptr = ptr->next;
		}

		int path[100] = { 0 };
		int pathIndex = 0;
		int min = nodeNum + 1;

		int finalPath[100] = { 0 };
		int finalIndex = 0;

		ShortesPath(endPtr, startPtr, 0, min, path, pathIndex, finalPath, finalIndex);

		for (int i = 0; i < finalIndex; i++)
		{
			std::cout << finalPath[i] << ' ';
		}
		std::cout << '\n';
	}

	bool canReach(int A, int B, int noNodes)
	{
		LinkedNodeInt* ptr = start;
		LinkedNodeInt* ptrA = nullptr;
		LinkedNodeInt* ptrB = nullptr;

		while (ptr)
		{
			if (!ptrA && ptr->node == A)
				ptrA = ptr;

			if (!ptrB && ptr->node == B)
				ptrB = ptr;

			if (ptrA && ptrB)
				break;

			ptr = ptr->next;
		}

		if (!ptrA || !ptrB)
			return false;

		return canReach(ptrB, ptrA, noNodes, 1);
	}

	// SEP 2022
	LinkedNodeInt* findNode(int val)
	{
		LinkedNodeInt* ptr = start;
		LinkedNodeInt* ret = nullptr;

		while (ptr)
		{
			if (ptr->status != 1 && !ptr->isMracna)
				ret = findNode(ptr, ptr->napitak, val);

			if (ret != nullptr)
			{
				return ret;
			}

			ptr = ptr->next;
		}

	}
	
	// KOL2 2023 GRUPA A
	int subGraphCnt(int p)
	{
		toUndirected();

		LinkedNodeInt* ptr = start;

		setStatusForAllNodes(1); // 1 - neobdradjen
		int count = 0;
		while (ptr)
		{
			if (ptr->status == 1)
			{
				if (subGraphBfs(ptr, p))
					count++;
			}
			ptr = ptr->next;
		}

		return count;
	}
	// KOL2 2023 GRUPA A



	// KOL2 2023 GRUPA B

	bool doesConnectedComponentExist(int k)
	{
		LinkedNodeInt* ptr = start;

		setStatusForAllNodes(1);
		while (ptr)
		{
			if (ptr->status == 1)
			{
				int m = subGraphNodeCount(ptr);
				std::cout << '\n';
				if (m >= k)
					return true;
			}
			ptr = ptr->next;
		}

		return false;
	}


	// KOL2 2023 GRUPA B


	// JUN2 2021

	int reachableInNHoops(int node, int n)
	{
		LinkedNodeInt* ptr = start;

		while (ptr)
		{
			if (ptr->node == node)
				break;
			ptr = ptr->next;
		}

		if (!ptr)
			return 0;

		return reachableInNHoops(ptr, n);
	}

	// JUN2 2021


private:
	
	int reachableInNHoops(LinkedNodeInt* node, int n)
	{
		int count = 0;
		setStatusForAllNodes(0);


		countPathsLenghtN(node, 0, n, count);

		return count;
	}

	void countPathsLenghtN(LinkedNodeInt* ptr, int currLenght, int n, int& count)
	{
		if (ptr->status != 1)
		{
			if (currLenght == n)
			{
				count++;
				return;
			}

			ptr->status = 1;
			LinkedEdgeInt* pot = ptr->adj;

			while (pot)
			{
				countPathsLenghtN(pot->dest, currLenght + 1, n, count);
				pot = pot->link;
			}
		}

		ptr->status = 0;
	}


	// KOL2 2023 GRUPA A
	bool subGraphBfs(LinkedNodeInt* ptr, int p)
	{
		bool hasP = false;

		QueueAsArrayLinkedNodeInt red(nodeNum);

		ptr->status = 2;
		red.enqueue(ptr);

		while (!red.isEmpty())
		{
			LinkedNodeInt* pom = red.dequeue();
			pom->visit();
			
			pom->status = 3;

			if (pom->node > p)
				hasP = true;

			LinkedEdgeInt* pot = pom->adj;
			while (pot)
			{
				if (pot->dest->status == 1)
				{
					pot->dest->status = 2;
					red.enqueue(pot->dest);
				}
				pot = pot->link;
			}
		}

		std::cout << '\n';
		return hasP;
	}
	// KOL2 2023 GRUPA A


	// KOL2 2023 GRUPA B
		// najobicniji bfs ali radim po 100 put da ima sve tu kao
	int subGraphNodeCount(LinkedNodeInt* ptr)
	{
		QueueAsArrayLinkedNodeInt red(nodeNum);
		int count = 0;

		ptr->status = 2;
		red.enqueue(ptr);

		while (!red.isEmpty())
		{
			LinkedNodeInt* pom = red.dequeue();
			pom->status = 3;
			pom->visit();
			count++;

			LinkedEdgeInt* pot = pom->adj;
			while (pot)
			{
				if (pot->dest->status == 1)
				{
					pot->dest->status = 2;
					red.enqueue(pot->dest);
				}
				pot = pot->link;
			}
		}

		return count;
	}
	// KOL2 2023 GRUPA B


	LinkedNodeInt* findNode(LinkedNodeInt* ptr, int curr, int val)
	{
		if (ptr->status != 1)
		{
			ptr->status = 1;

			if (ptr->isMracna)
				return nullptr;

			if (curr >= val)
				return ptr;

			LinkedEdgeInt* pot = ptr->adj;
			while (pot)
			{
				LinkedNodeInt* node = findNode(pot->dest, curr + ptr->napitak, val);
		
				if (node != nullptr)
					return node;

				pot = pot->link;
			}
		}

		ptr->status = 0;
		return nullptr;
	}

	bool canReach(LinkedNodeInt* ptrB, LinkedNodeInt* ptr, int noNodes, int currNum)
	{
		if (ptr->node == ptrB->node)
		{	
			if (currNum <= noNodes)
				return true;

			return false;
		}

		if (ptr->status != 1)
		{
			ptr->status = 1;

			LinkedEdgeInt* pot = ptr->adj;
			while (pot)
			{
				if (canReach(ptrB, pot->dest, noNodes, currNum + 1))
				{
					return true;
				}
				pot = pot->link;
			}
		}
		ptr->status = 0;
		return false;
	}

	void ShortesPath(LinkedNodeInt* end, LinkedNodeInt* ptr, int len, int& min, 
		int* path, int& pathIndex, int* outPath, int& outPathIndex)
	{
		if (ptr->node == end->node)
		{
			path[pathIndex++] = ptr->node;
			if (len < min)
			{
				for (int i = 0; i < pathIndex; i++)
				{
					outPath[i] = path[i];
				}
				outPathIndex = pathIndex;
				min = len;
			}
#ifdef PRINT
			for (int i = 0; i < pathIndex; i++)
			{
				std::cout << path[i] << ' ';
			}
			std::cout << "\n\n";
#endif
			pathIndex--;
			return;
		}

		if (ptr->status != 1)
		{
			ptr->status = 1;
			path[pathIndex++] = ptr->node;

			LinkedEdgeInt* pot = ptr->adj;
			while (pot)
			{
				ShortesPath(end, pot->dest, len + 1, min, path, pathIndex, outPath, outPathIndex);
				pot = pot->link;
			}

			ptr->status = 0;
			pathIndex--;
		}
	}

public:
	void setStatusForNode(int node, int status)
	{
		LinkedNodeInt* ptr = start;

		while (ptr)
		{
			if (ptr->node == node)
			{
				ptr->status = status;
				break;
			}

			ptr = ptr->next;
		}
	}

	bool arePathsPossible(int begin, int goal1, int goal2, int mid)
	{
		LinkedNodeInt* ptr = start;
		LinkedNodeInt* beginPtr = nullptr;
		LinkedNodeInt* goal1Ptr = nullptr;
		LinkedNodeInt* goal2Ptr = nullptr;
		LinkedNodeInt* midPtr = nullptr;

		while (ptr)
		{
			if (!beginPtr && ptr->node == begin)
				beginPtr = ptr;

			if (!goal1Ptr && ptr->node == goal1)
				goal1Ptr = ptr;

			if (!goal2Ptr && ptr->node == goal2)
				goal2Ptr = ptr;

			if (!midPtr && ptr->node == mid)
				midPtr = ptr;

			if (beginPtr && goal1Ptr && goal2Ptr && midPtr)
				break;

			ptr = ptr->next;
		}

		return arePathsPossible(beginPtr, goal1Ptr, goal2Ptr, midPtr);
	}

	void myDfs(LinkedNodeInt* start, LinkedNodeInt* ptr, int len, int& max, int* path, int& pathIndex)
	{
		if (ptr->status == 1)
		{
			if (ptr->node == start->node)
			{
				max = std::max(max, len);
				std::cout << "Cikluse duzine " << pathIndex + 1 << " :\n";
				for (int i = 0; i < pathIndex; i++)
				{
					std::cout << path[i] << " -> ";
				}
				std::cout << start->node << '\n';
			}

			return;
		}

		ptr->status = 1;
		path[pathIndex++] = ptr->node;
		LinkedEdgeInt* edging = ptr->adj;
		while(edging)
		{
			myDfs(start, edging->dest, len + 1, max, path, pathIndex);
			edging = edging->link;
		}

		ptr->status = 0;
		pathIndex--;
	}

	int longestSimpleCycle() {
		int maxLen = 0;
		std::vector<int> path; // Vector to store the current path

		LinkedNodeInt* ptr = start;
		while (ptr != nullptr) {
			setStatusForAllNodes(0);
			dfsHelper(ptr, ptr, 0, maxLen, path);
			ptr = ptr->next;
		}

		return maxLen;
	}

	void dfsHelper(LinkedNodeInt* start, LinkedNodeInt* ptr, int len, int& maxLen, std::vector<int>& path) {
		if (ptr->status == 1) {
			// Found a cycle
			if (ptr->node == start->node) {
				maxLen = std::max(len, maxLen);
				// Print the cycle
				std::cout << "Cycle found: ";
				for (int node : path) {
					std::cout << node << " ";
				}
				std::cout << start->node << std::endl; // Print the start node to complete the cycle
			}
			return;
		}

		ptr->status = 1; // Mark the node as visited
		path.push_back(ptr->node); // Add the node to the path
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr) {
			if (pEdge->dest->status != 1 || (pEdge->dest->status == 1 && pEdge->dest->node == start->node)) {
				dfsHelper(start, pEdge->dest, len + 1, maxLen, path);
			}
			pEdge = pEdge->link;
		}
		path.pop_back(); // Remove the node from the path (backtracking)
		ptr->status = 0; // Unmark the node (backtracking)
	}

	void showAllCycles()
	{
		int put[100] = { 0 };
		int lPut = 0;
		LinkedNodeInt* ptr = start;

		while (ptr)
		{
			findCycle(ptr->node, put, &lPut);
			ptr = ptr->next;
		}
	}

	void print() const;

	int topologicalOrder()
	{
		setStatusForAllNodes(0);

		LinkedNodeInt* ptr = start;

		while (ptr)
		{
			LinkedEdgeInt* pot = ptr->adj;
			while (pot)
			{
				pot->dest->status++;
				pot = pot->link;
			}
			ptr = ptr->next;
		}


#ifdef IDIOT
		while (ptr)
		{
			LinkedNodeInt* ptr2 = start;

			while (ptr2)
			{
				LinkedEdgeInt* poteg = ptr2->adj;

				while (poteg)
				{
					if (poteg->dest->node == ptr->node)
						ptr->status++;
					poteg = poteg->link;
				}
				ptr2 = ptr2->next;
			}
			ptr = ptr->next;
		}
#endif

		QueueAsArrayLinkedNodeInt red(nodeNum);

		ptr = start;
		int count = 0;

		while (ptr)
		{
			if (ptr->status == 0)
				red.enqueue(ptr);
			ptr = ptr->next;
		}

		while (!red.isEmpty())
		{
			LinkedNodeInt* ptr2 = red.dequeue();
			//ptr2->visit();
			count++;

			LinkedEdgeInt* potezi = ptr2->adj;

			while (potezi)
			{
				potezi->dest->status--;

				if (potezi->dest->status == 0)
					red.enqueue(potezi->dest);

				potezi = potezi->link;
			}
		}

		return count;
	}

	bool isCyclic()
	{
		LinkedNodeInt* ptr = start;
		int nodes = 0;
		while (ptr)
		{
			nodes++;
			ptr = ptr->next;
		}

		int topologicalCount = topologicalOrder();

		if (topologicalCount != nodes)
			return true;

		return false;
	}

private:
	bool arePathsPossible(LinkedNodeInt* beggin, LinkedNodeInt* goal1, LinkedNodeInt* goal2, LinkedNodeInt* mid)
	{
		int path[100] = { 0 };
		int pathIndex = 0;

		int outPath[100] = { 0 };
		int outIndex = 0;

		int min = nodeNum;

		setStatusForAllNodes(0);
		ShortesPath(mid, beggin, 0, min, path, pathIndex, outPath, outIndex);

		if (outIndex <= 0)
		{
			std::cout << "Ne postoji put od mid\n";
			return false;
		}
		
		std::cout << "Postoji put do mid\n";
		for (int i = 0; i < outIndex - 1; i++)
		{
			std::cout << outPath[i] << " -> ";
		}
		std::cout << outPath[outIndex - 1] << '\n';

		setStatusForAllNodes(0);
		for (int i = 0; i < outIndex; i++)
		{
			// Oznacavamo cvorove na putu od start do mid kao vec obradjen
			setStatusForNode(outPath[i], 1);
		}

		// treci pomocni niz sta da se radi
		int pom[100] = { 0 };
		int pomI = outIndex;

		for (int i = 0; i < outIndex; i++)
		{
			pom[i] = outPath[i];
		}
		setStatusForNode(mid->node, 0);


		outIndex = 0;
		pathIndex = 0;
		min = nodeNum;

		ShortesPath(goal1, mid, 0, min, path, pathIndex, outPath, outIndex);

		if (outIndex <= 0)
		{
			std::cout << "Put do goal1 ne postoji\n";
			return false;
		}
		std::cout << "Put go goal1 postoji:\n";
		for (int i = 0; i < pomI; i++)
		{
			std::cout << pom[i] << " -> ";
		}
		for (int i = 1; i < outIndex - 1; i++)
		{
			std::cout << outPath[i] << " -> ";
		}
		std::cout << outPath[outIndex - 1] << '\n';

		setStatusForAllNodes(0);
		for (int i = 0; i < pomI; i++)
		{
			setStatusForNode(pom[i], 1);
		}
		setStatusForNode(mid->node, 0);

		outIndex = 0;
		pathIndex = 0;
		min = nodeNum;

		ShortesPath(goal2, mid, 0, min, path, pathIndex, outPath, outIndex);

		if (outIndex <= 0)
		{
			std::cout << "Put do goal2 ne postoji\n";
			return false;
		}

		std::cout << "Put do goal2 postoji:\n";
		for (int i = 0; i < pomI; i++)
		{
			std::cout << pom[i] << " -> ";
		}
		for (int i = 1; i < outIndex - 1; i++)
		{
			std::cout << outPath[i] << " -> ";
		}
		std::cout << outPath[outIndex - 1] << '\n';

		return true;
	}

	void setStatusForAllNodes(int status) const;
public:
	long breadthFirstTraversal(const int& data) const;
	long depthFirstTraversalIterative(const int& data) const;
private:
	long depthFirstTraversalRecursive(LinkedNodeInt* ptr) const;
public:
	long depthFirstTraversalRecursive(const int& data) const;

	long topologicalOrderTravrsal() const;

	int findCycle(int startNode, int* put, int* lPut);

	bool cycleThroughTwoNodes(int data1, int data2, int* put, int* lPut);

	bool findPath(int dataStart, int dataEnd, int* put, int* lPut);


private:
	int findCycle(LinkedNodeInt* startNode, LinkedNodeInt* ptr, int* put, int* lPut);
	bool findPath(LinkedNodeInt* ptr, LinkedNodeInt* ptrEnd, int* put, int* lPut);

	void dfs(LinkedNodeInt* start, LinkedNodeInt* ptr);
};

