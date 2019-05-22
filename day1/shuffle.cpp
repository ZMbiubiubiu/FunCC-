#include <iostream>
#include <random>
#include <ctime>
using namespace std;

// 生成随机数
vector<unsigned> randVec() {
    // 一个给定的随机数发生器一直会产生生成相同的随机数序列.
    // 函数内部定义了局部的随机数发生器.那么每次调用都会生成相同序列.怎么解决?
    // 使用static,是为了函数调用之间保存住状态.
    // 第一次调用会使用u(e)生成的序列中前100个序列
    // 第二次调用会使用u(e)生成的序列中接下来100个序列
    static default_random_engine e;
    static uniform_int_distribution<unsigned> u(0, 9);
    vector<unsigned> ret;
    for (size_t i=0; i<100; i++) { // 生成100个均匀分布在[0,9]范围的随机数
        ret.push_back(u(e));
    }
    return ret;
}
void shuffle(vector<unsigned> cards) {
    // 随机洗100次牌
    static default_random_engine e;
    static uniform_int_distribution<unsigned> u(0,51);
    int where1, where2;
    int tmp;
    for (int i=0; i<100; i++) {
        where1 = u(e);
        where2 = u(e);
        tmp = cards[where1];
        cards[where1] = cards[where2];
        cards[where2] = tmp;
    }
}

void print(vector<unsigned> arr) {
    for (int i=0; i<arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    default_random_engine e;
    // default_random_engine e1(100); // 设置相同的种子,生成的序列会相同.如何验证?
    // default_random_engine e2(100); // 两个序列,用两个引擎,但是种子相同,试试便知.
    uniform_int_distribution<unsigned> u(0, 9);
    vector<unsigned> ret, vet;
    for (size_t i=0; i<20; i++) { // 生成100个均匀分布在[0,9]范围的随机数
        ret.push_back(u(e));
    }

    print(ret);
    for (size_t i=0; i<20; i++) { // 生成100个均匀分布在[0,9]范围的随机数
        vet.push_back(u(e)); 
    }
    print(vet);
    bool flag = ret == vet;
    cout << flag << endl;
    return 0;
}