#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helloneon-intrinsics.h"

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


#define  FIR_ITERATIONS    600
#define  FIR_KERNEL_SIZE   32
#define  FIR_OUTPUT_SIZE   256
#define  FIR_INPUT_SIZE    (FIR_OUTPUT_SIZE + FIR_KERNEL_SIZE)

static const short  fir_kernel[FIR_KERNEL_SIZE] = {
    0x10, 0x20, 0x40, 0x70, 0x8c, 0xa2, 0xce, 0xf0, 0xe9, 0xce, 0xa2, 0x8c, 070, 0x40, 0x20, 0x10,
    0x10, 0x20, 0x40, 0x70, 0x8c, 0xa2, 0xce, 0xf0, 0xe9, 0xce, 0xa2, 0x8c, 070, 0x40, 0x20, 0x10 };

/* return current time in milliseconds */
static double
now_ms(void)
{
    struct timespec res;
    clock_gettime(CLOCK_REALTIME, &res);
    return 1000.0 * res.tv_sec + (double)res.tv_nsec / 1e6;
}


/* this is a FIR filter implemented in C */
static void
fir_filter_c(short* output, const short* input, const short* kernel, int width, int kernelSize)
{
    int  offset = -kernelSize / 2;
    int  nn;
    for (nn = 0; nn < width; nn++) {
        int sum = 0;
        int mm;
        for (mm = 0; mm < kernelSize; mm++) {
            sum += kernel[mm] * input[nn + offset + mm];
        }
        output[nn] = (short)((sum + 0x8000) >> 16); // ”““∆Œª£∫≥˝“‘2^n
    }
}


int main1() {
  
    char buffer[512];
    double  t0, t1, time_c, time_neon;
    static short        fir_output[FIR_OUTPUT_SIZE];
    static short        fir_input_0[FIR_INPUT_SIZE];
    static const short* fir_input = fir_input_0 + (FIR_KERNEL_SIZE / 2);
    static short        fir_output_expected[FIR_OUTPUT_SIZE];

    /* setup FIR input - whatever */
    {
        int  nn;
        for (nn = 0; nn < FIR_INPUT_SIZE; nn++) {
            fir_input_0[nn] = (5 * nn) & 255;
        }
        fir_filter_c(fir_output_expected, fir_input, fir_kernel, FIR_OUTPUT_SIZE, FIR_KERNEL_SIZE);
    }
    /* Benchmark small FIR filter loop - C version */
   
    t0 = now_ms();
    {
        int  count = FIR_ITERATIONS;
        for (; count > 0; count--) {
            fir_filter_c(fir_output, fir_input, fir_kernel, FIR_OUTPUT_SIZE, FIR_KERNEL_SIZE);
        }
    }
    t1 = now_ms();
    time_c = t1 - t0;

    printf( "FIR Filter benchmark:\nC version          : %g ms\n", time_c);
    //strlcpy(buffer, str, sizeof buffer);
    
    time_c = 0;
    
   
    /* Benchmark small FIR filter loop - Neon version */
    t0 = now_ms();
    {
        int  count = FIR_ITERATIONS;
        for (; count > 0; count--) {
            fir_filter_neon_intrinsics(fir_output, fir_input, fir_kernel, FIR_OUTPUT_SIZE, FIR_KERNEL_SIZE);
        }
    }
    t1 = now_ms();
    time_neon = t1 - t0;
    printf("Neon version          :%g ms (x%g faster)\n", time_neon, time_c / (time_neon < 1e-6 ? 1. : time_neon));
    //strlcat(buffer, str, sizeof buffer);
    //free(str);

    /* check the result, just in case */
    {
        int  nn, fails = 0;
        for (nn = 0; nn < FIR_OUTPUT_SIZE; nn++) {
            if (fir_output[nn] != fir_output_expected[nn]) {
                if (++fails < 16)
                    D("neon[%d] = %d expected %d", nn, fir_output[nn], fir_output_expected[nn]);
            }
        }
        D("%d fails\n", fails);
    }

}