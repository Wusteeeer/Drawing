#ifndef DSHAPE_H
#define DSHAPE_H

#include "c_util.h"
#include "vector.h"
#include "screen.h"
#include "brush.h"

#define PI 3.14159265358979323846
#define TWO_PI 2.0f*PI
#define HALF_PI PI/2.0f
#define EULER 2.71828182845904523536

/*@brief Draw a rectangle on sc from corner c1 to corner c2 with an edge size of edgeSize*/
void draw_rectangle(Screen *sc, Vector *c1, Vector *c2, int edgeSize, COLOR color, U_BYTE zOrder);

/*@brief Draw a rectangle on sc with center c, width w, height h and edge size of edgeSize*/
void draw_rectangle_c(Screen *sc, Vector *c, int w, int h, int edgeSize, COLOR color, U_BYTE zOrder);

/*@brief Draw a filled in rectangle on sc with corners c1 and c2*/
void draw_rectangle_fill(Screen *sc, Vector *c1, Vector *c2, COLOR color, U_BYTE zOrder);

/*@brief Draw a filled in rectangle on sc with center c, width w and height h*/
void draw_rectangle_fill_c(Screen *sc, Vector *c, int w, int h, COLOR color, U_BYTE zOrder);

/*@brief Draw a circle on sc from corner c1 to corner c2 with an edge size of edgeSize*/
void draw_circle(Screen *sc, Vector *c1, Vector *c2, int edgeSize, COLOR color, U_BYTE zOrder);

/*@brief Draw a circle on sc with center c, radius r and edge size of edgeSize*/
void draw_circle_c(Screen *sc, Vector *c, int r, int edgeSize, COLOR color, U_BYTE zOrder);

/*@brief Draw line from p1 to p2*/
void draw_line_2D(Screen *sc, Brush *br, Vector *p1, Vector *p2);

/*@brief Draw a curve with the parametrization r(t) = h(t)i + g(t)j where start <= t <= end*/
void draw_p_curve_2D(Screen *sc, double (*ht)(double), double (*gt)(double), double start, double end, Brush *br, float precision, bool closed);


/**/
bool falls_within_rounded_corner(Vector *p, Vector *c1, Vector *c2, int cornerRadius);

#endif //DHSAPE_H