#include<bits/stdc++.h>
using namespace std;

#define FILE "mfea.txt"
#define POP_SIZE 10
#define MAX_GENERATION 100
#define rmp 0.5 
#define MAX_N 20

int len1, len2;
int N;
int distance1[MAX_N][MAX_N], distance2[MAX_N][MAX_N];

class Individual {
public:
    int dim; 
    int path[MAX_N];
    int f1, f2;
    int skill_factor; 
    double scalar_fitness;
    Individual() {
        this->dim = N;
    }

    Individual(const Individual &p) {
        this->dim = p.dim;
        for(int i=0; i<dim; i++) 
            this->path[i] = p.path[i];
        this->f1 = p.f1;
        this->f2 = p.f2;
        this->skill_factor = p.skill_factor;
        this->scalar_fitness = p.scalar_fitness;
    }

    // generate random solution
    void random_init() {
        vector<int> v(this->dim);
        for (int i=0; i<this->dim; i++) 
            v[i] = i+1;
        for (int i=0; i<this->dim; i++) {
            int index = rand() % this->dim;
            swap(v[i], v[index]);
        }
        for (int i=0; i<this->dim; i++) {
            this->path[i] = v[i];
        }
    }

    void evaluate_f1() {
        // tsp 1
        vector<int> path_1; 
        double factorial_cost_1 = 0;
        for (int i=0; i<dim; i++){
            if (path[i] <= len1)
                path_1.push_back(path[i]);
        }
        for (int i=0; i<len1; i++){
            factorial_cost_1 += distance1[path_1[i]][path_1[i+1]%len1];
        }
        this->f1 = factorial_cost_1;
    }

    void evaluate_f2() {
        // tsp 2
        vector<int> path_2;
        double factorial_cost_2 = 0;
        for (int i=0; i<dim; i++) {
            if (path[i] <=len2)
                path_2.push_back(path[i]);
        }
        for (int i=0; i<len2; i++) {
            factorial_cost_2 += distance2[path_2[i]][path_2[i+1]%len2];
        }
        this->f2 = factorial_cost_2;
    }

    static vector<Individual> crossover(Individual p1, Individual p2) {
        vector<Individual> children;
        Individual c1(p1);
        Individual c2(p2);

        double r = 1.0 * rand() / RAND_MAX;
        vector<int> index;
        if (p1.skill_factor == p2.skill_factor || r < rmp) {
            index.push_back(0);
            int value1 = p1.path[0], value2 = p2.path[0];
            int rootval = value1;
            while(value2 != rootval) {
                for (int i=1; i<p1.dim; i++) {
                    if (p1.path[i] == value2) {
                        value1 = p1.path[i];
                        value2 = p2.path[i];
                        index.push_back(i);
                    }
                }
            }

            for (int i=0; i<p1.dim; i++) {
                if(find(index.begin(), index.end(), i) != index.end()) {
                    c1.path[i] = p1.path[i];
                    c2.path[i] = p2.path[i];
                } else {
                    c1.path[i] = p2.path[i];
                    c2.path[i] = p1.path[i];
                }
            } 

            int randswap = rand() % 10;
            if (randswap % 2==0) 
                swap(c1.skill_factor, c2.skill_factor);
            children.push_back(c1);
            children.push_back(c2); 
        } else {
            int mutate_index1 = rand() % p1.dim;
            int mutate_index2 = rand() % p1.dim;
            while (mutate_index2 == mutate_index1)
                mutate_index2 = rand() % p1.dim;
            c1.path[mutate_index1] = p1.path[mutate_index2];
            c1.path[mutate_index2] = p1.path[mutate_index1];
            c2.path[mutate_index1] = p2.path[mutate_index2];
            c2.path[mutate_index2] = p2.path[mutate_index1];
            children.push_back(c1);
            children.push_back(c2);
        }
        return children;
    }
};

class Population {
public:  
    vector<Individual> population;
    Individual best_indv;

    void init() {
        for (int i=0; i<POP_SIZE; i++) {
            Individual p; 
            p.random_init();
            p.evaluate_f1();
            p.evaluate_f2();
            population.push_back(p);            
        }
        best_indv = population[0];
        update_best();
    }

    void update_best() {
        for (Individual &p: population) {
            if (p.scalar_fitness > best_indv.scalar_fitness) 
                best_indv = p;
        }
    }

    void update_pop() {
        vector<int> f1_rank;
        vector<int> f2_rank;
        vector<int> f1;
        vector<int> f2;
        
        // update rank
        for (Individual &p : population) {
            p.evaluate_f1();
            p.evaluate_f2();
            f1.push_back(p.f1);
            f2.push_back(p.f2);
        }

        vector<int> temp1; 
        for (int i=0; i<population.size(); i++)
            temp1.push_back(f1[i]);
        sort(temp1.begin(), temp1.end());
        for (int i=0; i<population.size(); i++) {
            auto it = find(temp1.begin(), temp1.end(), f1[i]);
            f1_rank.push_back(it - temp1.begin() + 1);
        }

        vector<int> temp2;
        for (int i=0; i<population.size(); i++) 
            temp2.push_back(f2[i]);
        sort(temp2.begin(), temp2.end());
        for (int i=0; i<population.size(); i++) {
            auto it = find(temp2.begin(), temp2.end(), f2[i]);
            f2_rank.push_back(it - temp2.begin() + 1);
        }
        // update skill factor and scalar fitness
        for (int i=0; i<population.size(); i++) {
            if (f1_rank[i] < f2_rank[i])
                population[i].skill_factor = 1;
            else population[i].skill_factor = 2;
        }
        for (int i=0; i<population.size(); i++) {
            double temp = 1.0 * 1/ population[i].skill_factor;
            population[i].scalar_fitness = temp;
        }
    }
    
    void reproduction(int count) {
        
        vector<Individual> offspring;
        while (offspring.size() < POP_SIZE) {
            //Choose parent 
            Individual p1, p2;
            int n1 = rand() % POP_SIZE;
            int n2 = rand() % POP_SIZE;
            int n3 = rand() % POP_SIZE;
            int n4 = rand() % POP_SIZE;
            while (n2 == n1) n2 = rand() % POP_SIZE;
            while (n3 == n1 || n3 == n2) n3 = rand() % POP_SIZE;
            while (n4 == n1 || n4 == n2 || n4 == n3) n4 = rand() % POP_SIZE;
            if (population[n1].scalar_fitness > population[n2].scalar_fitness)
                p1 = population[n1];
            else p1 = population[n2];
            if (population[n3].scalar_fitness > population[n4].scalar_fitness)
                p2 = population[n3];
            else p2 = population[n4];

            //crossover
            
            vector<Individual> children = Individual::crossover(p1,p2);
            offspring.insert(offspring.end(), children.begin(), children.end());
        }   
        population.insert(population.end(), offspring.begin(), offspring.end()); 
          
    }

    void selection(int count) {
        vector<Individual> candidates = population;
        population.clear();
        // while (population.size() < count) {
        //     Individual best = candidates[0];
        //     int index;
        //     for (int i=0; i<candidates.size(); i++) {
        //         if (candidates[i].scalar_fitness > best.scalar_fitness) {
        //             best = candidates[i];
        //             index = i;
        //         }
        //     }
        //     population.push_back(best);
        // }

        sort(candidates.begin(), candidates.end(), [](const Individual &x, Individual &y) {return x.scalar_fitness < y.scalar_fitness;});
        for (int i=POP_SIZE-1; i<2*POP_SIZE; i++) 
            population.push_back(candidates[i]);
    }

};

int main() {
    ifstream fi(FILE);
    srand(time(NULL));
    fi >> len1 >> len2;
    N = max(len1, len2);
    for (int i=0; i<len1; i++) 
        for (int j=0; j<len1; j++) 
            fi >> distance1[i][j];

    for (int i=0; i<len2; i++)
        for (int j=0; j<len2; j++) 
            fi >> distance2[i][j];
        
    
    Population pop;
    pop.init();
    pop.update_pop();
    cout << "Generation 0, best solution tsp1 = "<< pop.best_indv.f1 << " tsp2 = " << pop.best_indv.f2 << endl;
    for (int i=0; i<pop.best_indv.dim; i++)
            cout << pop.best_indv.path[i] << " ";
    cout << endl;
    for (int t=1; t<=MAX_GENERATION; t++) {
        pop.reproduction(POP_SIZE);
        for (Individual &indiv : pop.population) {
            indiv.evaluate_f1();
            indiv.evaluate_f2();
        }
        pop.update_pop();
        pop.selection(POP_SIZE);
        Individual best = pop.population[0];
        pop.update_best();
        cout << "Generation " << t << " , best solution f1 = "<< pop.best_indv.f1 << " tsp2 = " << pop.best_indv.f2 << endl;
        for (int i=0; i<pop.best_indv.dim; i++)
            cout << pop.best_indv.path[i] << " ";
        cout << endl;
    }
    return 0;
}