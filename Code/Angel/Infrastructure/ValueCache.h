#pragma once

#define CREATE_VALUECACHE_FUNCTOR( type, objClass, instance, method ) \
	new ValueCache<type, objClass>::Functor<type,objClass>(instance, &objClass::method)

template<class T, class C>
class ValueCache
{
public:

	template<class T2, class C2>
	class Functor
	{
	public:

		Functor( C2* obj, void(C2::*fpt)( T2& ) )
		{
			_obj = obj;
			_delegate = fpt;
		}

		void operator()(T2& val)
		{
			if( _obj != NULL)
				(*_obj.*_delegate)(val);
		}
	private:
		C2* _obj;
		void (C2::*_delegate)( T2& );
	};

	ValueCache(Functor<T,C>* del)
	{
		_dirty = true;
		_delegate = del;
	}

	~ValueCache()
	{
		if( _delegate != NULL)
			delete _delegate;
	}

	T& Value()
	{
		if (_dirty)
		{
			(*_delegate)( _cachedValue);
			_dirty = false;
		}
		return _cachedValue;
	}

	void Dirty()
	{
		_dirty = true;
	}

private:
	T _cachedValue;
	bool _dirty;
	Functor<T,C>* _delegate;
};
