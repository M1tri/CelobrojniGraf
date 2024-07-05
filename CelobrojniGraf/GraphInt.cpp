#include "GraphInt.h"

#include <iostream>
using namespace std;

#include "QueueAsArrayInt.h"
#include "StackAsArrayInt.h"

GraphAsListsInt::GraphAsListsInt() : start(nullptr), nodeNum()
{
}

GraphAsListsInt::~GraphAsListsInt()
{
//	cout << "Not implemented!" << endl;
}

LinkedNodeInt* GraphAsListsInt::findNode(const int& data) const
{
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr && ptr->node != data)
		ptr = ptr->next;
	return ptr;
}

LinkedEdgeInt* GraphAsListsInt::findEdge(const int& dataSrc, const int& dataDest) const
{
	LinkedNodeInt* ptr = findNode(dataSrc);
	if (ptr == nullptr)
		return nullptr;
	LinkedEdgeInt* pEdge = ptr->adj;
	while (pEdge != nullptr && pEdge->dest->node != dataDest)
		pEdge = pEdge->link;
	return pEdge;
}

void GraphAsListsInt::insertNode(const int& data)
{
	start = new LinkedNodeInt(data, nullptr, start);
	nodeNum++;
}

bool GraphAsListsInt::insertEdge(const int& dataSrc, const int& dataDest, const double& weight /*= 0*/)
{
	LinkedNodeInt* pSrc = nullptr;
	LinkedNodeInt* pDest = nullptr;
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr && (pSrc == nullptr || pDest == nullptr)) {
		if (ptr->node == dataSrc) {
			pSrc = ptr;
		}
		else if (ptr->node == dataDest) {
			pDest = ptr;
		}
		ptr = ptr->next;
	}
	if (pSrc == nullptr || pDest == nullptr)
		return false;
	pSrc->adj = new LinkedEdgeInt(pDest, pSrc->adj);
	return true;
}

bool GraphAsListsInt::deleteEdge(const int& dataSrc, const int& dataDest)
{
	LinkedNodeInt* pSrc = findNode(dataSrc);
	if (pSrc == nullptr)
		return false;

	LinkedEdgeInt* pEdgePrev = nullptr;
	LinkedEdgeInt* pEdge = pSrc->adj;
	while (pEdge != nullptr && pEdge->dest->node != dataDest) {
		pEdgePrev = pEdge;
		pEdge = pEdge->link;
	}
	if (pEdge == nullptr)
		return false;

	if (pEdgePrev == nullptr)
		pSrc->adj = pEdge->link;
	else
		pEdgePrev->link = pEdge->link;

	delete pEdge;

	return true;
}

void GraphAsListsInt::deleteEdgeToNode(const LinkedNodeInt* pDest)
{
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr)
	{
		LinkedEdgeInt* pEdgePrev = nullptr;
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr && pEdge->dest != pDest) {
			pEdgePrev = pEdge;
			pEdge = pEdge->link;
		}
		if (pEdge != nullptr)
		{
			if (pEdgePrev == nullptr)
				ptr->adj = pEdge->link;
			else
				pEdgePrev->link = pEdge->link;
		}
		ptr = ptr->next;
	}
}

bool GraphAsListsInt::deleteNode(const int& data)
{
	LinkedNodeInt* prev = nullptr;
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr && ptr->node != data) {
		prev = ptr;
		ptr = ptr->next;
	}
	if (ptr == nullptr)
		return false;

	LinkedEdgeInt* pEdge = ptr->adj;
	while (pEdge != nullptr) {
		LinkedEdgeInt* pEdgeTmp = pEdge->link;
		delete pEdge;
		pEdge = pEdgeTmp;
	}
	ptr->adj = nullptr;

	deleteEdgeToNode(ptr);

	if (prev == nullptr)
		start = start->next;
	else
		prev->next = ptr->next;

	delete ptr;
	nodeNum--;

	return true;
}

void GraphAsListsInt::print() const
{
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr)
	{
		cout << ptr->node << " -> ";
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr) {
			cout << pEdge->dest->node << " | ";
			pEdge = pEdge->link;
		}
		cout << endl;
		ptr = ptr->next;
	}
}

void GraphAsListsInt::setStatusForAllNodes(int status) const
{
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr) 
	{	
		ptr->status = status;
		ptr = ptr->next;
	}
}

long GraphAsListsInt::breadthFirstTraversal(const int& data) const
{
	long retVal = 0;

	LinkedNodeInt* ptr = findNode(data);
	if (ptr == nullptr)
		return 0;

	setStatusForAllNodes(1);

	QueueAsArrayLinkedNodeInt queue(nodeNum);
	queue.enqueue(ptr);
	ptr->status = 2;
	while (!queue.isEmpty()) {
		ptr = queue.dequeue();
		ptr->status = 3;
		ptr->visit();
		retVal += 1;
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr) {
			if (pEdge->dest->status == 1) {
				queue.enqueue(pEdge->dest);
				pEdge->dest->status = 2;
			}
			pEdge = pEdge->link;
		}
	}
	cout << endl;
	return retVal;
}

long GraphAsListsInt::depthFirstTraversalIterative(const int& data) const
{
	long retVal = 0;

	LinkedNodeInt* ptr = findNode(data);
	if (ptr == nullptr)
		return 0;

	setStatusForAllNodes(1);

	StackAsArrayLinkedNodeInt stack(nodeNum);
	stack.push(ptr);
	ptr->status = 2;
	while (!stack.isEmpty()) {
		ptr = stack.pop();
		ptr->status = 3;
		ptr->visit();
		retVal += 1;
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr) {
			if (pEdge->dest->status == 1) {
				stack.push(pEdge->dest);
				pEdge->dest->status = 2;
			}
			pEdge = pEdge->link;
		}
	}
	cout << endl;
	return retVal;
}

long GraphAsListsInt::depthFirstTraversalRecursive(LinkedNodeInt* ptr) const
{
	int retVal = 0;
	if (ptr->status != 1) {
		ptr->visit();
		ptr->status = 1;
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr) {
			retVal += depthFirstTraversalRecursive(pEdge->dest);
			pEdge = pEdge->link;
		}
		retVal++;
	}
	return retVal;
}

long GraphAsListsInt::depthFirstTraversalRecursive(const int& data) const
{
	LinkedNodeInt* pNode = nullptr;
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr) {
		ptr->status = 0;
		if (ptr->node == data) {
			pNode = ptr;
		}
		ptr = ptr->next;
	}

	if (pNode == nullptr)
		return 0;

	return depthFirstTraversalRecursive(pNode);
}

long GraphAsListsInt::topologicalOrderTravrsal() const
{
	int retVal = 0;

	setStatusForAllNodes(0);

	LinkedNodeInt* ptr = start;
	while (ptr != nullptr) {
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr) {
			pEdge->dest->status += 1;
			pEdge = pEdge->link;
		}
		ptr = ptr->next;
	}

	QueueAsArrayLinkedNodeInt queue(nodeNum);
	ptr = start;
	while (ptr != nullptr) {
		if (ptr->status == 0)
			queue.enqueue(ptr);
		ptr = ptr->next;
	}

	while (!queue.isEmpty()) {
		ptr = queue.dequeue();
		ptr->visit();
		retVal += 1;
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr) {
			pEdge->dest->status--;
			if (pEdge->dest->status == 0)
				queue.enqueue(pEdge->dest);
			pEdge = pEdge->link;
		}
	}
	cout << endl;
	return retVal;
}

// TODO: Realizovati metod koji odredjuje i prikazuje jedan (bilo koji) ciklus
//		 u grafu koji prolazi kroz dva zadata cvora i ne mora biti prost.


// random funkcije
bool GraphAsListsInt::cycleThroughTwoNodes(int data1, int data2, int* put, int* lPut)
{
	LinkedNodeInt* ptr = start;

	while (ptr)
	{
		LinkedEdgeInt* pot = ptr->adj;

		while (pot)
		{
			bool foundFirst = false;
			bool foundSecond = false;
			setStatusForAllNodes(0);
			int ret = findCycle(ptr, pot->dest, put, lPut);
			if (ret != 0)
			{
				for (int i = 0; i < *lPut; i++)
				{
					if (put[i] == data1)
					{
						foundFirst = true;
					}

					if (put[i] == data2)
					{
						foundSecond = true;
					}
				}

				if (foundFirst && foundSecond)
				{
					return true;
				}

				*lPut = 0;

			}

			pot = pot->link;
		}
		ptr = ptr->next;
	}

	return false;
}
int GraphAsListsInt::findCycle(int startNode, int* put, int* lPut)
{
	LinkedNodeInt* ptr = start;

	while (ptr != nullptr)
	{
		if (ptr->node == startNode)
		{
			break;
		}

		ptr = ptr->next;
	}

	if (ptr == nullptr)
		return 0;

	int ret = 0;
	LinkedEdgeInt* edge = ptr->adj;
	while (edge != nullptr)
	{
		setStatusForAllNodes(0);
		ret = findCycle(ptr, edge->dest, put, lPut);
		if (ret != 0)
		{
			std::cout << startNode << " -> ";
			for (int i = *lPut - 1; i > 0; i--)
			{
				std::cout << put[i] << " -> ";
			}
			std::cout << startNode << '\n';

			*lPut = 0;
		}

		edge = edge->link;
	}

	return 0;
}
int GraphAsListsInt::findCycle(LinkedNodeInt* startNode, LinkedNodeInt* ptr, int* put, int* lPut)
{
	if (ptr->node == startNode->node)
	{
		put[(*lPut)++] = startNode->node;

		return 1;
	}

	int retVal = 0;
	if (ptr->status != 1)
	{
		ptr->status = 1;

		LinkedEdgeInt* poteg = ptr->adj;

		while (poteg && *lPut == 0)
		{
			retVal = findCycle(startNode, poteg->dest, put, lPut);
			poteg = poteg->link;
		}

		if (*lPut != 0)
		{
			put[(*lPut)++] = ptr->node;
		}
	}

	ptr->status = 0;

	return retVal;
}
bool GraphAsListsInt::findPath(int dataStart, int dataEnd, int* put, int* lPut)
{
	LinkedNodeInt* ptrStart = nullptr, *ptrEnd = nullptr, *iter = start;

	while (iter)
	{
		if (ptrStart == nullptr && iter->node == dataStart)
			ptrStart = iter;

		if (ptrEnd == nullptr && iter->node == dataEnd)
			ptrEnd = iter;

		if (ptrStart != nullptr && ptrEnd != nullptr)
			break;
		
		iter = iter->next;
	}

	if (!ptrStart || !ptrEnd)
		return false;

	LinkedEdgeInt* pot = ptrStart->adj;
	setStatusForAllNodes(0);

	while (pot)
	{
		if (findPath(pot->dest, ptrEnd, put, lPut))
		{
			return true;
		}
		pot = pot->link;
	}

	return false;
}
bool GraphAsListsInt::findPath(LinkedNodeInt* ptr, LinkedNodeInt* end, int* put, int* lPut)
{
	if (ptr->node == end->node)
	{
		put[(*lPut)++] = ptr->node;
		return true;
	}

	bool toRet = false;
	if (ptr->status != 1)
	{
		ptr->status = 1;
		LinkedEdgeInt* pot = ptr->adj;
		while (pot && *lPut == 0)
		{
			if (*lPut == 0)
			{
				toRet = findPath(pot->dest, end, put, lPut);
				pot = pot->link;
			}

			if (*lPut != 0)
			{
				put[(*lPut)++] = ptr->node;
			}
		}
	}

	return toRet;
}
void GraphAsListsInt::toUndirected()
{
	LinkedNodeInt* ptr = start;

	while (ptr)
	{
		LinkedEdgeInt* edge = ptr->adj;

		while (edge)
		{
			LinkedEdgeInt* potezi = edge->dest->adj;

			while (potezi && potezi->dest->node != ptr->node)
			{
				potezi = potezi->link;
			}

			if (potezi == nullptr)
			{
				insertEdge(edge->dest->node, ptr->node);
			}
			edge = edge->link;
		}
		ptr = ptr->next;
	}
}
void GraphAsListsInt::setStatusForNode(int node, int status)
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
void GraphAsListsInt::showAllCycles()
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
void GraphAsListsInt::ShortestPath(int startNode, int endNode)
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
void GraphAsListsInt::countPathsLenghtN(LinkedNodeInt* ptr, int currLenght, int n, int& count)
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

// random funkcije

// JUN 2023
void GraphAsListsInt::connectMaxAndMin()
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
int GraphAsListsInt::cudanBFS(int data)
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
int GraphAsListsInt::cudanBFS(LinkedNodeInt* ptr)
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
// JUN2023

// SEP 2023
LinkedNodeInt* GraphAsListsInt::findNode(int val)
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
LinkedNodeInt* GraphAsListsInt::findNode(LinkedNodeInt* ptr, int curr, int val)
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
// SEP 2023

// OKT 2023
bool GraphAsListsInt::canReach(int A, int B, int noNodes)
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
bool GraphAsListsInt::canReach(LinkedNodeInt* ptrB, LinkedNodeInt* ptr, int noNodes, int currNum)
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
// OKT 2023

// DEC 2023
int GraphAsListsInt::LongestSimpleCycle()
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
void GraphAsListsInt::myDfs(LinkedNodeInt* start, LinkedNodeInt* ptr, int len, int& max, int* path, int& pathIndex)
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
		LinkedEdgeInt* edge = ptr->adj;
		while (edge)
		{
			myDfs(start, edge->dest, len + 1, max, path, pathIndex);
			edge = edge->link;
		}

		ptr->status = 0;
		pathIndex--;
	}
// DEC 2023	

// KOL2 2023 GRUPA B
bool GraphAsListsInt::doesConnectedComponentExist(int k)
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
int GraphAsListsInt::subGraphNodeCount(LinkedNodeInt* ptr)
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

// KOL2 2023 GRUPA A
int GraphAsListsInt::subGraphCnt(int p)
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
bool GraphAsListsInt::subGraphBfs(LinkedNodeInt* ptr, int p)
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

// JUN2 2023
bool GraphAsListsInt::isCyclic()
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
int GraphAsListsInt::topologicalOrder()
	{
		setStatusForAllNodes(0);

		LinkedNodeInt* ptr = start;

		// status je sada ulazni stepen cvora
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
// JUN2 2023

// JAN 2024
bool GraphAsListsInt::arePathsPossible(int begin, int goal1, int goal2, int mid)
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
bool GraphAsListsInt::arePathsPossible(LinkedNodeInt* beggin, LinkedNodeInt* goal1, LinkedNodeInt* goal2, LinkedNodeInt* mid)
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
void GraphAsListsInt::ShortesPath(LinkedNodeInt* end, LinkedNodeInt* ptr, int len, int& min,
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
// JAN 2024


// JUN2 2021
int GraphAsListsInt::reachableInNHoops(int node, int n)
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
int GraphAsListsInt::reachableInNHoops(LinkedNodeInt* node, int n)
	{
		int count = 0;
		setStatusForAllNodes(0);


		countPathsLenghtN(node, 0, n, count);

		return count;
	}
// JUN2 2021
