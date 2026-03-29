#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

int g_count=0;
mutex m1;

void test1()
{
    for(int i=0;i<50000;i++)                            
    {                                                  
        lock_guard<mutex> guard1(m1);
        //lock_guard<mutex> new_guard=move(guard1); 无法移动
        //lock_guard<mutex> new_guard(guard1);      无法拷贝构造
        //lock_guard<mutex> new_guard=guard1;       无法等号赋值
        g_count++;
    }
}

void test2()
{
    for(int i=0;i<30000;i++)
    {
        unique_lock<mutex> unique1(m1,defer_lock);  //延迟加锁
        unique1.lock();                             //手动加锁
        unique_lock<mutex> new_unique=move(unique1);//转移绑定关系,此时已加锁,新对象只需负责解锁
        //unique_lock<mutex> new_unique=unique1;      无法拷贝构造
        //unique_lock<mutex> new_unique(unique1);     无法等号赋值
        g_count++;
        new_unique.unlock();
    }
}

void test3()
{
    for(int i=0;i<20000;i++)
    {
        m1.lock();
        g_count++;
        m1.unlock();
    }
}

int main()
{
    thread t1(test1);
    thread t2(test2);
    thread t3(test3);

    t1.join();
    t2.join();
    t3.join();
    cout<<"result:"<<g_count<<endl;
    return 0;
}