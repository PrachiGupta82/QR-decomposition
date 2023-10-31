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
//typedef std::complex<ap_fixed <42,4> > complex_tout;

struct arr_pkt_in { complex_tin elements[N]; };
//struct arr_pkt_out { complex_tout elements[N]; };

typedef std::complex<ap_fixed <32,5> > complex_tout;
typedef ap_fixed <32,5> my_data;

void dot_prod(hls::stream < arr_pkt_in >&in, hls::stream < my_data > &out);

