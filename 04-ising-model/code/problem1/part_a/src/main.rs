use rand::rngs::StdRng;
use rand::{Rng, SeedableRng}; // Import the SeedableRng trait // Import the Standard RNG struct

use std::fs::File;
use std::io::{BufWriter, Write};

fn main() -> std::io::Result<()> {
    const TRUE_PI: f64 = std::f64::consts::PI;

    // Create a generator seeded with a specific number (e.g., 42)
    let mut rng = StdRng::seed_from_u64(0);

    let file_out = File::create("pi_error.csv")?;
    let mut writer = BufWriter::new(file_out);

    writeln!(writer, "iteration,approximation,ln_error")?;

    let radius = 1.0;
    let num_points = 10_000_000;
    let mut num_points_in_circle = 0;
    for i in 1..=num_points {
        let x = rng.r#gen::<f64>();
        let y = rng.r#gen::<f64>();
        let r = x * x + y * y;
        if r < radius {
            num_points_in_circle += 1;
        }
        let pi_approx: f64 = 4.0 * (num_points_in_circle as f64) / (i as f64) as f64;
        let error = (TRUE_PI - pi_approx).abs();
        let log_error = error.ln();
        // println!("PI {:>3}: {:.8}", i, pi_approx);
        // println!("Error {:>3}: {:.4}", i, log_error);

        writeln!(writer, "{},{},{}", i, pi_approx, log_error)?;
    }

    writer.flush()?;

    println!("Data written to pi_error.csv");
    Ok(())
}
