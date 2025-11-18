#ifndef SINGLETON_H
#define SINGLETON_H
#include "global.h"
template <typename T>
class Singleton{
protected:
    Singleton() = default;//构造函数保护，外部不能实例化
    Singleton(const Singleton<T>&) = delete;//禁止拷贝
    Singleton& operator = (const Singleton<T>& st) =delete;//禁止赋值
    static std::shared_ptr<T> _instance;//禁止单例实例
public:
    static std::shared_ptr<T> GetInstance(){//相当于全局访问点，保证全局只有唯一的httpmgr
        static std::once_flag s_flag;//std::once_flag 是 C++11 提供的线程同步工具   每个模板T有独立的s_flag
        std::call_once(s_flag,[&](){//确保下方函数只会执行一次
            //make_shared()为什么不用  --  make share 不能访问 保护、私有构造函数，所以构造函数在Protect或者private中只能用new
            _instance = std::shared_ptr<T>(new T);
        });
        return _instance;
    }
    // 第一次调用 GetInstance() → call_once 执行 Lambda → 创建对象 → 存入 _instance
    // 后续调用 GetInstance() → call_once 不再执行 → 直接返回 _instance

    void PrintAdress(){
        std::cout << _instance.get() <<std::endl;
    }

    ~Singleton(){
        std::cout << "this is singleton destruct" << std::endl;
    }
};

template <typename T>
std::shared_ptr<T> Singleton<T>:: _instance =nullptr;

#endif // SINGLETON_H
