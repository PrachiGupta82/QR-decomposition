#include "header.h"

in_type temp_in;
out_type temp_out;

void div(hls::stream < in_type >&in, hls::stream < out_type > &out)

{
#pragma HLS inTERFACE axis register both port=in
#pragma HLS inTERFACE axis register both port=out

#pragma HLS PIPELINE II=1
	in>>temp_in;
	temp_out=1/((double)temp_in);
	out<<temp_out;
}
