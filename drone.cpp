#include<bits/stdc++.h>
using namespace std;

#define N 50
#define NTruck 3
#define NDrone 3
#define NCustomer 21
#define POP_SIZE 10

// vTruck, vDrone, x, y: km; releaseDate: minute
double vTruck = 30.0;
double vDrone = 45.0;
int droneCapacity = 3;
int timeHorizon;
int x[NCustomer], y[NCustomer], releaseDate[NCustomer]; 
double distance[N][N];

class Individual {
public: 
    int dim;
    vector<int> path;
    vector<double> rand_per;
    vector<int> route_t1;
    vector<int> route_t2;
    vector<int> route_t3;
    vector<int> goodCol[NCustomer + 1];
    vector<double> per_t1;
    vector<double> per_t2;
    vector<double> per_t3;


    Individual() {
        this->dim = NCustomer + NTruck - 1;
    }

    Individual(const Individual &p) {
        this->dim = p.dim;
        for (int i=0; i<dim; i++)
            this->path[i] = p.path[i];
    
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
                this->route_t1.push_back(path[index]);
                this->per_t1.push_back(rand_per[index]);
                index++;
                if (this->path[index] > NCustomer) {
                    count++; index++;
                }
            }
            if(count == 1 && this->path[index] <= NCustomer) {
                this->route_t2.push_back(path[index]);
                this->per_t2.push_back(rand_per[index]);
                index++;
                if (this->path[index] > NCustomer) {
                    count++; index++;
                }
            }
            if(count == 2 && this->path[index] <= NCustomer) {
                this->route_t3.push_back(path[index]);
                this->per_t3.push_back(rand_per[index]);
                index++;
                if (this->path[index] > NCustomer) {
                    count++; index++;
                }
            }
        }
    }

    //  good collecting point
    void good_collect() {
        //truck 1 
        for (int i=0; i<this->route_t1.size(); i++) {
            double value = this->per_t1[i];
            for (int j=0; j<=i; j++) {
                if (value > (double) j / (i + 1) && value <= (double) (j + 1) / (i + 1)) {
                    this->goodCol[j].push_back(route_t1[i]);
                }
            }
        }
        //truck 2
        for (int i=0; i<this->route_t2.size(); i++) {
            double value = this->per_t2[i];
            for (int j=0; j<=i; j++) {
                if (value > (double) j / (i + 1) && value <= (double) (j + 1) / (i + 1)) {
                    this->goodCol[j].push_back(route_t2[i]);
                }
            }
        }
        //truck 3
        for (int i=0; i<this->route_t3.size(); i++) {
            double value = this->per_t3[i];
            for (int j=0; j<=i; j++) {
                if (value > (double) j / (i + 1) && value <= (double) (j + 1) / (i + 1)) {
                    this->goodCol[j].push_back(route_t3[i]);
                }
            }
        }
    }

    //evaluate
    void evaluate() {

    }



};

// void Input() {
//     for (int i=0; i<NCustomer; i++) {
//         cin >> x[i] >> y[i] >> releaseDate[i];
//     }
//     for (int i=0; i<NCustomer; i++) {
//         for (int j=0; j<NCustomer; j++) {
//             if (i==j) distance[i][j] = 0;
//             distance[i][j] = sqrt(pow(x[i]-x[j], 2)+ pow(y[i]- y[j], 2));
//         }
//     }
// }

int main() {
    //Input();
    Individual p;
    p.random_init();
    p.random_percent();
    p.truck_routing();
    for (int i=0; i<p.route_t1.size(); i++) {
        cout << p.route_t1[i] << " ";
    }
    for (int i=0; i<p.route_t2.size(); i++) {
        cout << p.route_t2[i] << " ";
    }
    for (int i=0; i<p.route_t3.size(); i++) {
        cout << p.route_t3[i] << " ";
    }
}
