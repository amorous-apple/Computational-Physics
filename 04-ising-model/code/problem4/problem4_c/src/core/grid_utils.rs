use rand::Rng;

use crate::core::evaluate_state::calc_h_sum;

// Printing a square matrix of states
pub fn _print_state<const L: usize>(state: &[[i8; L]; L]) {
    for row in state {
        for col in row {
            if *col == 1 {
                print!("@");
            } else {
                print!(".");
            }
        }
        println!();
    }
}

// Filling &mut state with the unique spin state corresponding to an index
pub fn _create_state<const L: usize>(state: &mut [[i8; L]; L], index: u64) {
    for (i, spin) in state.iter_mut().flatten().enumerate() {
        let bit = (index >> i) & 1;
        *spin = if bit == 1 { 1 } else { -1 };
    }
}

pub fn create_hot_state<const L: usize>() -> [[i8; L]; L] {
    let mut rng = rand::thread_rng();

    // Filling the state with random spins following a 50/50 chance
    std::array::from_fn(|_row| std::array::from_fn(|_col| if rng.gen_bool(0.5) { 1 } else { -1 }))
}

// Performing a sweep of the grid with the heatbath-algorithm
pub fn sweep_heatbath<const L: usize>(state: &mut [[i8; L]; L], beta: f64, h: f64) {
    let mut rng = rand::thread_rng();
    for row in 0..L {
        for col in 0..L {
            let delta = calc_h_sum(state, (row, col));
            let k = beta * (delta + h);
            let z = 2.0 * k.cosh();
            let q = k.exp() / z;

            let p_rand: f64 = rng.gen_range(0.0..1.0);

            if p_rand < q {
                // Flipping the spin if energy is decreased
                state[row][col] = 1;
            } else {
                state[row][col] = -1;
            }
        }
    }
}
