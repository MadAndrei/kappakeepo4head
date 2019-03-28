#include<stdio.h>
#include<float.h>
#include<math.h>

#define cabs(n) ( (n)<0?(-(n)):(n) )

int main(){
	double d;
	scanf("%lf",&d);
	int a = (int)d;
	printf("%d\n",a);
	
	double tmp = d - a;
	int n = 0;
	double c = tmp;
	double E = 0.000000009;
	while(cabs((c-(int)c)-round(c-(int)c))>E){
		n++;
		c*=10;
		E*=10;
	}
	printf("%.*lf",n,tmp);
	return 0;
}
