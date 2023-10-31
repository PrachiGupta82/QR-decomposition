#include "dot_header.h"

int main()
{
	hls::stream < arr_pkt_in >in;
	hls::stream < my_data > out;
	arr_pkt_in temp_in;
	my_data temp_out;

	complex_tin arr[8]={{0.7294, 0.4534}, {0.2686, -0.1022}, {0.6035, -0.2399}, {-0.0300, 0.6618}, {-0.3887, 0.2489}, {-0.0432, 0.2529}, {0.4746, -0.1849}, {-0.0691, 0.1241}};

	for(int i=0;i<N;i++)
	{
		temp_in.elements[i]=arr[i];
	}

	in<<temp_in;
	dot_prod(in,out);
	out>>temp_out;
	cout<<"out"<<temp_out<<endl;

}

