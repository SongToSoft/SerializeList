#pragma once

#include "ListNode.h"
#include <iostream>
#include <fstream>

class ListRand {
public:
	ListRand();
	~ListRand();
	ListNode* Add(const std::string& value);
	void AddRandomLink(int nodeIndex, int targetIndex);
	void Print();
	void Serialize(std::ofstream &out);
	void Deserialize(std::ifstream &in);

private:
	ListNode* Head;
	ListNode* Tail;
	int Count;
};