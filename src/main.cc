#include <v8.h>
#include <node.h>
#include "sorry.h"

using namespace v8;

void Initialize(Handle<Object> exports)
{
    // enum windows api
    exports->Set(String::NewSymbol("EnumWindows"),
                 FunctionTemplate::New(MyEnumWindows)->GetFunction());

    // set window position api
    exports->Set(String::NewSymbol("SetWindowPos"),
                 FunctionTemplate::New(MySetWindowPos)->GetFunction());

    // get window long api
    exports->Set(String::NewSymbol("GetWindowLong"),
                 FunctionTemplate::New(MyGetWindowLong)->GetFunction());

    // get window rect api
    exports->Set(String::NewSymbol("GetWindowRect"),
                 FunctionTemplate::New(MyGetWindowRect)->GetFunction());

    // get monitor info api
    exports->Set(String::NewSymbol("GetMonitorInfo"),
                 FunctionTemplate::New(MyGetMonitorInfo)->GetFunction());

    // monitor from window api
    exports->Set(String::NewSymbol("MonitorFromWindow"),
                 FunctionTemplate::New(MyMonitorFromWindow)->GetFunction());
}

NODE_MODULE(sorry, Initialize)