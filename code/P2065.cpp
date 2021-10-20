#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 1000010, M = 2000010, INF = 1e9;

long long head[N], edge[M], next_[M], ver[M], tot;
int  q[N], d[N], cur[N];
int n, m, S, T;
int red, blue, total;
int p[35500], b[35500]; 

int min_(int x, int y){
	if(x < y) return x;
	return y;
}

void add(int x, int y, int z){
	ver[tot] = y; edge[tot] = z; next_[tot] = head[x]; head[x] = tot ++;
	ver[tot] = x; edge[tot] = 0; next_[tot] = head[y]; head[y] = tot ++;
}

void divide(int x, int e){								//用试除法找质数点并连接 
	
	int y = 0;
	for (int o = 2; o <= sqrt(x); o ++){
		if(x % o == 0) {
			p[++ y] = o;
			while (x % o == 0) x /= o;
		}
	}
	if(x > 1) p[++ y] = x;
	for(int o = 1;o <= y; o ++) {
		if(b[p[o]] != 0) add(e, b[p[o]] + red + blue, 1);
		else b[p[o]] = ++ total, add(e, b[p[o]] + red + blue, 1);
	}
	return ;
}

void divide_2(int x,int e){
	int y = 0;
	for (int o = 2; o <= sqrt(x); o ++){
		if(x % o == 0) {
			p[++ y] = o;
			while (x % o == 0) x /= o;
		}
	}
	if(x > 1) p[++ y] = x;
	for(int o = 1;o <= y; o ++) {
		if(b[p[o]] != 0) add(b[p[o]] + red + blue, e, 1);
	}
	return ;
}

bool bfs() {												
	int hh = 0, tt = 0;
	memset(d, -1, sizeof d);
	q[0] = S, d[S] = 0, cur[S] = head[S];
	while (hh <= tt) {
		int t = q[hh++];
		for (int i = head[t]; ~i; i = next_[i]) {
			int ver_ = ver[i];
			if (d[ver_] == -1 && edge[i]) {
				d[ver_] = d[t] + 1;
				cur[ver_] = head[ver_];						 
				if (ver_ == T) return true;
				q[++ tt] = ver_;
			}
		}
	}
	return false;   
}

int find(int u, int limit) {									 
	if(u == T) return limit;
   	int flow = 0;
	for (int i = cur[u]; ~i && flow < limit; i = next_[i]) {
		cur[u] = i;
		int ver_ = ver[i];
		if (d[ver_] == d[u] + 1 && edge[i]) {
			int t = find(ver_, min_(edge[i], limit - flow));
			if (!t) d[ver_] = -1;
			edge[i] -= t, edge[i ^ 1] += t, flow += t;
		}
	}
	return flow;
}

int dinic() {												 //dinic 跑网络流 
	int r = 0, flow;
	while (bfs()) while (flow = find(S, INF)) r += flow;
	return r;
}

int num;

int main(){
	cin >> num;                                       //num为问题轮数
	
	for(int w = num; w > 0; w --){
		tot = 0;                                       //tot为节点总数
        //数组初始化
		memset(head, -1, sizeof head);
		memset(p, 0, sizeof p);
		memset(b, 0, sizeof b);
		total = 0;
		cin >> blue >> red;                             //两种卡片的数量
		for(int j = 1;j <= blue; j++){					//接入蓝色卡片 
			add(0, j, 1);
		}
		for(int j = 1;j <= blue; j++){                  //
			int blue_;
			cin >> blue_;
			divide(blue_, j);
		}
		for(int i = 1; i <= red; i++){
			int red_;
			cin >> red_;
			divide_2(red_, i + blue);
		}
		
		for(int i = 1; i <= red; i++){
			add(i + blue, red + blue + total + 1, 1);
		}
		S = 0;
		T = blue + red + total + 1;
		cout << dinic() << endl;
	}
	return 0;
}