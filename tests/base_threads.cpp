#include <iostream>
#include <pthread.h>
#include <unistd.h>

void *myThread(void *arg)
{
    std::cout << "Thread is running... " << getpid() << "\n";
    sleep(1);
    return nullptr;
}

int main()
{
    pthread_t t1, t2;
    pthread_create(&t1, nullptr, myThread, nullptr);
    pthread_create(&t2, nullptr, myThread, nullptr);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);

    std::cout << "Main thread finished.\n";
    return 0;
}
