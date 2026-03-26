mod core;
use core::analytical::{calc_anal_energy_density, calc_anal_magnetization};
use core::evaluate_state::{calc_h, calc_m};
use core::file_io::write_data;
use core::grid_utils::create_state;

// Defining a macro to run the simulation for all given grid sizes
macro_rules! enter_the_matrix {
    ( $( $size:expr), *) => {
        $(
           println!("===================================");
           println!("Simulating L = {}",$size);
           println!("{} states possible",1 << ($size * $size));
           simulate_ising::<$size>();
        )*
    }
}

fn main() {
    enter_the_matrix!(2, 3, 4);
}

// Running the Ising-Simulation for grid size L
fn simulate_ising<const L: usize>() {
    let num_spins: usize = L * L;
    let num_states: u64 = 1 << num_spins;
    let mut state = [[0i8; L]; L];

    // Setting up the list of inverse temperatures to test (beta in [0,1.0])
    const NUM_STEPS: usize = 200;
    let beta_vals: [f64; NUM_STEPS] =
        std::array::from_fn(|step| step as f64 / (NUM_STEPS - 1) as f64);

    let mut z_vals: [f64; NUM_STEPS] = [0.0; NUM_STEPS]; // Z

    let mut expectval_h: [f64; NUM_STEPS] = [0.0; NUM_STEPS]; // <H>
    let mut energy_density: [f64; NUM_STEPS] = [0.0; NUM_STEPS]; // epsilon = <H> / L^2
    let mut anal_energy_density: [f64; NUM_STEPS] = [0.0; NUM_STEPS]; // epsilon
    //
    let mut expectval_m: [f64; NUM_STEPS] = [0.0; NUM_STEPS]; // <m>
    let mut expectval_m_abs: [f64; NUM_STEPS] = [0.0; NUM_STEPS]; // <|m|>
    let mut anal_m: [f64; NUM_STEPS] = [0.0; NUM_STEPS]; // <|m|>

    // Creating a unique state for every num_states
    for index in 0..num_states {
        create_state(&mut state, index);
        let h = calc_h(&state);
        let m = calc_m(&state);
        // println!("========================");
        // println!("index: {index}, h: {h}, m: {m}");
        // print_state(&state);

        // Calculating running values for h, m, and |m| at every temp
        for temp in 0..NUM_STEPS {
            let weight: f64 = (-beta_vals[temp] * h as f64).exp();
            z_vals[temp] += weight;
            expectval_h[temp] += weight * h as f64;
            expectval_m[temp] += weight * m;
            expectval_m_abs[temp] += weight * m.abs();
        }
    }

    // Normalizing all of the desired measurements and calculating analytical values
    for (i, z) in z_vals.iter().enumerate() {
        expectval_h[i] /= z;
        energy_density[i] = expectval_h[i] / num_spins as f64;
        anal_energy_density[i] = calc_anal_energy_density(beta_vals[i]);

        expectval_m[i] /= z;
        expectval_m_abs[i] /= z;
        anal_m[i] = calc_anal_magnetization(beta_vals[i]);
    }

    write_data::<L>(
        &beta_vals,
        &energy_density,
        &anal_energy_density,
        &expectval_m,
        &expectval_m_abs,
        &anal_m,
    );
}
