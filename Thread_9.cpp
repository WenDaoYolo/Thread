#include<condition_variable>
#include<iostream>
#include<windows.h>
#include<thread>
#include<mutex>
using namespace std;
condition_variable cv;
condition_variable_any cva;
mutex m1,m2;

void test1()
{
    cout<<"Thread1: I'm sleeping..."<<endl;
    m1.lock();
    cva.wait(m1);
    cout<<"Thread1: Yes sir!"<<endl;
}

int main()
{
    thread t1(test1);
    Sleep(2500);
    cout<<"Thread0: Wake up!"<<endl;
    Sleep(2500);
    cva.notify_one();

    t1.join();
    
    condition_variable c;
    condition_variable_any b;
    condition_variable_any d;
    //c.native_handle();      don't care about more,some compiler doesn't support

    unique_lock<mutex> u1(m1);
    lock_guard<mutex> g1(m2);
    c.wait(u1);
    d.wait(g1);
    
    {
        c.wait(u1,1);
        b.wait(u1,2);
    }

    return 0;
}