#include <stdio.h>
#include <ap_fixed.h>
#include <ap_int.h>
#include <iostream>
#include <hls_stream.h>
#include <complex>
#include <cmath>

#define N 8

using namespace std;

typedef std::complex<ap_fixed <26,6> > complex_tout;
typedef std::complex<ap_fixed <21,2> > complex_tin;
typedef ap_fixed <32,12> in32;

typedef ap_fixed <22,3> mydata;                           //R[i][i]
typedef ap_fixed <68,8> mydata2;

//struct arr_out {complex_tin elements[N];};
struct arr_out {complex_tout elements[N];};
struct arr_in {complex_tin elements[N];};

typedef  ap_uint<4>my_int;

void inverse(hls::stream <arr_in> &Q_in,
					hls::stream < arr_in > &R_in,
					hls::stream <in32> &div,
					hls::stream < arr_out >&X_out);
