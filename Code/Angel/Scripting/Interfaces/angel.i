%module angel

%include <attribute.i>
%include <std_set.i>
%include <std_vector.i>
%include <std_string.i>

%include inheritance.i

%typemap(in, noblock=1) SWIGTYPE *ANGEL_DISOWN (int res = 0) {
	res = SWIG_ConvertPtr($input, %as_voidptrptr(&$1), $descriptor, SWIG_POINTER_DISOWN | %convertptr_flags);
	if (!SWIG_IsOK(res)) {
		%argument_fail(res,"$type", $symname, $argnum);
	}
	{
		Swig::Director *director = dynamic_cast<Swig::Director *>($1);
		if (director) director->swig_disown();		
	}
}

typedef std::string			String;
typedef std::set<String>	StringSet;
typedef std::vector<String>	StringList;
%template(StringSet)		std::set<std::string>;
%template(StringList)		std::vector<std::string>;

%include vector2.i
%include color.i
%include messaging.i
%include renderable.i

%include world.i
%include log.i
%include console.i
%include tuning.i
%include sound.i
%include controller.i
%include mouse.i
%include actor.i
%include camera.i
%include physics_actor.i
%include particles.i
%include text_actor.i
