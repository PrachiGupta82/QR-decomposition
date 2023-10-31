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
typedef ap_fixed <32,12> div_data;
typedef std::complex<ap_fixed <24,5> > complex_tout;

//typedef std::complex<ap_fixed <40,20> > temp_mul;;

struct arr_pkt_in { complex_tin elements[N]; };
struct arr_pkt_out { complex_tout elements[N]; };

typedef ap_fixed<54, 15> mydata;

void Q_matrix(hls::stream <arr_pkt_in> &U_in, hls::stream < div_data >&div_in, hls::stream < arr_pkt_out >&Q_out);

