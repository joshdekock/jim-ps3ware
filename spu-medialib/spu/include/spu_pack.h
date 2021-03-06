/**
 * SPU-MEDIALIB utility
 * --------------------------------
 * Licensed under the BSD license, see LICENSE for details
 *
 * pack.h - vector unpacking helper functions
 *
 * Copyright (c) 2007, Kristian Jerpetj�n <kristian.jerpetjoen@gmail.com>
 *
 * $Id: pack.h 26 2007-04-20 01:42:55Z warren $
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

#ifndef __SPU_PACK_H
#define __SPU_PACK_H

static inline vector float unpackhh(vector unsigned char a) {
	return (spu_convtf((vector unsigned int)spu_shuffle(a,((vector unsigned char){0}),((vector unsigned char){16,16,16,0,16,16,16,1,16,16,16,2,16,16,16,3})),0));
}

static inline vector float unpacklh(vector unsigned char a) {
	return (spu_convtf((vector signed int)spu_shuffle(a,((vector unsigned char){0}),((vector unsigned char){16,16,16,4,16,16,16,5,16,16,16,6,16,16,16,7})),0));
}

static inline vector float unpackhl(vector unsigned char a) {
	return (spu_convtf((vector signed int)spu_shuffle(a,((vector unsigned char){0}),((vector unsigned char){16,16,16,8,16,16,16,9,16,16,16,10,16,16,16,11})),0));
}

static inline vector float unpackll(vector unsigned char a) {
	return (spu_convtf((vector signed int)spu_shuffle(a,((vector unsigned char){0}),((vector unsigned char){16,16,16,12,16,16,16,13,16,16,16,14,16,16,16,15})),0));
}


static inline vector float unpackfaabb(vector float a) {
	return (spu_shuffle(a,a,((vector unsigned char){0,1,2,3,0,1,2,3,4,5,6,7,4,5,6,7})));
}

static inline vector float unpackfccdd(vector float a) {
	return (spu_shuffle(a,a,((vector unsigned char){8,9,10,11,8,9,10,11,12,13,14,15,12,13,14,15})));
}

#endif

