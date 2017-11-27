// speed_calculator.h: interface for the speed_calculator class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _SPEED_CALCULATOR_072C2751_2829_47B4_9AD4_895DA0DDC065_H__
#define _SPEED_CALCULATOR_072C2751_2829_47B4_9AD4_895DA0DDC065_H__
/*
该数据计算类目前有一个问题，GetTickCount()在系统运行到49.7天后会归零，该情况未处理
*/

///速度计算器，用来计算FPS
class speed_calculator  
{
public:
	// cycle 表示计算速度时，从当前时间往前推，参与计算的样本数
	// unit 表示每个样本收集数据的时间跨度，单位毫秒
	speed_calculator(uint64_t cycle, uint64_t unit = 1, int need_lock = 0);
	virtual ~speed_calculator();

	void add_bytes( unsigned int bytes );
    uint64_t speed_value( void ); // 获得当前的速度，单位是字节/秒

    void clear(); // 清空所有速度，从零开始

protected:
    void update( uint64_t tickcount );
    void clean( uint64_t start_index, uint64_t end_index );

private:
	    //只要有指针成员，就必须要定义拷贝构造函数和重载=
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
