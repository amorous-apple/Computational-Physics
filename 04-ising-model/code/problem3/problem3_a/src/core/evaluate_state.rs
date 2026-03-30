// Calculating H for a single state (J = 1, h = 0)
pub fn calc_h<const L: usize>(state: &[[i8; L]; L]) -> i32 {
    let mut h_val: i32 = 0;
    for row in 0..L {
        for col in 0..L {
            // NOTE: Only counting spins below and to the right of the current location. This
            // simplification is valid due to the periodic boundary conditions. If we consider the
            // bonds in all four directions, then we would need to divide the result by two in the
            // end to account for double-counted interactions.
            let cell_spin = state[row][col];
            h_val += (cell_spin * state[(row + 1) % L][col]) as i32;
            h_val += (cell_spin * state[row][(col + 1) % L]) as i32;
        }
    }
    -h_val
}

// Calculating the energy change from flipping a single spin
pub fn calc_dh<const L: usize>(state: &[[i8; L]; L], position: (usize, usize)) -> f64 {
    let row = position.0;
    let col = position.1;
    let s_neighbors: i8 = state[(row + 1) % L][col]
        + state[row][(col + 1) % L]
        + state[(row + L - 1) % L][col]
        + state[row][(col + L - 1) % L];
    2.0 * state[row][col] as f64 * s_neighbors as f64
}
