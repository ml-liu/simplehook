// speed_calculator.cpp: implementation of the speed_calculator class.
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>
#include "common.h"
#include "speed_calculator.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define MIN(a, b) ((a) > (b)?(b):(a))

speed_calculator::speed_calculator( uint64_t  cycle, uint64_t  unit, int need_lock )
{
    _cycle  = cycle;
    _unit   = unit;

    _start_index = current_msecond()/_unit;
	_end_index = _start_index + 1;

	_samples_ptr = new unsigned int[_cycle];
    memset( _samples_ptr, 0, sizeof(unsigned int)*_cycle );

	m_need_lock = need_lock;

	if(m_need_lock == 1){
		pthread_mutex_init(&this->m_lock,NULL); 
	}
}

speed_calculator::~speed_calculator()
{
	if ( NULL != _samples_ptr )
	{
		delete [] _samples_ptr;
	}
	_samples_ptr = NULL;	
}

void speed_calculator::clean( uint64_t  start_index, uint64_t  end_index )
{
    if ( start_index >= end_index )
    {
        return;
    }

    uint64_t unit_count = end_index-start_index;
    unit_count = MIN( unit_count, _cycle );
    uint64_t  i = 0;
    for ( i=0; i<unit_count; i++ )
    {
        _samples_ptr[(start_index+i)%_cycle] = 0;
    }
}

void speed_calculator::update( uint64_t tickcount )
{
    uint64_t  current_index = tickcount/_unit;
    
    clean( _end_index, current_index + 1 );
    
    _end_index = current_index + 1;
    if (  _end_index - _start_index > _cycle )   //_start_index < _end_index - _cycle )
    {
        _start_index = _end_index - _cycle;
    }
    
}

void speed_calculator::add_bytes( unsigned int bytes )
{
    uint64_t tickcount = current_msecond();
    uint64_t current_index = tickcount/_unit;


	if(m_need_lock)
		pthread_mutex_lock(&this->m_lock);
	
    update( tickcount );
    
    _samples_ptr[current_index%_cycle] += bytes;

	if(m_need_lock)
		pthread_mutex_unlock(&this->m_lock);	
}

uint64_t speed_calculator::speed_value(void)
{
    uint64_t  tickcount = current_msecond();

	if(m_need_lock)
		pthread_mutex_lock(&this->m_lock);	
    
    update( tickcount );

    uint64_t total = 0;

    uint64_t  unit_count = _end_index-_start_index;
    uint64_t  i = 0;
    for ( i=0; i<unit_count; i++ )
    {
        total += _samples_ptr[(_start_index+i)%_cycle];
    }

	if(m_need_lock)
		pthread_mutex_unlock(&this->m_lock);	

    uint64_t temp = unit_count*_unit>0?unit_count*_unit:1;

    return (total*1000)/(temp);
}

void speed_calculator::clear()
{
    _start_index = current_msecond()/_unit;
    _end_index = _start_index + 1;    
    memset( _samples_ptr, 0, sizeof(unsigned int)*_cycle );
}

