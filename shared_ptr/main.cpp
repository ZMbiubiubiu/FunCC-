#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "SharedPointer.h"

using namespace std;

class MyClass {
public:
    ~MyClass() {
        cout << "释放MyClass(" << _id << ")\n";
    }

    MyClass(int i) : _id(i) {

    }

    void Print() const {
        cout << "MyClass(" << _id << ")" << endl;
    }

private:
    int _id;
};

int main() {
    {
        MyClass *px = new MyClass(1);

        SharedPointer<MyClass> ap(px);
        cout << "ap的引用计数(1): "
             << ap.GetReferenceCount() << endl;
        cout << "将ap赋值给bp\n";
        SharedPointer<MyClass> bp = ap;
        cout << "ap的引用计数(2): "
             << ap.GetReferenceCount() << endl;
        SharedPointer<MyClass> cp;


        cout << "将ap赋值给cp\n";


        cp = ap;

        cout << "ap的引用计数(3): "
             << ap.GetReferenceCount() << endl;


        MyClass *qx = new MyClass(5);
        SharedPointer<MyClass> dp(qx);
        ap = dp;

        cout << "ap的引用计数(2): "
             << ap.GetReferenceCount() << endl;

        cout << "dp的引用计数(2): "
             << dp.GetReferenceCount() << endl;

        //"像指针一样使用智能指针"
        dp->Print();
        (*cp).Print();
    }

    cin.get();
}