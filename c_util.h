#ifndef C_UTIL_H
#define C_UTIL_H

#ifdef _cplusplus
extern "C" {
#endif


#define ARGBTORGBA(argb) \
    (((argb&0x000000FF)<<8)|((argb&0x0000FF00)<<8)|((argb&0x00FF0000)<<8)|((argb&0xFF000000)>>24))

#define RGBATOARGB(rgba) \
    (((rgba&0xFF000000)>>8)|((rgba&0x00FF0000)>>8)|((rgba&0x0000FF00)>>8)|((rgba&0x000000FF)<<24))

#define REDCHANNEL(argb) \
    ((argb&0x00FF0000)>>16)

#define GREENCHANNEL(argb) \
    ((argb&0x0000FF00)>>8)

#define BLUECHANNEL(argb) \
    ((argb&0x000000FF))

#define ALPHACHANNEL(argb) \
    ((argb&0xFF000000)>>24)

/*@brief typedef unsigned byte*/
typedef unsigned char U_BYTE;

/*@brief typedef unsigned long*/
typedef unsigned long COLOR;

#define ARGB(a, r, g, b) \
    ((COLOR)(a<<24|r<<16|g<<8|b))


/*@brief Background color*/
#define BACKGROUND (COLOR)0xFF202020

/*@brief White color*/
#define WHITE (COLOR)0xFFFFFFFF

/*@brief Black color*/
#define BLACK (COLOR)0xFF000000

/*@brief Blue color 100% alpha*/
#define BLUE (COLOR)0xFF0000FF

/*@brief Red color 100% alpha*/
#define RED (COLOR)0xFFFF0000

/*@brief Green color 100% alpha*/
#define GREEN (COLOR)0xFF00FF00

/*@brief Yellow color*/
#define YELLOW (COLOR)0xFFFFFF00

/*@brief Transparent*/
#define TRANSPARENT (COLOR)-1

#ifdef _cplusplus
} //extern "C"
#endif

#endif