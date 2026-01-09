// File: vector_add.cu

#include <iostream>
#include <cuda_runtime.h>

// CUDA kernel to add two vectors
__global__ void
vectorAdd(const float * A, const float * B, float * C, int N)
{
  int i = blockDim.x * blockIdx.x + threadIdx.x;
  if (i < N)
    C[i] = A[i] + B[i];
}

int
main()
{
  int N = 1 << 20; // 1M elements
  size_t size = N * sizeof(float);

  // Allocate memory on host
  float * h_A = (float *)malloc(size);
  float * h_B = (float *)malloc(size);
  float * h_C = (float *)malloc(size);

  // Initialize input vectors
  for (int i = 0; i < N; ++i)
  {
    h_A[i] = static_cast<float>(i);
    h_B[i] = static_cast<float>(2 * i);
  }

  // Allocate memory on device
  float *d_A, *d_B, *d_C;
  cudaMalloc(&d_A, size);
  cudaMalloc(&d_B, size);
  cudaMalloc(&d_C, size);

  // Copy data from host to device
  cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
  cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

  // Launch kernel
  int threadsPerBlock = 256;
  int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;
  vectorAdd<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);

  // Copy result back to host
  cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

  // Verify results
  for (int i = 0; i < 5; ++i)
    std::cout << "h_C[" << i << "] = " << h_C[i] << std::endl;

  // Cleanup
  cudaFree(d_A);
  cudaFree(d_B);
  cudaFree(d_C);
  free(h_A);
  free(h_B);
  free(h_C);

  return 0;
}
