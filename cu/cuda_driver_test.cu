#include <cuda.h>
#include <iostream>

int
main()
{
  CUresult res;

  // Initialize the CUDA driver API
  res = cuInit(0);
  if (res != CUDA_SUCCESS)
  {
    std::cerr << "cuInit failed with error code " << res << std::endl;
    return 1;
  }

  int deviceCount = 0;
  res = cuDeviceGetCount(&deviceCount);
  if (res != CUDA_SUCCESS)
  {
    std::cerr << "cuDeviceGetCount failed with error code " << res << std::endl;
    return 1;
  }

  std::cout << "Detected " << deviceCount << " CUDA device(s)" << std::endl;

  for (int i = 0; i < deviceCount; ++i)
  {
    CUdevice dev;
    cuDeviceGet(&dev, i);

    char name[128];
    cuDeviceGetName(name, sizeof(name), dev);
    std::cout << "Device " << i << ": " << name << std::endl;
  }

  return 0;
}
