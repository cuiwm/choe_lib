
#include <pthread.h>
#include <boost/lockfree/queue.hpp>
#include <iostream>
#include <time.h>
#include <sstream>
#include <boost/atomic.hpp>
#include <stdio.h>

using namespace std;

//生产数量
boost::atomic_int producer_count(0);
//消费数量
boost::atomic_int consumer_count(0);
//队列
boost::lockfree::queue<string*> queue(512);


//迭代次数
const int iterations = 10000;

//生产函数
void* producer(void* args)
{
    for (int i = 0; i != iterations; ++i) {
        int value = ++producer_count;
        ostringstream oss;
        oss << value;
        string* pstr = new string(oss.str());
        //原子计数————多线程不存在计数不上的情况       
        //若没有进入队列，则重复推送
        while(!queue.push(pstr));
        //cout<<"queue push:>>>>>>>>>>>> "<<*pstr << " ." <<endl;
        printf(">>>>>queue push:>>>>>>>>>>>>%s\n", pstr->c_str());
    }
    return 0;
}

//是否生产完毕标志
boost::atomic<bool> done (false);

//消费函数
void* consumer(void* args)
{
    string*  mypstr;
    //当没有生产完毕，则边消费边生产
    while (!done) {
        //只要能弹出元素，就消费
        while (queue.pop(mypstr)) {
            if (mypstr) {
                //cout<<"queue pop:"<<*mypstr<<endl;
                printf("pop:%s\n", mypstr->c_str());
                delete mypstr;
            } else {
                printf("pop errrrrrrrrrrrrrrrrrrrrrrr\n");
                //cout<<"queue pop: error"<<endl;
            }
            ++consumer_count;
        }
    }
    //如果生产完毕，则消费
    while (queue.pop(mypstr)){
        ++consumer_count;

            if (mypstr) {
                //cout<<"queue pop:"<<*mypstr<<endl;
                printf("pop:%s\n", mypstr->c_str());
                delete mypstr;
            } else {
                printf("pop errrrrrrrrrrrrrrrrrrrrrrr\n");
                //cout<<"queue pop: error"<<endl;
            }
    }
    return 0;
}

int main(int argc, char* argv[])
{
    cout << "boost::lockfree::queue is ";
    if (!queue.is_lock_free())
        cout << "not ";
    cout << "lockfree" << endl;

    struct timespec time_start={0, 0},time_end={0, 0};
    clock_gettime(CLOCK_REALTIME, &time_start);

    pthread_t producer_tid;
    pthread_t consumer_tid;

    pthread_create(&producer_tid, NULL, producer, NULL);
    pthread_create(&consumer_tid, NULL, consumer, NULL);

    //等待生产者生产完毕
    pthread_join(producer_tid, NULL);
    //可以消费标志
    done = true;     //主线程不等生产线程完毕就设置done标记
    cout << "producer done" << endl;    //输出以观察主线程和各子线程的执行顺序

    //等待消费者结束
    pthread_join(consumer_tid, NULL);
    clock_gettime(CLOCK_REALTIME, &time_end);

    long cost = (time_end.tv_sec-time_start.tv_sec)/1000000 + (time_end.tv_nsec-time_start.tv_nsec)/1000;

    cout<<"===========cost time:"<<cost<<"us==========="<<endl;

    //输出生产和消费数量
    cout << "produced " << producer_count << " objects." << endl;
    cout << "consumed " << consumer_count << " objects." << endl;

    return 0;
}
