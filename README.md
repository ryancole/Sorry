`Sorry` is a node.js module that provides simple wrappers around several Win32 API functions.

## Building

You must have the pre-reqs for `node-gyp` installed. Build `Sorry` with `node-gyp` ...

```
node-gyp.cmd clean; node-gyp.cmd configure; node-gyp.cmd build; npm test
```