#ifndef CALLBACK_H
#define CALLBACK_H

template <class T>
class Callback
{
	public:
		Callback(T cb, void * data)
		: _callback(cb)
		, _data(data)
		{}

		virtual ~Callback()
		{}

		void call(void * ctx)
		{
			if (_callback)
			{
				_callback(ctx, _data);
			}
		}

	protected:
		T _callback;
		void * _data;
};

#endif /* CALLBACK_H */
