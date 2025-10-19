#include "lib/library.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h> 
#include <thread>
#include <chrono>
#include <string>
#include <cstring>
using std::string;



// turns doubles into strings of manageable size used in output names 
std::string to_string(double &variable)
{
   std::ostringstream Str;
   Str.precision(1);
   Str <<std::fixed<< variable;
   return(Str.str());
}

void write_to_file(vector<double> vec, string filename){
    std::ofstream file(filename);
    for(vector<double>::size_type i = 0; i < vec.size(); i++){
        if(i == vec.size()-1){
            file << vec[i];
            break;

        }
        else{
        file << vec[i] << ";";
        }
    }
    file.close();
}
int main(){
std::cout<<"Project: numerical hydrodynamics\nWhich exercise would you like to solve? 1 or 2?"<<std::endl;
int input = 0;
std::cin>>input;
if(input == 1){
// parameters to be adjusted
double a = 1.0;
double N = 400.0;        // 40.0
double sigma = 1.1;     // 0.9; 1.0; 1.1
double t_max = 400.0;     // 400.0
double x_min = -1.0;
double x_max = 1.0;

double dx = (x_max - x_min)/N;
double dt = sigma*dx/a;

// grid cells
vector<double> psi(N+4,0.0); // N+4 elements in total, including ghost cells
vector<double> u(N+4,0.0);
// cell boundaries
vector<double> x_a(N+4,0.0);
for(int i = 0; i <= N; i++){
   x_a[i+2] = x_min + (i)*dx;
}
// cell centers
vector<double> x_b(N+4,0.0);
for(int i = 0; i < N; i++){
   x_b[i+2] = x_min + 0.5*dx + i*dx;
}
// initial conditions
for(int i = 2; i <= N+2 ; i++){
    if(abs(x_b[i]) <= 0.333333333333333333){
        psi[i] = 1.0;
    }
    else{
        psi[i] = 0.0;
    }
    
}
// velocity u
for(int j = 2; j <= N+2; j++){
    u[j] = a;
}
// keeps track of time
auto start = std::chrono::high_resolution_clock::now();
vector<double> psi_out(N+4,0.0);
psi_out = library::advection(psi, N, dt, dx, u, t_max);

auto end = std::chrono::high_resolution_clock::now();
std::chrono::duration<double, std::milli> runtime = end - start;
std::cout << "runtime: " << runtime.count() << " ms\n";
write_to_file(psi_out, "output1/psi_N"+to_string(N)+"_sigma"+to_string(sigma) +".txt");
write_to_file(x_b, "output1/xb_N"+ to_string(N) +"_sigma"+ to_string(sigma) +".txt");
write_to_file(x_b, "output1/xa_N"+ to_string(N) +"_sigma"+ to_string(sigma) +".txt");
return 0;
}

else if(input == 2){
// parameters
double x_min = 0.0;
double x_max = 1.0;
double gamma = 1.4;
double N = 100;
double t_max = 0.228;
double dt = 0.001;
double dx = (x_max - x_min) / N;
 // cells + ghost cells
vector<double> rho(N+4,0.0);
vector<double> u(N+4,0.0);
vector<double> epsilon(N+4,0.0);
vector<double> p(N+4,0.0);
vector<double> xb(N+4,0.0);
vector<double> xa(N+4,0.0);
// cell borders

for(int i = 0; i <= N; i++){
   xa[i+2] = x_min + (i)*dx;
}
// cell centers

for(int i = 0; i < N; i++){
   xb[i+2] = x_min + 0.5*dx + i*dx;
}

// initial conditions
 for(int i = 0; i < N+4; i++){
     if(xb[i] <= 0.5){
         rho[i] = 1.0;
         u[i] = 0.0;
         p[i] = 1.0;
         epsilon[i] = 2.5;
     }
     else{
         rho[i] = 0.125;
         u[i] = 0.0;
         p[i] = 0.1;
         epsilon[i] = 2.0;
     }
 }

vector<vector<double>> result = library::solve_shocktube(rho, u, epsilon, p, N, dt, dx, t_max, gamma);

vector<double> temp(N+4);
for(int j = 0; j < N+4; j++){
    temp[j] = result[2][j] * (gamma -1);
}
write_to_file(result[0], "output2/rho.txt");
write_to_file(result[1], "output2/u.txt");
write_to_file(result[2], "output2/epsilon.txt");
write_to_file(result[3], "output2/p.txt");
write_to_file(result[4], "output2/sigma_max.txt");
write_to_file(temp, "output2/T.txt");
write_to_file(xb, "output2/xb.txt");

return 0;
}
else{
    std::cout<<"please enter 1 or 2 next time :)"<<std::endl;
    return 0;
}
}