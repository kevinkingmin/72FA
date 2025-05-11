#ifndef SINGLETON_H
#define SINGLETON_H

#include<QSharedPointer>
#include<QMutexLocker>
#include<QMutex>

template<typename T>
class Singleton{

public:
    typedef QSharedPointer<T> InstancePointer;

public:
    static T *instance();

private:
    Singleton();
    Singleton(const Singleton &);
    ~Singleton();
    Singleton &operator=(const Singleton &);

private:
    static QMutex _mutex;
    static InstancePointer _instance;
};

template<typename T>
QMutex Singleton<T>::_mutex;
template<typename T>
typename Singleton<T>::InstancePointer Singleton<T>::_instance;

template<typename T>
T *Singleton<T>::instance(){
    if(_instance.isNull()){
        QMutexLocker locker(&_mutex);
        if(_instance.isNull()){
            _instance.reset(new T);
        }
    }
    return(_instance.data());
}

#endif //SINGLETON_H