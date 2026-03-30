mod core;
use core::analytical::{calc_anal_energy_density, calc_anal_magnetization};
use core::evaluate_state::{calc_h, calc_total_m};
use core::grid_utils::{create_hot_state, sweep};

use std::fs::OpenOptions;
use std::io::Write;

// use crate::core::analytical::{calc_anal_energy_density, calc_anal_magnetization};
// use crate::core::evaluate_state::calc_total_m;

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
    // Creating the file for all data to be written
    let output_file = "./data/task_3b_data.csv";
    std::fs::write(output_file, "L,energy_density,m_abs,m_sqr\n")
        .expect("Failed to create output file and write header.");

    const BETA: f64 = 0.4406868;
    let energy_density_anal = calc_anal_energy_density(BETA);
    let m_anal = calc_anal_magnetization(BETA);
    let m_anal_sqr = m_anal * m_anal;
    println!("analytical values for...");
    println!("energy_density:{energy_density_anal}, m:{m_anal}, m_sqr:{m_anal_sqr}");

    enter_the_matrix!(
        4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27,
        28, 29, 30, 31, 32
    );
}

// Running the Ising-Simulation for grid size L
fn simulate_ising<const L: usize>() {
    let num_spins = L * L;
    const NUM_SWEEPS: usize = 200_000;
    const NUM_WARMUP_SWEEPS: usize = 10_000;
    const N_TRY: usize = 1;
    const BETA: f64 = 0.4406868;

    let mut state: [[i8; L]; L] = create_hot_state();

    for _ in 0..NUM_WARMUP_SWEEPS {
        sweep(&mut state, BETA, N_TRY);
    }

    // Initializing running sums to calculate average values over many sweeps
    let mut sum_h: f64 = 0.0;

    let mut sum_m: f64 = 0.0;
    let mut sum_m_sqr: f64 = 0.0;

    for _ in 1..=NUM_SWEEPS {
        sweep(&mut state, BETA, N_TRY);
        let h = calc_h(&state) as f64;
        sum_h += h;

        let m = calc_total_m(&state).abs();
        sum_m += m;
        sum_m_sqr += m * m;
    }
    // Normalizing values
    let energy_density = sum_h / num_spins as f64 / NUM_SWEEPS as f64;
    let magnetization = sum_m / num_spins as f64 / NUM_SWEEPS as f64;
    let magnetization_sqr = sum_m_sqr / (num_spins as f64 * num_spins as f64) / NUM_SWEEPS as f64;

    // anal_energy_density[i] = calc_anal_energy_density(*beta);
    // anal_m[i] = calc_anal_magnetization(*beta);

    let mut lineout = OpenOptions::new()
        .append(true)
        .open("./data/task_3b_data.csv")
        .expect("Unable able to open data file for appending line.");

    writeln!(
        lineout,
        "{},{:.6},{:.6},{:.6}",
        L, energy_density, magnetization, magnetization_sqr
    )
    .expect("Faile to write lineout.");
}
