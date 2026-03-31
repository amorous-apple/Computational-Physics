use std::io::Write;

pub fn write_data<const L: usize>(
    beta_vals: &[f64],
    energy_density: &[f64],
    anal_energy_density: &[f64],
    magnetization: &[f64],
    anal_m: &[f64],
    specific_heat: &[f64],
) {
    let target_dir = "./data";
    std::fs::create_dir_all(target_dir).expect("Unable to create target_dir");

    let filename = format!("{target_dir}/ising_L{L}.csv");
    let mut fileout = std::fs::File::create(&filename).expect("Failed to create fileout");

    // Writing heading
    writeln!(
        fileout,
        "beta_vals,energy_density,anal_energy_density,m,anal_m,specific_heat"
    )
    .expect("Unable to write heading to fileout");

    let num_steps = beta_vals.len();
    for temp in 0..num_steps {
        writeln!(
            fileout,
            "{:.6},{:.6},{:.6},{:.6},{:.6},{:.6}",
            beta_vals[temp],
            energy_density[temp],
            anal_energy_density[temp],
            magnetization[temp],
            anal_m[temp],
            specific_heat[temp],
        )
        .expect("Unable to write dataline to fileout");
    }

    println!("Printed ising_L{L} to fileout.");
}
