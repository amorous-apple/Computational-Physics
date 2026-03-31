mod core;
use core::evaluate_state::calc_h;
use core::file_io::write_data_thermalization;
use core::grid_utils::{create_hot_state, sweep};

// Defining a macro to run the simulation for all given grid sizes
macro_rules! enter_the_matrix {
    ( $( $size:expr), *) => {
        $(
           println!("===================================");
           println!("Simulating L = {}",$size);
           // println!("{} states possible",1 << ($size * $size));
           simulate_ising::<$size>();
        )*
    }
}

fn main() {
    enter_the_matrix!(128);
}

// Running the Ising-Simulation for grid size L
fn simulate_ising<const L: usize>() {
    let num_spins: usize = L * L;
    // Performing Nt sweeps with Ntry hits for the Metropolis-Multihit simulation of the Ising
    // model
    const MAX_SWEEPS: usize = 6000; // Nt
    const MAX_MULTIHITS: usize = 5; // Ntry
    const RECORD_INTERVAL: usize = 50; // Record every 50 sweeps

    const NUM_DATAPOINTS: usize = (MAX_SWEEPS / RECORD_INTERVAL) * MAX_MULTIHITS;

    let mut sweep_indices: Vec<usize> = Vec::with_capacity(NUM_DATAPOINTS);
    let mut ntry_indices: Vec<usize> = Vec::with_capacity(NUM_DATAPOINTS);
    let mut energy_densities: Vec<f64> = Vec::with_capacity(NUM_DATAPOINTS);

    let init_state: [[i8; L]; L] = create_hot_state();
    let beta_vals: [f64; 11] = std::array::from_fn(|step| step as f64 / 10.0);

    for beta in beta_vals {
        sweep_indices.clear();
        ntry_indices.clear();
        energy_densities.clear();

        for ntry in 1..=MAX_MULTIHITS {
            let mut state = init_state.clone();

            for sweep_index in 1..=MAX_SWEEPS {
                sweep(&mut state, beta, ntry);

                if sweep_index % 50 == 0 {
                    let h = calc_h(&state);
                    let energy_density = h as f64 / num_spins as f64;

                    sweep_indices.push(sweep_index);
                    ntry_indices.push(ntry);
                    energy_densities.push(energy_density);
                }
            }
        }
        write_data_thermalization::<L>(beta, &sweep_indices, &ntry_indices, &energy_densities);
    }
}
