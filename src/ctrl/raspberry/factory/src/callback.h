#ifndef CALLBACK_H
#define CALLBACK_H

template <class T, class U, class V>
class Callback
{
	public:
		Callback()
		{}

		Callback(T cb, U ctx)
		: _callback(cb)
		, _ctx(ctx)
		{}

		virtual ~Callback()
		{}

		void set(T cb, U ctx)
		{
			_callback=cb;
			_ctx=ctx;
		}

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
