#include <iostream>
#include<cmath>

using namespace std;

long double factorial(int num)
{
	if ((num == 1)||(num==0)) //基本情况返回1;
		return 1;
	else
		return num * factorial(num - 1);
}
long double combination(int N1, int N2)
{
	return factorial(N1)/( factorial(N2)*factorial(N1-N2) );
}

double Calculatep(int NIs,int NIp,int NIa,int epsilon_c) {
	double p;
	double exponent=1.00/(epsilon_c+10.00*NIs+NIp+NIa);
	p=exp(-exponent);
	return p;
}

double Calculateq(double p,int NI,int NT,int N) {
	double q=0.00;
	int sub=max(1,N-(NT-1-NI)); //1
	int sup=min(N,NI); //6
	for (int i=sub;i<=sup;i++)
	{
		double a=combination(NT-NI-1,N-i);  
		double b=combination(NI,i);
		double c=combination(NT,N);
		double SumUp;
		for (int j=1; j<=i;j++)
		{
			SumUp=SumUp+p*pow(1-p,j);
		}
		q=q+((a*b)/c)*SumUp;
	}
	return q;
	cout<<q<<endl;
}

double CalculatePW(int TNIp,int TNIa,int TNIs,int NS,int NW,int epsilon_cw) {
	double PW;
	PW=0.005;
	return PW;
	
}