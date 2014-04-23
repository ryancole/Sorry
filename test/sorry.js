var sorry = require('../build/release/sorry');

// get available windows
var windows = sorry.EnumWindows();

windows.forEach(function (window) {

    var GWL_STYLE = -16;
    var WS_CAPTION = 12582912;
    var WS_VISIBLE = 268435456;

    // get window style
    var style = sorry.GetWindowLong(window, GWL_STYLE);

    // check for caption and visibility
    if ((style & 281018368) === 281018368)
    {
        centerWindow(window);
    }

});

function centerWindow(window)
{
    // get window dimensions
    var dimensions = sorry.GetWindowRect(window);

    // calculate width and height
    var width = dimensions.right - dimensions.left;
    var height = dimensions.bottom - dimensions.top;

    // get the nearest monitor for the window
    var monitor = sorry.MonitorFromWindow(window);

    // get resolution details for the monitor
    var resolution = sorry.GetMonitorInfo(monitor);

    // calculate the new window position
    var top = Math.floor(resolution.monitor.top + (resolution.monitor.bottom - resolution.monitor.top - height) / 2);
    var left = Math.floor(resolution.monitor.left + (resolution.monitor.right - resolution.monitor.left - width) / 2);

    // set window position
    return sorry.SetWindowPos(window, left, top);
}