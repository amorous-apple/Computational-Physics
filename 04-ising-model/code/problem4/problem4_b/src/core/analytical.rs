pub fn calc_anal_energy_density(beta: f64) -> f64 {
    if beta == 0.0 {
        return 0.0;
    }
    let coth_term: f64 = 1.0 / (-(2.0 * beta).tanh());
    let tanh_term: f64 = 2.0 * (2.0 * beta).tanh().powf(2.0) - 1.0;

    let xi: f64 = 2.0 * (2.0 * beta).tanh() / (2.0 * beta).cosh();
    let xi_sqr: f64 = xi * xi;
    let k_term: f64 = (2.0 / std::f64::consts::PI) * calc_elliptical(xi_sqr);

    coth_term * (1.0 + tanh_term * k_term)
}

// Calculating the analytical value of a complete elliptical integral of the first kind through the
// AGM (Arithmetic-Geometric Mean) method (https://en.wikipedia.org/wiki/Elliptic_integral)
fn calc_elliptical(xi_sqr: f64) -> f64 {
    let mut a: f64 = 1.0;
    let mut g: f64 = (1.0 - xi_sqr).sqrt();

    while (a - g).abs() > 10E-7 {
        let a1 = 0.5 * (a + g);
        let g1 = (a * g).sqrt();
        a = a1;
        g = g1;
    }

    std::f64::consts::PI / (2.0 * a)
}

pub fn calc_anal_magnetization(beta: f64) -> f64 {
    let beta_crit: f64 = 0.440687;
    // Return 0 magnetization above the critical temperature
    if beta < beta_crit {
        return 0.0;
    }

    let inner: f64 = 1.0 - (2.0 * beta).sinh().powf(-4.0);
    inner.powf(1.0 / 8.0)
}
