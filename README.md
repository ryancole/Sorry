`Sorry` is a node.js module that provides simple wrappers around several Win32 API functions. If you're looking at `Sorry` and contemplating using it, I feel your pain and I am `Sorry`.

## Building

You must have the pre-reqs for `node-gyp` installed. Build `Sorry` with `node-gyp` ...

```
node-gyp.cmd clean; node-gyp.cmd configure; node-gyp.cmd build; npm test
```
