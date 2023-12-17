#include <stdio.h>
#include <math.h>
#include <complex.h>

int main() {
    double Rocket_W = 15;   // kg
    double Fuel_W = 6;      // kg
    double Fuel_Burn = 3;   // kg/s
    double g = 9.81;        // m/s^2
    double Sum_W = Rocket_W + Fuel_W;
    double time = Fuel_W / Fuel_Burn;
    double v_t[100 * (int)time][2];
    double t_W_r = 2;        // thrust weight ratio
    double v_e = (g * Sum_W * t_W_r) / Fuel_Burn;   // m/s
    double S = 0;
    int k = 0;

    // Open a file for writing
    FILE *data = fopen("data.txt", "w");
	FILE *plot = popen("gnuplot -persist", "w");


	fprintf(plot, "set term wxt persist\n");
	fprintf(plot, "set title \"Velocity vs Time\"\n");

    if (data == NULL) {
        fprintf(stderr, "Error opening output file.\n");
        return 1;
    }

    for (double t = 0; t <= time; t += 0.01) {
        double Gravity_Velocity = g * t;
    	double ln_term = log(Sum_W / (Sum_W * (1 - Fuel_Burn * t)));
    	double v = v_e * (fabs(ln_term)) - Gravity_Velocity;

        if (v >= v_e && k == 0)
            k = 1;
		else
		{
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
