//
// Created by Passerby on 2022/3/29.
//
#include "iostream"
using namespace std;
const int SIZE = 1e5;
const int LAYOUR = 16;
int f[SIZE][LAYOUR];
int length[SIZE][LAYOUR];
int origin[SIZE][3];
int lastappear[2*SIZE];
int prevappear[2*SIZE];
int deep[SIZE];
void getForefathers(int self, int father){
    deep[self] = deep[f[self][0]]+1;
    for(int i=1;(1<<i) < deep[self]; i++) {
        f[self][i] = f[f[self][i - 1]][i - 1];
        length[self][i] = length[self][i - 1]+length[f[self][i-1]][i-1];
    }
    for(int index=lastappear[self];index;index = prevappear[index]) {
        int temp,dis;
        if(index%2) {
            temp=origin[(index-1)/2][1];
            dis=origin[(index-1)/2][2];
        }else{
            temp=origin[(index-2)/2][0];
            dis=origin[(index-2)/2][2];
        }
        if (temp == father) continue;
        f[temp][0] = self;
        length[temp][0] = dis;
        getForefathers(temp, self);
    }
}
void Threecity() {
    int n;
    cin >> n;
    int _2px[LAYOUR];
    _2px[0] = 1;
    for (int i = 1; i < LAYOUR; i++) _2px[i] = _2px[i - 1] << 1;
    int a, b, c;
    for (int i = 0; i < n-1; i++) {
        scanf("%d%d%d", &a, &b, &c);
        prevappear[2 * i + 1] = lastappear[a];
        prevappear[2 * i + 2] = lastappear[b];
        lastappear[a] = 2 * i + 1;
        lastappear[b] = 2 * i + 2;
        origin[i][0] = a;
        origin[i][1] = b;
        origin[i][2] = c;
    }
    f[1][0] = 0;
    getForefathers(1, 0);
    int Q;
    cin >> Q;
    for (int q = 0; q < Q; q++) {
        int x, y;
        int cities[3];
        int result = 0;
        scanf("%d%d%d", cities, cities+1, cities+2);
        for(int city=0;city<3;city++) {
            x=cities[city%3];
            y=cities[(city+1)%3];
            if (deep[x] > deep[y]) {
                int t = x;
                x = y;
                y = t;
            }
            int temp1 = deep[y] - deep[x];
            for (int i = LAYOUR - 1; i >= 0; i--) {
                if (temp1 / _2px[i]) {
                    result += length[y][i];
                    y = f[y][i];
                    temp1 -= _2px[i];
                }
            }
            if (x != y) {
                for (int i = LAYOUR - 1; i >= 0; i--) {
                    if (f[x][i] != f[y][i]) {
                        result += (length[y][i] + length[x][i]);
                        x = f[x][i];
                        y = f[y][i];
                    }
                }
                result += length[x][0] + length[y][0];
            }
        }
        result/=2;
        printf("%d\n", result);
    }
}