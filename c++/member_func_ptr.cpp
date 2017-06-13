/*************************************************************************
  > File Name: member_func_ptr.cpp
  > Author: xgod
  > Mail: xgod@163.com 
  > Created Time: Tue 13 Jun 2017 02:14:22 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;

class A {
	public:
		int f();
		int (A::*x)(); // <- declare by saying what class it is a pointer to
};

int A::f() {
	return 1;
}

/*
 *The syntax is wrong. A member pointer is a different type category from a ordinary pointer. The member pointer will have to be used together with an object of its class:
 a.x does not yet say on what object the function is to be called on. It just says that you want to use the pointer stored in the object a. Prepending a another time as the left operand to the .* operator will tell the compiler on what object to call the function on.
*/

int main(int argc, char* argv[])
{
	A a;
	a.x = &A::f; // use the :: syntax
	printf("%d\n",(a.*(a.x))()); // use together with an object of its class
	return 0;
}
