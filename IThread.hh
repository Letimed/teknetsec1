#include <pthread.h>

class ScopeLock
{
public:
    ScopeLock(pthread_mutex_t &mutex);
    ~ScopeLock();
private:
    pthread_mutex_t &m_mutex;
};
