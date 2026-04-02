#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
using namespace std;

mutex m1,m2,m3;                  //原始互斥锁

void test1()
{
    lock(m1,m2,m3);
    m1.lock();
    m1.unlock();
    m1.try_lock();

    lock_guard<mutex> g1(m1);    //RAII守卫锁
    lock_guard<mutex> g2(m1,adopt_lock);

    unique_lock<mutex> u1(m2);   //RAII独占锁
    unique_lock<mutex> u2,u3;
    u2=move(u1);
    u3=unique_lock<mutex>(m3);
    unique_lock<mutex> u4(m1,defer_lock);
    unique_lock<mutex> u5(m2,adopt_lock);
    unique_lock<mutex> u6(m3,try_to_lock);
    u1.try_lock();
    u1.lock();
    u1.unlock();

    //scoped_lock s1(m3);        //RAII作用域锁(C++17新特性)

    condition_variable c1;       //单一条件变量
    condition_variable_any ca1;  //通用条件变量
}

int main()                       //默认主线程(main)
{
    thread t1(test1);            //创建子线程1(test1)
    t1.join();                   //控制子线程1的生命周期
    return 0;
}
