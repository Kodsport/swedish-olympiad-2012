#include <utility>
#include <set>
#include <string>
#include <cassert>
#include <cstring>
#include <cmath>
#include "streamcorr.h"

using namespace std;
typedef long long int64;

bool author_messages = false;

void author_message(const char *s) {
  if (author_messages) {
    report_feedback(authormessage, s);
  }
}
int T[101][101],p[100];


int num(int nr,int m,int h) {
  int i,sum=0;
  if(nr==h || m==0) return 1;
  if(T[nr][m]!=-1) return T[nr][m];
  for(i=(nr==0)?1:0;i<=p[nr] && i<=m;i++) sum+=num(nr+1,i,h);
  T[nr][m]=sum;
  return sum;
}

int main(int argc, char **argv) {
  init_io(argc, argv);
  int i, j, N, ok, n, nn;
  void *r1;
  int answer, ans;
  judge_ans >> answer;
  r1 = author_out >> ans;
  if(!r1){
    author_message("Invalid format.");
    report_error("Invalid format.");
  }
  if(ans != answer){
    report_feedback("Gives %d, should give %d\n", authormessage, ans, answer); 
    report_error("Gives %d, should give %d\n", ans, answer); 
  }
  judge_in >> N;
  ok = 1;
  for(n = 0, nn = 0; nn < N; n++){
    r1 = author_out >> p[n];
    if(!r1){
      author_message("Invalid format.");
      report_error("Invalid format.");
    }
    if(p[n] <= 0 || (n > 0 && p[n] > p[n-1])) ok = 0;
    nn += p[n];
  }
  if(nn != N) ok = 0;
  if(!ok){
    author_message("Invalid diagram");
    report_error("Invalid diagram\n");
  }
  for(i = 0; i<n; i++) for(j=0; j<=p[0]; j++) T[i][j] = -1;
  if(num(0, p[0], n) != ans){
    author_message("Not an optimal diagram.\n");
    report_error("Not an optimal diagram.\n");
  }
  accept();
}
