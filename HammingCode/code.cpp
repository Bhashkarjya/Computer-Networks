#include<iostream>
#include<math.h>
using namespace std;
void display(int arr[],int n)
{
	for(int i=0;i<n;i++)
		cout<<arr[i];
}
int calculateParity(int arr[],int n,int m)
{
	int i,sum,c;
	for(i=m-1,c=0,sum=0;i<n;i++)
	{
			if(i==m-1) {sum=0;c++;}
			else 	{sum+=arr[i];c++;}
			if(c==m){c=0;i+=m;}
	}
	if(sum%2==0)return 0;
	else return 1;
}
int checkParity(int arr[],int n,int m)
{
	int i,sum,c;
	for(i=m-1,c=0,sum=0;i<n;i++)
	{
			sum+=arr[i];
			c++;
			if(c==m){c=0;i+=m;}
	}
	if(sum%2==0)return 0;
	else return 1;
}
int main()
{
	int input[1000],bits[2000],sum,flag,n,m,k,i,j,parity[10];
	do
	{
		cout<<"Enter Number of Bits: ";
		cin>>n;
		cout<<endl<<"Enter Bits to Transfer: ";
		for(i=0;i<n;i++)
			cin>>input[i];
		for(i=0,m=0;i<n;i++)
		{
			if((int)pow(2,i)<=n)m++;
			else break;
		}m--;
		cout<<endl<<"You Entered: ";
		display(input,n);															
		for(i=0,k=0;i<n;i++)														
		{
			for(j=0,flag=0;j<=m;j++)
				if(i+1==pow(2,j)){flag=1;bits[i]=7;n++;break;}
			if(flag==0){bits[i]=input[k];k++;}
		}
		for(i=0;i<=m;i++)															
		{
			bits[(int)pow(2,i)-1]=parity[i]=calculateParity(bits,n,(int)pow(2,i));
			cout<<endl<<"P"<<i<<": "<<parity[i];
		}
		cout<<endl<<"Hamming Code Generated: ";
		display(bits,n);
		cout<<endl<<"Enter Error Bit: ";
		cin>>k;
		bits[k-1]=1-bits[k-1];												
		cout<<endl<<"Transmitted Data: ";
		display(bits,n);
		for(sum=0,i=0;i<=m;i++)													
		{
			parity[i]=checkParity(bits,n,(int)pow(2,i));
			cout<<endl<<"P"<<i<<": "<<parity[i];
			if(parity[i])sum+=(int)pow(2,i);
		}
		cout<<endl<<endl<<"Error Found at Bit Position "<<sum;
		bits[sum-1]=1-bits[sum-1];												
		cout<<endl<<endl<<"Corrected Data: ";
		display(bits,n);
		cout<<endl<<endl<<"Actual Message: ";
		for(i=0,j=0;i<n;i++)														
			if((i!=(((int)pow(2,j))-1)) || (j>m))cout<<bits[i];
			else j++;
		cout<<endl<<"Continue?  1: Yes   0: No"<<endl<<"Enter Choice: ";
		cin>>i;
	}while(i);
	return 0;
}