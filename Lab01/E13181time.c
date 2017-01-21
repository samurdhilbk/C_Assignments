#include <stdio.h>	//import standard I/O library
#include <stdlib.h>	//import standard library

int main(){

int t1,t2;	//define the time variables
printf("Enter the start time: ");	//prompt for first input
scanf("%d",&t1);	//accept first input
printf("Enter the duration: ");		//prompt for second input
scanf("%d",&t2);	//accept second input
int T1,T2,ans1,ans2;	//accept intermediate variables
T1=t1%100+(t1-t1%100)/100*60;		//convert t1 to minutes
T2=t2%100+(t2-t2%100)/100*60;		//convert t1 to minutes
ans1=((T1+T2)%1440)/60;		//add the times and get the number of hours
ans2=((T1+T2)%1440)%60;		//add the times and get the number of minutes
if(ans2<10 && ans1<10) printf("End time is 0%d0%d.\n",ans1,ans2);	//pad both with 0
else if(ans1<10) printf("End time is 0%d%d.\n",ans1,ans2);	//pad ans1 with 0
else if(ans2<10) printf("End time is %d0%d.\n",ans1,ans2);	//pad ans2 with 0
else printf("End time is %d%d.\n",ans1,ans2);	//output with no padding
}
