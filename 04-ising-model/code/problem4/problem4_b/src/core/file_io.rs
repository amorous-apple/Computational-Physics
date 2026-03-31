use std::io::Write;

pub fn write_data<const L: usize>(h_vals: &[f64], magnetization: &[f64], beta: f64) {
    let target_dir = "./data";
    std::fs::create_dir_all(target_dir).expect("Unable to create target_dir");

    let filename = format!("{target_dir}/hysteresis_L{L}_Beta{beta}.csv");
    let mut fileout = std::fs::File::create(&filename).expect("Failed to create fileout");

    // Writing heading
    writeln!(fileout, "h_value,magnetization").expect("Unable to write heading to fileout");

    let num_steps = h_vals.len();
    for h in 0..num_steps {
        writeln!(fileout, "{:.6},{:.6}", h_vals[h], magnetization[h],)
            .expect("Unable to write dataline to fileout");
    }

    println!("Printed ising_L{L} to fileout.");
}
