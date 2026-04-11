#include<condition_variable>
#include<functional>
#include<iostream>
#include<iomanip>
#include<thread>
#include<vector>
#include<chrono>
#include<queue>
#include<mutex>
using namespace std;

mutex print_mtx;
float timer1,timer2;

class ThreadPool
{
	public:
		//停止位标识符，控制线程池的结束
		bool stop;                     
		//符合生产者-消费者模型->任务队列 
		mutex mtx;                     
		size_t ThreadNums;
		//线程池结束且所有任务执行完则结束
		//队列不为空或添加新任务则执行任务             
		condition_variable cv;         
		vector<thread> threads;
		queue<function<void()>> tasks;
		
		ThreadPool(size_t ThreadNums):stop(false),ThreadNums(ThreadNums)
		{
			for(int i=0;i<ThreadNums;i++)
			{
				thread t([this]{
					while(true)
					{
						unique_lock<mutex> lock(this->mtx);
						cv.wait(lock,[this]{return !(this->tasks).empty()||this->stop;});
						if(this->stop&&tasks.empty()) return;
							
						function<void()> task=tasks.front();
						tasks.pop();
						lock.unlock();
                        task();
					}
				});
				threads.push_back(move(t));
			}	
		}
		
		void enqueue(function<void()> task)
		{
			unique_lock<mutex> lock(this->mtx);
			this->tasks.push(task);
			cv.notify_one();
		}
		
		~ThreadPool()
		{
            {
                unique_lock<mutex> lock(mtx);
			    this->stop=true;
            }

            cv.notify_all();

			for(int i=0;i<this->ThreadNums;i++)
				this->threads[i].join();
		}
};

void print(int i)
{
    unique_lock<mutex> lock(print_mtx);
    this_thread::sleep_for(chrono::seconds(1));
	cout<<"thread "<<left<<setw(3)<<this_thread::get_id()
	<<" is execute task "<<left<<setw(3)<<i<<endl;
}

int main()
{
	ThreadPool p1(10);
	for(int i=0;i<20;i++)
		p1.enqueue([i]{print(i);});
		
	return 0;
}