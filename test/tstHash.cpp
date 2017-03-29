/*************************************************************************
  > File Name: tautomic.c
  > Author: xgod
  > Mail: xgod@163.com 
  > Created Time: Fri 04 Mar 2016 05:24:52 PM CST
 ************************************************************************/

#include<stdio.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <ext/hash_map>
using __gnu_cxx::hash_map;

static int count = 0;
typedef __gnu_cxx::hash_map<unsigned int, unsigned int> HMAP;
HMAP g_map;
pthread_mutex_t g_mutex;

void *test_func(void *arg)
{
    int idx;
    int i=0;
    for(i=0;i<2000;++i){
        
        //printf("%d --before\n", count);
        //printf("%d ret:\n",  __sync_fetch_and_add(&count,1));
        //printf("%d after-- \n", count);
         idx=__sync_add_and_fetch(&count,1) % 39998;
         pthread_mutex_lock(&g_mutex);
         HMAP::const_iterator it = g_map.find(idx);
         if (it != g_map.end())
         {
             printf("find already insert............%d\n", idx);
         }
         std::pair<HMAP::iterator, bool> ret = g_map.insert(std::pair<unsigned int, unsigned int>(idx, idx));
         if (!ret.second)
             printf("insert error %d\n", idx);
         pthread_mutex_unlock(&g_mutex);

    }
    return NULL;
}

int main(int argc, const char *argv[])
{
    pthread_t id[20];
    int i = 0;
    pthread_mutex_init(&g_mutex, NULL);

    for(i=0;i<20;++i){
        pthread_create(&id[i],NULL,test_func,NULL);
    }

    for(i=0;i<20;++i){
        pthread_join(id[i],NULL);
    }
    pthread_mutex_destroy(&g_mutex);
    printf("%d\n",count);
    return 0;
}
