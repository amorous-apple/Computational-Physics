use rand::rngs::StdRng;
use rand::{Rng, SeedableRng}; // Import the SeedableRng trait // Import the Standard RNG struct

use std::fs::File;
use std::io::{BufWriter, Write};

const NUM_POINTS: u64 = 10_000;

fn main() -> std::io::Result<()> {
    const TRUE_PI: f64 = std::f64::consts::PI;

    // Create a generator seeded with a specific number (e.g., 42)
    let mut rng = StdRng::seed_from_u64(0);

    // Creating the output file and a file-writing-buffer
    let file_out = File::create("normal_distribution.csv")?;
    let mut writer = BufWriter::new(file_out);

    writeln!(writer, "iteration,random_num")?;

    for i in (1..=NUM_POINTS).step_by(2) {
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

        // Writing two random numbers to the buffer
        writeln!(writer, "{i},{z0}\n{},{z1}", i + 1)?;
    }

    writer.flush()?;

    println!("Data written to file");
    Ok(())
}
