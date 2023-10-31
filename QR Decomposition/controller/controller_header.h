#include <stdio.h>
#include <ap_fixed.h>
#include <ap_int.h>
#include <iostream>
#include <hls_stream.h>
#include <complex>
#include <cmath>

#define N 8

using namespace std;

typedef std::complex<ap_fixed <16,1> > complex_tin;
typedef std::complex<ap_fixed <24,5> > complex_tout;

typedef ap_fixed <22,3> mydata;                           //R[i][i]
struct arr_out {complex_tin elements[N];};
struct arr_in {complex_tout elements[N];};
struct arr_out_r {complex_tout elements[N];};

typedef  ap_uint<4>my_int;

void controller_src(hls::stream <complex_tin> &U_in,
					hls::stream < mydata > &R_in,
					hls::stream <arr_in> &Q_in,
					hls::stream <arr_out >&U_out,
					hls::stream <arr_out_r> &R_out);
