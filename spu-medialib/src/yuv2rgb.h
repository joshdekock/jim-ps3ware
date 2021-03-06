/**
 * SPU YUV 2 RGB conversion kernel
 * --------------------------------
 * Licensed under the BSDv2 
 *
 * yuv2rgb.h - ppu header for the spe accellerated yuv2rgb converter 
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


#ifndef __YUV2RGB_H
#define __YUV2RGB_H

#include <libspe2.h>

#ifdef __cplusplus
extern "C" {
#endif


struct yuv2rgb_s;
typedef struct yuv2rgb_s yuv2rgb_t;

typedef void * ea_t;

/**
* init_yuv2rgb 
* initiates the spu yuv2rgb.
*/ 
yuv2rgb_t * csc_init_yuv2rgb(int srcW, int srcH, int offset, int maxwidth,
				ea_t front_inBuffer, ea_t back_inBuffer,
                                ea_t front_outBuffer, ea_t back_outBuffer);

/**
*gets the spe context pointer from the initiated yuv2rgb
*/
spe_context_ptr_t csc_getCTX(yuv2rgb_t*);

/**
* recive_message waits for a interrupt message from the spu notifying a loop completion
*/
unsigned int csc_receive_message(yuv2rgb_t*);


/**
* sends a message to the spu telling it what to do options are RDY UPDATE and STOP defined in spu_control.h
*/
void csc_send_message(yuv2rgb_t*,unsigned int message);

/**
* destroys the spu scaler object and this object
*/
void csc_yuv2rgb_destroy(yuv2rgb_t*);

/**
* get functions for image sizes
*/
unsigned int csc_get_srcW(const yuv2rgb_t*);
unsigned int csc_get_srcH(const yuv2rgb_t*);
unsigned int csc_get_offset(const yuv2rgb_t*);
unsigned int csc_get_maxwidth(const yuv2rgb_t*);

/**
* set functions for image sizes (only takes effect if followed by an update!)
*/
void csc_set_srcW(yuv2rgb_t*,int dstw);
void csc_set_srcH(yuv2rgb_t*,int srcw);
void csc_set_offset(yuv2rgb_t*,int offset);
void csc_set_maxwidth(yuv2rgb_t*,int maxwidth);

#ifdef __cplusplus
}
#endif

#endif
