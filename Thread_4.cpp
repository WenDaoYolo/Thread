#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

mutex m1,m2;

void test1()
{
    lock_guard<mutex> g1(m1);
    lock_guard<mutex> g2(m2);
    cout<<"hello test1"<<endl;
}

void test2()
{
    lock_guard<mutex> g1(m1);
    lock_guard<mutex> g2(m2);
    cout<<"hello test2"<<endl;
}

int main()
{
    thread t1(test1),t2(test2);
    t1.join();
    t2.join();

    return 0;
}