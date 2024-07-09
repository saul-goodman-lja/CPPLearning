#ifndef _NONCOPYABLE_HH
#define _NONCOPYABLE_HH

class NonCopyable{
protected: 
    NonCopyable(){}
    ~NonCopyable(){}
    
    NonCopyable(const NonCopyable &) = delete;
    NonCopyable &operator=(const NonCopyable &) = delete;
};

#endif