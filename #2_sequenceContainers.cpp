#include <iostream>
#include <vector>
#include <tuple>
#include <random>
#include <algorithm>
#include <string>
#include <cctype>
#include <iterator>
#include <functional>
#include <set>
#include <queue>
#include <array>
#include <list>

/*
Containers:

Sequence Containers(array and linked list):
-vector, deque, list, forward list, array

Associative containers(binary tree) - all the elements are always sorted in associative containers
- set, multiset
- map, multimap

Unordered Containers(hash table)
-Unordered set/multiset
-Unordered map/multimap

*/

std::ostream& operator<<(std::ostream& ostr, const std::list<int> &list)
{
	for (auto &i : list)
	{
		ostr << " " << i;
	}
	return ostr;
}


int main()
{

	//Vector - grows in one direction

	std::vector<int>vec; //vec.size == 0
	vec.push_back(4);
	vec.push_back(1);
	vec.push_back(8);	// vec: {4,1,8}; vec.size == 3

						//Vector specific operations:
						//--position in the vector
	std::cout << vec[2];	// 8 (no range check)
	std::cout << vec.at(2);	// 8 (throw range_error exception of out of range) -- better


							//--3 ways how to traverse vector container

	for (int i = 0; i < vec.size(); ++i)
	{
		std::cout << vec[i] << " ";
	}

	//iterator is faster and its universal way of traversing a container. 
	//I could replace vector by list and its valid. -- better

	for (std::vector<int>::iterator itr = std::begin(vec); itr != std::end(vec); ++itr)
		std::cout << *itr;

	//C++11 provides new way to traverse a container - ranged-based of loop

	for (auto it : vec)
		std::cout << it << " ";

	//Vector is a dynamically allocated contiguous array in memory. No other container provides this.
	int* p = &vec[0]; p[2] = 6;


	// Common member functions of all containers. There is no penalty of abstraction. It is very efficient and
	// all the penalty has been optimized away.

	//vec: {4,1,8}

	if (vec.empty()) { std::cout << "Not possible.\n"; }

	std::cout << vec.size(); //3

	std::vector<int> vec2(vec); //Copy constuctor, vec2: {4,1,8}

	vec.clear();

	vec2.swap(vec);  //vec2 becomes empty and vec has 3 items

					 /*
					 Properties of Vector:
					 1) fast insert/remove at the end: O(1)
					 2) slow insert/remove at the beginning or in the middle: O(n) - because the items has to be shifted.
					 3) slow search: O(n)

					 Properties of deque
					 -Same as vector except its fast insert/remove both at the beginning and at the end
					 deq.push_front(2);
					 deq.push_back(3);

					 Properties of list - double linked list
					 1) Fast insert/remove at any place inside the list O(1)
					 2) Slow search O(n) -- much slower than vector. Memory access is a bottleneck of modern CPUs. That is why they have caches
					 3) no random access, no [] operator

					 */

					 //examples - list
	std::list<int> mylist = { 5,2,9 };
	mylist.push_back(6);
	mylist.push_front(4); //mylist: {4,5,2,9,6}

	std::list<int>::iterator itr = find(std::begin(mylist), std::end(mylist), 2); //itr -> 2
	std::cout << *itr;
	mylist.insert(itr, 8); //mylist: {4,5,8,2,9,6} O(1), faster than deque or vector

	itr++;				//itr -> 9
	mylist.erase(itr); //mylist: {4,5,8,2,6}

					   //2) Slow search O(n) --much slower than vector.Memory access is a bottleneck of modern CPUs.
					   //That is why they have caches. Vector stores data in contiguous chunk of memory. 
					   //When you  you swap it using cache. It is more likely you get everything in the cache.
					   //Compare to list, chunks are stored on different places in a memory therefore you get lot of cache misses.
					   //You end up swapping data in and out in cache all the time.
					   //Each Element in a list also contains two more pointers, so it uses much more memory.

					   //List hovever, has one killing function nobody can match -- Splice O(1)
	std::list<int> mylist1 = { 1,2,3,4,5 };
	std::list<int> mylist2 = { 10,20,30,40,50 };
	//overloaded << operator


	auto it = mylist1.begin();
	std::advance(it, 2);

	mylist1.splice(it, mylist2);
	std::cout << "list1: " << mylist1 << "\n";
	std::cout << "list2: " << mylist2 << "\n";

	std::cout << "iterator is at: " << *it << std::endl;

	mylist2.splice(mylist2.begin(), mylist1, it, mylist1.end());

	/*
		list1:  1 2 10 20 30 40 50
		list2:  3 4 5
	*/
	// mylist1.splice(itr, mylist2, itr_a, itr_b);


	// Forward list - its like a list but only has forward pointer
	

	// Arrays -- you can use begin/end/size/swap with the C type arrays but you can use std::array
	// There are two big limitations to an array: 
	// 1)Size cannot be changed
	// 2)Two arrays of integers may have different type. Eg if one array has 3 integers and the other has 4.
	// if I have a function that takes 3 elements it will not take array with 4 elements since they are diffetent type
	
	//int a[3] = { 3,4,5 };
	std::array<int, 3> a = { 3,4,5 }; 

	a.begin();
	a.end();
	a.size();
	std::swap(a[1], a[2]);


	std::cout << std::endl;

	system("pause");
	return 0;

}
