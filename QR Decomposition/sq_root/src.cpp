
#include "header.h"

in_type temp_in;
out_type temp_out;

//#define DOUBLE_PREC

void sq_root(hls::stream < in_type >&in, hls::stream < out_type >&out)
{

#pragma HLS inTERFACE axis register both port=in
#pragma HLS inTERFACE axis register both port=out
#pragma HLS PIPELINE II=1

	in>>temp_in;

//#ifdef DOUBLE_PREC
//	temp_out=sqrt((double)temp_in);
//#else
	temp_out=sqrt((double)temp_in);
//#endif
	out<<temp_out;
}
