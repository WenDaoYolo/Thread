#include<iostream>
#include<mutex>
#include<thread>
#include<condition_variable>
using namespace std;

condition_variable cv;
bool ready=false;
mutex m1;

bool check()
{
    //.....
    return ready;
}

void test1()
{
    {
        unique_lock<mutex> u1(m1);
        cv.wait(u1,[]{return ready;});
        cv.wait(u1,check);             //call_back_function
    } 
}

int main()
{
    thread t1(test1);
    ready=true;
    cv.notify_one();

    t1.join();
    return 0;
}