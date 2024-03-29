/*
Thanks output created by group D2 on 12.5.2022
Some parts of the code modified from
https://blog.csdn.net/hit1524468/article/details/110733016
*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <cstdlib>
 
using namespace std;
 
#define WINDOWS_SYSTEM (0)
#define LINUX_STSTEM (1)
#define SYSTEM_TYPE (1)
 
#if SYSTEM_TYPE == WINDOWS_SYSTEM
#include <iostream>
#include <windows.h>
 
inline std::ostream& blue(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE
                            |FOREGROUND_GREEN|FOREGROUND_INTENSITY);
    return s;
}
 
inline std::ostream& red(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
                            FOREGROUND_RED|FOREGROUND_INTENSITY);
    return s;
}
inline std::ostream& green(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
                            FOREGROUND_GREEN|FOREGROUND_INTENSITY);
    return s;
}
 
inline std::ostream& yellow(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
                            FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
    return s;
}
 
inline std::ostream& white(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
                            FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    return s;
}
 
struct color {
    color(WORD attribute):m_color(attribute){};
    WORD m_color;
};
 
template <class _Elem, class _Traits>
std::basic_ostream<_Elem,_Traits>&
operator<<(std::basic_ostream<_Elem,_Traits>& i, const color& c)
{
    HANDLE hStdout=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,c.m_color);
    return i;
}
 
#elif SYSTEM_TYPE == LINUX_STSTEM
 
const std::vector<std::string> TERMINAL_CONTROL={std::string("\033[0m"), // 关闭属性
                                                 std::string("\033[1m"), // 设置高亮
                                                 std::string("\033[3m"), // 斜体
                                                 std::string("\033[4m"), // 下划线
                                                 std::string("\033[5m"), // 闪烁（无效）
                                                 std::string("\033[7m"), // 反显
                                                 std::string("\033[8m"), // 消隐
                                                 std::string("\033[30m"), // 设置前景色:黑色
                                                 std::string("\033[40m"), // 设置背景色:黑色
                                                 std::string("\033[31m"), // 设置前景色:深红
                                                 std::string("\033[41m"), // 设置背景色:深红
                                                 std::string("\033[32m"), // 设置前景色:绿色
                                                 std::string("\033[42m"), // 设置背景色:绿色
                                                 std::string("\033[33m"), // 设置前景色:黄色
                                                 std::string("\033[43m"), // 设置背景色:黄色
                                                 std::string("\033[34m"), // 设置前景色:蓝色
                                                 std::string("\033[44m"), // 设置背景色:蓝色
                                                 std::string("\033[35m"), // 设置前景色:紫色
                                                 std::string("\033[45m"), // 设置背景色:紫色
                                                 std::string("\033[36m"), // 设置前景色:深绿色
                                                 std::string("\033[46m"), // 设置背景色:深绿色
                                                 std::string("\033[37m"), // 设置前景色:白色
                                                 std::string("\033[47m"), // 设置背景色:白色
                                                 std::string("\033[nA"), // 光标上移n行
                                                 std::string("\033[nB"), // 光标下移n行
                                                 std::string("\033[nC"), // 光标右移n列
                                                 std::string("\033[nD"), // 光标左移n列
                                                 std::string("\033[y;xH"), // 设置光标位置(无效)
                                                 std::string("\033[2J"), // 清屏
                                                 std::string("\033[K"), // 清除从光标道行尾的内容
                                                 std::string("\033[s"), // 保存光标位置
                                                 std::string("\033[u"), // 恢复光标位置
                                                 std::string("\033[?25l"), // 隐藏光标
                                                 std::string("\033[?25h"), // 显示光标
                                                };
 
inline std::ostream& blue(std::ostream &s)
{
    //    s << "\033[0m\033[34m\033[1m"; // ok
    s << "\033[0;1;34m";
    return s;
}
 
inline std::ostream& red(std::ostream &s)
{
    //    s << "\033[0m\033[31m\033[1m"; // ok
    s << "\033[0;1;31m";
    return s;
}
 
inline std::ostream& green(std::ostream &s)
{
    //    s << "\033[0m\033[32m\033[1m"; // ok
    s << "\033[0;1;32m";
    return s;
}
 
inline std::ostream& yellow(std::ostream &s)
{
    //    s << "\033[0m\033[33m\033[1m"; // ok
    s << "\033[0;1;33m";
    return s;
}
 
inline std::ostream& white(std::ostream &s)
{
    //    s << "\033[0m\033[37m\033[1m"; // ok
    s << "\033[0;1;37m";
    return s;
}
 
 
inline std::ostream& reset(std::ostream& s)
{
    s << "\033[0m";
    return s;
}
 
#endif
 
 
int thanks()
{
    cout << endl;
    cout << endl;
    cout << endl;
    Sleep(200);
    cout<< red << "   _______  _                    _              _        _        _ " << "\033[0m" << endl;
    Sleep(200);
    cout<< red << "  |__   __|| |                  | |            | |      | |      | |" << "\033[0m" << endl;
    Sleep(200);
    cout<< yellow << "     | |   | |__    __ _  _ __  | | __ ___     | |      | |      | |" << std::endl;
    Sleep(200);
    cout<< green << "     | |   | '_ \\  / _` || '_ \\ | |/ // __|    | |      | |      | |" << "\033[0m" << endl;
    Sleep(200);
    cout<< "\033[0;1;36m" << "     | |   | | | || (_| || | | ||   < \\__ \\    |_|      |_|      |_|" << reset << std::endl;
    Sleep(200);
    cout<< blue << "     |_|   |_| |_| \\__,_||_| |_||_|\\_\\|___/     _        _        _  " << reset << std::endl;
    Sleep(200);
    cout<< "\033[0;1;35m" << "                                               (_)      (_)      (_)    " << reset << std::endl;
    Sleep(200);
    cout<< "                                                                                              \n";
    Sleep(200);
    cout<< endl;
    cout<< endl;
    cout<< endl;
    return 0;
}
