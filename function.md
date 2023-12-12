# 数字华容道 代码模块展示及相关函数介绍
## CMakeLists
```cmake
cmake_minimum_required(VERSION 3.26)
project(hrd)

set(CMAKE_CXX_STANDARD 17)
include_directories(./easyx/include)
link_directories(./easyx/lib64)
link_libraries(libeasyx.a)

add_executable(hrd0 hrd0.cpp)

target_link_libraries(hrd0 winmm)  
```
*使用Clion编译本程序时cmakelists里必须要加最后一行，不然音乐处理函数将无法正常编译。（应该是Clion编译器与VS编译器的区别）*

## 库的调用
```c
#include<graphics.h>     //图形库
#include<stdio.h>        //标准输入输出库
#include <stdbool.h>     //布尔类型库
#include <conio.h>       //控制台输入输出库
#include <stdlib.h>      //系统函数库
#include<time.h>         //处理时间库
#include <mmsystem.h>    //音乐处理库
#pragma comment(lib,"winmm.lib")//处理接口
```

## 游戏主体：3×3/4×4/5×5棋盘处理函数
```c
//以下是处理4*4棋盘的函数

/**
 * 检测棋盘是否已经拼好
 * @param pan 棋盘的二维数组
 * @return true：已拼好；false：未拼好
 */
bool is_well(int pan[][4]);

/**
 * 检测上下左右操作是否合法
 * @param row 空位即将出现的行
 * @param col 空位即将出现的列
 * @return 返回true为合法，false为不合法
 */
bool if_tran(int row, int col);

/**
 * 将棋盘对应位置换位
 * @param row 空位即将出现的行
 * @param col 空位即将出现的列
 * @param row_n 空位现在所在行
 * @param col_n 空位现在所在列
 * @param pan 棋盘对应的二维数组
 */
void tran_pan(int row, int col, int row_n, int col_n, int pan[][4]);

/**
 * 画出棋盘
 * @param n 数字
 * @param x 行
 * @param y 列
 */
void Paintshu(int n, int x, int y);

/**
 * 显示步数
 * @param n 步数
 */
void Paintcount(int n);

/**
 * 画线
 */
void Paintline();


//以下是处理3*3棋盘的函数.效果基本同上
bool is_well3(int pan[][3]);
bool if_tran3(int row, int col);
void tran_pan3(int row, int col, int row_n, int col_n, int pan[][3]);
void Paintshu3(int n, int x, int y);
void Paintcount3(int n);
void Paintline3();


//以下是处理5*5棋盘的函数.效果基本同上
bool is_well5(int pan[][5]);
bool if_tran5(int row, int col);
void tran_pan5(int row, int col, int row_n, int col_n, int pan[][5]);
void Paintshu5(int n, int x, int y);
void Paintcount5(int n);
void Paintline5();

//4*4 5*5棋盘随机打乱函数

/**
 * 随机打乱4*4棋盘，同时改变当时空格行与当时空格列
 * @param puzzle 4*4棋盘
 * @param empty_row 当前空格行指针
 * @param empty_column 当前空格列指针
 */
void suiji_4(int puzzle[][4], int *empty_row, int *empty_column);

/**
 * 随机打乱5*5棋盘，同时改变当时空格行与当时空格列
 * @param puzzle 5*5棋盘
 * @param empty_row 当前空格行指针
 * @param empty_column 当前空格列指针
 */
void suiji_5(int puzzle[][5], int *empty_row, int *empty_column);
```
*为什么会没有3×3棋盘打乱函数？因为如果打乱了我们后面现场可能就拼不出来了。*

函数具体内容请见源程序。

## 游戏页面展示函数
**为了使各版块更区分清楚，我们的每一个页面都单独编写了一个函数**
```c
//绘制页面函数
void beginning();       //难度选择页面
void record();          //游戏记录页面
void choose3();         //3*3棋盘
void choose4();         //4*4棋盘
void choose5();         //5*5棋盘
void Paintendyes();     //游戏胜利页面
void Paintendno();      //游戏失败页面
void chushi();          //游戏初始页面
```

## 游戏其他处理函数（音乐、画面、按钮等）
```c
//下面是播放背景音乐的函数
void BGM();
void BGM_buttom();
void BGM_win();
void BGM_lose();

//加载图片函数
void photo_zhuye();
void photo_youxi3();
void photo_youxi4();
void photo_youxi5();
void photo_youxi_win();
void photo_youxi_lose();
void photo_youxi_record();

//绘制按钮函数
void photo_zhuye_button();
```
## 游戏记录处理函数
```c
int fileinput()
{
    FILE* p;

    p = fopen("D:\\hrd\\record\\record.txt", "a+");
    fprintf(p, "\n您的游戏成绩记录如下:\n");
    for (int i = 0; i <= 9; i++) {
        if (finalrecord[i].judge == 1) {
            if(finalrecord[i].choice==3)
               fprintf(p, "第%d局：难度3*3 您的步数为%d  用时%d秒  \n", finalrecord[i].n, finalrecord[i].count, finalrecord[i].timeused);
            if (finalrecord[i].choice == 4)
                fprintf(p, "第%d局：难度4*4 您的步数为%d  用时%d秒  \n", finalrecord[i].n, finalrecord[i].count, finalrecord[i].timeused);
            if (finalrecord[i].choice == 5)
                fprintf(p, "第%d局：难度5*5 您的步数为%d  用时%d秒  \n", finalrecord[i].n, finalrecord[i].count, finalrecord[i].timeused);
        
        }
        if (finalrecord[i].judge == 2) {
            if (finalrecord[i].choice == 3)
                fprintf(p, "第%d局：难度3*3 步数为%d （未成功） \n", finalrecord[i].n, finalrecord[i].count);
            if (finalrecord[i].choice == 4)
                fprintf(p, "第%d局：难度4*4 步数为%d （未成功） \n", finalrecord[i].n, finalrecord[i].count);
            if (finalrecord[i].choice == 5)
                fprintf(p, "第%d局：难度5*5 步数为%d （未成功） \n", finalrecord[i].n, finalrecord[i].count);
        }
    }
    fclose(p);

    return 0;
}
```

## 数据结构与按钮构成
```c
//按钮位置确定
#define win_width 600
#define win_length 800

#define but_x 225
#define but_y0 270
#define but_y1 350
#define but_y2 430
#define but_wid 150
#define but_len 60
#define title_x1 175
#define title_y1 20
#define title_x2 425
#define title_y2 190

//存储结构
typedef struct finalrecord_grade {
    int n;
    int choice=0;
    int count;
    int timeused;
    int judge = 0;
}DATA;

DATA finalrecord[10] = { };

//按钮
typedef struct q {
    int x1, y1, width, length;
} BUTTON;
BUTTON begin = { but_x,but_y0,but_wid,but_len };
BUTTON records = { but_x,but_y1,but_wid,but_len };
BUTTON logout = { but_x,but_y2,but_wid,but_len };
BUTTON choose33 = { but_x,but_y0,but_wid,but_len };
BUTTON choose44 = { but_x,but_y1,but_wid,but_len };
BUTTON choose55 = { but_x,but_y2,but_wid,but_len };

RECT b = { but_x,but_y0,but_x + but_wid,but_y0 + but_len };
RECT r = { but_x,but_y1,but_x + but_wid,but_y1 + but_len };
RECT e = { but_x,but_y2,but_x + but_wid,but_y2 + but_len };
RECT t = { title_x1,title_y1,title_x2,title_y2 };
```