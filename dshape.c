#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "dshape.h"


void draw_rectangle(Screen *sc, Vector *c1, Vector *c2, int edgeSize, COLOR color, U_BYTE zOrder){
    

    Vector *topCorner, *bottomCorner;

    //If c1 is closer to origin
    if(compareTo_vector(c1, c2) < 0){
        topCorner = c1;
        bottomCorner = c2;
    }else{
        topCorner = c2;
        bottomCorner = c1;
    }


    int width = getX(bottomCorner)-getX(topCorner);
    int height = getY(bottomCorner)-getY(topCorner);

    COLOR map[edgeSize][edgeSize];
    for(int i = 0; i < edgeSize; i++){
        for(int j = 0; j < edgeSize; j++){
            map[i][j] = color;
        }
    }

    /*
        If c1 and c2 are (10,10) and (100, 200) then we also have corners (100, 10) and (10, 200)
        Then we can think of the rectangle as the four lines
        L1 = {y = 10, 10 <= x <= 100} (from (10,10) to (100, 0))
        L2 = {x = 100, 10 <= y <= 200} (from (100, 10) to (100, 200))
        L3 = {y = 200, 10 <= x <= 100} (from (100, 200) to (10, 200))
        L4 = {x = 10, 10 <= y <= 200} (from (10, 200) to (10, 10))
        This is the boundary curve C of the domain D where
        D = {(x,y) : 10 <= x <= 100, 10 <= y <= 200}
        We can parameterize the four lines as
        r1(t) = (t, 10) where 10 <= t <= 100
        r2(t) = (100, t) where 10 <= t <= 200
        r3(t) = (110-t, 200) where 10 <= t <= 100
        r4(t) = (10, 210-t) where 10 <= t <= 200
        We can therefore make the algorithm O(w+h) in time complexity (disregarding edgeSize)

        Generalized form:
        Width = w, Height = h, Corners C1 = (x1, y1), C2 = (x2, y2) where C1 is the top corner

        L1 = {y = y1, x1 <= x <= x2} (From (x1, y1) to (x2, y1))
        L2 = {y1 <= y <= y2, x = x2} (From (x2, y1) to (x2, y2))
        L3 = {y = y2, x1 <= x <= x2} (From (x2, y2) to (x1, y2))
        L4 = {y1 <= y <= y2, x = x1} (From (x1, y2) to (x1, y1))
        Parameterized we get
        r1(t) = (t, y1) Where x1 <= t <= x2
        r2(t) = (x2, t) Where y1 <= t <= y2
        r3(t) = (t, y2) Where x1 <= t <= x2
        r4(t) = (x2, t) Where y1 <= t <= y2
    */
    int edgeCeiling = (int)ceil((float)edgeSize/2.0f);
    int edgeFloor = (int)floor(-edgeSize/2); 
    for(int i = edgeFloor; i < edgeCeiling; i++){
        for(int t = getX(topCorner)+edgeFloor; t < getX(bottomCorner)+edgeCeiling; t++){
            
            int topY = getY(topCorner)+i;
            int bottomY = getY(bottomCorner)+i;

            setPixelColor(sc, t, topY, color);
            setPixelZOrder(sc, t, topY, zOrder);
            
            setPixelColor(sc, t, bottomY, color);
            setPixelZOrder(sc, t, bottomY, zOrder);

        }

        for(int t = getY(topCorner); t < getY(bottomCorner); t++){
        
            int topX = getX(topCorner)+i;
            int bottomX = getX(bottomCorner)+i;

            setPixelColor(sc, topX, t, color);
            setPixelZOrder(sc, topX, t, zOrder);
            
            setPixelColor(sc, bottomX, t, color);
            setPixelZOrder(sc, bottomX, t, zOrder);

        }
    }
    

    

}

void draw_rectangle_c(Screen *sc, Vector *c, int w, int h, int edgeSize, COLOR color, U_BYTE zOrder){

}

void draw_circle(Screen *sc, Vector *c1, Vector *c2, int edgeSize, COLOR color, U_BYTE zOrder){

}

void draw_circle_c(Screen *sc, Vector *c, int r, int edgeSize, COLOR color, U_BYTE zOrder){

}

void draw_line_2D(Screen *sc, Brush *br, Vector *p1, Vector *p2){

    Vector *dir = subtractVector(p2, p1);
    normalizeVector(dir);

    Vector *temp = createVector(2, V2(getX(p1), getY(p1)));
    while(distance(temp, p2) >= 1.0f){
        draw(sc, br, getX(temp), getY(temp));
        addX(temp, getX(dir));
        addY(temp, getY(dir));
    }

    destroyVector(temp);
    destroyVector(dir);

}

void draw_p_curve_2D(Screen *sc, double (*ht)(double), double (*gt)(double), double start, double end, Brush *br, float precision, bool closed){

    Vector *previousPos = createVector(2, V2(-1,-1));
    Vector *currentPos = createVector(2, V2(0,0));
    for(float t = start; t <= end; t+=precision){

        int x = (int)(ht(t));
        int y = (int)(gt(t));
        
        setValues(currentPos, V2(x, y));
        
        if(getX(previousPos) != -1){
         
            draw_line_2D(sc, br, previousPos, currentPos);
        
        }
            
        setValues(previousPos, V2(getX(currentPos), getY(currentPos)));
    }

    if(closed){
        Vector *startPos = createVector(2, V2(ht(start), gt(start)));
        draw_line_2D(sc, br, currentPos, startPos);
        destroyVector(startPos);
    }
    
    destroyVector(currentPos);
    destroyVector(previousPos);

}