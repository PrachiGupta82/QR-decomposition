#include "Q_header.h"

int main()
{
	hls::stream <arr_pkt_in> U_in;
	hls::stream < div_data >div_in;
	hls::stream < arr_pkt_out >Q_out;

	div_data temp_div;
	arr_pkt_in temp_U;
	arr_pkt_in temp_U_arr[8];
	arr_pkt_out temp_Qout;
	typedef std::complex<ap_fixed <40,20> > temp_mul;

	complex_tin arr[13]={{0.1,0.1},{0.2,-0.2},{0.31,0.1},{0.4,-0.2},{0.51,0.1},{0.6,0.1},{0.7,-0.2},{0.8,0.1},{0.93,-0.4},{0.14,0.14},{0.15,0.15},{0.16,0.16},{0.20,0.20}};

	div_in<<3;

	for(int i=0;i<N;i++)
	{
		temp_U.elements[i]=arr[i];
	}
	U_in<<temp_U;
	Q_matrix(U_in,div_in,Q_out);
	Q_out>>temp_Qout;
	cout<<"DISPLAYING OUTPUT"<<endl;
	for(int i=0;i<N;i++)
		{
			cout<<i<<"    "<<temp_Qout.elements[i]<<endl;
		}

	div_in<<2;


	for(int i=7;i<15;i++)
		{
			temp_U.elements[i-7]=arr[i];
		}
		U_in<<temp_U;
		Q_matrix(U_in,div_in,Q_out);
		Q_out>>temp_Qout;
		cout<<"DISPLAYING OUTPUT"<<endl;
		for(int i=0;i<N;i++)
			{
				cout<<i<<"    "<<temp_Qout.elements[i]<<endl;
			}

//	temp_div=0.2;
//	div_in<<temp_div;
//	for(int i=0;i<8;i++)
//	{
//		temp_U=arr[i];
//		U_in<<temp_U;
//		Q_matrix(U_in,div_in,Q_out);
//		Q_out>>temp_Qout;
//		cout<<temp_Qout<<endl;
//	}

}
