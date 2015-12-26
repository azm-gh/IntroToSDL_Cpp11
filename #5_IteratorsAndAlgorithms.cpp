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
#include <forward_list>

// Crash course to pointers and references 


std::vector <int> vec1;							// a global vector of ints

void f() {
	vec1.push_back(1);							// add to the global vector
	std::vector <int>::iterator it = vec1.begin();
	*it = 2;									// change what was 1 to 2
	int * p = &(*it);							// get pointer to first element
	*p = 3;										// change what was 2 to 3
}

struct Sum  //  overloaded operator() in a functor to compute sum
{
	int sum;
	Sum() { sum = 0; }
	void operator()(int n) { sum += n; }
};

bool isOdd(int i)
{
	return i % 2;
}


int main()
{

	// Iterators

	// 1) Random access iterator: vector,deque,array

	std::vector<int>::iterator itr;
	//itr = itr + 5; //advance itr by 5
	std::vector<int>vec = { 1,2,3,4,5 };
	for (itr = vec.begin(); itr != vec.end(); itr++)
		std::cout << "Address: " << &(*itr) << " ";		// Return the address of the thing pointed to by the iterator
														//std::cout << *itr << " ";
	itr = vec.begin();									// without this line, the line below itr++ would throw an exception
	itr++;
	itr--;

	// 2) Bidirectional Iterator: list, set/multiset, map/multimap (list + associative containers)
	std::list<int>::iterator itr1;
	std::list<int>list1 = { 1,2,3,4,5 };
	itr1 = list1.begin();
	++itr1;
	--itr1;

	// 3) Forward Iterator: forward_list
	std::forward_list<int>::iterator itr2;
	std::forward_list<int>fwlist1 = { 1,2,3,4,5 };
	itr2 = fwlist1.begin();
	++itr2;
	// --itr2; -- nope

	//Unordered containers provide 'at least' forward iterators

	// 4) Input iterator: read and process values while moving forward. Cannot write
	int x = *itr2;
	std::cout << "Itr2: " << x << std::endl;

	// 5) Output iterator: output values while iterating forward. You can write into 
	//	  dereferenced itr but cannot read from it
	*itr2 = 100;
	std::cout << "Itr2: " << *itr2 << std::endl;

	//Every container has a iterator and a const_iterator
	std::list<int>::iterator itr3;
	std::set<int>::const_iterator citr;
	std::set<int>::const_iterator citr2;	//read only access to container elements

	std::set<int> myset = { 2,4,1,5,1,9 };
	for (citr = myset.begin(); citr != myset.end(); ++citr)
	{
		std::cout << *citr << std::endl;
	}

	Sum s = std::for_each(myset.begin(), myset.end(), Sum());

	/*
	Will not work since its const
	std::for_each(myset.cbegin(), myset.cend(), [](int n) {n++; });

	Will also not work since set elements are immutable
	std::for_each(myset.begin(), myset.end(), [](int &n) {n++; });
	*/

	//However it will work for lists
	std::list<int> mylist = { 2,4,1,5,1,9 };
	std::for_each(mylist.begin(), mylist.end(), [](int &n) {n++; });


	//Iterator functions
	citr = myset.begin();
	citr2 = myset.begin();
	std::advance(citr, 2);	// Move itr forward 2 spots itr +=2
	std::advance(citr2, 4);
	std::distance(citr, citr2); // for non random access iterators

	std::cout << std::endl;
	std::cout << s.sum << std::endl;

	/*
	Iterator Adaptor(Predefined Iterator)
	- A special, more powerful iterator
	1.Insert iterator
	2.Stream iterator
	3.Reverse iterator
	4.Move iterator (C++11)
	*/

	// 1. Insert iterator

	std::vector<int> vec1 = { 4,5 };
	std::vector<int> vec2 = { 12,14,16,18 };
	std::vector<int>::iterator it = find(vec2.begin(), vec2.end(), 16);

	std::insert_iterator<std::vector<int> > i_itr(vec2, it);
	std::copy(vec1.begin(), vec1.end(), // source
		i_itr);							// destination
	for (const auto &z : vec2) //vec 2: {12,14,4,5,16,18}
		std::cout << z << " ";
	std::cout << std::endl;

	//Other insert iterators: back_insert_iterator, front_insert_iterator

	// 2.Stream iterators
	std::string input;
	std::vector<std::string> vec4 = { "car", "ship", "plane" };

	/*
	//commented out because it requires input. Uncomment if you want to test

	std::copy(std::istream_iterator<std::string>(std::cin), std::istream_iterator<std::string>(), //default constructor represents end of the stream
	std::back_inserter(vec4));

	std::copy(vec4.begin(), vec4.end(), std::ostream_iterator<std::string>(std::cout, " ")); //prints the vec4

	//combining these two above statemenets above:

	std::copy(std::istream_iterator<std::string>(std::cin), std::istream_iterator<std::string>(),
	std::ostream_iterator<std::string>(std::cout, " "));
	*/

	// 3. Reverse iterator
	std::vector<int> vecr = { 4,5,6,7 };
	std::reverse_iterator<std::vector<int>::iterator> ritr;
	for (ritr = vecr.rbegin(); ritr != vecr.rend(); ritr++)
		std::cout << *ritr << std::endl;

	// Algorithms

	std::vector<int> vec6 = { 4,2,5,1,3,9 };
	std::vector<int>::iterator itrmin = std::min_element(vec6.begin(), vec6.end()); // itr -> 1
	std::cout << "Min values is: " << *itrmin << std::endl;

	// Note 1: Algorithm always process ranges in half-open way: [begin, end)
	std::vector<int>::iterator sort_itr;
	std::sort(vec6.begin(), itrmin); // 2,4,5,1,3,9 (1 is not included. Itr is pointing to 1)
	std::reverse(itrmin, vec6.end()); // 2,4,5,9,3,1. Also itr -> 9
	std::cout << "Min values is: " << *itrmin << std::endl;
	
	//note 2:
	std::vector<int> vec7(3);
	std::copy(itrmin, vec6.end(), // source
		vec7.begin());			  // destination

	for (const auto &z : vec7) 
		std::cout << z << " ";  // 9,3,1
	std::cout << std::endl;

	//Note 3:
	std::vector<int> vec_back;
	copy(itrmin, vec6.end(), std::back_inserter(vec_back)); //inserting instead of overwriting. NOT efficient.
	//same result but faster - efficient and safe
	vec_back.insert(vec_back.end(), itrmin, vec6.end());

	//Note 4: Algorithm with function
	//bool isOdd(int i) -- outside of main

	std::vector<int> vecbool = { 2,4,5,9,2 };
	std::vector<int>::iterator itrb = std::find_if(vecbool.begin(), vecbool.end(), isOdd); //itr -> 5

	// Note 5: Algorithm with native C++ Array
	int arr[4] = { 6,3,7,4 };
	std::sort(arr, arr + 4);  // iterator cant be thought as a pointer 
	

  std::cout << std::endl;

	system("pause");
	return 0;

}
