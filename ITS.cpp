#include<iostream>
#include<math.h>
#include<iomanip> 
#include<string.h>
using namespace std;
int main()
{
int n;
cout<<"\nEnter the number of subjects: ";
cin>>n;
int bt[n],p[n],s[n],wt[n],tat[n],ts,its[n],tq[n][n],rbt[n],ord[n];//burst time,priority,shortness 
component,waiting time,turnaround time,time slice(original),time quantum,round burst 
time,order
string subjects[n];
string abc;
for(int i=0; i<n; i++)
{
wt[i]=tat[i]=0;
s[i]=1;//initializing shortness component for all processes as 1, that is, the difference 
between the burst time of the current process and its previous process is positive.
for(int j=0; j<n; j++)
tq[i][j]=0;
}
for(int i=0; i<n; i++)
{
cout<<"\nEnter name of subject "<<i+1<<": ";
cin>>subjects[i];
cout<<"\nEnter duration of "<<subjects[i]<<": ";
cin>>bt[i];
cout<<"\nEnter the total credit for "<<subjects[i]<<": ";
cin>>p[i]; 
p[i]=5-p[i];
}
cout<<"\nEnter the minimum time period of a class: ";
cin>>ts;
int flag=0,j=0;
//sorting based on burst time
for(int i=0; i<n-1; i++)
for(int j=0; j<n-1; j++)
if(bt[j]>bt[j+1])
{
int t=bt[j];
bt[j]=bt[j+1];
bt[j+1]=t;
t=p[j];
p[j]=p[j+1];
p[j+1]=t;
abc=subjects[j];
subjects[j]=subjects[j+1];
subjects[j+1]=abc;
}
//sorting based on priority
for(int i=0; i<n; i++)
p[i]+=i;
for(int i=0; i<n-1; i++)
for(int j=0; j<n-1; j++)
if(p[j]>p[j+1])
{
int t=bt[j];
bt[j]=bt[j+1]; 
bt[j+1]=t;
t=p[j];
p[j]=p[j+1];
p[j+1]=t;
abc=subjects[j];
subjects[j]=subjects[j+1];
subjects[j+1]=abc;
}
for(int i=0; i<n; i++)
rbt[i]=bt[i];
while(!flag)
{
for(int i=0; i<n; i++)
{
if(p[i]>0.67*n) p[i]=0;
else if(p[i]>0.33*n) p[i]=1;
else p[i]=2;
if(i!=0)
if((bt[i]-bt[i-1])>0)
s[i]=0;//shortness component=0 if the (Burst Time)i>(Burst Time)i-1 and shortness 
component=1 if the (Burst Time)i<=(Burst Time)i-1
its[i]=ts+bt[i]+s[i]+p[i];
if(j==0)
{
if(s[i]==1) 
tq[j][i]=its[i];
else
tq[j][i]=ceil(0.5*(float)its[i]);
if(rbt[i]<tq[j][i])
tq[j][i]=rbt[i];
rbt[i]=rbt[i]-tq[j][i];
}
else
{
if(rbt[i]<=0)
tq[j][i]=0;
else if(s[i]==1)
tq[j][i]=2*tq[j-1][i];
else
tq[j][i]=1.5*tq[j-1][i];
if(rbt[i]<tq[j][i])
tq[j][i]=rbt[i];
rbt[i]=rbt[i]-tq[j][i];
}
}
j++;
flag=-1;
for(int i=0; i<n; i++)
if(rbt[i]>0) 
flag=0;
}
cout<<"\n\nOrder of subjects:\n";
for(int i=0; i<n; i++)
cout<<subjects[i]<<" ";
cout<<"\n\nDuration of the classes:\n";
for(int i=0; i<n; i++)
cout<<bt[i]<<" ";;
cout<<"\n\nIntelligent Time Slices for the subjects:\n";
for(int i=0; i<n; i++)
cout<<setw(5)<<its[i];
/*cout<<"\n\nDynamic Time Quantums for the processes:\n";
for(int x=0; x<j; x++)
{
cout<<"Round "<<x+1<<": "<<endl;
for(int y=0; y<n; y++)
cout<<setw(5)<<tq[x][y];
cout<<endl;
}*/
for(int x=0; x<n; x++)
{
flag=-1;
for(int y=0; y<j; y++)
{ 
for(int z=0; z<n; z++)
{
if(z!=x)
wt[x]+=tq[y][z];
else if(z==x&&tq[y+1][z]==0)
{
flag=0;
break;
}
}
tat[x]+=tq[y][x];
if(flag==0)
break;
}
tat[x]+=wt[x];
}
cout<<"\nWaiting time for the subjects(from 0 minutes):\n";
for(int i=0; i<n; i++)
cout<<setw(5)<<wt[i];
cout<<endl;
cout<<"\n\nTime taken to complete each subject(from the completion of 1st subject to 
last subject):\n";
for(int i=0; i<n; i++)
cout<<setw(5)<<tat[i];
float avwt=0,avtat=0;
for(int i=0; i<n; i++) 
{
avwt+=wt[i];
avtat+=tat[i];
}
cout<<"\nTotal time spent in a day to complete the subjects: "<<tat[n-1]<<" minutes 
"<<endl;
avwt/=n;
avtat/=n;
cout<<"\n\nAverage waiting time: "<<avwt<<" minutes"<<endl;
cout<<"\nAverage time spent to finish classes: "<<avtat<<" minutes"<<endl;
}
