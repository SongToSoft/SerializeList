#include "ListRand.h"
#include <iostream>
#include <unordered_map>

ListRand::ListRand() {
	Head = nullptr;
	Tail = nullptr;
	Count = 0;
}

ListRand::~ListRand() {
	auto pointer = Head;
	while (pointer) {
		auto node = pointer;
		pointer = pointer->Next;
		delete node;
		node = nullptr;
	}
}

ListNode* ListRand::Add(const std::string& value) {
	ListNode* node = new ListNode();
	node->Data = value;
	if (Tail) {
		Tail->Next = node;
	}
	node->Prev = Tail;
	node->Rand = nullptr;

	Tail = node;
	if (!Head) {
		Head = node;
	}
	++Count;
	return node;
}

void ListRand::AddRandomLink(int nodeIndex, int targetIndex) {
	if (((nodeIndex < 0) || (nodeIndex > Count)) ||
		  ((targetIndex < 0) || (targetIndex > Count))) {
		std::cout << "Index out of bounds list" << std::endl;
		return;
	}
	ListNode* nodePointer = nullptr;
	ListNode* targetPointer = nullptr;
	int counter = 0;
	auto pointer = Head;
	while (pointer) {
		if (nodeIndex == counter) {
			nodePointer = pointer;
		}
		if (targetIndex == counter) {
			targetPointer = pointer;
		}
		if ((nodePointer) && (targetPointer)) {
			nodePointer->Rand = targetPointer;
			break;
		}
		pointer = pointer->Next;
		++counter;
	}
}

void ListRand::Print() {
	auto pointer = Head;
	while (pointer) {
		std::cout << pointer->Data << " ";
		if (pointer->Rand) {
			std::cout << "-(" << pointer->Rand->Data << ") ";
		}
		pointer = pointer->Next;
	}
	std::cout << std::endl;
}

void ListRand::Serialize(std::ofstream &out) {
	std::unordered_map<ListNode*, int> nodeMap;
	int counter = 0;
	auto pointer = Head;
	while (pointer) {
		nodeMap.insert({ pointer, counter });
		++counter;
		pointer = pointer->Next;
	}
	pointer = Head;
	while (pointer) {
		out << pointer->Data << std::endl;
		if (pointer->Rand)
		{
			out << nodeMap[pointer->Rand] << std::endl;
		}
		else
		{
			out << -1 << std::endl;
		}
		pointer = pointer->Next;
	}
}

void ListRand::Deserialize(std::ifstream &in) {
	std::unordered_map<ListNode*, int> nodeMap;
	std::unordered_map<int, ListNode*> nodeIndexMap;
	std::string line;
	int counter = 0;
	while (getline(in, line)) {
		auto node = Add(line);
		getline(in, line);
		nodeMap.insert({ node, std::stoi(line) });
		nodeIndexMap.insert({ counter, node });
		++counter;
	}
	auto pointer = Head;
	while (pointer) {
		if (nodeMap[pointer] != (-1)) {
			pointer->Rand = nodeIndexMap[nodeMap[pointer]];
		}
		pointer = pointer->Next;
	}
}