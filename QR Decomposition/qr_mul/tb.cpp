#include "header.h"

int main()
{
	hls::stream <complex_tin1> in;
	hls :: stream <complex_tin2> mul;
	hls :: stream <out_type> out_real;
	hls :: stream <out_type> out_imag;

	complex_tin1 temp_in;
	complex_tin2 temp_mul;
	out_type temp_out_real;
	out_type temp_out_imag;

	complex_tin1 arr[]={{0.2678, -0.4882}, {-0.5998, 0.2345}, {-0.0087, -0.1907}, {-0.7017, -0.3451}};

	complex_tin2 arr2[]={{1.80025, 0}, {0.287783, -0.13146}, {-0.451546, -0.335207}};

	for(int i=0;i<3;i++)
	{
		in<<arr[i];
		mul<<arr2[i];
		qr_mul(in,mul,out_real,out_imag);
		out_real>>temp_out_real;
		out_imag>>temp_out_imag;
		cout<<"real ->"<<temp_out_real<<"  imag -> "<<temp_out_imag<<endl;
	}
}
