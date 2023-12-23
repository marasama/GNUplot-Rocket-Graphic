#include <stdio.h>
#include <complex.h>

int main() {
    double Rocket_W = 15;   // kg
    double Fuel_W = 6;      // kg
    double Fuel_Burn = 3;   // kg/s
    double g = 9.81;        // m/s^2
    double Sum_W = Rocket_W + Fuel_W;
    double time = Fuel_W / Fuel_Burn;
    double thrust_weight_ratio = 2;        // thrust weight ratio
    double v_e = (g * Sum_W * thrust_weight_ratio) / Fuel_Burn;   // m/s
    double S = 0;
    int k = 0;

    // Open a file for writing
    FILE *data = fopen("data.txt", "w");
    FILE *plot = popen("gnuplot -persist", "w");

    fprintf(plot, "set term wxt persist\n");
    fprintf(plot, "set title \"Velocity vs Time\"\n");
    for (double t = 0.01; t <= time; t += 0.01) {
        double Gravity_Velocity = g * t;
        // Use complex logarithm to handle negative or zero values
        double complex ln_term = clog(Sum_W / (Sum_W * (1 - Fuel_Burn * t)));
        double v = v_e * cabs(ln_term) - Gravity_Velocity;

        if (v >= v_e && k == 0)
            k = 1;
        else {
            if (k != 1)
                v = 0;
        }
        // Write data to the file
        fprintf(data, "%f %f\n", t, v);
        fflush(data);
        S += v / 100;
    }
    fprintf(plot, "plot 'data.txt' using 1:2 with lines lw 3\n");
    fflush(plot);
    fclose(data);
    return 0;
}
