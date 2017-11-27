// speed_calculator.h: interface for the speed_calculator class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _SPEED_CALCULATOR_072C2751_2829_47B4_9AD4_895DA0DDC065_H__
#define _SPEED_CALCULATOR_072C2751_2829_47B4_9AD4_895DA0DDC065_H__
/*
�����ݼ�����Ŀǰ��һ�����⣬GetTickCount()��ϵͳ���е�49.7������㣬�����δ����
*/

///�ٶȼ���������������FPS
class speed_calculator  
{
public:
	// cycle ��ʾ�����ٶ�ʱ���ӵ�ǰʱ����ǰ�ƣ���������������
	// unit ��ʾÿ�������ռ����ݵ�ʱ���ȣ���λ����
	speed_calculator(uint64_t cycle, uint64_t unit = 1, int need_lock = 0);
	virtual ~speed_calculator();

	void add_bytes( unsigned int bytes );
    uint64_t speed_value( void ); // ��õ�ǰ���ٶȣ���λ���ֽ�/��

    void clear(); // ��������ٶȣ����㿪ʼ

protected:
    void update( uint64_t tickcount );
    void clean( uint64_t start_index, uint64_t end_index );

private:
	    //ֻҪ��ָ���Ա���ͱ���Ҫ���忽�����캯��������=
	speed_calculator(const speed_calculator &calculator);
	speed_calculator &operator = (const speed_calculator &calculator);

private:
	unsigned int *_samples_ptr;
    uint64_t _start_index;
	uint64_t _end_index;
	uint64_t _cycle;
	uint64_t _unit;
	int m_need_lock;
	pthread_mutex_t  m_lock;
};

#endif  
