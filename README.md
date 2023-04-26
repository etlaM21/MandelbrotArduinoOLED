# Mandelbrot Zoom Implementation in Arduino

Mandelbrot Arduino sketch running on Teensy 3.0 with a 3 x 0.96 inch (128 x 64 Pixel) OLED display connected via I2C.
The sketch uses the Adafruit_SSD1306 library to draw on the display.

The tactile two-pin push button switch is connected to Teensy pin 2 to switch between three draw modes:
1. Refresh screen when new mandelbrot zoom is fully calculated
2. Refresh screen when one column of pixels of new mandelbrot zoom is fully calculated
2. Refresh screen whenever a single pixel of new mandelbrot zoom is fully calculated

Sketch currently zooms in fifty times.

## Complex numbers

There is no complex library used, instead real numbers simulate a complex-number operation.

The algorithm can be found on [Wikipedia: Plotting algorithms for the Mandelbrot set](https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set).

A "naïve escape time algorithm" escapes when the complex part c > 2. This could be optimized.

## openFrameworks implementation
For debugging / testing purposes an openFramework implementation can also be found under [openFrameworks_mandelbrot](openFrameworks_mandelbrot).

It does not feature different draw modes and sleeps 200 milliseconds between zooms.

Implementation was compiled with the nightly release on 04/04/2023.