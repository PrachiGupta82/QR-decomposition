#include "header.h"
out_type temp;

int main()
{
	hls::stream < in_type >in;
	hls::stream < out_type >out;
	in<<1.44;
	div(in,out);
	out>>temp;
	cout<<temp<<endl;

	in<<3.45;
	div(in,out);
	out>>temp;
	cout<<temp<<endl;

	in<<2.22;
	div(in,out);
	out>>temp;
	cout<<temp<<endl;


}
