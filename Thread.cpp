#include "IThread.hh"

ScopeLock::ScopeLock(pthread_mutex_t &mutex):
m_mutex(mutex)
{
    pthread_mutex_lock(&m_mutex);
}
ScopeLock::~ScopeLock()
{
    pthread_mutex_unlock(&m_mutex);
}
