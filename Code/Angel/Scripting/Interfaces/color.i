%module angel
%{
#include "../../Infrastructure/Color.h"
%}

#ifdef SWIGPYTHON
//all this junk just lets us treat lists as Colors
%typemap(in) Color
{
	bool error = false;
	if (PyList_Check($input))
	{
		int arrLength = PyList_Size($input);
		if (arrLength < 3)
		{
			error = true;
		}
		else
		{
			PyObject* pr = PyList_GetItem($input, 0);
			PyObject* pg = PyList_GetItem($input, 1);
			PyObject* pb = PyList_GetItem($input, 2);
			
			float r, g, b, a;
			if (PyFloat_Check(pr))
			{
				r = PyFloat_AsDouble(pr);
			}
			else if (PyInt_Check(pr))
			{
				r = (float)PyInt_AsLong(pr);
			}
			else
			{
				error = true;
			}
			
			if (PyFloat_Check(pg))
			{
				g = PyFloat_AsDouble(pg);
			}
			else if (PyInt_Check(pg))
			{
				g = (float)PyInt_AsLong(pg);
			}
			else
			{
				error = true;
			}
			
			if (PyFloat_Check(pb))
			{
				b = PyFloat_AsDouble(pb);
			}
			else if (PyInt_Check(pg))
			{
				b = (float)PyInt_AsLong(pb);
			}
			else
			{
				error = true;
			}
			if (arrLength < 4)
			{
				a = 1.0f;
			}
			else
			{
				PyObject* pa = PyList_GetItem($input, 3);
				
				if (PyFloat_Check(pa))
				{
					a = PyFloat_AsDouble(pa);
				}
				else if (PyInt_Check(pa))
				{
					a = (float)PyInt_AsLong(pa);
				}
				else
				{
					error = true;
				}
			}
			
			if (!error)
			{
				$1 = Color(r, g, b, a);
			}
		}
	}
	else
	{
		error = true;
	}
	
	if (error)
	{
		int result;
		void* arg_pointer;
		result = SWIG_ConvertPtr($input, &arg_pointer, SWIGTYPE_p_Vector2,  0 );
		if (!SWIG_IsOK(result)) {
			%argument_fail(result,"$type", $symname, $argnum);
		}  
		if (!arg_pointer) {
			%argument_nullref("$type", $symname, $argnum);
		} else {
			$1 = *(reinterpret_cast< Color * >(arg_pointer));
		}
	}
}

%typecheck(SWIG_TYPECHECK_POINTER) Color
{
	if (PyList_Check($input))
	{
		$1 = 1;
	}
	else
	{
		PyObject* classType = PyObject_GetAttrString($input, "__class__");
		PyObject* pythonName = PyObject_GetAttrString(classType, "__name__");
		const char* className = PyString_AsString(pythonName);
		int length = PyString_Size(pythonName);
		if (strncmp("Color", className, length) == 0)
		{
			$1 = 1;
		}
		else
		{
			$1 = 0;
		}
	}
}
#endif

class Color
{
public:
	float R, G, B, A;
	
	Color();
	Color(float r, float g, float b, float a=1.0f);
	Color(int r, int g, int b, int a=255);
	Color(String hexString);
	
	bool operator==(const Color &c) const;
	bool operator!=(const Color &c) const;
	
	Color operator-(const Color &c) const;
	Color operator+(const Color &c) const;
	Color operator/(float divider) const;
	Color operator*(float scaleFactor) const;
};
