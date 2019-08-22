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

