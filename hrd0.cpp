//
// Created by huawei on 2023/11/22.
//

#define _CRT_SECURE_NO_WARNINGS 1
#include<graphics.h>
#include<stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <stdlib.h>
#include<time.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")//处理接口

//下面是播放背景音乐的函数
void BGM()
{
    mciSendStringW(L"open D:\\\\hrd\\\\music\\\\a.wav alias mymusic", 0, 0, 0);
    mciSendStringW(L"play mymusic", 0, 0, 0);
    mciSendStringW(L"play mymusic repeat", 0, 0, 0); // 使用 'repeat' 参数来循环播放
    mciSendStringW(L"seek mymusic1 to start", 0, 0, 0);
}

void BGM_buttom()
{
    mciSendStringW(L"stop mymusic1", 0, 0, 0); // 停止上一次的播放
    mciSendStringW(L"close mymusic1", 0, 0, 0); // 关闭上一次的文件

    mciSendStringW(L"open D:\\\\hrd\\\\music\\\\buttom.wav alias mymusic1", 0, 0, 0);
    mciSendStringW(L"play mymusic1", 0, 0, 0);
}

void BGM_win()
{
    mciSendStringW(L"stop mymusic2", 0, 0, 0); // 停止上一次的播放
    mciSendStringW(L"close mymusic2", 0, 0, 0); // 关闭上一次的文件

    mciSendStringW(L"open D:\\\\hrd\\\\music\\\\win.wav alias mymusic2", 0, 0, 0);
    mciSendStringW(L"play mymusic2", 0, 0, 0);
}

void BGM_lose()
{
    mciSendStringW(L"stop mymusic3", 0, 0, 0); // 停止上一次的播放
    mciSendStringW(L"close mymusic3", 0, 0, 0); // 关闭上一次的文件

    mciSendStringW(L"open D:\\\\hrd\\\\music\\\\lose.wav alias mymusic3", 0, 0, 0);
    mciSendStringW(L"play mymusic3", 0, 0, 0);
}

//加载图片函数
void photo_zhuye()
{
    IMAGE mage;
    loadimage(&mage, "back.jpg");
    putimage(0, 0, &mage);
}

void photo_youxi()
{
    IMAGE mage;
    loadimage(&mage, "back2.jpg");
    putimage(0, 0, &mage);
}

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

int num = 0;

//数据结构
typedef struct finalrecord_grade {
    int n;
    int choice=0;
    int count;
    int timeused;
    int judge = 0;
}DATA;

DATA finalrecord[10] = { };

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

//绘制页面函数
void beginning();
void record();
void choose3();
void choose4();
void choose5();
void Paintendyes();
void Paintendno();
void chushi();

void drawbutton(BUTTON btn);  //绘制按钮函数

int fileinput();  //游戏记录处理函数

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
void tran_pan3(int row, int col, int row_n, int col_n, int pan[][5]);
void Paintshu5(int n, int x, int y);
void Paintcount5(int n);
void Paintline5();



int main() {
    initgraph(win_width, win_length);
    setbkcolor(WHITE);

    chushi();
    _getch();
    return 0;

}

void drawbutton(BUTTON btn) {
    setlinecolor(BLACK);
    rectangle(btn.x1, btn.y1, btn.x1 + btn.width, btn.y1 + btn.length);// 如果直接不贴图
}

void beginning() {                                                                        //绘制游戏界面
    cleardevice();
    photo_zhuye();
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    drawbutton(choose33);
    drawbutton(choose44);
    drawbutton(choose55);
    settextstyle(30, 0, "华文中宋");
    outtextxy(130, 720, "返回主页面");
    settextstyle(58, 0, "华文中宋");
    drawtext("3*3", &b, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawtext("4*4", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawtext("5*5", &e, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    int a = 0;
    while (true) {
        if (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            switch (msg.uMsg) {
            case WM_LBUTTONDOWN:
                if ((msg.x >= choose33.x1) && (msg.x <= choose33.x1 + choose33.width) && (msg.y >= choose33.y1) && (msg.y <= choose33.y1 + choose33.length))
                    a = 1;
                else if ((msg.x >= choose44.x1) && (msg.x <= choose44.x1 + choose44.width) && (msg.y >= choose44.y1) && (msg.y <= choose44.y1 + choose44.length))
                    a = 2;
                else if ((msg.x >= choose55.x1) && (msg.x <= choose55.x1 + choose55.width) && (msg.y >= choose55.y1) && (msg.y <= choose55.y1 + choose55.length))
                    a = 3;
                else if  (msg.x >= 120 && msg.x <= 260 && msg.y <= 750 && msg.y >= 700)
                    a = 4;
                break;
            }
        }
        if (a)
            break;
    }
    switch (a) {
    case 1:choose3(); break;
    case 2:choose4(); break;
    case 3:choose5(); break;
    case 4:chushi(); break;
    }
    _getch();
    closegraph();
}
void record() {
    char a[10][100] = { };                                  //绘制历史记录的界面
    int i;
    setbkcolor(WHITE);
    cleardevice();
    photo_zhuye();
    while (1)
    {
        MOUSEMSG m;
        int b = 0;
        if (MouseHit())
        {
            m = GetMouseMsg();

            switch (m.uMsg)
            {

            case WM_LBUTTONDOWN:

                //printf("%d,%d ", m.x, m.y);
                if (m.x >= 120 && m.x <= 260 && m.y <= 750 && m.y >= 700)b = 1;

                break;
            }
        }

        switch (b)
        {
        case 1:chushi(); break;
        }

        settextcolor(BLACK);
        settextstyle(30, 0, "华文中宋");
        outtextxy(120, 100, "您的游戏记录如下：");
        outtextxy(130, 720, "返回主页面");
        for (i = 0; i <= 9; i++) {
            if (finalrecord[i].judge == 1)
            {
                if (finalrecord[i].choice == 3) {
                    settextstyle(30, 0, "行楷");
                    sprintf_s(a[i], "第%d局 3*3 %d步 用时%d秒", finalrecord[i].n, finalrecord[i].count, finalrecord[i].timeused);
                    outtextxy(100, i * 50 + 150, a[i]);
                    settextstyle(30, 0, "行楷");
                    outtextxy(100, i * 50 + 150, a[i]);
                    setlinecolor(BLUE);
                    rectangle(90, i * 50 + 140, 510, i * 50 + 190);
                }
                if (finalrecord[i].choice == 4) {
                    settextstyle(30, 0, "行楷");
                    sprintf_s(a[i], "第%d局 4*4 %d步 用时%d秒", finalrecord[i].n, finalrecord[i].count, finalrecord[i].timeused);
                    outtextxy(100, i * 50 + 150, a[i]);
                    settextstyle(30, 0, "行楷");
                    outtextxy(100, i * 50 + 150, a[i]);
                    setlinecolor(BLUE);
                    rectangle(90, i * 50 + 140, 510, i * 50 + 190);
                }
                if (finalrecord[i].choice == 5) {
                    settextstyle(30, 0, "行楷");
                    sprintf_s(a[i], "第%d局 5*5 %d步 用时%d秒", finalrecord[i].n, finalrecord[i].count, finalrecord[i].timeused);
                    outtextxy(100, i * 50 + 150, a[i]);
                    settextstyle(30, 0, "行楷");
                    outtextxy(100, i * 50 + 150, a[i]);
                    setlinecolor(BLUE);
                    rectangle(90, i * 50 + 140, 510, i * 50 + 190);
                }
            }
            if (finalrecord[i].judge == 2) {
                if (finalrecord[i].choice == 3) {
                    settextstyle(30, 0, "行楷");
                    sprintf_s(a[i], "第%d局 3*3 %d步 (未完成)", finalrecord[i].n, finalrecord[i].count);
                    outtextxy(100, i * 50 + 150, a[i]);
                    settextstyle(30, 0, "行楷");
                    outtextxy(100, i * 50 + 150, a[i]);
                    setlinecolor(BLUE);
                    rectangle(90, i * 50 + 140, 510, i * 50 + 190);
                }
                if (finalrecord[i].choice == 4) {
                        settextstyle(30, 0, "行楷");
                        sprintf_s(a[i], "第%d局 4*4 %d步 (未完成)", finalrecord[i].n, finalrecord[i].count);
                        outtextxy(100, i * 50 + 150, a[i]);
                        settextstyle(30, 0, "行楷");
                        outtextxy(100, i * 50 + 150, a[i]);
                        setlinecolor(BLUE);
                        rectangle(90, i * 50 + 140, 510, i * 50 + 190);
                    }
                if (finalrecord[i].choice == 5) {
                            settextstyle(30, 0, "行楷");
                            sprintf_s(a[i], "第%d局 5*5 %d步 (未完成)", finalrecord[i].n, finalrecord[i].count);
                            outtextxy(100, i * 50 + 150, a[i]);
                            settextstyle(30, 0, "行楷");
                            outtextxy(100, i * 50 + 150, a[i]);
                            setlinecolor(BLUE);
                            rectangle(90, i * 50 + 140, 510, i * 50 + 190);
                        }
            }


        }
    }

    _getch();




}

bool is_well(int pan[][4]) {
    for (int i = 0; i < 4; ++i) {
        if (pan[0][i] != i + 1) {
            return false;
        }
    }
    for (int i = 0; i < 4; ++i) {
        if (pan[1][i] != i + 5) {
            return false;
        }
    }
    for (int i = 0; i < 4; ++i) {
        if (pan[2][i] != i + 9) {
            return false;
        }
    }
    for (int i = 0; i < 3; ++i) {
        if (pan[3][i] != i + 13) {
            return false;
        }
    }
    return true;
}



bool if_tran(int row, int col) {
    if (row > 3 || col > 3 || row < 0 || col < 0) {
        return false;
    }

    return true;
}

void tran_pan(int row, int col, int row_n, int col_n, int pan[][4]) {
    pan[row_n][col_n] = pan[row][col];
    pan[row][col] = 0;
}
void Paintshu(int n, int x, int y)
{
    settextcolor(BLACK);
    settextstyle(90, 0, "华文中宋");
    setbkmode(TRANSPARENT);
    setcolor(BLUE);
    setbkmode(TRANSPARENT);
    //设置字体格式
    if (n >= 1 && n <= 9)
    {
        char a = n + '0';
        outtextxy(125 + x * 100, 210 + y * 100, a);
    }
    if (n == 10)
    {
        outtextxy(105 + x * 100, 210 + y * 100, "10");
    }
    else if (n == 11)
    {
        outtextxy(105 + x * 100, 210 + y * 100, "11");
    }
    else if (n == 12)
    {
        outtextxy(105 + x * 100, 210 + y * 100, "12");
    }
    else if (n == 13)
    {
        outtextxy(105 + x * 100, 210 + y * 100, "13");
    }
    else if (n == 14)
    {
        outtextxy(105 + x * 100, 210 + y * 100, "14");
    }
    else if (n == 15)
    {
        outtextxy(105 + x * 100, 210 + y * 100, "15");
    }
}

void Paintcount(int n)
{
    settextcolor(BLACK);
    settextstyle(50, 0, "华文中宋");
    setbkmode(TRANSPARENT);
    setcolor(RED);
    //设置字体格式
    char a[100000] = { 0 };
    _itoa(n, a, 10);
    outtextxy(220, 700, "步数:");
    outtextxy(350, 700, a);
}

void Paintline() {
    settextcolor(BLACK);
    settextstyle(100, 0, "华文中宋");
    setcolor(BLUE);
    setbkmode(TRANSPARENT);
    setlinecolor(BLACK);
    char arr[] = "4*4";
    int width = textwidth(arr);
    outtextxy(300 - width / 2, 50, "4*4");
    line(100, 200, 500, 200);
    line(100, 300, 500, 300);
    line(100, 400, 500, 400);
    line(100, 500, 500, 500);
    line(100, 600, 500, 600);
    line(100, 200, 100, 600);
    line(200, 200, 200, 600);
    line(300, 200, 300, 600);
    line(400, 200, 400, 600);
    line(500, 200, 500, 600);
}


bool is_well3(int pan[][3]) {
    for (int i = 0; i < 3; ++i) {
        if (pan[0][i] != i + 1) {
            return false;
        }
    }
    for (int i = 0; i < 3; ++i) {
        if (pan[1][i] != i + 4) {
            return false;
        }
    }
    for (int i = 0; i < 2; ++i) {
        if (pan[2][i] != i + 7) {
            return false;
        }
    }
    return true;
}

bool if_tran3(int row, int col) {
    if (row > 2 || col > 2 || row < 0 || col < 0) {
        return false;
    }

    return true;
}

void tran_pan3(int row, int col, int row_n, int col_n, int pan[][3]) {
    pan[row_n][col_n] = pan[row][col];
    pan[row][col] = 0;
}

void Paintshu3(int n, int x, int y)
{
    settextcolor(BLACK);
    settextstyle(90, 0, "华文中宋");
    setcolor(BLUE);
    setbkmode(TRANSPARENT);
    //设置字体格式
    if (n >= 1 && n <= 8)
    {
        char a = n + '0';
        outtextxy(130 + x * 133, 210 + y * 133, a);
    }
}

void Paintcount3(int n)
{
    settextcolor(BLACK);
    settextstyle(50, 0, "华文中宋");
    setcolor(RED);
    setbkmode(TRANSPARENT);
    //设置字体格式
    char a[100000] = { 0 };
    _itoa(n, a, 10);
    outtextxy(220, 700, "步数:");
    outtextxy(350, 700, a);
}

void Paintline3() {
    settextcolor(BLACK);
    settextstyle(100, 0, "华文中宋");
    setcolor(BLUE);
    setbkmode(TRANSPARENT);
    setlinecolor(BLACK);
    char arr[] = "3*3";
    int width = textwidth(arr);
    outtextxy(300 - width / 2, 50, "3*3");
    line(100, 200, 500, 200);
    line(100, 333, 500, 333);
    line(100, 467, 500, 467);
    line(100, 600, 500, 600);
    line(100, 200, 100, 600);
    line(233, 200, 233, 600);
    line(367, 200, 367, 600);
    line(500, 200, 500, 600);
}

void choose3() //3*3棋盘
{
    int hua3[3][3] = { {1,2,3},
                      {4,8,5},
                      {7,6,0} };
    int row_n = 2;
    int col_n = 2;
    int count = 0;
    int time1, time2, timeused;
    setbkcolor(WHITE);
    cleardevice();

    time1 = time(NULL);
    while (!is_well3(hua3)) //当棋盘还未拼好
    {

        cleardevice();
        BeginBatchDraw(); //开始批量绘图
        photo_youxi();
        Paintline3();

        Paintcount3(count); //显示步数

        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                Paintshu3(hua3[i][j], j, i);
            }
        }
        //显示棋盘

        EndBatchDraw(); // 结束批量绘图

        int row = row_n, col = col_n;
        //目标移动点

        bool if_tra = true;  // 位置是否合法，初始为true

        //检测键盘操作
        if (_kbhit())
        {
            char key = _getch();
            printf("%d %c\n", key, key);
            switch (key)
            {
            case 72:
                row++;
                if_tra = if_tran3(row, col); //检测合法
                if (if_tra)
                {
                    tran_pan3(row, col, row_n, col_n, hua3); //移动位置
                    count++; //步数加一
                    row_n = row;
                    col_n = col;
                    BGM_buttom();
                    //更新坐标
                }
                else
                {
                    row = row_n;
                    col = col_n;
                    //还回到原来状态
                }
                break;
            case 80:
                row--;
                if_tra = if_tran3(row, col); //检测合法
                if (if_tra)
                {
                    tran_pan3(row, col, row_n, col_n, hua3); //移动位置
                    count++; //步数加一
                    row_n = row;
                    col_n = col;
                    BGM_buttom();
                    //更新坐标
                }
                else
                {
                    row = row_n;
                    col = col_n;
                    //还回到原来状态
                }
                break;
            case 75:
                col++;
                if_tra = if_tran3(row, col); //检测合法
                if (if_tra)
                {
                    tran_pan3(row, col, row_n, col_n, hua3); //移动位置
                    count++; //步数加一
                    row_n = row;
                    col_n = col;
                    BGM_buttom();
                    //更新坐标
                }
                else
                {
                    row = row_n;
                    col = col_n;
                    //还回到原来状态
                }
                break;
            case 77:
                col--;
                if_tra = if_tran3(row, col); //检测合法
                if (if_tra)
                {
                    tran_pan3(row, col, row_n, col_n, hua3); //移动位置
                    count++; //步数加一
                    row_n = row;
                    col_n = col;
                    BGM_buttom();
                    //更新坐标
                }
                else
                {
                    row = row_n;
                    col = col_n;
                    //还回到原来状态
                }
                break;
            case 27:
                finalrecord[num].n = num + 1;
                finalrecord[num].count = count;
                finalrecord[num ].choice = 3;
                finalrecord[num].judge = 2;
                Paintendno();
                chushi();
                break;
            }
        }

    }
    time2 = time(NULL);
    timeused = time2 - time1;
    finalrecord[num].n = num + 1;
    finalrecord[num].count = count;
    finalrecord[num].choice = 3;
    finalrecord[num].judge = 1;
    finalrecord[num].timeused = timeused;
    Paintendyes();
    getchar();
    closegraph();
}

void choose4() //4*4棋盘
{
    int huarongdao[4][4] = { {5,7,3,2},
                            {9,1,8,12},
                            {15,6,13,14},
                            {10,4,11,0} };
    //对棋盘进行初始化

    int row_n = 3;
    int col_n = 3;
    //对目前空位所在位置初始化

    int count = 0; //统计移动步数
    int time1, time2, timeused;
    setbkcolor(WHITE);
    cleardevice();

    //初始化页面，背景设置为白色
    time1 = time(NULL);
    while (!is_well(huarongdao)) //当棋盘还未拼好
    {

        cleardevice();
        BeginBatchDraw(); //开始批量绘图
        photo_youxi();
        Paintline();
        Paintcount(count); //显示步数

        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                Paintshu(huarongdao[i][j], j, i);
            }
        }
        //显示棋盘

        EndBatchDraw(); // 结束批量绘图

        int row = row_n, col = col_n;
        //目标移动点

        bool if_tra = true;  // 位置是否合法，初始为true

        //检测键盘操作
        if (_kbhit())
        {
            char key = _getch();
            printf("%d %c\n", key, key);
            switch (key)
            {
            case 72:
                row++;
                if_tra = if_tran(row, col); //检测合法
                if (if_tra)
                {
                    tran_pan(row, col, row_n, col_n, huarongdao); //移动位置
                    count++; //步数加一
                    row_n = row;
                    col_n = col;
                    BGM_buttom();
                    //更新坐标
                }
                else
                {
                    row = row_n;
                    col = col_n;
                    //还回到原来状态
                }
                break;
            case 80:
                row--;
                if_tra = if_tran(row, col); //检测合法
                if (if_tra)
                {
                    tran_pan(row, col, row_n, col_n, huarongdao); //移动位置
                    count++; //步数加一
                    row_n = row;
                    col_n = col;
                    BGM_buttom();
                    //更新坐标
                }
                else
                {
                    row = row_n;
                    col = col_n;
                    //还回到原来状态
                }
                break;
            case 75:
                col++;
                if_tra = if_tran(row, col); //检测合法
                if (if_tra)
                {
                    tran_pan(row, col, row_n, col_n, huarongdao); //移动位置
                    count++; //步数加一
                    row_n = row;
                    col_n = col;
                    BGM_buttom();
                    //更新坐标
                }
                else
                {
                    row = row_n;
                    col = col_n;
                    //还回到原来状态
                }
                break;
            case 77:
                col--;
                if_tra = if_tran(row, col); //检测合法
                if (if_tra)
                {
                    tran_pan(row, col, row_n, col_n, huarongdao); //移动位置
                    count++; //步数加一
                    row_n = row;
                    col_n = col;
                    BGM_buttom();
                    //更新坐标
                }
                else
                {
                    row = row_n;
                    col = col_n;
                    //还回到原来状态
                }
                break;
            case 27:
                finalrecord[num].n = num + 1;
                finalrecord[num].count = count;
                finalrecord[num].choice = 4;
                finalrecord[num].judge = 2;

                Paintendno();

                chushi();
                break;
            }
        }

    }
    time2 = time(NULL);
    timeused = time2 - time1;
    finalrecord[num].n = num + 1;
    finalrecord[num].count = count;
    finalrecord[num].choice = 4;
    finalrecord[num].judge = 1;
    finalrecord[num].timeused = timeused;
    Paintendyes();
    getchar();
    closegraph();
}

bool is_well5(int pan[][5]) {
    for (int i = 0; i < 5; ++i) {
        if (pan[0][i] != i + 1) {
            return false;
        }
    }
    for (int i = 0; i < 5; ++i) {
        if (pan[1][i] != i + 6) {
            return false;
        }
    }
    for (int i = 0; i < 5; ++i) {
        if (pan[2][i] != i + 11) {
            return false;
        }
    }
    for (int i = 0; i < 5; ++i) {
        if (pan[3][i] != i + 16) {
            return false;
        }
    }
    for (int i = 0; i < 4; ++i) {
        if (pan[4][i] != i + 21) {
            return false;
        }
    }
    return true;
}

bool if_tran5(int row, int col) {
    if (row > 4 || col > 4 || row < 0 || col < 0) {
        return false;
    }

    return true;
}

void tran_pan5(int row, int col, int row_n, int col_n, int pan[][5]) {
    pan[row_n][col_n] = pan[row][col];
    pan[row][col] = 0;
}

void Paintshu5(int n, int x, int y)
{
    settextcolor(BLACK);
    settextstyle(72, 0, "华文中宋");
    setcolor(BLUE);
    setbkmode(TRANSPARENT);
    //设置字体格式
    if (n >= 1 && n <= 9)
    {
        char a = n + '0';
        outtextxy(120 + x * 80, 205 + y * 80, a);
    }
    if (n == 10)
    {
        outtextxy(105 + x * 80, 205 + y * 80, "10");
    }
    else if (n == 11)
    {
        outtextxy(105 + x * 80, 205 + y * 80, "11");
    }
    else if (n == 12)
    {
        outtextxy(105 + x * 80, 205 + y * 80, "12");
    }
    else if (n == 13)
    {
        outtextxy(105 + x * 80, 205 + y * 80, "13");
    }
    else if (n == 14)
    {
        outtextxy(105 + x * 80, 205 + y * 80, "14");
    }
    else if (n == 15)
    {
        outtextxy(105 + x * 80, 205 + y * 80, "15");
    }
    else if (n == 16)
    {
        outtextxy(105 + x * 80, 205 + y * 80, "16");
    }
    else if (n == 17)
    {
        outtextxy(105 + x * 80, 205 + y * 80, "17");
    }
    else if (n == 18)
    {
        outtextxy(105 + x * 80, 205 + y * 80, "18");
    }
    else if (n == 19)
    {
        outtextxy(105 + x * 80, 205 + y * 80, "19");
    }
    else if (n == 20)
    {
        outtextxy(105 + x * 80, 205 + y * 80, "20");
    }
    else if (n == 21)
    {
        outtextxy(105 + x * 80, 205 + y * 80, "21");
    }
    else if (n == 22)
    {
        outtextxy(105 + x * 80, 205 + y * 80, "22");
    }
    else if (n == 23)
    {
        outtextxy(105 + x * 80, 205 + y * 80, "23");
    }
    else if (n == 24)
    {
        outtextxy(105 + x * 80, 205 + y * 80, "24");
    }
}


void Paintcount5(int n)
{
    settextcolor(BLACK);
    settextstyle(50, 0, "华文中宋");
    setcolor(RED);
    setbkmode(TRANSPARENT);
    //设置字体格式
    char a[100000] = { 0 };
    _itoa(n, a, 10);
    outtextxy(220, 700, "步数:");
    outtextxy(350, 700, a);
}

void Paintline5() {
    settextcolor(BLACK);
    settextstyle(100, 0, "华文中宋");
    setcolor(BLUE);
    setbkmode(TRANSPARENT);
    setlinecolor(BLACK);
    char arr[] = "5*5";
    int width = textwidth(arr);
    outtextxy(300 - width / 2, 50, "5*5");
    line(100, 200, 500, 200);
    line(100, 280, 500, 280);
    line(100, 360, 500, 360);
    line(100, 440, 500, 440);
    line(100, 520, 500, 520);
    line(100, 600, 500, 600);
    line(100, 200, 100, 600);
    line(180, 200, 180, 600);
    line(260, 200, 260, 600);
    line(340, 200, 340, 600);
    line(420, 200, 420, 600);
    line(500, 200, 500, 600);
}

void choose5()
{
    int huarongdao[5][5] = { {5,7,3,2,16},
                            {9,1,8,12,17},
                            {15,6,13,14,18},
                            {19,10,20,22,11},
                            {23,4,21,24,0} };
    //对棋盘进行初始化

    int row_n = 4;
    int col_n = 4;
    //对目前空位所在位置初始化

    int count = 0; //统计移动步数
    int time1, time2, timeused;
    setbkcolor(WHITE);
    cleardevice();

    //初始化页面，背景设置为白色
    time1 = time(NULL);
    while (!is_well5(huarongdao)) //当棋盘还未拼好
    {

        cleardevice();
        BeginBatchDraw(); //开始批量绘图
        photo_youxi();
        Paintline5();

        Paintcount5(count); //显示步数

        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 5; ++j)
            {
                Paintshu5(huarongdao[i][j], j, i);
            }
        }
        //显示棋盘

        EndBatchDraw(); // 结束批量绘图

        int row = row_n, col = col_n;
        //目标移动点

        bool if_tra = true;  // 位置是否合法，初始为true

        //检测键盘操作
        if (_kbhit())
        {
            char key = _getch();
            printf("%d %c\n", key, key);
            switch (key)
            {
            case 72:
                row++;
                if_tra = if_tran5(row, col); //检测合法
                if (if_tra)
                {
                    tran_pan5(row, col, row_n, col_n, huarongdao); //移动位置
                    count++; //步数加一
                    row_n = row;
                    col_n = col;
                    BGM_buttom();
                    //更新坐标
                }
                else
                {
                    row = row_n;
                    col = col_n;
                    //还回到原来状态
                }
                break;
            case 80:
                row--;
                if_tra = if_tran5(row, col); //检测合法
                if (if_tra)
                {
                    tran_pan5(row, col, row_n, col_n, huarongdao); //移动位置
                    count++; //步数加一
                    row_n = row;
                    col_n = col;
                    BGM_buttom();
                    //更新坐标
                }
                else
                {
                    row = row_n;
                    col = col_n;
                    //还回到原来状态
                }
                break;
            case 75:
                col++;
                if_tra = if_tran5(row, col); //检测合法
                if (if_tra)
                {
                    tran_pan5(row, col, row_n, col_n, huarongdao); //移动位置
                    count++; //步数加一
                    row_n = row;
                    col_n = col;
                    BGM_buttom();
                    //更新坐标
                }
                else
                {
                    row = row_n;
                    col = col_n;
                    //还回到原来状态
                }
                break;
            case 77:
                col--;
                if_tra = if_tran5(row, col); //检测合法
                if (if_tra)
                {
                    tran_pan5(row, col, row_n, col_n, huarongdao); //移动位置
                    count++; //步数加一
                    row_n = row;
                    col_n = col;
                    BGM_buttom();
                    //更新坐标
                }
                else
                {
                    row = row_n;
                    col = col_n;
                    //还回到原来状态
                }
                break;
            case 27:
                finalrecord[num].n = num + 1;
                finalrecord[num].count = count;
                finalrecord[num].choice = 5;
                finalrecord[num].judge = 2;
                Paintendno();

                chushi();
                break;
            }
        }
    }
    time2 = time(NULL);
    timeused = time2 - time1;
    finalrecord[num].n = num + 1;
    finalrecord[num].count = count;
    finalrecord[num].choice = 5;
    finalrecord[num].judge = 1;
    finalrecord[num].timeused = timeused;
    Paintendyes();

    getchar();
    closegraph();
}

void chushi()
{
    cleardevice();
    mciSendStringW(L"stop mymusic2", 0, 0, 0);
    mciSendStringW(L"stop mymusic3", 0, 0, 0);
    BGM();
    photo_zhuye();
    settextcolor(BLACK);
    drawbutton(begin);
    drawbutton(records);
    drawbutton(logout);
    settextcolor(BLACK);
    setbkmode(TRANSPARENT);
    settextstyle(30, 0, "华文中宋");
    drawtext("开始游戏", &b, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawtext("游戏记录", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawtext("退出游戏", &e, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    settextcolor(RED);
    settextstyle(49, 0, "楷体");
    drawtext("数字华容道", &t, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    int a = 0;
    while (true) {
        if (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            switch (msg.uMsg) {
            case WM_LBUTTONDOWN:
                if ((msg.x >= begin.x1) && (msg.x <= begin.x1 + begin.width) && (msg.y >= begin.y1) && (msg.y <= begin.y1 + begin.length))
                    a = 1;
                else if ((msg.x >= records.x1) && (msg.x <= records.x1 + records.width) && (msg.y >= records.y1) && (msg.y <= records.y1 + records.length))
                    a = 2;
                else if ((msg.x >= logout.x1) && (msg.x <= logout.x1 + logout.width) && (msg.y >= logout.y1) && (msg.y <= logout.y1 + logout.length))
                    a = 3;
                break;
            }
        }
        if (a)
            break;
    }
    switch (a) {
    case 1:beginning(); break;
    case 2:record(); break;
    case 3:exit(0);
    }
}
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

void Paintendyes() {                                                       //绘制完成游戏结束界面
    char c[100] = { 0 };
    setbkcolor(WHITE);
    cleardevice();
    photo_zhuye();
    mciSendStringW(L"close mymusic", 0, 0, 0);
    BGM_win();
    rectangle(120, 100, 220, 150);
    setlinecolor(BLACK);
    settextcolor(BLACK);
    setbkmode(TRANSPARENT);
    settextstyle(30, 0, "华文中宋");
    sprintf(c, "你的步数为%d步，你用时为%d秒", finalrecord[num].count, finalrecord[num].timeused);
    settextstyle(23, 0, "华文中宋");
    outtextxy(122, 110, "返回主页面");
    num++;
    fileinput();
    outtextxy(100, 300, c);
    settextstyle(25, 0, "华文中宋");
    outtextxy(30, 400, "游戏记录已保存至文件游戏成绩记录中，欢迎前往查看!");
    outtextxy(30, 430, "点击上方 返回主页面 来重新开启一局游戏");
    while (1)
    {
        MOUSEMSG m;
        int a = 0;
        if (MouseHit())
        {
            m = GetMouseMsg();

            switch (m.uMsg)
            {

            case WM_LBUTTONDOWN:

                //printf("%d,%d ", m.x, m.y);
                if (m.x >= 120 && m.x <= 250 && m.y <= 150 && m.y >= 100)a = 1;

                break;
            }
        }

        switch (a)
        {
        case 1:chushi(); break;
        }
    }


}
void Paintendno() {                                             //绘制放弃游戏界面      
    char c[100] = { 0 };
    setbkcolor(WHITE);
    cleardevice();
    photo_zhuye();
    mciSendStringW(L"close mymusic", 0, 0, 0);
    BGM_lose();
    rectangle(120, 100, 220, 150);
    setlinecolor(BLACK);
    settextcolor(BLACK);
    setbkmode(TRANSPARENT);
    settextstyle(30, 0, "华文中宋");
    sprintf(c, "你已选择放弃游戏，你当前的步数为%d", finalrecord[num].count, finalrecord[num].timeused);
    num++;
    settextstyle(23, 0, "华文中宋");
    outtextxy(122, 110, "返回主页面");
    fileinput();
    outtextxy(100, 300, c);
    settextstyle(25, 0, "华文中宋");
    outtextxy(30, 400, "游戏记录已保存至文件游戏成绩记录中，欢迎前往查看!");
    outtextxy(30, 430, "点击上方 返回主页面 来重新开启一局游戏");
    while (1)
    {
        MOUSEMSG m;
        int a = 0;
        if (MouseHit())
        {
            m = GetMouseMsg();

            switch (m.uMsg)
            {

            case WM_LBUTTONDOWN:

                //printf("%d,%d ", m.x, m.y);
                if (m.x >= 120 && m.x <= 250 && m.y <= 150 && m.y >= 100)a = 1;

                break;
            }
        }
        switch (a)
        {
        case 1:chushi(); break;
        }
    }
}