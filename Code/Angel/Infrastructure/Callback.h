#pragma once 

///A callback template to simplify storage/retrieval of method pointers
/** 
 * Storing pointers to member functions (as opposed to just loose functions)
 *  can be complicated and error-prone. This template class is designed to make
 *  such things simpler. An example usage is in the SoundDevice class. 
 * 
 * Note that this template only lets you store callbacks that take a single
 *  parameter. 
 */
template <class ClassInstance, class ParamType>
class TGenericCallback
{
public:
	TGenericCallback()
	{
		_function = 0;
	}
	
	typedef void (ClassInstance::*FunctionPointer)(ParamType param);
	
	virtual void Execute(ParamType param) const
	{
		if (_function) 
			(_instance->*_function)(param);
		else 
			printf("WARNING: No callback function specified!");
	}
	
	void SetCallback(	ClassInstance* instance, 
						FunctionPointer function)
	{
		_instance = instance;
		_function = function;
	}
	
	const ClassInstance* GetInstance()
	{
		return _instance;
	}
	
	const FunctionPointer GetFunction()
	{
		return _function;
	}
	
private:
	ClassInstance*	_instance;
	FunctionPointer  _function;
};
