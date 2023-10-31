#include "header.h"

void inverse_output(hls::stream < complex_tin > &in,
					hls::stream < mul_type > &mul,
					hls:: stream < complex_tin > &out)
{

#pragma HLS data_pack variable=in
#pragma HLS data_pack variable=out

#pragma HLS PIPELINE II=1
#pragma HLS INTERFACE axis register both port=out
#pragma HLS INTERFACE axis register both port=mul
#pragma HLS INTERFACE axis register both port=in
//#pragma HLS INTERFACE axis register both port=mul_out


//#pragma HLS data_pack variable=R_in
	complex_tin temp_in;
	complex_tin temp_out;
	mul_type temp_mul;

	static mul_type mul_arr[N];

	enum state{in_mul, cal};
	static state present_state;

	static ap_uint<4> z=0;
	#pragma HLS RESET variable=z

	static ap_uint<7> i=0;
	#pragma HLS RESET variable=i

	switch(present_state)
	{
	case(in_mul):{
					//cout<<"in mul+++++++++++++"<<endl;
					if(z<N-1)
					{
						mul>>mul_arr[z];
						//cout<<i<<" "
						z=z+1;
						present_state=in_mul;
					}
					else
					{
						//cout<<"in mul+++++++++++++"<<endl;
						mul>>mul_arr[z];
						z=z+1;
						present_state=cal;
					}

				}
				break;
	case(cal):{
				//cout<<"in cal----------------------+++++++++++++"<<endl;
				if((i%8)==0)
				{
					z=z-1;
					//temp_mul=mul_arr[z];
				}
				if(i<63)
				{
					in>>temp_in;
					//cout<<i<<" -in- "<<temp_in<< "mul-> "<<mul_arr[z]<<endl;
					ap_fixed <26,6> real_part = temp_in.real() * mul_arr[z];
					ap_fixed <26,6> imag_part = temp_in.imag() * mul_arr[z];
					temp_out= complex_tin(real_part, imag_part);
					//cout<<i<<" -temp_out-> "<<temp_in<<endl;
					present_state=cal;
					i=i+1;
					out<<temp_out;
					//mul_out<<mul_arr[z];
				}
				else
				{
					in>>temp_in;
					//cout<<i<<" -in- "<<temp_in<< "mul-> "<<mul_arr[z]<<endl;
					ap_fixed <26,6> real_part = temp_in.real() * mul_arr[z];
					ap_fixed <26,6> imag_part = temp_in.imag() * mul_arr[z];
					temp_out= complex_tin(real_part, imag_part);
					//cout<<i<<" -temp_out-> "<<temp_in<<endl;
					present_state=in_mul;
					i=0;
					out<<temp_out;
					//mul_out<<mul_arr[z];
				}
				}
				break;
	default: present_state=in_mul;
	}



}
