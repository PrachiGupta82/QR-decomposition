#include "header.h"
ap_fixed<24,4> temp;

int main()
{
	hls::stream < in_type >in;
	hls::stream < out_type >out;
	in<<1.44;
	sq_root(in,out);
	out>>temp;
	cout<<temp<<endl;

	in<<3.45;
	sq_root(in,out);
	out>>temp;
	cout<<temp<<endl;

	in<<9;
	sq_root(in,out);
	out>>temp;
	cout<<temp<<endl;


}
