/* -----------------------------------------------------------------------------
 * See the LICENSE file for information on copyright, usage and redistribution
 * of SWIG, and the README file for authors - http://www.swig.org/release.html.
 *
 * std_set.i
 *
 * std::set typemaps for LUA
 * ----------------------------------------------------------------------------- */

%{
#include <set>
%}
%include <std_except.i> // the general exepctions
/*
A really cut down version of the set class.

It would be useful to have a set<->Lua table conversion routine

*/
namespace std {

	template<class T>
    class set {
      public:
        set();
        set(unsigned int);
        set(const set&);
        set(unsigned int,T);
        unsigned int size() const;
        unsigned int max_size() const;
        bool empty() const;
        void clear();
        void insert(T val);
        void erase();
    };

}

