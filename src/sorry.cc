#include <v8.h>
#include <node.h>
#include <vector>
#include <Windows.h>

using namespace v8;

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
    // cast the collection of handles
    std::vector<int>* handles = reinterpret_cast<std::vector<int>*>(lParam);

    // add hwnd to collection
    handles->push_back((int)hWnd);

    return true;
}

Handle<Value> EnumWindows(const Arguments& args)
{
    HandleScope scope;

    std::vector<int> handles;

    // populate handles collection
    if (EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&handles)))
    {
        // initialize collection of handles
        auto result = Array::New(handles.size());

        for (unsigned int x = 0; x < handles.size(); x++)
        {
            result->Set(Number::New(x), Number::New(handles[x]));
        }

        return scope.Close(result);
    }

    return scope.Close(Array::New(0));
}

void Initialize(Handle<Object> exports)
{
    // enum windows api
    exports->Set(String::NewSymbol("EnumWindows"),
                 FunctionTemplate::New(EnumWindows)->GetFunction());
}

NODE_MODULE(sorry, Initialize)