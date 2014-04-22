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