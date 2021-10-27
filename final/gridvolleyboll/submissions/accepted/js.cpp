#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(it,x) for(auto& it : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

template<typename T> ostream& operator<<(ostream& os, const vector<T> &v) { rep(i,0,sz(v)) { if (i) os << " " << v[i]; else os << v[i]; } os << endl; return os; }
template<typename T> istream& operator>>(istream& is, vector<T> &v) { trav(it, v) is >> it; return is; }
template<typename T> using v = vector<T>; template<typename T> using vv = v<v<T>>; template<typename T> using vvv = v<v<v<T>>>;
template<typename T> std::vector<T> make(T init, std::size_t size) { return std::vector<T>(size, init); }
template<typename T, typename... Args> auto make(T init, std::size_t first, Args... sizes) { auto inner = make<T>(init, sizes...); return std::vector<decltype(inner)>(first, inner); }
template<typename A, typename B> auto smax(A& a, const B& b) { if (b > a) a = b; }
template<typename A, typename B> auto smin(A& a, const B& b) { if (b < a) a = b;}
bool within(int r, int c, int R, int C) { return 0 <= r && r < R && 0 <= c && c < C; }

const int ST = 3 * 4 * 3 * 4 * 3 * 4 * 3 * 4 * 3 * 4;
int X, Y;
vi F(4), S(4);

struct State {
    vi x, y;
    int hasBall;
    int passes;

    bool canThrow(int sx, int sy) {
        int dx = x[hasBall] - sx;
        int dy = y[hasBall] - sy;
        if (dx * dx + dy * dy > F[hasBall]) return false;
        if (passes == 2 && (sx / X == x[hasBall] / X)) return false;
        return true;
    }

    bool canCatch(int p, int sx, int sy) {
        int dx = x[p] - sx;
        int dy = y[p] - sy;
        return dx * dx + dy * dy <= S[p];
    }

    int id() {
        int d = passes;
        rep(i,0,4) {
            d *= X;
            d += x[i] % X;
            d *= Y;
            d += y[i];
        }
        d *= 4;
        d += hasBall;
        return d;
    }

    void print() {
        cerr << hasBall << " " << passes << endl;
        cerr << x << y;
    }
};

template<class T>
void trycatch(State& s, int x, int y, T&& callback) {
    rep(i,0,4) {
        // same player can't catch
        if (i == s.hasBall) continue;
        // wrong half of the plan
        if ((i / 2) != (x / X)) continue; 
        // not too fast
        if (!s.canCatch(i, x, y)) continue;
        State nstate = s;
        nstate.x[i] = x;
        nstate.y[i] = y;
        nstate.hasBall = i;
        // is a pass
        if ((i / 2) == (s.hasBall / 2)) {
            nstate.passes++;
        } else {
            nstate.passes = 0;
        }
        callback(nstate);
    }
}

bool wins(State& s) {
    rep(x,0,2*X) rep(y,0,Y) {
        if (s.hasBall / 2 == x / X) continue; // is a pass
        if (!s.canThrow(x, y)) continue;
        rep(i,0,4) {
            if (s.hasBall / 2 == i / 2) continue; // is a pass
            if (s.canCatch(i, x, y)) goto no;
        }
        return true;
no:;
    }
    return false;
}

template<class T>
void getMoves(State& s, T&& ed) {
}

void solve() {
    cin >> X >> Y;
    rep(i,0,4) cin >> F[i] >> S[i];
    vector<int> outleft(ST);
    vector<vector<pii>> G(ST);
    vector<pii> dtw(ST, pii(-1, 0));
    queue<int> Q;

    rep(a1x,0,X) rep(a1y,0,Y) 
        rep(a2x,0,X) rep(a2y,0,Y) 
        rep(b1x,X,2*X) rep(b1y,0,Y) 
        rep(b2x,X,2*X) rep(b2y,0,Y) 
        rep(pass,0,3) rep(has,0,4) {
            State s;
            s.x = {a1x, a2x, b1x, b2x};
            s.y = {a1y, a2y, b1y, b2y};
            s.passes = pass;
            s.hasBall = has;

            int id = s.id();
            bool winning = wins(s);
            if (winning) {
                Q.push(id);
                dtw[id] = make_pair(has / 2, 1);
                continue;
            }

            rep(x,0,2*X) rep(y,0,Y) {
                if (!s.canThrow(x, y)) continue;
                vi moves;
                trycatch(s, x, y, [&](State& ns) {
                    moves.push_back(ns.id());
                });
                if (sz(moves) == 2) {
                    outleft[id]++;
                    G[moves[0]].emplace_back(id, moves[1]);
                    G[moves[1]].emplace_back(id, moves[0]);
                } else {
                    outleft[id] += sz(moves);
                    trav(m, moves) G[m].emplace_back(id, -1);
                }
            }

            if (outleft[id] == 0) {
                Q.push(id);
                dtw[id] = make_pair(1 - (has / 2), 0); // We have no response, so it's already lost
            }
        }

    vector<bool> done(ST);
    vector<int> bestloss(ST);
    while (!Q.empty()) {
        int w = Q.front(); Q.pop();
        done[w] = true;
        int tteam = (w % 4) / 2;
        trav(F, G[w]) {
            int from = F.first;
            int ot = F.second;
            bool fteam = (from % 4) / 2;
            int nmove = dtw[w].second + (tteam != fteam);
            bool winMove = fteam == dtw[w].first;
            if (ot != -1 && winMove && !done[ot]) continue; // winning move; must wait for other in pair
            if (ot != -1 && done[ot] && fteam != dtw[ot].first) {
                smax(bestloss[from], nmove);
                continue; // other was done, and we lose so the pair is already marked
            }

            if (winMove) {
                if (dtw[from].first == -1) {
                    dtw[from] = make_pair(fteam, nmove);
                    Q.push(from);
                } else smin(dtw[from].second, nmove);
                if (ot != -1) smin(dtw[from].second, dtw[ot].second + (tteam != fteam));
            } else {
                smax(bestloss[from], nmove);
                if (--outleft[from] == 0) {
                    dtw[from].first = !fteam;
                    dtw[from].second = bestloss[from];
                    Q.push(from);
                }
            }
        }
    }

    {
        int bestwin = 1000;
        rep(a2x,0,X) rep(a2y,0,Y)  {
            int worstwin = 0;
            rep(b1x,X,2*X) rep(b1y,0,Y) 
                rep(b2x,X,2*X) rep(b2y,0,Y) {
                    State s;
                    s.x = {0, a2x, b1x, b2x};
                    s.y = {0, a2y, b1y, b2y};
                    s.passes = 2;
                    s.hasBall = 0;
                    int id = s.id();
                    if (dtw[id].first != 0) goto skip;
                    smax(worstwin, dtw[id].second);
                }
            smin(bestwin, worstwin);
skip:;
        }
        if (bestwin != 1000) {
            cout << "win" << endl << bestwin << endl;
            exit(0);
        }
    }

    {
        int bestloss = 0;
        rep(a2x,0,X) rep(a2y,0,Y)  {
            int worstloss = 1000;
            rep(b1x,X,2*X) rep(b1y,0,Y) 
                rep(b2x,X,2*X) rep(b2y,0,Y) {
                    State s;
                    s.x = {0, a2x, b1x, b2x};
                    s.y = {0, a2y, b1y, b2y};
                    s.passes = 2;
                    s.hasBall = 0;
                    int id = s.id();
                    if (dtw[id].first == 1) smin(worstloss, dtw[id].second);
                }
            if (worstloss == 1000) {
                cout << "tie" << endl;
                exit(0);
            }
            smax(bestloss, worstloss);
        }
        cout << "loss" << endl << bestloss << endl;
        exit(0);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int TC = 1;
    if (!TC) cin >> TC;
    rep(i,1,TC+1) {
        // cout << i << " ";
        solve();
    }
}
