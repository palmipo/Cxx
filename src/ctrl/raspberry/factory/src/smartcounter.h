#ifndef SMART_COUNTER_H
#define SMART_COUNTER_H

#include <string>

template <class T>
class SmartCounter
{
	public:
		SmartCounter();
		SmartCounter(const std::string &, const T &);
	
		SmartCounter < T > & operator++();
		SmartCounter < T > & operator--();

		virtual int32_t count() const;
		virtual const std::string & name() const;

		const T & instance() const;

	protected:
		int32_t _nb_instance;
		std::string _ctrl_id;
		T _instance;
};

#endif

template < class T >
SmartCounter < T >::SmartCounter()
: _ctrl_id(std::string())
, _nb_instance(0)
, _instance(0)
{}

template < class T >
SmartCounter < T >::SmartCounter(const std::string & name, const T & t)
: _ctrl_id(name)
, _nb_instance(0)
, _instance(t)
{}

template < class T >
SmartCounter < T > & SmartCounter < T >::operator++()
{
	_nb_instance += 1;
	return *this;
}

template < class T >
SmartCounter < T > & SmartCounter < T >::operator--()
{
	_nb_instance -=1;
	return *this;
}

template < class T >
int32_t SmartCounter < T >::count() const
{
	return _nb_instance;
}

template < class T >
const std::string & SmartCounter < T >::name() const
{
	return _ctrl_id;
}

template < class T >
const T & SmartCounter < T >::instance() const
{
	return _instance;
}
