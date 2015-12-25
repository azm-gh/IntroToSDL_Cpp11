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
#include <map>

/*
	Associative Containers:
		-Typically implemented with binary tree
		- The key attribute of AC is that its always sorted
		- When you insert item into binary tree, it will be inserted in proper location
		- Same with removal. It will be rearanged.

		- Always sorted by default criteria <
		- No push_back(), push_front() 
		- The name associative comes from the map where a value is associated with a key
		  In case of Set you can think of it as the value is the same as the key
*/


int main()
{

	// 1) Set
	//	-- no duplicates (in case of set)
	//	-- logarthmic searching time when it comes to inserting/finding is the most important feature of  AC
	//  -- traversing is slow (compared to vector and deque) but same as list
	//  -- no random access, no [] operator

	std::set<int> myset;
	myset.insert(3);	//myset {3}
	myset.insert(1);	//myset {1,3}
	myset.insert(7);	//myset {1,3,7} O(log(n)) -- insertion always takes logarithimic time

	std::set<int>::iterator it;
	it = myset.find(7); // O(log(n)), it points to 7 -- fast as well. Faster than sequence containers
						// in case of sequnece containers it takes linear time to search
						// Sequence containers don't even have find() member function(it takes too long to find).
	
	//The insertion returns a pair. The second parameter is bool. It inform us whether the insertion was
	//sucessfull or not. In this case its false and it points to 3
	std::pair<std::set<int>::iterator, bool> ret;
	ret = myset.insert(3);	//no new element inserted
	if (ret.second == false)
		it = ret.first;		// 'it' now points to element 3

	myset.insert(it, 9);	// myset {1,3,7,9} O(log(n)) => O(1). The insertion cannot be decided by you.
							// it is not inserted in front of 3 but at the end. 'it' in this case is used as
							// a hint to find where 9 is to be inserted. If you provide good hint you can reduce
							// the insertion time from logarithimc to constant time O(log(n)) => O(1).
							// 'it' is still pointing to 3.
							
	myset.erase(it);		//myset {1,7,9}
	myset.erase(7);			//myset {1,9}
	
							// Non of the sequence containers provide this kind of erase 

	std::cout << std::endl;


	// 2. Multiset - is like a set but allows duplicate items. Insertion is always sucessfull.
	std::multiset<int> myset1;

	/*  for set/multiset the value of the element cannot be modified. It is read only
		int *it = 10;  that means that dereference of a iterator is a constant. You cannot assign value to it.
		If you modify the set or multiset value you many corrupt the structure

		You can sort AC not just by operator < but also by key/pair values
		This is why we have Map and Multimap. These two has the same interface as set and multiset
		except each element is pair of key and value */

	//3. Map -- no duplicates
	std::map<char, int> mymap; // a map from char to int
	mymap.insert(std::pair<char, int>('a', 100));
	mymap.insert(std::make_pair('z', 200));

	std::map<char, int>::iterator it1 = mymap.begin();
	mymap.insert(it1, std::pair<char, int>('b', 300)); // 'it' is a hint

	it1 = mymap.find('z');  // O(log(n)) -- fast

	//showing contents
	for (it1 = mymap.begin(); it1 != mymap.end(); it1++)
		std::cout << (*it1).first << " => " << (*it1).second << std::endl;

	// 4. Multimap
	//	-- is a map but allows duplicates
	// for both map and multimap, keys cannot be modified
	// type of *it: pair<const char, int>
	// (*it).first = 'd'   --- results in error



	std::cout << std::endl;

	system("pause");
	return 0;

}
