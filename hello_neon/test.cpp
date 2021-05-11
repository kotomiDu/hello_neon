#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "helloneon-intrinsics.h"
#include "vpmath.h"
#include <chrono>

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define  D(...)  do {} while (0)

#define TEST_SIZE 257
#define  FIR_ITERATIONS    600000

int main() {

    char buffer[512];
    std::chrono::steady_clock::time_point begin, end;
    double  t0, t1, time_c, time_neon;
    float input1[TEST_SIZE];
    float input2[TEST_SIZE];
    float output[TEST_SIZE];
    float output_expected[TEST_SIZE];

    /* setup  input - whatever */
    {
        srand((unsigned int)time(NULL));
        int  nn;
        float a = 5.0;
        for (nn = 0; nn < TEST_SIZE; nn++) {
            input1[nn] = (float(rand()) / float((RAND_MAX)) * a);
            input2[nn] = (float(rand()) / float((RAND_MAX)) * a);
        }
    }




    /* Benchmark loop - C++ version */

    begin = std::chrono::steady_clock::now();
    {
        int  count = FIR_ITERATIONS;
        for (; count > 0; count--) {
            cVpFloat1DAdd(output_expected, TEST_SIZE, input1, input2);
        }
    }
    end = std::chrono::steady_clock::now();
    time_c = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
    printf("cVpFloat1DAdd         :%g ms\n", time_c);


    /* Benchmark loop - Neon version */
    begin = std::chrono::steady_clock::now();
    {
        int  count = FIR_ITERATIONS;
        for (; count > 0; count--) {
            VpFloat1DAdd(output, TEST_SIZE, input1, input2);
        }
    }
    end = std::chrono::steady_clock::now();
    time_neon = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
    printf("VpFloat1DAdd          :%g ms (x%g faster)\n", time_neon, time_c / (time_neon < 1e-6 ? 1. : time_neon));

    /* check the result, just in case */
    {
        int  nn, fails = 0;
        for (nn = 0; nn < TEST_SIZE; nn++) {
            if (output[nn] != output_expected[nn]) {
                if (++fails < 16)
                    D("neon[%d] = %d expected %d", nn, fir_output[nn], fir_output_expected[nn]);
            }
        }
        D("%d fails\n", fails);
    }
    // print output to avoid compiler over-optimization
    printf("%.2f, %.2f\n", output[TEST_SIZE - 1], output_expected[TEST_SIZE - 1]);

    /* Benchmark loop - C++ version */
    begin = std::chrono::steady_clock::now();
    {
        int  count = FIR_ITERATIONS;
        for (; count > 0; count--) {
            cVpFloat1DSub(output_expected, TEST_SIZE, input1, input2);
        }
    }
    end = std::chrono::steady_clock::now();
    time_c = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
    printf("cVpFloat1DSub         :%g ms\n", time_c);

    /* Benchmark loop - Neon version */
    begin = std::chrono::steady_clock::now();
    {
        int  count = FIR_ITERATIONS;
        for (; count > 0; count--) {
            VpFloat1DSub(output, TEST_SIZE, input1, input2);
        }
    }
    end = std::chrono::steady_clock::now();
    time_neon = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
    printf("VpFloat1DSub          :%g ms (x%g faster)\n", time_neon, time_c / (time_neon < 1e-6 ? 1. : time_neon));

    /* check the result, just in case */
    {
        int  nn, fails = 0;
        for (nn = 0; nn < TEST_SIZE; nn++) {
            if (output[nn] != output_expected[nn]) {
                if (++fails < 16)
                    D("neon[%d] = %d expected %d", nn, fir_output[nn], fir_output_expected[nn]);
            }
        }
        D("%d fails\n", fails);
    }
    // print output to avoid compiler over-optimization
    printf("%.2f, %.2f\n", output[0], output_expected[0]);
    /* Benchmark loop - C++ version */
    begin = std::chrono::steady_clock::now();
    {
        int  count = FIR_ITERATIONS;
        for (; count > 0; count--) {
            cVpFloat1DMul(output_expected, TEST_SIZE, input1, input2[0]);
        }
    }
    end = std::chrono::steady_clock::now();
    time_c = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
    printf("cVpFloat1DMul         :%g ms\n", time_c);

    /* Benchmark loop - Neon version */
    begin = std::chrono::steady_clock::now();
    {
        int  count = FIR_ITERATIONS;
        for (; count > 0; count--) {
            VpFloat1DMul(output, TEST_SIZE, input1, input2[0]);
        }
    }
    end = std::chrono::steady_clock::now();
    time_neon = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
    printf("VpFloat1DMul          :%g ms (x%g faster)\n", time_neon, time_c / (time_neon < 1e-6 ? 1. : time_neon));

    /* check the result, just in case */
    {
        int  nn, fails = 0;
        for (nn = 0; nn < TEST_SIZE; nn++) {
            if (output[nn] != output_expected[nn]) {
                if (++fails < 16)
                    D("neon[%d] = %d expected %d", nn, fir_output[nn], fir_output_expected[nn]);
            }
        }
        D("%d fails\n", fails);
    }
    // print output to avoid compiler over-optimization
    printf("%.2f, %.2f\n", output[0], output_expected[0]);
    /* Benchmark loop - C++ version */
    begin = std::chrono::steady_clock::now();
    {
        int  count = FIR_ITERATIONS;
        for (; count > 0; count--) {
            cVpFloat1DMul(output_expected, TEST_SIZE, input1, input2);
        }
    }
    end = std::chrono::steady_clock::now();
    time_c = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
    printf("cVpFloat1DMul         :%g ms\n", time_c);

    /* Benchmark loop - Neon version */
    begin = std::chrono::steady_clock::now();
    {
        int  count = FIR_ITERATIONS;
        for (; count > 0; count--) {
            VpFloat1DMul(output, TEST_SIZE, input1, input2);
        }
    }
    end = std::chrono::steady_clock::now();
    time_neon = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
    printf("VpFloat1DMul          :%g ms (x%g faster)\n", time_neon, time_c / (time_neon < 1e-6 ? 1. : time_neon));

    /* check the result, just in case */
    {
        int  nn, fails = 0;
        for (nn = 0; nn < TEST_SIZE; nn++) {
            if (output[nn] != output_expected[nn]) {
                if (++fails < 16)
                    D("neon[%d] = %d expected %d", nn, fir_output[nn], fir_output_expected[nn]);
            }
        }
        D("%d fails\n", fails);
    }
    // print output to avoid compiler over-optimization
    printf("%.2f, %.2f\n", output[0], output_expected[0]);
    /* Benchmark loop - C++ version */
    begin = std::chrono::steady_clock::now();
    {
        int  count = FIR_ITERATIONS;
        for (; count > 0; count--) {
            cVpFloat1DDiv(output_expected, TEST_SIZE, input1, input2[0]);
        }
    }
    end = std::chrono::steady_clock::now();
    time_c = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
    printf("cVpFloat1DDiv         :%g ms\n", time_c);

    /* Benchmark loop - Neon version */
    begin = std::chrono::steady_clock::now();
    {
        int  count = FIR_ITERATIONS;
        for (; count > 0; count--) {
            VpFloat1DDiv(output, TEST_SIZE, input1, input2[0]);
        }
    }
    end = std::chrono::steady_clock::now();
    time_neon = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
    printf("VpFloat1DDiv          :%g ms (x%g faster)\n", time_neon, time_c / (time_neon < 1e-6 ? 1. : time_neon));

    /* check the result, just in case */
    {
        int  nn, fails = 0;
        for (nn = 0; nn < TEST_SIZE; nn++) {
            if (output[nn] != output_expected[nn]) {
                if (++fails < 16)
                    D("neon[%d] = %d expected %d", nn, fir_output[nn], fir_output_expected[nn]);
            }
        }
        D("%d fails\n", fails);
    }
    // print output to avoid compiler over-optimization
    printf("%.2f, %.2f\n", output[0], output_expected[0]);


}