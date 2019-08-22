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
