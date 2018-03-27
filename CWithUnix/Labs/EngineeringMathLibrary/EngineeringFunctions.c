#include <dlfcn.h>
#include "engeom.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    void *handle;
    char *err;
    float srad, crad, cht;

    FILE *outFile;
    char outFileName[21];
    char response;

    //Define DLL pointers
    void (*eng_sphere_d)(float, float*, float*);
    float (*eng_volCylinder_d)(float, float);
    float (*eng_sumFloats_d)(float*, int);
    double (*eng_sin_d)(float);

    //Get handle to dynamic library
    handle = dlopen("./libEngeom.so", RTLD_LAZY);
    if (handle == (void *)0)
    {
		fputs(dlerror(), stderr);
		exit(-1);
    }

    //Check if pointers exist
    eng_sphere_d = dlsym(handle, "eng_sphere");
    err = dlerror();
    if (err != NULL)
    {
		fputs(err, stderr);
		exit(-1);
    }

    eng_volCylinder_d = dlsym(handle, "eng_volCylinder");
    err = dlerror();
    if (err != NULL)
    {
		fputs(err, stderr);
		exit(-1);
    }

    eng_sumFloats_d = dlsym(handle, "eng_sumFloats");
    err = dlerror();
    if (err != NULL)
    {
		fputs(err, stderr);
		exit(-1);
    }

    eng_sin_d = dlsym(handle, "eng_sin");
    err = dlerror();
    if (err != NULL)
    {
		fputs(err, stderr);
		exit(-1);
    }

    do
    {
        printf("Enter output file name: ");
        scanf("%s", outFileName);
        
        //check if file already exists and asks for user authorizations
        if((outFile = fopen(outFileName, "r")) != NULL)
        {
            printf("A file by that name already exists.\n");
            do
            {
                printf("Do you wish to override? [y/n]: ");
                scanf(" %c", &response);
            }
            while(toupper(response) != 'N' && toupper(response) != 'Y');
        }
    }
    while(toupper(response) == 'N');

    //creates output file if it doesnt exist, or overwrite
    outFile = fopen(outFileName, "w");
    if (outFile == NULL)
    {
        printf("File could not be created.\n");
        printf("Exiting Program!\n");
        exit(1);
    }

    //sphere radius
    printf("Enter the radius of a sphere: ");
    scanf("%f", &srad);
    float s_surface, s_volume;
    (*eng_sphere_d)(srad, &s_surface, &s_volume);
    printf("The surface area is: %f\n", s_surface);
    printf("The Volume is: %f\n", s_volume);
    fprintf(outFile, "The surface area of a %.3fcm radius sphere is: %fcm\n", srad, s_surface);
    fprintf(outFile, "The volume of a %.3fcm radius sphere is: %fcm\n\n", srad, s_volume);


    //cylinder radius
    printf("Enter the radius of a cylinder: ");
    scanf("%f", &crad);
    printf("Enter the height of a cylinder: ");
    scanf("%f", &cht);
    float c_volume = (*eng_volCylinder_d)(crad, cht);
    printf("The volume of a cylinder is: %f\n", c_volume);
    fprintf(outFile, "The volume of a %.2fft x %.2fft cylinder is: %fft\n\n", crad, cht, c_volume);


    //sum of array
    int arrSize = 0;
    printf("Enter the size of a float array: ");
    scanf("%d", &arrSize);
    float farray[arrSize];
    for (int i = 0; i < arrSize; i++)
    {
		printf("Enter the size of %dst float array: ", i+1);
		scanf("%f", &farray[i]);
    }

    //display entered data
    printf("Unsorted Data:\n");
    fprintf(outFile, "Unsorted Data:\n");
    for (int i = 0; i < arrSize; i++)
    {
        printf("%f\n", farray[i]);
        fprintf(outFile, "%f\n", farray[i]);
    }

    //sort, add, and display data
    float fsum = (*eng_sumFloats_d)(farray, arrSize);
    printf("Sorted Data:\n");
    fprintf(outFile, "\nSorted Data:\n");
    for (int i = 0; i < arrSize; i++)
    {
        printf("%f\n", farray[i]);
        fprintf(outFile, "%f\n", farray[i]);
    }
    printf("The sum of the float array is: %f\n\n", fsum);
    fprintf(outFile, "The sum of the float array is: %f\n\n", fsum);

    //get the sine of some angles
	int sinCount = 0;
    printf("Enter the number of angles: ");
    scanf("%d", &sinCount);
    double sinResult;
    float sinOf;
    for (int i = 0; i < sinCount; i++)
    {
		printf("Enter the size of %dst angle: ", i+1);
		scanf("%f", &sinOf);
		sinResult = (*eng_sin_d)(sinOf);
        printf("sin(%f) = %lf\n", sinOf, sinResult);
        fprintf(outFile, "sin(%f) = %lf\n", sinOf, sinResult);
    }

    dlclose(handle);

    return 0;
}