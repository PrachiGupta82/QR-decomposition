#include <stdio.h>
#include <ap_fixed.h>
#include <ap_int.h>
#include <iostream>
#include <hls_stream.h>
#include <complex>
#include <cmath>

#define N 8

using namespace std;

typedef std::complex<ap_fixed <26,6> > complex_tin;
typedef ap_fixed <32,12> mul_type;
//typedef std::complex<ap_fixed <26,6> > complex_tin;

void inverse_output(hls::stream < complex_tin > &in,
					hls::stream < mul_type > &mul,
					hls:: stream < complex_tin > &out);
