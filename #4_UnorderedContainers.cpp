#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <string>
#include <iterator>
#include <set>
#include <queue>
#include <array>
#include <list>
#include <map>
#include <unordered_set>
#include <unordered_map>
 

/*
	C++ 11 introduces Unordered Associative Container
	 - Unordered Set or Multiset
	 - Unordered Map or Multimap
	 - Internally unordered container is implemented with hash table which is an array of linked list.
	   Also called array of buckets. And linked lists are called entries
*/

void foo(const std::unordered_map<char, std::string>& m)
{
	//m['S'] = "SUNDAY";				//will not compile, m is not modifyable
	//std::cout << m['S'] << std::end;  //-- error again 
	auto itr = m.find('S');
	if (itr != m.end())
		std::cout << (*itr).first << std::endl;

}



int main()
{
	std::unordered_set<std::string> myset = { "red", "green", "blue" };
	std::unordered_set<std::string>::const_iterator itr = myset.find("green"); // O(1)
	if (itr != myset.end()) //important check - because if itr pointing to an end, its undefined behaviour.
		std::cout << *itr << std::endl;
	myset.insert("yellow"); // O(1)

	std::vector<std::string> vec = { "purple","pink" };
	myset.insert(vec.begin(), vec.end());
	
	//Hash table specific APIs:
	std::cout << "load_factor = " << myset.load_factor() << std::endl; //ratio of elements and buckets
	std::string x = "red";
	std::cout << x << " is in the bucket #" << myset.bucket(x) << std::endl;
	std::cout << "Total bucket #" << myset.bucket_count() << std::endl;

	//hash collision => performance degrade -- HC means many items are inserted in the same buckets
	// constant time -> linear time O(1) -> O(n)

	/*
		Properties of unordered containers:
		1) Fastest search/insert at any place O(1)
		   Associative container takes O(log(n)), vector,deque takes O(n)
		   list takes O(1) to insert(assuming you have a pointer in place), O(n) to search
		2) Unordered set/multiset: element value cannot be changed
		   Unordered map/multimap: element key cannot be changed.
	*/

	// Associative Array - can be implemented with map or unordered map

	std::unordered_map<char, std::string> day = { {'S', "Sunday"}, {'M', "Monday"} };
	std::cout << day['S'] << std::endl; // No range check
	std::cout << day.at('S') << std::endl; // Has range check

	std::vector<int> vec1 = { 1,2,3 };
	//vec1[5] = 5; // compile error

	day['W'] = "Wednesday"; //inserting {'W', "Wednesday"}
	day.insert(std::make_pair('F', "Friday")); //Inserting {'F', "Friday"}


	day.insert(std::make_pair('M', "MONDAY")); //fail to modify, it's unordered_map
	day['M'] = "MONDAY"; // Succeed to modify. Subscript operator has ability to modify the container.

	//This has following consequences -- see void foo above maim
	foo(day);

	/*
		Notes about Associative Array:
		1) Search time: unordered_map, O(1); map, O(log(n)); -- guaranteed
		2) Unordered map can degrade to O(n);
		3) Can't use multimap an unordered_multimap, they dont have [] <subscript operator>
	*/

	/*
		Container Adapters
		  - provides restricted interface to meet specia needs
		  - Implemented with fundamental container classes

		  1) stack: LIFO, push(), pop(), top()
		  2) queue: FIFO, push(), pop(), front(), back()
		  3) Priority queue: first item always has the greatest priority. push(), pop(), top()
	--
		
		Another way of categorizing containers:
			1) Array based containers: vector, deque
			2) Node based containers: list + associative containers + unordered containers

			-- Array based containers invalidates pointers:
				native pointers, iterators, references
	
	*/

	std::vector<int> vec2 = { 1,2,3,4 };
	int *p = &vec2[2]; // p points to 3
	vec2.insert(vec2.begin(), 0);
	std::cout << *p << std::endl; // 2 or ? -- undefined behaviour


	
	

	std::cout << std::endl;

	system("pause");
	return 0;

}
