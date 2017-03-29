/*************************************************************************
    > File Name: tmultimap.cpp
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Wed 22 Feb 2017 06:21:31 PM CST
 ************************************************************************/

#include <iostream>
#include <map>
#include <string>
using namespace std;
int main()
{
   multimap <string ,int> m;//multimap的创建
   m.insert(pair<string,int>("Jack",1));//插入
   m.insert(pair<string,int>("Jack",2));
   m.insert(pair<string,int>("Body",1));
   m.insert(pair<string,int>("Navy",4));
   m.insert(pair<string,int>("Demo",3));
 
   multimap<string,int>::iterator iter;
   for (iter = m.begin();iter != m.end();++iter)//遍历
   {
    cout<<(*iter).first<<"  "<<(*iter).second<<endl;
   }

   m.erase("Navy");//multimap的删除
   cout<<"The element after delete:"<<endl;
   for (iter = m.begin();iter != m.end();++iter)
   {
    cout<<(*iter).first<<"  "<<(*iter).second<<endl;
   }

   //multimap元素的查找 
   multimap<string,int>::iterator it;
   //count + find
   int num=m.count("Jack");
   it = m.find("Jack");
   cout<<"the search Jack result is :"<<endl;
   int i;
   for(i=1;i<=num;i++)
   {
      cout<<(*it).first<<"  "<<(*it).second<<endl;
      it++;
   }
   if(i==1){ cout<<"can not find!"<<endl; }
}
