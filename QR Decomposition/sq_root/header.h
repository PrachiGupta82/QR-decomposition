#include <stdio.h>
#include <ap_fixed.h>
#include <ap_int.h>
#include <iostream>
#include <hls_stream.h>
#include <complex>
#include <cmath>

using namespace std;

typedef ap_fixed <32,5> in_type;
typedef ap_fixed <24,4> out_type;


void sq_root(hls::stream < in_type >&in, hls::stream < out_type >&out);
