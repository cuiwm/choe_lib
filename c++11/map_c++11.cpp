/*************************************************************************
    > File Name: map_c++11.cpp
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Tue 27 Jun 2017 05:00:53 PM CST
 ************************************************************************/

#include <iostream>
#include <map>

using namespace std;

int main(int argc, char* argv[])
{
  std::map<char,int> mymap;
  std::map<char,int>::iterator it;
  std::map<char,int>::iterator it2;

  // insert some values:
  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;
  mymap['d']=40;
  mymap['e']=50;
  mymap['f']=60;

//  it=mymap.find('b');
//  mymap.erase (it);                   // erasing by iterator
//
//  mymap.erase ('c');                  // erasing by key
//
//  it=mymap.find ('e');
//  //mymap.erase ( it, mymap.end() );    // erasing by range

  // show content:
  for (it=mymap.begin(); it!=mymap.end(); ) {

    if (it->second == 40) {
        std::cout << it->first << " =>delete it++ " << it->second << '\n';
        //it = mymap.erase(it);
         mymap.erase(it++);
    } else {

        std::cout << it->first << " => " << it->second << '\n';
        ++it;
    }
  }

  return 0;
}
