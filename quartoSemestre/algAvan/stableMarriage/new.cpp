#include <stdio.h>
#define SINGLE 0
int main() {
    int t, n;
    scanf("%d", &t);                           // number of test cases
    while(t--) {
        scanf("%d", &n);
        int mList[n+1][n+1];                   // men's preference list
        int wList[n+1][n+1];                   // women's preference list
        int manCurrentMatch[n+1];              // current match of men
        int womanCurrentMatch[n+1];            // current match of men
        int manNextProposal[n+1];              // each man will propose this indexed woman in his preference list

        //taking inputs...
        for (int i = 1; i <= n; i++) {         // for each woman
            womanCurrentMatch[i] = SINGLE;     // set her to be single
            for(int j = 0; j <= n; j++) {
                scanf("%d", &wList[i][j]);
            }
        }

        for (int i = 1; i <= n; i++) {         // for each man
            manCurrentMatch[i] = SINGLE;       // set him to be single
            manNextProposal[i] = 1;            // each man will start by proposing 1st woman in his list
            for(int j = 0; j <= n; j++) {
                scanf("%d", &mList[i][j]);
            }
        }

        //algorithm...
        bool freeManAvailable = true;           // at begining we have free man available
        int m = 1;                              // taking the first man as free for first iteration
        while(freeManAvailable) {
            freeManAvailable = false;
            int w = mList[m][manNextProposal[m]++];  // the woman man proposes
            if(womanCurrentMatch[w] == SINGLE) {
                //w is currently free, engage (m and w)...
                womanCurrentMatch[w] = m;
                manCurrentMatch[m] = w;
            } else {
                //w is engaged...
                bool itsABetterProposal = false;     // check if it's a better proposal
                //check her preference list
                for(int y = 1; y <= n; y++) {
                    if(wList[w][y] == womanCurrentMatch[w]) {
                        itsABetterProposal = false; break;
                    }
                    if(wList[w][y] == m) {
                        itsABetterProposal = true; break;
                    }
                }
                if(itsABetterProposal) {
                    // if a better proposal, then engage (m and w), and set w's previous partner as free...
                    manCurrentMatch[womanCurrentMatch[w]] = SINGLE;
                    womanCurrentMatch[w] = m;
                    manCurrentMatch[m] = w;
                }
            }

            //finding a new free man...
            for(int x = 1; x <= n; x++) {
                if(manCurrentMatch[x] == SINGLE) {
                    m = x;
                    freeManAvailable = true;
                    break;
                }
            }
        }

        //show output...
        for(int i = 1; i <= n;  i++) {
            printf("%d %d\n", i, manCurrentMatch[i]);
        }
    }

    return 0;
}