#include "controller_header.h"

int main()
{
hls::stream <complex_tin> U_in;
hls::stream < mydata > R_in;
hls::stream <arr_in> Q_in;
hls::stream <arr_out > U_out;
hls::stream <arr_out_r> R_out;
//hls::stream <my_int > ps;                //----

complex_tin temp_in;
mydata temp_R_in;
arr_out temp_U_out_tb;
arr_in temp_Q_in;
arr_out_r temp_R_out;
my_int ps_temp;

complex_tin arr[74]={{0.2678, -0.4882}, {-0.5998, 0.2345}, {-0.0087, -0.1907}, {-0.7017, -0.3451}, {0.4566, 0.2486}, {0.7155, -0.6986}, {0.0323, -0.5136}, {0.7070, 0.1338},
	        {-0.1562, -0.1630}, {-0.3559, 0.1913}, {0.4171, -0.4512}, {0.3648, -0.1153}, {0.1147, 0.0585}, {0.3179, 0.0915}, {-0.6028, 0.5314}, {0.2227, -0.4093},
	        {-0.1982, 0.4953}, {-0.2461, -0.3109}, {0.3214, -0.0154}, {0.0000, 0.0716}, {-0.4739, 0.2961}, {0.0007, 0.5708}, {0.4755, 0.2164}, {0.4489, -0.1725},
	        {0.7294, 0.4534}, {0.2686, -0.1022}, {0.6035, -0.2399}, {-0.0300, 0.6618}, {-0.3887, 0.2489}, {-0.0432, 0.2529}, {0.4746, -0.1849}, {-0.0691, 0.1241},
	        {-0.6909, -0.6570}, {-0.5432, -0.7242}, {0.5843, 0.6750}, {0.6049, -0.1230}, {0.5777, -0.4811}, {-0.6582, -0.4627}, {0.3325, -0.4620}, {-0.1010, -0.3710},
	        {0.5757, -0.1506}, {0.3307, 0.7235}, {-0.2479, 0.6283}, {0.1642, 0.7220}, {-0.7045, -0.5560}, {0.2720, -0.1959}, {-0.5233, -0.1072}, {0.4862, -0.3132},
	        {0.6177, 0.0402}, {-0.5878, -0.4975}, {0.2971, -0.6686}, {0.1759, -0.2968}, {-0.0151, 0.7460}, {-0.6839, -0.0587}, {0.2386, -0.0269}, {-0.6226, 0.1750},
	        {0.4427, -0.1244}, {0.2298, -0.5886}, {-0.4517, 0.3555}, {0.5373, 0.3006}, {-0.4963, -0.4916}, {-0.6406, 0.7199}, {0.0278, -0.5671}, {-0.5483, -0.3508},
			{0.5757, -0.1506}, {0.3307, 0.7235}, {-0.2479, 0.6283},{0.4427, -0.1244}, {0.2298, -0.5886},{-0.1562, -0.1630}, {-0.3559, 0.1913}, {0.4171, -0.4512}, {0.3648, -0.1153},{0.4489, -0.1725}};

mydata arr2[8]={0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8};

for (int m=0;m<64;m++)
{
	U_in<<arr[m];
	controller_src(U_in,R_in,Q_in,U_out,R_out);
	//cout<<ps_temp<<endl;
}

controller_src(U_in,R_in,Q_in,U_out,R_out);
//cout<<ps_temp<<endl;
U_out>>temp_U_out_tb;
//R_out>>temp_R_out;
//cout<<"R-----"<<temp_R_out<<endl;
for(int m=0;m<N;m++)
{
cout<<m<<"---"<<temp_U_out_tb.elements[m]<<endl;
}

R_in<<0.2;
controller_src(U_in,R_in,Q_in,U_out,R_out);
//cout<<ps_temp<<endl;

for(int m=0;m<N;m++)
{
	temp_Q_in.elements[m]=arr[m];
	//controller_src(U_in,R_in,Q_in,U_out,R_out);
}
Q_in<<temp_Q_in;
controller_src(U_in,R_in,Q_in,U_out,R_out);

//controller_src(U_in,R_in,Q_in,U_out,R_out);


for(int n=0;n<6;n++)
{
	for(int m=0;m<1;m++)
	{
	controller_src(U_in,R_in,Q_in,U_out,R_out);
	}

	controller_src(U_in,R_in,Q_in,U_out,R_out);
	U_out>>temp_U_out_tb;

	for(int m=0;m<N;m++)
	{
	cout<<m<<"---"<<temp_U_out_tb.elements[m]<<endl;
	}

	R_in<<arr2[n];
	controller_src(U_in,R_in,Q_in,U_out,R_out);

	for(int m=32;m<40;m++)
	{
		temp_Q_in.elements[m-32]=arr[m];
		//controller_src(U_in,R_in,Q_in,U_out,R_out);
	}
	Q_in<<temp_Q_in;
	controller_src(U_in,R_in,Q_in,U_out,R_out);
}

for(int m=0;m<1;m++)
{
controller_src(U_in,R_in,Q_in,U_out,R_out);
}

controller_src(U_in,R_in,Q_in,U_out,R_out);
U_out>>temp_U_out_tb;

for(int m=0;m<N;m++)
{
cout<<m<<"---"<<temp_U_out_tb.elements[m]<<endl;
}

R_in<<0.8;
controller_src(U_in,R_in,Q_in,U_out,R_out);



for(my_int m=0;m<N;m++)
{
	controller_src(U_in,R_in,Q_in,U_out,R_out);
	R_out>>temp_R_out;
	for(int p=0;p<N;p++)
		cout<<p<<"---"<<temp_R_out.elements[p]<<"   ";
	cout<<endl;
}

for (int m=0;m<2;m++)
{
	U_in<<arr[m];
	controller_src(U_in,R_in,Q_in,U_out,R_out);
}
//controller_src(U_in,R_in,Q_in,U_out,R_out);
//controller_src(U_in,R_in,Q_in,U_out,R_out);

//for(int m=0;m<2;m++)
//{
//controller_src(U_in,R_in,Q_in,U_out,R_out);
//}
}
