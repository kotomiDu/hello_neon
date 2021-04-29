#pragma once

void VpFloat1DAdd(float* output, int size, const float* input1, const float* input2);
void VpFloat1DSub(float* output, int size, const float* input1, const float* input2);
void VpFloat1DMul(float* output, int size, const float* input1, float input2);
void VpFloat1DMul(float* output, int size, const float* input1, const float* input2);
void VpFloat1DDiv(float* output, int size, const float* input1, float input2);

void cVpFloat1DAdd(float* output, int size, const float* input1, const float* input2);
void cVpFloat1DSub(float* output, int size, const float* input1, const float* input2);
void cVpFloat1DMul(float* output, int size, const float* input1, float input2);
void cVpFloat1DMul(float* output, int size, const float* input1, const float* input2);
void cVpFloat1DDiv(float* output, int size, const float* input1, float input2);