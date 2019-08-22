`C/C++`Program`  `Computer fundamentals`

使用 C/C++ 实现各种设计.  
[1、洗牌](#1-洗牌)  
[2、智能指针](2-实现C++智能指针)  
[3、LRU缓存](#3-实现LRU缓存)  
[4、判断计算机大小端](#4-编写函数确定计算机的字节序：大端or小端)  
[5](#)  
[6](#)  


### 1 洗牌  

字面意义上的洗牌,练习各自的库.  
[Python版本]():具名元组、random库、python风格的类    
[C版本]():标准库stdlib中的time、srand和rand组合在一起产生(均匀分布)伪随机数  
[C++版本]():新引入的随机数引擎类和随机数分布类  

### 2 实现C++智能指针

所谓智能指针，便是自动回收内存。拥有类似`python`中上下文管理器的作用。智能指针本质上是一个对象，表现的像一个指针。
shared_ptr 智能指针，引用计数机制。当某个对象的引用计数为0时，内存被回收。
```C++
//
// Created by 张猛 on 2019-08-22.
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

```

### 3 实现LRU缓存  
O(1) 时间内实现 `get/put` 操作;  
`get/put` 的节点都需要放到头部；

```C++
LRUCache cache = new LRUCache( 2 /* 缓存容量 */ );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // 返回  1
cache.put(3, 3);    // 该操作会使得密钥 2 作废
cache.get(2);       // 返回 -1 (未找到)
cache.put(4, 4);    // 该操作会使得密钥 1 作废
cache.get(1);       // 返回 -1 (未找到)
cache.get(3);       // 返回  3
cache.get(4);       // 返回  4
```

```python
# 字典+双向链表
# 字典  key:node<key, value>
# 双向链表记录顺序，以及在必要时刻剔除节点，移动节点到最前面
# 为了避免每次替换头结点以及删除最后一个节点的判断临界问题：我们添加两个哨兵节点
#  head  <-> tail
class DLinkedNode(): 
    def __init__(self):
        self.key = 0
        self.value = 0
        self.prev = None
        self.next = None
            
class LRUCache():
    def _add_node(self, node):
        """
        put 新加节点时
        Always add the new node right after head.
        """
        node.prev = self.head
        node.next = self.head.next

        self.head.next.prev = node
        self.head.next = node

    def _remove_node(self, node):
        """
        节点数超过容量时
        Remove an existing node from the linked list.
        """
        prev = node.prev
        next = node.next

        prev.next = next
        next.prev = prev

    def _move_to_head(self, node):
        """
        get访问以及put更新节点时
        Move certain node in between to the head.
        """
        self._remove_node(node)
        self._add_node(node)

    def _pop_tail(self):
        """
        Pop the current tail.
        """
        res = self.tail.prev
        self._remove_node(res)
        return res

    def __init__(self, capacity):
        """
        :type capacity: int
        """
        self.cache = {}
        self.size = 0
        self.capacity = capacity
        self.head, self.tail = DLinkedNode(), DLinkedNode()

        self.head.next = self.tail
        self.tail.prev = self.head
        

    def get(self, key):
        """
        :type key: int
        :rtype: int
        """
        node = self.cache.get(key, None)
        if not node:
            return -1

        # move the accessed node to the head;
        self._move_to_head(node)

        return node.value

    def put(self, key, value):
        """
        :type key: int
        :type value: int
        :rtype: void
        """
        node = self.cache.get(key)

        if not node: 
            newNode = DLinkedNode()
            newNode.key = key
            newNode.value = value

            self.cache[key] = newNode
            self._add_node(newNode)

            self.size += 1

            if self.size > self.capacity:
                # pop the tail
                tail = self._pop_tail()
                del self.cache[tail.key]
                self.size -= 1
        else:
            # update the value.
            node.value = value
            self._move_to_head(node)
```
```C++
//
// Created by 张猛 on 2019-08-22.
//

#ifndef FUNCC_LRUCACHE_H
#define FUNCC_LRUCACHE_H

class LRUCache {
private:
    unordered_map<int, list < pair < int, int>>::iterator> hashtable; // key->双向链表的 !迭代器!（迭代器中存储的为key, value）
    list <pair<int, int>> ls; // 双向链表
    int cap;  // 容量
    int curr;
};

};
public:

LRUCache(int capacity) : hashtable(), ls(), cap(capacity), curr(0) {}

int get(int key) {
    if (hashtable.find(key) == hashtable.end()) return -1;
    auto itr = hashtable[key];  // 能够找到
    if (itr == ls.begin())   // 双向链表的第一个节点便是目标
        return itr->second;  // 找到返回值. itr->first：键值对的key；itr->second：键值对的value
    else {
        ls.push_front(pair<int, int>(itr->first, itr->second));
        auto new_itr = ls.begin();
        hashtable[key] = new_itr;
        ls.erase(itr);
        return ls.front().second;
    }
    return 1;
}

void put(int key, int value) {
    if (hashtable.find(key) != hashtable.end()) {
        ls.erase(hashtable[key]);
        ls.push_front(pair<int, int>(key, value));
        auto new_itr = ls.begin();
        hashtable[key] = new_itr;
        return;
    }
    if (curr == cap) {
        hashtable.erase(ls.back().first);
        ls.pop_back();
        curr--;
    }
    ls.push_front(pair<int, int>(key, value));
    auto new_itr = ls.begin();
    hashtable[key] = new_itr;
    curr++;
}


/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */

#endif //FUNCC_LRUCACHE_H

```

### 4 编写函数确定计算机的字节序：大端or小端  
1111 1111  0000 0000
* 大端：高位字节存储在低位地址 -> 1111 1111 0000 0000
* 小端：高位字节存储在高位字节 -> 0000 0000 1111 1111
```C++
//
// Created by 张猛 on 2019-08-22.
//

#include <iostream>

using namespace std;

// union 下的数据共享同一段内存
union {
    short s;   //short在16位、32位、64位下都是2字节
    char c[2];
} un;

//返回1表示大端，0表示小端，-1表示unknown
int bigEndian() {

    un.s = 0x0102;
    if (un.c[0] == 1 && un.c[1] == 2) return 1;
    else if (un.c[0] == 2 && un.c[1] == 1) return 0;
    else return -1;
}

int main() {
    cout << sizeof(un) << endl;
    int result = bigEndian();
    switch (result) {
        case 1: {
            cout << "大端" << endl;
            break;
        }
        case 0: {
            cout << "小端" << endl;
            break;
        }
        case -1:
            cout << "未知" << endl;
    }
    return 0;
}


```