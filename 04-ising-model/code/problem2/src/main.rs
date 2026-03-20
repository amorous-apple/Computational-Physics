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
    // enter_the_matrix!(2, 3);
    enter_the_matrix!(2);
}

// Running the Ising-Simulation for grid size L
fn simulate_ising<const L: usize>() {
    let num_spins: usize = L * L;
    let num_states: usize = 1 << num_spins;

    // Creating a unique state for every num_states
    for index in 0..num_states {
        let mut state = [[0i8; L]; L];
        for row in 0..L {
            for col in 0..L {
                let spin = ((index >> (row * L + col)) & 1) as i8;
                if spin == 1 {
                    state[row][col] = 1;
                } else {
                    state[row][col] = -1;
                }
            }
        }
        println!("========================");
        println!("index: {index}");
        print_states(&state);
    }
}

// Printing a square matrix of states
fn print_states<const L: usize>(state: &[[i8; L]; L]) {
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
