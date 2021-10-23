#include <cmath>
#include <iostream>
#include <iomanip>
#include <cassert>
using namespace std;

#define MAXN 15

double dst(double dx, double dy) { return sqrt(dx*dx+dy*dy); }

int N;
double x[2*MAXN],y[2*MAXN];
double T[2*MAXN][1<<MAXN];
int P[2*MAXN][1<<MAXN];

// Vad är kortaste vägen hem om hon är vid now och har besökt attraktionerna enligt bitmasken vis?
double MLX(int now, int vis) {
  double best=1E100, d, xx, yy;
  int i,j,k,next = -1;
  if (T[now][vis]>=0) return T[now][vis];
  xx=(vis>0)?x[now]:0;
  yy=(vis>0)?y[now]:0;
  if(vis==(1<<N)-1) best=dst(xx,yy), next = -2;
  else for(i=0;i<N;i++) if(!((vis>>i)&1)) {
      for(j=0;j<2;j++) {
        k=i*2+j;
        d=dst(xx-x[k],yy-y[k])+MLX(k,vis|(1<<i));
        if(d<best) {
           best=d;
           next=i*2+j;
        }
      }
    }
  assert(next != -1);
  T[now][vis]=best;
  P[now][vis]=next;
  return best;
}

int main() {
  int i,j,now,vis;
  cin >> N;
  for(i=0;i<N;i++) for(j=0;j<2;j++) cin >> x[i*2+j] >> y[i*2+j];
  for(i=0;i<2*N;i++) for(j=0;j<(1<<N);j++) T[i][j]=-1;
  cout << setprecision(20) << fixed << MLX(0,0) << endl;
  now=0; vis=0;
  for(i=0;i<N;i++) {
    j=P[now][vis];
	cout << j/2+1 << ' ' << j%2+1 << endl;
    now=j;
    vis|=(1<<(j/2));
  }
  return 0;
}
