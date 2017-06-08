/*************************************************************************
    > File Name: t001.cpp
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Wed 07 Jun 2017 05:52:09 PM CST
 ************************************************************************/

#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[])
{ 
    istringstream istr; 
    istr.str("1 56.7"); 
    //上述两个过程可以简单写成 istringstream istr("1 56.7"); 
    cout << istr.str()<<endl; 
    int a; 
    float b; 
    istr>>a; 
    cout<<a<<endl; 
    istr>>b; 
    cout<<b<<endl; 
    system("pause"); 
	return 0;
}
