#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

mutex m1;                 //定义互斥锁m1

void thread1()
{
    m1.lock();            //手动加锁
    cout<<"will dead locking soon..."<<endl;
    m1.lock();            //再次加锁，占有的同时请求，则产生死锁
    m1.unlock();                           
}

int main()
{
    thread t1(thread1);

    t1.join();
    return 0;
}