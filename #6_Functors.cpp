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
/*
Functors. Functor is a class which defines the operator() that
lets you create objects that ''looks like'' a function.

Benefits:
-Smart Functions: capabilities beyond operator()
It can remember state
-It can have its own type

 //Build in functors
 /*
	less greater greater_equal less_equal  not_equal_to logical_and
	logical_not logical_or multiplies minus plus divide modululs negate
 */														  

 

// 1)Simple example
class X
{
public:
	void operator()(std::string str)
	{
		std::cout << "Calling functor X with parameter " << str << std::endl;
	}
};


// 2)parametrized function
class Y
{
public:
	Y(int i) {}
	void operator() (std::string str)
	{
		std::cout << "Calling functor Y with parameter " << str << std::endl;
	}
};


// 3) Example why it is not good idea to use templates and function for such purpose
void add2(int i)  //not extendable, we are hardcoding a number to a function name. Global variables are not solution.
{
	std::cout << i + 2;
}


// 3a) second option is to use a template
template<int val> //value val resolved at compile time so it has to be compile time constant, aka cannot use eg int x = 2 and addVal<x>;
void addVal(int i)
{
	std::cout << val + i << std::endl;
}


// 3b) Best is to create a functor
class AddValue
{
	int val;
public:
	AddValue(int j) : val(j) {}
	void operator() (int i)
	{
		std::cout << i + val << std::endl;
	}
};

// 3c) Or to improve the addVal function using bind
void addVal2(int z, int val)
{
	std::cout << z + val << std::endl;
}

// 4)you can also convert regular function to a functor
double Pow(double x, double y)
{
	return std::pow(x, y);
}



// 5) why do we need functors in STL
bool lsb_less(int x, int y)
{
	return((x % 10) < (y % 10));
}
//--will not compile if inside set<int,lsb_less>. Set requires function type not just a function 
//--or function pointer.We need to define a functor

class Lsb_less
{
public:
	bool operator() (int x, int y)
	{
		return (x % 10) < (y % 10);
	}
};


// 6) Predicate - A functor or a function that returns a boolean and does not modify data
class NeedCopy
{
public:
	bool operator()(int x)
	{
		return(x > 20) || (x < 5);
	}
};


int main()
{
	X foo; 			//1
	foo("Hi");

	Y(8)("Hey");	//2

	//But why would we not create a function which takes two parameters int and string ?
	//Example:
	int x = 2;
	std::vector<int> vec = { 2,3,4,5 };
	for_each(std::begin(vec), std::end(vec), add2); //for function 3)
	for_each(std::begin(vec), std::end(vec), addVal<2>); // for template 3a)
	for_each(std::begin(vec), std::end(vec), AddValue(x)); // for functor 3b)


	

	int y = std::multiplies<int>()(3, 4); //example of std functor

	if (std::not_equal_to<int>() (y, 12)) //if x != 10;
		std::cout << "does not equal 12" << std::endl;


	// (3c) Using Lambdas for Parameter binding(partial function application)

	std::set<int> myset = { 1,2,3,4,5 };
	std::vector<int> vec2;
	std::vector<int> vec3 = { 1,2,3,4 };

	//Multiply mysets elements by 10 and save it in a vec:
	std::transform(std::begin(myset), std::end(myset),
		std::back_inserter(vec2),
		std::bind(std::multiplies<int>(), std::placeholders::_1, 10));
	//first parameter is multiplies<int>() is substituted with myset's element.
	//vec: {10,20,30,40.50}


	//addVal2 application
	std::for_each(std::begin(vec3), std::end(vec3), std::bind(addVal2, std::placeholders::_1, 44));
	std::for_each(std::begin(vec3), std::end(vec3), [](int &n) {n++; });  //or lambda :)
	for (auto z : vec3)
		std::cout << z << " ";

	std::cout << std::endl;

	//convert regular function POW to a functor
 	std::set<int> myset2= { 5,32,8,2,3,23};
	std::deque<int> deq;
	auto f = std::function<double(double, double)>(Pow);
	transform(std::begin(myset2), std::end(myset2),
		std::back_inserter(deq),
		bind(f, std::placeholders::_1, 2));
	// d: {25, 36, 49, 64, 81}

	
	
	//insert into deque when (x>20) || (x>5). Instead of a function or a function I can use lambdas 
	transform(std::begin(myset2), std::end(myset2),
		std::back_inserter(deq),
		[](int x) {return (x > 20) || (x < 5);}
	);

	//5) why do we need functors in STL
	std::set<int> myset3 = { 3,1,25,7,12 };
	std::set<int,Lsb_less> myset4 = { 1,12,3,25,7};  


	//6) predicate usage -- Predicate is used for comparison or condition check
	transform(std::begin(myset4), std::end(myset4),
		std::back_inserter(deq),
		NeedCopy()
		);




	std::cout << std::endl;

	system("pause");
	return 0;

}
}
