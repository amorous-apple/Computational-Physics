use rand::rngs::StdRng;
use rand::{Rng, SeedableRng}; // Import the SeedableRng trait // Import the Standard RNG struct

use std::fs::File;
use std::io::{BufWriter, Write};

const NUM_POINTS: usize = 10_000_000;

fn main() {
    // Creating an array to store normally distributed x-values
    let mut x_arr = vec![0.0_f64; NUM_POINTS];

    const TRUE_PI: f64 = std::f64::consts::PI;

    // Create a generator seeded with a specific number (e.g., 42)
    let mut rng = StdRng::seed_from_u64(0);

    for i in (0..NUM_POINTS).step_by(2) {
        // Generating two uniformly distributed random numbers and performing a Box-Muller
        // transform to create two normally-distributed random numbers z0 and z1

        // mu is the desired average of the distribution and sigma the width
        let mu = 0.0;
        let sigma = 1.0;

        let x = rng.r#gen::<f64>();
        let y = rng.r#gen::<f64>();

        let r: f64 = sigma * (-2.0 * x.ln()).sqrt();
        let theta: f64 = 2.0 * TRUE_PI * y;

        let z0 = r * theta.cos() + mu;
        let z1 = r * theta.sin() + mu;

        x_arr[i] = z0;
        x_arr[i + 1] = z1;
    }

    let mut func_arr = vec![0.0_f64; NUM_POINTS];

    // Calculating cos(x) for all x-values
    for i in 0..NUM_POINTS {
        func_arr[i] = x_arr[i].cos();
    }

    let mut running_total: f64 = 0.0;

    let integral_val = (-0.5_f64).exp();

    // Writing the data to file
    let file_out = File::create("integral_error.csv").expect("Error creating file_out");
    let mut writer = BufWriter::new(file_out);

    writeln!(writer, "iteration,approximation,ln_error").expect("Error writing header to file");

    // Calculating an array of the running integral estimate
    for i in 0..NUM_POINTS {
        running_total += func_arr[i];
        let integral_estimate: f64 = running_total / (i + 1) as f64;

        let integral_lnerror = (integral_estimate - integral_val).abs().ln();

        writeln!(
            writer,
            "{},{},{}",
            i + 1,
            integral_estimate,
            integral_lnerror
        )
        .expect("Error writing data to file");
    }
    writer.flush().expect("Error flushing to buff");

    println!("Data written to integral_error.csv");
}
