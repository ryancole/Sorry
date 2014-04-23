#ifndef _SORRY_H_
#define _SORRY_H_

#include <v8.h>
#include <node.h>
#include <Windows.h>

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam);
v8::Handle<v8::Value> MyFindWindow(const v8::Arguments& args);
v8::Handle<v8::Value> MyEnumWindows(const v8::Arguments& args);
v8::Handle<v8::Value> MySetWindowPos(const v8::Arguments& args);
v8::Handle<v8::Value> MyGetWindowLong(const v8::Arguments& args);
v8::Handle<v8::Value> MyGetWindowRect(const v8::Arguments& args);
v8::Handle<v8::Value> MyGetMonitorInfo(const v8::Arguments& args);
v8::Handle<v8::Value> MyMonitorFromWindow(const v8::Arguments& args);

#endif