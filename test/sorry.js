var sorry = require('../build/release/sorry');

// print methods
console.log(sorry);

// call methods
console.log(sorry.EnumWindows(function (handle) {

    console.log(handle);

}));