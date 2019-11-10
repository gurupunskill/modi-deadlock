#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <iostream>
using namespace std;

enum ROLE {FOLLOWER, CANDIDATE, LEADER};
enum VOTE_TYPE {AGAINST=-1, FOR=1};

class process {
    
public:

    int uid; //index in array
    ROLE role;
    int n_votes;
    int leader_uid;
    vector<int> rc;

    process() {
        uid = -1;
        role = FOLLOWER;
        n_votes = 0;
        leader_uid = -1;
    }
};

class process_manager {
    
    int n_processes;
    int m_processes;
    int message_count;
    process *processes;

public:

    process_manager(int n, int m, vector<vector<int> > RC) {
        n_processes = n;
        m_processes = m;
        processes = new process[n_processes];
        message_count = 0;

        //Creating the processes that request concurrently for deadlock detection.
        for(int i = 0; i < n_processes; i++) {
            processes[i].uid = i;
            processes[i].rc = RC[i];
            if(i < m) processes[i].role = CANDIDATE;
            else processes[i].role = FOLLOWER;
        }
    }

    // algorithm 1
    void ddr_init(int uid_i) {
        if(processes[uid_i].leader_uid != -1) {
            //send ddri(leader_uid) to leader_uid
            // cout<<"Leader has been chosen already"<<endl;
        }
        else {
            bool done = false;
            for(int uid_j = 0; uid_j < n_processes; uid_j++) {
                if(uid_i != uid_j) {
                    done = vote_request(uid_i, uid_j);
                    if(done) break;
                }
            }
            processes[uid_i].role = CANDIDATE;
            //send ddri(leader_uid) to leader_uid
        }
    }

    // algorithm 2
    bool vote_request(int from_uid, int to_uid) {
        // cout << "vote_request from " << from_uid << " to " << to_uid << endl;
        increment_message_count();
        if(processes[to_uid].role == CANDIDATE 
            && (to_uid > from_uid)) {
            // Vote against
            // cout << to_uid << " votes against " << from_uid <<  endl;
            return vote(AGAINST, from_uid);
        }
        else {
            //Vote for
            // cout << to_uid << " votes for " << from_uid <<  endl;
            return vote(FOR, from_uid);
        }
    }

    // algorithm 3
    bool vote(VOTE_TYPE type, int uid_j) {
        increment_message_count();
        processes[uid_j].n_votes += type;
        if(processes[uid_j].n_votes == n_processes-1) {
            iamleader(uid_j);
            return true;
        }
        return false;
    }

    void iamleader(int uid_i) {
        // cout << uid_i << " is the LEADER" << endl;
        for (int i = 0; i < n_processes; i++) {
            processes[i].leader_uid = uid_i;
            increment_message_count();
        }
    }

    //Algorithm 4 - Leader processing the ddr requests
    void process_requests() {
        for (int i = 0; i < m_processes; i++) {
            increment_message_count();
            for(int j = 0; j<processes[i].rc.size(); j++) {
                if(processes[i].rc[j]) {
                    increment_message_count();
                    // cout<<"Leader processing DDR from "<<i<<" for Resource at "<<j<<endl;
                    // cout<<"Leader responds to "<<i<<" with appropriate report regarding resource."<<endl; 
                }
            }
        }
    }

    void increment_message_count() {
        message_count++;
    }

    int get_message_count() {
        return message_count;
    }
};

#endif