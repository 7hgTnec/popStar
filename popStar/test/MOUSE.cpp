#include <stdio.h>    
#include <windows.h>    
#include <conio.h>  
#include<iostream>  
using namespace std;
HANDLE handle_in;    
HANDLE handle_out;    
//CONSOLE_SCREEN_BUFFER_INFO csbi;        //定义窗口缓冲区信息结构体    
           
        
int main()    
{   cout<<"111111"<<endl;
    handle_in = GetStdHandle(STD_INPUT_HANDLE);      //获得标准输入设备句柄    
    handle_out = GetStdHandle(STD_OUTPUT_HANDLE);    //获得标准输出设备句柄    
    INPUT_RECORD mouserec;      //定义输入事件结构体    
    DWORD res;      //用于存储读取记录    
    COORD pos;      //用于存储鼠标当前位置    
    COORD size = {80, 25};  //窗口缓冲区大小    
    //GetConsoleScreenBufferInfo(handle_out, &csbi);  //获得窗口缓冲区信息    
    //SetConsoleScreenBufferSize(handle_out, size);   //设置窗口缓冲区大小    
    for (;;)    
    {   cout<<"2"<<endl;
        ReadConsoleInput(handle_in, &mouserec, 1, &res);      //读取输入事件    
        pos = mouserec.Event.MouseEvent.dwMousePosition;    //获得当前鼠标位置    
        
        
		cout<<"3"<<endl;
		cout<<pos.X<<endl;
		cout<<pos.Y<<endl;
        if (mouserec.EventType == WM_LBUTTONDOWN)    //如果当前为鼠标事件    
        {  
			cout<<"4"<<endl;
        }    
    }    
    CloseHandle(handle_out);    
    CloseHandle(handle_in);    
    return 0;    
}
