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
pub fn create_state<const L: usize>(state: &mut [[i8; L]; L], index: u64) {
    for (i, spin) in state.iter_mut().flatten().enumerate() {
        let bit = (index >> i) & 1;
        *spin = if bit == 1 { 1 } else { -1 };
    }
}
