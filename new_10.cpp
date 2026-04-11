#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

class tls_0
{
    public:
        static thread_local int a;
        static thread_local char b;
};
thread_local int tls_0::a=10;
thread_local char tls_0::b='A';

thread_local int s1=20;
thread_local tls_0 s2;
tls_0 s3;
mutex print;

void tls_1()
{
    int x=10;
    s1++;
    s2.a++;
    s3.a++;
    print.lock();
    cout<<"x:"<<x<<" s1:"<<s1<<" s2.a:"<<s2.a<<" s3.a:"<<s3.a<<endl;
    print.unlock();
}

void tls_2()
{
    int x=16;
    s1--;
    s2.a--;
    s3.a--;

    print.lock();
    cout<<"x:"<<x<<" s1:"<<s1<<" s2.a:"<<s2.a<<" s3.a:"<<s3.a<<endl;
    print.unlock();
}

int main()
{
    thread t1(tls_1);
    thread t2(tls_2);

    t1.join();
    t2.join();
    return 0;
}