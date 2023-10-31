#include "Q_header.h"

div_data temp_div;
arr_pkt_in temp_U;
complex_tin temp_U_arr[8];
arr_pkt_out temp_Qout;
//typedef std::complex<ap_fixed <40,20> > temp_mul;

void Q_matrix(hls::stream <arr_pkt_in> &U_in,
				hls::stream < div_data >&div_in,
				hls::stream < arr_pkt_out >&Q_out)
{
#pragma HLS PIPELINE II=1
	static ap_uint<7> num=0;
	#pragma HLS RESET variable=num

#pragma HLS data_pack variable=U_in
#pragma HLS data_pack variable=Q_out


#pragma HLS inTERFACE axis register both port=U_in
#pragma HLS inTERFACE axis register both port=div_in
#pragma HLS inTERFACE axis register both port=Q_out

	U_in>>temp_U;
	div_in>>temp_div;
	for(int i=0;i<N;i++)
	{
		mydata real_part = temp_U.elements[i].real() * temp_div;
		mydata imag_part = temp_U.elements[i].imag() * temp_div;

		temp_Qout.elements[i] = complex_tout(real_part, imag_part);
	}
Q_out<<temp_Qout;

}
