mod core;
use core::evaluate_state::calc_m;
use core::file_io::write_data;
use core::grid_utils::{create_hot_state, sweep_heatbath};

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
    const NUM_SWEEPS: usize = 5_000;
    const NUM_WARMUP_SWEEPS: usize = 1_000;
    const BETA: f64 = 0.7;

    let mut state: [[i8; L]; L] = create_hot_state();

    const NUM_DATAPOINTS: usize = 400;
    const HALF_NUM_DATAPOINTS: usize = NUM_DATAPOINTS / 2;

    // Creating a range of h_vals from -1.0 to 1.0
    let h_vals: [f64; HALF_NUM_DATAPOINTS] =
        std::array::from_fn(|x| -1.0 + 2.0 * (x as f64 / (HALF_NUM_DATAPOINTS - 1) as f64));
    let mut h_vals_full: [f64; NUM_DATAPOINTS] = [0.0; NUM_DATAPOINTS];
    let mut m_vals: [f64; NUM_DATAPOINTS] = [0.0; NUM_DATAPOINTS];

    // Running the loop for h from -1.0 to 1.0
    for (i, h) in h_vals.iter().enumerate() {
        println!("h: ({i}/{NUM_DATAPOINTS})");
        // Warmup
        for _ in 0..NUM_WARMUP_SWEEPS {
            sweep_heatbath(&mut state, BETA, *h);
        }

        let mut m: f64 = 0.0;
        for _ in 0..NUM_SWEEPS {
            sweep_heatbath(&mut state, BETA, *h);
            m += calc_m(&state);
        }
        h_vals_full[i] = *h;
        let m_mean = m / NUM_SWEEPS as f64;
        m_vals[i] = m_mean;
    }
    // Running the loop for h from 1.0 to -1.0
    for (i, h) in h_vals.iter().rev().enumerate() {
        println!("h: ({}/{NUM_DATAPOINTS})", i + HALF_NUM_DATAPOINTS);
        // Warmup
        for _ in 0..NUM_WARMUP_SWEEPS {
            sweep_heatbath(&mut state, BETA, *h);
        }

        let mut m: f64 = 0.0;
        for _ in 0..NUM_SWEEPS {
            sweep_heatbath(&mut state, BETA, *h);
            m += calc_m(&state);
        }
        h_vals_full[i + HALF_NUM_DATAPOINTS] = *h;
        let m_mean = m / NUM_SWEEPS as f64;
        m_vals[i + HALF_NUM_DATAPOINTS] = m_mean;
    }

    write_data::<L>(&h_vals_full, &m_vals, BETA);
}
