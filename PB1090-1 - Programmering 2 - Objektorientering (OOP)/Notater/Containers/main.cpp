import std;

import myLinkedList;

int main() {
	// Sequence containers
	//	Data can be accessed sequentially
	std::array<int, 10> array;
	std::vector<int> vector;
	std::deque<int> deque;
	std::forward_list<int> s_list;
	std::list<int> d_list;

	// Associative containers
	//	Can be searched quickly
	std::set<std::string, int> set;
	std::map<std::string, int> map;

	// Container adaptors
	//	Different interfaces for sequential containers
	std::stack<int> stack;
	std::queue<int> queue;
	
	MyList<int> list2;
	list2.push_back(1);
	list2.push_back(2);
	list2.push_back(3);



	return 0;
}