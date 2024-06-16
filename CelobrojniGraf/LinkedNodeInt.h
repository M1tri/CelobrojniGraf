#pragma once

#include "LinkedEdgeInt.h"

class LinkedNodeInt
{
public:
	int node;
	LinkedEdgeInt* adj;
	LinkedNodeInt* next;
	int status;

	// SEP 2022
	bool isMracna;
	int napitak;


	LinkedNodeInt* prev;


	LinkedNodeInt();
	LinkedNodeInt(int nodeN);
	LinkedNodeInt(int node, bool isMracna, int napitak) : node(node), isMracna(isMracna), napitak(napitak)
	{}
	

	LinkedNodeInt(int nodeN, LinkedEdgeInt* adjN, LinkedNodeInt* nextN);
	LinkedNodeInt(int nodeN, LinkedEdgeInt* adjN, LinkedNodeInt* nextN, int statusN);

	void visit();
};
