#include "color.h"
#include "image.h"
#include "platform.h"
#include "sphere.h"
#include "spheres.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>

#define SPHERE_COUNT 1000
#define SPHERE_MIN_RADIUS 20.0f
#define SPHERE_MAX_RADIUS 100.0f
#define SPHERE_MIN_Z 500.0f
#define SPHERE_MAX_Z 10000000.0f

int main(int argc, char *argv[])
{
    image_t out_image;
    image_init(&out_image, 1024, 1024);

#ifdef __NVCC__
    /* TODO: Allocate memory for the image on the GPU device. */

#endif

    sphere_t *spheres =
        spheres_create_random(
            SPHERE_COUNT,
            SPHERE_MIN_RADIUS, SPHERE_MAX_RADIUS,
            0.0f, (float) out_image.width,
            0.0f, (float) out_image.height,
            SPHERE_MIN_Z, SPHERE_MAX_Z
        );

#ifdef __NVCC__
    /* TODO: Allocate memory (`cudaMalloc`) for spheres on the GPU device. */

    /* TODO: Copy sphere data from the CPU world to the GPU memory (`cudaMemcpy`). */

#endif

#ifndef __NVCC__
    fputs("CPU path is used.\n", stderr);

    spheres_raytrace(spheres, SPHERE_COUNT, out_image);
#else
    fputs("GPU path is used.\n", stderr);

    /* TODO: Decide on how many threads and blocks do you need, considering
             that we may not have more than 1024 threads per every block. */

    /* TODO: Start the kernel with the pointers to the sphere data and the image
             on the GPU. The kernel will run on multiple cores and execution
             units in parallel for every pixel. */

    /* TODO: For debugging purposes, you may check for the last error with the
             `cudaGetLastError` call and the `cudaGetErrorString` call to print
             the error message. */

    /* TODO: Copy the image data from the GPU back to the CPU (`cudaMemcpy`). */

    /* TODO: Synchronize execution with the CPU (`cudaDeviceSynchronize`). */

#endif

    image_print_as_ppm(&out_image);

end:
#ifdef __NVCC__
    /* TODO: Free the GPU memory (`cudaFree`). */

#endif

    spheres_free(spheres);
    image_free_data(&out_image);

    return 0;
}
