#include <v8.h>
#include <node.h>
#include "sorry.h"

using namespace v8;

void Initialize(Handle<Object> exports)
{
    // enum windows api
    exports->Set(String::NewSymbol("EnumWindows"),
                 FunctionTemplate::New(MyEnumWindows)->GetFunction());

    // get monitor info api
    exports->Set(String::NewSymbol("GetMonitorInfo"),
                 FunctionTemplate::New(MyGetMonitorInfo)->GetFunction());

    // monitor from window api
    exports->Set(String::NewSymbol("MonitorFromWindow"),
                 FunctionTemplate::New(MyMonitorFromWindow)->GetFunction());
}

NODE_MODULE(sorry, Initialize)