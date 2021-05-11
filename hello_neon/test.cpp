#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helloneon-intrinsics.h"
#include "vpmath.h"


#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>


#define CLOCK_REALTIME 0
//struct timespec { long tv_sec; long tv_nsec; };    //header part
static int clock_gettime(int, struct timespec* spec)      //C-file part
{
    __int64 wintime; GetSystemTimeAsFileTime((FILETIME*)&wintime);
    wintime -= 116444736000000000i64;  //1jan1601 to 1jan1970
    spec->tv_sec = wintime / 10000000i64;           //seconds
    spec->tv_nsec = wintime % 10000000i64 * 100;      //nano-seconds
    return 0;
}


#define  D(...)  do {} while (0)

#define TEST_SIZE 257
#define  FIR_ITERATIONS    600000

/* return current time in milliseconds */
static double
now_ms(void)
{
    struct timespec res;
    clock_gettime(CLOCK_REALTIME, &res);
    return 1000.0 * res.tv_sec + (double)res.tv_nsec / 1e6;
}



int main() {

    char buffer[512];
    double  t0, t1, time_c, time_neon;
    float input1[TEST_SIZE];
    float input2[TEST_SIZE];
    float output[TEST_SIZE];
    float output_expected[TEST_SIZE];

    /* setup  input - whatever */
    {
        int  nn;
        for (nn = 0; nn < TEST_SIZE; nn++) {
           
            input1[nn] = static_cast <float> (rand());
            input2[nn] = static_cast <float> (rand());
        }
    }


    time_c = 0;

    /* Benchmark loop - C++ version */
    t0 = now_ms();
    {
        int  count = FIR_ITERATIONS;
        for (; count > 0; count--) {
            cVpFloat1DAdd(output_expected, TEST_SIZE, input1, input2);
        }
    }
    t1 = now_ms();
    time_c = t1 - t0;
    printf("cVpFloat1DAdd         :%g ms\n", time_c);

    /* Benchmark loop - Neon version */
    t0 = now_ms();
    {
        int  count = FIR_ITERATIONS;
        for (; count > 0; count--){
            VpFloat1DAdd(output, TEST_SIZE, input1, input2);
        }
    }
    t1 = now_ms();
    time_neon = t1 - t0;
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

    /* Benchmark loop - C++ version */
    t0 = now_ms();
    {
        int  count = FIR_ITERATIONS;
        for (; count > 0; count--) {
            cVpFloat1DSub(output_expected, TEST_SIZE, input1, input2);
        }
    }
    t1 = now_ms();
    time_c = t1 - t0;
    printf("cVpFloat1DSub         :%g ms\n", time_c);

    /* Benchmark loop - Neon version */
    t0 = now_ms();
    {
        int  count = FIR_ITERATIONS;
        for (; count > 0; count--) {
            VpFloat1DSub(output, TEST_SIZE, input1, input2);
        }
    }
    t1 = now_ms();
    time_neon = t1 - t0;
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

    /* Benchmark loop - C++ version */
    t0 = now_ms();
    {
        int  count = FIR_ITERATIONS;
        for (; count > 0; count--) {
            cVpFloat1DMul(output_expected, TEST_SIZE, input1, input2[0]);
        }
    }
    t1 = now_ms();
    time_c = t1 - t0;
    printf("cVpFloat1DMul         :%g ms\n", time_c);

    /* Benchmark loop - Neon version */
    t0 = now_ms();
    {
        int  count = FIR_ITERATIONS;
        for (; count > 0; count--) {
            VpFloat1DMul(output, TEST_SIZE, input1, input2[0]);
        }
    }
    t1 = now_ms();
    time_neon = t1 - t0;
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

    /* Benchmark loop - C++ version */
    t0 = now_ms();
    {
        int  count = FIR_ITERATIONS;
        for (; count > 0; count--) {
            cVpFloat1DMul(output_expected, TEST_SIZE, input1, input2);
        }
    }
    t1 = now_ms();
    time_c = t1 - t0;
    printf("cVpFloat1DMul         :%g ms\n", time_c);

    /* Benchmark loop - Neon version */
    t0 = now_ms();
    {
        int  count = FIR_ITERATIONS;
        for (; count > 0; count--) {
            VpFloat1DMul(output, TEST_SIZE, input1, input2);
        }
    }
    t1 = now_ms();
    time_neon = t1 - t0;
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

    /* Benchmark loop - C++ version */
    t0 = now_ms();
    {
        int  count = FIR_ITERATIONS;
        for (; count > 0; count--) {
            cVpFloat1DDiv(output_expected, TEST_SIZE, input1, input2[0]);
        }
    }
    t1 = now_ms();
    time_c = t1 - t0;
    printf("cVpFloat1DDiv         :%g ms\n", time_c);

    /* Benchmark loop - Neon version */
    t0 = now_ms();
    {
        int  count = FIR_ITERATIONS;
        for (; count > 0; count--) {
            VpFloat1DDiv(output, TEST_SIZE, input1, input2[0]);
        }
    }
    t1 = now_ms();
    time_neon = t1 - t0;
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
    printf("%f", output[0]);
    printf("%f", output_expected[0]);

}