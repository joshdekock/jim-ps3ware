/**
 * SPU YUV420/YV12 scaler to ARGB conversion kernel
 * --------------------------------
 * Licensed under the BSDv2 
 *
 * yuv2argb_scaler.h - ppu header for the spe accellerated yuv scaler and argb converter 
 *
 * Copyright (c) 2007, Kristian Jerpetj�n <kristian.jerpetjoen@gmail.com>
 * $Id:
 */

// Copyright (c) 2007, Kristian Jerpetj�n <kristian.jerpetjoen@gmail.com>

// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. The names of the authors may not be used to endorse or promote products
//    derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE AUTHORS ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


#ifndef __SPU_BLITTER_H
#define __SPU_BLITTER_H

#include <libspe2.h>
#include <spu-medialib/yuv_datastructs.h>

#ifdef __cplusplus
extern "C" {
#endif

//struct img_args;
typedef struct img_args img_argt;

struct blitter_s;
typedef struct blitter_s blitter_t;

//typedef void * ea_t;
typedef unsigned long long ea_t;
/**
* init_yuv2rgb 
* initiates the spu yuv2rgb.
*/ 

blitter_t * blitt(img_argt *iargs_arg);

// yuvscaler2argb_t * yuvscsc_init_yuv2argb_scaler(int srcW, int srcH,int dstW,int dstH, int offset, int maxwidth,
// 				ea_t front_inYBuffer, ea_t back_inYBuffer,
// 				ea_t front_inUBuffer, ea_t back_inUBuffer,
// 				ea_t front_inVBuffer, ea_t back_inVBuffer,
//                                 ea_t front_outBuffer, ea_t back_outBuffer);

//#define SPU_BLITT(Y,U,V,LINES,STRIDE0,STRIDE1,OSTRIDE0,0) 

/**
*gets the spe context pointer from the initiated yuv2rgb
*/
// spe_context_ptr_t yuvscsc_getCTX(yuvscaler2argb_t*);

/**
* recive_message waits for a interrupt message from the spu notifying a loop completion
*/
 unsigned int receive_message(blitter_t*);
unsigned int receive_message_hard(blitter_t *);

/**
* sends a message to the spu telling it what to do options are RDY UPDATE and STOP defined in spu_control.h
*/
 void send_message(blitter_t*,unsigned int message);

/**
* destroys the spu scaler object and this object
*/
void destroy(blitter_t*);

/**
* get functions for image sizes
*/
// unsigned int yuvscsc_get_srcW(const yuvscaler2argb_t*);
// unsigned int yuvscsc_get_srcH(const yuvscaler2argb_t*);
// unsigned int yuvscsc_get_offset(const yuvscaler2argb_t*);
// unsigned int yuvscsc_get_maxwidth(const yuvscaler2argb_t*);

/**
* set functions for image sizes (only takes effect if followed by an update!)
*/
// void yuvscsc_set_srcW(yuvscaler2argb_t*,int srcw);
// void yuvscsc_set_srcH(yuvscaler2argb_t*,int srch);
// void yuvscsc_set_dstW(yuvscaler2argb_t*,int dstw);
// void yuvscsc_set_dstH(yuvscaler2argb_t*,int dsth);
// void yuvscsc_set_offset(yuvscaler2argb_t*,int offset);
// void yuvscsc_set_maxwidth(yuvscaler2argb_t*,int maxwidth);

/**
* functions for setting buffer pointers (only takes effect if followed by an update!)
*/

// void yuvscsc_set_Buffers(yuvscaler2argb_t*, ea_t inYBuffer,ea_t inUBuffer,ea_t inVBuffer,ea_t outBuffer,int currentbuff);
//void yuvscsc_set_backBuffers(yuvscaler2argb_t*, ea_t back_inYBuffer,ea_t back_inUBuffer,ea_t back_inVBuffer,ea_t back_outBuffer);

#ifdef __cplusplus
}
#endif

#endif

