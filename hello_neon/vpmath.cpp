#define USE_NEON_2_SSE
#ifdef USE_NEON_2_SSE
#include "helloneon-intrinsics.h"
#include "NEON_2_SSE.h"
#endif

#include "vpmath.h"
#include "helloneon-intrinsics.h"
#include "NEON_2_SSE.h"
void VpFloat1DAdd(float* output, int size, const float* input1, const float* input2){
#ifdef USE_NEON_2_SSE
	//printf("VpFloat1DAdd\n");
	float32x4_t res, v1_vec, v2_vec;
	int j;
	int M = size - 4;
	for (j = 0; j <= M; j += 4)
	{
		v1_vec = vld1q_f32((input1)+j);
		v2_vec = vld1q_f32(input2 + j);
		res = vaddq_f32(v1_vec, v2_vec);
		vst1q_f32(output + j, res);
	}
	if (size & 3)
	{
		for (; j < size; ++j) {
			output[j] = input1[j] + input2[j];
		}
	}

#else
	for(int i = 0; i < size; ++i){
		output[i] = input1[i] + input2[i];
	}
#endif
}

void VpFloat1DSub(float* output, int size, const float* input1, const float* input2){
#ifdef USE_NEON_2_SSE
	float32x4_t res, v1_vec, v2_vec;
	int j;
	int M = size - 4;
	for (j = 0; j <= M; j += 4)
	{
		v1_vec = vld1q_f32((input1)+j);
		v2_vec = vld1q_f32(input2+j);
		res = vsubq_f32(v1_vec, v2_vec);
		vst1q_f32(output + j, res);
	}
	if (size & 3)
	{
		for (; j < size; ++j) {
			output[j] = input1[j] - input2[j];
		}
	}

#else
	for(int i = 0; i < size; ++i){
		output[i] = input1[i] - input2[i];
	}
#endif
}

void VpFloat1DMul(float* output, int size, const float* input1, float input2){
#ifdef USE_NEON_2_SSE
	float32x4_t res, v1_vec, v2_vec;
	int j;
	int M = size - 4;
	v2_vec = vdupq_n_f32(input2);
	for (j = 0; j <= M; j += 4)
	{
		v1_vec = vld1q_f32((input1)+j);		
		res = vmulq_f32(v1_vec, v2_vec);
		vst1q_f32(output + j, res);
	}
	if (size & 3)
	{
		for (; j < size; ++j) {
			output[j] = input1[j] * input2;
		}
	}

#else
	for(int i = 0; i < size; ++i){
		output[i] = input1[i] * input2;
	}
#endif
}

void VpFloat1DMul(float* output, int size, const float* input1, const float* input2){
#ifdef USE_NEON_2_SSE
	float32x4_t res, v1_vec, v2_vec;
	int j;
	int M = size - 4;
	for (j = 0; j <= M; j += 4)
	{
		v1_vec = vld1q_f32((input1)+j);
		v2_vec = vld1q_f32((input2)+j);
		res = vmulq_f32(v1_vec, v2_vec);
		vst1q_f32(output + j,res);
	}
	if (size & 3)
	{
		for (; j < size; ++j) {
			output[j] = input1[j] * input2[j];
		}
	}

#else
	for(int i = 0; i < size; ++i){
		output[i] = input1[i] * input2[i];
	}
#endif
}

void VpFloat1DDiv(float* output, int size, const float* input1, float input2){
#ifdef USE_NEON_2_SSE
	float32x4_t res, v1_vec, v2_vec;
	int j;
	int M = size - 4;
	v2_vec = vdupq_n_f32(1.0f/input2);
	for (j = 0; j <= M; j += 4)
	{
		v1_vec = vld1q_f32((input1)+j);
		res = vmulq_f32(v1_vec, v2_vec);
		vst1q_f32(output + j, res);
	}
	if (size & 3)
	{
		for (; j < size; ++j) {
			output[j] = input1[j] / input2;
		}
	}
#else
	for(int i = 0; i < size; ++i)	{
		output[i] = input1[i] / input2;
	}
#endif
}


void cVpFloat1DAdd(float* output, int size, const float* input1, const float* input2) {
	for (int i = 0; i < size; ++i) {
		output[i] = input1[i] + input2[i];
	}
}

void cVpFloat1DSub(float* output, int size, const float* input1, const float* input2) {
	for (int i = 0; i < size; ++i) {
		output[i] = input1[i] - input2[i];
	}
}

void cVpFloat1DMul(float* output, int size, const float* input1, float input2) {
	for (int i = 0; i < size; ++i) {
		output[i] = input1[i] * input2;
	}
}

void cVpFloat1DMul(float* output, int size, const float* input1, const float* input2) {

	for (int i = 0; i < size; ++i) {
		output[i] = input1[i] * input2[i];
	}
}

void cVpFloat1DDiv(float* output, int size, const float* input1, float input2) {
	for (int i = 0; i < size; ++i) {
		output[i] = input1[i] / input2;
	}
}

