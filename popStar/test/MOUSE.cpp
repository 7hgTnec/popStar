#include <stdio.h>    
#include <windows.h>    
#include <conio.h>  
#include<iostream>  
using namespace std;
HANDLE handle_in;    
HANDLE handle_out;    
//CONSOLE_SCREEN_BUFFER_INFO csbi;        //���崰�ڻ�������Ϣ�ṹ��    
           
        
int main()    
{   cout<<"111111"<<endl;
    handle_in = GetStdHandle(STD_INPUT_HANDLE);      //��ñ�׼�����豸���    
    handle_out = GetStdHandle(STD_OUTPUT_HANDLE);    //��ñ�׼����豸���    
    INPUT_RECORD mouserec;      //���������¼��ṹ��    
    DWORD res;      //���ڴ洢��ȡ��¼    
    COORD pos;      //���ڴ洢��굱ǰλ��    
    COORD size = {80, 25};  //���ڻ�������С    
    //GetConsoleScreenBufferInfo(handle_out, &csbi);  //��ô��ڻ�������Ϣ    
    //SetConsoleScreenBufferSize(handle_out, size);   //���ô��ڻ�������С    
    for (;;)    
    {   cout<<"2"<<endl;
        ReadConsoleInput(handle_in, &mouserec, 1, &res);      //��ȡ�����¼�    
        pos = mouserec.Event.MouseEvent.dwMousePosition;    //��õ�ǰ���λ��    
        
        
		cout<<"3"<<endl;
		cout<<pos.X<<endl;
		cout<<pos.Y<<endl;
        if (mouserec.EventType == WM_LBUTTONDOWN)    //�����ǰΪ����¼�    
        {  
			cout<<"4"<<endl;
        }    
    }    
    CloseHandle(handle_out);    
    CloseHandle(handle_in);    
    return 0;    
}
