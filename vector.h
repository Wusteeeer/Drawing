#ifndef VECTOR_H
#define VECTOR_H


#define V2(x, y) \
    ((float[]){x, y})

#define V3(x, y, z) \
    ((float[]){x, y, z})

#define V4(x, y, z, w) \
    ((float[]){x, y, z, w});

typedef struct vector Vector;

Vector *createVector(int size, float *values);
void destroyVector(Vector *v);

void printVector(Vector *v);

float getX(Vector *v);
float getY(Vector *v);
float getZ(Vector *v);
float getW(Vector *v);
float getValue(Vector *v, int index);
float vectorMag(Vector *v);

void addX(Vector *v, float add);
void addY(Vector *v, float add);
void addZ(Vector *v, float add);

/*@brief v1.mag > v2.mag ? >0 : <0 ; v1.mag == v2.mag => 0*/
int compareTo_vector(Vector *v1, Vector *v2);

void setValues(Vector *v, float *vals);

Vector *addVector(Vector *v1, Vector *v2);
Vector *subtractVector(Vector *v1, Vector *v2);
Vector *dotProduct(Vector *v1, Vector *v2);
Vector *crossProduct(Vector *v1, Vector *v2);
Vector *scaleVector(Vector *v, float scalar);
Vector *scaleDownVector(Vector *v, float scalar);
Vector *projectVector(Vector *v1, Vector *v2);
float distance(Vector *v1, Vector *v2);
void normalizeVector(Vector *v);

#endif //VECTOR_H