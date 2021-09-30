#ifndef CALLBACK_H
#define CALLBACK_H

template <class T, class U, class V>
class Callback
{
	public:
		Callback(T cb, U ctx)
		: _callback(cb)
		, _ctx(ctx)
		{}

		virtual ~Callback()
		{}

		void call(V data)
		{
			if (_callback)
			{
				_callback(_ctx, data);
			}
		}

	protected:
		T _callback;
		U _ctx;
};

#endif /* CALLBACK_H */
