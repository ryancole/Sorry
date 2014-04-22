#include <v8.h>
#include <node.h>
#include <vector>
#include <Windows.h>

using namespace v8;

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
    // cast the collection of handles
    std::vector<HWND>* handles = reinterpret_cast<std::vector<HWND>*>(lParam);

    // add hwnd to collection
    handles->push_back(hWnd);

    return true;
}

Handle<Value> EnumWindows(const Arguments& args)
{
    HandleScope scope;

    // parameter validation
    if (args.Length() != 1 || !args[0]->IsFunction())
    {
        ThrowException(Exception::SyntaxError(String::New("expects one callback parameter")));
        return scope.Close(Boolean::New(false));
    }

    std::vector<HWND> handles;

    // populate handles collection
    auto result = EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&handles));

    // store callback function
    auto callback = Local<Function>::Cast(args[0]);

    // initialize collection of handles
    auto array = Array::New(handles.size());

    for (unsigned int x = 0; x < handles.size(); x++)
    {
        array->Set(Number::New(x), Number::New((int)handles[x]));
    }

    // intialize callback function parameter
    Local<Value> argv[1] = { array };

    // execute the callback
    callback->Call(Context::GetCurrent()->Global(), 1, argv);

    return scope.Close(Boolean::New(result == 1));
}

void Initialize(Handle<Object> exports)
{
    // enum windows api
    exports->Set(String::NewSymbol("EnumWindows"),
                 FunctionTemplate::New(EnumWindows)->GetFunction());
}

NODE_MODULE(sorry, Initialize)