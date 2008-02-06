#include <spu_mfcio.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../src/types.h"
#include "fx.h"

#define F_(X)		0x##X, 0x##X, 0x##X, 0x##X


#define F_X		0x00, 0x01, 0x02, 0x03
#define F_Y		0x04, 0x05, 0x06, 0x07
#define F_Z		0x08, 0x09, 0x0A, 0x0B
#define F_W		0x0C, 0x0D, 0x0E, 0x0F

#define S_X		0x10, 0x11, 0x12, 0x13
#define S_Y		0x14, 0x15, 0x16, 0x17
#define S_Z		0x18, 0x19, 0x1A, 0x1B
#define S_W		0x1C, 0x1D, 0x1E, 0x1F


#define C16_0       0x80, 0x80, 0x00, 0x01
#define C16_1       0x80, 0x80, 0x02, 0x03
#define C16_2       0x80, 0x80, 0x04, 0x05
#define C16_3       0x80, 0x80, 0x06, 0x07
#define C16_4       0x80, 0x80, 0x08, 0x09
#define C16_5       0x80, 0x80, 0x0A, 0x0B
#define C16_6       0x80, 0x80, 0x0C, 0x0D
#define C16_7       0x80, 0x80, 0x0E, 0x0F

#define N16_0       0x80, 0x80, 0x10, 0x11
#define N16_1       0x80, 0x80, 0x12, 0x13
#define N16_2       0x80, 0x80, 0x14, 0x15
#define N16_3       0x80, 0x80, 0x16, 0x17
#define N16_4       0x80, 0x80, 0x18, 0x19
#define N16_5       0x80, 0x80, 0x1A, 0x1B
#define N16_6       0x80, 0x80, 0x1C, 0x1D
#define N16_7       0x80, 0x80, 0x1E, 0x1F


#define C8_0       0x80, 0x80, 0x80, 0x00
#define C8_1       0x80, 0x80, 0x80, 0x01
#define C8_2       0x80, 0x80, 0x80, 0x02
#define C8_3       0x80, 0x80, 0x80, 0x03
#define C8_4       0x80, 0x80, 0x80, 0x04
#define C8_5       0x80, 0x80, 0x80, 0x05
#define C8_6       0x80, 0x80, 0x80, 0x06
#define C8_7       0x80, 0x80, 0x80, 0x07
#define C8_8       0x80, 0x80, 0x80, 0x08
#define C8_9       0x80, 0x80, 0x80, 0x09
#define C8_A       0x80, 0x80, 0x80, 0x0A
#define C8_B       0x80, 0x80, 0x80, 0x0B
#define C8_C       0x80, 0x80, 0x80, 0x0C
#define C8_D       0x80, 0x80, 0x80, 0x0D
#define C8_E       0x80, 0x80, 0x80, 0x0E
#define C8_F       0x80, 0x80, 0x80, 0x0F

#define N8_0       0x80, 0x80, 0x80, 0x10
#define N8_1       0x80, 0x80, 0x80, 0x11
#define N8_2       0x80, 0x80, 0x80, 0x12
#define N8_3       0x80, 0x80, 0x80, 0x13
#define N8_4       0x80, 0x80, 0x80, 0x14
#define N8_5       0x80, 0x80, 0x80, 0x15
#define N8_6       0x80, 0x80, 0x80, 0x16
#define N8_7       0x80, 0x80, 0x80, 0x17
#define N8_8       0x80, 0x80, 0x80, 0x18
#define N8_9       0x80, 0x80, 0x80, 0x19
#define N8_A       0x80, 0x80, 0x80, 0x1A
#define N8_B       0x80, 0x80, 0x80, 0x1B
#define N8_C       0x80, 0x80, 0x80, 0x1C
#define N8_D       0x80, 0x80, 0x80, 0x1D
#define N8_E       0x80, 0x80, 0x80, 0x1E
#define N8_F       0x80, 0x80, 0x80, 0x1F

#define E_2  0x80, 0x80
#define E_3  0x80, 0x80, 0x80
#define E_4  0x80, 0x80, 0x80, 0x80
#define E_5  0x80, 0x80, 0x80, 0x80, 0x80
#define E_6  0x80, 0x80, 0x80, 0x80, 0x80, 0x80
#define E_7  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80
#define E_8  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80
#define E_9  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80
#define E_10 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80
#define E_11 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80
#define E_12 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80
#define E_13 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80
#define E_14 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80

#define SHUFFLE_MERGE4(A, B, C, D)	(vector unsigned char)(A, B, C, D)

#define SWZ (vector unsigned char)

#define X( A )  spu_shuffle( A, A, SWZ{ F_X, E_12 } )
#define Y( A )  spu_shuffle( A, A, SWZ{ F_Y, E_12 } )
#define Z( A )  spu_shuffle( A, A, SWZ{ F_Z, E_12 } )
#define W( A )  spu_shuffle( A, A, SWZ{ F_W, E_12 } )

#define XY( A )  spu_shuffle( A, A, SWZ{ F_X, F_Y, E_8 } )
#define YX( A )  spu_shuffle( A, A, SWZ{ F_Y, F_X, E_8 } )


#define XXXX( A )  spu_shuffle( A, A, SWZ{ F_X, F_X, F_X, F_X } )
#define YYYY( A )  spu_shuffle( A, A, SWZ{ F_Y, F_Y, F_Y, F_Y } )
#define ZZZZ( A )  spu_shuffle( A, A, SWZ{ F_Z, F_Z, F_Z, F_Z } )
#define WWWW( A )  spu_shuffle( A, A, SWZ{ F_W, F_W, F_W, F_W } )
#define YZWX( A )  spu_shuffle( A, A, SWZ{ F_Y, F_Z, F_W, F_X } )
#define ZWXY( A )  spu_shuffle( A, A, SWZ{ F_Z, F_W, F_X, F_Y } )
#define WXYZ( A )  spu_shuffle( A, A, SWZ{ F_W, F_X, F_Y, F_Z } )
#define YXWZ( A )  spu_shuffle( A, A, SWZ{ F_Y, F_X, F_W, F_Z } )

#define YZXW( A )  spu_shuffle( A, A, SWZ{ F_Y, F_Z, F_X, F_W } )
#define ZXYW( A )  spu_shuffle( A, A, SWZ{ F_Z, F_X, F_Y, F_W } )

#define Q16_0( A )  spu_shuffle( A, A, SWZ{ C16_0, E12 } )
#define Q16_1( A )  spu_shuffle( A, A, SWZ{ C16_1, E12 } )
#define Q16_2( A )  spu_shuffle( A, A, SWZ{ C16_2, E12 } )
#define Q16_3( A )  spu_shuffle( A, A, SWZ{ C16_3, E12 } )
#define Q16_4( A )  spu_shuffle( A, A, SWZ{ C16_4, E12 } )
#define Q16_5( A )  spu_shuffle( A, A, SWZ{ C16_5, E12 } )
#define Q16_6( A )  spu_shuffle( A, A, SWZ{ C16_6, E12 } )
#define Q16_7( A )  spu_shuffle( A, A, SWZ{ C16_7, E12 } )

#define NANF (vec_float4){ 1.0f/ 0.0f, 1.0f/ 0.0f, 1.0f/ 0.0f, 1.0f/ 0.0f }

#define ZEROF (vec_float4){ 0.0f, 0.0f, 0.0f, 0.0f }
#define F1111 (vec_float4){ 1.0f, 1.0f, 1.0f, 1.0f }
#define F1000 (vec_float4){ 1.0f, 0.0f, 0.0f, 0.0f }
#define F0100 (vec_float4){ 0.0f, 1.0f, 0.0f, 0.0f }
#define F0010 (vec_float4){ 0.0f, 0.0f, 1.0f, 0.0f }
#define F0001 (vec_float4){ 0.0f, 0.0f, 0.0f, 1.0f }

#define EPSF (vec_float4){ 0.0001f, 0.0001f, 0.0001f, 0.0001f }
#define EPNF (vec_float4){ -0.0001f, -0.0001f, -0.0001f, -0.0001f }

#define V16I (vec_uint4){ 16, 16, 16, 16 }

float inline GetTime( unsigned long long &te )
{
	unsigned long long v = spu_read_decrementer();
	float time = ( te - v ) /  ( 3193000.0f * 25.0f );
	te = v;
	return time;
}


void inline _D( const vec_int4 & t, const char *str = "", const char *term = "\n" )
{
	for( int i = 0; i < 4; ++i )
	{
		printf( "%8x%s", ( (int *)&t)[i], i == 3 ? "":str );
	}
	printf( "%s", term );
};


void inline _D( const vec_uint4 & t, const char *str = "", const char *term = "\n" )
{
	for( int i = 0; i < 4; ++i )
	{
		printf( "%d%s", ( (unsigned int *)&t)[i], i == 3 ? "":str );
	}
	printf( "%s", term );
};

void inline _D( const vec_float4 & t, const char *str = "", const char *term = "\n" )
{
	for( int i = 0; i < 4; ++i )
	{
		printf( "%f%s", ( (float *)&t)[i], i == 3 ? "":str );
	}
	printf( "%s", term );
};
