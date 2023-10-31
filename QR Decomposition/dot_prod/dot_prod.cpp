#include "dot_header.h"



void dot_prod(hls::stream < arr_pkt_in >&in, hls::stream < my_data > &out)
{
#pragma HLS inTERFACE axis register both port=in
#pragma HLS inTERFACE axis register both port=out
#pragma HLS PIPELINE II=1
#pragma HLS data_pack variable=in
	arr_pkt_in temp_in;
	complex_tout temp_out(0.0,0.0);

	in>>temp_in;
	for(int i=0;i<N;i++)
	{

		temp_out += temp_in.elements[i].real()* temp_in.elements[i].real();
		temp_out += temp_in.elements[i].imag()* temp_in.elements[i].imag();
		//cout <<i<<"  "<<temp_in.elements[i]<<"--"<<temp_out.real()<<endl;

	}

	out<<temp_out.real();

}
