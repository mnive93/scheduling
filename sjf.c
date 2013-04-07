#include<stdio.h>

#include<stdlib.h>

struct schedule

{

int at,bt,pid,st,et,wt,rt,tat,rem;

int finished,count;

}p[100],fin[100];



void gantt(struct schedule p[10],int n)
{
	int i,j,count=0;
	printf("\n-----------------------------------------------------------------------\n|");	
	for(i=0;i<n;i++)
	{
		count += p[i].rem;
		for(j=0;j<=count;j++)
			printf("_");
		printf("%d|",p[i].pid);
	}
	count=0;
	printf("\n0");
	for(i=0;i<n;i++)
	{
		count += p[i].rem;
		for(j=0;j<=count;j++)
			printf(" ");
		printf("%d",p[i].et);
	}
	printf("\n------------------------------------------------------------------------------");
}

void display(struct schedule p1[100],int n)

{
float avgwt,avgtat;
int totw=0,totat=0;

int i;

printf("\n---------------------------------------------------------\n");

printf("\npid|\tat|\tbt|\tst|\tet|\twt|\trt|\ttat\n");

printf("---------------------------------------------------------\n");

for(i=0;i<n;i++)

{

printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p1[i].pid,p1[i].at,p1[i].bt,p1[i].st,p1[i].et,p1[i].wt,p1[i].rt,p1[i].tat);
totw+=p1[i].wt;
totat+=p1[i].tat;
}

printf("----------------------------------------------------------\n");
printf("%d %d\n",totw,totat);
avgwt=(float)totw/n;
avgtat=(float)totat/n;
printf("AVERAGE WAITING TIME IS : %f\n",avgwt);
printf("AVERAGE TURN AROUND TIME IS:%f\n",avgtat);

}

void sort (int n,int choice)

{

    struct schedule s;

	int i,j,result;

for(i=0;i<n;i++)

{

for(j=0;j<n;j++)

{

if(choice==1)

{

result=(p[i].at <  p[j].at);

}

else if(choice==2)

result=(p[i].bt <  p[j].bt);

if(result)

{

//printf("here\n");

s=p[i];

p[i]=p[j];

p[j]=s;

}

}

}





}

void calc(int n)

{

int flag=0;

int i;

for(i=0;i<n;i++)

{

if(flag==0)

{

p[i].st=p[i].at;

p[i].et=p[i].st+p[i].bt;

p[i].wt=p[i].st-p[i].at;

p[i].rt=p[i].wt;

p[i].tat=p[i].et-p[i].at;

flag=1;

}

else

{

p[i].st=p[i-1].et;

if(p[i].st<p[i].at)

p[i].st=p[i].at;

p[i].et=p[i].st+p[i].bt;

p[i].wt=p[i].st-p[i].at;

p[i].rt=p[i].wt;

p[i].tat=p[i].et-p[i].at;



}

}

}





void fcfs(int n)

{



sort(n,1);

calc(n);

}



void nsjf(int n)

{

struct schedule temp;

int i,j;

int min,count=0;

for(i=0;i<n;i++)

if(p[i].at==0)

count++;

if(count!=n)

{

sort(n,1);

min=p[0].bt+p[0].at;

printf("%d\n",min);

for(i=1;i<n;i++)

{

if(i!=1)

{

for(j=i-1;j<i;j++)

{

if(p[j].at <= min && p[i].bt <  p[j].bt  )

{

temp=p[i];

p[i]=p[j];

p[j]=temp;

min+=p[i].bt;

//printf("%d\n",min);

}

}

}

}

}

else

sort(n,2);

calc(n);

}     

int small(int n,int start,int arr)

{

int index=-1,i;

//min=p[start].at+p[start].bt

for(i=0;i<n;i++)

{

if(p[i].finished!=1)

{

if(p[i].rem  < fin[start].rem && p[i].at < arr && p[i].rem >0 &&p[i].pid!=fin[start].pid )

{
arr=p[i].at;
index=i;

}

}

}

return index;

}

int find(int value,int n)

{

int i;

for(i=0;i<n;i++)

{

if(fin[value].pid==p[i].pid )

{

return i;

}

}

}

int load(int n,int arr,int pro)

{

int i,max=999,pos=-1,flag=0;

for(i=0;i<n;i++)

{
                if(p[i].at > arr && p[i].finished!=1&& flag==0)
                {arr=p[i].at;}

if(p[i].finished!=1 && p[i].rem < max &&p[i].at<=arr )

{
flag=1;
max=p[i].rem;

pos=i;

}

}

return pos;

}

int find_calc(int temp,int pos)

{

    int i;

for(i=0;i<temp;i++)

{

    if(fin[pos].pid==fin[i].pid)

{

    return i;

    break;

}

}

}

void psjf(int n)

{

int res;

int i,index,pro;

int temp=0,pos,prev;

int max=0,value=0;

int cnt=0,flag=0;

sort(n,1);
//for(i=0;i<n;i++)
//printf("%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt);
for(i=0;i<n;i++)

{

p[i].rem=p[i].bt;

value+=p[i].bt;

p[i].count=0;

p[i].finished=0;

p[i].tat=0;

}

res=temp;

max+=p[0].bt+p[0].at;

fin[0]=p[0];

while(max<=value)

{

    //        printf("%d temp\n",temp);

//printf("here in while\n");

index=small(n,temp,max);

if(index==-1 )

{

res=temp;

pro=find(temp,n);

//printf("%d pos\n",pro);

p[pro].finished=1;

if(flag==0)

{

  //         printf("in flag\n");

max=0;           }

flag=1;

max+=p[pro].rem;

fin[temp]=p[pro];
if(fin[temp-1].et<fin[temp].at)
fin[temp].st=fin[temp].at;
else

fin[temp].st=fin[temp-1].et;

//printf("%d rem\n",p[pro].rem);

//printf("%d count\n",p[pro].count);

if(p[pro].count==1)

{

prev=find_calc(temp,temp);

fin[temp].et=fin[temp].st+p[pro].rem;

fin[temp].wt=fin[temp].st+fin[prev].wt-fin[prev].et;

}

else

{

fin[temp].et=fin[temp].st+fin[temp].bt;

fin[temp].wt=fin[temp].st-fin[temp].at;

}

p[pro].count=0;

p[pro].rem=0;

fin[temp].rem=0;

fin[temp].tat=fin[temp].et-fin[temp].at;

//printf("%d %d fini\npid\n",fin[pro].finished,fin[pro].pid);

pos=load(n,max,pro);

if(pos==-1)

break;

else

{

fin[res+1]=p[pos];

fin[res+1].st=fin[temp].et;

}

//printf("%d id",fin[res+1].pid);

}

else if(index!=-1)

{

     

//    printf("in else index is %d\n",index);

res=temp;

fin[res+1]=p[index];

pos=find(temp,n);

if(flag==0)

{

      //     printf("in flag\n");

           max=0;

           max+=p[index].at;

}

//printf("max %d\n",max);

flag=1;




p[pos].count=1;

p[pos].rem=p[pos].rem-max;
fin[temp]=p[pos];
//printf("%d rem\n",fin[temp].rem);

fin[temp].et=max;

fin[temp].wt=fin[temp].st-fin[temp].at;

fin[res+1].st=fin[temp].et;

}

temp+=1;

}
int totwt=0,totat=0;
float avgwt,avgtat;
gantt(fin,temp+1);

printf("\n---------------------------------------------------------\n");

printf("\npid|\tat|\tbt|\tst|\tet|\twt|\tremt|\ttat\n");

printf("---------------------------------------------------------\n");

for(i=0;i<temp+1;i++)

{

printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",fin[i].pid,fin[i].at,fin[i].bt,fin[i].st,fin[i].et,fin[i].wt,fin[i].rem,fin[i].tat);
totwt+=fin[i].wt;
totat+=fin[i].tat;
}

printf("----------------------------------------------------------\n");
//printf("%d %d\n",avgwt,avgtat);
avgwt= (float)totwt/(temp+1);
avgtat=(float)totat/(temp+1);
printf("AVERAGE WAITING TIME IS : %f\n",avgwt);
printf("AVERAGE TURN AROUND TIME IS:%f\n",avgtat);



}



int main()

{



int ch,i,n;

printf("enter the number of processes\n");

scanf("%d",&n);

for(i=0;i<n;i++)

{

printf("enter process id\n");

scanf("%d",&p[i].pid);

printf("enter the arrival time\n");

scanf("%d",&p[i].at);

printf("enter the service time\n");

scanf("%d",&p[i].bt);

}

do

{

printf("1.fcfs \n2.sjf non-premptive\n3.sjf premptive\n");

printf("enter choice\n");

scanf("%d",&ch);

if(ch==1)

{

fcfs(n);

gantt(p,n);

display(p,n);

}

if(ch==2)

{

nsjf(n);

gantt(p,n);

display(p,n);

}

if(ch==3)

{

         psjf(n);

         }

}while(ch!=4);

return 0;

}


