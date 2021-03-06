/**
 * SPU_REGISTER
 * --------------------------------
 * Licensed under the BSDv2 
 *
 * spu_register.h - General purpose spu program unique id register
 *
 * Copyright (c) 2007, Kristian "unsolo" Jerpetj�n <kristian.jerpetjoen@gmail.com>
 * Copyright (c) 2007, Steven "Sauce" Osman <sosman@terratron.com>
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

#ifndef __SPU_REGISTER_H
#define __SPU_REGISTER_H

#define MAX_SPU_PROGRAMS 256
#include <list>
#include <vector>
//#include <malloc.h>
#include <pthread.h>	

using namespace std;
 
typedef uint32_t spu_program_unique_id;
typedef uint32_t message_queue_size;
//typedef uint8_t priority; //the programs priority (not used yet)
//typedef uint32_t time;
typedef bool spu_state;

struct spu_bound_message {
	uint32_t active;
	uint32_t message0;
	uint32_t message1;
	uint32_t message2;
	char acDetails[120];
}__attribute__((aligned(128))); //divided into 128 bit blocks is perhaps an idea

typedef struct {
	spu_program_unique_id id;
	spu_state active; //keeps track of which spu programs are actually running on the spus
	spu_state in_use; // verification that the id is actually in use..
	message_queue_size mqsize;
	spu_bound_message *mqpointer;
	pthread_mutex_t lock;
//	priority pri=3; //not used yet 
//	time load_interval=0; //0 means no restrictions // not used yet
//	time idle_time;
	void *program;
	
}spu_program;

class spu_register 
{
	public:
 	spu_register(){

		free_spuid.resize(MAX_SPU_PROGRAMS);
		for (spu_program_unique_id i=0;i<MAX_SPU_PROGRAMS;i++){
			free_spuid.push_back(i);
		}
	};
	~spu_register(){};
	
	spu_program_unique_id register_program(uint32_t queue_size)
	{
		if (free_spuid.empty()) { return -1; }

		spu_program_unique_id id = free_spuid.back();

		spuid[id].id=id;

		spuid[id].in_use=1;

		spuid[id].active=false;
	
		spuid[id].mqsize=queue_size;	
	
		spu_bound_message *d;
	//	memset(d,0,sizeof(spu_bound_message)*queue_size);
		d=new spu_bound_message[queue_size];
	
	//	spuid[id].mqpointer=d;

		free_spuid.pop_back();

		return id;
 	};

	int register_spu_message(spu_program_unique_id id, spu_bound_message msg)
	{
		bool written;

		for (int i = 0; i < spuid[id].mqsize;i++)
		{

			if (!spuid[id].mqpointer[i].active)
			{
				pthread_mutex_lock(&spuid[id].lock);
				//spuid[id].lock.enterMutex();
				if (!spuid[id].mqpointer[i].active ) //case where someone wrote to it while we where trying to lock it
				{
					pthread_mutex_unlock(&spuid[id].lock);
				} else {
					strcpy(spuid[id].mqpointer[i].acDetails,msg.acDetails);
					spuid[id].mqpointer[i].message0=msg.message0;
					spuid[id].mqpointer[i].message1=msg.message1;
					spuid[id].mqpointer[i].message2=msg.message2;
					spuid[id].mqpointer[i].active=true; // this is what the spu will be looking for before lock reading perhaps
					pthread_mutex_unlock(&spuid[id].lock);
					break;
				}
			}
		}

	}	

	void unregister_program(spu_program_unique_id id)
	{
		if (spuid[id].in_use) // to avoid un used id's getting pushed back ito the free_spuid because of bad programmers
		{
			spuid[id].in_use=false;
			free_spuid.push_back(id);
		}
	}
	
	//void set_priotiry(spu_program_unique_id,priority);
	//void set_load_interval(spu_program_unique_id,load_interval);
	public:
	bool is_active(spu_program_unique_id id) {return spuid[id].active;}
	bool is_in_use(spu_program_unique_id id) {return spuid[id].in_use;}
	void set_active(spu_program_unique_id id) {spuid[id].active=true;}
	
	
	protected:
	spu_program spuid[MAX_SPU_PROGRAMS];
	vector<spu_program_unique_id>  free_spuid;

};


#endif

