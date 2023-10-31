#include "inv_header.h"

void inverse(hls::stream <arr_in> &Q_in,
					hls::stream < arr_in > &R_in,
					hls::stream <in32> &div,
					hls::stream < arr_out >&X_out)
{

#pragma HLS PIPELINE II=1
#pragma HLS data_pack variable=R_in
#pragma HLS data_pack variable=Q_in

#pragma HLS INTERFACE axis register both port=Q_in
#pragma HLS INTERFACE axis register both port=R_in
#pragma HLS INTERFACE axis register both port=div
#pragma HLS INTERFACE axis register both port=X_out

	arr_in temp_Q_in;
	arr_in temp_R_in;
	in32 temp_div[N];
	arr_out temp_X_out;

	static complex_tin Q_temp;
	static complex_tin Q_t[N][N];
	static complex_tin R[N][N];
	static complex_tout X[N][N];
	static complex_tout mem[64];

	static int i=0;
	#pragma HLS RESET variable=i

	static int z=0;
	#pragma HLS RESET variable=z

		static int j=0;
	#pragma HLS RESET variable=j

		static ap_uint<7> num=0;
	#pragma HLS RESET variable=num

	enum state {in_q, in_r, cal};
	static state present_state;
#pragma HLS RESET variable=present_state

	switch(present_state)
	{
	case(in_q):
			{
				if(i<N-1)
				{
					div>>temp_div[i];
					//cout<<"div= "<<temp_div[i]<<endl;
					Q_in>>temp_Q_in;
					for (my_int m=0;m<N;m++)
					{
						Q_temp=temp_Q_in.elements[m];
						Q_t[m][i]=conj(Q_temp);
						X[m][i]=conj(Q_temp);

						//cout<<m<<"---"<<temp_Q_in.elements[m]<<"-----"<<Q_t[i][m]<<endl;
					}

					i=i+1;
					present_state=in_q;
				}
				else
				{
					div>>temp_div[i];
					//cout<<"div= "<<temp_div[i]<<endl;
					Q_in>>temp_Q_in;
					for (my_int m=0;m<N;m++)
					{
						Q_temp=temp_Q_in.elements[m];
						Q_t[m][i]=conj(Q_temp);
						X[m][i]=conj(Q_temp);
					}

					i=0;

					present_state=in_r;
				}
			}
			break;

	case(in_r):{
				if(i<N-1)
					{
						R_in>>temp_R_in;
						for (my_int m=0;m<N;m++)
						{
							R[i][m]=temp_R_in.elements[m];
						}

						i=i+1;
						present_state=in_r;
					}
					else
					{
						R_in>>temp_R_in;
						for (my_int m=0;m<N;m++)
						{
							R[i][m]=temp_R_in.elements[m];
						}

						i=0;
						z=7;
						present_state=cal;
					}
				}
				break;

	case(cal):{

				//for (int z=7;z>=0;z--)
				if(z>=0)
				{
					for(int l=1;l<(8-z);l++)
					{
						for(int n=0;n<8;n++)
							{
								mydata2 mul_real=R[z][z+l].real() * X[z+l][n].real();
								mydata2 mul_real2=R[z][z+l].imag() * X[z+l][n].imag();
								ap_fixed <28,8> real_part = X[z][n].real() - mul_real + mul_real2;
//
								mydata2 mul_imag=R[z][z+l].real() * X[z+l][n].imag();
								mydata2 mul_imag2=R[z][z+l].imag() * X[z+l][n].real();
								ap_fixed <28,8> imag_part = X[z][n].imag() - mul_imag - mul_imag2;

								X[z][n] = complex_tout(real_part, imag_part);
							}
					}


					for(int r=0;r<8;r++)
					{
						ap_fixed <26,6> real_part = X[z][r].real() * temp_div[z];
						ap_fixed <26,6> imag_part = X[z][r].imag() * temp_div[z];
						X[z][r] = complex_tout(real_part, imag_part);
						cout<<"X["<<z<<"]["<<r<<"]="<<X[z][r]<<endl;
						temp_X_out.elements[r]=X[z][r];
						cout<<temp_X_out.elements[r]<<endl;
					}
					X_out<<temp_X_out;

					if(z>0)
					{
						present_state=cal;
						z=z-1;
					}
					else
						present_state=in_q;
				}
//				cout<<"matrix X is"<<endl;
//
//					for(int m=0;m<N;m++)
//					{
//						for(int n=0;n<N;n++)
//						{
//							cout<<X[m][n]<<"    ";
//						}
//						cout<<endl;
//					}

//					cout<<"GOING TO OUTPUT STATE"<<endl;
				//present_state=print;
				}
				break;

/*case(print):{

//		cout<<"matrix X is"<<endl;
		//
		for(int m=0;m<N;m++)
		{
			for(int n=0;n<N;n++)
			{
				cout<<X[m][n]<<"    ";
			}
			cout<<endl;
		}
		present_state=output;
	}
	break;

	case(output):{
					if(i<8)
						{
//							if(j<N-1)
//							{
//
							for(int p=0;p<N;p++)
							{
								temp_X_out.elements[j]=X[i][p];
							}
								X_out<<temp_X_out;
								//j=j+1;
								num=num+1;
								present_state=output;

						}

						else
						{
							for(int p=0;p<N;p++)
							{
								temp_X_out.elements[j]=X[i][p];
							}
								X_out<<temp_X_out;
							num=num+1;
							if(num==64)
							{

								cout<<"GOING IN in q"<<endl;
								i=0;
								j=0;
								num=0;
								present_state=in_q;
							}
							else
							{
								present_state=output;
								i=i+1;
								j=0;
							}
						}


				}
				break;*/
	}



}
