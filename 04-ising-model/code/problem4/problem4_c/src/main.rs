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
    const NUM_SWEEPS: usize = 500;
    const NUM_WARMUP_SWEEPS: usize = 100;

    let mut state: [[i8; L]; L] = create_hot_state();

    const NUM_BETA_STEPS: usize = 50;
    // Setting up the list of inverse temperatures to test (beta in [0,1.0])
    let beta_vals: [f64; NUM_BETA_STEPS] =
        std::array::from_fn(|step| step as f64 / (NUM_BETA_STEPS - 1) as f64);

    const NUM_H_STEPS: usize = 50;
    // Creating a range of h_vals from -1.0 to 1.0
    let h_vals: [f64; NUM_H_STEPS] =
        std::array::from_fn(|x| -1.0 + 2.0 * (x as f64 / (NUM_H_STEPS - 1) as f64));

    const NUM_DATAPOINTS: usize = NUM_BETA_STEPS * NUM_H_STEPS;
    let mut data_beta: Vec<f64> = Vec::with_capacity(NUM_DATAPOINTS);
    let mut data_h: Vec<f64> = Vec::with_capacity(NUM_DATAPOINTS);
    let mut data_mag: Vec<f64> = Vec::with_capacity(NUM_DATAPOINTS);
    let mut data_mag_abs: Vec<f64> = Vec::with_capacity(NUM_DATAPOINTS);

    for (i, beta) in beta_vals.iter().enumerate() {
        println!("running beta {i}/{NUM_BETA_STEPS}");
        for h in h_vals {
            data_beta.push(*beta);
            data_h.push(h);
            // Warmup
            for _ in 0..NUM_WARMUP_SWEEPS {
                sweep_heatbath(&mut state, *beta, h);
            }
            let mut running_m: f64 = 0.0;
            let mut running_m_abs: f64 = 0.0;
            for _ in 0..NUM_SWEEPS {
                sweep_heatbath(&mut state, *beta, h);
                let current_m = calc_m(&state);
                running_m += current_m;
                running_m_abs += current_m.abs();
            }
            let m = running_m / NUM_SWEEPS as f64;
            let m_abs = running_m_abs / NUM_SWEEPS as f64;
            data_mag.push(m);
            data_mag_abs.push(m_abs);
        }
    }
    write_data::<L>(&data_beta, &data_h, &data_mag, &data_mag_abs);
}
