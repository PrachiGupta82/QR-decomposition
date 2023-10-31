#include "header.h"

void qr_mul(hls::stream <complex_tin1> &in,
			hls :: stream <complex_tin2> &mul,
			hls :: stream <out_type> &out_real,
			hls :: stream <out_type> &out_imag)
{


#pragma HLS interface axis register both port =mul
#pragma HLS INTERFACE axis register both port=in
#pragma HLS INTERFACE axis register both port=out_real
#pragma HLS INTERFACE axis register both port=out_imag


	complex_tin1 temp_in;
	complex_tin2 temp_mul;
	out_type temp_out_real;
	out_type temp_out_imag;


	mydata mul_real;
	mydata mul_real2;
	mydata mul_imag;
	mydata mul_imag2;

	mydata real_part;
	mydata imag_part;

	in>>temp_in;
	mul>>temp_mul;

	mul_real=temp_mul.real() * temp_in.real();
	mul_real2=temp_mul.imag() * temp_in.imag();
	real_part= mul_real-mul_real2;
	temp_out_real= out_type(real_part);
	out_real<<temp_out_real;

	mul_imag=temp_mul.imag() * temp_in.real();
	mul_imag2=temp_mul.real() * temp_in.imag();
	imag_part= mul_imag+mul_imag2;
	temp_out_imag= out_type(imag_part);
	out_imag<<temp_out_imag;


}
