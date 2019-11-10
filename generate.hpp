#ifndef GENERATE_HPP
#define GENERATE_HPP

#include<bits/stdc++.h>
using namespace std;

vector<vector<int> > simple_cycle(int m, int n) {
    vector<vector<int> > ret(n, vector<int>(n, 0));
    int i = 0, j = 1;

    while(i < m && j < m) {
        ret[i][j] = 1;
        i++; j++;
    }

    ret[m-1][0] = 1;
    return ret;
}

void print_mx(vector<vector<int> > mx) {
    int m = mx.size();
    int n = mx[0].size();

    int i, j;
    for(i = 0; i < m; i++) {
        for(j = 0; j < n; j++) {
            cout << mx[i][j] << " ";
        }
        cout << endl;
    }
}

#endif