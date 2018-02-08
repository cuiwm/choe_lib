/*************************************************************************
  > File Name: myRvalue.cpp
  > Author: xgod
  > Mail: xgod@163.com 
  > Created Time: Thu 22 Jun 2017 06:29:17 PM CST
 ************************************************************************/

#include <iostream>
#include <string>

using namespace std;

string print1 ()
{
    char buf[128];
    snprintf(buf, sizeof(buf), "%s %s", "hello world", __func__);

    return buf;
}

string print2()
{
    return std::move(print1());
}


int main(int argc, char* argv[])
{

    printf("%s\n", print2().c_str());
    return 0;
}
