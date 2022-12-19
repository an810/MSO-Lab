#include<bits/stdc++.h>
using namespace std;

#define NTruck 3
#define NDrone 3
#define NCustomer 21

class Individual {
public: 
    int dim; 
    vector<int> path;
    vector<double> rand_per;
    vector<int> route_t1;
    vector<int> route_t2;
    vector<int> route_t3;
    vector<double> per_t1;
    vector<double> per_t2;
    vector<double> per_t3;


    Individual() {
        this->dim = NCustomer + NTruck - 1;
    }

    Individual(const Individual &p) {

    }

    void random_init() {
        vector<int> mark;
        for (int i=0; i<=this->dim; i++) 
            mark.push_back(0);
        for (int i=0; i<this->dim; i++) {
            int temp = rand() % this->dim+1;
            while (mark[temp] != 0) {
                temp = rand() % this->dim;
            }
            this->path.push_back(temp);
            mark[temp] = 1;
        }
    }

    void random_percent() {
        int count = 0;
        while (count < this->dim) {
            int n1 = rand() % 100+1;
            int n2 = rand() % 100+1;
            while (n2<n1 || n2 == n1) {
                n2 = rand() % 100+1;
            }
            double temp = 1.0 * n1 / n2;
            this->rand_per.push_back(temp);
        }
    }

    // decode the route for each truck
    void truck_routing() {
        int index = 0;
        int count = 0;
        while (index < this->dim) {
            if(count == 0 && this->path[index] <= NCustomer) {
                route_t1.push_back(path[index]);
                per_t1.push_back(rand_per[index]);
                index++;
                if (this->path[index] > NCustomer) {
                    count++; index++;
                }
            }
            if(count == 1 && this->path[index] <= NCustomer) {
                route_t2.push_back(path[index]);
                per_t2.push_back(rand_per[index]);
                index++;
                if (this->path[index] > NCustomer) {
                    count++; index++;
                }
            }
            if(count == 2 && this->path[index] <= NCustomer) {
                route_t3.push_back(path[index]);
                per_t3.push_back(rand_per[index]);
                index++;
                if (this->path[index] > NCustomer) {
                    count++; index++;
                }
            }
        }
    }

    //  good collecting point
    void good_collect() {
        
    }


};


int main() {
     
}