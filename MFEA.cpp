#include<bits/stdc++.h>
using namespace std;

#define FILE "mfea.txt"
#define POP_SIZE 10
#define MAX_GENERATION 100
#define rmp 0.5 
#define MAX_N 20

int len1, len2;
int N;
int t;
int distance1[MAX_N][MAX_N], distance2[MAX_N][MAX_N];

class Individual {
public:
    int dim; 
    int path[MAX_N];
    int f1, f2;
    int skill_factor; 
    double scalar_fitness;
    int birth;

    Individual() 
    {
        this->dim = N;
    }

    Individual(const Individual &p) {
        this->birth = p.birth;
        this->dim = p.dim;
        for(int i=0; i<dim; i++) 
            this->path[i] = p.path[i];
        this->f1 = p.f1;
        this->f2 = p.f2;
        this->skill_factor = p.skill_factor;
        this->scalar_fitness = p.scalar_fitness;
    }

    // generate random solution
    void random_init()      
    {
        vector<int> v(this->dim);
        for (int i=0; i<this->dim; i++) 
            v[i] = i+1;
        for (int i=0; i<this->dim; i++)
         {
            int index = rand() % this->dim;
            swap(v[i], v[index]);
        }
        for (int i=0; i<this->dim; i++) 
        {
            this->path[i]=v[i];
        }
    }

    void evaluate_f1() 
    {
        vector<int> path_1; 
        double factorial_cost_1 = 0;
        for (int i=0; i<dim; i++)
        {
            if (path[i] <= len1)
                path_1.push_back(path[i]);
        }
        for (int i=0; i<dim; i++)
            if (path[i] <= len1) {path_1.push_back(path[i]);break;}
        for (int i=0; i<len1; i++){
            factorial_cost_1 += distance1[path_1[i]][path_1[i+1]];
        }
        this->f1 = factorial_cost_1;
    }

    void evaluate_f2() 
    {
        vector<int> path_2;
        double factorial_cost_2 = 0;
        for (int i=0; i<dim; i++) {
            if (path[i] <=len2)
                path_2.push_back(path[i]);
        }
        for (int i=0; i<dim; i++)
            if (path[i] <= len2) {path_2.push_back(path[i]);break;}
        for (int i=0; i<len2; i++) {
            factorial_cost_2 += distance2[path_2[i]][path_2[i+1]];
        }
        this->f2 = factorial_cost_2;
    }

    static vector<Individual> crossover(Individual p1, Individual p2) {
        vector<Individual> children;
        Individual c1(p1);
        Individual c2(p2);

        double r = 1.0 * rand() / RAND_MAX;

        vector<int> index;
        if (p1.skill_factor == p2.skill_factor || r < rmp) 
        {
            int start=rand()%p1.dim;
            index.push_back(start);
            int value1 = p1.path[start], value2 = p2.path[start];
            int rootval = value1;
            while(value2 != rootval) 
            {
                for (int i=0; i<p1.dim; i++) 
                    if (p1.path[i] == value2) 
                    {
                        value1 = p1.path[i];
                        value2 = p2.path[i];
                        index.push_back(i);
                        break;
                    }
                
            }
            

            for (int i=0; i<index.size();i++)
            {
                swap(c1.path[index[i]],c2.path[index[i]]);
            }
            // for (int i=0; i<p1.dim; i++) {
            //     if(find(index.begin(), index.end(), i) != index.end()) {
            //         c1.path[i] = p1.path[i];
            //         c2.path[i] = p2.path[i];
            //     } else {
            //         c1.path[i] = p2.path[i];
            //         c2.path[i] = p1.path[i];
            //     }
            // } 

            int randswap = rand() % 10;
            if (randswap % 2==0) 
                swap(c1.skill_factor, c2.skill_factor);
            c1.birth=t;
            c2.birth=t;
            c1.evaluate_f1();
            c1.evaluate_f2();
            c2.evaluate_f1();
            c2.evaluate_f2();
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
            c1.birth=t;
            c2.birth=t;
            c1.evaluate_f1();
            c1.evaluate_f2();
            c2.evaluate_f1();
            c2.evaluate_f2();
            children.push_back(c1);
            children.push_back(c2);
        }
        return children;
    }
};

class Population {
public:  
    vector<Individual> indv;
    Individual best_indv;
    Individual best_indv1, best_indv2;

    void update_best() 
    {
        best_indv=indv[0];
        for (Individual &p: indv) 
        {
            if (p.scalar_fitness > best_indv.scalar_fitness) 
                best_indv = p;
        }
    }

    void record_best() 
    {
        for (int i=0;i<POP_SIZE;i++)
        {
            if (best_indv1.f1 > indv[i].f1) 
                best_indv1 = indv[i];
            if (best_indv2.f2 > indv[i].f2) 
                best_indv2 = indv[i];
        }
    }

    void update_pop() 
    {
        vector<int> f1_rank;
        vector<int> f2_rank;
        vector<pair<int,int>> f1;
        vector<pair<int,int>> f2;
        
        // update rank
        for (Individual &p : indv) 
        {
            p.evaluate_f1();
            p.evaluate_f2();
            f1_rank.push_back(0);
            f2_rank.push_back(0);
        }

        for (int i=indv.size()-1; i>=0; i--)
        {
            f1.push_back(make_pair(indv[i].f1,i));
            f2.push_back(make_pair(indv[i].f2,i));
        }
        sort(f1.begin(), f1.end());
        sort(f2.begin(), f2.end());

        for (int i=0;i<f1.size();i++)
        {
            f1_rank[f1[i].second]=i+1;
            f2_rank[f2[i].second]=i+1;
        }
    
        // vector<int> temp1; 
        // for (int i=0; i<indv.size(); i++)
        //     temp1.push_back(f1[i]);
        // sort(temp1.begin(), temp1.end());
        // for (int i=0; i<indv.size(); i++) {
        //     auto it = find(temp1.begin(), temp1.end(), f1[i]);
        //     f1_rank.push_back(it - temp1.begin() + 1);
        // }

        // vector<int> temp2;
        // for (int i=0; i<indv.size(); i++) 
        //     temp2.push_back(f2[i]);
        // sort(temp2.begin(), temp2.end());
        // for (int i=0; i<indv.size(); i++) {
        //     auto it = find(temp2.begin(), temp2.end(), f2[i]);
        //     f2_rank.push_back(it - temp2.begin() + 1);
        // }

        // update skill factor and scalar fitness
        for (int i=0; i<indv.size(); i++) 
        {
            if (f1_rank[i] < f2_rank[i])
                indv[i].skill_factor = 1;
            else indv[i].skill_factor = 2;
        }
        for (int i=0; i<indv.size(); i++) {
            double temp = 1.0 * 1/ min(f1_rank[i],f2_rank[i]);    //updated
            indv[i].scalar_fitness = temp;
        }
    }

    void init() 
    {

        for (int i=0; i<POP_SIZE; i++) 
        {
            Individual p; 
            p.random_init();
            p.evaluate_f1();
            p.evaluate_f2();
            p.birth=1;
            indv.push_back(p);    
        }
        best_indv = indv[0];
        best_indv1 = indv[0];
        best_indv2 = indv[0];
        update_pop();
        update_best();
    }

    void selection(Population offspring) 
    {
        vector<pair<double,int>> v;
        for (int i=0;i<offspring.indv.size();i++)
        {
            v.push_back(make_pair(offspring.indv[i].scalar_fitness,i));
        }
        sort(v.begin(), v.end());

        vector<Individual> new_pop;
        for (int i=0;i<POP_SIZE;i++)
            new_pop.push_back( offspring.indv[v[offspring.indv.size()-i-1].second] );
        
        // cout<<"new pop:"<<endl;
        // for (int i=0;i<POP_SIZE;i++)
        // {
        //     for (int j=0;j<9;j++) cout<<new_pop[i].path[j]<<" ";
        //     cout<<" | scalar-fitness: "<<new_pop[i].scalar_fitness<<endl;
        // }

        this->indv=new_pop;

    }
    
    void reproduction(Population pop) {
        
        Population offspring;

        for (int i=0;i<POP_SIZE;i++)
        {
            offspring.indv.push_back(pop.indv[i]);
        }

        while (offspring.indv.size() < 2*POP_SIZE) 
        {
            //Choose parent 
            Individual p1, p2;
            int n1 = rand() % POP_SIZE;
            int n2 = rand() % POP_SIZE;
            int n3 = rand() % POP_SIZE;
            int n4 = rand() % POP_SIZE;
            while (n2 == n1) n2 = rand() % POP_SIZE;
            while (n3 == n1 || n3 == n2) n3 = rand() % POP_SIZE;
            while (n4 == n1 || n4 == n2 || n4 == n3) n4 = rand() % POP_SIZE;
            if (pop.indv[n1].scalar_fitness > pop.indv[n2].scalar_fitness)
                p1 = pop.indv[n1];
            else p1 = pop.indv[n2];
            if (pop.indv[n3].scalar_fitness > pop.indv[n4].scalar_fitness)
                p2 = pop.indv[n3];
            else p2 = pop.indv[n4];

            //crossover
            
            vector<Individual> children = Individual::crossover(p1,p2);
            offspring.indv.insert(offspring.indv.end(), children.begin(), children.end());
        }   

        offspring.update_pop();
        
        // cout<<endl<<"offsprings: "<<endl;
        // for (int i=0;i<offspring.indv.size();i++)
        // {
        //     for (int j=0;j<9;j++)
        //         cout<<offspring.indv[i].path[j]<<" ";
        //     cout<<" | scalar-fitness: "<<offspring.indv[i].scalar_fitness<<endl;
        // }

        this->indv=offspring.indv;
        
    }

};

int main() 
{
    ifstream fi(FILE);
    srand(time(NULL));
    fi >> len1 >> len2;
    N = max(len1, len2);

    for (int i=1; i<=len1; i++) 
        for (int j=1; j<=len1; j++) 
            fi >> distance1[i][j];

    for (int i=1; i<=len2; i++)
        for (int j=1; j<=len2; j++) 
            fi >> distance2[i][j];
        
    Population pop;
    pop.init();
    cout<<endl<<"Age at generation 1: "<<endl;
        for (int i=0;i<pop.indv.size();i++)
        {
            cout<<pop.indv[i].birth<<" ";
        }
        cout<<endl;
    pop.record_best();

    cout << "Generation 0, best solution tsp1 = "<< pop.best_indv1.f1 << " tsp2 = " << pop.best_indv2.f2 << endl;

    
    // Population offspring;
    // offspring.reproduction(pop);
    // pop.selection(offspring);

    for ( t=1; t<=MAX_GENERATION; t++) 
    {
        Population offspring;
        offspring.reproduction(pop);
        pop.selection(offspring);
        pop.update_pop();
        pop.record_best();
        pop.update_best();
        cout << "Generation " << t << " , best solution f1 = "<< pop.best_indv.f1 << " tsp2 = " << pop.best_indv.f2 << " "<<endl;
    }

    cout<<endl;
    cout<<"Best route for TSP 1: "<<endl;
    for (int i=0;i<N;i++)
    {
        cout<<pop.best_indv1.path[i]<<" ";
    }
    cout<<" | f2: "<<pop.best_indv1.f1<<endl;

    cout<<"Best route for TSP 2: "<<endl;
    for (int i=0;i<N;i++)
    {
        cout<<pop.best_indv2.path[i]<<" ";
    }
    cout<<" | f2: "<<pop.best_indv2.f2<<endl;

    cout<<endl<<"Stats at generation 100: "<<endl;
    for (int i=0;i<pop.indv.size();i++)
    {
        cout<<"f1: "<<pop.indv[i].f1<<" | f2: "<<pop.indv[i].f2<<" | Birth: "<<pop.indv[i].birth<<endl;
    }
    cout<<endl;
    // int min_f1=INT_MAX,min_f2=INT_MAX;
    // for (int i=0;i<POP_SIZE;i++)
    // {
    //     min_f1=min(min_f1,pop.indv[i].f1);
    //     min_f2=min(min_f2,pop.indv[i].f2);
    // }
    // cout<<"At generation 100, min of f1: "<<min_f1 <<" , min of f2: "<<min_f2<<endl;


    // // Scalar-fitness at gen 100
    // cout<<"Scalar-fitness at gen 100: "<<endl;
    // for (int i=0;i<POP_SIZE;i++)
    // {
    //     cout<<pop.indv[i].scalar_fitness<<endl;
    // }
    return 0;
}
