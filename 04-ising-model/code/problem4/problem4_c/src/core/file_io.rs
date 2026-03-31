use std::io::Write;

pub fn write_data<const L: usize>(
    beta_vals: &[f64],
    h_vals: &[f64],
    magnetization: &[f64],
    magnetization_abs: &[f64],
) {
    let target_dir = "./data";
    std::fs::create_dir_all(target_dir).expect("Unable to create target_dir");

    let filename = format!("{target_dir}/ising_L{L}.csv");
    let mut fileout = std::fs::File::create(&filename).expect("Failed to create fileout");

    // Writing heading
    writeln!(
        fileout,
        "beta_value,h_value,magnetization,magnetization_abs"
    )
    .expect("Unable to write heading to fileout");

    let num_steps = beta_vals.len();
    for step in 0..num_steps {
        writeln!(
            fileout,
            "{:.6},{:.6},{:.6},{:.6}",
            beta_vals[step], h_vals[step], magnetization[step], magnetization_abs[step],
        )
        .expect("Unable to write dataline to fileout");
    }

    println!("Printed ising_L{L} to fileout.");
}
