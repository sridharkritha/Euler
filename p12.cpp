#include <iostream>
#include <bitset>
#define SIZE 10000000
#define MAX (int)(SIZE-3)/2
#define MAX_2(x, y) (((x) > (y)) ? (x) : (y))
using namespace std;

int primes[MAX+1]; //array that stores the primes up to sqrt(SIZE)
bitset<MAX+1> bset; //auxiliary bitset used to make the sieve

void Sieve_GeneratePrimes()
{
	int i,j;
	for(i=0;i*i<=SIZE;i++) //we only have to get primes up to sqrt(SIZE)
		if(!bset.test(i))
			for(j=i+1;(2*j+1)*(2*i+3)<=SIZE;j++)
				bset.set(((2*j+1)*(2*i+3)-3)/2); //setting all non-primes
	primes[0]=2; //store the first prime (that is 2)
	for(i=1,j=0;j<MAX+1;j++)
		if(!bset.test(j))
			primes[i++]=2*j+3; //store the remaining odd primes
}

/* Miller-Rabin primality test, iteration signifies the accuracy of the test */
/* This function calculates (ab)%c */
int modulo(int a,int b,int c){
	long long x=1,y=a; // long long is taken to avoid overflow of intermediate results
	while(b > 0){
		if(b%2 == 1){
			x=(x*y)%c;
		}
		y = (y*y)%c; // squaring the base
		b /= 2;
	}
	return x%c;
}
/* this function calculates (a*b)%c taking into account that a*b might overflow */
long long mulmod(long long a,long long b,long long c){
	long long x = 0,y=a%c;
	while(b > 0){
		if(b%2 == 1){
			x = (x+y)%c;
		}
		y = (y*2)%c;
		b /= 2;
	}
	return x%c;
}

bool Miller(long long p,int iteration){
	if(p<2){
		return false;
	}
	if(p!=2 && p%2==0){
		return false;
	}
	long long s=p-1;
	while(s%2==0){
		s/=2;
	}
	for(int i=0;i<iteration;i++){
		long long a=rand()%(p-1)+1,temp=s;
		long long mod=modulo(a,temp,p);
		while(temp!=p-1 && mod!=1 && mod!=p-1){
			mod=mulmod(mod,mod,p);
			temp *= 2;
		}
		if(mod!=p-1 && temp%2==0){
			return false;
		}
	}
	return true;
}


int main() {
	int n=1, a =0, b=0,i=0,aCount=0,bCount=0,nFactor=0, pow =1;
	bool flag=true;
	Sieve_GeneratePrimes();

	while(true) {
		//n = 2160;
		// Making 'a' is always less than 'b'
		if(0==n%2) {
			a = (n/2);
			b = n + 1;

		}
		else {
			a = (n+1)/2;
			b = n ;
		}

		if(!Miller(a,5)) {
			// 'a' is not a prime
			while(true) {
				if(a%primes[i]==0) {
					a = a/primes[i];
					aCount++;
				}
				else {
					if(a>=primes[i+1]){
						++i;
						pow = pow * (aCount+1);
						aCount =0;
					}

					else {
						pow = pow * (aCount+1);
						aCount =0;
						break;
					}

				}
			}
		}
		else {
			++aCount;
			pow = pow * (aCount+1);
		}

		i = 0;
		if(!Miller(b,5)) {
			// 'b' is not a prime
			while(true) {
				if(b%primes[i]==0) {
					b = b/primes[i];
					bCount++;
				}
				else {
					if(b>=primes[i+1]) {
						++i;
						pow = pow * (bCount+1);
						bCount =0;
					}
					else
					{
						pow = pow * (bCount+1);
						bCount =0;
						break;
					}
				}
			}
		}
		else {
			++bCount;
			pow = pow * (bCount+1);
		}
		nFactor = pow; //(aCount+1) * (bCount+1);
		if(nFactor > 500)
		{
			std::cout<<(n/2)*(n+1);
			break;
		}
		++n;
		aCount = bCount = nFactor = 0;
		pow = 1;
	}

	return 0;
}
