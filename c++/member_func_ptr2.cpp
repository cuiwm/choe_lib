/*************************************************************************
  > File Name: member_func_ptr2.cpp
  > Author: xgod
  > Mail: xgod@163.com 
  > Created Time: Tue 13 Jun 2017 02:18:54 PM CST
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;



class A 
{
    public: 
        void call();
    private:
        void printH();
        void command(std::string a, std::string b, void (A::*func)());
};

void A::printH()
{
    std::cout<< "H\n";
}

void A::call()
{
    command("a","a", &A::printH);
}

void A::command(std::string a, std::string b, void (A::*func)())
{
    if(a == b)
    {
        //Pay attention to (this->*func)(); and the way to declare the function pointer with class name void (A::*func)()
        (this->*func)();
    }
}

int main(int argc, char* argv[])
{
    A a;
    a.call();
    return 0;
}
