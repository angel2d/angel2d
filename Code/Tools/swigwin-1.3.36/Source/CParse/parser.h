/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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
/* Line 1489 of yacc.c.  */
#line 344 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

