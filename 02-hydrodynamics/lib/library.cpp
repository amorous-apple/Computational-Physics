#include "library.hpp"


vector<double> library::advection(vector<double> psi, double N , double dt, double dx, vector<double> u, double t_max){
    double t = 0.0;
    vector<double> psi_temp = psi;
    while(t <= t_max){
        vector<double> psi_new = psi_temp;
        psi_new[0] = psi_new[int(N)];
        psi_new[1] = psi_new[int(N)+1]; // periodic boundary condition
        psi_new[int(N)+2] = psi_new[2];
        psi_new[int(N)+3] = psi_new[3];
        vector<double> F_m(int(N)+4,0.0);
        double psi_adv = 0.0;
        for(int i = 2; i <= int(N)+2; i++){
            if(u[i] > 0.0){
                double delta_psi = library::calc_delta_rho(psi_temp, N, i-1);
                psi_adv = psi_temp[i-1] + 0.5*(1 - u[i]*(dt/dx))*delta_psi; // equation 2.15
            }
            else{
                double delta_psi = library::calc_delta_rho(psi_temp, N, i);
                psi_adv = psi_temp[i] - 0.5*(1 + u[i]*(dt/dx))*delta_psi;
            }
            F_m[i] = psi_adv * u[i]; // equation 2.14
        }
        F_m[0] = F_m[int(N)]; // periodic boundary condition
        F_m[1] = F_m[int(N)+1];
        F_m[int(N)+2] = F_m[2];
        F_m[int(N)+3] = F_m[3];

        for(int i = 2; i <= int(N)+1; i++){
            psi_new[i] = psi_temp[i] - dt/dx*(F_m[i+1] - F_m[i]); // equation 2.13 
        }
        psi_temp = psi_new;
        t += dt;
    }
    return psi_temp;
    
}
    
double library::calc_delta_rho(vector<double> rho, double N, int i){ // equation 2.16
    double temp = ((rho[i+1] - rho[i])*(rho[i] - rho[i-1]));
    if( temp > 0.0){
        if (std::abs(rho[i+1] - rho[i-1]) < 1e-10) {
            return 0.0;
        }
        double delta_rho = 2.0*temp/(rho[i+1] - rho[i-1]);
        return delta_rho;
        
    }
    else{
        return 0.0;
    }
}

double library::calc_delta_u(vector<double> u, double N, int i){ // equation 2.22
    double temp = ((u[i+1] - u[i])*(u[i] - u[i-1]));
    if(temp > 0.0){
        double delta_u = 2.0*temp/(u[i+1] - u[i-1]) + 1e-10;
        return delta_u;
    }
    else{
        return 0.0;
    }
}

double library::calc_delta_epsilon(vector<double> epsilon, double N, int i){  // equation 2.29
    double temp = ((epsilon[i+1] - epsilon[i])*(epsilon[i] - epsilon[i-1]));
    if(temp > 0.0){
        double delta_epsilon = 2.0*temp/(epsilon[i+1] - epsilon[i-1]) + 1e-10;
        return delta_epsilon;
    }
    else{
        return 0.0;
    }
}

vector<double> library::rho_advection(vector<double> rho, double N , double dt, double dx, vector <double> u){
    vector <double> result(int(N)+4,0.0);
    for(int i = 2; i <= int(N)+2; i++){
        if(u[i] > 0.0){
            double delta_rho = library::calc_delta_rho(rho, N, i-1);
            result[i] = rho[i-1] + 0.5*(1 - u[i]*(dt/dx))*delta_rho;
        }
        else{
            double delta_rho = library::calc_delta_rho(rho, N, i);
            result[i] = rho[i] - 0.5*(1 + u[i]*(dt/dx))*delta_rho;
        }
    }
    return result;
}

vector<double> library::u_advection(vector<double> u, double N , double dt, double dx){
    vector <double> result(N+4,0.0);
    for(int i = 2; i <= int(N)+2; i++){
        double u_mean = 0.5*(u[i] + u[i+1]);
        if(u_mean > 0.0){
            double delta_u = library::calc_delta_u(u, N, i);
            result[i] = u[i] + 0.5*(1 - u_mean*(dt/dx))*delta_u;
        }
        else{
            double delta_u = library::calc_delta_u(u, N, i+1);
            result[i] = u[i+1] - 0.5*(1 + u_mean*(dt/dx))*delta_u;
        }
    }
    return result;
}

vector<double> library::epsilon_advection(vector<double> epsilon, double N , double dt, double dx, vector <double> u){
    vector <double> epsilon_adv(int(N)+4,0.0);
    for(int i = 2; i <= int(N)+2; i++){
        if(u[i] > 0.0){
            double delta_epsilon = library::calc_delta_epsilon(epsilon, N, i-1);
            epsilon_adv[i] = epsilon[i-1] + 0.5*(1 - u[i]*(dt/dx))*delta_epsilon; // Gleichung 2.15
        }
        else{
            double delta_epsilon = library::calc_delta_epsilon(epsilon, N, i);
            epsilon_adv[i] = epsilon[i] - 0.5*(1 + u[i]*(dt/dx))*delta_epsilon; // Gleichung 2.15
        }
    }
    return epsilon_adv;
}

vector<vector<double>> library::calc_F(vector<double> rho, vector<double> u, vector<double> epsilon, double N, double dt, double dx){
    vector<double> F_I(int(N)+4,0.0);
    vector<double> F_e(int(N)+4,0.0);
    vector<double> F_m(int(N)+4,0.0);
    vector<vector<double>> F;
    vector<double> rho_adv = library::rho_advection(rho, N, dt, dx, u);
    vector<double> u_adv = library::u_advection(u, N, dt, dx);
    vector<double> epsilon_adv = library::epsilon_advection(epsilon, N, dt, dx, u);
    for(int i = 2; i <= int(N)+2; i++){
       F_m[i] = rho_adv[i]*u_adv[i];
       F_e[i] = F_m[i]*epsilon_adv[i];
    }
    // set ghost fluxes (mirror periodic/consistent assignment)
    F_m[0] = F_m[int(N)];
    F_m[1] = F_m[int(N)+1];
    F_m[int(N)+2] = F_m[2];
    F_m[int(N)+3] = F_m[3];

    for(int i = 2; i <= int(N)+2; i++){
       F_I[i] = 0.5*(F_m[i] + F_m[i+1])*u_adv[i];
    }
    F.push_back(F_m);
    F.push_back(F_I);
    F.push_back(F_e);
    return F;
}

vector<vector<double>> library::solve_shocktube(vector<double> rho, vector<double> u, vector<double> epsilon, vector<double> p, double N, double dt, double dx, double t_max, double gamma){
    double t = 0.0;
    vector<vector<double>> result;
    vector<double> sigma_vec;
    while (t < t_max){
        vector<double> rho_mean(N+4,0.0);
        vector<double> rho_mean_new(N+5,0.0);
        vector<double> rho_new = rho;
        vector<double> u_new = u;
        vector<double> epsilon_new = epsilon;
        vector<double> p_new = p;
       
        vector<double> courant(N+4,0.0);
        for(int i = 0; i < N+4; i++){
            courant[i] = sqrt(gamma*p[i] / rho[i]);
            double courant_max =*std::max_element(courant.begin(), courant.end());
            auto u_minmax = std::minmax_element(u.begin(), u.end());
            double u_max = 0;
            if(abs(*u_minmax.first) > abs(*u_minmax.second)){
                u_max =*u_minmax.first;
            }
            else{
                u_max =*u_minmax.second;
            }
            double c_max = courant_max + u_max;
            double sigma = c_max*dt/dx;
            sigma_vec.push_back(sigma);
        }
        // flux
        vector<vector<double>> F = calc_F(rho, u, epsilon, N, dt, dx);
        
        for(int i = 2; i<= N+2; i++){
            rho_new[i] = rho[i] - (dt/dx)*(F[0][i+1] - F[0][i]);
        }
        for(int i = 3; i<= N+2; i++){
            rho_mean[i] = 0.5*(rho[i-1] + rho[i]);
            rho_mean_new[i] = 0.5*(rho_new[i-1] + rho_new[i]);
            u_new[i] = (u[i]*rho_mean[i] - dt/dx*(F[1][i] - F[1][i-1])) / rho_mean_new[i];
        }
        for(int i = 2; i<= N+2; i++){
            epsilon_new[i] = (epsilon[i]*rho[i] - dt/dx*(F[2][i+1] - F[2][i])) / rho_new[i];
        }

        // boundary conditions
        u_new[2] = 0;
        u_new[1] = -u_new[3];
        u_new[N+2] = 0;
        u_new[N+3] = -u_new[N+1];
        rho_new[1] = rho_new[2];
        rho_new[0] = rho_new[3];
        rho_new[N+2] = rho_new[N+1];
        rho_new[N+3] = rho_new[N];
        epsilon_new[1] = epsilon_new[2];
        epsilon_new[0] = epsilon_new[3];
        epsilon_new[N+2] = epsilon_new[N+1];
        epsilon_new[N+3] = epsilon_new[N];


        for(int i = 0; i < N+4; i++){
            p_new[i] = (gamma - 1)*rho_new[i]*epsilon_new[i];
        }
        vector<double> u_temp = u_new;
        for(int i = 3; i <= N+2; i++){
            u_new[i] = u_new[i] - dt/dx*(p_new[i] - p_new[i-1]) / rho_mean_new[i];
        }
        for(int i = 2; i <= N+2; i++){
            epsilon_new[i] = epsilon_new[i] - dt/dx*p_new[i]/rho_new[i]*(u_temp[i+1] - u_temp[i]);
        }
        rho = rho_new;
        u = u_new;
        epsilon = epsilon_new;
        p = p_new;
        t += dt;
    }
    vector<double> sigma_max = {*std::max_element(sigma_vec.begin(), sigma_vec.end())};
    result.push_back(rho);
    result.push_back(u);
    result.push_back(epsilon);
    result.push_back(p);
    result.push_back(sigma_max);
    return result;
}

void library::print_vector(vector<double> &vec){
    for(vector<double>::size_type i = 0; i < vec.size(); i++){
        std::cout << vec[i] << std::endl;
    }
}