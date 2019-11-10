#include <bits/stdc++.h>
#include "process.hpp"
#include "generate.hpp"

using namespace std;


int main(){
    int N_min = 5, N_max = 50, N_increment = 5;
    int M_min = 1;

    int N, M;
    for(N = N_min; N <= N_max; N+=N_increment) {
        for(M = N; M <= N; M++ ) {
            vector<vector<int> > RC = simple_cycle(M, N);
            
            process_manager manager(N,M, RC);
            // Get manager to invoke the ddr by all the candidates.
            for(int i=0;i<M+1;i++)
                manager.ddr_init(i);
            
            // Now the leader has been chosen.
            manager.process_requests();

            // Total number of messages analysis
            cout << "Total number of messages exchanged for N = " << N <<" and M = " << M << " is = " <<manager.get_message_count()<<endl;
        }
    }
    return 0;
}