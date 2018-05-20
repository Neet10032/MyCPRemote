// MyDebug.h: interface for the MyDebug class.
//
//////////////////////////////////////////////////////////////////////



//MyOutputDebugString.h   
#ifndef MY_OUTPUTDEBUGSTRING_H  
#define MY_OUTPUTDEBUGSTRING_H  
#define MYPRINT  

#include <string>  

//使用示例：MyOutputDebugStringA("%d,%s",123,"hello");  
void MyOutputDebugStringA(const char * lpcszOutputString, ...);

//使用示例：MyOutputDebugStringW(L"%d,%s",456,L"world!");  
void MyOutputDebugStringW(const wchar_t * szOutputString, ...);

#ifdef UNICODE
#define MyOutputDebugString  MyOutputDebugStringW
#else
#define MyOutputDebugString  MyOutputDebugStringA
#endif // !UNICODE


#endif


