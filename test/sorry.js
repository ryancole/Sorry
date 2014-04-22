var sorry = require('../build/release/sorry');

// get available windows
var windows = sorry.EnumWindows();

windows.forEach(function (window) {

    // get monitor identifier for the window
    var monitor = sorry.MonitorFromWindow(window);

    // get monitor info for the monitor
    var details = sorry.GetMonitorInfo(monitor);

    console.log(details);

});