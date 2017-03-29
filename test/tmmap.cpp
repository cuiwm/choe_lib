/*************************************************************************
    > File Name: tmmap.cpp
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Wed 22 Feb 2017 08:04:05 PM CST
 ************************************************************************/
/*promble: multimap
主要操作：
          1、遍历整个multimap
          2、遍历某个特定的键
          3、查找某个特定的键
          4、删除某个特定的键和特定的值
          
///////////////////*/

#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <stack>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;
/////////////////////////////////////////////////////

multimap<int,int,greater<int> > mump;  //键值从大到小 less<Type> 键值从小到大
typedef multimap<int,int>::iterator Iterator;
int main()
{
    mump.insert(make_pair(1,2));
    mump.insert(make_pair(1,4));
    mump.insert(make_pair(3,4));
    mump.insert(make_pair(1,5));
    mump.insert(make_pair(1,6));
    mump.insert(make_pair(3,4));
    mump.insert(make_pair(3,5));
    mump.insert(make_pair(1,5));
    mump.insert(make_pair(3,4));
    mump.insert(make_pair(4,4));
    mump.insert(make_pair(1,5));
    mump.insert(make_pair(1,5));
    mump.insert(make_pair(5,4));
    mump.insert(make_pair(3,4));

   //遍历整个multimap

    cout << "---------------visit all multimap------------ " << endl;
    Iterator it;
    it = mump.begin();
    for(it = mump.begin();it != mump.end();++it) {
        cout << it->first << "  " << it->second << endl;
    }

     cout << "----------------- End --------------------------- " << endl;
    //单独遍历只有涉及某个key, equal_range(key)

    cout << endl << "-----------------visit only one key multimap--------------- " << endl;
    pair<Iterator,Iterator> it2;
    it2 = mump.equal_range(1);
    /*
       equal_range()返回的是一个pair，该pair的存放的是两个迭代器
       equal_range().first 存放的迭代器指向的是起始位置
       equal_range().second 存放的迭代器指向的是末尾的位置
       有点类似于map中的begin()/end()
    */

    for(it = it2.first;it != it2.second;++it) {
        cout << it->first << "\\|// " << it->second << endl;

    }
    cout << " ------------------- End ----------------- " << endl;

    //删除某个键值，某个值

     cout << " -----------Delete only one key and only one value ------------- " << endl;
     it2 = mump.equal_range(1);
     for(it = it2.first;it != it2.second; ++it) {
        if(it->first == 1 && it->second == 5) {
            cout << "delete: " << it->first << " " << it->second << endl;
            mump.erase(it);
        }
     }

      it = mump.begin();
      for(;it != mump.end();++it) {
        cout << it->first << " " << it->second << endl;
      }
     cout << "-------------------- End --------------------------- " << endl;

    //删除某个键值
    cout << endl << "-------------Delete only one key------------ " << endl;
    it = mump.find(1);
    cout << " delete 3 after " << endl;
    mump.erase(3);
    it = mump.begin();
    for(;it != mump.end();++it) {
        cout << it->first << " " << it->second << endl;
    }
    cout << "-------------End----------------" << endl;
    return 0;
}

