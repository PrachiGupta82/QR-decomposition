#include "controller_header.h"

typedef std::complex < ap_fixed <42,4> > dot_arr;

dot_arr dot_prod2(arr_in Qf,complex_tin Uf[8]);


typedef std::complex < ap_fixed <26,6> > arr2;
typedef ap_fixed <40,20> arr3;                                       //div
typedef std::complex<ap_fixed <40,10> > complex_t;

void controller_src(hls::stream <complex_tin> &U_in,
					hls::stream < mydata > &R_in,
					hls::stream <arr_in> &Q_in,
					hls::stream <arr_out >&U_out,
					hls::stream <arr_out_r> &R_out)
{

#pragma HLS PIPELINE II=1
#pragma HLS data_pack variable=U_in
#pragma HLS data_pack variable=R_out
#pragma HLS data_pack variable=Q_in
#pragma HLS data_pack variable=U_out
#pragma HLS INTERFACE axis register both port=U_in
#pragma HLS INTERFACE axis register both port=R_in
#pragma HLS INTERFACE axis register both port=Q_in
#pragma HLS INTERFACE axis register both port=U_out
#pragma HLS INTERFACE axis register both port=R_out



	complex_tin temp_in;
	mydata temp_R_in;
	arr_out temp_U_out;
	arr_out_r temp_R_out;

	static complex_tin U[N][N];
	static complex_tout R[N][N];
	static arr_in temp_Q_in;

	complex_tin vect[8];

	static int i=0;
	#pragma HLS RESET variable=i

		static int j=0;
	#pragma HLS RESET variable=j

		static ap_uint<7> num=0;
		#pragma HLS RESET variable=num

		ap_uint <4> m;

		enum state {input, send_u, receive_r, receive_q, mat_r, output};
		static state present_state;
	#pragma HLS RESET variable=present_state
		//cout<<"-------------------"<<present_state<<endl;
		//ps<<present_state;
		switch(present_state)
		{

		case(input):{
			if(i<N)
				{
					if(j<N-1)
					{
						U_in>>temp_in;
						U[i][j]=temp_in;
						j=j+1;
						num=num+1;
						present_state=input;

					}

					else
					{
						U_in>>temp_in;
						U[i][j]=temp_in;
						num=num+1;
						if(num==64)
						{
							i=0;
							j=0;
							num=0;
							present_state=send_u;
						}
						else
						{
							present_state=input;
							i=i+1;
							j=0;
						}
					}
				}

			else
				present_state=input;


					}
					break;
		case(send_u):{
						for(my_int m=0;m<N;m++)
						{
							temp_U_out.elements[m]=U[m][i];
							//cout<<"U["<<m<<"]["<<i<<"]"<<temp_U_out.elements[m]<<endl;
						}
						U_out<<temp_U_out;
						present_state=receive_r;

					}
					break;
		case(receive_r):{

						R_in>>temp_R_in;
						R[i][i]=temp_R_in;

						if(i<N-1)
							present_state=receive_q;

						else
						{
							i=0;
							present_state=output;
						}


					}
					break;
		case(receive_q):{

						Q_in>>temp_Q_in;
						present_state=mat_r;
					}
					break;
		case(mat_r):{
					//cout<<"in mat_R"<<endl;
					for(int l=i+1;l<N;l++)
						{
							for(my_int m=0;m<8;m++)
							{
								//vect1[m]=Q[m][k];
								vect[m]=U[m][l];
							}
							R[i][l]=dot_prod2(temp_Q_in,vect);
							//cout<<"R["<<i<<"]["<<l<<"]="<<R[i][l];
							//cout<<endl;
							for(my_int m=0;m<8;m++)
							{
								arr3 real_part = U[m][l].real() - (R[i][l].real() * temp_Q_in.elements[m].real()) + (R[i][l].imag() * temp_Q_in.elements[m].imag());
								arr3 imag_part = U[m][l].imag() - (R[i][l].real() * temp_Q_in.elements[m].imag()) - (R[i][l].imag() * temp_Q_in.elements[m].real());
								U[m][l] = complex_tout(real_part, imag_part);
							}
						}
					i=i+1;
					present_state=send_u;

					}
					break;
		case(output):{
					//cout<<"IN OUTPUT*********************************"<<i<<endl;
						if(i<N-1)
						{
							for(my_int m=0;m<N;m++)
								temp_R_out.elements[m]=R[i][m];
							R_out<<temp_R_out;
							i=i+1;
							present_state=output;
						}

						else
						{
							//cout<<"in else of output  -- "<<i<<endl;
							for(my_int m=0;m<N;m++)
								temp_R_out.elements[m]=R[i][m];
							R_out<<temp_R_out;
							i=0;
							present_state=input;
						}


					}
					break;

		}

}

dot_arr dot_prod2(arr_in Qf,complex_tin Uf[8])
	{
#pragma HLS PIPELINE II=1
	dot_arr result(0.0, 0.0);
		for (my_int m = 0; m < N; m++)
		{
			//cout<<"in"<< Qf[i]<< Uf[i] <<endl;
			complex_tout U_cast(Uf[m].real(), Uf[m].imag());
			result += std::conj(Qf.elements[m]) * U_cast;

		}
		return result;
	}

//dot_arr controller_src(arr_in Qf,complex_tin Uf[8])
//	{
////#pragma HLS PIPELINE II=1
//	dot_arr result(0.0, 0.0);
//		for (my_int m = 0; m < N; m++)
//		{
//			//cout<<"in"<< Qf[i]<< Uf[i] <<endl;
//			complex_tout U_cast(Uf[m].real(), Uf[m].imag());
//			result += std::conj(Qf.elements[m]) * U_cast;
//
//		}
//		return result;
//	}


