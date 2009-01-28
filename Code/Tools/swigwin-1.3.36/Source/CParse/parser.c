/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     HBLOCK = 259,
     POUND = 260,
     STRING = 261,
     INCLUDE = 262,
     IMPORT = 263,
     INSERT = 264,
     CHARCONST = 265,
     NUM_INT = 266,
     NUM_FLOAT = 267,
     NUM_UNSIGNED = 268,
     NUM_LONG = 269,
     NUM_ULONG = 270,
     NUM_LONGLONG = 271,
     NUM_ULONGLONG = 272,
     TYPEDEF = 273,
     TYPE_INT = 274,
     TYPE_UNSIGNED = 275,
     TYPE_SHORT = 276,
     TYPE_LONG = 277,
     TYPE_FLOAT = 278,
     TYPE_DOUBLE = 279,
     TYPE_CHAR = 280,
     TYPE_WCHAR = 281,
     TYPE_VOID = 282,
     TYPE_SIGNED = 283,
     TYPE_BOOL = 284,
     TYPE_COMPLEX = 285,
     TYPE_TYPEDEF = 286,
     TYPE_RAW = 287,
     TYPE_NON_ISO_INT8 = 288,
     TYPE_NON_ISO_INT16 = 289,
     TYPE_NON_ISO_INT32 = 290,
     TYPE_NON_ISO_INT64 = 291,
     LPAREN = 292,
     RPAREN = 293,
     COMMA = 294,
     SEMI = 295,
     EXTERN = 296,
     INIT = 297,
     LBRACE = 298,
     RBRACE = 299,
     PERIOD = 300,
     CONST_QUAL = 301,
     VOLATILE = 302,
     REGISTER = 303,
     STRUCT = 304,
     UNION = 305,
     EQUAL = 306,
     SIZEOF = 307,
     MODULE = 308,
     LBRACKET = 309,
     RBRACKET = 310,
     ILLEGAL = 311,
     CONSTANT = 312,
     NAME = 313,
     RENAME = 314,
     NAMEWARN = 315,
     EXTEND = 316,
     PRAGMA = 317,
     FEATURE = 318,
     VARARGS = 319,
     ENUM = 320,
     CLASS = 321,
     TYPENAME = 322,
     PRIVATE = 323,
     PUBLIC = 324,
     PROTECTED = 325,
     COLON = 326,
     STATIC = 327,
     VIRTUAL = 328,
     FRIEND = 329,
     THROW = 330,
     CATCH = 331,
     EXPLICIT = 332,
     USING = 333,
     NAMESPACE = 334,
     NATIVE = 335,
     INLINE = 336,
     TYPEMAP = 337,
     EXCEPT = 338,
     ECHO = 339,
     APPLY = 340,
     CLEAR = 341,
     SWIGTEMPLATE = 342,
     FRAGMENT = 343,
     WARN = 344,
     LESSTHAN = 345,
     GREATERTHAN = 346,
     MODULO = 347,
     DELETE_KW = 348,
     LESSTHANOREQUALTO = 349,
     GREATERTHANOREQUALTO = 350,
     EQUALTO = 351,
     NOTEQUALTO = 352,
     QUESTIONMARK = 353,
     TYPES = 354,
     PARMS = 355,
     NONID = 356,
     DSTAR = 357,
     DCNOT = 358,
     TEMPLATE = 359,
     OPERATOR = 360,
     COPERATOR = 361,
     PARSETYPE = 362,
     PARSEPARM = 363,
     PARSEPARMS = 364,
     CAST = 365,
     LOR = 366,
     LAND = 367,
     OR = 368,
     XOR = 369,
     AND = 370,
     RSHIFT = 371,
     LSHIFT = 372,
     MINUS = 373,
     PLUS = 374,
     MODULUS = 375,
     SLASH = 376,
     STAR = 377,
     LNOT = 378,
     NOT = 379,
     UMINUS = 380,
     DCOLON = 381
   };
#endif
/* Tokens.  */
#define ID 258
#define HBLOCK 259
#define POUND 260
#define STRING 261
#define INCLUDE 262
#define IMPORT 263
#define INSERT 264
#define CHARCONST 265
#define NUM_INT 266
#define NUM_FLOAT 267
#define NUM_UNSIGNED 268
#define NUM_LONG 269
#define NUM_ULONG 270
#define NUM_LONGLONG 271
#define NUM_ULONGLONG 272
#define TYPEDEF 273
#define TYPE_INT 274
#define TYPE_UNSIGNED 275
#define TYPE_SHORT 276
#define TYPE_LONG 277
#define TYPE_FLOAT 278
#define TYPE_DOUBLE 279
#define TYPE_CHAR 280
#define TYPE_WCHAR 281
#define TYPE_VOID 282
#define TYPE_SIGNED 283
#define TYPE_BOOL 284
#define TYPE_COMPLEX 285
#define TYPE_TYPEDEF 286
#define TYPE_RAW 287
#define TYPE_NON_ISO_INT8 288
#define TYPE_NON_ISO_INT16 289
#define TYPE_NON_ISO_INT32 290
#define TYPE_NON_ISO_INT64 291
#define LPAREN 292
#define RPAREN 293
#define COMMA 294
#define SEMI 295
#define EXTERN 296
#define INIT 297
#define LBRACE 298
#define RBRACE 299
#define PERIOD 300
#define CONST_QUAL 301
#define VOLATILE 302
#define REGISTER 303
#define STRUCT 304
#define UNION 305
#define EQUAL 306
#define SIZEOF 307
#define MODULE 308
#define LBRACKET 309
#define RBRACKET 310
#define ILLEGAL 311
#define CONSTANT 312
#define NAME 313
#define RENAME 314
#define NAMEWARN 315
#define EXTEND 316
#define PRAGMA 317
#define FEATURE 318
#define VARARGS 319
#define ENUM 320
#define CLASS 321
#define TYPENAME 322
#define PRIVATE 323
#define PUBLIC 324
#define PROTECTED 325
#define COLON 326
#define STATIC 327
#define VIRTUAL 328
#define FRIEND 329
#define THROW 330
#define CATCH 331
#define EXPLICIT 332
#define USING 333
#define NAMESPACE 334
#define NATIVE 335
#define INLINE 336
#define TYPEMAP 337
#define EXCEPT 338
#define ECHO 339
#define APPLY 340
#define CLEAR 341
#define SWIGTEMPLATE 342
#define FRAGMENT 343
#define WARN 344
#define LESSTHAN 345
#define GREATERTHAN 346
#define MODULO 347
#define DELETE_KW 348
#define LESSTHANOREQUALTO 349
#define GREATERTHANOREQUALTO 350
#define EQUALTO 351
#define NOTEQUALTO 352
#define QUESTIONMARK 353
#define TYPES 354
#define PARMS 355
#define NONID 356
#define DSTAR 357
#define DCNOT 358
#define TEMPLATE 359
#define OPERATOR 360
#define COPERATOR 361
#define PARSETYPE 362
#define PARSEPARM 363
#define PARSEPARMS 364
#define CAST 365
#define LOR 366
#define LAND 367
#define OR 368
#define XOR 369
#define AND 370
#define RSHIFT 371
#define LSHIFT 372
#define MINUS 373
#define PLUS 374
#define MODULUS 375
#define SLASH 376
#define STAR 377
#define LNOT 378
#define NOT 379
#define UMINUS 380
#define DCOLON 381




/* Copy the first part of user declarations.  */
#line 12 "parser.y"


#define yylex yylex

char cvsroot_parser_y[] = "$Id: parser.y 10540 2008-06-21 15:23:02Z wsfulton $";

#include "swig.h"
#include "cparse.h"
#include "preprocessor.h"
#include <ctype.h>

/* We do this for portability */
#undef alloca
#define alloca malloc

/* -----------------------------------------------------------------------------
 *                               Externals
 * ----------------------------------------------------------------------------- */

int  yyparse();

/* NEW Variables */

static Node    *top = 0;      /* Top of the generated parse tree */
static int      unnamed = 0;  /* Unnamed datatype counter */
static Hash    *extendhash = 0;     /* Hash table of added methods */
static Hash    *classes = 0;        /* Hash table of classes */
static Symtab  *prev_symtab = 0;
static Node    *current_class = 0;
String  *ModuleName = 0;
static Node    *module_node = 0;
static String  *Classprefix = 0;  
static String  *Namespaceprefix = 0;
static int      inclass = 0;
static char    *last_cpptype = 0;
static int      inherit_list = 0;
static Parm    *template_parameters = 0;
static int      extendmode   = 0;
static int      compact_default_args = 0;
static int      template_reduce = 0;
static int      cparse_externc = 0;

static int      max_class_levels = 0;
static int      class_level = 0;
static Node   **class_decl = NULL;

/* -----------------------------------------------------------------------------
 *                            Assist Functions
 * ----------------------------------------------------------------------------- */


 
/* Called by the parser (yyparse) when an error is found.*/
static void yyerror (const char *e) {
  (void)e;
}

static Node *new_node(const String_or_char *tag) {
  Node *n = NewHash();
  set_nodeType(n,tag);
  Setfile(n,cparse_file);
  Setline(n,cparse_line);
  return n;
}

/* Copies a node.  Does not copy tree links or symbol table data (except for
   sym:name) */

static Node *copy_node(Node *n) {
  Node *nn;
  Iterator k;
  nn = NewHash();
  Setfile(nn,Getfile(n));
  Setline(nn,Getline(n));
  for (k = First(n); k.key; k = Next(k)) {
    String *ci;
    String *key = k.key;
    char *ckey = Char(key);
    if ((strcmp(ckey,"nextSibling") == 0) ||
	(strcmp(ckey,"previousSibling") == 0) ||
	(strcmp(ckey,"parentNode") == 0) ||
	(strcmp(ckey,"lastChild") == 0)) {
      continue;
    }
    if (Strncmp(key,"csym:",5) == 0) continue;
    /* We do copy sym:name.  For templates */
    if ((strcmp(ckey,"sym:name") == 0) || 
	(strcmp(ckey,"sym:weak") == 0) ||
	(strcmp(ckey,"sym:typename") == 0)) {
      String *ci = Copy(k.item);
      Setattr(nn,key, ci);
      Delete(ci);
      continue;
    }
    if (strcmp(ckey,"sym:symtab") == 0) {
      Setattr(nn,"sym:needs_symtab", "1");
    }
    /* We don't copy any other symbol table attributes */
    if (strncmp(ckey,"sym:",4) == 0) {
      continue;
    }
    /* If children.  We copy them recursively using this function */
    if (strcmp(ckey,"firstChild") == 0) {
      /* Copy children */
      Node *cn = k.item;
      while (cn) {
	Node *copy = copy_node(cn);
	appendChild(nn,copy);
	Delete(copy);
	cn = nextSibling(cn);
      }
      continue;
    }
    /* We don't copy the symbol table.  But we drop an attribute 
       requires_symtab so that functions know it needs to be built */

    if (strcmp(ckey,"symtab") == 0) {
      /* Node defined a symbol table. */
      Setattr(nn,"requires_symtab","1");
      continue;
    }
    /* Can't copy nodes */
    if (strcmp(ckey,"node") == 0) {
      continue;
    }
    if ((strcmp(ckey,"parms") == 0) || (strcmp(ckey,"pattern") == 0) || (strcmp(ckey,"throws") == 0)
	|| (strcmp(ckey,"kwargs") == 0)) {
      ParmList *pl = CopyParmList(k.item);
      Setattr(nn,key,pl);
      Delete(pl);
      continue;
    }
    /* Looks okay.  Just copy the data using Copy */
    ci = Copy(k.item);
    Setattr(nn, key, ci);
    Delete(ci);
  }
  return nn;
}

/* -----------------------------------------------------------------------------
 *                              Variables
 * ----------------------------------------------------------------------------- */

static char  *typemap_lang = 0;    /* Current language setting */

static int cplus_mode  = 0;
static String  *class_rename = 0;

/* C++ modes */

#define  CPLUS_PUBLIC    1
#define  CPLUS_PRIVATE   2
#define  CPLUS_PROTECTED 3

/* include types */
static int   import_mode = 0;

void SWIG_typemap_lang(const char *tm_lang) {
  typemap_lang = Swig_copy_string(tm_lang);
}

void SWIG_cparse_set_compact_default_args(int defargs) {
  compact_default_args = defargs;
}

int SWIG_cparse_template_reduce(int treduce) {
  template_reduce = treduce;
  return treduce;  
}

/* -----------------------------------------------------------------------------
 *                           Assist functions
 * ----------------------------------------------------------------------------- */

static int promote_type(int t) {
  if (t <= T_UCHAR || t == T_CHAR) return T_INT;
  return t;
}

/* Perform type-promotion for binary operators */
static int promote(int t1, int t2) {
  t1 = promote_type(t1);
  t2 = promote_type(t2);
  return t1 > t2 ? t1 : t2;
}

static String *yyrename = 0;

/* Forward renaming operator */

static String *resolve_node_scope(String *cname);


Hash *Swig_cparse_features() {
  static Hash   *features_hash = 0;
  if (!features_hash) features_hash = NewHash();
  return features_hash;
}

static String *feature_identifier_fix(String *s) {
  if (SwigType_istemplate(s)) {
    String *tp, *ts, *ta, *tq;
    tp = SwigType_templateprefix(s);
    ts = SwigType_templatesuffix(s);
    ta = SwigType_templateargs(s);
    tq = Swig_symbol_type_qualify(ta,0);
    Append(tp,tq);
    Append(tp,ts);
    Delete(ts);
    Delete(ta);
    Delete(tq);
    return tp;
  } else {
    return NewString(s);
  }
}

/* Generate the symbol table name for an object */
/* This is a bit of a mess. Need to clean up */
static String *add_oldname = 0;



static String *make_name(Node *n, String *name,SwigType *decl) {
  int destructor = name && (*(Char(name)) == '~');

  if (yyrename) {
    String *s = NewString(yyrename);
    Delete(yyrename);
    yyrename = 0;
    if (destructor  && (*(Char(s)) != '~')) {
      Insert(s,0,"~");
    }
    return s;
  }

  if (!name) return 0;
  return Swig_name_make(n,Namespaceprefix,name,decl,add_oldname);
}

/* Generate an unnamed identifier */
static String *make_unnamed() {
  unnamed++;
  return NewStringf("$unnamed%d$",unnamed);
}

/* Return if the node is a friend declaration */
static int is_friend(Node *n) {
  return Cmp(Getattr(n,"storage"),"friend") == 0;
}

static int is_operator(String *name) {
  return Strncmp(name,"operator ", 9) == 0;
}


/* Add declaration list to symbol table */
static int  add_only_one = 0;

static void add_symbols(Node *n) {
  String *decl;
  String *wrn = 0;
  if (inclass && n) {
    cparse_normalize_void(n);
  }
  while (n) {
    String *symname = 0;
    /* for friends, we need to pop the scope once */
    String *old_prefix = 0;
    Symtab *old_scope = 0;
    int isfriend = inclass && is_friend(n);
    int iscdecl = Cmp(nodeType(n),"cdecl") == 0;
    int only_csymbol = 0;
    if (extendmode) {
      Setattr(n,"isextension","1");
    }
    
    if (inclass) {
      String *name = Getattr(n, "name");
      if (isfriend) {
	/* for friends, we need to add the scopename if needed */
	String *prefix = name ? Swig_scopename_prefix(name) : 0;
	old_prefix = Namespaceprefix;
	old_scope = Swig_symbol_popscope();
	Namespaceprefix = Swig_symbol_qualifiedscopename(0);
	if (!prefix) {
	  if (name && !is_operator(name) && Namespaceprefix) {
	    String *nname = NewStringf("%s::%s", Namespaceprefix, name);
	    Setattr(n,"name",nname);
	    Delete(nname);
	  }
	} else {
	  Symtab *st = Swig_symbol_getscope(prefix);
	  String *ns = st ? Getattr(st,"name") : prefix;
	  String *base  = Swig_scopename_last(name);
	  String *nname = NewStringf("%s::%s", ns, base);
	  Setattr(n,"name",nname);
	  Delete(nname);
	  Delete(base);
	  Delete(prefix);
	}
	Namespaceprefix = 0;
      } else {
	/* for member functions, we need to remove the redundant
	   class scope if provided, as in
	   
	   struct Foo {
	   int Foo::method(int a);
	   };
	   
	*/
	String *prefix = name ? Swig_scopename_prefix(name) : 0;
	if (prefix) {
	  if (Classprefix && (Equal(prefix,Classprefix))) {
	    String *base = Swig_scopename_last(name);
	    Setattr(n,"name",base);
	    Delete(base);
	  }
	  Delete(prefix);
	}

        /*
	if (!Getattr(n,"parentNode") && class_level) set_parentNode(n,class_decl[class_level - 1]);
        */
	Setattr(n,"ismember","1");
      }
    }
    if (!isfriend && inclass) {
      if ((cplus_mode != CPLUS_PUBLIC)) {
	only_csymbol = 1;
	if (cplus_mode == CPLUS_PROTECTED) {
	  Setattr(n,"access", "protected");
	  only_csymbol = !Swig_need_protected(n);
	} else {
	  Setattr(n,"access", "private");
	  /* private are needed only when they are pure virtuals - why? */
	  if ((Cmp(Getattr(n,"storage"),"virtual") == 0) && (Cmp(Getattr(n,"value"),"0") == 0)) {
	    only_csymbol = 0;
	  }
	}
      } else {
	  Setattr(n,"access", "public");
      }
    }
    if (Getattr(n,"sym:name")) {
      n = nextSibling(n);
      continue;
    }
    decl = Getattr(n,"decl");
    if (!SwigType_isfunction(decl)) {
      String *name = Getattr(n,"name");
      String *makename = Getattr(n,"parser:makename");
      if (iscdecl) {	
	String *storage = Getattr(n, "storage");
	if (Cmp(storage,"typedef") == 0) {
	  Setattr(n,"kind","typedef");
	} else {
	  SwigType *type = Getattr(n,"type");
	  String *value = Getattr(n,"value");
	  Setattr(n,"kind","variable");
	  if (value && Len(value)) {
	    Setattr(n,"hasvalue","1");
	  }
	  if (type) {
	    SwigType *ty;
	    SwigType *tmp = 0;
	    if (decl) {
	      ty = tmp = Copy(type);
	      SwigType_push(ty,decl);
	    } else {
	      ty = type;
	    }
	    if (!SwigType_ismutable(ty)) {
	      SetFlag(n,"hasconsttype");
	      SetFlag(n,"feature:immutable");
	    }
	    if (tmp) Delete(tmp);
	  }
	  if (!type) {
	    Printf(stderr,"notype name %s\n", name);
	  }
	}
      }
      Swig_features_get(Swig_cparse_features(), Namespaceprefix, name, 0, n);
      if (makename) {
	symname = make_name(n, makename,0);
        Delattr(n,"parser:makename"); /* temporary information, don't leave it hanging around */
      } else {
        makename = name;
	symname = make_name(n, makename,0);
      }
      
      if (!symname) {
	symname = Copy(Getattr(n,"unnamed"));
      }
      if (symname) {
	wrn = Swig_name_warning(n, Namespaceprefix, symname,0);
      }
    } else {
      String *name = Getattr(n,"name");
      SwigType *fdecl = Copy(decl);
      SwigType *fun = SwigType_pop_function(fdecl);
      if (iscdecl) {	
	Setattr(n,"kind","function");
      }
      
      Swig_features_get(Swig_cparse_features(),Namespaceprefix,name,fun,n);

      symname = make_name(n, name,fun);
      wrn = Swig_name_warning(n, Namespaceprefix,symname,fun);
      
      Delete(fdecl);
      Delete(fun);
      
    }
    if (!symname) {
      n = nextSibling(n);
      continue;
    }
    if (only_csymbol || GetFlag(n,"feature:ignore")) {
      /* Only add to C symbol table and continue */
      Swig_symbol_add(0, n);
    } else if (strncmp(Char(symname),"$ignore",7) == 0) {
      char *c = Char(symname)+7;
      SetFlag(n,"feature:ignore");
      if (strlen(c)) {
	SWIG_WARN_NODE_BEGIN(n);
	Swig_warning(0,Getfile(n), Getline(n), "%s\n",c+1);
	SWIG_WARN_NODE_END(n);
      }
      Swig_symbol_add(0, n);
    } else {
      Node *c;
      if ((wrn) && (Len(wrn))) {
	String *metaname = symname;
	if (!Getmeta(metaname,"already_warned")) {
	  SWIG_WARN_NODE_BEGIN(n);
	  Swig_warning(0,Getfile(n),Getline(n), "%s\n", wrn);
	  SWIG_WARN_NODE_END(n);
	  Setmeta(metaname,"already_warned","1");
	}
      }
      c = Swig_symbol_add(symname,n);

      if (c != n) {
        /* symbol conflict attempting to add in the new symbol */
        if (Getattr(n,"sym:weak")) {
          Setattr(n,"sym:name",symname);
        } else {
          String *e = NewStringEmpty();
          String *en = NewStringEmpty();
          String *ec = NewStringEmpty();
          int redefined = Swig_need_redefined_warn(n,c,inclass);
          if (redefined) {
            Printf(en,"Identifier '%s' redefined (ignored)",symname);
            Printf(ec,"previous definition of '%s'",symname);
          } else {
            Printf(en,"Redundant redeclaration of '%s'",symname);
            Printf(ec,"previous declaration of '%s'",symname);
          }
          if (Cmp(symname,Getattr(n,"name"))) {
            Printf(en," (Renamed from '%s')", SwigType_namestr(Getattr(n,"name")));
          }
          Printf(en,",");
          if (Cmp(symname,Getattr(c,"name"))) {
            Printf(ec," (Renamed from '%s')", SwigType_namestr(Getattr(c,"name")));
          }
          Printf(ec,".");
	  SWIG_WARN_NODE_BEGIN(n);
          if (redefined) {
            Swig_warning(WARN_PARSE_REDEFINED,Getfile(n),Getline(n),"%s\n",en);
            Swig_warning(WARN_PARSE_REDEFINED,Getfile(c),Getline(c),"%s\n",ec);
          } else if (!is_friend(n) && !is_friend(c)) {
            Swig_warning(WARN_PARSE_REDUNDANT,Getfile(n),Getline(n),"%s\n",en);
            Swig_warning(WARN_PARSE_REDUNDANT,Getfile(c),Getline(c),"%s\n",ec);
          }
	  SWIG_WARN_NODE_END(n);
          Printf(e,"%s:%d:%s\n%s:%d:%s\n",Getfile(n),Getline(n),en,
                 Getfile(c),Getline(c),ec);
          Setattr(n,"error",e);
	  Delete(e);
          Delete(en);
          Delete(ec);
        }
      }
    }
    /* restore the class scope if needed */
    if (isfriend) {
      Swig_symbol_setscope(old_scope);
      if (old_prefix) {
	Delete(Namespaceprefix);
	Namespaceprefix = old_prefix;
      }
    }
    Delete(symname);

    if (add_only_one) return;
    n = nextSibling(n);
  }
}


/* add symbols a parse tree node copy */

static void add_symbols_copy(Node *n) {
  String *name;
  int    emode = 0;
  while (n) {
    char *cnodeType = Char(nodeType(n));

    if (strcmp(cnodeType,"access") == 0) {
      String *kind = Getattr(n,"kind");
      if (Strcmp(kind,"public") == 0) {
	cplus_mode = CPLUS_PUBLIC;
      } else if (Strcmp(kind,"private") == 0) {
	cplus_mode = CPLUS_PRIVATE;
      } else if (Strcmp(kind,"protected") == 0) {
	cplus_mode = CPLUS_PROTECTED;
      }
      n = nextSibling(n);
      continue;
    }

    add_oldname = Getattr(n,"sym:name");
    if ((add_oldname) || (Getattr(n,"sym:needs_symtab"))) {
      if (add_oldname) {
	DohIncref(add_oldname);
	/*  Disable this, it prevents %rename to work with templates */
	/* If already renamed, we used that name  */
	/*
	if (Strcmp(add_oldname, Getattr(n,"name")) != 0) {
	  Delete(yyrename);
	  yyrename = Copy(add_oldname);
	}
	*/
      }
      Delattr(n,"sym:needs_symtab");
      Delattr(n,"sym:name");

      add_only_one = 1;
      add_symbols(n);

      if (Getattr(n,"partialargs")) {
	Swig_symbol_cadd(Getattr(n,"partialargs"),n);
      }
      add_only_one = 0;
      name = Getattr(n,"name");
      if (Getattr(n,"requires_symtab")) {
	Swig_symbol_newscope();
	Swig_symbol_setscopename(name);
	Delete(Namespaceprefix);
	Namespaceprefix = Swig_symbol_qualifiedscopename(0);
      }
      if (strcmp(cnodeType,"class") == 0) {
	inclass = 1;
	current_class = n;
	if (Strcmp(Getattr(n,"kind"),"class") == 0) {
	  cplus_mode = CPLUS_PRIVATE;
	} else {
	  cplus_mode = CPLUS_PUBLIC;
	}
      }
      if (strcmp(cnodeType,"extend") == 0) {
	emode = cplus_mode;
	cplus_mode = CPLUS_PUBLIC;
      }
      add_symbols_copy(firstChild(n));
      if (strcmp(cnodeType,"extend") == 0) {
	cplus_mode = emode;
      }
      if (Getattr(n,"requires_symtab")) {
	Setattr(n,"symtab", Swig_symbol_popscope());
	Delattr(n,"requires_symtab");
	Delete(Namespaceprefix);
	Namespaceprefix = Swig_symbol_qualifiedscopename(0);
      }
      if (add_oldname) {
	Delete(add_oldname);
	add_oldname = 0;
      }
      if (strcmp(cnodeType,"class") == 0) {
	inclass = 0;
	current_class = 0;
      }
    } else {
      if (strcmp(cnodeType,"extend") == 0) {
	emode = cplus_mode;
	cplus_mode = CPLUS_PUBLIC;
      }
      add_symbols_copy(firstChild(n));
      if (strcmp(cnodeType,"extend") == 0) {
	cplus_mode = emode;
      }
    }
    n = nextSibling(n);
  }
}

/* Extension merge.  This function is used to handle the %extend directive
   when it appears before a class definition.   To handle this, the %extend
   actually needs to take precedence.  Therefore, we will selectively nuke symbols
   from the current symbol table, replacing them with the added methods */

static void merge_extensions(Node *cls, Node *am) {
  Node *n;
  Node *csym;

  n = firstChild(am);
  while (n) {
    String *symname;
    if (Strcmp(nodeType(n),"constructor") == 0) {
      symname = Getattr(n,"sym:name");
      if (symname) {
	if (Strcmp(symname,Getattr(n,"name")) == 0) {
	  /* If the name and the sym:name of a constructor are the same,
             then it hasn't been renamed.  However---the name of the class
             itself might have been renamed so we need to do a consistency
             check here */
	  if (Getattr(cls,"sym:name")) {
	    Setattr(n,"sym:name", Getattr(cls,"sym:name"));
	  }
	}
      } 
    }

    symname = Getattr(n,"sym:name");
    DohIncref(symname);
    if ((symname) && (!Getattr(n,"error"))) {
      /* Remove node from its symbol table */
      Swig_symbol_remove(n);
      csym = Swig_symbol_add(symname,n);
      if (csym != n) {
	/* Conflict with previous definition.  Nuke previous definition */
	String *e = NewStringEmpty();
	String *en = NewStringEmpty();
	String *ec = NewStringEmpty();
	Printf(ec,"Identifier '%s' redefined by %%extend (ignored),",symname);
	Printf(en,"%%extend definition of '%s'.",symname);
	SWIG_WARN_NODE_BEGIN(n);
	Swig_warning(WARN_PARSE_REDEFINED,Getfile(csym),Getline(csym),"%s\n",ec);
	Swig_warning(WARN_PARSE_REDEFINED,Getfile(n),Getline(n),"%s\n",en);
	SWIG_WARN_NODE_END(n);
	Printf(e,"%s:%d:%s\n%s:%d:%s\n",Getfile(csym),Getline(csym),ec, 
	       Getfile(n),Getline(n),en);
	Setattr(csym,"error",e);
	Delete(e);
	Delete(en);
	Delete(ec);
	Swig_symbol_remove(csym);              /* Remove class definition */
	Swig_symbol_add(symname,n);            /* Insert extend definition */
      }
    }
    n = nextSibling(n);
  }
}

static void append_previous_extension(Node *cls, Node *am) {
  Node *n, *ne;
  Node *pe = 0;
  Node *ae = 0;

  if (!am) return;
  
  n = firstChild(am);
  while (n) {
    ne = nextSibling(n);
    set_nextSibling(n,0);
    /* typemaps and fragments need to be prepended */
    if (((Cmp(nodeType(n),"typemap") == 0) || (Cmp(nodeType(n),"fragment") == 0)))  {
      if (!pe) pe = new_node("extend");
      appendChild(pe, n);
    } else {
      if (!ae) ae = new_node("extend");
      appendChild(ae, n);
    }    
    n = ne;
  }
  if (pe) prependChild(cls,pe);
  if (ae) appendChild(cls,ae);
}
 

/* Check for unused %extend.  Special case, don't report unused
   extensions for templates */
 
static void check_extensions() {
  Iterator ki;

  if (!extendhash) return;
  for (ki = First(extendhash); ki.key; ki = Next(ki)) {
    if (!Strchr(ki.key,'<')) {
      SWIG_WARN_NODE_BEGIN(ki.item);
      Swig_warning(WARN_PARSE_EXTEND_UNDEF,Getfile(ki.item), Getline(ki.item), "%%extend defined for an undeclared class %s.\n", ki.key);
      SWIG_WARN_NODE_END(ki.item);
    }
  }
}

/* Check a set of declarations to see if any are pure-abstract */

static List *pure_abstract(Node *n) {
  List *abs = 0;
  while (n) {
    if (Cmp(nodeType(n),"cdecl") == 0) {
      String *decl = Getattr(n,"decl");
      if (SwigType_isfunction(decl)) {
	String *init = Getattr(n,"value");
	if (Cmp(init,"0") == 0) {
	  if (!abs) {
	    abs = NewList();
	  }
	  Append(abs,n);
	  Setattr(n,"abstract","1");
	}
      }
    } else if (Cmp(nodeType(n),"destructor") == 0) {
      if (Cmp(Getattr(n,"value"),"0") == 0) {
	if (!abs) {
	  abs = NewList();
	}
	Append(abs,n);
	Setattr(n,"abstract","1");
      }
    }
    n = nextSibling(n);
  }
  return abs;
}

/* Make a classname */

static String *make_class_name(String *name) {
  String *nname = 0;
  if (Namespaceprefix) {
    nname= NewStringf("%s::%s", Namespaceprefix, name);
  } else {
    nname = NewString(name);
  }
  if (SwigType_istemplate(nname)) {
    String *prefix, *args, *qargs;
    prefix = SwigType_templateprefix(nname);
    args   = SwigType_templateargs(nname);
    qargs  = Swig_symbol_type_qualify(args,0);
    Append(prefix,qargs);
    Delete(nname);
    Delete(args);
    Delete(qargs);
    nname = prefix;
  }
  return nname;
}

static List *make_inherit_list(String *clsname, List *names) {
  int i, ilen;
  String *derived;
  List *bases = NewList();

  if (Namespaceprefix) derived = NewStringf("%s::%s", Namespaceprefix,clsname);
  else derived = NewString(clsname);

  ilen = Len(names);
  for (i = 0; i < ilen; i++) {
    Node *s;
    String *base;
    String *n = Getitem(names,i);
    /* Try to figure out where this symbol is */
    s = Swig_symbol_clookup(n,0);
    if (s) {
      while (s && (Strcmp(nodeType(s),"class") != 0)) {
	/* Not a class.  Could be a typedef though. */
	String *storage = Getattr(s,"storage");
	if (storage && (Strcmp(storage,"typedef") == 0)) {
	  String *nn = Getattr(s,"type");
	  s = Swig_symbol_clookup(nn,Getattr(s,"sym:symtab"));
	} else {
	  break;
	}
      }
      if (s && ((Strcmp(nodeType(s),"class") == 0) || (Strcmp(nodeType(s),"template") == 0))) {
	String *q = Swig_symbol_qualified(s);
	Append(bases,s);
	if (q) {
	  base = NewStringf("%s::%s", q, Getattr(s,"name"));
	  Delete(q);
	} else {
	  base = NewString(Getattr(s,"name"));
	}
      } else {
	base = NewString(n);
      }
    } else {
      base = NewString(n);
    }
    if (base) {
      Swig_name_inherit(base,derived);
      Delete(base);
    }
  }
  return bases;
}

/* If the class name is qualified.  We need to create or lookup namespace entries */

static Symtab *get_global_scope() {
  Symtab *symtab = Swig_symbol_current();
  Node   *pn = parentNode(symtab);
  while (pn) {
    symtab = pn;
    pn = parentNode(symtab);
    if (!pn) break;
  }
  Swig_symbol_setscope(symtab);
  return symtab;
}
 
/* Remove the block braces, { and }, if the 'noblock' attribute is set.
 * Node *kw can be either a Hash or Parmlist. */
static String *remove_block(Node *kw, const String *inputcode) {
  String *modified_code = 0;
  while (kw) {
   String *name = Getattr(kw,"name");
   if (name && (Cmp(name,"noblock") == 0)) {
     char *cstr = Char(inputcode);
     size_t len = Len(inputcode);
     if (len && cstr[0] == '{') {
       --len; ++cstr; 
       if (len && cstr[len - 1] == '}') { --len; }
       /* we now remove the extra spaces */
       while (len && isspace((int)cstr[0])) { --len; ++cstr; }
       while (len && isspace((int)cstr[len - 1])) { --len; }
       modified_code = NewStringWithSize(cstr, len);
       break;
     }
   }
   kw = nextSibling(kw);
  }
  return modified_code;
}


static Node *nscope = 0;
static Node *nscope_inner = 0;
static String *resolve_node_scope(String *cname) {
  Symtab *gscope = 0;
  nscope = 0;
  nscope_inner = 0;  
  if (Swig_scopename_check(cname)) {
    Node   *ns;
    String *prefix = Swig_scopename_prefix(cname);
    String *base = Swig_scopename_last(cname);
    if (prefix && (Strncmp(prefix,"::",2) == 0)) {
      /* Use the global scope */
      String *nprefix = NewString(Char(prefix)+2);
      Delete(prefix);
      prefix= nprefix;
      gscope = get_global_scope();
    }    
    if (!prefix || (Len(prefix) == 0)) {
      /* Use the global scope, but we need to add a 'global' namespace.  */
      if (!gscope) gscope = get_global_scope();
      /* note that this namespace is not the "unnamed" one,
	 and we don't use Setattr(nscope,"name", ""),
	 because the unnamed namespace is private */
      nscope = new_node("namespace");
      Setattr(nscope,"symtab", gscope);;
      nscope_inner = nscope;
      return base;
    }
    /* Try to locate the scope */
    ns = Swig_symbol_clookup(prefix,0);
    if (!ns) {
      Swig_error(cparse_file,cparse_line,"Undefined scope '%s'\n", prefix);
    } else {
      Symtab *nstab = Getattr(ns,"symtab");
      if (!nstab) {
	Swig_error(cparse_file,cparse_line,
		   "'%s' is not defined as a valid scope.\n", prefix);
	ns = 0;
      } else {
	/* Check if the node scope is the current scope */
	String *tname = Swig_symbol_qualifiedscopename(0);
	String *nname = Swig_symbol_qualifiedscopename(nstab);
	if (tname && (Strcmp(tname,nname) == 0)) {
	  ns = 0;
	  cname = base;
	}
	Delete(tname);
	Delete(nname);
      }
      if (ns) {
	/* we will try to create a new node using the namespaces we
	   can find in the scope name */
	List *scopes;
	String *sname;
	Iterator si;
	String *name = NewString(prefix);
	scopes = NewList();
	while (name) {
	  String *base = Swig_scopename_last(name);
	  String *tprefix = Swig_scopename_prefix(name);
	  Insert(scopes,0,base);
	  Delete(base);
	  Delete(name);
	  name = tprefix;
	}
	for (si = First(scopes); si.item; si = Next(si)) {
	  Node *ns1,*ns2;
	  sname = si.item;
	  ns1 = Swig_symbol_clookup(sname,0);
	  assert(ns1);
	  if (Strcmp(nodeType(ns1),"namespace") == 0) {
	    if (Getattr(ns1,"alias")) {
	      ns1 = Getattr(ns1,"namespace");
	    }
	  } else {
	    /* now this last part is a class */
	    si = Next(si);
	    ns1 = Swig_symbol_clookup(sname,0);
	    /*  or a nested class tree, which is unrolled here */
	    for (; si.item; si = Next(si)) {
	      if (si.item) {
		Printf(sname,"::%s",si.item);
	      }
	    }
	    /* we get the 'inner' class */
	    nscope_inner = Swig_symbol_clookup(sname,0);
	    /* set the scope to the inner class */
	    Swig_symbol_setscope(Getattr(nscope_inner,"symtab"));
	    /* save the last namespace prefix */
	    Delete(Namespaceprefix);
	    Namespaceprefix = Swig_symbol_qualifiedscopename(0);
	    /* and return the node name, including the inner class prefix */
	    break;
	  }
	  /* here we just populate the namespace tree as usual */
	  ns2 = new_node("namespace");
	  Setattr(ns2,"name",sname);
	  Setattr(ns2,"symtab", Getattr(ns1,"symtab"));
	  add_symbols(ns2);
	  Swig_symbol_setscope(Getattr(ns1,"symtab"));
	  Delete(Namespaceprefix);
	  Namespaceprefix = Swig_symbol_qualifiedscopename(0);
	  if (nscope_inner) {
	    if (Getattr(nscope_inner,"symtab") != Getattr(ns2,"symtab")) {
	      appendChild(nscope_inner,ns2);
	      Delete(ns2);
	    }
	  }
	  nscope_inner = ns2;
	  if (!nscope) nscope = ns2;
	}
	cname = base;
	Delete(scopes);
      }
    }
    Delete(prefix);
  }
  return cname;
}
 




/* Structures for handling code fragments built for nested classes */

typedef struct Nested {
  String   *code;        /* Associated code fragment */
  int      line;         /* line number where it starts */
  char     *name;        /* Name associated with this nested class */
  char     *kind;        /* Kind of class */
  int      unnamed;      /* unnamed class */
  SwigType *type;        /* Datatype associated with the name */
  struct Nested   *next;        /* Next code fragment in list */
} Nested;

/* Some internal variables for saving nested class information */

static Nested      *nested_list = 0;

/* Add a function to the nested list */

static void add_nested(Nested *n) {
  Nested *n1;
  if (!nested_list) nested_list = n;
  else {
    n1 = nested_list;
    while (n1->next) n1 = n1->next;
    n1->next = n;
  }
}

/* Dump all of the nested class declarations to the inline processor
 * However.  We need to do a few name replacements and other munging
 * first.  This function must be called before closing a class! */

static Node *dump_nested(const char *parent) {
  Nested *n,*n1;
  Node *ret = 0;
  n = nested_list;
  if (!parent) {
    nested_list = 0;
    return 0;
  }
  while (n) {
    Node *retx;
    SwigType *nt;
    /* Token replace the name of the parent class */
    Replace(n->code, "$classname", parent, DOH_REPLACE_ANY);

    /* Fix up the name of the datatype (for building typedefs and other stuff) */
    Append(n->type,parent);
    Append(n->type,"_");
    Append(n->type,n->name);

    /* Add the appropriate declaration to the C++ processor */
    retx = new_node("cdecl");
    Setattr(retx,"name",n->name);
    nt = Copy(n->type);
    Setattr(retx,"type",nt);
    Delete(nt);
    Setattr(retx,"nested",parent);
    if (n->unnamed) {
      Setattr(retx,"unnamed","1");
    }
    
    add_symbols(retx);
    if (ret) {
      set_nextSibling(retx,ret);
      Delete(ret);
    }
    ret = retx;

    /* Insert a forward class declaration */
    /* Disabled: [ 597599 ] union in class: incorrect scope 
       retx = new_node("classforward");
       Setattr(retx,"kind",n->kind);
       Setattr(retx,"name",Copy(n->type));
       Setattr(retx,"sym:name", make_name(n->type,0));
       set_nextSibling(retx,ret);
       ret = retx; 
    */

    /* Make all SWIG created typedef structs/unions/classes unnamed else 
       redefinition errors occur - nasty hack alert.*/

    {
      const char* types_array[3] = {"struct", "union", "class"};
      int i;
      for (i=0; i<3; i++) {
	char* code_ptr = Char(n->code);
	while (code_ptr) {
	  /* Replace struct name (as in 'struct name {...}' ) with whitespace
	     name will be between struct and opening brace */
	
	  code_ptr = strstr(code_ptr, types_array[i]);
	  if (code_ptr) {
	    char *open_bracket_pos;
	    code_ptr += strlen(types_array[i]);
	    open_bracket_pos = strchr(code_ptr, '{');
	    if (open_bracket_pos) { 
	      /* Make sure we don't have something like struct A a; */
	      char* semi_colon_pos = strchr(code_ptr, ';');
	      if (!(semi_colon_pos && (semi_colon_pos < open_bracket_pos)))
		while (code_ptr < open_bracket_pos)
		  *code_ptr++ = ' ';
	    }
	  }
	}
      }
    }
    
    {
      /* Remove SWIG directive %constant which may be left in the SWIG created typedefs */
      char* code_ptr = Char(n->code);
      while (code_ptr) {
	code_ptr = strstr(code_ptr, "%constant");
	if (code_ptr) {
	  char* directive_end_pos = strchr(code_ptr, ';');
	  if (directive_end_pos) { 
            while (code_ptr <= directive_end_pos)
              *code_ptr++ = ' ';
	  }
	}
      }
    }
    {
      Node *head = new_node("insert");
      String *code = NewStringf("\n%s\n",n->code);
      Setattr(head,"code", code);
      Delete(code);
      set_nextSibling(head,ret);
      Delete(ret);      
      ret = head;
    }
      
    /* Dump the code to the scanner */
    start_inline(Char(n->code),n->line);

    n1 = n->next;
    Delete(n->code);
    free(n);
    n = n1;
  }
  nested_list = 0;
  return ret;
}

Node *Swig_cparse(File *f) {
  scanner_file(f);
  top = 0;
  yyparse();
  return top;
}

static void single_new_feature(const char *featurename, String *val, Hash *featureattribs, char *declaratorid, SwigType *type, ParmList *declaratorparms, String *qualifier) {
  String *fname;
  String *name;
  String *fixname;
  SwigType *t = Copy(type);

  /* Printf(stdout, "single_new_feature: [%s] [%s] [%s] [%s] [%s] [%s]\n", featurename, val, declaratorid, t, ParmList_str_defaultargs(declaratorparms), qualifier); */

  fname = NewStringf("feature:%s",featurename);
  if (declaratorid) {
    fixname = feature_identifier_fix(declaratorid);
  } else {
    fixname = NewStringEmpty();
  }
  if (Namespaceprefix) {
    name = NewStringf("%s::%s",Namespaceprefix, fixname);
  } else {
    name = fixname;
  }

  if (declaratorparms) Setmeta(val,"parms",declaratorparms);
  if (!Len(t)) t = 0;
  if (t) {
    if (qualifier) SwigType_push(t,qualifier);
    if (SwigType_isfunction(t)) {
      SwigType *decl = SwigType_pop_function(t);
      if (SwigType_ispointer(t)) {
	String *nname = NewStringf("*%s",name);
	Swig_feature_set(Swig_cparse_features(), nname, decl, fname, val, featureattribs);
	Delete(nname);
      } else {
	Swig_feature_set(Swig_cparse_features(), name, decl, fname, val, featureattribs);
      }
      Delete(decl);
    } else if (SwigType_ispointer(t)) {
      String *nname = NewStringf("*%s",name);
      Swig_feature_set(Swig_cparse_features(),nname,0,fname,val, featureattribs);
      Delete(nname);
    }
  } else {
    /* Global feature, that is, feature not associated with any particular symbol */
    Swig_feature_set(Swig_cparse_features(),name,0,fname,val, featureattribs);
  }
  Delete(fname);
  Delete(name);
}

/* Add a new feature to the Hash. Additional features are added if the feature has a parameter list (declaratorparms)
 * and one or more of the parameters have a default argument. An extra feature is added for each defaulted parameter,
 * simulating the equivalent overloaded method. */
static void new_feature(const char *featurename, String *val, Hash *featureattribs, char *declaratorid, SwigType *type, ParmList *declaratorparms, String *qualifier) {

  ParmList *declparms = declaratorparms;

  /* remove the { and } braces if the noblock attribute is set */
  String *newval = remove_block(featureattribs, val);
  val = newval ? newval : val;

  /* Add the feature */
  single_new_feature(featurename, val, featureattribs, declaratorid, type, declaratorparms, qualifier);

  /* Add extra features if there are default parameters in the parameter list */
  if (type) {
    while (declparms) {
      if (ParmList_has_defaultargs(declparms)) {

        /* Create a parameter list for the new feature by copying all
           but the last (defaulted) parameter */
        ParmList* newparms = CopyParmListMax(declparms, ParmList_len(declparms)-1);

        /* Create new declaration - with the last parameter removed */
        SwigType *newtype = Copy(type);
        Delete(SwigType_pop_function(newtype)); /* remove the old parameter list from newtype */
        SwigType_add_function(newtype,newparms);

        single_new_feature(featurename, Copy(val), featureattribs, declaratorid, newtype, newparms, qualifier);
        declparms = newparms;
      } else {
        declparms = 0;
      }
    }
  }
}

/* check if a function declaration is a plain C object */
static int is_cfunction(Node *n) {
  if (!cparse_cplusplus || cparse_externc) return 1;
  if (Cmp(Getattr(n,"storage"),"externc") == 0) {
    return 1;
  }
  return 0;
}

/* If the Node is a function with parameters, check to see if any of the parameters
 * have default arguments. If so create a new function for each defaulted argument. 
 * The additional functions form a linked list of nodes with the head being the original Node n. */
static void default_arguments(Node *n) {
  Node *function = n;

  if (function) {
    ParmList *varargs = Getattr(function,"feature:varargs");
    if (varargs) {
      /* Handles the %varargs directive by looking for "feature:varargs" and 
       * substituting ... with an alternative set of arguments.  */
      Parm     *p = Getattr(function,"parms");
      Parm     *pp = 0;
      while (p) {
	SwigType *t = Getattr(p,"type");
	if (Strcmp(t,"v(...)") == 0) {
	  if (pp) {
	    ParmList *cv = Copy(varargs);
	    set_nextSibling(pp,cv);
	    Delete(cv);
	  } else {
	    ParmList *cv =  Copy(varargs);
	    Setattr(function,"parms", cv);
	    Delete(cv);
	  }
	  break;
	}
	pp = p;
	p = nextSibling(p);
      }
    }

    /* Do not add in functions if kwargs is being used or if user wants old default argument wrapping
       (one wrapped method per function irrespective of number of default arguments) */
    if (compact_default_args 
	|| is_cfunction(function) 
	|| GetFlag(function,"feature:compactdefaultargs") 
	|| GetFlag(function,"feature:kwargs")) {
      ParmList *p = Getattr(function,"parms");
      if (p) 
        Setattr(p,"compactdefargs", "1"); /* mark parameters for special handling */
      function = 0; /* don't add in extra methods */
    }
  }

  while (function) {
    ParmList *parms = Getattr(function,"parms");
    if (ParmList_has_defaultargs(parms)) {

      /* Create a parameter list for the new function by copying all
         but the last (defaulted) parameter */
      ParmList* newparms = CopyParmListMax(parms,ParmList_len(parms)-1);

      /* Create new function and add to symbol table */
      {
	SwigType *ntype = Copy(nodeType(function));
	char *cntype = Char(ntype);
        Node *new_function = new_node(ntype);
        SwigType *decl = Copy(Getattr(function,"decl"));
        int constqualifier = SwigType_isconst(decl);
	String *ccode = Copy(Getattr(function,"code"));
	String *cstorage = Copy(Getattr(function,"storage"));
	String *cvalue = Copy(Getattr(function,"value"));
	SwigType *ctype = Copy(Getattr(function,"type"));
	String *cthrow = Copy(Getattr(function,"throw"));

        Delete(SwigType_pop_function(decl)); /* remove the old parameter list from decl */
        SwigType_add_function(decl,newparms);
        if (constqualifier)
          SwigType_add_qualifier(decl,"const");

        Setattr(new_function,"name", Getattr(function,"name"));
        Setattr(new_function,"code", ccode);
        Setattr(new_function,"decl", decl);
        Setattr(new_function,"parms", newparms);
        Setattr(new_function,"storage", cstorage);
        Setattr(new_function,"value", cvalue);
        Setattr(new_function,"type", ctype);
        Setattr(new_function,"throw", cthrow);

	Delete(ccode);
	Delete(cstorage);
	Delete(cvalue);
	Delete(ctype);
	Delete(cthrow);
	Delete(decl);

        {
          Node *throws = Getattr(function,"throws");
	  ParmList *pl = CopyParmList(throws);
          if (throws) Setattr(new_function,"throws",pl);
	  Delete(pl);
        }

        /* copy specific attributes for global (or in a namespace) template functions - these are not templated class methods */
        if (strcmp(cntype,"template") == 0) {
          Node *templatetype = Getattr(function,"templatetype");
          Node *symtypename = Getattr(function,"sym:typename");
          Parm *templateparms = Getattr(function,"templateparms");
          if (templatetype) {
	    Node *tmp = Copy(templatetype);
	    Setattr(new_function,"templatetype",tmp);
	    Delete(tmp);
	  }
          if (symtypename) {
	    Node *tmp = Copy(symtypename);
	    Setattr(new_function,"sym:typename",tmp);
	    Delete(tmp);
	  }
          if (templateparms) {
	    Parm *tmp = CopyParmList(templateparms);
	    Setattr(new_function,"templateparms",tmp);
	    Delete(tmp);
	  }
        } else if (strcmp(cntype,"constructor") == 0) {
          /* only copied for constructors as this is not a user defined feature - it is hard coded in the parser */
          if (GetFlag(function,"feature:new")) SetFlag(new_function,"feature:new");
        }

        add_symbols(new_function);
        /* mark added functions as ones with overloaded parameters and point to the parsed method */
        Setattr(new_function,"defaultargs", n);

        /* Point to the new function, extending the linked list */
        set_nextSibling(function, new_function);
	Delete(new_function);
        function = new_function;
	
	Delete(ntype);
      }
    } else {
      function = 0;
    }
  }
}

/* -----------------------------------------------------------------------------
 * tag_nodes()
 *
 * Used by the parser to mark subtypes with extra information.
 * ----------------------------------------------------------------------------- */

static void tag_nodes(Node *n, const String_or_char *attrname, DOH *value) {
  while (n) {
    Setattr(n, attrname, value);
    tag_nodes(firstChild(n), attrname, value);
    n = nextSibling(n);
  }
}



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 1373 "parser.y"
{
  char  *id;
  List  *bases;
  struct Define {
    String *val;
    String *rawval;
    int     type;
    String *qualifier;
    String *bitfield;
    Parm   *throws;
    String *throwf;
  } dtype;
  struct {
    char *type;
    String *filename;
    int   line;
  } loc;
  struct {
    char      *id;
    SwigType  *type;
    String    *defarg;
    ParmList  *parms;
    short      have_parms;
    ParmList  *throws;
    String    *throwf;
  } decl;
  Parm         *tparms;
  struct {
    String     *op;
    Hash       *kwargs;
  } tmap;
  struct {
    String     *type;
    String     *us;
  } ptype;
  SwigType     *type;
  String       *str;
  Parm         *p;
  ParmList     *pl;
  int           ivalue;
  Node         *node;
}
/* Line 187 of yacc.c.  */
#line 1752 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 1765 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  55
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3902

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  127
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  148
/* YYNRULES -- Number of rules.  */
#define YYNRULES  467
/* YYNRULES -- Number of states.  */
#define YYNSTATES  904

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   381

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     9,    12,    16,    19,    25,    29,
      32,    34,    36,    38,    40,    42,    44,    46,    49,    51,
      53,    55,    57,    59,    61,    63,    65,    67,    69,    71,
      73,    75,    77,    79,    81,    83,    85,    87,    89,    91,
      92,   100,   106,   110,   116,   122,   126,   129,   132,   138,
     141,   147,   150,   155,   157,   159,   167,   175,   181,   182,
     190,   192,   194,   197,   200,   202,   208,   214,   220,   224,
     229,   233,   241,   250,   256,   260,   262,   264,   268,   270,
     275,   283,   290,   292,   294,   302,   312,   321,   332,   338,
     346,   353,   362,   364,   366,   372,   377,   383,   391,   393,
     397,   404,   411,   420,   422,   425,   429,   431,   434,   438,
     445,   451,   461,   464,   466,   468,   470,   471,   478,   484,
     486,   491,   493,   495,   498,   504,   511,   516,   524,   533,
     540,   542,   544,   546,   548,   550,   552,   553,   563,   564,
     573,   575,   578,   583,   584,   591,   595,   597,   599,   601,
     603,   605,   607,   609,   612,   614,   616,   618,   622,   624,
     628,   633,   634,   641,   642,   648,   654,   657,   658,   665,
     667,   669,   670,   674,   676,   678,   680,   682,   684,   686,
     688,   690,   694,   696,   698,   700,   702,   704,   706,   708,
     710,   712,   719,   726,   734,   743,   752,   760,   766,   769,
     772,   775,   776,   784,   785,   792,   793,   802,   804,   806,
     808,   810,   812,   814,   816,   818,   820,   822,   824,   826,
     828,   831,   834,   837,   842,   845,   851,   853,   856,   858,
     860,   862,   864,   866,   868,   870,   873,   875,   879,   881,
     884,   892,   896,   898,   901,   903,   907,   909,   911,   913,
     916,   922,   925,   928,   930,   933,   936,   938,   940,   942,
     944,   947,   951,   953,   956,   960,   965,   971,   976,   978,
     981,   985,   990,   996,  1000,  1005,  1010,  1012,  1015,  1020,
    1025,  1031,  1035,  1040,  1045,  1047,  1050,  1053,  1057,  1059,
    1062,  1064,  1067,  1071,  1076,  1080,  1085,  1088,  1092,  1096,
    1101,  1105,  1109,  1112,  1115,  1117,  1119,  1122,  1124,  1126,
    1128,  1130,  1133,  1135,  1138,  1142,  1144,  1146,  1148,  1151,
    1154,  1156,  1158,  1161,  1163,  1165,  1168,  1170,  1172,  1174,
    1176,  1178,  1180,  1182,  1184,  1186,  1188,  1190,  1192,  1194,
    1196,  1197,  1200,  1202,  1204,  1208,  1210,  1212,  1216,  1218,
    1220,  1222,  1224,  1226,  1228,  1234,  1236,  1238,  1242,  1247,
    1253,  1259,  1266,  1269,  1272,  1274,  1276,  1278,  1280,  1282,
    1284,  1286,  1290,  1294,  1298,  1302,  1306,  1310,  1314,  1318,
    1322,  1326,  1330,  1334,  1338,  1342,  1346,  1350,  1356,  1359,
    1362,  1365,  1368,  1371,  1373,  1374,  1378,  1380,  1382,  1386,
    1389,  1394,  1396,  1398,  1400,  1402,  1404,  1406,  1408,  1410,
    1412,  1414,  1416,  1421,  1427,  1429,  1433,  1437,  1442,  1447,
    1451,  1454,  1456,  1458,  1462,  1465,  1469,  1471,  1473,  1475,
    1477,  1479,  1482,  1487,  1489,  1493,  1495,  1499,  1503,  1506,
    1509,  1512,  1515,  1518,  1523,  1525,  1529,  1531,  1535,  1539,
    1542,  1545,  1548,  1551,  1553,  1555,  1557,  1559,  1563,  1565,
    1569,  1575,  1577,  1581,  1585,  1591,  1593,  1595
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     128,     0,    -1,   129,    -1,   107,   215,    40,    -1,   107,
       1,    -1,   108,   215,    40,    -1,   108,     1,    -1,   109,
      37,   212,    38,    40,    -1,   109,     1,    40,    -1,   129,
     130,    -1,   274,    -1,   131,    -1,   168,    -1,   176,    -1,
      40,    -1,     1,    -1,   175,    -1,     1,   106,    -1,   132,
      -1,   134,    -1,   135,    -1,   136,    -1,   137,    -1,   138,
      -1,   141,    -1,   142,    -1,   145,    -1,   146,    -1,   147,
      -1,   148,    -1,   149,    -1,   150,    -1,   153,    -1,   155,
      -1,   158,    -1,   160,    -1,   165,    -1,   166,    -1,   167,
      -1,    -1,    61,   271,   264,    43,   133,   193,    44,    -1,
      85,   164,    43,   162,    44,    -1,    86,   162,    40,    -1,
      57,     3,    51,   237,    40,    -1,    57,   231,   223,   220,
      40,    -1,    57,     1,    40,    -1,    84,     4,    -1,    84,
     269,    -1,    83,    37,     3,    38,    43,    -1,    83,    43,
      -1,    83,    37,     3,    38,    40,    -1,    83,    40,    -1,
     269,    43,   215,    44,    -1,   269,    -1,   139,    -1,    88,
      37,   140,    39,   272,    38,     4,    -1,    88,    37,   140,
      39,   272,    38,    43,    -1,    88,    37,   140,    38,    40,
      -1,    -1,   144,   271,   269,    54,   143,   129,    55,    -1,
       7,    -1,     8,    -1,    81,     4,    -1,    81,    43,    -1,
       4,    -1,     9,    37,   262,    38,   269,    -1,     9,    37,
     262,    38,     4,    -1,     9,    37,   262,    38,    43,    -1,
      53,   271,   262,    -1,    58,    37,   262,    38,    -1,    58,
      37,    38,    -1,    80,    37,     3,    38,   211,     3,    40,
      -1,    80,    37,     3,    38,   211,   231,   223,    40,    -1,
      62,   152,     3,    51,   151,    -1,    62,   152,     3,    -1,
     269,    -1,     4,    -1,    37,     3,    38,    -1,   274,    -1,
     154,   223,   262,    40,    -1,   154,    37,   272,    38,   223,
     256,    40,    -1,   154,    37,   272,    38,   269,    40,    -1,
      59,    -1,    60,    -1,    63,    37,   262,    38,   223,   256,
     156,    -1,    63,    37,   262,    39,   273,    38,   223,   256,
      40,    -1,    63,    37,   262,   157,    38,   223,   256,   156,
      -1,    63,    37,   262,    39,   273,   157,    38,   223,   256,
      40,    -1,    63,    37,   262,    38,   156,    -1,    63,    37,
     262,    39,   273,    38,    40,    -1,    63,    37,   262,   157,
      38,   156,    -1,    63,    37,   262,    39,   273,   157,    38,
      40,    -1,   270,    -1,    40,    -1,   100,    37,   212,    38,
      40,    -1,    39,   262,    51,   273,    -1,    39,   262,    51,
     273,   157,    -1,    64,    37,   159,    38,   223,   256,    40,
      -1,   212,    -1,    11,    39,   215,    -1,    82,    37,   161,
      38,   162,   270,    -1,    82,    37,   161,    38,   162,    40,
      -1,    82,    37,   161,    38,   162,    51,   164,    40,    -1,
     272,    -1,   164,   163,    -1,    39,   164,   163,    -1,   274,
      -1,   231,   222,    -1,    37,   212,    38,    -1,    37,   212,
      38,    37,   212,    38,    -1,    99,    37,   212,    38,   156,
      -1,    87,    37,   263,    38,   267,    90,   216,    91,    40,
      -1,    89,   269,    -1,   170,    -1,   174,    -1,   173,    -1,
      -1,    41,   269,    43,   169,   129,    44,    -1,   211,   231,
     223,   172,   171,    -1,    40,    -1,    39,   223,   172,   171,
      -1,    43,    -1,   220,    -1,   229,   220,    -1,    75,    37,
     212,    38,   220,    -1,   229,    75,    37,   212,    38,   220,
      -1,   211,    65,     3,    40,    -1,   211,    65,   239,    43,
     240,    44,    40,    -1,   211,    65,   239,    43,   240,    44,
     223,   171,    -1,   211,   231,    37,   212,    38,   257,    -1,
     177,    -1,   181,    -1,   182,    -1,   189,    -1,   190,    -1,
     200,    -1,    -1,   211,   254,   264,   247,    43,   178,   193,
      44,   180,    -1,    -1,   211,   254,    43,   179,   193,    44,
     223,   171,    -1,    40,    -1,   223,   171,    -1,   211,   254,
     264,    40,    -1,    -1,   104,    90,   185,    91,   183,   184,
      -1,   104,   254,   264,    -1,   170,    -1,   177,    -1,   197,
      -1,   182,    -1,   181,    -1,   199,    -1,   186,    -1,   187,
     188,    -1,   274,    -1,   253,    -1,   215,    -1,    39,   187,
     188,    -1,   274,    -1,    78,   264,    40,    -1,    78,    79,
     264,    40,    -1,    -1,    79,   264,    43,   191,   129,    44,
      -1,    -1,    79,    43,   192,   129,    44,    -1,    79,     3,
      51,   264,    40,    -1,   196,   193,    -1,    -1,    61,    43,
     194,   193,    44,   193,    -1,   142,    -1,   274,    -1,    -1,
       1,   195,   193,    -1,   168,    -1,   197,    -1,   198,    -1,
     201,    -1,   207,    -1,   199,    -1,   181,    -1,   202,    -1,
     211,   264,    40,    -1,   189,    -1,   182,    -1,   200,    -1,
     166,    -1,   167,    -1,   210,    -1,   141,    -1,   165,    -1,
      40,    -1,   211,   231,    37,   212,    38,   257,    -1,   124,
     266,    37,   212,    38,   208,    -1,    73,   124,   266,    37,
     212,    38,   209,    -1,   211,   106,   231,   228,    37,   212,
      38,   209,    -1,   211,   106,   231,   115,    37,   212,    38,
     209,    -1,   211,   106,   231,    37,   212,    38,   209,    -1,
      76,    37,   212,    38,    43,    -1,    69,    71,    -1,    68,
      71,    -1,    70,    71,    -1,    -1,   211,   254,     3,    43,
     203,   206,    40,    -1,    -1,   211,   254,    43,   204,   206,
      40,    -1,    -1,   211,   254,   264,    71,   250,    43,   205,
      40,    -1,   223,    -1,   274,    -1,   150,    -1,   136,    -1,
     148,    -1,   153,    -1,   155,    -1,   158,    -1,   146,    -1,
     160,    -1,   134,    -1,   135,    -1,   137,    -1,   256,    40,
      -1,   256,    43,    -1,   256,    40,    -1,   256,    51,   237,
      40,    -1,   256,    43,    -1,   211,   231,    71,   243,    40,
      -1,    41,    -1,    41,   269,    -1,    72,    -1,    18,    -1,
      73,    -1,    74,    -1,    77,    -1,   274,    -1,   213,    -1,
     215,   214,    -1,   274,    -1,    39,   215,   214,    -1,   274,
      -1,   232,   221,    -1,   104,    90,   254,    91,   254,   264,
     220,    -1,    45,    45,    45,    -1,   217,    -1,   219,   218,
      -1,   274,    -1,    39,   219,   218,    -1,   274,    -1,   215,
      -1,   244,    -1,    51,   237,    -1,    51,   237,    54,   243,
      55,    -1,    51,    43,    -1,    71,   243,    -1,   274,    -1,
     223,   220,    -1,   226,   220,    -1,   220,    -1,   223,    -1,
     226,    -1,   274,    -1,   228,   224,    -1,   228,   115,   224,
      -1,   225,    -1,   115,   224,    -1,   264,   102,   224,    -1,
     228,   264,   102,   224,    -1,   228,   264,   102,   115,   224,
      -1,   264,   102,   115,   224,    -1,   264,    -1,   124,   264,
      -1,    37,   264,    38,    -1,    37,   228,   224,    38,    -1,
      37,   264,   102,   224,    38,    -1,   224,    54,    55,    -1,
     224,    54,   243,    55,    -1,   224,    37,   212,    38,    -1,
     264,    -1,   124,   264,    -1,    37,   228,   225,    38,    -1,
      37,   115,   225,    38,    -1,    37,   264,   102,   225,    38,
      -1,   225,    54,    55,    -1,   225,    54,   243,    55,    -1,
     225,    37,   212,    38,    -1,   228,    -1,   228,   227,    -1,
     228,   115,    -1,   228,   115,   227,    -1,   227,    -1,   115,
     227,    -1,   115,    -1,   264,   102,    -1,   228,   264,   102,
      -1,   228,   264,   102,   227,    -1,   227,    54,    55,    -1,
     227,    54,   243,    55,    -1,    54,    55,    -1,    54,   243,
      55,    -1,    37,   226,    38,    -1,   227,    37,   212,    38,
      -1,    37,   212,    38,    -1,   122,   229,   228,    -1,   122,
     228,    -1,   122,   229,    -1,   122,    -1,   230,    -1,   230,
     229,    -1,    46,    -1,    47,    -1,    48,    -1,   232,    -1,
     229,   233,    -1,   233,    -1,   233,   229,    -1,   229,   233,
     229,    -1,   234,    -1,    29,    -1,    27,    -1,    31,   261,
      -1,    65,   264,    -1,    32,    -1,   264,    -1,   254,   264,
      -1,   235,    -1,   236,    -1,   236,   235,    -1,    19,    -1,
      21,    -1,    22,    -1,    25,    -1,    26,    -1,    23,    -1,
      24,    -1,    28,    -1,    20,    -1,    30,    -1,    33,    -1,
      34,    -1,    35,    -1,    36,    -1,    -1,   238,   243,    -1,
       3,    -1,   274,    -1,   240,    39,   241,    -1,   241,    -1,
       3,    -1,     3,    51,   242,    -1,   274,    -1,   243,    -1,
     244,    -1,   231,    -1,   245,    -1,   269,    -1,    52,    37,
     231,   221,    38,    -1,   246,    -1,    10,    -1,    37,   243,
      38,    -1,    37,   243,    38,   243,    -1,    37,   243,   228,
      38,   243,    -1,    37,   243,   115,    38,   243,    -1,    37,
     243,   228,   115,    38,   243,    -1,   115,   243,    -1,   122,
     243,    -1,    11,    -1,    12,    -1,    13,    -1,    14,    -1,
      15,    -1,    16,    -1,    17,    -1,   243,   119,   243,    -1,
     243,   118,   243,    -1,   243,   122,   243,    -1,   243,   121,
     243,    -1,   243,   120,   243,    -1,   243,   115,   243,    -1,
     243,   113,   243,    -1,   243,   114,   243,    -1,   243,   117,
     243,    -1,   243,   116,   243,    -1,   243,   112,   243,    -1,
     243,   111,   243,    -1,   243,    96,   243,    -1,   243,    97,
     243,    -1,   243,    95,   243,    -1,   243,    94,   243,    -1,
     243,    98,   243,    71,   243,    -1,   118,   243,    -1,   119,
     243,    -1,   124,   243,    -1,   123,   243,    -1,   231,    37,
      -1,   248,    -1,    -1,    71,   249,   250,    -1,   274,    -1,
     251,    -1,   250,    39,   251,    -1,   255,   264,    -1,   255,
     252,   255,   264,    -1,    69,    -1,    68,    -1,    70,    -1,
      66,    -1,    67,    -1,   253,    -1,    49,    -1,    50,    -1,
      73,    -1,   274,    -1,   229,    -1,    75,    37,   212,    38,
      -1,   229,    75,    37,   212,    38,    -1,   274,    -1,   256,
     258,    40,    -1,   256,   258,    43,    -1,    37,   212,    38,
      40,    -1,    37,   212,    38,    43,    -1,    51,   237,    40,
      -1,    71,   259,    -1,   274,    -1,   260,    -1,   259,    39,
     260,    -1,   264,    37,    -1,    90,   216,    91,    -1,   274,
      -1,     3,    -1,   269,    -1,   262,    -1,   274,    -1,   266,
     265,    -1,   101,   126,   266,   265,    -1,   266,    -1,   101,
     126,   266,    -1,   105,    -1,   101,   126,   105,    -1,   126,
     266,   265,    -1,   126,   266,    -1,   126,   105,    -1,   103,
     266,    -1,     3,   261,    -1,     3,   268,    -1,   101,   126,
       3,   268,    -1,     3,    -1,   101,   126,     3,    -1,   105,
      -1,   101,   126,   105,    -1,   126,     3,   268,    -1,   126,
       3,    -1,   126,   105,    -1,   103,     3,    -1,   269,     6,
      -1,     6,    -1,   269,    -1,    43,    -1,     4,    -1,    37,
     272,    38,    -1,   274,    -1,   262,    51,   273,    -1,   262,
      51,   273,    39,   272,    -1,   262,    -1,   262,    39,   272,
      -1,   262,    51,   139,    -1,   262,    51,   139,    39,   272,
      -1,   269,    -1,   245,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,  1526,  1526,  1539,  1543,  1546,  1549,  1552,  1555,  1560,
    1565,  1570,  1571,  1572,  1573,  1574,  1580,  1596,  1606,  1607,
    1608,  1609,  1610,  1611,  1612,  1613,  1614,  1615,  1616,  1617,
    1618,  1619,  1620,  1621,  1622,  1623,  1624,  1625,  1626,  1633,
    1633,  1705,  1715,  1726,  1747,  1769,  1780,  1789,  1808,  1814,
    1820,  1825,  1832,  1839,  1843,  1856,  1865,  1880,  1893,  1893,
    1943,  1944,  1951,  1971,  2002,  2006,  2016,  2021,  2039,  2079,
    2085,  2098,  2104,  2130,  2136,  2143,  2144,  2147,  2148,  2156,
    2202,  2248,  2259,  2262,  2289,  2294,  2299,  2304,  2311,  2316,
    2321,  2326,  2333,  2334,  2335,  2338,  2343,  2353,  2389,  2390,
    2420,  2437,  2445,  2458,  2483,  2489,  2493,  2496,  2507,  2512,
    2525,  2537,  2810,  2820,  2827,  2828,  2832,  2832,  2863,  2924,
    2928,  2950,  2956,  2962,  2968,  2974,  2987,  3002,  3012,  3090,
    3141,  3142,  3143,  3144,  3145,  3146,  3152,  3152,  3384,  3384,
    3506,  3507,  3519,  3539,  3539,  3774,  3780,  3783,  3786,  3789,
    3792,  3795,  3800,  3830,  3834,  3837,  3840,  3845,  3849,  3854,
    3864,  3895,  3895,  3924,  3924,  3946,  3973,  3988,  3988,  3998,
    3999,  4000,  4000,  4016,  4017,  4034,  4035,  4036,  4037,  4038,
    4039,  4040,  4041,  4042,  4043,  4044,  4045,  4046,  4047,  4048,
    4049,  4058,  4083,  4107,  4148,  4163,  4181,  4200,  4207,  4214,
    4222,  4245,  4245,  4280,  4280,  4311,  4311,  4329,  4330,  4336,
    4339,  4343,  4346,  4347,  4348,  4349,  4350,  4351,  4352,  4353,
    4356,  4361,  4368,  4376,  4384,  4395,  4401,  4402,  4410,  4411,
    4412,  4413,  4414,  4415,  4422,  4433,  4437,  4440,  4444,  4448,
    4458,  4466,  4474,  4487,  4491,  4494,  4498,  4502,  4530,  4538,
    4549,  4563,  4572,  4580,  4590,  4594,  4598,  4605,  4622,  4639,
    4647,  4655,  4664,  4668,  4677,  4688,  4700,  4710,  4723,  4730,
    4738,  4754,  4762,  4773,  4784,  4795,  4814,  4822,  4839,  4847,
    4854,  4865,  4876,  4887,  4906,  4912,  4918,  4925,  4934,  4937,
    4946,  4953,  4960,  4970,  4981,  4992,  5003,  5010,  5017,  5020,
    5037,  5047,  5054,  5060,  5065,  5071,  5075,  5081,  5082,  5083,
    5089,  5095,  5099,  5100,  5104,  5111,  5114,  5115,  5116,  5117,
    5118,  5120,  5123,  5128,  5153,  5156,  5210,  5214,  5218,  5222,
    5226,  5230,  5234,  5238,  5242,  5246,  5250,  5254,  5258,  5262,
    5268,  5268,  5294,  5295,  5298,  5311,  5319,  5327,  5344,  5347,
    5362,  5363,  5382,  5383,  5387,  5392,  5393,  5407,  5414,  5420,
    5427,  5434,  5442,  5446,  5452,  5453,  5454,  5455,  5456,  5457,
    5458,  5461,  5465,  5469,  5473,  5477,  5481,  5485,  5489,  5493,
    5497,  5501,  5505,  5509,  5513,  5527,  5534,  5538,  5544,  5548,
    5552,  5556,  5560,  5576,  5581,  5581,  5582,  5585,  5602,  5611,
    5624,  5637,  5638,  5639,  5643,  5647,  5653,  5656,  5660,  5666,
    5667,  5670,  5675,  5680,  5685,  5692,  5699,  5706,  5714,  5722,
    5730,  5731,  5734,  5735,  5738,  5744,  5750,  5753,  5754,  5757,
    5758,  5761,  5766,  5770,  5773,  5776,  5779,  5784,  5788,  5791,
    5798,  5804,  5813,  5818,  5822,  5825,  5828,  5831,  5836,  5840,
    5843,  5846,  5852,  5857,  5860,  5863,  5867,  5872,  5885,  5889,
    5894,  5900,  5904,  5909,  5913,  5920,  5923,  5928
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "HBLOCK", "POUND", "STRING",
  "INCLUDE", "IMPORT", "INSERT", "CHARCONST", "NUM_INT", "NUM_FLOAT",
  "NUM_UNSIGNED", "NUM_LONG", "NUM_ULONG", "NUM_LONGLONG", "NUM_ULONGLONG",
  "TYPEDEF", "TYPE_INT", "TYPE_UNSIGNED", "TYPE_SHORT", "TYPE_LONG",
  "TYPE_FLOAT", "TYPE_DOUBLE", "TYPE_CHAR", "TYPE_WCHAR", "TYPE_VOID",
  "TYPE_SIGNED", "TYPE_BOOL", "TYPE_COMPLEX", "TYPE_TYPEDEF", "TYPE_RAW",
  "TYPE_NON_ISO_INT8", "TYPE_NON_ISO_INT16", "TYPE_NON_ISO_INT32",
  "TYPE_NON_ISO_INT64", "LPAREN", "RPAREN", "COMMA", "SEMI", "EXTERN",
  "INIT", "LBRACE", "RBRACE", "PERIOD", "CONST_QUAL", "VOLATILE",
  "REGISTER", "STRUCT", "UNION", "EQUAL", "SIZEOF", "MODULE", "LBRACKET",
  "RBRACKET", "ILLEGAL", "CONSTANT", "NAME", "RENAME", "NAMEWARN",
  "EXTEND", "PRAGMA", "FEATURE", "VARARGS", "ENUM", "CLASS", "TYPENAME",
  "PRIVATE", "PUBLIC", "PROTECTED", "COLON", "STATIC", "VIRTUAL", "FRIEND",
  "THROW", "CATCH", "EXPLICIT", "USING", "NAMESPACE", "NATIVE", "INLINE",
  "TYPEMAP", "EXCEPT", "ECHO", "APPLY", "CLEAR", "SWIGTEMPLATE",
  "FRAGMENT", "WARN", "LESSTHAN", "GREATERTHAN", "MODULO", "DELETE_KW",
  "LESSTHANOREQUALTO", "GREATERTHANOREQUALTO", "EQUALTO", "NOTEQUALTO",
  "QUESTIONMARK", "TYPES", "PARMS", "NONID", "DSTAR", "DCNOT", "TEMPLATE",
  "OPERATOR", "COPERATOR", "PARSETYPE", "PARSEPARM", "PARSEPARMS", "CAST",
  "LOR", "LAND", "OR", "XOR", "AND", "RSHIFT", "LSHIFT", "MINUS", "PLUS",
  "MODULUS", "SLASH", "STAR", "LNOT", "NOT", "UMINUS", "DCOLON", "$accept",
  "program", "interface", "declaration", "swig_directive",
  "extend_directive", "@1", "apply_directive", "clear_directive",
  "constant_directive", "echo_directive", "except_directive", "stringtype",
  "fname", "fragment_directive", "include_directive", "@2", "includetype",
  "inline_directive", "insert_directive", "module_directive",
  "name_directive", "native_directive", "pragma_directive", "pragma_arg",
  "pragma_lang", "rename_directive", "rename_namewarn",
  "feature_directive", "stringbracesemi", "featattr", "varargs_directive",
  "varargs_parms", "typemap_directive", "typemap_type", "tm_list",
  "tm_tail", "typemap_parm", "types_directive", "template_directive",
  "warn_directive", "c_declaration", "@3", "c_decl", "c_decl_tail",
  "initializer", "c_enum_forward_decl", "c_enum_decl",
  "c_constructor_decl", "cpp_declaration", "cpp_class_decl", "@4", "@5",
  "cpp_opt_declarators", "cpp_forward_class_decl", "cpp_template_decl",
  "@6", "cpp_temp_possible", "template_parms", "templateparameters",
  "templateparameter", "templateparameterstail", "cpp_using_decl",
  "cpp_namespace_decl", "@7", "@8", "cpp_members", "@9", "@10",
  "cpp_member", "cpp_constructor_decl", "cpp_destructor_decl",
  "cpp_conversion_operator", "cpp_catch_decl", "cpp_protection_decl",
  "cpp_nested", "@11", "@12", "@13", "nested_decl", "cpp_swig_directive",
  "cpp_end", "cpp_vend", "anonymous_bitfield", "storage_class", "parms",
  "rawparms", "ptail", "parm", "valparms", "rawvalparms", "valptail",
  "valparm", "def_args", "parameter_declarator",
  "typemap_parameter_declarator", "declarator", "notso_direct_declarator",
  "direct_declarator", "abstract_declarator", "direct_abstract_declarator",
  "pointer", "type_qualifier", "type_qualifier_raw", "type", "rawtype",
  "type_right", "primitive_type", "primitive_type_list", "type_specifier",
  "definetype", "@14", "ename", "enumlist", "edecl", "etype", "expr",
  "valexpr", "exprnum", "exprcompound", "inherit", "raw_inherit", "@15",
  "base_list", "base_specifier", "access_specifier", "templcpptype",
  "cpptype", "opt_virtual", "cpp_const", "ctor_end", "ctor_initializer",
  "mem_initializer_list", "mem_initializer", "template_decl", "idstring",
  "idstringopt", "idcolon", "idcolontail", "idtemplate", "idcolonnt",
  "idcolontailnt", "string", "stringbrace", "options", "kwargs",
  "stringnum", "empty", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   127,   128,   128,   128,   128,   128,   128,   128,   129,
     129,   130,   130,   130,   130,   130,   130,   130,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   133,
     132,   134,   135,   136,   136,   136,   137,   137,   138,   138,
     138,   138,   139,   140,   140,   141,   141,   141,   143,   142,
     144,   144,   145,   145,   146,   146,   146,   146,   147,   148,
     148,   149,   149,   150,   150,   151,   151,   152,   152,   153,
     153,   153,   154,   154,   155,   155,   155,   155,   155,   155,
     155,   155,   156,   156,   156,   157,   157,   158,   159,   159,
     160,   160,   160,   161,   162,   163,   163,   164,   164,   164,
     165,   166,   167,   168,   168,   168,   169,   168,   170,   171,
     171,   171,   172,   172,   172,   172,   173,   174,   174,   175,
     176,   176,   176,   176,   176,   176,   178,   177,   179,   177,
     180,   180,   181,   183,   182,   182,   184,   184,   184,   184,
     184,   184,   185,   186,   186,   187,   187,   188,   188,   189,
     189,   191,   190,   192,   190,   190,   193,   194,   193,   193,
     193,   195,   193,   196,   196,   196,   196,   196,   196,   196,
     196,   196,   196,   196,   196,   196,   196,   196,   196,   196,
     196,   197,   198,   198,   199,   199,   199,   200,   201,   201,
     201,   203,   202,   204,   202,   205,   202,   206,   206,   207,
     207,   207,   207,   207,   207,   207,   207,   207,   207,   207,
     208,   208,   209,   209,   209,   210,   211,   211,   211,   211,
     211,   211,   211,   211,   212,   213,   213,   214,   214,   215,
     215,   215,   216,   217,   217,   218,   218,   219,   219,   220,
     220,   220,   220,   220,   221,   221,   221,   222,   222,   222,
     223,   223,   223,   223,   223,   223,   223,   223,   224,   224,
     224,   224,   224,   224,   224,   224,   225,   225,   225,   225,
     225,   225,   225,   225,   226,   226,   226,   226,   226,   226,
     226,   226,   226,   226,   227,   227,   227,   227,   227,   227,
     227,   228,   228,   228,   228,   229,   229,   230,   230,   230,
     231,   232,   232,   232,   232,   233,   233,   233,   233,   233,
     233,   233,   233,   234,   235,   235,   236,   236,   236,   236,
     236,   236,   236,   236,   236,   236,   236,   236,   236,   236,
     238,   237,   239,   239,   240,   240,   241,   241,   241,   242,
     243,   243,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   245,   245,   245,   245,   245,   245,
     245,   246,   246,   246,   246,   246,   246,   246,   246,   246,
     246,   246,   246,   246,   246,   246,   246,   246,   246,   246,
     246,   246,   246,   247,   249,   248,   248,   250,   250,   251,
     251,   252,   252,   252,   253,   253,   254,   254,   254,   255,
     255,   256,   256,   256,   256,   257,   257,   257,   257,   257,
     258,   258,   259,   259,   260,   261,   261,   262,   262,   263,
     263,   264,   264,   264,   264,   264,   264,   265,   265,   265,
     265,   266,   267,   267,   267,   267,   267,   267,   268,   268,
     268,   268,   269,   269,   270,   270,   270,   271,   271,   272,
     272,   272,   272,   272,   272,   273,   273,   274
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     3,     2,     3,     2,     5,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       7,     5,     3,     5,     5,     3,     2,     2,     5,     2,
       5,     2,     4,     1,     1,     7,     7,     5,     0,     7,
       1,     1,     2,     2,     1,     5,     5,     5,     3,     4,
       3,     7,     8,     5,     3,     1,     1,     3,     1,     4,
       7,     6,     1,     1,     7,     9,     8,    10,     5,     7,
       6,     8,     1,     1,     5,     4,     5,     7,     1,     3,
       6,     6,     8,     1,     2,     3,     1,     2,     3,     6,
       5,     9,     2,     1,     1,     1,     0,     6,     5,     1,
       4,     1,     1,     2,     5,     6,     4,     7,     8,     6,
       1,     1,     1,     1,     1,     1,     0,     9,     0,     8,
       1,     2,     4,     0,     6,     3,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     3,     1,     3,
       4,     0,     6,     0,     5,     5,     2,     0,     6,     1,
       1,     0,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     6,     6,     7,     8,     8,     7,     5,     2,     2,
       2,     0,     7,     0,     6,     0,     8,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     2,     4,     2,     5,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     3,     1,     2,
       7,     3,     1,     2,     1,     3,     1,     1,     1,     2,
       5,     2,     2,     1,     2,     2,     1,     1,     1,     1,
       2,     3,     1,     2,     3,     4,     5,     4,     1,     2,
       3,     4,     5,     3,     4,     4,     1,     2,     4,     4,
       5,     3,     4,     4,     1,     2,     2,     3,     1,     2,
       1,     2,     3,     4,     3,     4,     2,     3,     3,     4,
       3,     3,     2,     2,     1,     1,     2,     1,     1,     1,
       1,     2,     1,     2,     3,     1,     1,     1,     2,     2,
       1,     1,     2,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     2,     1,     1,     3,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     5,     1,     1,     3,     4,     5,
       5,     6,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     5,     2,     2,
       2,     2,     2,     1,     0,     3,     1,     1,     3,     2,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     4,     5,     1,     3,     3,     4,     4,     3,
       2,     1,     1,     3,     2,     3,     1,     1,     1,     1,
       1,     2,     4,     1,     3,     1,     3,     3,     2,     2,
       2,     2,     2,     4,     1,     3,     1,     3,     3,     2,
       2,     2,     2,     1,     1,     1,     1,     3,     1,     3,
       5,     1,     3,     3,     5,     1,     1,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
     467,     0,     0,     0,     0,     0,    10,     4,   467,   326,
     334,   327,   328,   331,   332,   329,   330,   317,   333,   316,
     335,   467,   320,   336,   337,   338,   339,     0,   307,   308,
     309,   407,   408,     0,   404,   405,     0,     0,   435,     0,
       0,   305,   467,   312,   315,   323,   324,   406,     0,   321,
     433,     6,     0,     0,   467,     1,    15,    64,    60,    61,
       0,   229,    14,   226,   467,     0,     0,    82,    83,   467,
     467,     0,     0,   228,   230,   231,     0,   232,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     9,    11,    18,    19,    20,    21,    22,    23,
      24,    25,   467,    26,    27,    28,    29,    30,    31,    32,
       0,    33,    34,    35,    36,    37,    38,    12,   113,   115,
     114,    16,    13,   130,   131,   132,   133,   134,   135,     0,
     233,   467,   441,   426,   318,     0,   319,     0,     0,     3,
     311,   306,   467,   340,     0,     0,   290,   304,     0,   256,
     239,   467,   262,   467,   288,   284,   276,   253,   313,   325,
     322,     0,     0,   431,     5,     8,     0,   234,   467,   236,
      17,     0,   453,   227,     0,     0,   458,     0,   467,     0,
     310,     0,     0,     0,     0,    78,     0,   467,   467,     0,
       0,   467,   163,     0,     0,    62,    63,     0,     0,    51,
      49,    46,    47,   467,     0,   467,     0,   467,   467,     0,
     112,   467,   467,     0,     0,     0,     0,     0,     0,   276,
     467,     0,     0,   356,   364,   365,   366,   367,   368,   369,
     370,     0,     0,     0,     0,     0,     0,     0,     0,   247,
       0,   242,   467,   351,   310,     0,   350,   352,   355,   353,
     244,   241,   436,   434,     0,   314,   467,   290,     0,     0,
     284,   321,   251,   249,     0,   296,     0,   350,   252,   467,
       0,   263,   289,   268,   302,   303,   277,   254,   467,     0,
     255,   467,     0,   286,   260,   285,   268,   291,   440,   439,
     438,     0,     0,   235,   238,   427,     0,   428,   452,   116,
     461,     0,    68,    45,   340,     0,   467,    70,     0,     0,
       0,    74,     0,     0,     0,    98,     0,     0,   159,     0,
     467,   161,     0,     0,   103,     0,     0,     0,   107,   257,
     258,   259,    42,     0,   104,   106,   429,     0,   430,    54,
       0,    53,     0,     0,   152,   467,   156,   406,   154,   145,
       0,   427,     0,     0,     0,     0,     0,     0,     0,   268,
       0,   467,     0,   343,   467,   467,   138,   322,     0,     0,
     362,   388,   389,   363,   391,   390,   425,     0,   243,   246,
     392,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   432,     0,
     290,   284,   321,     0,   276,   300,   298,   286,     0,   276,
     291,     0,   341,   297,   284,   321,   269,   467,     0,   301,
       0,   281,     0,     0,   294,     0,   261,   287,   292,     0,
     264,   437,     7,   467,     0,   467,     0,     0,   457,     0,
       0,    69,    39,    77,     0,     0,     0,     0,     0,     0,
       0,   160,     0,     0,   467,   467,     0,     0,   108,     0,
     467,     0,     0,     0,     0,     0,   143,     0,   153,   158,
      58,     0,     0,     0,     0,    79,     0,   126,   467,     0,
     321,     0,     0,   122,   467,     0,   142,   394,     0,   393,
     396,   357,     0,   304,     0,   467,   467,   386,   385,   383,
     384,     0,   382,   381,   377,   378,   376,   380,   379,   372,
     371,   375,   374,   373,     0,     0,   291,   279,   278,   292,
       0,     0,     0,   268,   270,   291,     0,   273,     0,   283,
     282,   299,   295,     0,   265,   293,   267,   237,    66,    67,
      65,     0,   462,   463,   466,   465,   459,    43,    44,     0,
      76,    73,    75,   456,    93,   455,     0,    88,   467,   454,
      92,     0,   465,     0,     0,    99,   467,   197,   165,   164,
       0,   226,     0,     0,    50,    48,   467,    41,   105,   444,
       0,   446,     0,    57,     0,     0,   110,   467,   467,   467,
     467,     0,     0,   346,     0,   345,   348,   467,   467,     0,
     119,   121,   118,     0,   123,   171,   190,     0,     0,     0,
       0,   230,     0,   217,   218,   210,   219,   188,   169,   215,
     211,   209,   212,   213,   214,   216,   189,   185,   186,   173,
     179,   183,   182,     0,     0,   174,   175,   178,   184,   176,
     180,   177,   187,     0,   233,   467,   136,   358,     0,   304,
     303,     0,     0,     0,   245,     0,   467,   280,   250,   271,
       0,   275,   274,   266,   117,     0,     0,     0,   467,     0,
     411,     0,   414,     0,     0,     0,     0,    90,   467,     0,
     162,   227,   467,     0,   101,     0,   100,     0,     0,     0,
     442,     0,   467,     0,    52,   146,   147,   150,   149,   144,
     148,   151,     0,   157,     0,     0,    81,     0,   467,     0,
     467,   340,   467,   129,     0,   467,   467,     0,   167,   199,
     198,   200,     0,     0,     0,   166,     0,     0,     0,   321,
     409,   395,   397,     0,   410,     0,   360,   359,     0,   354,
     387,   240,   272,   464,   460,    40,     0,   467,     0,    84,
     465,    95,    89,   467,     0,     0,    97,    71,     0,     0,
     109,   451,   449,   450,   445,   447,     0,    55,    56,     0,
      59,    80,   347,   349,   344,   127,     0,     0,     0,     0,
       0,   421,   467,     0,     0,   172,     0,     0,   467,     0,
       0,   467,     0,   467,   203,   322,   181,   467,   402,   401,
     403,   467,   399,     0,   361,     0,     0,   467,    96,     0,
      91,   467,    86,    72,   102,   448,   443,     0,   128,     0,
     419,   420,   422,     0,   415,   416,   124,   120,   467,     0,
     467,     0,   139,   467,     0,     0,     0,     0,   201,   467,
     467,   398,     0,     0,    94,   412,     0,    85,     0,   111,
     417,   418,     0,   424,   125,     0,     0,   467,     0,   467,
     467,   467,   225,   467,     0,   207,   208,     0,   400,   140,
     137,     0,   413,    87,   423,   168,   467,   192,     0,   467,
       0,     0,   191,     0,   204,   205,   141,   193,     0,   220,
     221,   196,   467,   467,   202,     0,   222,   224,   340,   195,
     194,   206,     0,   223
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,    92,    93,    94,   549,   613,   614,   615,
     616,    99,   339,   340,   617,   618,   589,   102,   103,   619,
     105,   620,   107,   621,   551,   184,   622,   110,   623,   557,
     447,   624,   314,   625,   323,   206,   334,   207,   626,   627,
     628,   629,   435,   118,   602,   482,   119,   120,   121,   122,
     123,   735,   485,   870,   630,   631,   587,   699,   343,   344,
     345,   468,   632,   127,   454,   320,   633,   786,   717,   634,
     635,   636,   637,   638,   639,   640,   863,   839,   895,   864,
     641,   877,   887,   642,   643,   258,   167,   293,   168,   240,
     241,   378,   242,   149,   150,   328,   151,   271,   152,   153,
     154,   218,    40,    41,   243,   180,    43,    44,    45,    46,
     263,   264,   362,   594,   595,   772,   245,   267,   247,   248,
     488,   489,   645,   731,   732,   801,    47,    48,   733,   888,
     713,   780,   821,   822,   132,   300,   337,    49,   163,    50,
     582,   690,   249,   560,   175,   301,   546,   169
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -550
static const yytype_int16 yypact[] =
{
     590,  3291,  3341,   121,   117,  2846,  -550,  -550,   -67,  -550,
    -550,  -550,  -550,  -550,  -550,  -550,  -550,  -550,  -550,  -550,
    -550,   -67,  -550,  -550,  -550,  -550,  -550,   115,  -550,  -550,
    -550,  -550,  -550,   191,  -550,  -550,    75,   161,  -550,   156,
    3797,   717,   325,   717,  -550,  -550,  1803,  -550,   191,  -550,
     100,  -550,   221,   227,  3549,  -550,   166,  -550,  -550,  -550,
     288,  -550,  -550,   318,   298,  3401,   303,  -550,  -550,   298,
     311,   333,   366,  -550,  -550,  -550,   392,  -550,   116,    42,
     420,   106,   431,   429,   384,  3599,  3599,   442,   455,   318,
     465,   600,  -550,  -550,  -550,  -550,  -550,  -550,  -550,  -550,
    -550,  -550,   298,  -550,  -550,  -550,  -550,  -550,  -550,  -550,
     983,  -550,  -550,  -550,  -550,  -550,  -550,  -550,  -550,  -550,
    -550,  -550,  -550,  -550,  -550,  -550,  -550,  -550,  -550,  3648,
    -550,  1740,  -550,  -550,  -550,   296,  -550,    49,   461,  -550,
     717,  -550,  2522,   463,  1862,  2350,    87,   241,   191,  -550,
    -550,   104,   323,   104,   356,   176,   252,  -550,  -550,  -550,
    -550,   518,    77,  -550,  -550,  -550,   484,  -550,   487,  -550,
    -550,   377,  -550,   126,   377,   377,  -550,   532,   108,  1003,
    -550,   256,   191,   530,   571,  -550,   377,  1522,  3549,   191,
     562,   129,  -550,   573,   616,  -550,  -550,   377,   620,  -550,
    -550,  -550,   623,  3549,   583,   228,   592,   596,   377,   318,
     623,  3549,  3549,   191,   318,   270,   381,   377,   312,   535,
     194,  1014,    85,  -550,  -550,  -550,  -550,  -550,  -550,  -550,
    -550,  2350,   610,  2350,  2350,  2350,  2350,  2350,  2350,  -550,
     557,  -550,   613,   621,   113,  1699,    -8,  -550,  -550,   623,
    -550,  -550,  -550,   100,   568,  -550,  2626,   742,   615,   626,
     928,   561,  -550,   614,  2350,  -550,  1825,  -550,  1699,  2626,
     191,   387,   356,  -550,  -550,   552,  -550,  -550,  3549,  1984,
    -550,  3549,  2106,    87,   387,   356,   575,   720,  -550,  -550,
     100,   635,  3549,  -550,  -550,  -550,   641,   623,  -550,  -550,
     330,   646,  -550,  -550,  -550,   715,   104,  -550,   649,   650,
     657,   652,    53,   667,   669,  -550,   673,   684,  -550,   191,
    -550,  -550,   688,   698,  -550,   700,   703,  3599,  -550,  -550,
    -550,  -550,  -550,  3599,  -550,  -550,  -550,   705,  -550,  -550,
     207,   131,   706,   655,  -550,   708,  -550,    43,  -550,  -550,
      20,   317,   933,   933,   648,   722,   105,   738,   381,   681,
     720,    83,   745,  -550,  2687,   625,  -550,   287,  1197,  3698,
    1163,  -550,  -550,  -550,  -550,  -550,  -550,  1740,  -550,  -550,
    -550,  2350,  2350,  2350,  2350,  2350,  2350,  2350,  2350,  2350,
    2350,  2350,  2350,  2350,  2350,  2350,  2350,  2350,  -550,   461,
     443,   341,   689,   284,  -550,  -550,  -550,   443,   394,   696,
     933,  2350,  1699,  -550,   970,    13,  -550,  3549,  2228,  -550,
     752,  -550,  1947,   762,  -550,  2069,   387,   356,  1027,   381,
     387,  -550,  -550,   487,   304,  -550,   377,  1212,  -550,   765,
     766,  -550,  -550,  -550,   509,   651,  1958,   770,  3549,  1003,
     779,  -550,   769,  2935,  -550,   865,  3599,   497,   787,   782,
     596,   281,   789,   377,  3549,   538,  -550,  3549,  -550,  -550,
    -550,   933,   299,   381,    25,  -550,   874,  -550,   829,   793,
     648,   801,   690,  -550,   203,  1621,  -550,  -550,   798,  -550,
    -550,  2350,  1404,  2472,    15,   325,   613,  1057,  1057,  1122,
    1122,  2716,  1382,  1479,  1489,  1249,  1163,   828,   828,   692,
     692,  -550,  -550,  -550,   191,   696,  -550,  -550,  -550,   443,
     407,  2191,   493,   696,  -550,   381,   808,  -550,  2313,  -550,
    -550,  -550,  -550,   381,   387,   356,   387,  -550,  -550,  -550,
     623,  3024,  -550,   809,  -550,   131,   811,  -550,  -550,  1621,
    -550,  -550,   623,  -550,  -550,  -550,   814,  -550,   674,   623,
    -550,   802,    78,   265,   651,  -550,   674,  -550,  -550,  -550,
    3113,   318,  3747,   351,  -550,  -550,  3549,  -550,  -550,   213,
     736,  -550,   774,  -550,   818,   821,  -550,   730,   708,  -550,
     674,   230,   381,   816,    94,  -550,  -550,   823,  3549,  1003,
    -550,  -550,  -550,   831,  -550,  -550,  -550,   830,   813,   815,
     817,   748,   518,  -550,  -550,  -550,  -550,  -550,  -550,  -550,
    -550,  -550,  -550,  -550,  -550,  -550,  -550,  -550,  -550,  -550,
    -550,  -550,  -550,   836,  1621,  -550,  -550,  -550,  -550,  -550,
    -550,  -550,  -550,  3450,   845,   822,  -550,  1699,  2350,  2472,
    2740,  2350,   852,   853,  -550,  2350,   104,  -550,  -550,  -550,
     498,  -550,  -550,   387,  -550,   377,   377,   855,  3549,   871,
     835,   538,  -550,  1212,   879,   377,   875,  -550,   674,   877,
    -550,   623,    -1,  1003,  -550,  3599,  -550,   882,   912,    84,
    -550,   111,  1740,   196,  -550,  -550,  -550,  -550,  -550,  -550,
    -550,  -550,  3500,  -550,  3202,   884,  -550,  2350,   829,   926,
    3549,  -550,   851,  -550,   887,   625,  3549,  1621,  -550,  -550,
    -550,  -550,   518,   889,  1003,  -550,  3698,    41,   212,   890,
    -550,   888,  -550,   369,  -550,  1621,  1699,  1699,  2350,  -550,
    1837,  -550,  -550,  -550,  -550,  -550,   894,  3549,   916,  -550,
     623,   917,  -550,   674,   948,   538,  -550,  -550,   918,   922,
    -550,  -550,   213,  -550,   213,  -550,   873,  -550,  -550,  1032,
    -550,  -550,  -550,  1699,  -550,  -550,   690,   929,   931,   191,
     505,  -550,   104,   690,   930,  -550,  1621,   932,  3549,   690,
     -15,  2687,  2350,    19,  -550,   198,  -550,   822,  -550,  -550,
    -550,   822,  -550,   934,  1699,   936,   949,  3549,  -550,   950,
    -550,   674,  -550,  -550,  -550,  -550,  -550,   951,  -550,   514,
    -550,   953,  -550,   935,  -550,  -550,  -550,  -550,   104,   956,
    3549,   959,  -550,  3549,   965,   967,   972,  1618,  -550,  1003,
     822,  -550,   191,   978,  -550,  -550,   973,  -550,   974,  -550,
    -550,  -550,   191,  -550,  -550,  1621,   975,   674,   985,  3549,
    3549,   823,  -550,  1003,   981,  -550,  -550,   372,  -550,  -550,
    -550,   690,  -550,  -550,  -550,  -550,   674,  -550,   543,   674,
     987,   990,  -550,   996,  -550,  -550,  -550,  -550,   447,  -550,
    -550,  -550,   674,   674,  -550,   997,  -550,  -550,  -550,  -550,
    -550,  -550,   999,  -550
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -550,  -550,  -314,  -550,  -550,  -550,  -550,    10,    12,    23,
      24,  -550,   605,  -550,    28,    30,  -550,  -550,  -550,    35,
    -550,    36,  -550,    38,  -550,  -550,    50,  -550,    54,  -446,
    -549,    55,  -550,    63,  -550,  -311,   545,   -84,    66,    70,
      72,    76,  -550,   425,  -377,   332,  -550,  -550,  -550,  -550,
     467,  -550,  -550,  -550,    -2,     5,  -550,  -550,  -550,  -550,
     588,   468,    81,  -550,  -550,  -550,  -536,  -550,  -550,  -550,
     472,  -550,   473,    90,  -550,  -550,  -550,  -550,  -550,   199,
    -550,  -550,  -375,  -550,    -3,   186,  -550,   628,   222,   373,
    -550,   570,   691,   -97,   572,  -550,   -44,  -117,  -181,  -112,
    -121,   -22,   -34,  -550,   576,    45,   -36,  -550,  1028,  -550,
    -286,  -550,  -550,  -550,   365,  -550,   966,  -119,  -410,  -550,
    -550,  -550,  -550,   236,   280,  -550,  -201,   -33,   277,  -493,
     219,  -550,  -550,   234,  1061,  -114,  -550,   739,  -142,  -113,
    -550,  -202,   726,   516,   183,  -165,  -409,     0
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -468
static const yytype_int16 yytable[] =
{
       6,   204,   129,   124,   140,   130,   453,   141,   133,   158,
     125,   347,   246,   667,   676,    95,   459,    96,   439,   586,
     155,   133,   833,   131,   253,   272,   298,   544,    97,    98,
     259,  -248,   324,   100,   285,   101,   544,   563,   284,   757,
     104,   106,   157,   108,     8,   191,    42,    42,   288,   290,
     355,   524,     8,   651,   277,   109,   280,   296,   213,   111,
     112,   302,   838,   524,   176,   671,   217,   308,   113,   176,
     185,   114,   312,   679,   470,   115,   403,   116,   791,   408,
       8,   117,  -155,  -248,   298,   192,   126,   762,     8,   131,
       8,   445,   446,   330,   336,   128,   222,   705,   725,    42,
     834,   284,   176,   357,   712,   254,   255,   147,     8,   131,
     195,   398,   792,   275,   764,   525,     8,    55,   677,     8,
     260,   541,    53,   477,   269,   274,  -342,   592,   366,  -428,
     652,   250,   298,   708,  -155,   306,   272,   298,   709,   285,
     570,   144,    36,    36,   259,   573,    38,    38,   431,   196,
     142,   157,  -467,   157,   252,   143,   216,   259,    54,   304,
     135,   329,   427,   147,   143,   148,   426,   144,   294,   299,
     430,   403,   408,   131,   464,   145,   244,   365,   133,     8,
     319,   785,   289,   155,   145,   755,    36,    42,    36,   763,
      38,   133,    38,   353,     8,   189,   139,   361,   131,   803,
     767,   137,   808,   161,  -467,   331,    36,   335,   338,   440,
      38,   270,   348,   269,    36,   793,   765,    36,    38,   131,
     363,    38,   155,    39,    52,   749,   162,   147,   146,   520,
     144,     8,    42,    42,   401,   147,   298,   148,   486,   768,
     166,   426,   379,   430,   157,   462,   463,   414,    42,   460,
     829,   138,   182,   419,   143,   794,    42,    42,   246,   295,
     809,   164,   172,   544,   751,   142,   347,   165,   483,   840,
     706,   542,   170,   351,   145,   704,   172,    36,   603,   272,
     285,    38,   144,   353,   579,   214,   427,    28,    29,    30,
     520,   283,    36,   285,   307,    36,    38,   522,   584,    38,
     270,    42,     8,   674,   675,   172,   157,   535,   538,   812,
     172,   534,   536,    36,    42,     8,   688,    38,   848,   875,
       6,   278,   517,    42,   172,   171,    42,   486,     8,    36,
    -467,   484,   561,    38,   473,   174,   305,    42,   279,   689,
     181,   251,   353,   146,     8,   469,   494,   539,   183,   356,
     147,   133,   148,   239,   287,   553,   522,   172,   487,   534,
     278,   133,   142,   147,   878,   157,   514,   490,   712,   436,
     186,    36,     8,   315,   316,    38,   143,   279,   256,   144,
     295,   437,   580,   172,     8,   352,   581,   604,   201,   326,
     172,   684,   147,   281,   555,   144,   145,   342,   535,   818,
      36,   558,   685,   187,    38,   566,   827,   131,   660,    42,
     282,   797,   832,    36,   216,   885,   663,    38,   356,  -467,
    -467,   147,   244,   148,   417,   778,    36,   358,   590,   188,
      38,   278,   518,   294,   346,     6,   270,   798,   799,   800,
     146,   418,    36,  -467,   278,   657,    38,   147,   279,   148,
     129,   124,   572,   130,     6,   130,   407,   194,   125,   650,
     335,   279,    42,    95,   420,    96,   198,   423,   197,   199,
      36,   274,   200,   155,    38,   660,    97,    98,   596,   208,
     256,   100,    36,   101,   157,   644,    38,   896,   104,   106,
     897,   108,   209,    42,   886,   157,   379,   144,   898,   723,
     743,   744,   211,   109,   891,   270,   262,   111,   112,    42,
      31,    32,    42,   550,   433,   172,   113,   899,   900,   114,
     678,     8,   291,   115,   670,   116,   292,    34,    35,   117,
     417,   659,   670,   310,   126,   417,   742,   574,   129,   124,
     575,   130,   553,   128,   172,   824,   125,   418,   825,   644,
     479,    95,   418,    96,   850,   715,   670,   851,   672,   741,
     815,   561,   816,   670,    97,    98,   672,   129,   124,   100,
     130,   101,   303,   246,   311,   125,   104,   106,   554,   108,
      95,   555,    96,   889,   702,   697,   890,   130,   469,     6,
     672,   109,   698,    97,    98,   111,   112,   672,   100,   239,
     101,   759,   318,   526,   113,   104,   106,   114,   108,   787,
     728,   115,   902,   116,   140,   650,   321,   117,   483,   322,
     109,    42,   126,   325,   111,   112,   327,   274,   419,   298,
     753,   128,   332,   113,   644,   333,   114,   360,   556,   758,
     115,   179,   116,    42,   670,   734,   117,   369,   376,    31,
      32,   126,   377,   405,     8,   553,   157,   172,   380,   399,
     128,   205,   205,   410,   406,   776,    34,    35,   411,   222,
     565,    28,    29,    30,   147,   432,   143,   428,   672,   434,
     789,   484,   133,   365,   438,   826,   585,   441,   305,   346,
     212,   554,   250,   442,   555,   443,   145,     1,     2,     3,
     481,   129,   124,   444,   130,   221,   448,   449,   596,   125,
     811,   450,   781,    42,    95,   157,    96,   644,     8,   670,
      28,    29,    30,     8,   451,   365,   455,    97,    98,   599,
     600,   854,   100,   601,   101,   644,   456,   244,   457,   104,
     106,   458,   108,   461,   465,     8,   466,   467,    61,   669,
     471,   556,    36,   672,   109,    42,    38,   356,   111,   112,
     472,    42,   687,    28,    29,    30,   216,   113,   835,   353,
     114,   571,   136,   147,   115,   148,   116,   670,   475,   142,
     117,   156,   157,   476,   714,   126,   644,   160,   478,   173,
     529,   516,    42,   133,   128,   865,   144,   734,   519,   871,
     531,   734,    73,    74,    75,   547,   548,    77,   564,   568,
     202,   672,   395,   396,   397,   210,    36,   190,   193,   865,
      38,    36,   567,   670,   576,    38,   577,   670,   157,   583,
     352,   597,   593,    42,    91,   429,    42,   147,   598,   866,
     734,   646,   670,    36,   270,   670,   661,    38,   665,   219,
     666,   668,    42,   673,   746,   644,   693,   672,   670,   670,
     710,   672,   691,   866,   692,   694,   148,   707,   716,    28,
      29,    30,   722,   718,   711,    42,   672,     8,    42,   672,
     724,   261,     8,    61,   719,   273,   720,   276,   721,  -170,
     738,   739,   672,   672,   286,   730,   777,   297,   669,   745,
     297,   297,   784,   205,    42,    42,   571,   297,   747,   205,
     748,   356,   297,   754,   239,   761,   305,   756,   219,   752,
     760,   309,   779,   297,   771,   782,   788,   797,   317,     8,
     796,     8,   805,   806,   297,   341,     8,    73,    74,    75,
     350,   297,    77,   297,   156,   495,   393,   394,   395,   396,
     397,     8,   349,   807,   354,   273,   675,   359,   813,   136,
     219,   367,   814,   305,   817,   142,   775,   819,   828,   830,
     305,   820,   853,     8,   831,    36,   844,   836,   843,    38,
      36,     8,   144,   156,    38,   305,     8,   845,   810,   533,
     847,   849,   852,   846,   216,   402,   404,   857,   270,   409,
     855,   147,   859,   148,   860,   578,     8,   269,   415,   416,
     861,   872,   695,   876,   873,   305,   856,     8,   869,   858,
     215,   884,   273,   879,   144,   892,   273,    36,   893,    36,
       8,    38,   205,    38,    36,     8,   894,   901,    38,   903,
     305,   216,   543,   407,   354,   880,   881,   783,   147,    36,
     148,   364,   148,    38,   696,   588,   703,   148,   452,   700,
     701,   537,   883,   216,   269,   766,   654,   653,   496,   791,
     147,    36,   148,   774,   159,    38,   867,   841,   842,    36,
     882,   144,   134,    38,    36,   407,   874,     0,    38,   686,
       0,   404,   404,   216,   270,   474,     0,   273,   216,   273,
     147,     0,   148,   480,    36,   147,     0,   148,    38,     0,
     266,   268,     0,     0,     0,    36,     0,     0,   216,    38,
       0,     0,     0,     0,     0,   147,     0,   148,    36,   216,
       0,     0,    38,    36,     0,     0,   147,    38,   148,     0,
     515,     0,   533,     0,     0,     0,     0,   216,   683,   404,
       0,   270,     0,   523,   147,     0,   148,     0,     0,     0,
     540,     0,   297,   545,     0,     0,     0,   273,   273,     0,
     552,   559,   562,   391,   392,   393,   394,   395,   396,   397,
       0,     0,     0,     0,   219,     0,     0,     0,   219,   297,
       0,   559,     0,     0,     0,     0,     0,   368,   591,   370,
     371,   372,   373,   374,   375,     0,     0,     0,     0,     0,
     404,   219,   273,     0,     0,   273,   381,   382,   172,   727,
       0,     0,     0,   224,   225,   226,   227,   228,   229,   230,
     412,     0,     0,     0,   156,   491,     0,     0,   391,   392,
     393,   394,   395,   396,   397,   422,     0,     0,   425,     0,
       0,     0,     0,   656,     0,     0,     0,   381,   382,   383,
     384,   205,     0,     0,   273,     0,     0,     0,     0,     0,
       0,     0,   273,     0,     0,     0,     0,     0,   769,   391,
     392,   393,   394,   395,   396,   397,     0,     0,     0,     0,
     559,   381,   382,   383,   384,   385,     0,   681,     0,   559,
       0,     0,   790,   219,     0,     0,     0,     0,   386,   387,
     388,   389,   492,   391,   392,   393,   394,   395,   396,   493,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   273,     0,     0,     0,     0,     0,     0,   219,     0,
       0,     0,     0,   381,   382,   383,   384,   497,   498,   499,
     500,   501,   502,   503,   504,   505,   506,   507,   508,   509,
     510,   511,   512,   513,   390,   391,   392,   393,   394,   395,
     396,   397,     0,     0,     0,     0,     0,   521,     0,     0,
       0,     0,   729,     0,   528,     0,     0,     0,     0,     0,
       0,   297,   297,     0,     0,     0,     0,   559,     0,   750,
       0,   297,     0,     0,     0,     0,     0,     8,     0,     0,
     172,     0,     0,   219,   223,   224,   225,   226,   227,   228,
     229,   230,   219,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,   231,   648,     0,     0,     0,     0,     0,   219,     0,
      28,    29,    30,    31,    32,     0,   232,   647,   506,   513,
       0,     0,     0,   219,     0,     0,   219,   795,     0,    33,
      34,    35,   802,     0,     0,     0,   381,   382,   383,   384,
       0,   559,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   219,   387,   388,   389,   390,   391,   392,
     393,   394,   395,   396,   397,    36,     0,     0,   219,    38,
       0,     0,     0,     0,     0,     0,     0,     0,   823,   233,
       0,     0,   234,   235,     0,     8,   236,   237,   238,     0,
     480,     0,     0,   313,     0,     0,     0,     0,     0,     0,
       0,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,     0,
       0,     0,     0,     0,     0,     0,     0,    27,    28,    29,
      30,    31,    32,   381,   382,   383,   384,     0,   219,     0,
       0,   868,   219,   381,   382,   383,   384,    33,    34,    35,
       0,   823,   388,   389,   390,   391,   392,   393,   394,   395,
     396,   397,   219,   389,   390,   391,   392,   393,   394,   395,
     396,   397,     0,     0,   736,   373,     0,   737,     0,     0,
       0,   740,   605,    36,  -467,    57,    37,    38,    58,    59,
      60,     0,     0,     0,     0,     0,     0,     0,     0,    61,
    -467,  -467,  -467,  -467,  -467,  -467,  -467,  -467,  -467,  -467,
    -467,  -467,  -467,  -467,  -467,  -467,  -467,  -467,   862,     0,
       0,   606,    63,     0,     0,  -467,     0,  -467,  -467,  -467,
    -467,  -467,     0,   773,     0,     0,     0,     0,    65,    66,
      67,    68,   607,    70,    71,    72,  -467,  -467,  -467,   608,
     609,   610,     0,    73,   611,    75,     0,    76,    77,    78,
       0,     0,     0,    82,   804,    84,    85,    86,    87,    88,
      89,     0,   381,   382,   383,   384,   385,     0,     0,     0,
      90,     0,  -467,     0,     0,    91,  -467,  -467,     0,   386,
     387,   388,   389,   390,   391,   392,   393,   394,   395,   396,
     397,     0,     0,     8,     0,   612,   172,     0,     0,     0,
     223,   224,   225,   226,   227,   228,   229,   230,   837,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,   231,     0,     0,
       0,     0,     0,     0,     0,    27,    28,    29,    30,    31,
      32,     0,   232,   381,   382,   383,   384,   385,     0,     0,
       0,     0,     0,     0,     0,    33,    34,    35,     0,     0,
     386,   387,   388,   389,   390,   391,   392,   393,   394,   395,
     396,   397,     9,    10,    11,    12,    13,    14,    15,    16,
       0,    18,     0,    20,     0,     0,    23,    24,    25,    26,
       0,    36,     0,     0,    37,    38,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   233,     0,     0,   234,   235,
       0,     0,   236,   237,   238,     8,     0,     0,   172,     0,
       0,     0,   223,   224,   225,   226,   227,   228,   229,   230,
     413,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,   231,
       0,     0,     0,     0,     0,     0,     0,     0,    28,    29,
      30,    31,    32,     0,   232,     0,     0,   265,     0,   381,
     382,   383,   384,   385,     0,     0,     0,    33,    34,    35,
       0,   381,   382,   383,   384,     0,   386,   387,   388,   389,
     390,   391,   392,   393,   394,   395,   396,   397,   386,   387,
     388,   389,   390,   391,   392,   393,   394,   395,   396,   397,
       0,   295,     0,    36,   172,     0,     0,    38,     0,   224,
     225,   226,   227,   228,   229,   230,     0,   233,     0,     0,
     234,   235,     0,     0,   236,   237,   238,     8,     0,     0,
     172,     0,     0,     0,   223,   224,   225,   226,   227,   228,
     229,   230,   530,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,   231,     0,     0,     0,     0,     0,     0,     0,     0,
      28,    29,    30,    31,    32,     0,   232,     0,     0,   421,
       0,   381,   382,   383,   384,   385,     0,     0,     0,    33,
      34,    35,     0,     0,     0,     0,     0,     0,   386,   387,
     388,   389,   390,   391,   392,   393,   394,   395,   396,   397,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    36,     0,     0,     0,    38,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   233,
       0,     0,   234,   235,     0,     0,   236,   237,   238,     8,
       0,     0,   172,     0,     0,     0,   223,   224,   225,   226,
     227,   228,   229,   230,   532,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,   231,     0,     0,     0,     0,     0,     0,
       0,     0,    28,    29,    30,    31,    32,     0,   232,     0,
       0,   424,     0,   381,   382,   383,   384,   385,     0,     0,
       0,    33,    34,    35,     0,     0,     0,     0,     0,     0,
     386,   387,   388,   389,   390,   391,   392,   393,   394,   395,
     396,   397,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    36,     0,     0,
       0,    38,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   233,     0,     0,   234,   235,     0,     0,   236,   237,
     238,     8,     0,     0,   172,     0,     0,     0,   223,   224,
     225,   226,   227,   228,   229,   230,   658,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,   231,     0,     0,     0,     0,
       0,     0,     0,     0,    28,    29,    30,    31,    32,     0,
     232,     0,     0,   527,     0,   381,   382,   383,   384,   385,
       0,     0,     0,    33,    34,    35,     0,     0,     0,     0,
       0,     0,   386,   387,   388,   389,   390,   391,   392,   393,
     394,   395,   396,   397,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    36,
       0,     0,     0,    38,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   233,     0,     0,   234,   235,     0,     0,
     236,   237,   238,     8,     0,     0,   172,     0,     0,     0,
     223,   224,   225,   226,   227,   228,   229,   230,   662,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,   231,     0,     0,
       0,     0,     0,     0,     0,     0,    28,    29,    30,    31,
      32,     0,   232,     0,     0,     0,     0,   381,   382,   383,
     384,   385,     0,     0,     0,    33,    34,    35,     0,     0,
       0,     0,     0,     0,   386,   387,   388,   389,   390,   391,
     392,   393,   394,   395,   396,   397,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    36,     0,     0,     0,    38,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   233,     0,     0,   234,   235,
       0,     0,   236,   237,   238,     8,     0,     0,   172,     0,
       0,     0,   223,   224,   225,   226,   227,   228,   229,   230,
       0,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,   231,
       0,     0,     0,     0,     0,     0,     0,     0,    28,    29,
      30,    31,    32,     0,   232,     8,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    33,    34,    35,
       0,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,   256,
       0,     0,     0,     0,     0,     0,     0,    27,    28,    29,
      30,    31,    32,    36,     0,     0,   144,    38,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    33,    34,    35,
     234,   235,     0,     0,   649,   237,   238,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    36,     0,     0,    37,    38,     0,     8,
       0,     0,     0,     0,     0,     0,     0,   257,     0,     0,
       0,     0,     0,     0,   147,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,   256,     0,     0,     0,     0,     0,     0,
       0,    27,    28,    29,    30,    31,    32,     0,     0,     0,
     144,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       8,    33,    34,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,     0,     0,     0,    36,     0,     0,
      37,    38,    27,    28,    29,    30,    31,    32,     0,     0,
       0,   400,     0,     8,     0,     0,     0,     0,   147,     0,
       0,     0,    33,    34,    35,     0,     0,     0,     0,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   655,    36,    31,
      32,    37,    38,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   352,     0,     0,    33,    34,    35,     0,   147,
     381,   382,   383,   384,   385,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   386,   387,   388,
     389,   390,   391,   392,   393,   394,   395,   396,   397,     0,
       0,    36,     0,     0,     0,    38,    -2,    56,     0,  -467,
      57,     0,     0,    58,    59,    60,     0,     0,     0,     0,
       0,     0,   147,     0,    61,  -467,  -467,  -467,  -467,  -467,
    -467,  -467,  -467,  -467,  -467,  -467,  -467,  -467,  -467,  -467,
    -467,  -467,  -467,     0,     0,     0,    62,    63,     0,     0,
       0,     0,  -467,  -467,  -467,  -467,  -467,     0,     0,    64,
       0,     0,     0,    65,    66,    67,    68,    69,    70,    71,
      72,  -467,  -467,  -467,     0,     0,     0,     0,    73,    74,
      75,     0,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    56,     0,  -467,    57,
       0,     0,    58,    59,    60,    90,     0,  -467,     0,     0,
      91,  -467,     0,    61,  -467,  -467,  -467,  -467,  -467,  -467,
    -467,  -467,  -467,  -467,  -467,  -467,  -467,  -467,  -467,  -467,
    -467,  -467,     0,     0,     0,    62,    63,     0,     0,   569,
       0,  -467,  -467,  -467,  -467,  -467,     0,     0,    64,     0,
       0,     0,    65,    66,    67,    68,    69,    70,    71,    72,
    -467,  -467,  -467,     0,     0,     0,     0,    73,    74,    75,
       0,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    56,     0,  -467,    57,     0,
       0,    58,    59,    60,    90,     0,  -467,     0,     0,    91,
    -467,     0,    61,  -467,  -467,  -467,  -467,  -467,  -467,  -467,
    -467,  -467,  -467,  -467,  -467,  -467,  -467,  -467,  -467,  -467,
    -467,     0,     0,     0,    62,    63,     0,     0,   664,     0,
    -467,  -467,  -467,  -467,  -467,     0,     0,    64,     0,     0,
       0,    65,    66,    67,    68,    69,    70,    71,    72,  -467,
    -467,  -467,     0,     0,     0,     0,    73,    74,    75,     0,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    56,     0,  -467,    57,     0,     0,
      58,    59,    60,    90,     0,  -467,     0,     0,    91,  -467,
       0,    61,  -467,  -467,  -467,  -467,  -467,  -467,  -467,  -467,
    -467,  -467,  -467,  -467,  -467,  -467,  -467,  -467,  -467,  -467,
       0,     0,     0,    62,    63,     0,     0,   680,     0,  -467,
    -467,  -467,  -467,  -467,     0,     0,    64,     0,     0,     0,
      65,    66,    67,    68,    69,    70,    71,    72,  -467,  -467,
    -467,     0,     0,     0,     0,    73,    74,    75,     0,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    56,     0,  -467,    57,     0,     0,    58,
      59,    60,    90,     0,  -467,     0,     0,    91,  -467,     0,
      61,  -467,  -467,  -467,  -467,  -467,  -467,  -467,  -467,  -467,
    -467,  -467,  -467,  -467,  -467,  -467,  -467,  -467,  -467,     0,
       0,     0,    62,    63,     0,     0,     0,     0,  -467,  -467,
    -467,  -467,  -467,     0,     0,    64,     0,   770,     0,    65,
      66,    67,    68,    69,    70,    71,    72,  -467,  -467,  -467,
       0,     0,     0,     0,    73,    74,    75,     0,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,     7,     0,     8,     0,     0,     0,     0,     0,
       0,    90,     0,  -467,     0,     0,    91,  -467,     0,     0,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,     0,     0,
       0,     0,     0,     0,     0,     0,    27,    28,    29,    30,
      31,    32,    51,     0,     8,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    33,    34,    35,     0,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,     0,     0,
       0,     0,     0,     0,     0,     0,    27,    28,    29,    30,
      31,    32,    36,     0,     0,    37,    38,     0,     0,     0,
       0,     0,   177,     0,   178,     0,    33,    34,    35,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,     0,     0,
       0,     0,    36,     0,     0,    37,    38,    28,    29,    30,
      31,    32,     0,     8,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    33,    34,    35,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    28,    29,    30,    31,
      32,     0,    36,     8,     0,     0,    38,     0,     0,     0,
       0,     0,     0,     0,     0,   220,    34,    35,     0,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    28,    29,    30,    31,
      32,    36,     8,     0,     0,    38,   726,     0,     0,     0,
       0,     0,     0,     0,     0,    33,    34,    35,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,     0,     0,     0,     0,
       0,     0,     0,     0,    27,    28,    29,    30,    31,    32,
       0,    36,     8,     0,     0,    38,   726,     0,     0,     0,
       0,     0,     0,     0,    33,    34,    35,     0,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,   203,     0,     0,     0,
       0,     0,     0,     0,     0,    28,    29,    30,    31,    32,
      36,     8,     0,    37,    38,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    33,    34,    35,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    28,    29,    30,    31,    32,     0,
      36,     8,     0,     0,    38,     0,     0,     0,     0,     0,
       0,     0,     0,   220,    34,    35,     0,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    28,    29,    30,    31,    32,    36,
     682,     0,     0,    38,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    33,    34,    35,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    28,    29,    30,    31,    32,     0,    36,
       8,     0,     0,    38,     0,     0,     0,     0,     0,     0,
       0,     0,    33,    34,    35,     0,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    31,    32,    36,     0,
       0,     0,    38,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    33,    34,    35,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    36,     0,
       0,     0,    38
};

static const yytype_int16 yycheck[] =
{
       0,    85,     5,     5,    40,     5,   320,    41,     8,    43,
       5,   212,   131,   549,   563,     5,   327,     5,   304,   465,
      42,    21,    37,    90,   137,   146,     6,   437,     5,     5,
     142,    39,   197,     5,   155,     5,   446,   446,   155,    40,
       5,     5,    42,     5,     3,     3,     1,     2,   161,   162,
     215,    38,     3,    38,   151,     5,   153,   171,    91,     5,
       5,   175,    43,    38,    64,   558,   110,   181,     5,    69,
      70,     5,   186,   566,    54,     5,   257,     5,    37,   260,
       3,     5,    39,    91,     6,    43,     5,     3,     3,    90,
       3,    38,    39,   205,   208,     5,   129,   590,   634,    54,
     115,   218,   102,   217,   597,   138,   140,   122,     3,    90,
       4,   253,    71,   147,     3,   102,     3,     0,   564,     3,
     142,   435,     1,    40,    37,   147,    43,   102,    43,    51,
     115,   131,     6,    39,    91,   179,   257,     6,    44,   260,
     454,    54,   101,   101,   256,   456,   105,   105,   290,    43,
      37,   151,    39,   153,   105,    51,   115,   269,    37,    51,
      45,   205,   283,   122,    51,   124,   283,    54,   168,    43,
     287,   352,   353,    90,    43,    71,   131,   221,   178,     3,
      51,   717,   105,   205,    71,   678,   101,   142,   101,   105,
     105,   191,   105,   215,     3,    79,    40,     3,    90,   735,
       4,   126,   751,   103,    91,   205,   101,   207,   208,   306,
     105,   124,   212,    37,   101,     3,   105,   101,   105,    90,
     220,   105,   244,     1,     2,   671,   126,   122,   115,   410,
      54,     3,   187,   188,   256,   122,     6,   124,    40,    43,
      54,   358,   242,   360,   244,    38,    39,   269,   203,   333,
     786,    90,    69,   275,    51,    43,   211,   212,   377,     3,
     753,    40,     6,   673,   673,    37,   467,    40,   365,    71,
      40,   436,   106,     3,    71,   589,     6,   101,    75,   400,
     401,   105,    54,   305,     3,   102,   407,    46,    47,    48,
     471,   115,   101,   414,    38,   101,   105,   414,   463,   105,
     124,   256,     3,    38,    39,     6,   306,   428,     4,   755,
       6,   428,   429,   101,   269,     3,   103,   105,   811,   855,
     320,    37,    38,   278,     6,    37,   281,    40,     3,   101,
      43,   365,   446,   105,   356,    37,    37,   292,    54,   126,
      37,    45,   364,   115,     3,   345,   368,    43,    37,    37,
     122,   351,   124,   131,   102,     4,   473,     6,    71,   476,
      37,   361,    37,   122,   857,   365,   399,   367,   861,    39,
      37,   101,     3,   187,   188,   105,    51,    54,    37,    54,
       3,    51,   101,     6,     3,   115,   105,   484,     4,   203,
       6,    40,   122,    37,    43,    54,    71,   211,   519,   776,
     101,   445,    51,    37,   105,   449,   783,    90,   525,   364,
      54,    39,   789,   101,   115,    43,   533,   105,    37,   102,
     103,   122,   377,   124,    37,   711,   101,   115,   472,    37,
     105,    37,    38,   433,   212,   435,   124,    68,    69,    70,
     115,    54,   101,   126,    37,    38,   105,   122,    54,   124,
     453,   453,   455,   453,   454,   455,   115,    37,   453,   493,
     460,    54,   417,   453,   278,   453,    37,   281,    37,    40,
     101,   493,    43,   495,   105,   592,   453,   453,   478,    37,
      37,   453,   101,   453,   484,   485,   105,    40,   453,   453,
      43,   453,    37,   448,   871,   495,   496,    54,    51,   612,
     665,   666,    37,   453,   879,   124,    43,   453,   453,   464,
      49,    50,   467,     4,   292,     6,   453,   892,   893,   453,
     564,     3,    38,   453,   558,   453,    39,    66,    67,   453,
      37,    38,   566,     3,   453,    37,    38,    40,   541,   541,
      43,   541,     4,   453,     6,    40,   541,    54,    43,   549,
     364,   541,    54,   541,    40,   599,   590,    43,   558,   656,
     762,   675,   764,   597,   541,   541,   566,   570,   570,   541,
     570,   541,    40,   692,     3,   570,   541,   541,    40,   541,
     570,    43,   570,    40,   587,   587,    43,   587,   588,   589,
     590,   541,   587,   570,   570,   541,   541,   597,   570,   377,
     570,   685,    40,   417,   541,   570,   570,   541,   570,   722,
     643,   541,   898,   541,   650,   649,    43,   541,   715,     3,
     570,   576,   541,     3,   570,   570,    43,   649,   650,     6,
     674,   541,    40,   570,   634,    39,   570,   102,   100,   683,
     570,    65,   570,   598,   678,   645,   570,    37,    91,    49,
      50,   570,    39,    38,     3,     4,   656,     6,    37,    91,
     570,    85,    86,   102,    38,   709,    66,    67,    54,   702,
     448,    46,    47,    48,   122,    40,    51,   102,   678,    38,
     724,   715,   682,   727,    38,   782,   464,    38,    37,   467,
      90,    40,   692,    43,    43,    38,    71,   107,   108,   109,
      75,   704,   704,    51,   704,   129,    39,    38,   708,   704,
     754,    38,   712,   668,   704,   715,   704,   717,     3,   753,
      46,    47,    48,     3,    40,   769,    38,   704,   704,    39,
      40,   828,   704,    43,   704,   735,    38,   692,    38,   704,
     704,    38,   704,    38,    38,     3,    91,    39,    18,    75,
     102,   100,   101,   753,   704,   710,   105,    37,   704,   704,
      38,   716,   576,    46,    47,    48,   115,   704,   790,   791,
     704,    41,    33,   122,   704,   124,   704,   811,    40,    37,
     704,    42,   782,   102,   598,   704,   786,    48,    43,    63,
      38,   102,   747,   793,   704,   839,    54,   797,   102,   843,
      38,   801,    72,    73,    74,    40,    40,    77,    38,    40,
      84,   811,   120,   121,   122,    89,   101,    78,    79,   863,
     105,   101,    43,   857,    37,   105,    44,   861,   828,    40,
     115,    38,     3,   788,   104,   115,   791,   122,    37,   839,
     840,    43,   876,   101,   124,   879,    38,   105,    39,   110,
      39,    37,   807,    51,   668,   855,    38,   857,   892,   893,
      37,   861,   126,   863,    90,    44,   124,    51,    37,    46,
      47,    48,   124,    43,    51,   830,   876,     3,   833,   879,
      44,   142,     3,    18,    71,   146,    71,   148,    71,    44,
      38,    38,   892,   893,   155,    73,   710,   171,    75,    44,
     174,   175,   716,   327,   859,   860,    41,   181,    37,   333,
      75,    37,   186,    38,   692,     3,    37,    40,   179,    40,
      38,   182,    71,   197,    40,    38,    37,    39,   189,     3,
      40,     3,    38,   747,   208,   209,     3,    72,    73,    74,
     214,   215,    77,   217,   205,   369,   118,   119,   120,   121,
     122,     3,   213,    37,   215,   216,    39,   218,    40,   220,
     221,   222,    40,    37,    91,    37,    40,    38,    38,    37,
      37,    40,    37,     3,   788,   101,    40,   791,    44,   105,
     101,     3,    54,   244,   105,    37,     3,    38,    40,   115,
      40,    40,    39,   807,   115,   256,   257,    38,   124,   260,
      44,   122,    37,   124,    37,   460,     3,    37,   269,   270,
      38,    38,   587,    38,    40,    37,   830,     3,    40,   833,
      37,    40,   283,    38,    54,    38,   287,   101,    38,   101,
       3,   105,   456,   105,   101,     3,    40,    40,   105,    40,
      37,   115,   437,   115,   305,   859,   860,   715,   122,   101,
     124,    37,   124,   105,   587,   467,   588,   124,   319,   587,
     587,   433,   863,   115,    37,   692,   496,   495,   377,    37,
     122,   101,   124,   708,    46,   105,   840,   797,   801,   101,
     861,    54,    21,   105,   101,   115,   852,    -1,   105,   573,
      -1,   352,   353,   115,   124,   356,    -1,   358,   115,   360,
     122,    -1,   124,   364,   101,   122,    -1,   124,   105,    -1,
     144,   145,    -1,    -1,    -1,   101,    -1,    -1,   115,   105,
      -1,    -1,    -1,    -1,    -1,   122,    -1,   124,   101,   115,
      -1,    -1,   105,   101,    -1,    -1,   122,   105,   124,    -1,
     401,    -1,   115,    -1,    -1,    -1,    -1,   115,   572,   410,
      -1,   124,    -1,   414,   122,    -1,   124,    -1,    -1,    -1,
     434,    -1,   436,   437,    -1,    -1,    -1,   428,   429,    -1,
     444,   445,   446,   116,   117,   118,   119,   120,   121,   122,
      -1,    -1,    -1,    -1,   445,    -1,    -1,    -1,   449,   463,
      -1,   465,    -1,    -1,    -1,    -1,    -1,   231,   472,   233,
     234,   235,   236,   237,   238,    -1,    -1,    -1,    -1,    -1,
     471,   472,   473,    -1,    -1,   476,    94,    95,     6,   643,
      -1,    -1,    -1,    11,    12,    13,    14,    15,    16,    17,
     264,    -1,    -1,    -1,   495,    38,    -1,    -1,   116,   117,
     118,   119,   120,   121,   122,   279,    -1,    -1,   282,    -1,
      -1,    -1,    -1,   514,    -1,    -1,    -1,    94,    95,    96,
      97,   685,    -1,    -1,   525,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   533,    -1,    -1,    -1,    -1,    -1,   702,   116,
     117,   118,   119,   120,   121,   122,    -1,    -1,    -1,    -1,
     564,    94,    95,    96,    97,    98,    -1,   571,    -1,   573,
      -1,    -1,   726,   564,    -1,    -1,    -1,    -1,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   592,    -1,    -1,    -1,    -1,    -1,    -1,   599,    -1,
      -1,    -1,    -1,    94,    95,    96,    97,   381,   382,   383,
     384,   385,   386,   387,   388,   389,   390,   391,   392,   393,
     394,   395,   396,   397,   115,   116,   117,   118,   119,   120,
     121,   122,    -1,    -1,    -1,    -1,    -1,   411,    -1,    -1,
      -1,    -1,   643,    -1,   418,    -1,    -1,    -1,    -1,    -1,
      -1,   665,   666,    -1,    -1,    -1,    -1,   671,    -1,   673,
      -1,   675,    -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,
       6,    -1,    -1,   674,    10,    11,    12,    13,    14,    15,
      16,    17,   683,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    -1,    -1,    -1,    -1,    -1,   709,    -1,
      46,    47,    48,    49,    50,    -1,    52,   491,   492,   493,
      -1,    -1,    -1,   724,    -1,    -1,   727,   728,    -1,    65,
      66,    67,   733,    -1,    -1,    -1,    94,    95,    96,    97,
      -1,   755,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   754,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   101,    -1,    -1,   769,   105,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   779,   115,
      -1,    -1,   118,   119,    -1,     3,   122,   123,   124,    -1,
     791,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,
      48,    49,    50,    94,    95,    96,    97,    -1,   839,    -1,
      -1,   842,   843,    94,    95,    96,    97,    65,    66,    67,
      -1,   852,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   863,   114,   115,   116,   117,   118,   119,   120,
     121,   122,    -1,    -1,   648,   649,    -1,   651,    -1,    -1,
      -1,   655,     1,   101,     3,     4,   104,   105,     7,     8,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    40,    -1,
      -1,    40,    41,    -1,    -1,    44,    -1,    46,    47,    48,
      49,    50,    -1,   707,    -1,    -1,    -1,    -1,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    -1,    72,    73,    74,    -1,    76,    77,    78,
      -1,    -1,    -1,    82,   738,    84,    85,    86,    87,    88,
      89,    -1,    94,    95,    96,    97,    98,    -1,    -1,    -1,
      99,    -1,   101,    -1,    -1,   104,   105,   106,    -1,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,    -1,    -1,     3,    -1,   124,     6,    -1,    -1,    -1,
      10,    11,    12,    13,    14,    15,    16,    17,   792,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,
      50,    -1,    52,    94,    95,    96,    97,    98,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    66,    67,    -1,    -1,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,    19,    20,    21,    22,    23,    24,    25,    26,
      -1,    28,    -1,    30,    -1,    -1,    33,    34,    35,    36,
      -1,   101,    -1,    -1,   104,   105,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   115,    -1,    -1,   118,   119,
      -1,    -1,   122,   123,   124,     3,    -1,    -1,     6,    -1,
      -1,    -1,    10,    11,    12,    13,    14,    15,    16,    17,
      55,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    47,
      48,    49,    50,    -1,    52,    -1,    -1,    55,    -1,    94,
      95,    96,    97,    98,    -1,    -1,    -1,    65,    66,    67,
      -1,    94,    95,    96,    97,    -1,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
      -1,     3,    -1,   101,     6,    -1,    -1,   105,    -1,    11,
      12,    13,    14,    15,    16,    17,    -1,   115,    -1,    -1,
     118,   119,    -1,    -1,   122,   123,   124,     3,    -1,    -1,
       6,    -1,    -1,    -1,    10,    11,    12,    13,    14,    15,
      16,    17,    55,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    47,    48,    49,    50,    -1,    52,    -1,    -1,    55,
      -1,    94,    95,    96,    97,    98,    -1,    -1,    -1,    65,
      66,    67,    -1,    -1,    -1,    -1,    -1,    -1,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,   105,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   115,
      -1,    -1,   118,   119,    -1,    -1,   122,   123,   124,     3,
      -1,    -1,     6,    -1,    -1,    -1,    10,    11,    12,    13,
      14,    15,    16,    17,    55,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    46,    47,    48,    49,    50,    -1,    52,    -1,
      -1,    55,    -1,    94,    95,    96,    97,    98,    -1,    -1,
      -1,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,
      -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   115,    -1,    -1,   118,   119,    -1,    -1,   122,   123,
     124,     3,    -1,    -1,     6,    -1,    -1,    -1,    10,    11,
      12,    13,    14,    15,    16,    17,    55,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    47,    48,    49,    50,    -1,
      52,    -1,    -1,    55,    -1,    94,    95,    96,    97,    98,
      -1,    -1,    -1,    65,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,
      -1,    -1,    -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   115,    -1,    -1,   118,   119,    -1,    -1,
     122,   123,   124,     3,    -1,    -1,     6,    -1,    -1,    -1,
      10,    11,    12,    13,    14,    15,    16,    17,    55,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    46,    47,    48,    49,
      50,    -1,    52,    -1,    -1,    -1,    -1,    94,    95,    96,
      97,    98,    -1,    -1,    -1,    65,    66,    67,    -1,    -1,
      -1,    -1,    -1,    -1,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   101,    -1,    -1,    -1,   105,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   115,    -1,    -1,   118,   119,
      -1,    -1,   122,   123,   124,     3,    -1,    -1,     6,    -1,
      -1,    -1,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    47,
      48,    49,    50,    -1,    52,     3,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,
      48,    49,    50,   101,    -1,    -1,    54,   105,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,
     118,   119,    -1,    -1,   122,   123,   124,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,    -1,    -1,   104,   105,    -1,     3,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   115,    -1,    -1,
      -1,    -1,    -1,    -1,   122,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    46,    47,    48,    49,    50,    -1,    -1,    -1,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    -1,   101,    -1,    -1,
     104,   105,    45,    46,    47,    48,    49,    50,    -1,    -1,
      -1,   115,    -1,     3,    -1,    -1,    -1,    -1,   122,    -1,
      -1,    -1,    65,    66,    67,    -1,    -1,    -1,    -1,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,   101,    49,
      50,   104,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   115,    -1,    -1,    65,    66,    67,    -1,   122,
      94,    95,    96,    97,    98,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,    -1,
      -1,   101,    -1,    -1,    -1,   105,     0,     1,    -1,     3,
       4,    -1,    -1,     7,     8,     9,    -1,    -1,    -1,    -1,
      -1,    -1,   122,    -1,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    -1,    40,    41,    -1,    -1,
      -1,    -1,    46,    47,    48,    49,    50,    -1,    -1,    53,
      -1,    -1,    -1,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    -1,    -1,    -1,    -1,    72,    73,
      74,    -1,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,     1,    -1,     3,     4,
      -1,    -1,     7,     8,     9,    99,    -1,   101,    -1,    -1,
     104,   105,    -1,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    -1,    40,    41,    -1,    -1,    44,
      -1,    46,    47,    48,    49,    50,    -1,    -1,    53,    -1,
      -1,    -1,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    -1,    -1,    -1,    -1,    72,    73,    74,
      -1,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,     1,    -1,     3,     4,    -1,
      -1,     7,     8,     9,    99,    -1,   101,    -1,    -1,   104,
     105,    -1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    -1,    40,    41,    -1,    -1,    44,    -1,
      46,    47,    48,    49,    50,    -1,    -1,    53,    -1,    -1,
      -1,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    -1,    -1,    -1,    -1,    72,    73,    74,    -1,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,     1,    -1,     3,     4,    -1,    -1,
       7,     8,     9,    99,    -1,   101,    -1,    -1,   104,   105,
      -1,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    -1,    40,    41,    -1,    -1,    44,    -1,    46,
      47,    48,    49,    50,    -1,    -1,    53,    -1,    -1,    -1,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    -1,    -1,    -1,    -1,    72,    73,    74,    -1,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,     1,    -1,     3,     4,    -1,    -1,     7,
       8,     9,    99,    -1,   101,    -1,    -1,   104,   105,    -1,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    -1,    40,    41,    -1,    -1,    -1,    -1,    46,    47,
      48,    49,    50,    -1,    -1,    53,    -1,    55,    -1,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      -1,    -1,    -1,    -1,    72,    73,    74,    -1,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,     1,    -1,     3,    -1,    -1,    -1,    -1,    -1,
      -1,    99,    -1,   101,    -1,    -1,   104,   105,    -1,    -1,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,
      49,    50,     1,    -1,     3,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    -1,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,
      49,    50,   101,    -1,    -1,   104,   105,    -1,    -1,    -1,
      -1,    -1,     1,    -1,     3,    -1,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      -1,    -1,   101,    -1,    -1,   104,   105,    46,    47,    48,
      49,    50,    -1,     3,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    46,    47,    48,    49,
      50,    -1,   101,     3,    -1,    -1,   105,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    66,    67,    -1,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    46,    47,    48,    49,
      50,   101,     3,    -1,    -1,   105,   106,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    66,    67,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50,
      -1,   101,     3,    -1,    -1,   105,   106,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    67,    -1,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    47,    48,    49,    50,
     101,     3,    -1,   104,   105,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    67,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    47,    48,    49,    50,    -1,
     101,     3,    -1,    -1,   105,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    -1,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    47,    48,    49,    50,   101,
       3,    -1,    -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    47,    48,    49,    50,    -1,   101,
       3,    -1,    -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    66,    67,    -1,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    49,    50,   101,    -1,
      -1,    -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,
      -1,    -1,   105
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   107,   108,   109,   128,   129,   274,     1,     3,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    45,    46,    47,
      48,    49,    50,    65,    66,    67,   101,   104,   105,   215,
     229,   230,   232,   233,   234,   235,   236,   253,   254,   264,
     266,     1,   215,     1,    37,     0,     1,     4,     7,     8,
       9,    18,    40,    41,    53,    57,    58,    59,    60,    61,
      62,    63,    64,    72,    73,    74,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      99,   104,   130,   131,   132,   134,   135,   136,   137,   138,
     141,   142,   144,   145,   146,   147,   148,   149,   150,   153,
     154,   155,   158,   160,   165,   166,   167,   168,   170,   173,
     174,   175,   176,   177,   181,   182,   189,   190,   200,   211,
     274,    90,   261,   274,   261,    45,   264,   126,    90,    40,
     233,   229,    37,    51,    54,    71,   115,   122,   124,   220,
     221,   223,   225,   226,   227,   228,   264,   274,   229,   235,
     264,   103,   126,   265,    40,    40,   212,   213,   215,   274,
     106,    37,     6,   269,    37,   271,   274,     1,     3,   231,
     232,    37,   271,    37,   152,   274,    37,    37,    37,    79,
     264,     3,    43,   264,    37,     4,    43,    37,    37,    40,
      43,     4,   269,    37,   164,   231,   162,   164,    37,    37,
     269,    37,    90,   254,   271,    37,   115,   223,   228,   264,
      65,   231,   254,    10,    11,    12,    13,    14,    15,    16,
      17,    37,    52,   115,   118,   119,   122,   123,   124,   215,
     216,   217,   219,   231,   232,   243,   244,   245,   246,   269,
     274,    45,   105,   266,   254,   229,    37,   115,   212,   226,
     228,   264,    43,   237,   238,    55,   243,   244,   243,    37,
     124,   224,   227,   264,   228,   229,   264,   220,    37,    54,
     220,    37,    54,   115,   224,   227,   264,   102,   266,   105,
     266,    38,    39,   214,   274,     3,   262,   269,     6,    43,
     262,   272,   262,    40,    51,    37,   223,    38,   262,   264,
       3,     3,   262,    11,   159,   212,   212,   264,    40,    51,
     192,    43,     3,   161,   272,     3,   212,    43,   222,   223,
     226,   274,    40,    39,   163,   274,   262,   263,   274,   139,
     140,   269,   212,   185,   186,   187,   215,   253,   274,   264,
     269,     3,   115,   228,   264,   272,    37,   262,   115,   264,
     102,     3,   239,   274,    37,   223,    43,   264,   243,    37,
     243,   243,   243,   243,   243,   243,    91,    39,   218,   274,
      37,    94,    95,    96,    97,    98,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   265,    91,
     115,   228,   264,   225,   264,    38,    38,   115,   225,   264,
     102,    54,   243,    55,   228,   264,   264,    37,    54,   228,
     212,    55,   243,   212,    55,   243,   224,   227,   102,   115,
     224,   265,    40,   215,    38,   169,    39,    51,    38,   237,
     220,    38,    43,    38,    51,    38,    39,   157,    39,    38,
      38,    40,   264,   129,   191,    38,    38,    38,    38,   162,
     164,    38,    38,    39,    43,    38,    91,    39,   188,   274,
      54,   102,    38,   228,   264,    40,   102,    40,    43,   212,
     264,    75,   172,   220,   229,   179,    40,    71,   247,   248,
     274,    38,   115,   122,   228,   231,   219,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   254,   264,   102,    38,    38,   102,
     225,   243,   224,   264,    38,   102,   212,    55,   243,    38,
      55,    38,    55,   115,   224,   227,   224,   214,     4,    43,
     269,   129,   272,   139,   245,   269,   273,    40,    40,   133,
       4,   151,   269,     4,    40,    43,   100,   156,   223,   269,
     270,   262,   269,   273,    38,   215,   223,    43,    40,    44,
     129,    41,   211,   162,    40,    43,    37,    44,   163,     3,
     101,   105,   267,    40,   272,   215,   156,   183,   187,   143,
     223,   269,   102,     3,   240,   241,   274,    38,    37,    39,
      40,    43,   171,    75,   220,     1,    40,    61,    68,    69,
      70,    73,   124,   134,   135,   136,   137,   141,   142,   146,
     148,   150,   153,   155,   158,   160,   165,   166,   167,   168,
     181,   182,   189,   193,   196,   197,   198,   199,   200,   201,
     202,   207,   210,   211,   274,   249,    43,   243,    38,   122,
     229,    38,   115,   221,   218,    71,   264,    38,    55,    38,
     224,    38,    55,   224,    44,    39,    39,   193,    37,    75,
     229,   256,   274,    51,    38,    39,   157,   156,   223,   256,
      44,   269,     3,   231,    40,    51,   270,   212,   103,   126,
     268,   126,    90,    38,    44,   170,   177,   181,   182,   184,
     197,   199,   211,   188,   129,   256,    40,    51,    39,    44,
      37,    51,   256,   257,   212,   223,    37,   195,    43,    71,
      71,    71,   124,   266,    44,   193,   106,   231,   254,   264,
      73,   250,   251,   255,   274,   178,   243,   243,    38,    38,
     243,   220,    38,   272,   272,    44,   212,    37,    75,   156,
     269,   273,    40,   223,    38,   256,    40,    40,   223,   164,
      38,     3,     3,   105,     3,   105,   216,     4,    43,   231,
      55,    40,   242,   243,   241,    40,   223,   212,   237,    71,
     258,   274,    38,   172,   212,   193,   194,   266,    37,   223,
     231,    37,    71,     3,    43,   264,    40,    39,    68,    69,
      70,   252,   264,   193,   243,    38,   212,    37,   157,   256,
      40,   223,   156,    40,    40,   268,   268,    91,   171,    38,
      40,   259,   260,   264,    40,    43,   220,   171,    38,   193,
      37,   212,   171,    37,   115,   228,   212,   243,    43,   204,
      71,   251,   255,    44,    40,    38,   212,    40,   256,    40,
      40,    43,    39,    37,   220,    44,   212,    38,   212,    37,
      37,    38,    40,   203,   206,   223,   274,   250,   264,    40,
     180,   223,    38,    40,   260,   193,    38,   208,   256,    38,
     212,   212,   257,   206,    40,    43,   171,   209,   256,    40,
      43,   209,    38,    38,    40,   205,    40,    43,    51,   209,
     209,    40,   237,    40
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 1526 "parser.y"
    {
                   if (!classes) classes = NewHash();
		   Setattr((yyvsp[(1) - (1)].node),"classes",classes); 
		   Setattr((yyvsp[(1) - (1)].node),"name",ModuleName);
		   
		   if ((!module_node) && ModuleName) {
		     module_node = new_node("module");
		     Setattr(module_node,"name",ModuleName);
		   }
		   Setattr((yyvsp[(1) - (1)].node),"module",module_node);
		   check_extensions();
	           top = (yyvsp[(1) - (1)].node);
               }
    break;

  case 3:
#line 1539 "parser.y"
    {
                 top = Copy(Getattr((yyvsp[(2) - (3)].p),"type"));
		 Delete((yyvsp[(2) - (3)].p));
               }
    break;

  case 4:
#line 1543 "parser.y"
    {
                 top = 0;
               }
    break;

  case 5:
#line 1546 "parser.y"
    {
                 top = (yyvsp[(2) - (3)].p);
               }
    break;

  case 6:
#line 1549 "parser.y"
    {
                 top = 0;
               }
    break;

  case 7:
#line 1552 "parser.y"
    {
                 top = (yyvsp[(3) - (5)].pl);
               }
    break;

  case 8:
#line 1555 "parser.y"
    {
                 top = 0;
               }
    break;

  case 9:
#line 1560 "parser.y"
    {  
                   /* add declaration to end of linked list (the declaration isn't always a single declaration, sometimes it is a linked list itself) */
                   appendChild((yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node));
                   (yyval.node) = (yyvsp[(1) - (2)].node);
               }
    break;

  case 10:
#line 1565 "parser.y"
    {
                   (yyval.node) = new_node("top");
               }
    break;

  case 11:
#line 1570 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 12:
#line 1571 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 13:
#line 1572 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 14:
#line 1573 "parser.y"
    { (yyval.node) = 0; }
    break;

  case 15:
#line 1574 "parser.y"
    {
                  (yyval.node) = 0;
		  Swig_error(cparse_file, cparse_line,"Syntax error in input(1).\n");
		  exit(1);
               }
    break;

  case 16:
#line 1580 "parser.y"
    { 
                  if ((yyval.node)) {
   		      add_symbols((yyval.node));
                  }
                  (yyval.node) = (yyvsp[(1) - (1)].node); 
	       }
    break;

  case 17:
#line 1596 "parser.y"
    {
                  (yyval.node) = 0;
                  skip_decl();
               }
    break;

  case 18:
#line 1606 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 19:
#line 1607 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 20:
#line 1608 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 21:
#line 1609 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 22:
#line 1610 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 23:
#line 1611 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 24:
#line 1612 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 25:
#line 1613 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 26:
#line 1614 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 27:
#line 1615 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 28:
#line 1616 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 29:
#line 1617 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 30:
#line 1618 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 31:
#line 1619 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 32:
#line 1620 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 33:
#line 1621 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 34:
#line 1622 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 35:
#line 1623 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 36:
#line 1624 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 37:
#line 1625 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 38:
#line 1626 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 39:
#line 1633 "parser.y"
    {
               Node *cls;
	       String *clsname;
	       cplus_mode = CPLUS_PUBLIC;
	       if (!classes) classes = NewHash();
	       if (!extendhash) extendhash = NewHash();
	       clsname = make_class_name((yyvsp[(3) - (4)].str));
	       cls = Getattr(classes,clsname);
	       if (!cls) {
		 /* No previous definition. Create a new scope */
		 Node *am = Getattr(extendhash,clsname);
		 if (!am) {
		   Swig_symbol_newscope();
		   Swig_symbol_setscopename((yyvsp[(3) - (4)].str));
		   prev_symtab = 0;
		 } else {
		   prev_symtab = Swig_symbol_setscope(Getattr(am,"symtab"));
		 }
		 current_class = 0;
	       } else {
		 /* Previous class definition.  Use its symbol table */
		 prev_symtab = Swig_symbol_setscope(Getattr(cls,"symtab"));
		 current_class = cls;
		 extendmode = 1;
	       }
	       Classprefix = NewString((yyvsp[(3) - (4)].str));
	       Namespaceprefix= Swig_symbol_qualifiedscopename(0);
	       Delete(clsname);
	     }
    break;

  case 40:
#line 1661 "parser.y"
    {
               String *clsname;
	       extendmode = 0;
               (yyval.node) = new_node("extend");
	       Setattr((yyval.node),"symtab",Swig_symbol_popscope());
	       if (prev_symtab) {
		 Swig_symbol_setscope(prev_symtab);
	       }
	       Namespaceprefix = Swig_symbol_qualifiedscopename(0);
               clsname = make_class_name((yyvsp[(3) - (7)].str));
	       Setattr((yyval.node),"name",clsname);

	       /* Mark members as extend */

	       tag_nodes((yyvsp[(6) - (7)].node),"feature:extend",(char*) "1");
	       if (current_class) {
		 /* We add the extension to the previously defined class */
		 appendChild((yyval.node),(yyvsp[(6) - (7)].node));
		 appendChild(current_class,(yyval.node));
	       } else {
		 /* We store the extensions in the extensions hash */
		 Node *am = Getattr(extendhash,clsname);
		 if (am) {
		   /* Append the members to the previous extend methods */
		   appendChild(am,(yyvsp[(6) - (7)].node));
		 } else {
		   appendChild((yyval.node),(yyvsp[(6) - (7)].node));
		   Setattr(extendhash,clsname,(yyval.node));
		 }
	       }
	       current_class = 0;
	       Delete(Classprefix);
	       Delete(clsname);
	       Classprefix = 0;
	       prev_symtab = 0;
	       (yyval.node) = 0;

	     }
    break;

  case 41:
#line 1705 "parser.y"
    {
                    (yyval.node) = new_node("apply");
                    Setattr((yyval.node),"pattern",Getattr((yyvsp[(2) - (5)].p),"pattern"));
		    appendChild((yyval.node),(yyvsp[(4) - (5)].p));
               }
    break;

  case 42:
#line 1715 "parser.y"
    {
		 (yyval.node) = new_node("clear");
		 appendChild((yyval.node),(yyvsp[(2) - (3)].p));
               }
    break;

  case 43:
#line 1726 "parser.y"
    {
		   if (((yyvsp[(4) - (5)].dtype).type != T_ERROR) && ((yyvsp[(4) - (5)].dtype).type != T_SYMBOL)) {
		     SwigType *type = NewSwigType((yyvsp[(4) - (5)].dtype).type);
		     (yyval.node) = new_node("constant");
		     Setattr((yyval.node),"name",(yyvsp[(2) - (5)].id));
		     Setattr((yyval.node),"type",type);
		     Setattr((yyval.node),"value",(yyvsp[(4) - (5)].dtype).val);
		     if ((yyvsp[(4) - (5)].dtype).rawval) Setattr((yyval.node),"rawval", (yyvsp[(4) - (5)].dtype).rawval);
		     Setattr((yyval.node),"storage","%constant");
		     SetFlag((yyval.node),"feature:immutable");
		     add_symbols((yyval.node));
		     Delete(type);
		   } else {
		     if ((yyvsp[(4) - (5)].dtype).type == T_ERROR) {
		       Swig_warning(WARN_PARSE_UNSUPPORTED_VALUE,cparse_file,cparse_line,"Unsupported constant value (ignored)\n");
		     }
		     (yyval.node) = 0;
		   }

	       }
    break;

  case 44:
#line 1747 "parser.y"
    {
		 if (((yyvsp[(4) - (5)].dtype).type != T_ERROR) && ((yyvsp[(4) - (5)].dtype).type != T_SYMBOL)) {
		   SwigType_push((yyvsp[(2) - (5)].type),(yyvsp[(3) - (5)].decl).type);
		   /* Sneaky callback function trick */
		   if (SwigType_isfunction((yyvsp[(2) - (5)].type))) {
		     SwigType_add_pointer((yyvsp[(2) - (5)].type));
		   }
		   (yyval.node) = new_node("constant");
		   Setattr((yyval.node),"name",(yyvsp[(3) - (5)].decl).id);
		   Setattr((yyval.node),"type",(yyvsp[(2) - (5)].type));
		   Setattr((yyval.node),"value",(yyvsp[(4) - (5)].dtype).val);
		   if ((yyvsp[(4) - (5)].dtype).rawval) Setattr((yyval.node),"rawval", (yyvsp[(4) - (5)].dtype).rawval);
		   Setattr((yyval.node),"storage","%constant");
		   SetFlag((yyval.node),"feature:immutable");
		   add_symbols((yyval.node));
		 } else {
		     if ((yyvsp[(4) - (5)].dtype).type == T_ERROR) {
		       Swig_warning(WARN_PARSE_UNSUPPORTED_VALUE,cparse_file,cparse_line,"Unsupported constant value\n");
		     }
		   (yyval.node) = 0;
		 }
               }
    break;

  case 45:
#line 1769 "parser.y"
    {
		 Swig_warning(WARN_PARSE_BAD_VALUE,cparse_file,cparse_line,"Bad constant value (ignored).\n");
		 (yyval.node) = 0;
	       }
    break;

  case 46:
#line 1780 "parser.y"
    {
		 char temp[64];
		 Replace((yyvsp[(2) - (2)].str),"$file",cparse_file, DOH_REPLACE_ANY);
		 sprintf(temp,"%d", cparse_line);
		 Replace((yyvsp[(2) - (2)].str),"$line",temp,DOH_REPLACE_ANY);
		 Printf(stderr,"%s\n", (yyvsp[(2) - (2)].str));
		 Delete((yyvsp[(2) - (2)].str));
                 (yyval.node) = 0;
	       }
    break;

  case 47:
#line 1789 "parser.y"
    {
		 char temp[64];
		 String *s = NewString((yyvsp[(2) - (2)].id));
		 Replace(s,"$file",cparse_file, DOH_REPLACE_ANY);
		 sprintf(temp,"%d", cparse_line);
		 Replace(s,"$line",temp,DOH_REPLACE_ANY);
		 Printf(stderr,"%s\n", s);
		 Delete(s);
                 (yyval.node) = 0;
               }
    break;

  case 48:
#line 1808 "parser.y"
    {
                    skip_balanced('{','}');
		    (yyval.node) = 0;
		    Swig_warning(WARN_DEPRECATED_EXCEPT,cparse_file, cparse_line, "%%except is deprecated.  Use %%exception instead.\n");
	       }
    break;

  case 49:
#line 1814 "parser.y"
    {
                    skip_balanced('{','}');
		    (yyval.node) = 0;
		    Swig_warning(WARN_DEPRECATED_EXCEPT,cparse_file, cparse_line, "%%except is deprecated.  Use %%exception instead.\n");
               }
    break;

  case 50:
#line 1820 "parser.y"
    {
		 (yyval.node) = 0;
		 Swig_warning(WARN_DEPRECATED_EXCEPT,cparse_file, cparse_line, "%%except is deprecated.  Use %%exception instead.\n");
               }
    break;

  case 51:
#line 1825 "parser.y"
    {
		 (yyval.node) = 0;
		 Swig_warning(WARN_DEPRECATED_EXCEPT,cparse_file, cparse_line, "%%except is deprecated.  Use %%exception instead.\n");
	       }
    break;

  case 52:
#line 1832 "parser.y"
    {		 
                 (yyval.node) = NewHash();
                 Setattr((yyval.node),"value",(yyvsp[(1) - (4)].id));
		 Setattr((yyval.node),"type",Getattr((yyvsp[(3) - (4)].p),"type"));
               }
    break;

  case 53:
#line 1839 "parser.y"
    {
                 (yyval.node) = NewHash();
                 Setattr((yyval.node),"value",(yyvsp[(1) - (1)].id));
              }
    break;

  case 54:
#line 1843 "parser.y"
    {
                (yyval.node) = (yyvsp[(1) - (1)].node);
              }
    break;

  case 55:
#line 1856 "parser.y"
    {
                   Hash *p = (yyvsp[(5) - (7)].node);
		   (yyval.node) = new_node("fragment");
		   Setattr((yyval.node),"value",Getattr((yyvsp[(3) - (7)].node),"value"));
		   Setattr((yyval.node),"type",Getattr((yyvsp[(3) - (7)].node),"type"));
		   Setattr((yyval.node),"section",Getattr(p,"name"));
		   Setattr((yyval.node),"kwargs",nextSibling(p));
		   Setattr((yyval.node),"code",(yyvsp[(7) - (7)].str));
                 }
    break;

  case 56:
#line 1865 "parser.y"
    {
		   Hash *p = (yyvsp[(5) - (7)].node);
		   String *code;
                   skip_balanced('{','}');
		   (yyval.node) = new_node("fragment");
		   Setattr((yyval.node),"value",Getattr((yyvsp[(3) - (7)].node),"value"));
		   Setattr((yyval.node),"type",Getattr((yyvsp[(3) - (7)].node),"type"));
		   Setattr((yyval.node),"section",Getattr(p,"name"));
		   Setattr((yyval.node),"kwargs",nextSibling(p));
		   Delitem(scanner_ccode,0);
		   Delitem(scanner_ccode,DOH_END);
		   code = Copy(scanner_ccode);
		   Setattr((yyval.node),"code",code);
		   Delete(code);
                 }
    break;

  case 57:
#line 1880 "parser.y"
    {
		   (yyval.node) = new_node("fragment");
		   Setattr((yyval.node),"value",Getattr((yyvsp[(3) - (5)].node),"value"));
		   Setattr((yyval.node),"type",Getattr((yyvsp[(3) - (5)].node),"type"));
		   Setattr((yyval.node),"emitonly","1");
		 }
    break;

  case 58:
#line 1893 "parser.y"
    {
                     (yyvsp[(1) - (4)].loc).filename = Copy(cparse_file);
		     (yyvsp[(1) - (4)].loc).line = cparse_line;
		     scanner_set_location(NewString((yyvsp[(3) - (4)].id)),1);
               }
    break;

  case 59:
#line 1897 "parser.y"
    {
                     String *mname = 0;
                     (yyval.node) = (yyvsp[(6) - (7)].node);
		     scanner_set_location((yyvsp[(1) - (7)].loc).filename,(yyvsp[(1) - (7)].loc).line);
		     if (strcmp((yyvsp[(1) - (7)].loc).type,"include") == 0) set_nodeType((yyval.node),"include");
		     if (strcmp((yyvsp[(1) - (7)].loc).type,"import") == 0) {
		       mname = (yyvsp[(2) - (7)].node) ? Getattr((yyvsp[(2) - (7)].node),"module") : 0;
		       set_nodeType((yyval.node),"import");
		       if (import_mode) --import_mode;
		     }
		     
		     Setattr((yyval.node),"name",(yyvsp[(3) - (7)].id));
		     /* Search for the module (if any) */
		     {
			 Node *n = firstChild((yyval.node));
			 while (n) {
			     if (Strcmp(nodeType(n),"module") == 0) {
			         if (mname) {
				   Setattr(n,"name", mname);
				   mname = 0;
				 }
				 Setattr((yyval.node),"module",Getattr(n,"name"));
				 break;
			     }
			     n = nextSibling(n);
			 }
			 if (mname) {
			   /* There is no module node in the import
			      node, ie, you imported a .h file
			      directly.  We are forced then to create
			      a new import node with a module node.
			   */			      
			   Node *nint = new_node("import");
			   Node *mnode = new_node("module");
			   Setattr(mnode,"name", mname);
			   appendChild(nint,mnode);
			   Delete(mnode);
			   appendChild(nint,firstChild((yyval.node)));
			   (yyval.node) = nint;
			   Setattr((yyval.node),"module",mname);
			 }
		     }
		     Setattr((yyval.node),"options",(yyvsp[(2) - (7)].node));
               }
    break;

  case 60:
#line 1943 "parser.y"
    { (yyval.loc).type = (char *) "include"; }
    break;

  case 61:
#line 1944 "parser.y"
    { (yyval.loc).type = (char *) "import"; ++import_mode;}
    break;

  case 62:
#line 1951 "parser.y"
    {
                 String *cpps;
		 if (Namespaceprefix) {
		   Swig_error(cparse_file, cparse_start_line, "%%inline directive inside a namespace is disallowed.\n");

		   (yyval.node) = 0;
		 } else {
		   (yyval.node) = new_node("insert");
		   Setattr((yyval.node),"code",(yyvsp[(2) - (2)].str));
		   /* Need to run through the preprocessor */
		   Setline((yyvsp[(2) - (2)].str),cparse_start_line);
		   Setfile((yyvsp[(2) - (2)].str),cparse_file);
		   Seek((yyvsp[(2) - (2)].str),0,SEEK_SET);
		   cpps = Preprocessor_parse((yyvsp[(2) - (2)].str));
		   start_inline(Char(cpps), cparse_start_line);
		   Delete((yyvsp[(2) - (2)].str));
		   Delete(cpps);
		 }
		 
	       }
    break;

  case 63:
#line 1971 "parser.y"
    {
                 String *cpps;
		 int start_line = cparse_line;
		 skip_balanced('{','}');
		 if (Namespaceprefix) {
		   Swig_error(cparse_file, cparse_start_line, "%%inline directive inside a namespace is disallowed.\n");
		   
		   (yyval.node) = 0;
		 } else {
		   String *code;
                   (yyval.node) = new_node("insert");
		   Delitem(scanner_ccode,0);
		   Delitem(scanner_ccode,DOH_END);
		   code = Copy(scanner_ccode);
		   Setattr((yyval.node),"code", code);
		   Delete(code);		   
		   cpps=Copy(scanner_ccode);
		   start_inline(Char(cpps), start_line);
		   Delete(cpps);
		 }
               }
    break;

  case 64:
#line 2002 "parser.y"
    {
                 (yyval.node) = new_node("insert");
		 Setattr((yyval.node),"code",(yyvsp[(1) - (1)].str));
	       }
    break;

  case 65:
#line 2006 "parser.y"
    {
		 String *code = NewStringEmpty();
		 (yyval.node) = new_node("insert");
		 Setattr((yyval.node),"section",(yyvsp[(3) - (5)].id));
		 Setattr((yyval.node),"code",code);
		 if (Swig_insert_file((yyvsp[(5) - (5)].id),code) < 0) {
		   Swig_error(cparse_file, cparse_line, "Couldn't find '%s'.\n", (yyvsp[(5) - (5)].id));
		   (yyval.node) = 0;
		 } 
               }
    break;

  case 66:
#line 2016 "parser.y"
    {
		 (yyval.node) = new_node("insert");
		 Setattr((yyval.node),"section",(yyvsp[(3) - (5)].id));
		 Setattr((yyval.node),"code",(yyvsp[(5) - (5)].str));
               }
    break;

  case 67:
#line 2021 "parser.y"
    {
		 String *code;
                 skip_balanced('{','}');
		 (yyval.node) = new_node("insert");
		 Setattr((yyval.node),"section",(yyvsp[(3) - (5)].id));
		 Delitem(scanner_ccode,0);
		 Delitem(scanner_ccode,DOH_END);
		 code = Copy(scanner_ccode);
		 Setattr((yyval.node),"code", code);
		 Delete(code);
	       }
    break;

  case 68:
#line 2039 "parser.y"
    {
                 (yyval.node) = new_node("module");
		 if ((yyvsp[(2) - (3)].node)) {
		   Setattr((yyval.node),"options",(yyvsp[(2) - (3)].node));
		   if (Getattr((yyvsp[(2) - (3)].node),"directors")) {
		     Wrapper_director_mode_set(1);
		   } 
		   if (Getattr((yyvsp[(2) - (3)].node),"dirprot")) {
		     Wrapper_director_protected_mode_set(1);
		   } 
		   if (Getattr((yyvsp[(2) - (3)].node),"allprotected")) {
		     Wrapper_all_protected_mode_set(1);
		   } 
		   if (Getattr((yyvsp[(2) - (3)].node),"templatereduce")) {
		     template_reduce = 1;
		   }
		   if (Getattr((yyvsp[(2) - (3)].node),"notemplatereduce")) {
		     template_reduce = 0;
		   }
		 }
		 if (!ModuleName) ModuleName = NewString((yyvsp[(3) - (3)].id));
		 if (!import_mode) {
		   /* first module included, we apply global
		      ModuleName, which can be modify by -module */
		   String *mname = Copy(ModuleName);
		   Setattr((yyval.node),"name",mname);
		   Delete(mname);
		 } else { 
		   /* import mode, we just pass the idstring */
		   Setattr((yyval.node),"name",(yyvsp[(3) - (3)].id));   
		 }		 
		 if (!module_node) module_node = (yyval.node);
	       }
    break;

  case 69:
#line 2079 "parser.y"
    {
                 Swig_warning(WARN_DEPRECATED_NAME,cparse_file,cparse_line, "%%name is deprecated.  Use %%rename instead.\n");
		 Delete(yyrename);
                 yyrename = NewString((yyvsp[(3) - (4)].id));
		 (yyval.node) = 0;
               }
    break;

  case 70:
#line 2085 "parser.y"
    {
		 Swig_warning(WARN_DEPRECATED_NAME,cparse_file,cparse_line, "%%name is deprecated.  Use %%rename instead.\n");
		 (yyval.node) = 0;
		 Swig_error(cparse_file,cparse_line,"Missing argument to %%name directive.\n");
	       }
    break;

  case 71:
#line 2098 "parser.y"
    {
                 (yyval.node) = new_node("native");
		 Setattr((yyval.node),"name",(yyvsp[(3) - (7)].id));
		 Setattr((yyval.node),"wrap:name",(yyvsp[(6) - (7)].id));
	         add_symbols((yyval.node));
	       }
    break;

  case 72:
#line 2104 "parser.y"
    {
		 if (!SwigType_isfunction((yyvsp[(7) - (8)].decl).type)) {
		   Swig_error(cparse_file,cparse_line,"%%native declaration '%s' is not a function.\n", (yyvsp[(7) - (8)].decl).id);
		   (yyval.node) = 0;
		 } else {
		     Delete(SwigType_pop_function((yyvsp[(7) - (8)].decl).type));
		     /* Need check for function here */
		     SwigType_push((yyvsp[(6) - (8)].type),(yyvsp[(7) - (8)].decl).type);
		     (yyval.node) = new_node("native");
	             Setattr((yyval.node),"name",(yyvsp[(3) - (8)].id));
		     Setattr((yyval.node),"wrap:name",(yyvsp[(7) - (8)].decl).id);
		     Setattr((yyval.node),"type",(yyvsp[(6) - (8)].type));
		     Setattr((yyval.node),"parms",(yyvsp[(7) - (8)].decl).parms);
		     Setattr((yyval.node),"decl",(yyvsp[(7) - (8)].decl).type);
		 }
	         add_symbols((yyval.node));
	       }
    break;

  case 73:
#line 2130 "parser.y"
    {
                 (yyval.node) = new_node("pragma");
		 Setattr((yyval.node),"lang",(yyvsp[(2) - (5)].id));
		 Setattr((yyval.node),"name",(yyvsp[(3) - (5)].id));
		 Setattr((yyval.node),"value",(yyvsp[(5) - (5)].str));
	       }
    break;

  case 74:
#line 2136 "parser.y"
    {
		(yyval.node) = new_node("pragma");
		Setattr((yyval.node),"lang",(yyvsp[(2) - (3)].id));
		Setattr((yyval.node),"name",(yyvsp[(3) - (3)].id));
	      }
    break;

  case 75:
#line 2143 "parser.y"
    { (yyval.str) = NewString((yyvsp[(1) - (1)].id)); }
    break;

  case 76:
#line 2144 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); }
    break;

  case 77:
#line 2147 "parser.y"
    { (yyval.id) = (yyvsp[(2) - (3)].id); }
    break;

  case 78:
#line 2148 "parser.y"
    { (yyval.id) = (char *) "swig"; }
    break;

  case 79:
#line 2156 "parser.y"
    {
                SwigType *t = (yyvsp[(2) - (4)].decl).type;
		Hash *kws = NewHash();
		String *fixname;
		fixname = feature_identifier_fix((yyvsp[(2) - (4)].decl).id);
		Setattr(kws,"name",(yyvsp[(3) - (4)].id));
		if (!Len(t)) t = 0;
		/* Special declarator check */
		if (t) {
		  if (SwigType_isfunction(t)) {
		    SwigType *decl = SwigType_pop_function(t);
		    if (SwigType_ispointer(t)) {
		      String *nname = NewStringf("*%s",fixname);
		      if ((yyvsp[(1) - (4)].ivalue)) {
			Swig_name_rename_add(Namespaceprefix, nname,decl,kws,(yyvsp[(2) - (4)].decl).parms);
		      } else {
			Swig_name_namewarn_add(Namespaceprefix,nname,decl,kws);
		      }
		      Delete(nname);
		    } else {
		      if ((yyvsp[(1) - (4)].ivalue)) {
			Swig_name_rename_add(Namespaceprefix,(fixname),decl,kws,(yyvsp[(2) - (4)].decl).parms);
		      } else {
			Swig_name_namewarn_add(Namespaceprefix,(fixname),decl,kws);
		      }
		    }
		    Delete(decl);
		  } else if (SwigType_ispointer(t)) {
		    String *nname = NewStringf("*%s",fixname);
		    if ((yyvsp[(1) - (4)].ivalue)) {
		      Swig_name_rename_add(Namespaceprefix,(nname),0,kws,(yyvsp[(2) - (4)].decl).parms);
		    } else {
		      Swig_name_namewarn_add(Namespaceprefix,(nname),0,kws);
		    }
		    Delete(nname);
		  }
		} else {
		  if ((yyvsp[(1) - (4)].ivalue)) {
		    Swig_name_rename_add(Namespaceprefix,(fixname),0,kws,(yyvsp[(2) - (4)].decl).parms);
		  } else {
		    Swig_name_namewarn_add(Namespaceprefix,(fixname),0,kws);
		  }
		}
                (yyval.node) = 0;
		scanner_clear_rename();
              }
    break;

  case 80:
#line 2202 "parser.y"
    {
		String *fixname;
		Hash *kws = (yyvsp[(3) - (7)].node);
		SwigType *t = (yyvsp[(5) - (7)].decl).type;
		fixname = feature_identifier_fix((yyvsp[(5) - (7)].decl).id);
		if (!Len(t)) t = 0;
		/* Special declarator check */
		if (t) {
		  if ((yyvsp[(6) - (7)].dtype).qualifier) SwigType_push(t,(yyvsp[(6) - (7)].dtype).qualifier);
		  if (SwigType_isfunction(t)) {
		    SwigType *decl = SwigType_pop_function(t);
		    if (SwigType_ispointer(t)) {
		      String *nname = NewStringf("*%s",fixname);
		      if ((yyvsp[(1) - (7)].ivalue)) {
			Swig_name_rename_add(Namespaceprefix, nname,decl,kws,(yyvsp[(5) - (7)].decl).parms);
		      } else {
			Swig_name_namewarn_add(Namespaceprefix,nname,decl,kws);
		      }
		      Delete(nname);
		    } else {
		      if ((yyvsp[(1) - (7)].ivalue)) {
			Swig_name_rename_add(Namespaceprefix,(fixname),decl,kws,(yyvsp[(5) - (7)].decl).parms);
		      } else {
			Swig_name_namewarn_add(Namespaceprefix,(fixname),decl,kws);
		      }
		    }
		    Delete(decl);
		  } else if (SwigType_ispointer(t)) {
		    String *nname = NewStringf("*%s",fixname);
		    if ((yyvsp[(1) - (7)].ivalue)) {
		      Swig_name_rename_add(Namespaceprefix,(nname),0,kws,(yyvsp[(5) - (7)].decl).parms);
		    } else {
		      Swig_name_namewarn_add(Namespaceprefix,(nname),0,kws);
		    }
		    Delete(nname);
		  }
		} else {
		  if ((yyvsp[(1) - (7)].ivalue)) {
		    Swig_name_rename_add(Namespaceprefix,(fixname),0,kws,(yyvsp[(5) - (7)].decl).parms);
		  } else {
		    Swig_name_namewarn_add(Namespaceprefix,(fixname),0,kws);
		  }
		}
                (yyval.node) = 0;
		scanner_clear_rename();
              }
    break;

  case 81:
#line 2248 "parser.y"
    {
		if ((yyvsp[(1) - (6)].ivalue)) {
		  Swig_name_rename_add(Namespaceprefix,(yyvsp[(5) - (6)].id),0,(yyvsp[(3) - (6)].node),0);
		} else {
		  Swig_name_namewarn_add(Namespaceprefix,(yyvsp[(5) - (6)].id),0,(yyvsp[(3) - (6)].node));
		}
		(yyval.node) = 0;
		scanner_clear_rename();
              }
    break;

  case 82:
#line 2259 "parser.y"
    {
		    (yyval.ivalue) = 1;
                }
    break;

  case 83:
#line 2262 "parser.y"
    {
                    (yyval.ivalue) = 0;
                }
    break;

  case 84:
#line 2289 "parser.y"
    {
                    String *val = (yyvsp[(7) - (7)].str) ? NewString((yyvsp[(7) - (7)].str)) : NewString("1");
                    new_feature((yyvsp[(3) - (7)].id), val, 0, (yyvsp[(5) - (7)].decl).id, (yyvsp[(5) - (7)].decl).type, (yyvsp[(5) - (7)].decl).parms, (yyvsp[(6) - (7)].dtype).qualifier);
                    (yyval.node) = 0;
                  }
    break;

  case 85:
#line 2294 "parser.y"
    {
                    String *val = Len((yyvsp[(5) - (9)].id)) ? NewString((yyvsp[(5) - (9)].id)) : 0;
                    new_feature((yyvsp[(3) - (9)].id), val, 0, (yyvsp[(7) - (9)].decl).id, (yyvsp[(7) - (9)].decl).type, (yyvsp[(7) - (9)].decl).parms, (yyvsp[(8) - (9)].dtype).qualifier);
                    (yyval.node) = 0;
                  }
    break;

  case 86:
#line 2299 "parser.y"
    {
                    String *val = (yyvsp[(8) - (8)].str) ? NewString((yyvsp[(8) - (8)].str)) : NewString("1");
                    new_feature((yyvsp[(3) - (8)].id), val, (yyvsp[(4) - (8)].node), (yyvsp[(6) - (8)].decl).id, (yyvsp[(6) - (8)].decl).type, (yyvsp[(6) - (8)].decl).parms, (yyvsp[(7) - (8)].dtype).qualifier);
                    (yyval.node) = 0;
                  }
    break;

  case 87:
#line 2304 "parser.y"
    {
                    String *val = Len((yyvsp[(5) - (10)].id)) ? NewString((yyvsp[(5) - (10)].id)) : 0;
                    new_feature((yyvsp[(3) - (10)].id), val, (yyvsp[(6) - (10)].node), (yyvsp[(8) - (10)].decl).id, (yyvsp[(8) - (10)].decl).type, (yyvsp[(8) - (10)].decl).parms, (yyvsp[(9) - (10)].dtype).qualifier);
                    (yyval.node) = 0;
                  }
    break;

  case 88:
#line 2311 "parser.y"
    {
                    String *val = (yyvsp[(5) - (5)].str) ? NewString((yyvsp[(5) - (5)].str)) : NewString("1");
                    new_feature((yyvsp[(3) - (5)].id), val, 0, 0, 0, 0, 0);
                    (yyval.node) = 0;
                  }
    break;

  case 89:
#line 2316 "parser.y"
    {
                    String *val = Len((yyvsp[(5) - (7)].id)) ? NewString((yyvsp[(5) - (7)].id)) : 0;
                    new_feature((yyvsp[(3) - (7)].id), val, 0, 0, 0, 0, 0);
                    (yyval.node) = 0;
                  }
    break;

  case 90:
#line 2321 "parser.y"
    {
                    String *val = (yyvsp[(6) - (6)].str) ? NewString((yyvsp[(6) - (6)].str)) : NewString("1");
                    new_feature((yyvsp[(3) - (6)].id), val, (yyvsp[(4) - (6)].node), 0, 0, 0, 0);
                    (yyval.node) = 0;
                  }
    break;

  case 91:
#line 2326 "parser.y"
    {
                    String *val = Len((yyvsp[(5) - (8)].id)) ? NewString((yyvsp[(5) - (8)].id)) : 0;
                    new_feature((yyvsp[(3) - (8)].id), val, (yyvsp[(6) - (8)].node), 0, 0, 0, 0);
                    (yyval.node) = 0;
                  }
    break;

  case 92:
#line 2333 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); }
    break;

  case 93:
#line 2334 "parser.y"
    { (yyval.str) = 0; }
    break;

  case 94:
#line 2335 "parser.y"
    { (yyval.str) = (yyvsp[(3) - (5)].pl); }
    break;

  case 95:
#line 2338 "parser.y"
    {
		  (yyval.node) = NewHash();
		  Setattr((yyval.node),"name",(yyvsp[(2) - (4)].id));
		  Setattr((yyval.node),"value",(yyvsp[(4) - (4)].id));
                }
    break;

  case 96:
#line 2343 "parser.y"
    {
		  (yyval.node) = NewHash();
		  Setattr((yyval.node),"name",(yyvsp[(2) - (5)].id));
		  Setattr((yyval.node),"value",(yyvsp[(4) - (5)].id));
                  set_nextSibling((yyval.node),(yyvsp[(5) - (5)].node));
                }
    break;

  case 97:
#line 2353 "parser.y"
    {
                 Parm *val;
		 String *name;
		 SwigType *t;
		 if (Namespaceprefix) name = NewStringf("%s::%s", Namespaceprefix, (yyvsp[(5) - (7)].decl).id);
		 else name = NewString((yyvsp[(5) - (7)].decl).id);
		 val = (yyvsp[(3) - (7)].pl);
		 if ((yyvsp[(5) - (7)].decl).parms) {
		   Setmeta(val,"parms",(yyvsp[(5) - (7)].decl).parms);
		 }
		 t = (yyvsp[(5) - (7)].decl).type;
		 if (!Len(t)) t = 0;
		 if (t) {
		   if ((yyvsp[(6) - (7)].dtype).qualifier) SwigType_push(t,(yyvsp[(6) - (7)].dtype).qualifier);
		   if (SwigType_isfunction(t)) {
		     SwigType *decl = SwigType_pop_function(t);
		     if (SwigType_ispointer(t)) {
		       String *nname = NewStringf("*%s",name);
		       Swig_feature_set(Swig_cparse_features(), nname, decl, "feature:varargs", val, 0);
		       Delete(nname);
		     } else {
		       Swig_feature_set(Swig_cparse_features(), name, decl, "feature:varargs", val, 0);
		     }
		     Delete(decl);
		   } else if (SwigType_ispointer(t)) {
		     String *nname = NewStringf("*%s",name);
		     Swig_feature_set(Swig_cparse_features(),nname,0,"feature:varargs",val, 0);
		     Delete(nname);
		   }
		 } else {
		   Swig_feature_set(Swig_cparse_features(),name,0,"feature:varargs",val, 0);
		 }
		 Delete(name);
		 (yyval.node) = 0;
              }
    break;

  case 98:
#line 2389 "parser.y"
    { (yyval.pl) = (yyvsp[(1) - (1)].pl); }
    break;

  case 99:
#line 2390 "parser.y"
    { 
		  int i;
		  int n;
		  Parm *p;
		  n = atoi(Char((yyvsp[(1) - (3)].dtype).val));
		  if (n <= 0) {
		    Swig_error(cparse_file, cparse_line,"Argument count in %%varargs must be positive.\n");
		    (yyval.pl) = 0;
		  } else {
		    (yyval.pl) = Copy((yyvsp[(3) - (3)].p));
		    Setattr((yyval.pl),"name","VARARGS_SENTINEL");
		    for (i = 0; i < n; i++) {
		      p = Copy((yyvsp[(3) - (3)].p));
		      set_nextSibling(p,(yyval.pl));
		      Delete((yyval.pl));
		      (yyval.pl) = p;
		    }
		  }
                }
    break;

  case 100:
#line 2420 "parser.y"
    {
		   (yyval.node) = 0;
		   if ((yyvsp[(3) - (6)].tmap).op) {
		     String *code = 0;
		     (yyval.node) = new_node("typemap");
		     Setattr((yyval.node),"method",(yyvsp[(3) - (6)].tmap).op);
		     if ((yyvsp[(3) - (6)].tmap).kwargs) {
		       ParmList *kw = (yyvsp[(3) - (6)].tmap).kwargs;
                       code = remove_block(kw, (yyvsp[(6) - (6)].str));
		       Setattr((yyval.node),"kwargs", (yyvsp[(3) - (6)].tmap).kwargs);
		     }
		     code = code ? code : NewString((yyvsp[(6) - (6)].str));
		     Setattr((yyval.node),"code", code);
		     Delete(code);
		     appendChild((yyval.node),(yyvsp[(5) - (6)].p));
		   }
	       }
    break;

  case 101:
#line 2437 "parser.y"
    {
		 (yyval.node) = 0;
		 if ((yyvsp[(3) - (6)].tmap).op) {
		   (yyval.node) = new_node("typemap");
		   Setattr((yyval.node),"method",(yyvsp[(3) - (6)].tmap).op);
		   appendChild((yyval.node),(yyvsp[(5) - (6)].p));
		 }
	       }
    break;

  case 102:
#line 2445 "parser.y"
    {
		   (yyval.node) = 0;
		   if ((yyvsp[(3) - (8)].tmap).op) {
		     (yyval.node) = new_node("typemapcopy");
		     Setattr((yyval.node),"method",(yyvsp[(3) - (8)].tmap).op);
		     Setattr((yyval.node),"pattern", Getattr((yyvsp[(7) - (8)].p),"pattern"));
		     appendChild((yyval.node),(yyvsp[(5) - (8)].p));
		   }
	       }
    break;

  case 103:
#line 2458 "parser.y"
    {
		 Hash *p;
		 String *name;
		 p = nextSibling((yyvsp[(1) - (1)].node));
		 if (p && (!Getattr(p,"value"))) {
 		   /* this is the deprecated two argument typemap form */
 		   Swig_warning(WARN_DEPRECATED_TYPEMAP_LANG,cparse_file, cparse_line,
				"Specifying the language name in %%typemap is deprecated - use #ifdef SWIG<LANG> instead.\n");
		   /* two argument typemap form */
		   name = Getattr((yyvsp[(1) - (1)].node),"name");
		   if (!name || (Strcmp(name,typemap_lang))) {
		     (yyval.tmap).op = 0;
		     (yyval.tmap).kwargs = 0;
		   } else {
		     (yyval.tmap).op = Getattr(p,"name");
		     (yyval.tmap).kwargs = nextSibling(p);
		   }
		 } else {
		   /* one-argument typemap-form */
		   (yyval.tmap).op = Getattr((yyvsp[(1) - (1)].node),"name");
		   (yyval.tmap).kwargs = p;
		 }
                }
    break;

  case 104:
#line 2483 "parser.y"
    {
                 (yyval.p) = (yyvsp[(1) - (2)].p);
		 set_nextSibling((yyval.p),(yyvsp[(2) - (2)].p));
		}
    break;

  case 105:
#line 2489 "parser.y"
    {
                 (yyval.p) = (yyvsp[(2) - (3)].p);
		 set_nextSibling((yyval.p),(yyvsp[(3) - (3)].p));
                }
    break;

  case 106:
#line 2493 "parser.y"
    { (yyval.p) = 0;}
    break;

  case 107:
#line 2496 "parser.y"
    {
                  Parm *parm;
		  SwigType_push((yyvsp[(1) - (2)].type),(yyvsp[(2) - (2)].decl).type);
		  (yyval.p) = new_node("typemapitem");
		  parm = NewParm((yyvsp[(1) - (2)].type),(yyvsp[(2) - (2)].decl).id);
		  Setattr((yyval.p),"pattern",parm);
		  Setattr((yyval.p),"parms", (yyvsp[(2) - (2)].decl).parms);
		  Delete(parm);
		  /*		  $$ = NewParm($1,$2.id);
				  Setattr($$,"parms",$2.parms); */
                }
    break;

  case 108:
#line 2507 "parser.y"
    {
                  (yyval.p) = new_node("typemapitem");
		  Setattr((yyval.p),"pattern",(yyvsp[(2) - (3)].pl));
		  /*		  Setattr($$,"multitype",$2); */
               }
    break;

  case 109:
#line 2512 "parser.y"
    {
		 (yyval.p) = new_node("typemapitem");
		 Setattr((yyval.p),"pattern", (yyvsp[(2) - (6)].pl));
		 /*                 Setattr($$,"multitype",$2); */
		 Setattr((yyval.p),"parms",(yyvsp[(5) - (6)].pl));
               }
    break;

  case 110:
#line 2525 "parser.y"
    {
                   (yyval.node) = new_node("types");
		   Setattr((yyval.node),"parms",(yyvsp[(3) - (5)].pl));
                   if ((yyvsp[(5) - (5)].str))
		     Setattr((yyval.node),"convcode",NewString((yyvsp[(5) - (5)].str)));
               }
    break;

  case 111:
#line 2537 "parser.y"
    {
                  Parm *p, *tp;
		  Node *n;
		  Node *tnode = 0;
		  Symtab *tscope = 0;
		  int     specialized = 0;

		  (yyval.node) = 0;

		  tscope = Swig_symbol_current();          /* Get the current scope */

		  /* If the class name is qualified, we need to create or lookup namespace entries */
		  if (!inclass) {
		    (yyvsp[(5) - (9)].str) = resolve_node_scope((yyvsp[(5) - (9)].str));
		  }

		  /*
		    We use the new namespace entry 'nscope' only to
		    emit the template node. The template parameters are
		    resolved in the current 'tscope'.

		    This is closer to the C++ (typedef) behavior.
		  */
		  n = Swig_cparse_template_locate((yyvsp[(5) - (9)].str),(yyvsp[(7) - (9)].p),tscope);

		  /* Patch the argument types to respect namespaces */
		  p = (yyvsp[(7) - (9)].p);
		  while (p) {
		    SwigType *value = Getattr(p,"value");
		    if (!value) {
		      SwigType *ty = Getattr(p,"type");
		      if (ty) {
			SwigType *rty = 0;
			int reduce = template_reduce;
			if (reduce || !SwigType_ispointer(ty)) {
			  rty = Swig_symbol_typedef_reduce(ty,tscope);
			  if (!reduce) reduce = SwigType_ispointer(rty);
			}
			ty = reduce ? Swig_symbol_type_qualify(rty,tscope) : Swig_symbol_type_qualify(ty,tscope);
			Setattr(p,"type",ty);
			Delete(ty);
			Delete(rty);
		      }
		    } else {
		      value = Swig_symbol_type_qualify(value,tscope);
		      Setattr(p,"value",value);
		      Delete(value);
		    }

		    p = nextSibling(p);
		  }

		  /* Look for the template */
		  {
                    Node *nn = n;
                    Node *linklistend = 0;
                    while (nn) {
                      Node *templnode = 0;
                      if (Strcmp(nodeType(nn),"template") == 0) {
                        int nnisclass = (Strcmp(Getattr(nn,"templatetype"),"class") == 0); /* if not a templated class it is a templated function */
                        Parm *tparms = Getattr(nn,"templateparms");
                        if (!tparms) {
                          specialized = 1;
                        }
                        if (nnisclass && !specialized && ((ParmList_len((yyvsp[(7) - (9)].p)) > ParmList_len(tparms)))) {
                          Swig_error(cparse_file, cparse_line, "Too many template parameters. Maximum of %d.\n", ParmList_len(tparms));
                        } else if (nnisclass && !specialized && ((ParmList_len((yyvsp[(7) - (9)].p)) < ParmList_numrequired(tparms)))) {
                          Swig_error(cparse_file, cparse_line, "Not enough template parameters specified. %d required.\n", ParmList_numrequired(tparms));
                        } else if (!nnisclass && ((ParmList_len((yyvsp[(7) - (9)].p)) != ParmList_len(tparms)))) {
                          /* must be an overloaded templated method - ignore it as it is overloaded with a different number of template parameters */
                          nn = Getattr(nn,"sym:nextSibling"); /* repeat for overloaded templated functions */
                          continue;
                        } else {
			  String *tname = Copy((yyvsp[(5) - (9)].str));
                          int def_supplied = 0;
                          /* Expand the template */
			  Node *templ = Swig_symbol_clookup((yyvsp[(5) - (9)].str),0);
			  Parm *targs = templ ? Getattr(templ,"templateparms") : 0;

                          ParmList *temparms;
                          if (specialized) temparms = CopyParmList((yyvsp[(7) - (9)].p));
                          else temparms = CopyParmList(tparms);

                          /* Create typedef's and arguments */
                          p = (yyvsp[(7) - (9)].p);
                          tp = temparms;
                          if (!p && ParmList_len(p) != ParmList_len(temparms)) {
                            /* we have no template parameters supplied in %template for a template that has default args*/
                            p = tp;
                            def_supplied = 1;
                          }

                          while (p) {
                            String *value = Getattr(p,"value");
                            if (def_supplied) {
                              Setattr(p,"default","1");
                            }
                            if (value) {
                              Setattr(tp,"value",value);
                            } else {
                              SwigType *ty = Getattr(p,"type");
                              if (ty) {
                                Setattr(tp,"type",ty);
                              }
                              Delattr(tp,"value");
                            }
			    /* fix default arg values */
			    if (targs) {
			      Parm *pi = temparms;
			      Parm *ti = targs;
			      String *tv = Getattr(tp,"value");
			      if (!tv) tv = Getattr(tp,"type");
			      while(pi != tp) {
				String *name = Getattr(ti,"name");
				String *value = Getattr(pi,"value");
				if (!value) value = Getattr(pi,"type");
				Replaceid(tv, name, value);
				pi = nextSibling(pi);
				ti = nextSibling(ti);
			      }
			    }
                            p = nextSibling(p);
                            tp = nextSibling(tp);
                            if (!p && tp) {
                              p = tp;
                              def_supplied = 1;
                            }
                          }

                          templnode = copy_node(nn);
                          /* We need to set the node name based on name used to instantiate */
                          Setattr(templnode,"name",tname);
			  Delete(tname);
                          if (!specialized) {
                            Delattr(templnode,"sym:typename");
                          } else {
                            Setattr(templnode,"sym:typename","1");
                          }
                          if ((yyvsp[(3) - (9)].id)) {
			    /*
			       Comment this out for 1.3.28. We need to
			       re-enable it later but first we need to
			       move %ignore from using %rename to use
			       %feature(ignore).

			       String *symname = Swig_name_make(templnode,0,$3,0,0);
			    */
			    String *symname = (yyvsp[(3) - (9)].id);
                            Swig_cparse_template_expand(templnode,symname,temparms,tscope);
                            Setattr(templnode,"sym:name",symname);
                          } else {
                            static int cnt = 0;
                            String *nname = NewStringf("__dummy_%d__", cnt++);
                            Swig_cparse_template_expand(templnode,nname,temparms,tscope);
                            Setattr(templnode,"sym:name",nname);
			    Delete(nname);
                            Setattr(templnode,"feature:onlychildren",
                                    "typemap,typemapitem,typemapcopy,typedef,types,fragment");
                          }
                          Delattr(templnode,"templatetype");
                          Setattr(templnode,"template",nn);
                          tnode = templnode;
                          Setfile(templnode,cparse_file);
                          Setline(templnode,cparse_line);
                          Delete(temparms);

                          add_symbols_copy(templnode);

                          if (Strcmp(nodeType(templnode),"class") == 0) {

                            /* Identify pure abstract methods */
                            Setattr(templnode,"abstract", pure_abstract(firstChild(templnode)));

                            /* Set up inheritance in symbol table */
                            {
                              Symtab  *csyms;
                              List *baselist = Getattr(templnode,"baselist");
                              csyms = Swig_symbol_current();
                              Swig_symbol_setscope(Getattr(templnode,"symtab"));
                              if (baselist) {
                                List *bases = make_inherit_list(Getattr(templnode,"name"),baselist);
                                if (bases) {
                                  Iterator s;
                                  for (s = First(bases); s.item; s = Next(s)) {
                                    Symtab *st = Getattr(s.item,"symtab");
                                    if (st) {
				      Setfile(st,Getfile(s.item));
				      Setline(st,Getline(s.item));
                                      Swig_symbol_inherit(st);
                                    }
                                  }
				  Delete(bases);
                                }
                              }
                              Swig_symbol_setscope(csyms);
                            }

                            /* Merge in addmethods for this class */

			    /* !!! This may be broken.  We may have to add the
			       addmethods at the beginning of the class */

                            if (extendhash) {
                              String *stmp = 0;
                              String *clsname;
                              Node *am;
                              if (Namespaceprefix) {
                                clsname = stmp = NewStringf("%s::%s", Namespaceprefix, Getattr(templnode,"name"));
                              } else {
                                clsname = Getattr(templnode,"name");
                              }
                              am = Getattr(extendhash,clsname);
                              if (am) {
                                Symtab *st = Swig_symbol_current();
                                Swig_symbol_setscope(Getattr(templnode,"symtab"));
                                /*			    Printf(stdout,"%s: %s %x %x\n", Getattr(templnode,"name"), clsname, Swig_symbol_current(), Getattr(templnode,"symtab")); */
                                merge_extensions(templnode,am);
                                Swig_symbol_setscope(st);
				append_previous_extension(templnode,am);
                                Delattr(extendhash,clsname);
                              }
			      if (stmp) Delete(stmp);
                            }
                            /* Add to classes hash */
                            if (!classes) classes = NewHash();

                            {
                              if (Namespaceprefix) {
                                String *temp = NewStringf("%s::%s", Namespaceprefix, Getattr(templnode,"name"));
                                Setattr(classes,temp,templnode);
				Delete(temp);
                              } else {
				String *qs = Swig_symbol_qualifiedscopename(templnode);
                                Setattr(classes, qs,templnode);
				Delete(qs);
                              }
                            }
                          }
                        }

                        /* all the overloaded templated functions are added into a linked list */
                        if (nscope_inner) {
                          /* non-global namespace */
                          if (templnode) {
                            appendChild(nscope_inner,templnode);
			    Delete(templnode);
                            if (nscope) (yyval.node) = nscope;
                          }
                        } else {
                          /* global namespace */
                          if (!linklistend) {
                            (yyval.node) = templnode;
                          } else {
                            set_nextSibling(linklistend,templnode);
			    Delete(templnode);
                          }
                          linklistend = templnode;
                        }
                      }
                      nn = Getattr(nn,"sym:nextSibling"); /* repeat for overloaded templated functions. If a templated class there will never be a sibling. */
                    }
		  }
	          Swig_symbol_setscope(tscope);
		  Delete(Namespaceprefix);
		  Namespaceprefix = Swig_symbol_qualifiedscopename(0);
                }
    break;

  case 112:
#line 2810 "parser.y"
    {
		  Swig_warning(0,cparse_file, cparse_line,"%s\n", (yyvsp[(2) - (2)].id));
		  (yyval.node) = 0;
               }
    break;

  case 113:
#line 2820 "parser.y"
    {
                    (yyval.node) = (yyvsp[(1) - (1)].node); 
                    if ((yyval.node)) {
   		      add_symbols((yyval.node));
                      default_arguments((yyval.node));
   	            }
                }
    break;

  case 114:
#line 2827 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 115:
#line 2828 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 116:
#line 2832 "parser.y"
    {
		  if (Strcmp((yyvsp[(2) - (3)].id),"C") == 0) {
		    cparse_externc = 1;
		  }
		}
    break;

  case 117:
#line 2836 "parser.y"
    {
		  cparse_externc = 0;
		  if (Strcmp((yyvsp[(2) - (6)].id),"C") == 0) {
		    Node *n = firstChild((yyvsp[(5) - (6)].node));
		    (yyval.node) = new_node("extern");
		    Setattr((yyval.node),"name",(yyvsp[(2) - (6)].id));
		    appendChild((yyval.node),n);
		    while (n) {
		      SwigType *decl = Getattr(n,"decl");
		      if (SwigType_isfunction(decl)) {
			Setattr(n,"storage","externc");
		      }
		      n = nextSibling(n);
		    }
		  } else {
		     Swig_warning(WARN_PARSE_UNDEFINED_EXTERN,cparse_file, cparse_line,"Unrecognized extern type \"%s\".\n", (yyvsp[(2) - (6)].id));
		    (yyval.node) = new_node("extern");
		    Setattr((yyval.node),"name",(yyvsp[(2) - (6)].id));
		    appendChild((yyval.node),firstChild((yyvsp[(5) - (6)].node)));
		  }
                }
    break;

  case 118:
#line 2863 "parser.y"
    {
              (yyval.node) = new_node("cdecl");
	      if ((yyvsp[(4) - (5)].dtype).qualifier) SwigType_push((yyvsp[(3) - (5)].decl).type,(yyvsp[(4) - (5)].dtype).qualifier);
	      Setattr((yyval.node),"type",(yyvsp[(2) - (5)].type));
	      Setattr((yyval.node),"storage",(yyvsp[(1) - (5)].id));
	      Setattr((yyval.node),"name",(yyvsp[(3) - (5)].decl).id);
	      Setattr((yyval.node),"decl",(yyvsp[(3) - (5)].decl).type);
	      Setattr((yyval.node),"parms",(yyvsp[(3) - (5)].decl).parms);
	      Setattr((yyval.node),"value",(yyvsp[(4) - (5)].dtype).val);
	      Setattr((yyval.node),"throws",(yyvsp[(4) - (5)].dtype).throws);
	      Setattr((yyval.node),"throw",(yyvsp[(4) - (5)].dtype).throwf);
	      if (!(yyvsp[(5) - (5)].node)) {
		if (Len(scanner_ccode)) {
		  String *code = Copy(scanner_ccode);
		  Setattr((yyval.node),"code",code);
		  Delete(code);
		}
	      } else {
		Node *n = (yyvsp[(5) - (5)].node);
		/* Inherit attributes */
		while (n) {
		  String *type = Copy((yyvsp[(2) - (5)].type));
		  Setattr(n,"type",type);
		  Setattr(n,"storage",(yyvsp[(1) - (5)].id));
		  n = nextSibling(n);
		  Delete(type);
		}
	      }
	      if ((yyvsp[(4) - (5)].dtype).bitfield) {
		Setattr((yyval.node),"bitfield", (yyvsp[(4) - (5)].dtype).bitfield);
	      }

	      /* Look for "::" declarations (ignored) */
	      if (Strstr((yyvsp[(3) - (5)].decl).id,"::")) {
                /* This is a special case. If the scope name of the declaration exactly
                   matches that of the declaration, then we will allow it. Otherwise, delete. */
                String *p = Swig_scopename_prefix((yyvsp[(3) - (5)].decl).id);
		if (p) {
		  if ((Namespaceprefix && Strcmp(p,Namespaceprefix) == 0) ||
		      (inclass && Strcmp(p,Classprefix) == 0)) {
		    String *lstr = Swig_scopename_last((yyvsp[(3) - (5)].decl).id);
		    Setattr((yyval.node),"name",lstr);
		    Delete(lstr);
		    set_nextSibling((yyval.node),(yyvsp[(5) - (5)].node));
		  } else {
		    Delete((yyval.node));
		    (yyval.node) = (yyvsp[(5) - (5)].node);
		  }
		  Delete(p);
		} else {
		  Delete((yyval.node));
		  (yyval.node) = (yyvsp[(5) - (5)].node);
		}
	      } else {
		set_nextSibling((yyval.node),(yyvsp[(5) - (5)].node));
	      }
           }
    break;

  case 119:
#line 2924 "parser.y"
    { 
                   (yyval.node) = 0;
                   Clear(scanner_ccode); 
               }
    break;

  case 120:
#line 2928 "parser.y"
    {
		 (yyval.node) = new_node("cdecl");
		 if ((yyvsp[(3) - (4)].dtype).qualifier) SwigType_push((yyvsp[(2) - (4)].decl).type,(yyvsp[(3) - (4)].dtype).qualifier);
		 Setattr((yyval.node),"name",(yyvsp[(2) - (4)].decl).id);
		 Setattr((yyval.node),"decl",(yyvsp[(2) - (4)].decl).type);
		 Setattr((yyval.node),"parms",(yyvsp[(2) - (4)].decl).parms);
		 Setattr((yyval.node),"value",(yyvsp[(3) - (4)].dtype).val);
		 Setattr((yyval.node),"throws",(yyvsp[(3) - (4)].dtype).throws);
		 Setattr((yyval.node),"throw",(yyvsp[(3) - (4)].dtype).throwf);
		 if ((yyvsp[(3) - (4)].dtype).bitfield) {
		   Setattr((yyval.node),"bitfield", (yyvsp[(3) - (4)].dtype).bitfield);
		 }
		 if (!(yyvsp[(4) - (4)].node)) {
		   if (Len(scanner_ccode)) {
		     String *code = Copy(scanner_ccode);
		     Setattr((yyval.node),"code",code);
		     Delete(code);
		   }
		 } else {
		   set_nextSibling((yyval.node),(yyvsp[(4) - (4)].node));
		 }
	       }
    break;

  case 121:
#line 2950 "parser.y"
    { 
                   skip_balanced('{','}');
                   (yyval.node) = 0;
               }
    break;

  case 122:
#line 2956 "parser.y"
    { 
                   (yyval.dtype) = (yyvsp[(1) - (1)].dtype); 
                   (yyval.dtype).qualifier = 0;
		   (yyval.dtype).throws = 0;
		   (yyval.dtype).throwf = 0;
              }
    break;

  case 123:
#line 2962 "parser.y"
    { 
                   (yyval.dtype) = (yyvsp[(2) - (2)].dtype); 
		   (yyval.dtype).qualifier = (yyvsp[(1) - (2)].str);
		   (yyval.dtype).throws = 0;
		   (yyval.dtype).throwf = 0;
	      }
    break;

  case 124:
#line 2968 "parser.y"
    { 
		   (yyval.dtype) = (yyvsp[(5) - (5)].dtype); 
                   (yyval.dtype).qualifier = 0;
		   (yyval.dtype).throws = (yyvsp[(3) - (5)].pl);
		   (yyval.dtype).throwf = NewString("1");
              }
    break;

  case 125:
#line 2974 "parser.y"
    { 
                   (yyval.dtype) = (yyvsp[(6) - (6)].dtype); 
                   (yyval.dtype).qualifier = (yyvsp[(1) - (6)].str);
		   (yyval.dtype).throws = (yyvsp[(4) - (6)].pl);
		   (yyval.dtype).throwf = NewString("1");
              }
    break;

  case 126:
#line 2987 "parser.y"
    {
		   SwigType *ty = 0;
		   (yyval.node) = new_node("enumforward");
		   ty = NewStringf("enum %s", (yyvsp[(3) - (4)].id));
		   Setattr((yyval.node),"name",(yyvsp[(3) - (4)].id));
		   Setattr((yyval.node),"type",ty);
		   Setattr((yyval.node),"sym:weak", "1");
		   add_symbols((yyval.node));
	      }
    break;

  case 127:
#line 3002 "parser.y"
    {
		  SwigType *ty = 0;
                  (yyval.node) = new_node("enum");
		  ty = NewStringf("enum %s", (yyvsp[(3) - (7)].id));
		  Setattr((yyval.node),"name",(yyvsp[(3) - (7)].id));
		  Setattr((yyval.node),"type",ty);
		  appendChild((yyval.node),(yyvsp[(5) - (7)].node));
		  add_symbols((yyval.node));       /* Add to tag space */
		  add_symbols((yyvsp[(5) - (7)].node));       /* Add enum values to id space */
               }
    break;

  case 128:
#line 3012 "parser.y"
    {
		 Node *n;
		 SwigType *ty = 0;
		 String   *unnamed = 0;
		 int       unnamedinstance = 0;

		 (yyval.node) = new_node("enum");
		 if ((yyvsp[(3) - (8)].id)) {
		   Setattr((yyval.node),"name",(yyvsp[(3) - (8)].id));
		   ty = NewStringf("enum %s", (yyvsp[(3) - (8)].id));
		 } else if ((yyvsp[(7) - (8)].decl).id) {
		   unnamed = make_unnamed();
		   ty = NewStringf("enum %s", unnamed);
		   Setattr((yyval.node),"unnamed",unnamed);
                   /* name is not set for unnamed enum instances, e.g. enum { foo } Instance; */
		   if ((yyvsp[(1) - (8)].id) && Cmp((yyvsp[(1) - (8)].id),"typedef") == 0) {
		     Setattr((yyval.node),"name",(yyvsp[(7) - (8)].decl).id);
                   } else {
                     unnamedinstance = 1;
                   }
		   Setattr((yyval.node),"storage",(yyvsp[(1) - (8)].id));
		 }
		 if ((yyvsp[(7) - (8)].decl).id && Cmp((yyvsp[(1) - (8)].id),"typedef") == 0) {
		   Setattr((yyval.node),"tdname",(yyvsp[(7) - (8)].decl).id);
                   Setattr((yyval.node),"allows_typedef","1");
                 }
		 appendChild((yyval.node),(yyvsp[(5) - (8)].node));
		 n = new_node("cdecl");
		 Setattr(n,"type",ty);
		 Setattr(n,"name",(yyvsp[(7) - (8)].decl).id);
		 Setattr(n,"storage",(yyvsp[(1) - (8)].id));
		 Setattr(n,"decl",(yyvsp[(7) - (8)].decl).type);
		 Setattr(n,"parms",(yyvsp[(7) - (8)].decl).parms);
		 Setattr(n,"unnamed",unnamed);

                 if (unnamedinstance) {
		   SwigType *cty = NewString("enum ");
		   Setattr((yyval.node),"type",cty);
		   Setattr((yyval.node),"unnamedinstance","1");
		   Setattr(n,"unnamedinstance","1");
		   Delete(cty);
                 }
		 if ((yyvsp[(8) - (8)].node)) {
		   Node *p = (yyvsp[(8) - (8)].node);
		   set_nextSibling(n,p);
		   while (p) {
		     SwigType *cty = Copy(ty);
		     Setattr(p,"type",cty);
		     Setattr(p,"unnamed",unnamed);
		     Setattr(p,"storage",(yyvsp[(1) - (8)].id));
		     Delete(cty);
		     p = nextSibling(p);
		   }
		 } else {
		   if (Len(scanner_ccode)) {
		     String *code = Copy(scanner_ccode);
		     Setattr(n,"code",code);
		     Delete(code);
		   }
		 }

                 /* Ensure that typedef enum ABC {foo} XYZ; uses XYZ for sym:name, like structs.
                  * Note that class_rename/yyrename are bit of a mess so used this simple approach to change the name. */
                 if ((yyvsp[(7) - (8)].decl).id && (yyvsp[(3) - (8)].id) && Cmp((yyvsp[(1) - (8)].id),"typedef") == 0) {
		   String *name = NewString((yyvsp[(7) - (8)].decl).id);
                   Setattr((yyval.node), "parser:makename", name);
		   Delete(name);
                 }

		 add_symbols((yyval.node));       /* Add enum to tag space */
		 set_nextSibling((yyval.node),n);
		 Delete(n);
		 add_symbols((yyvsp[(5) - (8)].node));       /* Add enum values to id space */
	         add_symbols(n);
		 Delete(unnamed);
	       }
    break;

  case 129:
#line 3090 "parser.y"
    {
                   /* This is a sick hack.  If the ctor_end has parameters,
                      and the parms parameter only has 1 parameter, this
                      could be a declaration of the form:

                         type (id)(parms)

			 Otherwise it's an error. */
                    int err = 0;
                    (yyval.node) = 0;

		    if ((ParmList_len((yyvsp[(4) - (6)].pl)) == 1) && (!Swig_scopename_check((yyvsp[(2) - (6)].type)))) {
		      SwigType *ty = Getattr((yyvsp[(4) - (6)].pl),"type");
		      String *name = Getattr((yyvsp[(4) - (6)].pl),"name");
		      err = 1;
		      if (!name) {
			(yyval.node) = new_node("cdecl");
			Setattr((yyval.node),"type",(yyvsp[(2) - (6)].type));
			Setattr((yyval.node),"storage",(yyvsp[(1) - (6)].id));
			Setattr((yyval.node),"name",ty);

			if ((yyvsp[(6) - (6)].decl).have_parms) {
			  SwigType *decl = NewStringEmpty();
			  SwigType_add_function(decl,(yyvsp[(6) - (6)].decl).parms);
			  Setattr((yyval.node),"decl",decl);
			  Setattr((yyval.node),"parms",(yyvsp[(6) - (6)].decl).parms);
			  if (Len(scanner_ccode)) {
			    String *code = Copy(scanner_ccode);
			    Setattr((yyval.node),"code",code);
			    Delete(code);
			  }
			}
			if ((yyvsp[(6) - (6)].decl).defarg) {
			  Setattr((yyval.node),"value",(yyvsp[(6) - (6)].decl).defarg);
			}
			Setattr((yyval.node),"throws",(yyvsp[(6) - (6)].decl).throws);
			Setattr((yyval.node),"throw",(yyvsp[(6) - (6)].decl).throwf);
			err = 0;
		      }
		    }
		    if (err) {
		      Swig_error(cparse_file,cparse_line,"Syntax error in input(2).\n");
		      exit(1);
		    }
                }
    break;

  case 130:
#line 3141 "parser.y"
    {  (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 131:
#line 3142 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 132:
#line 3143 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 133:
#line 3144 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 134:
#line 3145 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 135:
#line 3146 "parser.y"
    { (yyval.node) = 0; }
    break;

  case 136:
#line 3152 "parser.y"
    {
                   List *bases = 0;
		   Node *scope = 0;
		   (yyval.node) = new_node("class");
		   Setline((yyval.node),cparse_start_line);
		   Setattr((yyval.node),"kind",(yyvsp[(2) - (5)].id));
		   if ((yyvsp[(4) - (5)].bases)) {
		     Setattr((yyval.node),"baselist", Getattr((yyvsp[(4) - (5)].bases),"public"));
		     Setattr((yyval.node),"protectedbaselist", Getattr((yyvsp[(4) - (5)].bases),"protected"));
		     Setattr((yyval.node),"privatebaselist", Getattr((yyvsp[(4) - (5)].bases),"private"));
		   }
		   Setattr((yyval.node),"allows_typedef","1");

		   /* preserve the current scope */
		   prev_symtab = Swig_symbol_current();
		  
		   /* If the class name is qualified.  We need to create or lookup namespace/scope entries */
		   scope = resolve_node_scope((yyvsp[(3) - (5)].str));
		   Setfile(scope,cparse_file);
		   Setline(scope,cparse_line);
		   (yyvsp[(3) - (5)].str) = scope;
		   
		   /* support for old nested classes "pseudo" support, such as:

		         %rename(Ala__Ola) Ala::Ola;
			class Ala::Ola {
			public:
			    Ola() {}
		         };

		      this should disappear when a proper implementation is added.
		   */
		   if (nscope_inner && Strcmp(nodeType(nscope_inner),"namespace") != 0) {
		     if (Namespaceprefix) {
		       String *name = NewStringf("%s::%s", Namespaceprefix, (yyvsp[(3) - (5)].str));		       
		       (yyvsp[(3) - (5)].str) = name;
		       Namespaceprefix = 0;
		       nscope_inner = 0;
		     }
		   }
		   Setattr((yyval.node),"name",(yyvsp[(3) - (5)].str));

		   Delete(class_rename);
                   class_rename = make_name((yyval.node),(yyvsp[(3) - (5)].str),0);
		   Classprefix = NewString((yyvsp[(3) - (5)].str));
		   /* Deal with inheritance  */
		   if ((yyvsp[(4) - (5)].bases)) {
		     bases = make_inherit_list((yyvsp[(3) - (5)].str),Getattr((yyvsp[(4) - (5)].bases),"public"));
		   }
		   if (SwigType_istemplate((yyvsp[(3) - (5)].str))) {
		     String *fbase, *tbase, *prefix;
		     prefix = SwigType_templateprefix((yyvsp[(3) - (5)].str));
		     if (Namespaceprefix) {
		       fbase = NewStringf("%s::%s", Namespaceprefix,(yyvsp[(3) - (5)].str));
		       tbase = NewStringf("%s::%s", Namespaceprefix, prefix);
		     } else {
		       fbase = Copy((yyvsp[(3) - (5)].str));
		       tbase = Copy(prefix);
		     }
		     Swig_name_inherit(tbase,fbase);
		     Delete(fbase);
		     Delete(tbase);
		     Delete(prefix);
		   }
                   if (strcmp((yyvsp[(2) - (5)].id),"class") == 0) {
		     cplus_mode = CPLUS_PRIVATE;
		   } else {
		     cplus_mode = CPLUS_PUBLIC;
		   }
		   Swig_symbol_newscope();
		   Swig_symbol_setscopename((yyvsp[(3) - (5)].str));
		   if (bases) {
		     Iterator s;
		     for (s = First(bases); s.item; s = Next(s)) {
		       Symtab *st = Getattr(s.item,"symtab");
		       if (st) {
			 Setfile(st,Getfile(s.item));
			 Setline(st,Getline(s.item));
			 Swig_symbol_inherit(st); 
		       }
		     }
		     Delete(bases);
		   }
		   Delete(Namespaceprefix);
		   Namespaceprefix = Swig_symbol_qualifiedscopename(0);
		   cparse_start_line = cparse_line;

		   /* If there are active template parameters, we need to make sure they are
                      placed in the class symbol table so we can catch shadows */

		   if (template_parameters) {
		     Parm *tp = template_parameters;
		     while(tp) {
		       String *tpname = Copy(Getattr(tp,"name"));
		       Node *tn = new_node("templateparm");
		       Setattr(tn,"name",tpname);
		       Swig_symbol_cadd(tpname,tn);
		       tp = nextSibling(tp);
		       Delete(tpname);
		     }
		   }
		   if (class_level >= max_class_levels) {
		       if (!max_class_levels) {
			   max_class_levels = 16;
		       } else {
			   max_class_levels *= 2;
		       }
		       class_decl = realloc(class_decl, sizeof(Node*) * max_class_levels);
		       if (!class_decl) {
			   Swig_error(cparse_file, cparse_line, "realloc() failed\n");
		       }
		   }
		   class_decl[class_level++] = (yyval.node);
		   inclass = 1;
               }
    break;

  case 137:
#line 3266 "parser.y"
    {
		 Node *p;
		 SwigType *ty;
		 Symtab *cscope = prev_symtab;
		 Node *am = 0;
		 String *scpname = 0;
		 (yyval.node) = class_decl[--class_level];
		 inclass = 0;
		 
		 /* Check for pure-abstract class */
		 Setattr((yyval.node),"abstract", pure_abstract((yyvsp[(7) - (9)].node)));
		 
		 /* This bit of code merges in a previously defined %extend directive (if any) */
		 
		 if (extendhash) {
		   String *clsname = Swig_symbol_qualifiedscopename(0);
		   am = Getattr(extendhash,clsname);
		   if (am) {
		     merge_extensions((yyval.node),am);
		     Delattr(extendhash,clsname);
		   }
		   Delete(clsname);
		 }
		 if (!classes) classes = NewHash();
		 scpname = Swig_symbol_qualifiedscopename(0);
		 Setattr(classes,scpname,(yyval.node));
		 Delete(scpname);

		 appendChild((yyval.node),(yyvsp[(7) - (9)].node));
		 
		 if (am) append_previous_extension((yyval.node),am);

		 p = (yyvsp[(9) - (9)].node);
		 if (p) {
		   set_nextSibling((yyval.node),p);
		 }
		 
		 if (cparse_cplusplus && !cparse_externc) {
		   ty = NewString((yyvsp[(3) - (9)].str));
		 } else {
		   ty = NewStringf("%s %s", (yyvsp[(2) - (9)].id),(yyvsp[(3) - (9)].str));
		 }
		 while (p) {
		   Setattr(p,"storage",(yyvsp[(1) - (9)].id));
		   Setattr(p,"type",ty);
		   p = nextSibling(p);
		 }
		 /* Dump nested classes */
		 {
		   String *name = (yyvsp[(3) - (9)].str);
		   if ((yyvsp[(9) - (9)].node)) {
		     SwigType *decltype = Getattr((yyvsp[(9) - (9)].node),"decl");
		     if (Cmp((yyvsp[(1) - (9)].id),"typedef") == 0) {
		       if (!decltype || !Len(decltype)) {
			 String *cname;
			 name = Getattr((yyvsp[(9) - (9)].node),"name");
			 cname = Copy(name);
			 Setattr((yyval.node),"tdname",cname);
			 Delete(cname);

			 /* Use typedef name as class name */
			 if (class_rename && (Strcmp(class_rename,(yyvsp[(3) - (9)].str)) == 0)) {
			   Delete(class_rename);
			   class_rename = NewString(name);
			 }
			 if (!Getattr(classes,name)) {
			   Setattr(classes,name,(yyval.node));
			 }
			 Setattr((yyval.node),"decl",decltype);
		       }
		     }
		   }
		   appendChild((yyval.node),dump_nested(Char(name)));
		 }

		 if (cplus_mode != CPLUS_PUBLIC) {
		 /* we 'open' the class at the end, to allow %template
		    to add new members */
		   Node *pa = new_node("access");
		   Setattr(pa,"kind","public");
		   cplus_mode = CPLUS_PUBLIC;
		   appendChild((yyval.node),pa);
		   Delete(pa);
		 }

		 Setattr((yyval.node),"symtab",Swig_symbol_popscope());

		 Classprefix = 0;
		 if (nscope_inner) {
		   /* this is tricky */
		   /* we add the declaration in the original namespace */
		   appendChild(nscope_inner,(yyval.node));
		   Swig_symbol_setscope(Getattr(nscope_inner,"symtab"));
		   Delete(Namespaceprefix);
		   Namespaceprefix = Swig_symbol_qualifiedscopename(0);
		   add_symbols((yyval.node));
		   if (nscope) (yyval.node) = nscope;
		   /* but the variable definition in the current scope */
		   Swig_symbol_setscope(cscope);
		   Delete(Namespaceprefix);
		   Namespaceprefix = Swig_symbol_qualifiedscopename(0);
		   add_symbols((yyvsp[(9) - (9)].node));
		 } else {
		   Delete(yyrename);
		   yyrename = Copy(class_rename);
		   Delete(Namespaceprefix);
		   Namespaceprefix = Swig_symbol_qualifiedscopename(0);

		   add_symbols((yyval.node));
		   add_symbols((yyvsp[(9) - (9)].node));
		 }
		 Swig_symbol_setscope(cscope);
		 Delete(Namespaceprefix);
		 Namespaceprefix = Swig_symbol_qualifiedscopename(0);
	       }
    break;

  case 138:
#line 3384 "parser.y"
    {
	       String *unnamed;
	       unnamed = make_unnamed();
	       (yyval.node) = new_node("class");
	       Setline((yyval.node),cparse_start_line);
	       Setattr((yyval.node),"kind",(yyvsp[(2) - (3)].id));
	       Setattr((yyval.node),"storage",(yyvsp[(1) - (3)].id));
	       Setattr((yyval.node),"unnamed",unnamed);
	       Setattr((yyval.node),"allows_typedef","1");
	       Delete(class_rename);
	       class_rename = make_name((yyval.node),0,0);
	       if (strcmp((yyvsp[(2) - (3)].id),"class") == 0) {
		 cplus_mode = CPLUS_PRIVATE;
	       } else {
		 cplus_mode = CPLUS_PUBLIC;
	       }
	       Swig_symbol_newscope();
	       cparse_start_line = cparse_line;
	       if (class_level >= max_class_levels) {
		   if (!max_class_levels) {
		       max_class_levels = 16;
		   } else {
		       max_class_levels *= 2;
		   }
		   class_decl = realloc(class_decl, sizeof(Node*) * max_class_levels);
		   if (!class_decl) {
		       Swig_error(cparse_file, cparse_line, "realloc() failed\n");
		   }
	       }
	       class_decl[class_level++] = (yyval.node);
	       inclass = 1;
	       Classprefix = NewStringEmpty();
	       Delete(Namespaceprefix);
	       Namespaceprefix = Swig_symbol_qualifiedscopename(0);
             }
    break;

  case 139:
#line 3418 "parser.y"
    {
	       String *unnamed;
	       Node *n;
	       Classprefix = 0;
	       (yyval.node) = class_decl[--class_level];
	       inclass = 0;
	       unnamed = Getattr((yyval.node),"unnamed");

	       /* Check for pure-abstract class */
	       Setattr((yyval.node),"abstract", pure_abstract((yyvsp[(5) - (8)].node)));

	       n = new_node("cdecl");
	       Setattr(n,"name",(yyvsp[(7) - (8)].decl).id);
	       Setattr(n,"unnamed",unnamed);
	       Setattr(n,"type",unnamed);
	       Setattr(n,"decl",(yyvsp[(7) - (8)].decl).type);
	       Setattr(n,"parms",(yyvsp[(7) - (8)].decl).parms);
	       Setattr(n,"storage",(yyvsp[(1) - (8)].id));
	       if ((yyvsp[(8) - (8)].node)) {
		 Node *p = (yyvsp[(8) - (8)].node);
		 set_nextSibling(n,p);
		 while (p) {
		   String *type = Copy(unnamed);
		   Setattr(p,"name",(yyvsp[(7) - (8)].decl).id);
		   Setattr(p,"unnamed",unnamed);
		   Setattr(p,"type",type);
		   Delete(type);
		   Setattr(p,"storage",(yyvsp[(1) - (8)].id));
		   p = nextSibling(p);
		 }
	       }
	       set_nextSibling((yyval.node),n);
	       Delete(n);
	       {
		 /* If a proper typedef name was given, we'll use it to set the scope name */
		 String *name = 0;
		 if ((yyvsp[(1) - (8)].id) && (strcmp((yyvsp[(1) - (8)].id),"typedef") == 0)) {
		   if (!Len((yyvsp[(7) - (8)].decl).type)) {	
		     String *scpname = 0;
		     name = (yyvsp[(7) - (8)].decl).id;
		     Setattr((yyval.node),"tdname",name);
		     Setattr((yyval.node),"name",name);
		     Swig_symbol_setscopename(name);

		     /* If a proper name was given, we use that as the typedef, not unnamed */
		     Clear(unnamed);
		     Append(unnamed, name);
		     
		     n = nextSibling(n);
		     set_nextSibling((yyval.node),n);

		     /* Check for previous extensions */
		     if (extendhash) {
		       String *clsname = Swig_symbol_qualifiedscopename(0);
		       Node *am = Getattr(extendhash,clsname);
		       if (am) {
			 /* Merge the extension into the symbol table */
			 merge_extensions((yyval.node),am);
			 append_previous_extension((yyval.node),am);
			 Delattr(extendhash,clsname);
		       }
		       Delete(clsname);
		     }
		     if (!classes) classes = NewHash();
		     scpname = Swig_symbol_qualifiedscopename(0);
		     Setattr(classes,scpname,(yyval.node));
		     Delete(scpname);
		   } else {
		     Swig_symbol_setscopename((char*)"<unnamed>");
		   }
		 }
		 appendChild((yyval.node),(yyvsp[(5) - (8)].node));
		 appendChild((yyval.node),dump_nested(Char(name)));
	       }
	       /* Pop the scope */
	       Setattr((yyval.node),"symtab",Swig_symbol_popscope());
	       if (class_rename) {
		 Delete(yyrename);
		 yyrename = NewString(class_rename);
	       }
	       Delete(Namespaceprefix);
	       Namespaceprefix = Swig_symbol_qualifiedscopename(0);
	       add_symbols((yyval.node));
	       add_symbols(n);
	       Delete(unnamed);
              }
    break;

  case 140:
#line 3506 "parser.y"
    { (yyval.node) = 0; }
    break;

  case 141:
#line 3507 "parser.y"
    {
                        (yyval.node) = new_node("cdecl");
                        Setattr((yyval.node),"name",(yyvsp[(1) - (2)].decl).id);
                        Setattr((yyval.node),"decl",(yyvsp[(1) - (2)].decl).type);
                        Setattr((yyval.node),"parms",(yyvsp[(1) - (2)].decl).parms);
			set_nextSibling((yyval.node),(yyvsp[(2) - (2)].node));
                    }
    break;

  case 142:
#line 3519 "parser.y"
    {
              if ((yyvsp[(1) - (4)].id) && (Strcmp((yyvsp[(1) - (4)].id),"friend") == 0)) {
		/* Ignore */
                (yyval.node) = 0; 
	      } else {
		(yyval.node) = new_node("classforward");
		Setfile((yyval.node),cparse_file);
		Setline((yyval.node),cparse_line);
		Setattr((yyval.node),"kind",(yyvsp[(2) - (4)].id));
		Setattr((yyval.node),"name",(yyvsp[(3) - (4)].str));
		Setattr((yyval.node),"sym:weak", "1");
		add_symbols((yyval.node));
	      }
             }
    break;

  case 143:
#line 3539 "parser.y"
    { template_parameters = (yyvsp[(3) - (4)].tparms); }
    break;

  case 144:
#line 3539 "parser.y"
    {
		      String *tname = 0;
		      int     error = 0;

		      /* check if we get a namespace node with a class declaration, and retrieve the class */
		      Symtab *cscope = Swig_symbol_current();
		      Symtab *sti = 0;
		      Node *ntop = (yyvsp[(6) - (6)].node);
		      Node *ni = ntop;
		      SwigType *ntype = ni ? nodeType(ni) : 0;
		      while (ni && Strcmp(ntype,"namespace") == 0) {
			sti = Getattr(ni,"symtab");
			ni = firstChild(ni);
			ntype = nodeType(ni);
		      }
		      if (sti) {
			Swig_symbol_setscope(sti);
			Delete(Namespaceprefix);
			Namespaceprefix = Swig_symbol_qualifiedscopename(0);
			(yyvsp[(6) - (6)].node) = ni;
		      }

                      template_parameters = 0;
                      (yyval.node) = (yyvsp[(6) - (6)].node);
		      if ((yyval.node)) tname = Getattr((yyval.node),"name");
		      
		      /* Check if the class is a template specialization */
		      if (((yyval.node)) && (Strchr(tname,'<')) && (!is_operator(tname))) {
			/* If a specialization.  Check if defined. */
			Node *tempn = 0;
			{
			  String *tbase = SwigType_templateprefix(tname);
			  tempn = Swig_symbol_clookup_local(tbase,0);
			  if (!tempn || (Strcmp(nodeType(tempn),"template") != 0)) {
			    SWIG_WARN_NODE_BEGIN(tempn);
			    Swig_warning(WARN_PARSE_TEMPLATE_SP_UNDEF, Getfile((yyval.node)),Getline((yyval.node)),"Specialization of non-template '%s'.\n", tbase);
			    SWIG_WARN_NODE_END(tempn);
			    tempn = 0;
			    error = 1;
			  }
			  Delete(tbase);
			}
			Setattr((yyval.node),"specialization","1");
			Setattr((yyval.node),"templatetype",nodeType((yyval.node)));
			set_nodeType((yyval.node),"template");
			/* Template partial specialization */
			if (tempn && ((yyvsp[(3) - (6)].tparms)) && ((yyvsp[(6) - (6)].node))) {
			  List   *tlist;
			  String *targs = SwigType_templateargs(tname);
			  tlist = SwigType_parmlist(targs);
			  /*			  Printf(stdout,"targs = '%s' %s\n", targs, tlist); */
			  if (!Getattr((yyval.node),"sym:weak")) {
			    Setattr((yyval.node),"sym:typename","1");
			  }
			  
			  if (Len(tlist) != ParmList_len(Getattr(tempn,"templateparms"))) {
			    Swig_error(Getfile((yyval.node)),Getline((yyval.node)),"Inconsistent argument count in template partial specialization. %d %d\n", Len(tlist), ParmList_len(Getattr(tempn,"templateparms")));
			    
			  } else {

			  /* This code builds the argument list for the partial template
                             specialization.  This is a little hairy, but the idea is as
                             follows:

                             $3 contains a list of arguments supplied for the template.
                             For example template<class T>.

                             tlist is a list of the specialization arguments--which may be
                             different.  For example class<int,T>.

                             tp is a copy of the arguments in the original template definition.
     
                             The patching algorithm walks through the list of supplied
                             arguments ($3), finds the position in the specialization arguments
                             (tlist), and then patches the name in the argument list of the
                             original template.
			  */

			  {
			    String *pn;
			    Parm *p, *p1;
			    int i, nargs;
			    Parm *tp = CopyParmList(Getattr(tempn,"templateparms"));
			    nargs = Len(tlist);
			    p = (yyvsp[(3) - (6)].tparms);
			    while (p) {
			      for (i = 0; i < nargs; i++){
				pn = Getattr(p,"name");
				if (Strcmp(pn,SwigType_base(Getitem(tlist,i))) == 0) {
				  int j;
				  Parm *p1 = tp;
				  for (j = 0; j < i; j++) {
				    p1 = nextSibling(p1);
				  }
				  Setattr(p1,"name",pn);
				  Setattr(p1,"partialarg","1");
				}
			      }
			      p = nextSibling(p);
			    }
			    p1 = tp;
			    i = 0;
			    while (p1) {
			      if (!Getattr(p1,"partialarg")) {
				Delattr(p1,"name");
				Setattr(p1,"type", Getitem(tlist,i));
			      } 
			      i++;
			      p1 = nextSibling(p1);
			    }
			    Setattr((yyval.node),"templateparms",tp);
			    Delete(tp);
			  }
#if 0
			  /* Patch the parameter list */
			  if (tempn) {
			    Parm *p,*p1;
			    ParmList *tp = CopyParmList(Getattr(tempn,"templateparms"));
			    p = (yyvsp[(3) - (6)].tparms);
			    p1 = tp;
			    while (p && p1) {
			      String *pn = Getattr(p,"name");
			      Printf(stdout,"pn = '%s'\n", pn);
			      if (pn) Setattr(p1,"name",pn);
			      else Delattr(p1,"name");
			      pn = Getattr(p,"type");
			      if (pn) Setattr(p1,"type",pn);
			      p = nextSibling(p);
			      p1 = nextSibling(p1);
			    }
			    Setattr((yyval.node),"templateparms",tp);
			    Delete(tp);
			  } else {
			    Setattr((yyval.node),"templateparms",(yyvsp[(3) - (6)].tparms));
			  }
#endif
			  Delattr((yyval.node),"specialization");
			  Setattr((yyval.node),"partialspecialization","1");
			  /* Create a specialized name for matching */
			  {
			    Parm *p = (yyvsp[(3) - (6)].tparms);
			    String *fname = NewString(Getattr((yyval.node),"name"));
			    String *ffname = 0;

			    char   tmp[32];
			    int    i, ilen;
			    while (p) {
			      String *n = Getattr(p,"name");
			      if (!n) {
				p = nextSibling(p);
				continue;
			      }
			      ilen = Len(tlist);
			      for (i = 0; i < ilen; i++) {
				if (Strstr(Getitem(tlist,i),n)) {
				  sprintf(tmp,"$%d",i+1);
				  Replaceid(fname,n,tmp);
				}
			      }
			      p = nextSibling(p);
			    }
			    /* Patch argument names with typedef */
			    {
			      Iterator tt;
			      List *tparms = SwigType_parmlist(fname);
			      ffname = SwigType_templateprefix(fname);
			      Append(ffname,"<(");
			      for (tt = First(tparms); tt.item; ) {
				SwigType *rtt = Swig_symbol_typedef_reduce(tt.item,0);
				SwigType *ttr = Swig_symbol_type_qualify(rtt,0);
				Append(ffname,ttr);
				tt = Next(tt);
				if (tt.item) Putc(',',ffname);
				Delete(rtt);
				Delete(ttr);
			      }
			      Delete(tparms);
			      Append(ffname,")>");
			    }
			    {
			      String *partials = Getattr(tempn,"partials");
			      if (!partials) {
				partials = NewList();
				Setattr(tempn,"partials",partials);
				Delete(partials);
			      }
			      /*			      Printf(stdout,"partial: fname = '%s', '%s'\n", fname, Swig_symbol_typedef_reduce(fname,0)); */
			      Append(partials,ffname);
			    }
			    Setattr((yyval.node),"partialargs",ffname);
			    Swig_symbol_cadd(ffname,(yyval.node));
			  }
			  }
			  Delete(tlist);
			  Delete(targs);
			} else {
			  /* Need to resolve exact specialization name */
			  /* add default args from generic template */
			  String *ty = Swig_symbol_template_deftype(tname,0);
			  String *fname = Swig_symbol_type_qualify(ty,0);
			  Swig_symbol_cadd(fname,(yyval.node));
			  Delete(ty);
			  Delete(fname);
			}
		      }  else if ((yyval.node)) {
			Setattr((yyval.node),"templatetype",nodeType((yyvsp[(6) - (6)].node)));
			set_nodeType((yyval.node),"template");
			Setattr((yyval.node),"templateparms", (yyvsp[(3) - (6)].tparms));
			if (!Getattr((yyval.node),"sym:weak")) {
			  Setattr((yyval.node),"sym:typename","1");
			}
			add_symbols((yyval.node));
                        default_arguments((yyval.node));
			/* We also place a fully parameterized version in the symbol table */
			{
			  Parm *p;
			  String *fname = NewStringf("%s<(", Getattr((yyval.node),"name"));
			  p = (yyvsp[(3) - (6)].tparms);
			  while (p) {
			    String *n = Getattr(p,"name");
			    if (!n) n = Getattr(p,"type");
			    Append(fname,n);
			    p = nextSibling(p);
			    if (p) Putc(',',fname);
			  }
			  Append(fname,")>");
			  Swig_symbol_cadd(fname,(yyval.node));
			}
		      }
		      (yyval.node) = ntop;
		      Swig_symbol_setscope(cscope);
		      Delete(Namespaceprefix);
		      Namespaceprefix = Swig_symbol_qualifiedscopename(0);
		      if (error) (yyval.node) = 0;
                  }
    break;

  case 145:
#line 3774 "parser.y"
    {
		  Swig_warning(WARN_PARSE_EXPLICIT_TEMPLATE, cparse_file, cparse_line, "Explicit template instantiation ignored.\n");
                   (yyval.node) = 0; 
                }
    break;

  case 146:
#line 3780 "parser.y"
    {
		  (yyval.node) = (yyvsp[(1) - (1)].node);
                }
    break;

  case 147:
#line 3783 "parser.y"
    {
                   (yyval.node) = (yyvsp[(1) - (1)].node);
                }
    break;

  case 148:
#line 3786 "parser.y"
    {
                   (yyval.node) = (yyvsp[(1) - (1)].node);
                }
    break;

  case 149:
#line 3789 "parser.y"
    {
		  (yyval.node) = 0;
                }
    break;

  case 150:
#line 3792 "parser.y"
    {
                  (yyval.node) = (yyvsp[(1) - (1)].node);
                }
    break;

  case 151:
#line 3795 "parser.y"
    {
                  (yyval.node) = (yyvsp[(1) - (1)].node);
                }
    break;

  case 152:
#line 3800 "parser.y"
    {
		   /* Rip out the parameter names */
		  Parm *p = (yyvsp[(1) - (1)].pl);
		  (yyval.tparms) = (yyvsp[(1) - (1)].pl);

		  while (p) {
		    String *name = Getattr(p,"name");
		    if (!name) {
		      /* Hmmm. Maybe it's a 'class T' parameter */
		      char *type = Char(Getattr(p,"type"));
		      /* Template template parameter */
		      if (strncmp(type,"template<class> ",16) == 0) {
			type += 16;
		      }
		      if ((strncmp(type,"class ",6) == 0) || (strncmp(type,"typename ", 9) == 0)) {
			char *t = strchr(type,' ');
			Setattr(p,"name", t+1);
		      } else {
			/*
			 Swig_error(cparse_file, cparse_line, "Missing template parameter name\n");
			 $$.rparms = 0;
			 $$.parms = 0;
			 break; */
		      }
		    }
		    p = nextSibling(p);
		  }
                 }
    break;

  case 153:
#line 3830 "parser.y"
    {
                      set_nextSibling((yyvsp[(1) - (2)].p),(yyvsp[(2) - (2)].pl));
                      (yyval.pl) = (yyvsp[(1) - (2)].p);
                   }
    break;

  case 154:
#line 3834 "parser.y"
    { (yyval.pl) = 0; }
    break;

  case 155:
#line 3837 "parser.y"
    {
		    (yyval.p) = NewParm(NewString((yyvsp[(1) - (1)].id)), 0);
                  }
    break;

  case 156:
#line 3840 "parser.y"
    {
                    (yyval.p) = (yyvsp[(1) - (1)].p);
                  }
    break;

  case 157:
#line 3845 "parser.y"
    {
                         set_nextSibling((yyvsp[(2) - (3)].p),(yyvsp[(3) - (3)].pl));
                         (yyval.pl) = (yyvsp[(2) - (3)].p);
                       }
    break;

  case 158:
#line 3849 "parser.y"
    { (yyval.pl) = 0; }
    break;

  case 159:
#line 3854 "parser.y"
    {
                  String *uname = Swig_symbol_type_qualify((yyvsp[(2) - (3)].str),0);
		  String *name = Swig_scopename_last((yyvsp[(2) - (3)].str));
                  (yyval.node) = new_node("using");
		  Setattr((yyval.node),"uname",uname);
		  Setattr((yyval.node),"name", name);
		  Delete(uname);
		  Delete(name);
		  add_symbols((yyval.node));
             }
    break;

  case 160:
#line 3864 "parser.y"
    {
	       Node *n = Swig_symbol_clookup((yyvsp[(3) - (4)].str),0);
	       if (!n) {
		 Swig_error(cparse_file, cparse_line, "Nothing known about namespace '%s'\n", (yyvsp[(3) - (4)].str));
		 (yyval.node) = 0;
	       } else {

		 while (Strcmp(nodeType(n),"using") == 0) {
		   n = Getattr(n,"node");
		 }
		 if (n) {
		   if (Strcmp(nodeType(n),"namespace") == 0) {
		     Symtab *current = Swig_symbol_current();
		     Symtab *symtab = Getattr(n,"symtab");
		     (yyval.node) = new_node("using");
		     Setattr((yyval.node),"node",n);
		     Setattr((yyval.node),"namespace", (yyvsp[(3) - (4)].str));
		     if (current != symtab) {
		       Swig_symbol_inherit(symtab);
		     }
		   } else {
		     Swig_error(cparse_file, cparse_line, "'%s' is not a namespace.\n", (yyvsp[(3) - (4)].str));
		     (yyval.node) = 0;
		   }
		 } else {
		   (yyval.node) = 0;
		 }
	       }
             }
    break;

  case 161:
#line 3895 "parser.y"
    { 
                Hash *h;
                (yyvsp[(1) - (3)].node) = Swig_symbol_current();
		h = Swig_symbol_clookup((yyvsp[(2) - (3)].str),0);
		if (h && ((yyvsp[(1) - (3)].node) == Getattr(h,"sym:symtab")) && (Strcmp(nodeType(h),"namespace") == 0)) {
		  if (Getattr(h,"alias")) {
		    h = Getattr(h,"namespace");
		    Swig_warning(WARN_PARSE_NAMESPACE_ALIAS, cparse_file, cparse_line, "Namespace alias '%s' not allowed here. Assuming '%s'\n",
				 (yyvsp[(2) - (3)].str), Getattr(h,"name"));
		    (yyvsp[(2) - (3)].str) = Getattr(h,"name");
		  }
		  Swig_symbol_setscope(Getattr(h,"symtab"));
		} else {
		  Swig_symbol_newscope();
		  Swig_symbol_setscopename((yyvsp[(2) - (3)].str));
		}
		Delete(Namespaceprefix);
		Namespaceprefix = Swig_symbol_qualifiedscopename(0);
             }
    break;

  case 162:
#line 3913 "parser.y"
    {
                Node *n = (yyvsp[(5) - (6)].node);
		set_nodeType(n,"namespace");
		Setattr(n,"name",(yyvsp[(2) - (6)].str));
                Setattr(n,"symtab", Swig_symbol_popscope());
		Swig_symbol_setscope((yyvsp[(1) - (6)].node));
		(yyval.node) = n;
		Delete(Namespaceprefix);
		Namespaceprefix = Swig_symbol_qualifiedscopename(0);
		add_symbols((yyval.node));
             }
    break;

  case 163:
#line 3924 "parser.y"
    {
	       Hash *h;
	       (yyvsp[(1) - (2)].node) = Swig_symbol_current();
	       h = Swig_symbol_clookup((char *)"    ",0);
	       if (h && (Strcmp(nodeType(h),"namespace") == 0)) {
		 Swig_symbol_setscope(Getattr(h,"symtab"));
	       } else {
		 Swig_symbol_newscope();
		 /* we don't use "__unnamed__", but a long 'empty' name */
		 Swig_symbol_setscopename("    ");
	       }
	       Namespaceprefix = 0;
             }
    break;

  case 164:
#line 3936 "parser.y"
    {
	       (yyval.node) = (yyvsp[(4) - (5)].node);
	       set_nodeType((yyval.node),"namespace");
	       Setattr((yyval.node),"unnamed","1");
	       Setattr((yyval.node),"symtab", Swig_symbol_popscope());
	       Swig_symbol_setscope((yyvsp[(1) - (5)].node));
	       Delete(Namespaceprefix);
	       Namespaceprefix = Swig_symbol_qualifiedscopename(0);
	       add_symbols((yyval.node));
             }
    break;

  case 165:
#line 3946 "parser.y"
    {
	       /* Namespace alias */
	       Node *n;
	       (yyval.node) = new_node("namespace");
	       Setattr((yyval.node),"name",(yyvsp[(2) - (5)].id));
	       Setattr((yyval.node),"alias",(yyvsp[(4) - (5)].str));
	       n = Swig_symbol_clookup((yyvsp[(4) - (5)].str),0);
	       if (!n) {
		 Swig_error(cparse_file, cparse_line, "Unknown namespace '%s'\n", (yyvsp[(4) - (5)].str));
		 (yyval.node) = 0;
	       } else {
		 if (Strcmp(nodeType(n),"namespace") != 0) {
		   Swig_error(cparse_file, cparse_line, "'%s' is not a namespace\n",(yyvsp[(4) - (5)].str));
		   (yyval.node) = 0;
		 } else {
		   while (Getattr(n,"alias")) {
		     n = Getattr(n,"namespace");
		   }
		   Setattr((yyval.node),"namespace",n);
		   add_symbols((yyval.node));
		   /* Set up a scope alias */
		   Swig_symbol_alias((yyvsp[(2) - (5)].id),Getattr(n,"symtab"));
		 }
	       }
             }
    break;

  case 166:
#line 3973 "parser.y"
    {
                   (yyval.node) = (yyvsp[(1) - (2)].node);
                   /* Insert cpp_member (including any siblings) to the front of the cpp_members linked list */
		   if ((yyval.node)) {
		     Node *p = (yyval.node);
		     Node *pp =0;
		     while (p) {
		       pp = p;
		       p = nextSibling(p);
		     }
		     set_nextSibling(pp,(yyvsp[(2) - (2)].node));
		   } else {
		     (yyval.node) = (yyvsp[(2) - (2)].node);
		   }
             }
    break;

  case 167:
#line 3988 "parser.y"
    { 
                  if (cplus_mode != CPLUS_PUBLIC) {
		     Swig_error(cparse_file,cparse_line,"%%extend can only be used in a public section\n");
		  }
             }
    break;

  case 168:
#line 3992 "parser.y"
    {
	       (yyval.node) = new_node("extend");
	       tag_nodes((yyvsp[(4) - (6)].node),"feature:extend",(char*) "1");
	       appendChild((yyval.node),(yyvsp[(4) - (6)].node));
	       set_nextSibling((yyval.node),(yyvsp[(6) - (6)].node));
	     }
    break;

  case 169:
#line 3998 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 170:
#line 3999 "parser.y"
    { (yyval.node) = 0;}
    break;

  case 171:
#line 4000 "parser.y"
    {
	       int start_line = cparse_line;
	       skip_decl();
	       Swig_error(cparse_file,start_line,"Syntax error in input(3).\n");
	       exit(1);
	       }
    break;

  case 172:
#line 4005 "parser.y"
    { 
		 (yyval.node) = (yyvsp[(3) - (3)].node);
   	     }
    break;

  case 173:
#line 4016 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 174:
#line 4017 "parser.y"
    { 
                 (yyval.node) = (yyvsp[(1) - (1)].node); 
		 if (extendmode) {
		   String *symname;
		   symname= make_name((yyval.node),Getattr((yyval.node),"name"), Getattr((yyval.node),"decl"));
		   if (Strcmp(symname,Getattr((yyval.node),"name")) == 0) {
		     /* No renaming operation.  Set name to class name */
		     Delete(yyrename);
		     yyrename = NewString(Getattr(current_class,"sym:name"));
		   } else {
		     Delete(yyrename);
		     yyrename = symname;
		   }
		 }
		 add_symbols((yyval.node));
                 default_arguments((yyval.node));
             }
    break;

  case 175:
#line 4034 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 176:
#line 4035 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 177:
#line 4036 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 178:
#line 4037 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 179:
#line 4038 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 180:
#line 4039 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 181:
#line 4040 "parser.y"
    { (yyval.node) = 0; }
    break;

  case 182:
#line 4041 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 183:
#line 4042 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 184:
#line 4043 "parser.y"
    { (yyval.node) = 0; }
    break;

  case 185:
#line 4044 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 186:
#line 4045 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 187:
#line 4046 "parser.y"
    { (yyval.node) = 0; }
    break;

  case 188:
#line 4047 "parser.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 189:
#line 4048 "parser.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 190:
#line 4049 "parser.y"
    { (yyval.node) = 0; }
    break;

  case 191:
#line 4058 "parser.y"
    {
              if (Classprefix) {
		 SwigType *decl = NewStringEmpty();
		 (yyval.node) = new_node("constructor");
		 Setattr((yyval.node),"storage",(yyvsp[(1) - (6)].id));
		 Setattr((yyval.node),"name",(yyvsp[(2) - (6)].type));
		 Setattr((yyval.node),"parms",(yyvsp[(4) - (6)].pl));
		 SwigType_add_function(decl,(yyvsp[(4) - (6)].pl));
		 Setattr((yyval.node),"decl",decl);
		 Setattr((yyval.node),"throws",(yyvsp[(6) - (6)].decl).throws);
		 Setattr((yyval.node),"throw",(yyvsp[(6) - (6)].decl).throwf);
		 if (Len(scanner_ccode)) {
		   String *code = Copy(scanner_ccode);
		   Setattr((yyval.node),"code",code);
		   Delete(code);
		 }
		 SetFlag((yyval.node),"feature:new");
	      } else {
		(yyval.node) = 0;
              }
              }
    break;

  case 192:
#line 4083 "parser.y"
    {
               String *name = NewStringf("%s",(yyvsp[(2) - (6)].str));
	       if (*(Char(name)) != '~') Insert(name,0,"~");
               (yyval.node) = new_node("destructor");
	       Setattr((yyval.node),"name",name);
	       Delete(name);
	       if (Len(scanner_ccode)) {
		 String *code = Copy(scanner_ccode);
		 Setattr((yyval.node),"code",code);
		 Delete(code);
	       }
	       {
		 String *decl = NewStringEmpty();
		 SwigType_add_function(decl,(yyvsp[(4) - (6)].pl));
		 Setattr((yyval.node),"decl",decl);
		 Delete(decl);
	       }
	       Setattr((yyval.node),"throws",(yyvsp[(6) - (6)].dtype).throws);
	       Setattr((yyval.node),"throw",(yyvsp[(6) - (6)].dtype).throwf);
	       add_symbols((yyval.node));
	      }
    break;

  case 193:
#line 4107 "parser.y"
    {
		String *name;
		char *c = 0;
		(yyval.node) = new_node("destructor");
	       /* Check for template names.  If the class is a template
		  and the constructor is missing the template part, we
		  add it */
	        if (Classprefix) {
                  c = strchr(Char(Classprefix),'<');
                  if (c && !Strchr((yyvsp[(3) - (7)].str),'<')) {
                    (yyvsp[(3) - (7)].str) = NewStringf("%s%s",(yyvsp[(3) - (7)].str),c);
                  }
		}
		Setattr((yyval.node),"storage","virtual");
	        name = NewStringf("%s",(yyvsp[(3) - (7)].str));
		if (*(Char(name)) != '~') Insert(name,0,"~");
		Setattr((yyval.node),"name",name);
		Delete(name);
		Setattr((yyval.node),"throws",(yyvsp[(7) - (7)].dtype).throws);
		Setattr((yyval.node),"throw",(yyvsp[(7) - (7)].dtype).throwf);
		if ((yyvsp[(7) - (7)].dtype).val) {
		  Setattr((yyval.node),"value","0");
		}
		if (Len(scanner_ccode)) {
		  String *code = Copy(scanner_ccode);
		  Setattr((yyval.node),"code",code);
		  Delete(code);
		}
		{
		  String *decl = NewStringEmpty();
		  SwigType_add_function(decl,(yyvsp[(5) - (7)].pl));
		  Setattr((yyval.node),"decl",decl);
		  Delete(decl);
		}

		add_symbols((yyval.node));
	      }
    break;

  case 194:
#line 4148 "parser.y"
    {
                 (yyval.node) = new_node("cdecl");
                 Setattr((yyval.node),"type",(yyvsp[(3) - (8)].type));
		 Setattr((yyval.node),"name",(yyvsp[(2) - (8)].str));
		 Setattr((yyval.node),"storage",(yyvsp[(1) - (8)].id));

		 SwigType_add_function((yyvsp[(4) - (8)].type),(yyvsp[(6) - (8)].pl));
		 if ((yyvsp[(8) - (8)].dtype).qualifier) {
		   SwigType_push((yyvsp[(4) - (8)].type),(yyvsp[(8) - (8)].dtype).qualifier);
		 }
		 Setattr((yyval.node),"decl",(yyvsp[(4) - (8)].type));
		 Setattr((yyval.node),"parms",(yyvsp[(6) - (8)].pl));
		 Setattr((yyval.node),"conversion_operator","1");
		 add_symbols((yyval.node));
              }
    break;

  case 195:
#line 4163 "parser.y"
    {
		 SwigType *decl;
                 (yyval.node) = new_node("cdecl");
                 Setattr((yyval.node),"type",(yyvsp[(3) - (8)].type));
		 Setattr((yyval.node),"name",(yyvsp[(2) - (8)].str));
		 Setattr((yyval.node),"storage",(yyvsp[(1) - (8)].id));
		 decl = NewStringEmpty();
		 SwigType_add_reference(decl);
		 SwigType_add_function(decl,(yyvsp[(6) - (8)].pl));
		 if ((yyvsp[(8) - (8)].dtype).qualifier) {
		   SwigType_push(decl,(yyvsp[(8) - (8)].dtype).qualifier);
		 }
		 Setattr((yyval.node),"decl",decl);
		 Setattr((yyval.node),"parms",(yyvsp[(6) - (8)].pl));
		 Setattr((yyval.node),"conversion_operator","1");
		 add_symbols((yyval.node));
	       }
    break;

  case 196:
#line 4181 "parser.y"
    {
		String *t = NewStringEmpty();
		(yyval.node) = new_node("cdecl");
		Setattr((yyval.node),"type",(yyvsp[(3) - (7)].type));
		Setattr((yyval.node),"name",(yyvsp[(2) - (7)].str));
		 Setattr((yyval.node),"storage",(yyvsp[(1) - (7)].id));
		SwigType_add_function(t,(yyvsp[(5) - (7)].pl));
		if ((yyvsp[(7) - (7)].dtype).qualifier) {
		  SwigType_push(t,(yyvsp[(7) - (7)].dtype).qualifier);
		}
		Setattr((yyval.node),"decl",t);
		Setattr((yyval.node),"parms",(yyvsp[(5) - (7)].pl));
		Setattr((yyval.node),"conversion_operator","1");
		add_symbols((yyval.node));
              }
    break;

  case 197:
#line 4200 "parser.y"
    {
                 skip_balanced('{','}');
                 (yyval.node) = 0;
               }
    break;

  case 198:
#line 4207 "parser.y"
    { 
                (yyval.node) = new_node("access");
		Setattr((yyval.node),"kind","public");
                cplus_mode = CPLUS_PUBLIC;
              }
    break;

  case 199:
#line 4214 "parser.y"
    { 
                (yyval.node) = new_node("access");
                Setattr((yyval.node),"kind","private");
		cplus_mode = CPLUS_PRIVATE;
	      }
    break;

  case 200:
#line 4222 "parser.y"
    { 
		(yyval.node) = new_node("access");
		Setattr((yyval.node),"kind","protected");
		cplus_mode = CPLUS_PROTECTED;
	      }
    break;

  case 201:
#line 4245 "parser.y"
    { cparse_start_line = cparse_line; skip_balanced('{','}');
	      }
    break;

  case 202:
#line 4246 "parser.y"
    {
	        (yyval.node) = 0;
		if (cplus_mode == CPLUS_PUBLIC) {
		  if ((yyvsp[(6) - (7)].decl).id && strcmp((yyvsp[(2) - (7)].id), "class") != 0) {
		    Nested *n = (Nested *) malloc(sizeof(Nested));
		    n->code = NewStringEmpty();
		    Printv(n->code, "typedef ", (yyvsp[(2) - (7)].id), " ",
			   Char(scanner_ccode), " $classname_", (yyvsp[(6) - (7)].decl).id, ";\n", NIL);

		    n->name = Swig_copy_string((yyvsp[(6) - (7)].decl).id);
		    n->line = cparse_start_line;
		    n->type = NewStringEmpty();
		    n->kind = (yyvsp[(2) - (7)].id);
		    n->unnamed = 0;
		    SwigType_push(n->type, (yyvsp[(6) - (7)].decl).type);
		    n->next = 0;
		    add_nested(n);
		  } else {
		    Swig_warning(WARN_PARSE_NESTED_CLASS, cparse_file, cparse_line, "Nested %s not currently supported (ignored).\n", (yyvsp[(2) - (7)].id));
		    if (strcmp((yyvsp[(2) - (7)].id), "class") == 0) {
		      /* For now, just treat the nested class as a forward
		       * declaration (SF bug #909387). */
		      (yyval.node) = new_node("classforward");
		      Setfile((yyval.node),cparse_file);
		      Setline((yyval.node),cparse_line);
		      Setattr((yyval.node),"kind",(yyvsp[(2) - (7)].id));
		      Setattr((yyval.node),"name",(yyvsp[(3) - (7)].id));
		      Setattr((yyval.node),"sym:weak", "1");
		      add_symbols((yyval.node));
		    }
		  }
		}
	      }
    break;

  case 203:
#line 4280 "parser.y"
    { cparse_start_line = cparse_line; skip_balanced('{','}');
              }
    break;

  case 204:
#line 4281 "parser.y"
    {
	        (yyval.node) = 0;
		if (cplus_mode == CPLUS_PUBLIC) {
		  if (strcmp((yyvsp[(2) - (6)].id),"class") == 0) {
		    Swig_warning(WARN_PARSE_NESTED_CLASS,cparse_file, cparse_line,"Nested class not currently supported (ignored)\n");
		    /* Generate some code for a new class */
		  } else if ((yyvsp[(5) - (6)].decl).id) {
		    /* Generate some code for a new class */
		    Nested *n = (Nested *) malloc(sizeof(Nested));
		    n->code = NewStringEmpty();
		    Printv(n->code, "typedef ", (yyvsp[(2) - (6)].id), " " ,
			    Char(scanner_ccode), " $classname_", (yyvsp[(5) - (6)].decl).id, ";\n",NIL);
		    n->name = Swig_copy_string((yyvsp[(5) - (6)].decl).id);
		    n->line = cparse_start_line;
		    n->type = NewStringEmpty();
		    n->kind = (yyvsp[(2) - (6)].id);
		    n->unnamed = 1;
		    SwigType_push(n->type,(yyvsp[(5) - (6)].decl).type);
		    n->next = 0;
		    add_nested(n);
		  } else {
		    Swig_warning(WARN_PARSE_NESTED_CLASS, cparse_file, cparse_line, "Nested %s not currently supported (ignored).\n", (yyvsp[(2) - (6)].id));
		  }
		}
	      }
    break;

  case 205:
#line 4311 "parser.y"
    { cparse_start_line = cparse_line; skip_balanced('{','}');
              }
    break;

  case 206:
#line 4312 "parser.y"
    {
	        (yyval.node) = 0;
		if (cplus_mode == CPLUS_PUBLIC) {
		  Swig_warning(WARN_PARSE_NESTED_CLASS,cparse_file, cparse_line,"Nested class not currently supported (ignored)\n");
		}
	      }
    break;

  case 207:
#line 4329 "parser.y"
    { (yyval.decl) = (yyvsp[(1) - (1)].decl);}
    break;

  case 208:
#line 4330 "parser.y"
    { (yyval.decl).id = 0; }
    break;

  case 209:
#line 4336 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 210:
#line 4339 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 211:
#line 4343 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 212:
#line 4346 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 213:
#line 4347 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 214:
#line 4348 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 215:
#line 4349 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 216:
#line 4350 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 217:
#line 4351 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 218:
#line 4352 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 219:
#line 4353 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 220:
#line 4356 "parser.y"
    {
	            Clear(scanner_ccode);
		    (yyval.dtype).throws = (yyvsp[(1) - (2)].dtype).throws;
		    (yyval.dtype).throwf = (yyvsp[(1) - (2)].dtype).throwf;
               }
    break;

  case 221:
#line 4361 "parser.y"
    { 
		    skip_balanced('{','}'); 
		    (yyval.dtype).throws = (yyvsp[(1) - (2)].dtype).throws;
		    (yyval.dtype).throwf = (yyvsp[(1) - (2)].dtype).throwf;
	       }
    break;

  case 222:
#line 4368 "parser.y"
    { 
                     Clear(scanner_ccode);
                     (yyval.dtype).val = 0;
                     (yyval.dtype).qualifier = (yyvsp[(1) - (2)].dtype).qualifier;
                     (yyval.dtype).bitfield = 0;
                     (yyval.dtype).throws = (yyvsp[(1) - (2)].dtype).throws;
                     (yyval.dtype).throwf = (yyvsp[(1) - (2)].dtype).throwf;
                }
    break;

  case 223:
#line 4376 "parser.y"
    { 
                     Clear(scanner_ccode);
                     (yyval.dtype).val = (yyvsp[(3) - (4)].dtype).val;
                     (yyval.dtype).qualifier = (yyvsp[(1) - (4)].dtype).qualifier;
                     (yyval.dtype).bitfield = 0;
                     (yyval.dtype).throws = (yyvsp[(1) - (4)].dtype).throws; 
                     (yyval.dtype).throwf = (yyvsp[(1) - (4)].dtype).throwf; 
               }
    break;

  case 224:
#line 4384 "parser.y"
    { 
                     skip_balanced('{','}');
                     (yyval.dtype).val = 0;
                     (yyval.dtype).qualifier = (yyvsp[(1) - (2)].dtype).qualifier;
                     (yyval.dtype).bitfield = 0;
                     (yyval.dtype).throws = (yyvsp[(1) - (2)].dtype).throws; 
                     (yyval.dtype).throwf = (yyvsp[(1) - (2)].dtype).throwf; 
               }
    break;

  case 225:
#line 4395 "parser.y"
    { }
    break;

  case 226:
#line 4401 "parser.y"
    { (yyval.id) = "extern"; }
    break;

  case 227:
#line 4402 "parser.y"
    { 
                   if (strcmp((yyvsp[(2) - (2)].id),"C") == 0) {
		     (yyval.id) = "externc";
		   } else {
		     Swig_warning(WARN_PARSE_UNDEFINED_EXTERN,cparse_file, cparse_line,"Unrecognized extern type \"%s\".\n", (yyvsp[(2) - (2)].id));
		     (yyval.id) = 0;
		   }
               }
    break;

  case 228:
#line 4410 "parser.y"
    { (yyval.id) = "static"; }
    break;

  case 229:
#line 4411 "parser.y"
    { (yyval.id) = "typedef"; }
    break;

  case 230:
#line 4412 "parser.y"
    { (yyval.id) = "virtual"; }
    break;

  case 231:
#line 4413 "parser.y"
    { (yyval.id) = "friend"; }
    break;

  case 232:
#line 4414 "parser.y"
    { (yyval.id) = "explicit"; }
    break;

  case 233:
#line 4415 "parser.y"
    { (yyval.id) = 0; }
    break;

  case 234:
#line 4422 "parser.y"
    {
                 Parm *p;
		 (yyval.pl) = (yyvsp[(1) - (1)].pl);
		 p = (yyvsp[(1) - (1)].pl);
                 while (p) {
		   Replace(Getattr(p,"type"),"typename ", "", DOH_REPLACE_ANY);
		   p = nextSibling(p);
                 }
               }
    break;

  case 235:
#line 4433 "parser.y"
    {
                  set_nextSibling((yyvsp[(1) - (2)].p),(yyvsp[(2) - (2)].pl));
                  (yyval.pl) = (yyvsp[(1) - (2)].p);
		}
    break;

  case 236:
#line 4437 "parser.y"
    { (yyval.pl) = 0; }
    break;

  case 237:
#line 4440 "parser.y"
    {
                 set_nextSibling((yyvsp[(2) - (3)].p),(yyvsp[(3) - (3)].pl));
		 (yyval.pl) = (yyvsp[(2) - (3)].p);
                }
    break;

  case 238:
#line 4444 "parser.y"
    { (yyval.pl) = 0; }
    break;

  case 239:
#line 4448 "parser.y"
    {
                   SwigType_push((yyvsp[(1) - (2)].type),(yyvsp[(2) - (2)].decl).type);
		   (yyval.p) = NewParm((yyvsp[(1) - (2)].type),(yyvsp[(2) - (2)].decl).id);
		   Setfile((yyval.p),cparse_file);
		   Setline((yyval.p),cparse_line);
		   if ((yyvsp[(2) - (2)].decl).defarg) {
		     Setattr((yyval.p),"value",(yyvsp[(2) - (2)].decl).defarg);
		   }
		}
    break;

  case 240:
#line 4458 "parser.y"
    {
                  (yyval.p) = NewParm(NewStringf("template<class> %s %s", (yyvsp[(5) - (7)].id),(yyvsp[(6) - (7)].str)), 0);
		  Setfile((yyval.p),cparse_file);
		  Setline((yyval.p),cparse_line);
                  if ((yyvsp[(7) - (7)].dtype).val) {
                    Setattr((yyval.p),"value",(yyvsp[(7) - (7)].dtype).val);
                  }
                }
    break;

  case 241:
#line 4466 "parser.y"
    {
		  SwigType *t = NewString("v(...)");
		  (yyval.p) = NewParm(t, 0);
		  Setfile((yyval.p),cparse_file);
		  Setline((yyval.p),cparse_line);
		}
    break;

  case 242:
#line 4474 "parser.y"
    {
                 Parm *p;
		 (yyval.p) = (yyvsp[(1) - (1)].p);
		 p = (yyvsp[(1) - (1)].p);
                 while (p) {
		   if (Getattr(p,"type")) {
		     Replace(Getattr(p,"type"),"typename ", "", DOH_REPLACE_ANY);
		   }
		   p = nextSibling(p);
                 }
               }
    break;

  case 243:
#line 4487 "parser.y"
    {
                  set_nextSibling((yyvsp[(1) - (2)].p),(yyvsp[(2) - (2)].p));
                  (yyval.p) = (yyvsp[(1) - (2)].p);
		}
    break;

  case 244:
#line 4491 "parser.y"
    { (yyval.p) = 0; }
    break;

  case 245:
#line 4494 "parser.y"
    {
                 set_nextSibling((yyvsp[(2) - (3)].p),(yyvsp[(3) - (3)].p));
		 (yyval.p) = (yyvsp[(2) - (3)].p);
                }
    break;

  case 246:
#line 4498 "parser.y"
    { (yyval.p) = 0; }
    break;

  case 247:
#line 4502 "parser.y"
    {
		  (yyval.p) = (yyvsp[(1) - (1)].p);
		  {
		    /* We need to make a possible adjustment for integer parameters. */
		    SwigType *type;
		    Node     *n = 0;

		    while (!n) {
		      type = Getattr((yyvsp[(1) - (1)].p),"type");
		      n = Swig_symbol_clookup(type,0);     /* See if we can find a node that matches the typename */
		      if ((n) && (Strcmp(nodeType(n),"cdecl") == 0)) {
			SwigType *decl = Getattr(n,"decl");
			if (!SwigType_isfunction(decl)) {
			  String *value = Getattr(n,"value");
			  if (value) {
			    String *v = Copy(value);
			    Setattr((yyvsp[(1) - (1)].p),"type",v);
			    Delete(v);
			    n = 0;
			  }
			}
		      } else {
			break;
		      }
		    }
		  }

               }
    break;

  case 248:
#line 4530 "parser.y"
    {
                  (yyval.p) = NewParm(0,0);
                  Setfile((yyval.p),cparse_file);
		  Setline((yyval.p),cparse_line);
		  Setattr((yyval.p),"value",(yyvsp[(1) - (1)].dtype).val);
               }
    break;

  case 249:
#line 4538 "parser.y"
    { 
                  (yyval.dtype) = (yyvsp[(2) - (2)].dtype); 
		  if ((yyvsp[(2) - (2)].dtype).type == T_ERROR) {
		    Swig_warning(WARN_PARSE_BAD_DEFAULT,cparse_file, cparse_line, "Can't set default argument (ignored)\n");
		    (yyval.dtype).val = 0;
		    (yyval.dtype).rawval = 0;
		    (yyval.dtype).bitfield = 0;
		    (yyval.dtype).throws = 0;
		    (yyval.dtype).throwf = 0;
		  }
               }
    break;

  case 250:
#line 4549 "parser.y"
    { 
		  (yyval.dtype) = (yyvsp[(2) - (5)].dtype);
		  if ((yyvsp[(2) - (5)].dtype).type == T_ERROR) {
		    Swig_warning(WARN_PARSE_BAD_DEFAULT,cparse_file, cparse_line, "Can't set default argument (ignored)\n");
		    (yyval.dtype) = (yyvsp[(2) - (5)].dtype);
		    (yyval.dtype).val = 0;
		    (yyval.dtype).rawval = 0;
		    (yyval.dtype).bitfield = 0;
		    (yyval.dtype).throws = 0;
		    (yyval.dtype).throwf = 0;
		  } else {
		    (yyval.dtype).val = NewStringf("%s[%s]",(yyvsp[(2) - (5)].dtype).val,(yyvsp[(4) - (5)].dtype).val); 
		  }		  
               }
    break;

  case 251:
#line 4563 "parser.y"
    {
		 skip_balanced('{','}');
		 (yyval.dtype).val = 0;
		 (yyval.dtype).rawval = 0;
                 (yyval.dtype).type = T_INT;
		 (yyval.dtype).bitfield = 0;
		 (yyval.dtype).throws = 0;
		 (yyval.dtype).throwf = 0;
	       }
    break;

  case 252:
#line 4572 "parser.y"
    { 
		 (yyval.dtype).val = 0;
		 (yyval.dtype).rawval = 0;
		 (yyval.dtype).type = 0;
		 (yyval.dtype).bitfield = (yyvsp[(2) - (2)].dtype).val;
		 (yyval.dtype).throws = 0;
		 (yyval.dtype).throwf = 0;
	       }
    break;

  case 253:
#line 4580 "parser.y"
    {
                 (yyval.dtype).val = 0;
                 (yyval.dtype).rawval = 0;
                 (yyval.dtype).type = T_INT;
		 (yyval.dtype).bitfield = 0;
		 (yyval.dtype).throws = 0;
		 (yyval.dtype).throwf = 0;
               }
    break;

  case 254:
#line 4590 "parser.y"
    {
                 (yyval.decl) = (yyvsp[(1) - (2)].decl);
		 (yyval.decl).defarg = (yyvsp[(2) - (2)].dtype).rawval ? (yyvsp[(2) - (2)].dtype).rawval : (yyvsp[(2) - (2)].dtype).val;
            }
    break;

  case 255:
#line 4594 "parser.y"
    {
              (yyval.decl) = (yyvsp[(1) - (2)].decl);
	      (yyval.decl).defarg = (yyvsp[(2) - (2)].dtype).rawval ? (yyvsp[(2) - (2)].dtype).rawval : (yyvsp[(2) - (2)].dtype).val;
            }
    break;

  case 256:
#line 4598 "parser.y"
    {
   	      (yyval.decl).type = 0;
              (yyval.decl).id = 0;
	      (yyval.decl).defarg = (yyvsp[(1) - (1)].dtype).rawval ? (yyvsp[(1) - (1)].dtype).rawval : (yyvsp[(1) - (1)].dtype).val;
            }
    break;

  case 257:
#line 4605 "parser.y"
    {
                 (yyval.decl) = (yyvsp[(1) - (1)].decl);
		 if (SwigType_isfunction((yyvsp[(1) - (1)].decl).type)) {
		   Delete(SwigType_pop_function((yyvsp[(1) - (1)].decl).type));
		 } else if (SwigType_isarray((yyvsp[(1) - (1)].decl).type)) {
		   SwigType *ta = SwigType_pop_arrays((yyvsp[(1) - (1)].decl).type);
		   if (SwigType_isfunction((yyvsp[(1) - (1)].decl).type)) {
		     Delete(SwigType_pop_function((yyvsp[(1) - (1)].decl).type));
		   } else {
		     (yyval.decl).parms = 0;
		   }
		   SwigType_push((yyvsp[(1) - (1)].decl).type,ta);
		   Delete(ta);
		 } else {
		   (yyval.decl).parms = 0;
		 }
            }
    break;

  case 258:
#line 4622 "parser.y"
    {
              (yyval.decl) = (yyvsp[(1) - (1)].decl);
	      if (SwigType_isfunction((yyvsp[(1) - (1)].decl).type)) {
		Delete(SwigType_pop_function((yyvsp[(1) - (1)].decl).type));
	      } else if (SwigType_isarray((yyvsp[(1) - (1)].decl).type)) {
		SwigType *ta = SwigType_pop_arrays((yyvsp[(1) - (1)].decl).type);
		if (SwigType_isfunction((yyvsp[(1) - (1)].decl).type)) {
		  Delete(SwigType_pop_function((yyvsp[(1) - (1)].decl).type));
		} else {
		  (yyval.decl).parms = 0;
		}
		SwigType_push((yyvsp[(1) - (1)].decl).type,ta);
		Delete(ta);
	      } else {
		(yyval.decl).parms = 0;
	      }
            }
    break;

  case 259:
#line 4639 "parser.y"
    {
   	      (yyval.decl).type = 0;
              (yyval.decl).id = 0;
	      (yyval.decl).parms = 0;
	      }
    break;

  case 260:
#line 4647 "parser.y"
    {
              (yyval.decl) = (yyvsp[(2) - (2)].decl);
	      if ((yyval.decl).type) {
		SwigType_push((yyvsp[(1) - (2)].type),(yyval.decl).type);
		Delete((yyval.decl).type);
	      }
	      (yyval.decl).type = (yyvsp[(1) - (2)].type);
           }
    break;

  case 261:
#line 4655 "parser.y"
    {
              (yyval.decl) = (yyvsp[(3) - (3)].decl);
	      SwigType_add_reference((yyvsp[(1) - (3)].type));
              if ((yyval.decl).type) {
		SwigType_push((yyvsp[(1) - (3)].type),(yyval.decl).type);
		Delete((yyval.decl).type);
	      }
	      (yyval.decl).type = (yyvsp[(1) - (3)].type);
           }
    break;

  case 262:
#line 4664 "parser.y"
    {
              (yyval.decl) = (yyvsp[(1) - (1)].decl);
	      if (!(yyval.decl).type) (yyval.decl).type = NewStringEmpty();
           }
    break;

  case 263:
#line 4668 "parser.y"
    { 
	     (yyval.decl) = (yyvsp[(2) - (2)].decl);
	     (yyval.decl).type = NewStringEmpty();
	     SwigType_add_reference((yyval.decl).type);
	     if ((yyvsp[(2) - (2)].decl).type) {
	       SwigType_push((yyval.decl).type,(yyvsp[(2) - (2)].decl).type);
	       Delete((yyvsp[(2) - (2)].decl).type);
	     }
           }
    break;

  case 264:
#line 4677 "parser.y"
    { 
	     SwigType *t = NewStringEmpty();

	     (yyval.decl) = (yyvsp[(3) - (3)].decl);
	     SwigType_add_memberpointer(t,(yyvsp[(1) - (3)].str));
	     if ((yyval.decl).type) {
	       SwigType_push(t,(yyval.decl).type);
	       Delete((yyval.decl).type);
	     }
	     (yyval.decl).type = t;
	     }
    break;

  case 265:
#line 4688 "parser.y"
    { 
	     SwigType *t = NewStringEmpty();
	     (yyval.decl) = (yyvsp[(4) - (4)].decl);
	     SwigType_add_memberpointer(t,(yyvsp[(2) - (4)].str));
	     SwigType_push((yyvsp[(1) - (4)].type),t);
	     if ((yyval.decl).type) {
	       SwigType_push((yyvsp[(1) - (4)].type),(yyval.decl).type);
	       Delete((yyval.decl).type);
	     }
	     (yyval.decl).type = (yyvsp[(1) - (4)].type);
	     Delete(t);
	   }
    break;

  case 266:
#line 4700 "parser.y"
    { 
	     (yyval.decl) = (yyvsp[(5) - (5)].decl);
	     SwigType_add_memberpointer((yyvsp[(1) - (5)].type),(yyvsp[(2) - (5)].str));
	     SwigType_add_reference((yyvsp[(1) - (5)].type));
	     if ((yyval.decl).type) {
	       SwigType_push((yyvsp[(1) - (5)].type),(yyval.decl).type);
	       Delete((yyval.decl).type);
	     }
	     (yyval.decl).type = (yyvsp[(1) - (5)].type);
	   }
    break;

  case 267:
#line 4710 "parser.y"
    { 
	     SwigType *t = NewStringEmpty();
	     (yyval.decl) = (yyvsp[(4) - (4)].decl);
	     SwigType_add_memberpointer(t,(yyvsp[(1) - (4)].str));
	     SwigType_add_reference(t);
	     if ((yyval.decl).type) {
	       SwigType_push(t,(yyval.decl).type);
	       Delete((yyval.decl).type);
	     } 
	     (yyval.decl).type = t;
	   }
    break;

  case 268:
#line 4723 "parser.y"
    {
                /* Note: This is non-standard C.  Template declarator is allowed to follow an identifier */
                 (yyval.decl).id = Char((yyvsp[(1) - (1)].str));
		 (yyval.decl).type = 0;
		 (yyval.decl).parms = 0;
		 (yyval.decl).have_parms = 0;
                  }
    break;

  case 269:
#line 4730 "parser.y"
    {
                  (yyval.decl).id = Char(NewStringf("~%s",(yyvsp[(2) - (2)].str)));
                  (yyval.decl).type = 0;
                  (yyval.decl).parms = 0;
                  (yyval.decl).have_parms = 0;
                  }
    break;

  case 270:
#line 4738 "parser.y"
    {
                  (yyval.decl).id = Char((yyvsp[(2) - (3)].str));
                  (yyval.decl).type = 0;
                  (yyval.decl).parms = 0;
                  (yyval.decl).have_parms = 0;
                  }
    break;

  case 271:
#line 4754 "parser.y"
    {
		    (yyval.decl) = (yyvsp[(3) - (4)].decl);
		    if ((yyval.decl).type) {
		      SwigType_push((yyvsp[(2) - (4)].type),(yyval.decl).type);
		      Delete((yyval.decl).type);
		    }
		    (yyval.decl).type = (yyvsp[(2) - (4)].type);
                  }
    break;

  case 272:
#line 4762 "parser.y"
    {
		    SwigType *t;
		    (yyval.decl) = (yyvsp[(4) - (5)].decl);
		    t = NewStringEmpty();
		    SwigType_add_memberpointer(t,(yyvsp[(2) - (5)].str));
		    if ((yyval.decl).type) {
		      SwigType_push(t,(yyval.decl).type);
		      Delete((yyval.decl).type);
		    }
		    (yyval.decl).type = t;
		    }
    break;

  case 273:
#line 4773 "parser.y"
    { 
		    SwigType *t;
		    (yyval.decl) = (yyvsp[(1) - (3)].decl);
		    t = NewStringEmpty();
		    SwigType_add_array(t,(char*)"");
		    if ((yyval.decl).type) {
		      SwigType_push(t,(yyval.decl).type);
		      Delete((yyval.decl).type);
		    }
		    (yyval.decl).type = t;
                  }
    break;

  case 274:
#line 4784 "parser.y"
    { 
		    SwigType *t;
		    (yyval.decl) = (yyvsp[(1) - (4)].decl);
		    t = NewStringEmpty();
		    SwigType_add_array(t,(yyvsp[(3) - (4)].dtype).val);
		    if ((yyval.decl).type) {
		      SwigType_push(t,(yyval.decl).type);
		      Delete((yyval.decl).type);
		    }
		    (yyval.decl).type = t;
                  }
    break;

  case 275:
#line 4795 "parser.y"
    {
		    SwigType *t;
                    (yyval.decl) = (yyvsp[(1) - (4)].decl);
		    t = NewStringEmpty();
		    SwigType_add_function(t,(yyvsp[(3) - (4)].pl));
		    if (!(yyval.decl).have_parms) {
		      (yyval.decl).parms = (yyvsp[(3) - (4)].pl);
		      (yyval.decl).have_parms = 1;
		    }
		    if (!(yyval.decl).type) {
		      (yyval.decl).type = t;
		    } else {
		      SwigType_push(t, (yyval.decl).type);
		      Delete((yyval.decl).type);
		      (yyval.decl).type = t;
		    }
		  }
    break;

  case 276:
#line 4814 "parser.y"
    {
                /* Note: This is non-standard C.  Template declarator is allowed to follow an identifier */
                 (yyval.decl).id = Char((yyvsp[(1) - (1)].str));
		 (yyval.decl).type = 0;
		 (yyval.decl).parms = 0;
		 (yyval.decl).have_parms = 0;
                  }
    break;

  case 277:
#line 4822 "parser.y"
    {
                  (yyval.decl).id = Char(NewStringf("~%s",(yyvsp[(2) - (2)].str)));
                  (yyval.decl).type = 0;
                  (yyval.decl).parms = 0;
                  (yyval.decl).have_parms = 0;
                  }
    break;

  case 278:
#line 4839 "parser.y"
    {
		    (yyval.decl) = (yyvsp[(3) - (4)].decl);
		    if ((yyval.decl).type) {
		      SwigType_push((yyvsp[(2) - (4)].type),(yyval.decl).type);
		      Delete((yyval.decl).type);
		    }
		    (yyval.decl).type = (yyvsp[(2) - (4)].type);
                  }
    break;

  case 279:
#line 4847 "parser.y"
    {
                    (yyval.decl) = (yyvsp[(3) - (4)].decl);
		    if (!(yyval.decl).type) {
		      (yyval.decl).type = NewStringEmpty();
		    }
		    SwigType_add_reference((yyval.decl).type);
                  }
    break;

  case 280:
#line 4854 "parser.y"
    {
		    SwigType *t;
		    (yyval.decl) = (yyvsp[(4) - (5)].decl);
		    t = NewStringEmpty();
		    SwigType_add_memberpointer(t,(yyvsp[(2) - (5)].str));
		    if ((yyval.decl).type) {
		      SwigType_push(t,(yyval.decl).type);
		      Delete((yyval.decl).type);
		    }
		    (yyval.decl).type = t;
		    }
    break;

  case 281:
#line 4865 "parser.y"
    { 
		    SwigType *t;
		    (yyval.decl) = (yyvsp[(1) - (3)].decl);
		    t = NewStringEmpty();
		    SwigType_add_array(t,(char*)"");
		    if ((yyval.decl).type) {
		      SwigType_push(t,(yyval.decl).type);
		      Delete((yyval.decl).type);
		    }
		    (yyval.decl).type = t;
                  }
    break;

  case 282:
#line 4876 "parser.y"
    { 
		    SwigType *t;
		    (yyval.decl) = (yyvsp[(1) - (4)].decl);
		    t = NewStringEmpty();
		    SwigType_add_array(t,(yyvsp[(3) - (4)].dtype).val);
		    if ((yyval.decl).type) {
		      SwigType_push(t,(yyval.decl).type);
		      Delete((yyval.decl).type);
		    }
		    (yyval.decl).type = t;
                  }
    break;

  case 283:
#line 4887 "parser.y"
    {
		    SwigType *t;
                    (yyval.decl) = (yyvsp[(1) - (4)].decl);
		    t = NewStringEmpty();
		    SwigType_add_function(t,(yyvsp[(3) - (4)].pl));
		    if (!(yyval.decl).have_parms) {
		      (yyval.decl).parms = (yyvsp[(3) - (4)].pl);
		      (yyval.decl).have_parms = 1;
		    }
		    if (!(yyval.decl).type) {
		      (yyval.decl).type = t;
		    } else {
		      SwigType_push(t, (yyval.decl).type);
		      Delete((yyval.decl).type);
		      (yyval.decl).type = t;
		    }
		  }
    break;

  case 284:
#line 4906 "parser.y"
    {
		    (yyval.decl).type = (yyvsp[(1) - (1)].type);
                    (yyval.decl).id = 0;
		    (yyval.decl).parms = 0;
		    (yyval.decl).have_parms = 0;
                  }
    break;

  case 285:
#line 4912 "parser.y"
    { 
                     (yyval.decl) = (yyvsp[(2) - (2)].decl);
                     SwigType_push((yyvsp[(1) - (2)].type),(yyvsp[(2) - (2)].decl).type);
		     (yyval.decl).type = (yyvsp[(1) - (2)].type);
		     Delete((yyvsp[(2) - (2)].decl).type);
                  }
    break;

  case 286:
#line 4918 "parser.y"
    {
		    (yyval.decl).type = (yyvsp[(1) - (2)].type);
		    SwigType_add_reference((yyval.decl).type);
		    (yyval.decl).id = 0;
		    (yyval.decl).parms = 0;
		    (yyval.decl).have_parms = 0;
		  }
    break;

  case 287:
#line 4925 "parser.y"
    {
		    (yyval.decl) = (yyvsp[(3) - (3)].decl);
		    SwigType_add_reference((yyvsp[(1) - (3)].type));
		    if ((yyval.decl).type) {
		      SwigType_push((yyvsp[(1) - (3)].type),(yyval.decl).type);
		      Delete((yyval.decl).type);
		    }
		    (yyval.decl).type = (yyvsp[(1) - (3)].type);
                  }
    break;

  case 288:
#line 4934 "parser.y"
    {
		    (yyval.decl) = (yyvsp[(1) - (1)].decl);
                  }
    break;

  case 289:
#line 4937 "parser.y"
    {
		    (yyval.decl) = (yyvsp[(2) - (2)].decl);
		    (yyval.decl).type = NewStringEmpty();
		    SwigType_add_reference((yyval.decl).type);
		    if ((yyvsp[(2) - (2)].decl).type) {
		      SwigType_push((yyval.decl).type,(yyvsp[(2) - (2)].decl).type);
		      Delete((yyvsp[(2) - (2)].decl).type);
		    }
                  }
    break;

  case 290:
#line 4946 "parser.y"
    { 
                    (yyval.decl).id = 0;
                    (yyval.decl).parms = 0;
		    (yyval.decl).have_parms = 0;
                    (yyval.decl).type = NewStringEmpty();
		    SwigType_add_reference((yyval.decl).type);
                  }
    break;

  case 291:
#line 4953 "parser.y"
    { 
		    (yyval.decl).type = NewStringEmpty();
                    SwigType_add_memberpointer((yyval.decl).type,(yyvsp[(1) - (2)].str));
                    (yyval.decl).id = 0;
                    (yyval.decl).parms = 0;
		    (yyval.decl).have_parms = 0;
      	          }
    break;

  case 292:
#line 4960 "parser.y"
    { 
		    SwigType *t = NewStringEmpty();
                    (yyval.decl).type = (yyvsp[(1) - (3)].type);
		    (yyval.decl).id = 0;
		    (yyval.decl).parms = 0;
		    (yyval.decl).have_parms = 0;
		    SwigType_add_memberpointer(t,(yyvsp[(2) - (3)].str));
		    SwigType_push((yyval.decl).type,t);
		    Delete(t);
                  }
    break;

  case 293:
#line 4970 "parser.y"
    { 
		    (yyval.decl) = (yyvsp[(4) - (4)].decl);
		    SwigType_add_memberpointer((yyvsp[(1) - (4)].type),(yyvsp[(2) - (4)].str));
		    if ((yyval.decl).type) {
		      SwigType_push((yyvsp[(1) - (4)].type),(yyval.decl).type);
		      Delete((yyval.decl).type);
		    }
		    (yyval.decl).type = (yyvsp[(1) - (4)].type);
                  }
    break;

  case 294:
#line 4981 "parser.y"
    { 
		    SwigType *t;
		    (yyval.decl) = (yyvsp[(1) - (3)].decl);
		    t = NewStringEmpty();
		    SwigType_add_array(t,(char*)"");
		    if ((yyval.decl).type) {
		      SwigType_push(t,(yyval.decl).type);
		      Delete((yyval.decl).type);
		    }
		    (yyval.decl).type = t;
                  }
    break;

  case 295:
#line 4992 "parser.y"
    { 
		    SwigType *t;
		    (yyval.decl) = (yyvsp[(1) - (4)].decl);
		    t = NewStringEmpty();
		    SwigType_add_array(t,(yyvsp[(3) - (4)].dtype).val);
		    if ((yyval.decl).type) {
		      SwigType_push(t,(yyval.decl).type);
		      Delete((yyval.decl).type);
		    }
		    (yyval.decl).type = t;
                  }
    break;

  case 296:
#line 5003 "parser.y"
    { 
		    (yyval.decl).type = NewStringEmpty();
		    (yyval.decl).id = 0;
		    (yyval.decl).parms = 0;
		    (yyval.decl).have_parms = 0;
		    SwigType_add_array((yyval.decl).type,(char*)"");
                  }
    break;

  case 297:
#line 5010 "parser.y"
    { 
		    (yyval.decl).type = NewStringEmpty();
		    (yyval.decl).id = 0;
		    (yyval.decl).parms = 0;
		    (yyval.decl).have_parms = 0;
		    SwigType_add_array((yyval.decl).type,(yyvsp[(2) - (3)].dtype).val);
		  }
    break;

  case 298:
#line 5017 "parser.y"
    {
                    (yyval.decl) = (yyvsp[(2) - (3)].decl);
		  }
    break;

  case 299:
#line 5020 "parser.y"
    {
		    SwigType *t;
                    (yyval.decl) = (yyvsp[(1) - (4)].decl);
		    t = NewStringEmpty();
                    SwigType_add_function(t,(yyvsp[(3) - (4)].pl));
		    if (!(yyval.decl).type) {
		      (yyval.decl).type = t;
		    } else {
		      SwigType_push(t,(yyval.decl).type);
		      Delete((yyval.decl).type);
		      (yyval.decl).type = t;
		    }
		    if (!(yyval.decl).have_parms) {
		      (yyval.decl).parms = (yyvsp[(3) - (4)].pl);
		      (yyval.decl).have_parms = 1;
		    }
		  }
    break;

  case 300:
#line 5037 "parser.y"
    {
                    (yyval.decl).type = NewStringEmpty();
                    SwigType_add_function((yyval.decl).type,(yyvsp[(2) - (3)].pl));
		    (yyval.decl).parms = (yyvsp[(2) - (3)].pl);
		    (yyval.decl).have_parms = 1;
		    (yyval.decl).id = 0;
                  }
    break;

  case 301:
#line 5047 "parser.y"
    { 
               (yyval.type) = NewStringEmpty();
               SwigType_add_pointer((yyval.type));
	       SwigType_push((yyval.type),(yyvsp[(2) - (3)].str));
	       SwigType_push((yyval.type),(yyvsp[(3) - (3)].type));
	       Delete((yyvsp[(3) - (3)].type));
           }
    break;

  case 302:
#line 5054 "parser.y"
    {
	     (yyval.type) = NewStringEmpty();
	     SwigType_add_pointer((yyval.type));
	     SwigType_push((yyval.type),(yyvsp[(2) - (2)].type));
	     Delete((yyvsp[(2) - (2)].type));
	     }
    break;

  case 303:
#line 5060 "parser.y"
    { 
	     	(yyval.type) = NewStringEmpty();	
		SwigType_add_pointer((yyval.type));
	        SwigType_push((yyval.type),(yyvsp[(2) - (2)].str));
           }
    break;

  case 304:
#line 5065 "parser.y"
    {
	      (yyval.type) = NewStringEmpty();
	      SwigType_add_pointer((yyval.type));
           }
    break;

  case 305:
#line 5071 "parser.y"
    {
	          (yyval.str) = NewStringEmpty();
	          if ((yyvsp[(1) - (1)].id)) SwigType_add_qualifier((yyval.str),(yyvsp[(1) - (1)].id));
               }
    break;

  case 306:
#line 5075 "parser.y"
    {
		  (yyval.str) = (yyvsp[(2) - (2)].str);
	          if ((yyvsp[(1) - (2)].id)) SwigType_add_qualifier((yyval.str),(yyvsp[(1) - (2)].id));
               }
    break;

  case 307:
#line 5081 "parser.y"
    { (yyval.id) = "const"; }
    break;

  case 308:
#line 5082 "parser.y"
    { (yyval.id) = "volatile"; }
    break;

  case 309:
#line 5083 "parser.y"
    { (yyval.id) = 0; }
    break;

  case 310:
#line 5089 "parser.y"
    {
                   (yyval.type) = (yyvsp[(1) - (1)].type);
                   Replace((yyval.type),"typename ","", DOH_REPLACE_ANY);
                }
    break;

  case 311:
#line 5095 "parser.y"
    {
                   (yyval.type) = (yyvsp[(2) - (2)].type);
	           SwigType_push((yyval.type),(yyvsp[(1) - (2)].str));
               }
    break;

  case 312:
#line 5099 "parser.y"
    { (yyval.type) = (yyvsp[(1) - (1)].type); }
    break;

  case 313:
#line 5100 "parser.y"
    {
		  (yyval.type) = (yyvsp[(1) - (2)].type);
	          SwigType_push((yyval.type),(yyvsp[(2) - (2)].str));
	       }
    break;

  case 314:
#line 5104 "parser.y"
    {
		  (yyval.type) = (yyvsp[(2) - (3)].type);
	          SwigType_push((yyval.type),(yyvsp[(3) - (3)].str));
	          SwigType_push((yyval.type),(yyvsp[(1) - (3)].str));
	       }
    break;

  case 315:
#line 5111 "parser.y"
    { (yyval.type) = (yyvsp[(1) - (1)].type);
                  /* Printf(stdout,"primitive = '%s'\n", $$);*/
                }
    break;

  case 316:
#line 5114 "parser.y"
    { (yyval.type) = (yyvsp[(1) - (1)].type); }
    break;

  case 317:
#line 5115 "parser.y"
    { (yyval.type) = (yyvsp[(1) - (1)].type); }
    break;

  case 318:
#line 5116 "parser.y"
    { (yyval.type) = NewStringf("%s%s",(yyvsp[(1) - (2)].type),(yyvsp[(2) - (2)].id)); }
    break;

  case 319:
#line 5117 "parser.y"
    { (yyval.type) = NewStringf("enum %s", (yyvsp[(2) - (2)].str)); }
    break;

  case 320:
#line 5118 "parser.y"
    { (yyval.type) = (yyvsp[(1) - (1)].type); }
    break;

  case 321:
#line 5120 "parser.y"
    {
		  (yyval.type) = (yyvsp[(1) - (1)].str);
               }
    break;

  case 322:
#line 5123 "parser.y"
    { 
		 (yyval.type) = NewStringf("%s %s", (yyvsp[(1) - (2)].id), (yyvsp[(2) - (2)].str));
               }
    break;

  case 323:
#line 5128 "parser.y"
    {
		 if (!(yyvsp[(1) - (1)].ptype).type) (yyvsp[(1) - (1)].ptype).type = NewString("int");
		 if ((yyvsp[(1) - (1)].ptype).us) {
		   (yyval.type) = NewStringf("%s %s", (yyvsp[(1) - (1)].ptype).us, (yyvsp[(1) - (1)].ptype).type);
		   Delete((yyvsp[(1) - (1)].ptype).us);
                   Delete((yyvsp[(1) - (1)].ptype).type);
		 } else {
                   (yyval.type) = (yyvsp[(1) - (1)].ptype).type;
		 }
		 if (Cmp((yyval.type),"signed int") == 0) {
		   Delete((yyval.type));
		   (yyval.type) = NewString("int");
                 } else if (Cmp((yyval.type),"signed long") == 0) {
		   Delete((yyval.type));
                   (yyval.type) = NewString("long");
                 } else if (Cmp((yyval.type),"signed short") == 0) {
		   Delete((yyval.type));
		   (yyval.type) = NewString("short");
		 } else if (Cmp((yyval.type),"signed long long") == 0) {
		   Delete((yyval.type));
		   (yyval.type) = NewString("long long");
		 }
               }
    break;

  case 324:
#line 5153 "parser.y"
    { 
                 (yyval.ptype) = (yyvsp[(1) - (1)].ptype);
               }
    break;

  case 325:
#line 5156 "parser.y"
    {
                    if ((yyvsp[(1) - (2)].ptype).us && (yyvsp[(2) - (2)].ptype).us) {
		      Swig_error(cparse_file, cparse_line, "Extra %s specifier.\n", (yyvsp[(2) - (2)].ptype).us);
		    }
                    (yyval.ptype) = (yyvsp[(2) - (2)].ptype);
                    if ((yyvsp[(1) - (2)].ptype).us) (yyval.ptype).us = (yyvsp[(1) - (2)].ptype).us;
		    if ((yyvsp[(1) - (2)].ptype).type) {
		      if (!(yyvsp[(2) - (2)].ptype).type) (yyval.ptype).type = (yyvsp[(1) - (2)].ptype).type;
		      else {
			int err = 0;
			if ((Cmp((yyvsp[(1) - (2)].ptype).type,"long") == 0)) {
			  if ((Cmp((yyvsp[(2) - (2)].ptype).type,"long") == 0) || (Strncmp((yyvsp[(2) - (2)].ptype).type,"double",6) == 0)) {
			    (yyval.ptype).type = NewStringf("long %s", (yyvsp[(2) - (2)].ptype).type);
			  } else if (Cmp((yyvsp[(2) - (2)].ptype).type,"int") == 0) {
			    (yyval.ptype).type = (yyvsp[(1) - (2)].ptype).type;
			  } else {
			    err = 1;
			  }
			} else if ((Cmp((yyvsp[(1) - (2)].ptype).type,"short")) == 0) {
			  if (Cmp((yyvsp[(2) - (2)].ptype).type,"int") == 0) {
			    (yyval.ptype).type = (yyvsp[(1) - (2)].ptype).type;
			  } else {
			    err = 1;
			  }
			} else if (Cmp((yyvsp[(1) - (2)].ptype).type,"int") == 0) {
			  (yyval.ptype).type = (yyvsp[(2) - (2)].ptype).type;
			} else if (Cmp((yyvsp[(1) - (2)].ptype).type,"double") == 0) {
			  if (Cmp((yyvsp[(2) - (2)].ptype).type,"long") == 0) {
			    (yyval.ptype).type = NewString("long double");
			  } else if (Cmp((yyvsp[(2) - (2)].ptype).type,"complex") == 0) {
			    (yyval.ptype).type = NewString("double complex");
			  } else {
			    err = 1;
			  }
			} else if (Cmp((yyvsp[(1) - (2)].ptype).type,"float") == 0) {
			  if (Cmp((yyvsp[(2) - (2)].ptype).type,"complex") == 0) {
			    (yyval.ptype).type = NewString("float complex");
			  } else {
			    err = 1;
			  }
			} else if (Cmp((yyvsp[(1) - (2)].ptype).type,"complex") == 0) {
			  (yyval.ptype).type = NewStringf("%s complex", (yyvsp[(2) - (2)].ptype).type);
			} else {
			  err = 1;
			}
			if (err) {
			  Swig_error(cparse_file, cparse_line, "Extra %s specifier.\n", (yyvsp[(1) - (2)].ptype).type);
			}
		      }
		    }
               }
    break;

  case 326:
#line 5210 "parser.y"
    { 
		    (yyval.ptype).type = NewString("int");
                    (yyval.ptype).us = 0;
               }
    break;

  case 327:
#line 5214 "parser.y"
    { 
                    (yyval.ptype).type = NewString("short");
                    (yyval.ptype).us = 0;
                }
    break;

  case 328:
#line 5218 "parser.y"
    { 
                    (yyval.ptype).type = NewString("long");
                    (yyval.ptype).us = 0;
                }
    break;

  case 329:
#line 5222 "parser.y"
    { 
                    (yyval.ptype).type = NewString("char");
                    (yyval.ptype).us = 0;
                }
    break;

  case 330:
#line 5226 "parser.y"
    { 
                    (yyval.ptype).type = NewString("wchar_t");
                    (yyval.ptype).us = 0;
                }
    break;

  case 331:
#line 5230 "parser.y"
    { 
                    (yyval.ptype).type = NewString("float");
                    (yyval.ptype).us = 0;
                }
    break;

  case 332:
#line 5234 "parser.y"
    { 
                    (yyval.ptype).type = NewString("double");
                    (yyval.ptype).us = 0;
                }
    break;

  case 333:
#line 5238 "parser.y"
    { 
                    (yyval.ptype).us = NewString("signed");
                    (yyval.ptype).type = 0;
                }
    break;

  case 334:
#line 5242 "parser.y"
    { 
                    (yyval.ptype).us = NewString("unsigned");
                    (yyval.ptype).type = 0;
                }
    break;

  case 335:
#line 5246 "parser.y"
    { 
                    (yyval.ptype).type = NewString("complex");
                    (yyval.ptype).us = 0;
                }
    break;

  case 336:
#line 5250 "parser.y"
    { 
                    (yyval.ptype).type = NewString("__int8");
                    (yyval.ptype).us = 0;
                }
    break;

  case 337:
#line 5254 "parser.y"
    { 
                    (yyval.ptype).type = NewString("__int16");
                    (yyval.ptype).us = 0;
                }
    break;

  case 338:
#line 5258 "parser.y"
    { 
                    (yyval.ptype).type = NewString("__int32");
                    (yyval.ptype).us = 0;
                }
    break;

  case 339:
#line 5262 "parser.y"
    { 
                    (yyval.ptype).type = NewString("__int64");
                    (yyval.ptype).us = 0;
                }
    break;

  case 340:
#line 5268 "parser.y"
    { /* scanner_check_typedef(); */ }
    break;

  case 341:
#line 5268 "parser.y"
    {
                   (yyval.dtype) = (yyvsp[(2) - (2)].dtype);
		   if ((yyval.dtype).type == T_STRING) {
		     (yyval.dtype).rawval = NewStringf("\"%(escape)s\"",(yyval.dtype).val);
		   } else if ((yyval.dtype).type != T_CHAR) {
		     (yyval.dtype).rawval = 0;
		   }
		   (yyval.dtype).bitfield = 0;
		   (yyval.dtype).throws = 0;
		   (yyval.dtype).throwf = 0;
		   scanner_ignore_typedef();
                }
    break;

  case 342:
#line 5294 "parser.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id); }
    break;

  case 343:
#line 5295 "parser.y"
    { (yyval.id) = (char *) 0;}
    break;

  case 344:
#line 5298 "parser.y"
    { 

                  /* Ignore if there is a trailing comma in the enum list */
                  if ((yyvsp[(3) - (3)].node)) {
                    Node *leftSibling = Getattr((yyvsp[(1) - (3)].node),"_last");
                    if (!leftSibling) {
                      leftSibling=(yyvsp[(1) - (3)].node);
                    }
                    set_nextSibling(leftSibling,(yyvsp[(3) - (3)].node));
                    Setattr((yyvsp[(1) - (3)].node),"_last",(yyvsp[(3) - (3)].node));
                  }
		  (yyval.node) = (yyvsp[(1) - (3)].node);
               }
    break;

  case 345:
#line 5311 "parser.y"
    { 
                   (yyval.node) = (yyvsp[(1) - (1)].node); 
                   if ((yyvsp[(1) - (1)].node)) {
                     Setattr((yyvsp[(1) - (1)].node),"_last",(yyvsp[(1) - (1)].node));
                   }
               }
    break;

  case 346:
#line 5319 "parser.y"
    {
		   SwigType *type = NewSwigType(T_INT);
		   (yyval.node) = new_node("enumitem");
		   Setattr((yyval.node),"name",(yyvsp[(1) - (1)].id));
		   Setattr((yyval.node),"type",type);
		   SetFlag((yyval.node),"feature:immutable");
		   Delete(type);
		 }
    break;

  case 347:
#line 5327 "parser.y"
    {
		   (yyval.node) = new_node("enumitem");
		   Setattr((yyval.node),"name",(yyvsp[(1) - (3)].id));
		   Setattr((yyval.node),"enumvalue", (yyvsp[(3) - (3)].dtype).val);
	           if ((yyvsp[(3) - (3)].dtype).type == T_CHAR) {
		     SwigType *type = NewSwigType(T_CHAR);
		     Setattr((yyval.node),"value",NewStringf("\'%(escape)s\'", (yyvsp[(3) - (3)].dtype).val));
		     Setattr((yyval.node),"type",type);
		     Delete(type);
		   } else {
		     SwigType *type = NewSwigType(T_INT);
		     Setattr((yyval.node),"value",(yyvsp[(1) - (3)].id));
		     Setattr((yyval.node),"type",type);
		     Delete(type);
		   }
		   SetFlag((yyval.node),"feature:immutable");
                 }
    break;

  case 348:
#line 5344 "parser.y"
    { (yyval.node) = 0; }
    break;

  case 349:
#line 5347 "parser.y"
    {
                   (yyval.dtype) = (yyvsp[(1) - (1)].dtype);
		   if (((yyval.dtype).type != T_INT) && ((yyval.dtype).type != T_UINT) &&
		       ((yyval.dtype).type != T_LONG) && ((yyval.dtype).type != T_ULONG) &&
		       ((yyval.dtype).type != T_SHORT) && ((yyval.dtype).type != T_USHORT) &&
		       ((yyval.dtype).type != T_SCHAR) && ((yyval.dtype).type != T_UCHAR) &&
		       ((yyval.dtype).type != T_CHAR)) {
		     Swig_error(cparse_file,cparse_line,"Type error. Expecting an int\n");
		   }
		   if ((yyval.dtype).type == T_CHAR) (yyval.dtype).type = T_INT;
                }
    break;

  case 350:
#line 5362 "parser.y"
    { (yyval.dtype) = (yyvsp[(1) - (1)].dtype); }
    break;

  case 351:
#line 5363 "parser.y"
    {
		 Node *n;
		 (yyval.dtype).val = (yyvsp[(1) - (1)].type);
		 (yyval.dtype).type = T_INT;
		 /* Check if value is in scope */
		 n = Swig_symbol_clookup((yyvsp[(1) - (1)].type),0);
		 if (n) {
                   /* A band-aid for enum values used in expressions. */
                   if (Strcmp(nodeType(n),"enumitem") == 0) {
                     String *q = Swig_symbol_qualified(n);
                     if (q) {
                       (yyval.dtype).val = NewStringf("%s::%s", q, Getattr(n,"name"));
                       Delete(q);
                     }
                   }
		 }
               }
    break;

  case 352:
#line 5382 "parser.y"
    { (yyval.dtype) = (yyvsp[(1) - (1)].dtype); }
    break;

  case 353:
#line 5383 "parser.y"
    {
		    (yyval.dtype).val = NewString((yyvsp[(1) - (1)].id));
                    (yyval.dtype).type = T_STRING;
               }
    break;

  case 354:
#line 5387 "parser.y"
    {
		  SwigType_push((yyvsp[(3) - (5)].type),(yyvsp[(4) - (5)].decl).type);
		  (yyval.dtype).val = NewStringf("sizeof(%s)",SwigType_str((yyvsp[(3) - (5)].type),0));
		  (yyval.dtype).type = T_ULONG;
               }
    break;

  case 355:
#line 5392 "parser.y"
    { (yyval.dtype) = (yyvsp[(1) - (1)].dtype); }
    break;

  case 356:
#line 5393 "parser.y"
    {
		  (yyval.dtype).val = NewString((yyvsp[(1) - (1)].str));
		  if (Len((yyval.dtype).val)) {
		    (yyval.dtype).rawval = NewStringf("'%(escape)s'", (yyval.dtype).val);
		  } else {
		    (yyval.dtype).rawval = NewString("'\\0'");
		  }
		  (yyval.dtype).type = T_CHAR;
		  (yyval.dtype).bitfield = 0;
		  (yyval.dtype).throws = 0;
		  (yyval.dtype).throwf = 0;
	       }
    break;

  case 357:
#line 5407 "parser.y"
    {
   	            (yyval.dtype).val = NewStringf("(%s)",(yyvsp[(2) - (3)].dtype).val);
		    (yyval.dtype).type = (yyvsp[(2) - (3)].dtype).type;
   	       }
    break;

  case 358:
#line 5414 "parser.y"
    {
                 (yyval.dtype) = (yyvsp[(4) - (4)].dtype);
		 if ((yyvsp[(4) - (4)].dtype).type != T_STRING) {
		   (yyval.dtype).val = NewStringf("(%s) %s", SwigType_str((yyvsp[(2) - (4)].dtype).val,0), (yyvsp[(4) - (4)].dtype).val);
		 }
 	       }
    break;

  case 359:
#line 5420 "parser.y"
    {
                 (yyval.dtype) = (yyvsp[(5) - (5)].dtype);
		 if ((yyvsp[(5) - (5)].dtype).type != T_STRING) {
		   SwigType_push((yyvsp[(2) - (5)].dtype).val,(yyvsp[(3) - (5)].type));
		   (yyval.dtype).val = NewStringf("(%s) %s", SwigType_str((yyvsp[(2) - (5)].dtype).val,0), (yyvsp[(5) - (5)].dtype).val);
		 }
 	       }
    break;

  case 360:
#line 5427 "parser.y"
    {
                 (yyval.dtype) = (yyvsp[(5) - (5)].dtype);
		 if ((yyvsp[(5) - (5)].dtype).type != T_STRING) {
		   SwigType_add_reference((yyvsp[(2) - (5)].dtype).val);
		   (yyval.dtype).val = NewStringf("(%s) %s", SwigType_str((yyvsp[(2) - (5)].dtype).val,0), (yyvsp[(5) - (5)].dtype).val);
		 }
 	       }
    break;

  case 361:
#line 5434 "parser.y"
    {
                 (yyval.dtype) = (yyvsp[(6) - (6)].dtype);
		 if ((yyvsp[(6) - (6)].dtype).type != T_STRING) {
		   SwigType_push((yyvsp[(2) - (6)].dtype).val,(yyvsp[(3) - (6)].type));
		   SwigType_add_reference((yyvsp[(2) - (6)].dtype).val);
		   (yyval.dtype).val = NewStringf("(%s) %s", SwigType_str((yyvsp[(2) - (6)].dtype).val,0), (yyvsp[(6) - (6)].dtype).val);
		 }
 	       }
    break;

  case 362:
#line 5442 "parser.y"
    {
		 (yyval.dtype) = (yyvsp[(2) - (2)].dtype);
                 (yyval.dtype).val = NewStringf("&%s",(yyvsp[(2) - (2)].dtype).val);
	       }
    break;

  case 363:
#line 5446 "parser.y"
    {
		 (yyval.dtype) = (yyvsp[(2) - (2)].dtype);
                 (yyval.dtype).val = NewStringf("*%s",(yyvsp[(2) - (2)].dtype).val);
	       }
    break;

  case 364:
#line 5452 "parser.y"
    { (yyval.dtype) = (yyvsp[(1) - (1)].dtype); }
    break;

  case 365:
#line 5453 "parser.y"
    { (yyval.dtype) = (yyvsp[(1) - (1)].dtype); }
    break;

  case 366:
#line 5454 "parser.y"
    { (yyval.dtype) = (yyvsp[(1) - (1)].dtype); }
    break;

  case 367:
#line 5455 "parser.y"
    { (yyval.dtype) = (yyvsp[(1) - (1)].dtype); }
    break;

  case 368:
#line 5456 "parser.y"
    { (yyval.dtype) = (yyvsp[(1) - (1)].dtype); }
    break;

  case 369:
#line 5457 "parser.y"
    { (yyval.dtype) = (yyvsp[(1) - (1)].dtype); }
    break;

  case 370:
#line 5458 "parser.y"
    { (yyval.dtype) = (yyvsp[(1) - (1)].dtype); }
    break;

  case 371:
#line 5461 "parser.y"
    {
		 (yyval.dtype).val = NewStringf("%s+%s",(yyvsp[(1) - (3)].dtype).val,(yyvsp[(3) - (3)].dtype).val);
		 (yyval.dtype).type = promote((yyvsp[(1) - (3)].dtype).type,(yyvsp[(3) - (3)].dtype).type);
	       }
    break;

  case 372:
#line 5465 "parser.y"
    {
		 (yyval.dtype).val = NewStringf("%s-%s",(yyvsp[(1) - (3)].dtype).val,(yyvsp[(3) - (3)].dtype).val);
		 (yyval.dtype).type = promote((yyvsp[(1) - (3)].dtype).type,(yyvsp[(3) - (3)].dtype).type);
	       }
    break;

  case 373:
#line 5469 "parser.y"
    {
		 (yyval.dtype).val = NewStringf("%s*%s",(yyvsp[(1) - (3)].dtype).val,(yyvsp[(3) - (3)].dtype).val);
		 (yyval.dtype).type = promote((yyvsp[(1) - (3)].dtype).type,(yyvsp[(3) - (3)].dtype).type);
	       }
    break;

  case 374:
#line 5473 "parser.y"
    {
		 (yyval.dtype).val = NewStringf("%s/%s",(yyvsp[(1) - (3)].dtype).val,(yyvsp[(3) - (3)].dtype).val);
		 (yyval.dtype).type = promote((yyvsp[(1) - (3)].dtype).type,(yyvsp[(3) - (3)].dtype).type);
	       }
    break;

  case 375:
#line 5477 "parser.y"
    {
		 (yyval.dtype).val = NewStringf("%s%%%s",(yyvsp[(1) - (3)].dtype).val,(yyvsp[(3) - (3)].dtype).val);
		 (yyval.dtype).type = promote((yyvsp[(1) - (3)].dtype).type,(yyvsp[(3) - (3)].dtype).type);
	       }
    break;

  case 376:
#line 5481 "parser.y"
    {
		 (yyval.dtype).val = NewStringf("%s&%s",(yyvsp[(1) - (3)].dtype).val,(yyvsp[(3) - (3)].dtype).val);
		 (yyval.dtype).type = promote((yyvsp[(1) - (3)].dtype).type,(yyvsp[(3) - (3)].dtype).type);
	       }
    break;

  case 377:
#line 5485 "parser.y"
    {
		 (yyval.dtype).val = NewStringf("%s|%s",(yyvsp[(1) - (3)].dtype).val,(yyvsp[(3) - (3)].dtype).val);
		 (yyval.dtype).type = promote((yyvsp[(1) - (3)].dtype).type,(yyvsp[(3) - (3)].dtype).type);
	       }
    break;

  case 378:
#line 5489 "parser.y"
    {
		 (yyval.dtype).val = NewStringf("%s^%s",(yyvsp[(1) - (3)].dtype).val,(yyvsp[(3) - (3)].dtype).val);
		 (yyval.dtype).type = promote((yyvsp[(1) - (3)].dtype).type,(yyvsp[(3) - (3)].dtype).type);
	       }
    break;

  case 379:
#line 5493 "parser.y"
    {
		 (yyval.dtype).val = NewStringf("%s << %s",(yyvsp[(1) - (3)].dtype).val,(yyvsp[(3) - (3)].dtype).val);
		 (yyval.dtype).type = promote_type((yyvsp[(1) - (3)].dtype).type);
	       }
    break;

  case 380:
#line 5497 "parser.y"
    {
		 (yyval.dtype).val = NewStringf("%s >> %s",(yyvsp[(1) - (3)].dtype).val,(yyvsp[(3) - (3)].dtype).val);
		 (yyval.dtype).type = promote_type((yyvsp[(1) - (3)].dtype).type);
	       }
    break;

  case 381:
#line 5501 "parser.y"
    {
		 (yyval.dtype).val = NewStringf("%s&&%s",(yyvsp[(1) - (3)].dtype).val,(yyvsp[(3) - (3)].dtype).val);
		 (yyval.dtype).type = T_INT;
	       }
    break;

  case 382:
#line 5505 "parser.y"
    {
		 (yyval.dtype).val = NewStringf("%s||%s",(yyvsp[(1) - (3)].dtype).val,(yyvsp[(3) - (3)].dtype).val);
		 (yyval.dtype).type = T_INT;
	       }
    break;

  case 383:
#line 5509 "parser.y"
    {
		 (yyval.dtype).val = NewStringf("%s==%s",(yyvsp[(1) - (3)].dtype).val,(yyvsp[(3) - (3)].dtype).val);
		 (yyval.dtype).type = T_INT;
	       }
    break;

  case 384:
#line 5513 "parser.y"
    {
		 (yyval.dtype).val = NewStringf("%s!=%s",(yyvsp[(1) - (3)].dtype).val,(yyvsp[(3) - (3)].dtype).val);
		 (yyval.dtype).type = T_INT;
	       }
    break;

  case 385:
#line 5527 "parser.y"
    {
		 /* Putting >= in the expression literally causes an infinite
		  * loop somewhere in the type system.  Just workaround for now
		  * - SWIG_GE is defined in swiglabels.swg. */
		 (yyval.dtype).val = NewStringf("%s SWIG_GE %s", (yyvsp[(1) - (3)].dtype).val, (yyvsp[(3) - (3)].dtype).val);
		 (yyval.dtype).type = T_INT;
	       }
    break;

  case 386:
#line 5534 "parser.y"
    {
		 (yyval.dtype).val = NewStringf("%s SWIG_LE %s", (yyvsp[(1) - (3)].dtype).val, (yyvsp[(3) - (3)].dtype).val);
		 (yyval.dtype).type = T_INT;
	       }
    break;

  case 387:
#line 5538 "parser.y"
    {
		 (yyval.dtype).val = NewStringf("%s?%s:%s", (yyvsp[(1) - (5)].dtype).val, (yyvsp[(3) - (5)].dtype).val, (yyvsp[(5) - (5)].dtype).val);
		 /* This may not be exactly right, but is probably good enough
		  * for the purposes of parsing constant expressions. */
		 (yyval.dtype).type = promote((yyvsp[(3) - (5)].dtype).type, (yyvsp[(5) - (5)].dtype).type);
	       }
    break;

  case 388:
#line 5544 "parser.y"
    {
		 (yyval.dtype).val = NewStringf("-%s",(yyvsp[(2) - (2)].dtype).val);
		 (yyval.dtype).type = (yyvsp[(2) - (2)].dtype).type;
	       }
    break;

  case 389:
#line 5548 "parser.y"
    {
                 (yyval.dtype).val = NewStringf("+%s",(yyvsp[(2) - (2)].dtype).val);
		 (yyval.dtype).type = (yyvsp[(2) - (2)].dtype).type;
	       }
    break;

  case 390:
#line 5552 "parser.y"
    {
		 (yyval.dtype).val = NewStringf("~%s",(yyvsp[(2) - (2)].dtype).val);
		 (yyval.dtype).type = (yyvsp[(2) - (2)].dtype).type;
	       }
    break;

  case 391:
#line 5556 "parser.y"
    {
                 (yyval.dtype).val = NewStringf("!%s",(yyvsp[(2) - (2)].dtype).val);
		 (yyval.dtype).type = T_INT;
	       }
    break;

  case 392:
#line 5560 "parser.y"
    {
		 String *qty;
                 skip_balanced('(',')');
		 qty = Swig_symbol_type_qualify((yyvsp[(1) - (2)].type),0);
		 if (SwigType_istemplate(qty)) {
		   String *nstr = SwigType_namestr(qty);
		   Delete(qty);
		   qty = nstr;
		 }
		 (yyval.dtype).val = NewStringf("%s%s",qty,scanner_ccode);
		 Clear(scanner_ccode);
		 (yyval.dtype).type = T_INT;
		 Delete(qty);
               }
    break;

  case 393:
#line 5576 "parser.y"
    {
		 (yyval.bases) = (yyvsp[(1) - (1)].bases);
               }
    break;

  case 394:
#line 5581 "parser.y"
    { inherit_list = 1; }
    break;

  case 395:
#line 5581 "parser.y"
    { (yyval.bases) = (yyvsp[(3) - (3)].bases); inherit_list = 0; }
    break;

  case 396:
#line 5582 "parser.y"
    { (yyval.bases) = 0; }
    break;

  case 397:
#line 5585 "parser.y"
    {
		   Hash *list = NewHash();
		   Node *base = (yyvsp[(1) - (1)].node);
		   Node *name = Getattr(base,"name");
		   List *lpublic = NewList();
		   List *lprotected = NewList();
		   List *lprivate = NewList();
		   Setattr(list,"public",lpublic);
		   Setattr(list,"protected",lprotected);
		   Setattr(list,"private",lprivate);
		   Delete(lpublic);
		   Delete(lprotected);
		   Delete(lprivate);
		   Append(Getattr(list,Getattr(base,"access")),name);
	           (yyval.bases) = list;
               }
    break;

  case 398:
#line 5602 "parser.y"
    {
		   Hash *list = (yyvsp[(1) - (3)].bases);
		   Node *base = (yyvsp[(3) - (3)].node);
		   Node *name = Getattr(base,"name");
		   Append(Getattr(list,Getattr(base,"access")),name);
                   (yyval.bases) = list;
               }
    break;

  case 399:
#line 5611 "parser.y"
    {
		 (yyval.node) = NewHash();
		 Setfile((yyval.node),cparse_file);
		 Setline((yyval.node),cparse_line);
		 Setattr((yyval.node),"name",(yyvsp[(2) - (2)].str));
                 if (last_cpptype && (Strcmp(last_cpptype,"struct") != 0)) {
		   Setattr((yyval.node),"access","private");
		   Swig_warning(WARN_PARSE_NO_ACCESS,cparse_file,cparse_line,
				"No access specifier given for base class %s (ignored).\n",(yyvsp[(2) - (2)].str));
                 } else {
		   Setattr((yyval.node),"access","public");
		 }
               }
    break;

  case 400:
#line 5624 "parser.y"
    {
		 (yyval.node) = NewHash();
		 Setfile((yyval.node),cparse_file);
		 Setline((yyval.node),cparse_line);
		 Setattr((yyval.node),"name",(yyvsp[(4) - (4)].str));
		 Setattr((yyval.node),"access",(yyvsp[(2) - (4)].id));
	         if (Strcmp((yyvsp[(2) - (4)].id),"public") != 0) {
		   Swig_warning(WARN_PARSE_PRIVATE_INHERIT, cparse_file, 
				cparse_line,"%s inheritance ignored.\n", (yyvsp[(2) - (4)].id));
		 }
               }
    break;

  case 401:
#line 5637 "parser.y"
    { (yyval.id) = (char*)"public"; }
    break;

  case 402:
#line 5638 "parser.y"
    { (yyval.id) = (char*)"private"; }
    break;

  case 403:
#line 5639 "parser.y"
    { (yyval.id) = (char*)"protected"; }
    break;

  case 404:
#line 5643 "parser.y"
    { 
                   (yyval.id) = (char*)"class"; 
		   if (!inherit_list) last_cpptype = (yyval.id);
               }
    break;

  case 405:
#line 5647 "parser.y"
    { 
                   (yyval.id) = (char *)"typename"; 
		   if (!inherit_list) last_cpptype = (yyval.id);
               }
    break;

  case 406:
#line 5653 "parser.y"
    {
                 (yyval.id) = (yyvsp[(1) - (1)].id);
               }
    break;

  case 407:
#line 5656 "parser.y"
    { 
                   (yyval.id) = (char*)"struct"; 
		   if (!inherit_list) last_cpptype = (yyval.id);
               }
    break;

  case 408:
#line 5660 "parser.y"
    {
                   (yyval.id) = (char*)"union"; 
		   if (!inherit_list) last_cpptype = (yyval.id);
               }
    break;

  case 411:
#line 5670 "parser.y"
    {
                    (yyval.dtype).qualifier = (yyvsp[(1) - (1)].str);
                    (yyval.dtype).throws = 0;
                    (yyval.dtype).throwf = 0;
               }
    break;

  case 412:
#line 5675 "parser.y"
    {
                    (yyval.dtype).qualifier = 0;
                    (yyval.dtype).throws = (yyvsp[(3) - (4)].pl);
                    (yyval.dtype).throwf = NewString("1");
               }
    break;

  case 413:
#line 5680 "parser.y"
    {
                    (yyval.dtype).qualifier = (yyvsp[(1) - (5)].str);
                    (yyval.dtype).throws = (yyvsp[(4) - (5)].pl);
                    (yyval.dtype).throwf = NewString("1");
               }
    break;

  case 414:
#line 5685 "parser.y"
    { 
                    (yyval.dtype).qualifier = 0; 
                    (yyval.dtype).throws = 0;
                    (yyval.dtype).throwf = 0;
               }
    break;

  case 415:
#line 5692 "parser.y"
    { 
                    Clear(scanner_ccode); 
                    (yyval.decl).have_parms = 0; 
                    (yyval.decl).defarg = 0; 
		    (yyval.decl).throws = (yyvsp[(1) - (3)].dtype).throws;
		    (yyval.decl).throwf = (yyvsp[(1) - (3)].dtype).throwf;
               }
    break;

  case 416:
#line 5699 "parser.y"
    { 
                    skip_balanced('{','}'); 
                    (yyval.decl).have_parms = 0; 
                    (yyval.decl).defarg = 0; 
                    (yyval.decl).throws = (yyvsp[(1) - (3)].dtype).throws;
                    (yyval.decl).throwf = (yyvsp[(1) - (3)].dtype).throwf;
               }
    break;

  case 417:
#line 5706 "parser.y"
    { 
                    Clear(scanner_ccode); 
                    (yyval.decl).parms = (yyvsp[(2) - (4)].pl); 
                    (yyval.decl).have_parms = 1; 
                    (yyval.decl).defarg = 0; 
		    (yyval.decl).throws = 0;
		    (yyval.decl).throwf = 0;
               }
    break;

  case 418:
#line 5714 "parser.y"
    {
                    skip_balanced('{','}'); 
                    (yyval.decl).parms = (yyvsp[(2) - (4)].pl); 
                    (yyval.decl).have_parms = 1; 
                    (yyval.decl).defarg = 0; 
                    (yyval.decl).throws = 0;
                    (yyval.decl).throwf = 0;
               }
    break;

  case 419:
#line 5722 "parser.y"
    { 
                    (yyval.decl).have_parms = 0; 
                    (yyval.decl).defarg = (yyvsp[(2) - (3)].dtype).val; 
                    (yyval.decl).throws = 0;
                    (yyval.decl).throwf = 0;
               }
    break;

  case 424:
#line 5738 "parser.y"
    {
	            skip_balanced('(',')');
                    Clear(scanner_ccode);
            	}
    break;

  case 425:
#line 5744 "parser.y"
    { 
                     String *s = NewStringEmpty();
                     SwigType_add_template(s,(yyvsp[(2) - (3)].p));
                     (yyval.id) = Char(s);
		     scanner_last_id(1);
                 }
    break;

  case 426:
#line 5750 "parser.y"
    { (yyval.id) = (char*)"";  }
    break;

  case 427:
#line 5753 "parser.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id); }
    break;

  case 428:
#line 5754 "parser.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id); }
    break;

  case 429:
#line 5757 "parser.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id); }
    break;

  case 430:
#line 5758 "parser.y"
    { (yyval.id) = 0; }
    break;

  case 431:
#line 5761 "parser.y"
    { 
                  (yyval.str) = 0;
		  if (!(yyval.str)) (yyval.str) = NewStringf("%s%s", (yyvsp[(1) - (2)].str),(yyvsp[(2) - (2)].str));
      	          Delete((yyvsp[(2) - (2)].str));
               }
    break;

  case 432:
#line 5766 "parser.y"
    { 
		 (yyval.str) = NewStringf("::%s%s",(yyvsp[(3) - (4)].str),(yyvsp[(4) - (4)].str));
                 Delete((yyvsp[(4) - (4)].str));
               }
    break;

  case 433:
#line 5770 "parser.y"
    {
		 (yyval.str) = NewString((yyvsp[(1) - (1)].str));
   	       }
    break;

  case 434:
#line 5773 "parser.y"
    {
		 (yyval.str) = NewStringf("::%s",(yyvsp[(3) - (3)].str));
               }
    break;

  case 435:
#line 5776 "parser.y"
    {
                 (yyval.str) = NewString((yyvsp[(1) - (1)].str));
	       }
    break;

  case 436:
#line 5779 "parser.y"
    {
                 (yyval.str) = NewStringf("::%s",(yyvsp[(3) - (3)].str));
               }
    break;

  case 437:
#line 5784 "parser.y"
    {
                   (yyval.str) = NewStringf("::%s%s",(yyvsp[(2) - (3)].str),(yyvsp[(3) - (3)].str));
		   Delete((yyvsp[(3) - (3)].str));
               }
    break;

  case 438:
#line 5788 "parser.y"
    {
                   (yyval.str) = NewStringf("::%s",(yyvsp[(2) - (2)].str));
               }
    break;

  case 439:
#line 5791 "parser.y"
    {
                   (yyval.str) = NewStringf("::%s",(yyvsp[(2) - (2)].str));
               }
    break;

  case 440:
#line 5798 "parser.y"
    {
		 (yyval.str) = NewStringf("::~%s",(yyvsp[(2) - (2)].str));
               }
    break;

  case 441:
#line 5804 "parser.y"
    {
                  (yyval.str) = NewStringf("%s%s",(yyvsp[(1) - (2)].id),(yyvsp[(2) - (2)].id));
		  /*		  if (Len($2)) {
		    scanner_last_id(1);
		    } */
              }
    break;

  case 442:
#line 5813 "parser.y"
    { 
                  (yyval.str) = 0;
		  if (!(yyval.str)) (yyval.str) = NewStringf("%s%s", (yyvsp[(1) - (2)].id),(yyvsp[(2) - (2)].str));
      	          Delete((yyvsp[(2) - (2)].str));
               }
    break;

  case 443:
#line 5818 "parser.y"
    { 
		 (yyval.str) = NewStringf("::%s%s",(yyvsp[(3) - (4)].id),(yyvsp[(4) - (4)].str));
                 Delete((yyvsp[(4) - (4)].str));
               }
    break;

  case 444:
#line 5822 "parser.y"
    {
		 (yyval.str) = NewString((yyvsp[(1) - (1)].id));
   	       }
    break;

  case 445:
#line 5825 "parser.y"
    {
		 (yyval.str) = NewStringf("::%s",(yyvsp[(3) - (3)].id));
               }
    break;

  case 446:
#line 5828 "parser.y"
    {
                 (yyval.str) = NewString((yyvsp[(1) - (1)].str));
	       }
    break;

  case 447:
#line 5831 "parser.y"
    {
                 (yyval.str) = NewStringf("::%s",(yyvsp[(3) - (3)].str));
               }
    break;

  case 448:
#line 5836 "parser.y"
    {
                   (yyval.str) = NewStringf("::%s%s",(yyvsp[(2) - (3)].id),(yyvsp[(3) - (3)].str));
		   Delete((yyvsp[(3) - (3)].str));
               }
    break;

  case 449:
#line 5840 "parser.y"
    {
                   (yyval.str) = NewStringf("::%s",(yyvsp[(2) - (2)].id));
               }
    break;

  case 450:
#line 5843 "parser.y"
    {
                   (yyval.str) = NewStringf("::%s",(yyvsp[(2) - (2)].str));
               }
    break;

  case 451:
#line 5846 "parser.y"
    {
		 (yyval.str) = NewStringf("::~%s",(yyvsp[(2) - (2)].id));
               }
    break;

  case 452:
#line 5852 "parser.y"
    { 
                   (yyval.id) = (char *) malloc(strlen((yyvsp[(1) - (2)].id))+strlen((yyvsp[(2) - (2)].id))+1);
                   strcpy((yyval.id),(yyvsp[(1) - (2)].id));
                   strcat((yyval.id),(yyvsp[(2) - (2)].id));
               }
    break;

  case 453:
#line 5857 "parser.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id);}
    break;

  case 454:
#line 5860 "parser.y"
    {
		 (yyval.str) = NewString((yyvsp[(1) - (1)].id));
               }
    break;

  case 455:
#line 5863 "parser.y"
    {
                  skip_balanced('{','}');
		  (yyval.str) = NewString(scanner_ccode);
               }
    break;

  case 456:
#line 5867 "parser.y"
    {
		 (yyval.str) = (yyvsp[(1) - (1)].str);
              }
    break;

  case 457:
#line 5872 "parser.y"
    {
                  Hash *n;
                  (yyval.node) = NewHash();
                  n = (yyvsp[(2) - (3)].node);
                  while(n) {
                     String *name, *value;
                     name = Getattr(n,"name");
                     value = Getattr(n,"value");
		     if (!value) value = (String *) "1";
                     Setattr((yyval.node),name, value);
		     n = nextSibling(n);
		  }
               }
    break;

  case 458:
#line 5885 "parser.y"
    { (yyval.node) = 0; }
    break;

  case 459:
#line 5889 "parser.y"
    {
		 (yyval.node) = NewHash();
		 Setattr((yyval.node),"name",(yyvsp[(1) - (3)].id));
		 Setattr((yyval.node),"value",(yyvsp[(3) - (3)].id));
               }
    break;

  case 460:
#line 5894 "parser.y"
    {
		 (yyval.node) = NewHash();
		 Setattr((yyval.node),"name",(yyvsp[(1) - (5)].id));
		 Setattr((yyval.node),"value",(yyvsp[(3) - (5)].id));
		 set_nextSibling((yyval.node),(yyvsp[(5) - (5)].node));
               }
    break;

  case 461:
#line 5900 "parser.y"
    {
                 (yyval.node) = NewHash();
                 Setattr((yyval.node),"name",(yyvsp[(1) - (1)].id));
	       }
    break;

  case 462:
#line 5904 "parser.y"
    {
                 (yyval.node) = NewHash();
                 Setattr((yyval.node),"name",(yyvsp[(1) - (3)].id));
                 set_nextSibling((yyval.node),(yyvsp[(3) - (3)].node));
               }
    break;

  case 463:
#line 5909 "parser.y"
    {
                 (yyval.node) = (yyvsp[(3) - (3)].node);
		 Setattr((yyval.node),"name",(yyvsp[(1) - (3)].id));
               }
    break;

  case 464:
#line 5913 "parser.y"
    {
                 (yyval.node) = (yyvsp[(3) - (5)].node);
		 Setattr((yyval.node),"name",(yyvsp[(1) - (5)].id));
		 set_nextSibling((yyval.node),(yyvsp[(5) - (5)].node));
               }
    break;

  case 465:
#line 5920 "parser.y"
    {
		 (yyval.id) = (yyvsp[(1) - (1)].id);
               }
    break;

  case 466:
#line 5923 "parser.y"
    {
                 (yyval.id) = Char((yyvsp[(1) - (1)].dtype).val);
               }
    break;


/* Line 1267 of yacc.c.  */
#line 10087 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 5930 "parser.y"


SwigType *Swig_cparse_type(String *s) {
   String *ns;
   ns = NewStringf("%s;",s);
   Seek(ns,0,SEEK_SET);
   scanner_file(ns);
   top = 0;
   scanner_next_token(PARSETYPE);
   yyparse();
   /*   Printf(stdout,"typeparse: '%s' ---> '%s'\n", s, top); */
   return top;
}


Parm *Swig_cparse_parm(String *s) {
   String *ns;
   ns = NewStringf("%s;",s);
   Seek(ns,0,SEEK_SET);
   scanner_file(ns);
   top = 0;
   scanner_next_token(PARSEPARM);
   yyparse();
   /*   Printf(stdout,"typeparse: '%s' ---> '%s'\n", s, top); */
   Delete(ns);
   return top;
}


ParmList *Swig_cparse_parms(String *s) {
   String *ns;
   char *cs = Char(s);
   if (cs && cs[0] != '(') {
     ns = NewStringf("(%s);",s);
   } else {
     ns = NewStringf("%s;",s);
   }   
   Seek(ns,0,SEEK_SET);
   scanner_file(ns);
   top = 0;
   scanner_next_token(PARSEPARMS);
   yyparse();
   /*   Printf(stdout,"typeparse: '%s' ---> '%s'\n", s, top); */
   return top;
}


