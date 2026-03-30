#include<iostream>
#include<mutex>
#include<thread>
using namespace std;

mutex m1,m2;

void thread1()
{
    m1.lock();
    for(int i=0;i<=1000000;i++); //延时，让线程2能拿到m2
    m2.lock();                   //等待m2但是不释放m1
    
    m1.unlock();
    m2.unlock();
}

void thread2()
{
    m2.lock();
    for(int i=0;i<=100000;i++); //延时，让线程1能拿到m1
    m1.lock();                  //等待m1但是不释放m2

    m2.unlock();              
    m1.unlock();
}

int main()
{
    thread t1(thread1),t2(thread2);    

    t1.join();
    t2.join();
    return 0;
}