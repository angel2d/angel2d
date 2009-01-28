
#ifndef __CALLBACK_H__
#define __CALLBACK_H__

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

    private:
        ClassInstance*	_instance;
        FunctionPointer  _function;
};

#endif //__CALLBACK_H__