/*************************************************************************
    > File Name: tbind.cpp
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Wed 01 Jun 2016 10:23:14 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;
#include <vector> 
#include <algorithm> 
#include <functional>
class add : public std::binary_function<int, int, void> 
{ 
public: 
  void operator()(int i, int j) const 
  { 
    std::cout << i + j << std::endl; 
  } 
};
int main() 
{ 
  std::vector<int> v; 
  v.push_back(1); 
  v.push_back(3); 
  v.push_back(2);
  std::for_each(v.begin(), v.end(), std::bind1st(add(), 10, _1)); 
}
