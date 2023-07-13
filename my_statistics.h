/* Header: my_statistics.h

    A set of mathematical functions developed for Probability and Statistics.

    Author: Guilherme Arruda

    GitHub: https://github.com/ohananoshi

    Created on: 23/02/2023

    Last updated: 23/02/2023
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdarg.h>

#define INCLUDED 1
#define NOT_INCLUDED 0

typedef bool (*compare_function)(double, double, bool);
typedef bool (*test_function)(long int);


bool bigger_than(double source_value, double value, bool include){
    if(include) return source_value >= value ? 1 : 0;
    else return source_value > value ? 1 : 0;
}

bool smaller_than(double source_value, double value, bool include){
    if(include) return source_value <= value ? 1 : 0;
    else return source_value < value ? 1 : 0;
}

bool is_even(long int value){
    return (value % 2 == 0) ? 1 : 0;
}

bool is_odd(long int value){
    return (value % 2 == 1) ? 1 : 0;
}

long int* parity_filter(long int* sample_source, unsigned int sample_length, test_function parity_test){

    long int* filtered_sample = (long int*)malloc(sizeof(long int));
    unsigned int filtered_sample_length = 0;

    for(int i = 0; i < sample_length; i++){
        if(parity_test(sample_source[i])){
            filtered_sample[filtered_sample_length] = sample_source[i];
            filtered_sample_length++;
            filtered_sample = (long int*)realloc(filtered_sample, filtered_sample_length*sizeof(long int));
        }
    }

    if(filtered_sample_length == 0){
        printf("No data matches the search parameters.");
        return NULL;
    }
    else return filtered_sample;
}

double* sample_filter(double* sample_source, unsigned int sample_length, compare_function* filter_functions, double *filter_args, unsigned int filters_number){

    double* filtred_sample = (double*)malloc(sizeof(double));
    int filtred_sample_length = 0;

    int true_count;

    for(int i = 0; i < sample_length; i++){
        true_count = 0;

        for(int j = 0, arg_count = 0;  j < filters_number; j++, arg_count+=2){
            if(filter_functions[j](sample_source[i], filter_args[arg_count], (bool)filter_args[arg_count+1])){
                true_count++;
            }else break;
        }
        if(true_count == filters_number){
            filtred_sample[filtred_sample_length] = sample_source[i];
            filtred_sample_length++;
            filtred_sample = (double *)realloc(filtred_sample, filtred_sample_length*sizeof(double));
        }
    }

    if(filtred_sample_length == 0){
        printf("No data matches the search parameters.");
        return NULL;
    }
    else return filtred_sample;

}

double sample_mean(double *sample_source, unsigned int sample_length){

    double mean = 0;

    for(int i = 0; i < sample_length; i++){
        mean += sample_source[i];
    }

    return mean/(double)sample_length;
}

double sample_variance(double *sample_source, double sample_mean, unsigned int sample_length){

    double variance = 0;

    for(int i = 0; i < sample_length; i ++){
        variance += pow(sample_source[i] - sample_mean, 2.0);
    }

    return variance;
}

double sample_std_deviation(double sample_variance){
    return sqrt(sample_variance);
}
