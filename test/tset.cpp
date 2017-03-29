/*************************************************************************
    > File Name: tset.cpp
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Thu 07 Apr 2016 03:24:14 PM CST
 ************************************************************************/
#include <string.h>
#include <iostream>
#include <set>
#include <iterator>
#include <vector>
#include <algorithm> //集合运算：并、交、差需要包含该头文件

using namespace std;

struct ltstr

{

    bool operator()(const char* s1,const char* s2) const

    {

       return strcmp(s1,s2)<0; //由小到大排序

//return strcmp(s1,s2)<0; //由大到小排序

    }

};

struct lt

{

    bool operator()(const string& s1,const string& s2) const

    {

       return strcmp(s1.c_str(),s2.c_str())<0; //由小到大排序

//return strcmp(s1,s2)<0; //由大到小排序

    }

};

int main (int argc, char* argv[])
{

    const int N = 6;

    const char* a[N] = {"isomer","ephemeral","prosaic","nugatory","artichoke","serif"};

    const char* b[N] = {"flat","this","artichoke","frigate","prosaic","isomer"};

    vector<string> va, vb, vc;
    va.reserve(N);
    vb.reserve(N);
//    vc.reserve(N);
    vc.resize(N);

    for (int i = 0; i < N; i++)
    {
       va.push_back(a[i]);
       vb.push_back(b[i]);
    }

    //sort(va.begin(), va.end(), less<const char*>() );
    //sort(va.begin(), va.end(), less<const char*>() );

    //sort(va.begin(), va.end(), ltstr() );
    //sort(vb.begin(), vb.end(), ltstr() );

    sort(va.begin(), va.end() );
    sort(vb.begin(), vb.end() );
    cout << "va:";
    copy(va.begin(), va.end(), ostream_iterator<string>(cout, " "));
    cout << endl;
    

    cout << "vb:";
    copy(vb.begin(), vb.end(), ostream_iterator<string>(cout, " "));
    cout << endl;

    

   vector<string>::iterator it =  std::set_intersection(va.begin(), va.end(), vb.begin(), vb.end(), vc.begin());

   vc.resize(it -vc.begin());

    cout << "vc:intersect ";
    copy(vc.begin(), vc.end(), ostream_iterator<string>(cout, " "));
    cout << endl;


    cout << endl;
    cout << endl;



    set<const char*,ltstr>A(a,a+N);
    set<const char*, ltstr > set1(a, a+N);

    set<const char*,ltstr> B(b,b+N);

    set<const char*,ltstr>C;

    set<const char*,ltstr>D;

    cout << "set1:";
    copy(set1.begin(), set1.end(), ostream_iterator<const char*>(cout, " "));
    cout <<endl;

    cout<<"Set A:";

    copy(A.begin(),A.end(),ostream_iterator<const char*>(cout," "));

    cout<<endl;

    cout<<"Set B:";

    copy(B.begin(),B.end(),ostream_iterator<const char*>(cout," "));

    cout<<endl;

    cout<<"Union: ";

    //set_union函数需要#include <algorithm>

    set_union(A.begin(),A.end(),B.begin(),B.end(),ostream_iterator<const char*>(cout," "),ltstr());

    cout<<endl;

    cout<<"Intersection: ";

    set_intersection(A.begin(),A.end(),B.begin(),B.end(),ostream_iterator<const char*>(cout," "),ltstr());

    cout<<endl;

    cout<<"Set C (difference of A and B):";

    set_difference(A.begin(),A.end(),B.begin(),B.end(),inserter(C,C.begin()),ltstr());//从A中减去B包含的元素

    copy(C.begin(),C.end(),ostream_iterator<const char*>(cout," "));

    cout<<endl;

    cout<<"Set D (difference of B and A):";

    set_difference(B.begin(),B.end(),A.begin(),A.end(),inserter(D,D.begin()),ltstr());//从B中减去A包含的元素

    copy(D.begin(),D.end(),ostream_iterator<const char*>(cout," "));

    cout<<endl;

    return 0;

}
