mod core;
use core::evaluate_state::calc_h;
use core::file_io::write_data;
use core::grid_utils::{create_hot_state, sweep_heatbath};

use crate::core::analytical::{calc_anal_energy_density, calc_anal_magnetization};
use crate::core::evaluate_state::calc_total_m;

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
    let num_spins = L * L;
    const NUM_SWEEPS: usize = 2_000;
    const NUM_WARMUP_SWEEPS: usize = 2_000;
    const N_TRY: usize = 1;

    let mut state: [[i8; L]; L] = create_hot_state();

    const NUM_STEPS: usize = 200;
    // Setting up the list of inverse temperatures to test (beta in [0,1.0])
    let beta_vals: [f64; NUM_STEPS] =
        std::array::from_fn(|step| step as f64 / (NUM_STEPS - 1) as f64);
    // let h_arr: [i32; NUM_STEPS] = [0; NUM_STEPS];
    let mut energy_density: [f64; NUM_STEPS] = [0.0; NUM_STEPS]; // epsilon = <H> / L^2
    let mut anal_energy_density: [f64; NUM_STEPS] = [0.0; NUM_STEPS]; // epsilon
    //
    let mut magnetization: [f64; NUM_STEPS] = [0.0; NUM_STEPS];
    let mut anal_m: [f64; NUM_STEPS] = [0.0; NUM_STEPS]; // <|m|>

    let mut specific_heat: [f64; NUM_STEPS] = [0.0; NUM_STEPS];

    for (i, beta) in beta_vals.iter().enumerate() {
        println!("Simulating beta = {beta} ({i}/{NUM_STEPS})");
        // Warmup sweeps
        for _ in 0..NUM_WARMUP_SWEEPS {
            sweep_heatbath(&mut state, *beta);
        }

        // Initializing running sums to calculate average values over many sweeps
        let mut sum_h: f64 = 0.0;
        let mut sum_h_sqr: f64 = 0.0;

        let mut sum_m: f64 = 0.0;

        for _ in 1..=NUM_SWEEPS {
            sweep_heatbath(&mut state, *beta);
            let h = calc_h(&state) as f64;
            sum_h += h;
            sum_h_sqr += h * h;

            sum_m += calc_total_m(&state).abs();
        }
        // Normalizing values
        let mean_sum_h = sum_h / NUM_SWEEPS as f64;
        let mean_sum_h_sqr = sum_h_sqr / NUM_SWEEPS as f64;

        let energy_variance = mean_sum_h_sqr - (mean_sum_h * mean_sum_h);
        specific_heat[i] = beta * beta * energy_variance / num_spins as f64;

        energy_density[i] = sum_h / num_spins as f64 / NUM_SWEEPS as f64;
        anal_energy_density[i] = calc_anal_energy_density(*beta);

        magnetization[i] = sum_m / num_spins as f64 / NUM_SWEEPS as f64;
        anal_m[i] = calc_anal_magnetization(*beta);
    }
    write_data::<L>(
        &beta_vals,
        &energy_density,
        &anal_energy_density,
        &magnetization,
        &anal_m,
        &specific_heat,
    );
}
