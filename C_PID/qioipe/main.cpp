#include"PID.cpp"
using namespace std;
int main(){
    PID pid_pos,pid_add;

    printf("请输入设定值:  ");scanf("%f",&set);
    printf("请输入设定值P  I  D:  ");scanf("%f",&P,&I,&D);

    initialization(&pid_pos);
    initialization(&pid_add);
    
    printf("\n普通位置式  普通增量式\n");
    for(int i=0;i<=200;i++){
        PID_position(&pid_pos);
        PID_add(&pid_add);
        printf("%f    %f\n",pid_pos.err,pid_add.err);
    }
    return 0;
}
/*
    真是一个bug改三天，改了一遍又一遍
    网上的教程翻了很多，真的有些大坑
    比如重复编译，
    #infdef
    #define
    #endif
    的教程看了很多，
    结果发现说的“要在main.cpp里加上include<PID.cpp>”
    根本就不用加（走了一tuo子弯路，寄
    以为防止重复编译能解决“退出代码 -1”；
    结构体指针也是，很多教程写的模里模糊的

    附一些看来挺好的教程
    结构体：https://blog.csdn.net/mataojie/article/details/121671343 
    PID：https://blog.csdn.net/u010312937/article/details/53363831
*/