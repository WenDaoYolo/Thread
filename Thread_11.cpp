#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#define MAXSIZE 10
#define TOTAL_DATA 1000
using namespace std;

typedef int ElemType;
mutex mtx,print_lock;
condition_variable cv_producer;
condition_variable cv_consumer;

class queue{
    public:
        ElemType* data;
        int front,rear;

		//构造队列
        queue(){
            this->rear=0;
            this->front=0;
            this->data=new ElemType[MAXSIZE];
        }
		
		//判断队满
        bool IsFull(){
            if((this->rear+1)%MAXSIZE==this->front)
                return true;
            return false;
        }
	
		//判断队空
        bool IsEmpty(){
            if(this->rear==this->front)
                return true;
            return false;
        }

		//安全入队
        void equeue(ElemType e,int id){
            unique_lock<mutex> ul(mtx);
	        cv_producer.wait(ul,[&]{return !this->IsFull();});
	        
            this->data[this->rear]=e;
            this->rear=(this->rear+1)%MAXSIZE;
            cout<<"生产者"<<id<<"生产了数据"<<e<<",缓冲区:";
            this->Display();

            cv_consumer.notify_one();
        }

		//安全出队
        ElemType dequeue(int id){
            unique_lock<mutex> ul(mtx);
            cv_consumer.wait(ul,[&]{return !this->IsEmpty();});
            
            ElemType tmp=this->data[this->front];
            this->front=(this->front+1)%MAXSIZE;
            cout<<"消费者"<<id<<"使用了数据"<<tmp<<",缓冲区:";
            this->Display();

            cv_producer.notify_one();
            return tmp;
        }

		//显示队列元素
        void Display(){
            int find=this->front;
            while(find!=this->rear){
                cout<<this->data[find]<<" ";
                find=(find+1)%MAXSIZE;
            }
            cout<<endl;
        }

		//析构队列
        ~queue(){
            if(this->data!=NULL){
                delete[] this->data;
                this->data=NULL;
            }
        }
};

queue buffer;

void produce1()
{
    int id=1;
    for(int i=1;i<=TOTAL_DATA/2;i++)
    buffer.equeue(i,id);
}

void produce2()
{
    int id=2;
    for(int i=TOTAL_DATA/2+1;i<=TOTAL_DATA;i++)
    buffer.equeue(i,id);
}

void consume1()
{
    int id=1;
    for(int i=1;i<=TOTAL_DATA/2;i++)
    ElemType get=buffer.dequeue(id);
}

void consume2()
{
    int id=2;
    for(int i=TOTAL_DATA/2+1;i<=TOTAL_DATA;i++)
    ElemType get=buffer.dequeue(id);
}

int main()
{
    thread producer1(produce1);
    thread producer2(produce2);
    thread consumer1(consume1);
    thread consumer2(consume2);

    producer1.join();
    producer2.join();
    consumer1.join();
    consumer2.join();
    return 0;
}