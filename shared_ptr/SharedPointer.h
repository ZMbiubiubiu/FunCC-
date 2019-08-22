//
// Created by 李雪菲 on 2019-08-22.
//

#ifndef SHARED_PTR_SHARED_POINTER_H
#define SHARED_PTR_SHARED_POINTER_H

template<class T>
class SharedPointer {
private:
    T   * m_pointer;
    int * m_refCount;
public:
    // 默认构造函数
    SharedPointer() : m_pointer(nullptr), m_refCount(nullptr) {};

    //构造函数，初始化时，指向一个已经分配好的资源
    explicit SharedPointer(T *adoptTarget) : m_pointer(adoptTarget), m_refCount(nullptr) {
        addReference();
    }

    // 构造函数，使用其它指针对象创建新对象
    // 拷贝构造函数
    explicit SharedPointer(const SharedPointer<T> &other) : m_pointer(other.m_pointer), m_refCount(other.m_refCount) {
        addReference();
    }

    // 析构函数，当refCount为0，释放资源
    ~SharedPointer() {
        removeReference();
    }

    // 重载赋值运算符
    // 被当做左值时，表明它不再指向所指的资源，故引用计数减一
    // 之后，它指向了新的资源，所以对应这个资源的引用计数加一
    SharedPointer<T> &operator=(const SharedPointer<T> &that) {
        if (*this == that) addReference();
        else {
            removeReference();
            this->m_pointer = that.m_pointer;
            this->m_refCount = that.m_refCount;
            addReference();
        }
        return *this;
    }

    // 判断是否指向同一个资源
    bool operator==(const SharedPointer<T> &other) const {
        return this->m_pointer == other.m_pointer;
    }

    bool operator!=(const SharedPointer<T> &other) const {
        return this->m_pointer != other.m_pointer;
    }

    // 指针解引用
    T &operator*() const {
        return *m_pointer;
    }

    // 调用所指对象的公共成员
    // "像指针一样使用智能指针"
    T *operator->() const {
        return m_pointer;
    }

    // 获得引用计数的数目
    int GetReferenceCount() const {
        if (m_refCount) {
            return *m_refCount;
        } else {
            return -1;
        }
    }

protected:
    // 增加引用计数，党委nullptr时，初始化1
    void addReference() {
        if (m_refCount) (*m_refCount)++;
        else {
            m_refCount = new int(0);
            *m_refCount = 1;
        }
    };

    // 减少引用计数
    void removeReference() {
        if (m_refCount) {
            (*m_refCount)--;
            if (*m_refCount == 0) {
                delete m_refCount;
                delete m_pointer;
                m_refCount = 0;
                m_pointer = 0;
            }
        }
    };
};


#endif //SHARED_PTR_SHARED_POINTER_H
