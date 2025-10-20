#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "vector.h"

typedef struct vector{
    int size;
    float magnitude;
    float *values;
}Vector;

Vector *createVector(int size, float *values){
    Vector *v = malloc(sizeof(Vector));
    v->size = size;
    v->values = malloc(size*sizeof(float));

    float acc = 0;
    for(int i = 0; i < size; i++){
        v->values[i] = values[i];
        acc += values[i]*values[i];
    }
    v->magnitude = sqrt(acc);
    return v;
}

void destroyVector(Vector *v){
    free(v->values);
    free(v);
}

void printVector(Vector *v){
    printf("<");
    for(int i = 0; i < v->size; i++){
        if(i != v->size-1){
            printf("%3.2f, ", v->values[i]);
        }else{
            printf("%3.2f", v->values[i]);
        }
    }
    printf(">\n\tMagnitude: %3.2f\n", v->magnitude);
}

float getX(Vector *v){
    if(v->size == 0) return -1;
    return v->values[0];
}

float getY(Vector *v){
    if(v->size <= 1) return -1;
    return v->values[1];
}

float getZ(Vector *v){
    if(v->size <= 2) return -1;
    return v->values[2];    
}

float getW(Vector *v){
    if(v->size <= 3) return -1;
    return v->values[3];    
}

float getValue(Vector *v, int index){
    if(index >= v->size) return -1;
    return v->values[index];
}

float vectorMag(Vector *v){
    return v->magnitude;
}

void addX(Vector *v, float add){
    if(v->size == 0) return;
    v->values[0] += add;
}

void addY(Vector *v, float add){
    if(v->size <= 1) return;
    v->values[1] += add;
}

void addZ(Vector *v, float add){
    if(v->size <= 2) return;
    v->values[2] += add;
}


void setValues(Vector *v, float *vals){
    if(sizeof(vals)/sizeof(float) < v->size) return;

    float acc = 0;
    for(int i = 0; i < v->size; i++){
        v->values[i] = vals[i];
        acc += vals[i]*vals[i];
    }
    v->magnitude = sqrt(acc);
}

float distance(Vector *v1, Vector *v2){
    return sqrt(((getX(v2)-getX(v1))*(getX(v2)-getX(v1)))+((getY(v2)-getY(v1))*(getY(v2)-getY(v1))));
}

Vector *addVector(Vector *v1, Vector *v2){
    float values[v1->size];
    for(int i = 0; i < v1->size; i++){
        values[i] = v1->values[i]+v2->values[i];
    }
    return createVector(v1->size, values);
}

Vector *subtractVector(Vector *v1, Vector *v2){
    float values[v1->size];
    for(int i = 0; i < v1->size; i++){
        values[i] = v1->values[i]-v2->values[i];
    }
    return createVector(v1->size, values);
}

Vector *dotProduct(Vector *v1, Vector *v2);
Vector *crossProduct(Vector *v1, Vector *v2);
Vector *scaleVector(Vector *v, float scalar);
Vector *scaleDownVector(Vector *v, float scalar);
Vector *projectVector(Vector *v1, Vector *v2);

void normalizeVector(Vector *v){
    if(v->magnitude == 0) return;
    for(int i = 0; i < v->size; i++){
        v->values[i] = v->values[i]/v->magnitude;
    }
    v->magnitude = 1.0f;
}