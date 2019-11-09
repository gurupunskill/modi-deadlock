#include <bits/stdc++.h>
#include "process.hpp"

using namespace std;

#define N 10
#define M 4

int main(){
    process_manager manager(N,M);
    //Get manager to invoke the ddr by all the candidates.
    for(int i=0;i<M+1;i++)
        manager.ddr_init(i);

    // Now the leader has been chosen.
    return 0;
}