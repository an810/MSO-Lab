#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100

double sphere(double x[], int dim) {
    double sum = 0.0;
    for (int i=0; i<dim; i++)
        sum += x[i] * x[i];
    return sum;
}

inline double randDouble(double low, double high) {
    double r = 1.0 * rand() / RAND_MAX;
    return low + (high - low) * r;
}


class Particle {
public:
    int dim;            // số chiều

    double x[MAX_N];          // vị trí hiện tại
    double p[MAX_N];          // vị trí tốt nhất từng có
    double v[MAX_N];          // vận tốc hiện tại

    double fitness;     // độ thích nghi
    double best_fitness;// độ thích nghi tốt nhất từng có


    Particle(int dim) {
        this->dim = dim;
        best_fitness = DBL_MAX;
    }

    void evaluate() {
        fitness = sphere(x, dim);
        if (fitness < best_fitness) {
            best_fitness = fitness;
            memcpy(p, x, dim*sizeof(double));
        }
    }

    void random_init(double low[], double high[]) {
        for (int i=0; i<dim; i++) {
            x[i] = randDouble(low[i], high[i]);
            v[i] = 0.5 * randDouble(-(high[i]-low[i]), high[i]-low[i]);
        }

        evaluate();
    }

    void update_velocity(double phi1, double phi2, double pg[]) {
        double r1 = randDouble(0, 1), r2 = randDouble(0, 1);
        for (int i=0; i<dim; i++)
            v[i] = v[i] + phi1*r1* (p[i]-x[i]) + phi2*r2* (pg[i]-x[i]);
    }

    void update_position(double low[], double high[]) {
        for (int i=0; i<dim; i++) {
            x[i] = x[i] + v[i];
            x[i] = max(low[i], min(x[i], high[i]));
        }
    }
};


class Swarm {
public:
    double *low, *high;         // cận dưới và trên
    int dim;                    // số chiều

    int pop_size;               // số cá thể
    vector<Particle> particles; // các cá thể

    double pg[MAX_N];           // vị trí tốt nhất toàn cục
    double g_fitness;           // độ thích nghi tại pg

    Swarm(int pop_size, int dim, double low[], double high[]) {
        this->pop_size = pop_size;
        this->dim = dim;
        this->low = low;
        this->high = high;

        g_fitness = DBL_MAX;
    }

    void swarm_init() {
        for (int k=0; k<pop_size; k++) {
            Particle p = Particle(dim);
            p.random_init(low, high);
            p.evaluate();
            particles.push_back(p);

            if (p.fitness < g_fitness) {
                g_fitness = p.fitness;
                memcpy(pg, p.x, dim*sizeof(double));
            }
        }
    }

    void searching(int max_iterations, double phi1, double phi2) {
        swarm_init();
        cout << "Iteration 0: best fitness = " << g_fitness << endl;

        for (int t=0; t<max_iterations; t++) {
            for (int i=0; i<pop_size; i++) {
                Particle p = particles[i];
                p.update_velocity(phi1, phi2, pg);
                p.update_position(low, high);

                p.evaluate();

                if (p.fitness < g_fitness) {
                    g_fitness = p.fitness;
                    memcpy(pg, p.x, dim*sizeof(double));
                }
            }

            cout << "Iteration " << t+1 << ": best fitness = " << g_fitness << endl;
        }
    }
};


int main() {
    int dim = 5;
    double low[MAX_N], high[MAX_N];
    for (int i=0; i<dim; i++) {
        low[i] = -100;
        high[i] = 100;
    }

    Swarm swarm = Swarm(20, dim, low, high);
    swarm.searching(100, 1, 3);
}
