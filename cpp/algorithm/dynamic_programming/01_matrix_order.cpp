#include <iostream>

using std::cout;
using std::endl;

float matrixOrder(int dim[], int n, int muntOrder[]){
    for(int low = n-1; low >= 1; low--){
        for(int high = low + 1; high <= n; high++){
            if(high - low == 1){
                //TODO base case
            }else{
                bestcost = INT_MAX;
            }
            for(int k = low + 1; k <= high - 1; k++){
                int a = cost[low][k];
                int b = cose[k][high];
                int c = multCost(dim[low], dim[k], dim[high]);
                if(a + b + c < bestCost){
                    bestCost = a + b + c;
                    bestLast = k;
                }
            }
            cost[low][high] = bestCost;
            last[low][high] = bestLast;
        }
    }
    extrctOrderWrap(n, last, multOrder);
    return cost[0][n];
}

int main(void){

    

    return 0;
}