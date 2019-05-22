#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define True 1
#define False 0
/*
    void srand(unsigned int seed)
    int rand(void)
    上面两个函数组合使用产生伪随机数.
    如果没有第一个随机初始化器.每次程序运行产生的伪随机数会一样.
    我们通常使用当天的时间作为种子
*/

/* 如果没有种子函数,每次的编译结果都一样.
int main()
{
    printf("%d\n",rand());
    printf("%d\n",rand());
    printf("%d\n",rand());
    return 0;
}
*/

void shuffle(int *cards, int n) {
    int i;
    static int first_time = True; // 静态变量保存是否为初始状态
    // 如果尚未初始化,用当天的当前时间作为种子
    if (first_time) {
        first_time = False;
        srand((unsigned int)time(NULL));
    }
    // 通过随机交换,来达到洗牌的效果
    int where1, where2;
    int tmp;
    for (int i=0; i<100; i++) { // 每次洗牌,交换100次
        where1 = rand() % n; // 每副牌有52张
        where2 = rand() % n;
        tmp = cards[where1];
        cards[where1] = cards[where2];
        cards[where2] = tmp;
    }
}

void print(int cards[], int n) {
    for (int i=0; i<n; i++) {
        printf("%d\t", cards[i]);
    }
    printf("\n");
}

int main()
{
    int cards[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    print(cards, 10);
    shuffle(cards, 10);
    print(cards, 10);
    return 0;

}