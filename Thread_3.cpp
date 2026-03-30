#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

mutex m1;

void test1()
{
    m1.lock();
    cout<<"test1"<<endl;
    return;                   //提前返回导致未解锁
    m1.unlock();                 
}

void test2()
{
    m1.lock();                //m1未解锁，导致t2阻塞
    cout<<"test2"<<endl;
    m1.unlock();
}

int main()
{
    thread t1(test1),t2(test2);

    t1.join();
    t2.join();
    return 0;
}