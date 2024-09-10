#include <stdio.h>
#include <stdlib.h>

typedef struct {

    float cgpa;
    float ctc;

}
Student;

void calcMeans(Student * students, float * cgpaMean, float * ctcMean);

float calcGradient(Student * students, float cgpaMean, float ctcMean);

float calcIntercept(Student * students, float gradient);

int main(int argc, char ** argv) {

    FILE * file;
    file = fopen("data.csv","r");

    if(file == NULL) {

        printf("Error!\n");
        return 1;

    }

    FILE * temp = file;
    Student students[200];

    for(int i = 0; !feof(file); i++) {

        fscanf(file,
        "%f,%f\n",
        &students[i].cgpa,
        &students[i].ctc);

    }

    fclose(file);

    //Using CL arguements to get the test CGPAs.

    int n = argc-1;
    float * testCGPAs = (float *)malloc(sizeof(float)*(n));

    for(int i = 0; i < n; i++) {

        *(testCGPAs+i) = atof(argv[i+1]);

    }

    float * cgpaMean = (float *)malloc(sizeof(float));
    float * ctcMean = (float *)malloc(sizeof(float));

    calcMeans(students, cgpaMean, ctcMean);

    float gradient = 0;
    gradient = calcGradient(students, *cgpaMean, *ctcMean);

    float intercept = 0;
    intercept = calcIntercept(students,gradient);

    printf("The gradient of the slope is : %f and the intercept is : %f\n",gradient,intercept);

    for(int i = 0; i < n; i++) {
        
        float temp = *(testCGPAs+i);
        printf("The test CGPA is : %f and it's predicted CTC is : %f\n",temp,temp*gradient + intercept);

    }

}

void calcMeans(Student * students, float * cgpaMean, float * ctcMean) {

    for(int i = 0; i < 200; i++) {

        *ctcMean += students[i].ctc;
        *cgpaMean += students[i].cgpa;

    }

    *ctcMean = *ctcMean/200;
    *cgpaMean = *cgpaMean/200;

}

float calcGradient(Student * students, float cgpaMean, float ctcMean) {

    float gradient;

    float numerator;
    float denominator;

    for(int i = 0; i < 200; i++) {

        numerator += (students[i].cgpa-cgpaMean)*(students[i].ctc-ctcMean);
        denominator += (students[i].cgpa-cgpaMean)*(students[i].cgpa-cgpaMean);

    }

    gradient = numerator/denominator;

    return gradient;

}

float calcIntercept(Student * students, float gradient) {

    float intercept;

    for(int i = 0; i < 200; i++) {

        intercept += (students[i].ctc-gradient*students[i].cgpa);

    }

    intercept = intercept/200;
    return intercept;

}
