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
	LinkedEdgeInt* edging = ptr->adj;
	while (edging != nullptr)
	{
		setStatusForAllNodes(0);
		ret = findCycle(ptr, edging->dest, put, lPut);
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

		edging = edging->link;
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




