#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

mutex m1,m2,m3;

void test4()
{

    unique_lock<mutex> u1,u2;
    unique_lock<mutex> u3(m3);
    u1=unique_lock<mutex>(m1);
    u2=move(u3);

    //unique_lock移动赋值的两种方式:=和move
    //scoped_lock可以单锁
    return;
}

int main()
{
    
    return 0;
}