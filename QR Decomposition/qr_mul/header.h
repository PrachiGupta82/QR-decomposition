#include <stdio.h>
#include <ap_fixed.h>
#include <ap_int.h>
#include <iostream>
#include <hls_stream.h>
#include <complex>
#include <cmath>

#define N 8

using namespace std;

typedef ap_fixed <26,6>  out_type;
typedef std::complex<ap_fixed <24,5> > complex_tin2;
typedef std::complex<ap_fixed <26,6> > complex_tin1;


typedef ap_fixed <52,12> mydata;

void qr_mul(hls::stream <complex_tin1> &in,
			hls :: stream <complex_tin2> &mul,
			hls :: stream <out_type> &out_real,
			hls :: stream <out_type> &out_imag);
