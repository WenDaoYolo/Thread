#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

mutex t1,t2;

int main()
{
    lock_guard<mutex> g1(t1);
    lock_guard<mutex> g2(t1,adopt_lock);
    //锁的生命周期全程由对象接管
    //mutex类的专属模板类

    unique_lock<mutex> u1;
    unique_lock<mutex> u2(t1);
    unique_lock<mutex> u1(t1,adopt_lock);
    unique_lock<mutex> u1(t1,defer_lock);
    //锁的生命周期由对象接管，可以接管或转移
    //mutex类的专属模板类
    u1.try_lock();
    u1.lock();
    u1.unlock();
    u1=move(u2);

    // std::lock();//
    // std::move();//
    //scoped_lock lock(t1,t2);  c++17才有的语法
    //编译器版本低可能不支持,但可以编译时修改

    return 0;

}
