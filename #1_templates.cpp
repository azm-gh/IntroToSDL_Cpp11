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

//Introduction to templates

// 1) Function template

//standard function
int square(int x)
{
	return x*x;
}

//or using templates

template<typename T>
T squareTem(T x)
{
	return x*x;
}

// 2) Class template
// see the full explanation in main function

template<typename T>
class BoVector
{
	std::array<T, 1000> arr;
	int size;
public:
	BoVector() :size(0) {}
	void push(T x) { arr[size] = x; size++; }
	
	T get(int i) const { return arr[i];}
	int getSize() const { return size; }
	
	void print() const
	{
		for (int i = 0; i < size; ++i)
			std::cout << arr[i] << " ";
	}
};

template<typename T>
BoVector<T> operator*(const BoVector<T>& rhs1, BoVector<T>& rhs2)
{
	BoVector<T> ret;
	for (int i = 0; i < rhs1.getSize(); i++)
	{
		ret.push(rhs1.get(i)*rhs2.get(i));
	}
	return ret;
}

int main()
{
	// 1) Function template

	std::cout << square(5) << std::endl;
	
	std::cout << squareTem<double>(5.5) << std::endl; //you actually do not have to specify template type
	std::cout << squareTem(5.5) << std::endl; //it will infer the type from the parameter

	//template has a side effect called 'code bloat'. If we use a lot square template functions on a 
	//lot of a datatypes, the code size will be bloated

	// 2) Class template

	BoVector<int> bv;  //will NOT infer the type from the parameter
	bv.push(2);
	bv.push(7);
	bv.print();

	std::cout << std::endl;

	std::cout << "Print squared bv: " << std::endl;
	
	/*Below we are passing template object to a template function squareTem
	First it will invoke square function with datatype BoVector and returns bv*bv.
	And this will invoke the operator multiple for BoVector. Twis will multiply bv item by item and returns
	new BoVector. This is an example of class Template working together with a function template*/

	bv = squareTem(bv); 
	bv.print();

	std::cout << std::endl;

	system("pause");
	return 0;

}
