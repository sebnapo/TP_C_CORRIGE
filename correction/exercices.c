#include <stdio.h>
#include <math.h>

void Iteratif(double a)
{
	double val[2];
	int i=0;

	val[i]=1;
	do
	{
		i=1-i;
		val[i]=0.5*(val[1-i]+a/val[1-i]);
	} while (fabs(val[0]-val[1])>0.0001);
	printf("sqrt(%f)=%f\n",a,val[i]);
}

double _Recursif(double a,double xn)
{
	double xn1=0.5*(xn+a/xn);
	if (fabs(xn1-xn)>0.0001) return(_Recursif(a,xn1));
	return(xn1);
}

void Recursif(double a)
{
	printf("sqrt(%f)=%f\n",a,_Recursif(a,1));
}

void Q1()
{
	printf("Itératif 36 et 456\n");
	Iteratif(36);
	Iteratif(456);

	printf("\nRécursif 81 et 654\n");
	Recursif(81);
	Recursif(654);
}

int conv2(int n)
{
	printf("%d en base 2 = ",n);
	while(n>0)
	{
		printf("%d",n%2);
		n/=2;
	}
	printf("\n");
}

int convB(int n,int B)
{
	printf("%d en base %d = ",n,B);
	while(n>0)
	{
		printf("%d",n%B);
		n/=B;
	}
	printf("\n");
}

void Q2()
{
	conv2(4);
	convB(10,8);
}

int main()
{
	printf("==================================\n=== Q1\n");
	Q1();

	printf("\n==================================\n=== Q2\n");
	Q2();

	return(0);
}
