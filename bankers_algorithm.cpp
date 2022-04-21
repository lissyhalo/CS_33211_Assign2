/*
 * Melissa Halozan
 * Assignment 2 : bankers_algorithm.cpp
 * CS OS
 *
 * C program for Banker's Algorithm 
 * see https://www.studytonight.com/operating-system/bankers-algorithm
 *
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

#define MAX_NP 10
#define MAX_NR 10

// helper to get string tokens from line of file
vector <string> get_tokens (string line) {
    vector <string> tokens;
    string intermediate;
    stringstream linestream(line);
    while(getline(linestream, intermediate, ','))
    {
        tokens.push_back(intermediate);
    }
    return tokens;
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Error: Input file is required." << endl;
        std::cerr << "       The main must be the first argument followed by " << endl;
        std::cerr << "       system snapshot table " << endl;
        std::cerr << "bankers_algorithm states.txt" << endl;
        std::cerr << "\nTable Format:" << endl;
        std::cerr << "First Row: NP = Number of processes (max " << MAX_NP << "), "; 
        std::cerr << "NR = Number of Resources (max  " << MAX_NP << ")" << endl;
        std::cerr << "NP Rows: NR resources allocated for processes" << endl;
        std::cerr << "NP Rows: NR maximum resources for processes" << endl;
        std::cerr << "Last Row : NR available resources" << endl;
        std::cerr << " 5, 3" << endl;
        std::cerr << " 0, 1, 0" << endl;
        std::cerr << " 2, 0, 0" << endl;
        std::cerr << " 3, 0, 2" << endl;
        std::cerr << " 2, 1, 1" << endl;
        std::cerr << " 0, 0, 2" << endl;
        std::cerr << " 7, 5, 3" << endl;
        std::cerr << " 3, 2, 2" << endl;
        std::cerr << " 9, 0, 2" << endl;
        std::cerr << " 2, 2, 2" << endl;
        std::cerr << " 4, 3, 3" << endl;
        std::cerr << " 3, 3, 2" << endl;

        std::cerr << std::endl << std::endl;
        return(1);
    }


    //
    // process the input file to get the state matrices
    //
    string state_file;
    string line;
    int NP, NR;
    vector <string> tokens;
    string intermediate;

    int alloc[MAX_NP][MAX_NR]; // max 10 processes x 10 resources
    int max[MAX_NP][MAX_NR]; // max 10 processes x 10 resources
    int avail[MAX_NR]; // max 10 resources

    state_file = argv[1];          //Get filename argument
    ifstream inFile(state_file);    

    // get first line with NP, NR
    getline(inFile, line);
    tokens = get_tokens (line);
    istringstream ( tokens[0] ) >> NP;
    istringstream ( tokens[1] ) >> NR;
    cout << "NP = " << NP << ", NR = " << NR << '\n';

    // get tables
    int process = 0;
    int resource = 0;
    int temp = 0;

    // read all lines from file, no checking
    while (getline(inFile, line)) {
        // split line into string tokens
        tokens = get_tokens (line);
        // get tokens, convert into integers, and save into tables
        for(resource = 0; resource < NR; resource++) {
            istringstream ( tokens[resource] )  >> temp;
            if (process < NP) {
                alloc[process][resource] = temp;
            }
            else if (process < 2*NP) {
                max[process - NP][resource] = temp;
            }
            else {
                avail[resource] = temp;
            }
        }
        process++;
    }
    inFile.close();

    cout << "alloc table:" << endl;
    for(process = 0; process < NP; process++) {
        for(resource = 0; resource < NR; resource++) {
            cout << alloc[process][resource] << " ";
        }
        cout << endl;
    }
    cout << "max table:" << endl;
    for(process = 0; process < NP; process++) {
        for(resource = 0; resource < NR; resource++) {
            cout << max[process][resource] << " ";
        }
        cout << endl;
    }
    cout << "available:" << endl;
        for(resource = 0; resource < NR; resource++) {
            cout << avail[resource] << " ";
        }
        cout << endl;


    // 
    // bankers algorithm 
    //
	int i, j, k; 

	int finish[MAX_NP], ans[MAX_NP], ind = 0;
    bool safe = true;    
	for (k = 0; k < NP; k++) { 
		finish[k] = 0; 
	} 
	int need[MAX_NP][MAX_NR]; 
	for (i = 0; i < NP; i++) { 
		for (j = 0; j < NR; j++) 
			need[i][j] = max[i][j] - alloc[i][j]; 
	} 
	int y = 0; 
    // repeat to make sure all 5 processes can get scheduled 
    //  (worst case just one is scheduled in inner loop)
	for (k = 0; k < NP; k++) { 
        // try to schedule each process
		for (i = 0; i < NP; i++) { 
			if (finish[i] == 0) {  // skip if process already finished
                // flag if there are enough resources for this process can run
				int flag = 0; 
				for (j = 0; j < NR; j++) { 
					if (need[i][j] > avail[j]){ 
						flag = 1; 
						break; 
					} 
				} 
                // process can run: save index, (run process), free its resources, mark as finished
				if (flag == 0) { 
					ans[ind++] = i;                    
					for (y = 0; y < NR; y++) 
						avail[y] += alloc[i][y]; 
					finish[i] = 1; 
				} 
			} 
		} 
	} 

    // check if all processes were scheduled
    for (i = 0; i < NP; i++) { 
        if (finish[i] == 0) {
            safe = false; 
        }
    } 

    if (safe == false) {
        printf("System is not in a safe state!\n"); 
    }
    else {
        cout << "System is in a safe state!\n"; 
        cout << "The safe sequence is as follows:\n"; 
        for (i = 0; i < NP - 1; i++) 
            cout << " P" << ans[i]<< " ->" ; 
        cout << " P" << ans[NP - 1] << "\n"; 
    }
    
       return (0); 

} 
