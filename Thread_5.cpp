#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

mutex m1,m2;

void test1()
{
    lock(m1,m2);
    lock_guard<mutex> g1(m1,adopt_lock);
    lock_guard<mutex> g2(m2,adopt_lock);
}

void test2()
{
    lock(m2,m1);
    lock_guard<mutex> g1(m1,adopt_lock);
    lock_guard<mutex> g2(m2,adopt_lock);
}

int main()
{
    thread t2(test2);
    thread t1(test1);
    
    t1.join();
    t2.join();
    return 0;
}