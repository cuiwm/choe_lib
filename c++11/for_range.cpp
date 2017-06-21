/*************************************************************************
    > File Name: for_range.cpp
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Wed 21 Jun 2017 11:33:33 AM CST
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main(int argc, char* argv[])
{

	string hello = "hello world";

	for (auto ch:hello) {
		cout << ch <<endl;
	}

    int array[] = {1, 2, 3, 4, 5};

    for (auto i :array) {
        cout << i <<endl;
    }

    
    vector<string> vec1 = { "i", "like", "ccc"};
    
    for (auto& it :vec1) {
        it = "ooo";
    }

    for (auto& it :vec1) {
        cout << it <<endl;
    }

    
    map<int, string> map1 = { {1, "one"}, {2, "two"}, {3, "three"}};
    //返回的是pair, 不是迭代器
    for (auto& p: map1) {
        cout << p.first << " " << p.second <<endl;
    }

	return 0;
}

