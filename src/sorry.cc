#include <vector>
#include "sorry.h"

using namespace v8;

Handle<Value> MyEnumWindows(const Arguments& args)
{
    HandleScope scope;

    std::vector<int> handles;

    // fetch all available window handles
    if (EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&handles)))
    {
        // initialize collection of handles
        auto result = Array::New(handles.size());

        // populate collection of handles
        for (unsigned int x = 0; x < handles.size(); x++)
        {
            result->Set(Number::New(x), Number::New(handles[x]));
        }

        // return collection of handles
        return scope.Close(result);
    }

    return scope.Close(Array::New(0));
}

Handle<Value> MySetWindowPos(const Arguments& args)
{
    HandleScope scope;

    // paramater validation
    if (args.Length() != 3 || 
        args[0]->IsUint32() == false ||
        args[1]->IsUint32() == false ||
        args[2]->IsUint32() == false)
    {
        ThrowException(Exception::SyntaxError(String::New("expected three integer parameters")));
        return scope.Close(Boolean::New(false));
    }

    // get parameters
    auto x = args[1]->ToUint32()->Value();
    auto y = args[2]->ToUint32()->Value();
    auto window = (HWND)args[0]->ToUint32()->Value();
    
    // set the window position
    auto result = SetWindowPos(window, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);

    // return result of SetWindowPos
    return scope.Close(Boolean::New(result == 1));
}

Handle<Value> MyGetWindowLong(const Arguments& args)
{
    HandleScope scope;

    // paramater validation
    if (args.Length() != 2 ||
        args[0]->IsUint32() == false ||
        args[1]->IsInt32() == false)
    {
        ThrowException(Exception::SyntaxError(String::New("expected two integer parameter")));
        return scope.Close(Undefined());
    }

    // get parameters
    auto index = args[1]->ToInt32()->Value();
    auto window = (HWND)args[0]->ToUint32()->Value();

    // get window long data
    auto result = GetWindowLong(window, index);

    return scope.Close(Int32::New(result));
}

Handle<Value> MyGetWindowRect(const Arguments& args)
{
    HandleScope scope;

    // paramater validation
    if (args.Length() != 1 || !args[0]->IsUint32())
    {
        ThrowException(Exception::SyntaxError(String::New("expected a single integer parameter")));
        return scope.Close(Undefined());
    }

    RECT rect;

    // get parameters
    auto window = (HWND)args[0]->ToUint32()->Value();

    // get window dimensions
    if (GetWindowRect(window, &rect) != 0)
    {
        auto result = Object::New();

        result->Set(String::NewSymbol("top"), Integer::New(rect.top));
        result->Set(String::NewSymbol("left"), Integer::New(rect.left));
        result->Set(String::NewSymbol("right"), Integer::New(rect.right));
        result->Set(String::NewSymbol("bottom"), Integer::New(rect.bottom));

        return scope.Close(result);
    }

    return scope.Close(Undefined());
}

Handle<Value> MyGetMonitorInfo(const Arguments& args)
{
    HandleScope scope;

    // paramater validation
    if (args.Length() != 1 || !args[0]->IsUint32())
    {
        ThrowException(Exception::SyntaxError(String::New("expected a single integer parameter")));
        return scope.Close(Undefined());
    }

    MONITORINFO details;

    // set size
    details.cbSize = sizeof(MONITORINFO);

    // get the provided monitor id
    auto monitor = (HMONITOR)args[0]->ToUint32()->Value();

    // get monitor info
    if (GetMonitorInfo(monitor, &details) != 0)
    {
        auto result = Object::New();
        auto resultWork = Object::New();
        auto resultMonitor = Object::New();

        // set work properties
        resultWork->Set(String::NewSymbol("top"), Integer::New(details.rcWork.top));
        resultWork->Set(String::NewSymbol("left"), Integer::New(details.rcWork.left));
        resultWork->Set(String::NewSymbol("right"), Integer::New(details.rcWork.right));
        resultWork->Set(String::NewSymbol("bottom"), Integer::New(details.rcWork.bottom));

        // set monitor properties
        resultMonitor->Set(String::NewSymbol("top"), Integer::New(details.rcMonitor.top));
        resultMonitor->Set(String::NewSymbol("left"), Integer::New(details.rcMonitor.left));
        resultMonitor->Set(String::NewSymbol("right"), Integer::New(details.rcMonitor.right));
        resultMonitor->Set(String::NewSymbol("bottom"), Integer::New(details.rcMonitor.bottom));

        result->Set(String::NewSymbol("work"), resultWork);
        result->Set(String::NewSymbol("monitor"), resultMonitor);
        result->Set(String::NewSymbol("primary"), Boolean::New(details.dwFlags & MONITORINFOF_PRIMARY));

        return scope.Close(result);
    }

    return scope.Close(Undefined());
}

Handle<Value> MyMonitorFromWindow(const Arguments& args)
{
    HandleScope scope;

    // paramater validation
    if (args.Length() != 1 || !args[0]->IsUint32())
    {
        ThrowException(Exception::SyntaxError(String::New("expected a single integer parameter")));
        return scope.Close(Undefined());
    }

    // get the provided hwnd
    auto hwnd = (HWND)args[0]->ToUint32()->Value();

    // get the monitor details
    auto monitor = (int)MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);

    return scope.Close(Number::New(monitor));
}

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
    // cast the collection of handles
    std::vector<int>* handles = reinterpret_cast<std::vector<int>*>(lParam);

    // add hwnd to collection
    handles->push_back((int)hWnd);

    return true;
}