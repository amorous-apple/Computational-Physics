use std::io::Write;
pub fn write_data_thermalization<const L: usize>(
    beta_val: f64,
    sweep_index: &[usize],
    n_try_index: &[usize],
    energy_density: &[f64],
) {
    let target_dir = "./data_thermalization";
    std::fs::create_dir_all(target_dir).expect("Unable to create dir: {target_dir}");

    let filename = format!("{target_dir}/thermalization_beta{beta_val:.1}.csv");
    let mut fileout = std::fs::File::create(&filename).expect("Failed to create fileout");

    // Writing heading
    writeln!(fileout, "beta_val,sweep_index,n_try_index,energy_density")
        .expect("Unable to write heading to fileout");

    let num_steps = sweep_index.len();
    for step in 0..num_steps {
        writeln!(
            fileout,
            "{:.1},{:.6},{:.6},{:.6}",
            beta_val, sweep_index[step], n_try_index[step], energy_density[step],
        )
        .expect("Unable to write dataline to fileout");
    }

    println!("Printed thermalization_beta{beta_val:.1} to fileout.");
}
