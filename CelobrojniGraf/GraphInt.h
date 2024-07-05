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

// random funkcije koje sam pisao, neke se koriste u neki zadaci
public:
	void toUndirected();
	int findCycle(int startNode, int* put, int* lPut);
	bool cycleThroughTwoNodes(int data1, int data2, int* put, int* lPut);
	bool findPath(int dataStart, int dataEnd, int* put, int* lPut);
	void ShortestPath(int startNode, int endNode);
	void setStatusForNode(int node, int status);
	void showAllCycles();
	void countPathsLenghtN(LinkedNodeInt* ptr, int currLenght, int n, int& count);

private:
	int findCycle(LinkedNodeInt* startNode, LinkedNodeInt* ptr, int* put, int* lPut);
	bool findPath(LinkedNodeInt* ptr, LinkedNodeInt* ptrEnd, int* put, int* lPut);
// random

// JUN 2023
public:
	int cudanBFS(int data);
	void connectMaxAndMin();
private:
	int cudanBFS(LinkedNodeInt* ptr);
// JUN 2023

// SEP 2023
public:
	LinkedNodeInt* findNode(int val);
private:
	LinkedNodeInt* findNode(LinkedNodeInt* ptr, int curr, int val);
// SEP 2023

// OKT 2023
public:
	bool canReach(int A, int B, int noNodes);
private:
	bool canReach(LinkedNodeInt* ptrB, LinkedNodeInt* ptr, int noNodes, int currNum);
// OKT 2023

// DEC 2023
public:
	int LongestSimpleCycle();
private:
	// nema potrebe za ovaj niz samo sam teo da pise ciklusi da vidim dal je tacno
	// samo start, ptr, len i max su potrebni parametri
	void myDfs(LinkedNodeInt* start, LinkedNodeInt* ptr, int len, int& max, int* path, int& pathIndex);
// DEC 2023

// KOL2 2023 GRUPA A
public:
	int subGraphCnt(int p);
private:
	bool subGraphBfs(LinkedNodeInt* ptr, int p);
// KOL2 2023 GRUPA A

// KOL2 2023 GRUPA B
public:
	bool doesConnectedComponentExist(int k);
private:
	// najobicniji bfs ali radim po 100 put da ima sve tu kao
	int subGraphNodeCount(LinkedNodeInt* ptr);
// KOL2 2023 GRUPA B

// JUN2 2023
public:
	bool isCyclic();
private:
	int topologicalOrder();
// JUN2 2023

// JAN 2024
public:
	// Ovo dosta bolje moze, treba se koristi onaj previous pointer da se cuva
	// putanja a ne 100 nizova da se prave al mrzi me da ga ispravljam radi i ovako
	bool arePathsPossible(int begin, int goal1, int goal2, int mid);
private:
	bool arePathsPossible(LinkedNodeInt* beggin, LinkedNodeInt* goal1, LinkedNodeInt* goal2, LinkedNodeInt* mid);
	void ShortesPath(LinkedNodeInt* end, LinkedNodeInt* ptr, int len, int& min,
		int* path, int& pathIndex, int* outPath, int& outPathIndex);
// JAN 2024

// JUN2 2021
public:
	int reachableInNHoops(int node, int n);
private:
	int reachableInNHoops(LinkedNodeInt* node, int n);
// JUN2 2021


public:
	void print() const;
	void setStatusForAllNodes(int status) const;
public:
	long breadthFirstTraversal(const int& data) const;
	long depthFirstTraversalIterative(const int& data) const;
private:
	long depthFirstTraversalRecursive(LinkedNodeInt* ptr) const;
public:
	long depthFirstTraversalRecursive(const int& data) const;
	long topologicalOrderTravrsal() const;
};

