/**
 * KFR (http://kfrlib.com)
 * Copyright (C) 2016  D Levin
 * See LICENSE.txt for details
 */

// library_version()
#include <kfr/version.hpp>

// print(), format()
#include <kfr/cometa/string.hpp>

#include <kfr/math.hpp>

// expression_pointer<>, topointer()
#include <kfr/expressions/pointer.hpp>

// simpleimpulse()
#include <kfr/dsp/oscillators.hpp>

// fir
#include <kfr/dsp/fir.hpp>

// fir_*
#include <kfr/dsp/fir_design.hpp>

// plot_save()
#include <kfr/io/python_plot.hpp>

#include <iostream>

using namespace kfr;
using namespace kfr::native;

int main(int argc, char** argv)
{
    println(library_version());

    using namespace native;
    const std::string options = "phaseresp=False";

    univector<double, 15> taps15;
    univector<double, 127> taps127;
    univector<double, 8191> taps8191;

    expression_pointer<double> hann = to_pointer(window_hann(taps15.size()));

    expression_pointer<double> kaiser = to_pointer(window_kaiser(taps127.size(), 3.0));

    expression_pointer<double> blackman_harris = to_pointer(window_blackman_harris(taps8191.size()));

    fir_lowpass(taps15, 0.15, hann, true);
    plot_save("fir_lowpass_hann", taps15, options + ", title='15-point lowpass FIR, Hann window'");

    fir_lowpass(taps127, 0.2, kaiser, true);
    plot_save("fir_lowpass_kaiser", taps127,
              options + ", title=r'127-point lowpass FIR, Kaiser window ($\\alpha=3.0$)'");

    fir_highpass(taps127, 0.2, kaiser, true);
    plot_save("fir_highpass_kaiser", taps127,
              options + ", title=r'127-point highpass FIR, Kaiser window ($\\alpha=3.0$)'");

    fir_bandpass(taps127, 0.2, 0.4, kaiser, true);
    plot_save("fir_bandpass_kaiser", taps127,
              options + ", title=r'127-point bandpass FIR, Kaiser window ($\\alpha=3.0$)'");

    fir_bandstop(taps127, 0.2, 0.4, kaiser, true);
    plot_save("fir_bandstop_kaiser", taps127,
              options + ", title=r'127-point bandstop FIR, Kaiser window ($\\alpha=3.0$)'");

    fir_lowpass(taps8191, 0.15, blackman_harris, true);
    plot_save("fir_lowpass_blackman", taps8191,
              options + ", title='8191-point lowpass FIR, Blackman-Harris window'");

    return 0;
}
