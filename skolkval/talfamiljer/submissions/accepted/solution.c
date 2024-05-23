#include <stdio.h>
#define MAX 1000000

int main() {
  int N,i,j,k,p[10],n[100];
  int mask[MAX];
  scanf("%d", &N);
  for(i=0;i<N;i++) scanf("%d", &n[i]);
  for(i=1;i<MAX;i++) mask[i]=0;   //Nollställ de binära talen: inga delbarheter registrerade
  for(i=1;i<MAX;i++) {   //Loopa över alla tal i
    
    //Räkna antal förekomster av varje siffra i talet i
    k=i;
    for(j=0;j<10;j++) p[j]=0;
    while (k>0) {p[k%10]++; k/=10; }

    //Bygg nu upp talet k med siffrorna i storleksordning men första siffran får inte vara 0
    for(j=1;j<10;j++) if(p[j]>0) {k=j; p[j]--; break; }
    for(j=0;j<10;j++) while (p[j]>0) {k=10*k+j; p[j]--; }
    
    for(j=0;j<N;j++) if(i%n[j]==0) mask[k]|=(1<<j);   //Loopa över småtalen och registrera eventuella delbarheter på talet k
  }
  for(i=1;i<MAX;i++) if(mask[i]==(1<<N)-1) break;    //Hitta första talet som har fått registrerat delbarhet med samtliga småtal (d.v.s. mask=2^N-1)
  printf("%d\n", i); 
  return 0;
}
