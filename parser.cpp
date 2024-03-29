/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "gramatica.y"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string.h>

#include "scanner.h"
#include "mkdisk.h"
#include "rmdisk.h"
#include "fdisk.h"
#include "rep.h"
#include "exec.h"
#include "mount.h"
#include "mkfs.h"
#include "login.h"
#include "mkdir.h"
#include "mkfile.h"
#include "ssl.h"
#include "ren.h"
#include "commands.h"

using namespace std;
extern int yylex(void);
extern char *yytext;
extern FILE *yyin;
extern void yyerror(const char *s);
extern int linea;


_MKDISK * mkdiskV;
_RMDISK * rmdiskV;
_FDISK * fdiskV;
_REP * repV;
_EXEC * execV;
_MOUNT * mountV;
_MKFS * mkfsV;
_LOGIN *loginV;
_MKDIR *mkdirV;
_MKFILE *mkfileV;
_SSL * sslV;
_REN * renV;
_COMMANDS * commandsV;

#line 115 "parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    numero = 258,
    cadena = 259,
    guion = 260,
    igual = 261,
    mkdisk = 262,
    size = 263,
    f = 264,
    u = 265,
    p = 266,
    r = 267,
    path = 268,
    rmdisk = 269,
    fdisk = 270,
    type = 271,
    delete_ = 272,
    name = 273,
    add = 274,
    mount = 275,
    unmount = 276,
    mkfs = 277,
    id = 278,
    fs = 279,
    usr = 280,
    pwd = 281,
    login = 282,
    logout = 283,
    mkgrp = 284,
    rmgrp = 285,
    mkusr = 286,
    rmusr = 287,
    chmod = 288,
    ugo = 289,
    ruta = 290,
    rep = 291,
    R_id = 292,
    R_ruta = 293,
    partition_id = 294,
    exec = 295,
    pause_ = 296,
    mkdir = 297,
    mkfile = 298,
    cont = 299,
    loss = 300,
    recovery = 301,
    ren = 302,
    mv = 303,
    dest = 304
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 125 "gramatica.y"

    char*STRING;
    char*NUM;

#line 222 "parser.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  39
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   252

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  116
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  226

#define YYUNDEFTOK  2
#define YYMAXUTOK   304


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      45,    46,    47,    48,    49
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   132,   132,   136,   137,   141,   141,   142,   142,   143,
     143,   144,   144,   145,   146,   147,   148,   148,   149,   150,
     150,   151,   151,   152,   152,   153,   154,   154,   155,   155,
     156,   157,   158,   158,   159,   159,   160,   164,   165,   169,
     170,   171,   172,   173,   177,   178,   182,   183,   187,   188,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   206,   207,   211,   212,   213,   214,   215,   216,   217,
     221,   222,   226,   227,   228,   229,   233,   234,   238,   239,
     240,   244,   245,   249,   250,   251,   252,   253,   254,   255,
     259,   260,   264,   265,   266,   270,   271,   275,   276,   277,
     278,   279,   280,   284,   285,   289,   290,   291,   292,   296,
     297,   301,   302,   303,   304,   305,   306
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "numero", "cadena", "guion", "igual",
  "mkdisk", "size", "f", "u", "p", "r", "path", "rmdisk", "fdisk", "type",
  "delete_", "name", "add", "mount", "unmount", "mkfs", "id", "fs", "usr",
  "pwd", "login", "logout", "mkgrp", "rmgrp", "mkusr", "rmusr", "chmod",
  "ugo", "ruta", "rep", "R_id", "R_ruta", "partition_id", "exec", "pause_",
  "mkdir", "mkfile", "cont", "loss", "recovery", "ren", "mv", "dest",
  "$accept", "INIT", "INSTRUCCIONES", "INSTRUCCION", "$@1", "$@2", "$@3",
  "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "MKDISKP", "MKDISKPARAM", "RMDISKP", "RMDISKPARAM", "FDISKP",
  "FDISKPARAM", "REPP", "REPPARAM", "MOUNTP", "MOUNTPARAM", "MKFSP",
  "MKFSPARAM", "LOGINP", "LOGINPARAM", "MKDIRP", "MKDIRPARAM", "MKFILEP",
  "MKFILEPARAM", "RENP", "RENPARAM", "COMMANDP", "COMMANDPARAM", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304
};
# endif

#define YYPACT_NINF (-53)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-3)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      37,   -53,   -53,   -53,   -53,   -53,     6,   -53,   -53,   -53,
     -53,   -53,     7,   -53,   -53,   -53,    85,    96,   -53,   -53,
     102,     0,   -53,    98,   100,   109,   110,    80,   122,   124,
     125,   127,   105,   128,   129,    99,   101,   130,   125,   -53,
     -53,   115,    98,   -53,   126,   100,   -53,   103,   109,   -53,
      91,   110,   -53,   131,    73,   122,   -53,   -21,   124,   -53,
     -10,   125,   -53,    58,   127,   -53,   134,    -3,   128,   -53,
       5,   129,   -53,   135,   136,   113,   130,   -53,   125,   137,
     138,   139,   140,   -53,   141,   -53,   142,   143,   144,   145,
     146,   147,   148,   149,   -53,   150,   151,   -53,   119,   153,
     154,   155,   -53,   156,   157,   158,   -53,   -53,   159,   160,
     161,   -53,   162,   163,   164,   165,   -53,     2,   -53,   166,
     -53,   167,   -53,   168,   169,   -53,   152,   170,   171,   172,
     -53,   173,   174,   175,    15,    19,   176,   177,   178,    21,
      70,   179,    30,   180,    25,    68,   -53,   181,   182,   183,
      83,    71,   184,    26,   185,    27,    28,   187,    69,    31,
     -53,   -53,    51,   186,    63,    64,   -53,   -53,    65,    84,
     -53,   -53,   -53,   -53,   -53,   -53,   -53,   -53,   -53,   -53,
     -53,   -53,   -53,   -53,   -53,   -53,   -53,   -53,   -53,   -53,
     -53,   -53,   -53,   188,   -53,   -53,   -53,   190,   -53,   -53,
     -53,   -53,   -53,   -53,   -53,   -53,   -53,   -53,   -53,   -53,
     -53,   -53,   -53,   -53,   -53,   -53,   -53,   -53,   -53,   -53,
     -53,   -53,   -53,   -53,   -53,   -53
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    36,     5,     7,     9,    16,     0,    19,    23,    25,
      34,    11,     0,    15,    21,    26,     0,     0,    28,    32,
       0,     0,     4,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     1,
       3,     0,     6,    38,     0,     8,    45,     0,    10,    49,
       0,    17,    71,     0,     0,    20,    77,     0,    24,    82,
       0,    35,   110,     0,    12,    62,     0,     0,    22,    91,
       0,    27,    96,     0,     0,     0,    29,   104,    33,     0,
       0,     0,     0,    37,     0,    44,     0,     0,     0,     0,
       0,     0,     0,     0,    48,     0,     0,    70,     0,     0,
       0,     0,    76,     0,     0,     0,    81,   116,     0,     0,
       0,   109,     0,     0,     0,     0,    61,     0,    92,     0,
      90,     0,    97,     0,     0,    95,     0,     0,     0,     0,
     103,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    18,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      13,    14,     0,     0,     0,     0,    30,    31,     0,     0,
      39,    40,    41,    43,    42,    47,    46,    50,    54,    51,
      60,    59,    53,    52,    55,    57,    56,    58,    75,    74,
      73,    72,    79,     0,    78,    85,    84,    88,    89,    86,
      83,   112,   111,   115,   114,   113,    64,    65,    63,    66,
      67,    69,    68,    94,    93,   100,    99,    98,   102,   101,
     106,   105,   108,   107,    80,    87
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -53,   -53,   -53,   193,   -53,   -53,   -53,   -53,   -53,   -53,
     -53,   -53,   -53,   -53,   -53,   -53,   -53,   189,   -53,   191,
     -53,   132,   -53,   117,   -53,   133,   -53,   192,   -53,   194,
     -53,   114,   -53,   116,   -53,   118,   195,   -52
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    20,    21,    22,    23,    24,    25,    31,    26,    28,
      33,    29,    34,    37,    38,    30,    42,    43,    45,    46,
      48,    49,    64,    65,    51,    52,    55,    56,    58,    59,
      68,    69,    71,    72,    76,    77,    61,    62
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      -2,     1,   107,   108,   103,   104,   160,     2,   118,   111,
     119,    27,    32,   121,     3,     4,   105,   122,   123,   173,
       5,     6,     7,   175,   109,   180,   111,     8,     9,   188,
     201,   204,   206,    10,   185,   211,    11,   161,     1,   110,
      12,    13,    14,    15,     2,    16,    17,    18,    19,   124,
     174,     3,     4,   186,   176,   213,   181,     5,     6,     7,
     189,   202,   205,   207,     8,     9,   212,   216,   218,   220,
      10,   112,   190,    11,   197,   198,   113,    12,    13,    14,
      15,   182,    16,    17,    18,    19,   214,   195,   222,    99,
      35,   191,   209,   183,   199,   114,   115,   100,   217,   219,
     221,    36,    39,    41,    95,    44,   196,   223,   210,    96,
     101,    86,    87,    88,    47,    50,    89,    53,    66,    90,
      91,    92,    93,    79,    80,    81,   128,    54,    82,    57,
      60,   129,    63,    67,    70,    75,    73,    98,    74,    84,
     117,   126,   127,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   162,   163,   164,   165,   170,   168,   169,   177,
      94,   116,   120,   187,    97,   193,     0,   125,   203,   215,
       0,   166,     0,     0,   130,     0,     0,   171,   172,     0,
     178,   179,   184,     0,   192,     0,     0,     0,     0,   167,
     208,     0,   224,   225,    40,     0,     0,     0,     0,     0,
       0,     0,   194,   200,     0,     0,     0,     0,     0,     0,
       0,    83,     0,    78,     0,     0,    85,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   102,     0,     0,
       0,     0,   106
};

static const yytype_int8 yycheck[] =
{
       0,     1,    12,    13,    25,    26,     4,     7,    11,    61,
      13,     5,     5,     8,    14,    15,    37,    12,    13,     4,
      20,    21,    22,     4,    34,     4,    78,    27,    28,     4,
       4,     4,     4,    33,     4,     4,    36,    35,     1,    49,
      40,    41,    42,    43,     7,    45,    46,    47,    48,    44,
      35,    14,    15,    23,    35,     4,    35,    20,    21,    22,
      35,    35,    35,    35,    27,    28,    35,     4,     4,     4,
      33,    13,     4,    36,     3,     4,    18,    40,    41,    42,
      43,    11,    45,    46,    47,    48,    35,     4,     4,    16,
       5,    23,    23,    23,    23,    37,    38,    24,    35,    35,
      35,     5,     0,     5,    13,     5,    23,    23,    39,    18,
      37,     8,     9,    10,     5,     5,    13,    37,    13,    16,
      17,    18,    19,     8,     9,    10,    13,     5,    13,     5,
       5,    18,     5,     5,     5,     5,    37,     6,    37,    13,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,    39,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     3,     6,     6,     3,
      48,    64,    68,     3,    51,     3,    -1,    71,     3,     3,
      -1,    39,    -1,    -1,    76,    -1,    -1,    23,    23,    -1,
      23,    23,    23,    -1,    23,    -1,    -1,    -1,    -1,    39,
      23,    -1,    24,    23,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    42,    -1,    38,    -1,    -1,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    58
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     7,    14,    15,    20,    21,    22,    27,    28,
      33,    36,    40,    41,    42,    43,    45,    46,    47,    48,
      51,    52,    53,    54,    55,    56,    58,     5,    59,    61,
      65,    57,     5,    60,    62,     5,     5,    63,    64,     0,
      53,     5,    66,    67,     5,    68,    69,     5,    70,    71,
       5,    74,    75,    37,     5,    76,    77,     5,    78,    79,
       5,    86,    87,     5,    72,    73,    13,     5,    80,    81,
       5,    82,    83,    37,    37,     5,    84,    85,    86,     8,
       9,    10,    13,    67,    13,    69,     8,     9,    10,    13,
      16,    17,    18,    19,    71,    13,    18,    75,     6,    16,
      24,    37,    77,    25,    26,    37,    79,    12,    13,    34,
      49,    87,    13,    18,    37,    38,    73,     6,    11,    13,
      81,     8,    12,    13,    44,    83,     6,     6,    13,    18,
      85,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,    39,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       4,    35,     6,     6,     6,     6,    39,    39,     6,     6,
       3,    23,    23,     4,    35,     4,    35,     3,    23,    23,
       4,    35,    11,    23,    23,     4,    23,     3,     4,    35,
       4,    23,    23,     3,    39,     4,    23,     3,     4,    23,
      39,     4,    35,     3,     4,    35,     4,    35,    23,    23,
      39,     4,    35,     4,    35,     3,     4,    35,     4,    35,
       4,    35,     4,    23,    24,    23
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    50,    51,    52,    52,    54,    53,    55,    53,    56,
      53,    57,    53,    53,    53,    53,    58,    53,    53,    59,
      53,    60,    53,    61,    53,    53,    62,    53,    63,    53,
      53,    53,    64,    53,    65,    53,    53,    66,    66,    67,
      67,    67,    67,    67,    68,    68,    69,    69,    70,    70,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    72,    72,    73,    73,    73,    73,    73,    73,    73,
      74,    74,    75,    75,    75,    75,    76,    76,    77,    77,
      77,    78,    78,    79,    79,    79,    79,    79,    79,    79,
      80,    80,    81,    81,    81,    82,    82,    83,    83,    83,
      83,    83,    83,    84,    84,    85,    85,    85,    85,    86,
      86,    87,    87,    87,    87,    87,    87
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     0,     3,     0,     3,     0,
       3,     0,     3,     5,     5,     1,     0,     3,     5,     0,
       3,     0,     3,     0,     3,     1,     0,     3,     0,     3,
       5,     5,     0,     3,     0,     3,     1,     2,     1,     4,
       4,     4,     4,     4,     2,     1,     4,     4,     2,     1,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     2,     1,     4,     4,     4,     4,     4,     4,     4,
       2,     1,     4,     4,     4,     4,     2,     1,     4,     4,
       5,     2,     1,     4,     4,     4,     4,     5,     4,     4,
       2,     1,     2,     4,     4,     2,     1,     2,     4,     4,
       4,     4,     4,     2,     1,     4,     4,     4,     4,     2,
       1,     4,     4,     4,     4,     4,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 5:
#line 141 "gramatica.y"
           {mkdiskV = new _MKDISK();}
#line 1670 "parser.cpp"
    break;

  case 6:
#line 141 "gramatica.y"
                                              {mkdiskV->exe();/*realiza la creación del disco*/}
#line 1676 "parser.cpp"
    break;

  case 7:
#line 142 "gramatica.y"
             {rmdiskV = new _RMDISK();}
#line 1682 "parser.cpp"
    break;

  case 8:
#line 142 "gramatica.y"
                                                {rmdiskV->exe();/*realiza la eliminación del disco*/}
#line 1688 "parser.cpp"
    break;

  case 9:
#line 143 "gramatica.y"
            {fdiskV = new _FDISK();}
#line 1694 "parser.cpp"
    break;

  case 10:
#line 143 "gramatica.y"
                                            {fdiskV->exe();/*realiza la eliminación del disco*/}
#line 1700 "parser.cpp"
    break;

  case 11:
#line 144 "gramatica.y"
          {repV = new _REP();}
#line 1706 "parser.cpp"
    break;

  case 12:
#line 144 "gramatica.y"
                                    {repV->exe();/*Imprime los reportes*/}
#line 1712 "parser.cpp"
    break;

  case 13:
#line 145 "gramatica.y"
                                   {execV = new _EXEC(); execV->setPath((yyvsp[0].STRING), true); execV->exe();}
#line 1718 "parser.cpp"
    break;

  case 14:
#line 146 "gramatica.y"
                                 {execV = new _EXEC(); execV->setPath((yyvsp[0].STRING), false); execV->exe();}
#line 1724 "parser.cpp"
    break;

  case 15:
#line 147 "gramatica.y"
             {cout << "\nLa ejecución del script se ha pausado, por favor presiona cualquier tecla para continuar."<<endl; cin.get();}
#line 1730 "parser.cpp"
    break;

  case 16:
#line 148 "gramatica.y"
            {mountV = new _MOUNT();}
#line 1736 "parser.cpp"
    break;

  case 17:
#line 148 "gramatica.y"
                                            {mountV->exe();/*realiza la eliminación del disco*/}
#line 1742 "parser.cpp"
    break;

  case 18:
#line 149 "gramatica.y"
                                            {mountV->unmount((yyvsp[0].STRING)); }
#line 1748 "parser.cpp"
    break;

  case 19:
#line 150 "gramatica.y"
           {mkfsV = new _MKFS();}
#line 1754 "parser.cpp"
    break;

  case 20:
#line 150 "gramatica.y"
                                        {mkfsV->exe();}
#line 1760 "parser.cpp"
    break;

  case 21:
#line 151 "gramatica.y"
            {mkdirV = new _MKDIR();}
#line 1766 "parser.cpp"
    break;

  case 22:
#line 151 "gramatica.y"
                                            {mkdirV->exe();}
#line 1772 "parser.cpp"
    break;

  case 23:
#line 152 "gramatica.y"
            {loginV = new _LOGIN();}
#line 1778 "parser.cpp"
    break;

  case 24:
#line 152 "gramatica.y"
                                            {loginV->exe();}
#line 1784 "parser.cpp"
    break;

  case 25:
#line 153 "gramatica.y"
             {loginV->logout();}
#line 1790 "parser.cpp"
    break;

  case 26:
#line 154 "gramatica.y"
             {mkfileV = new _MKFILE();}
#line 1796 "parser.cpp"
    break;

  case 27:
#line 154 "gramatica.y"
                                                {mkfileV->exe();}
#line 1802 "parser.cpp"
    break;

  case 28:
#line 155 "gramatica.y"
          {renV = new _REN();}
#line 1808 "parser.cpp"
    break;

  case 29:
#line 155 "gramatica.y"
                                    {renV->exe();}
#line 1814 "parser.cpp"
    break;

  case 30:
#line 156 "gramatica.y"
                                         {sslV = new _SSL(); sslV->setId((yyvsp[0].STRING)); sslV->simulateLoss();}
#line 1820 "parser.cpp"
    break;

  case 31:
#line 157 "gramatica.y"
                                             {sslV->setId((yyvsp[0].STRING)); sslV->simulateRecovery();}
#line 1826 "parser.cpp"
    break;

  case 32:
#line 158 "gramatica.y"
         {commandsV = new _COMMANDS();}
#line 1832 "parser.cpp"
    break;

  case 33:
#line 158 "gramatica.y"
                                                 {commandsV->exeMv();}
#line 1838 "parser.cpp"
    break;

  case 34:
#line 159 "gramatica.y"
            {commandsV = new _COMMANDS();}
#line 1844 "parser.cpp"
    break;

  case 35:
#line 159 "gramatica.y"
                                                    {commandsV->exeChmod();}
#line 1850 "parser.cpp"
    break;

  case 36:
#line 160 "gramatica.y"
            {}
#line 1856 "parser.cpp"
    break;

  case 39:
#line 169 "gramatica.y"
                                {mkdiskV->setSize(atoi((yyvsp[0].NUM)));}
#line 1862 "parser.cpp"
    break;

  case 40:
#line 170 "gramatica.y"
                         {mkdiskV->setFit((yyvsp[0].STRING));}
#line 1868 "parser.cpp"
    break;

  case 41:
#line 171 "gramatica.y"
                         {mkdiskV->setUnit((yyvsp[0].STRING));}
#line 1874 "parser.cpp"
    break;

  case 42:
#line 172 "gramatica.y"
                              {mkdiskV->setPath((yyvsp[0].STRING), false);}
#line 1880 "parser.cpp"
    break;

  case 43:
#line 173 "gramatica.y"
                                {mkdiskV->setPath((yyvsp[0].STRING), true);}
#line 1886 "parser.cpp"
    break;

  case 46:
#line 182 "gramatica.y"
                              {rmdiskV->setPath((yyvsp[0].STRING), false);}
#line 1892 "parser.cpp"
    break;

  case 47:
#line 183 "gramatica.y"
                                {rmdiskV->setPath((yyvsp[0].STRING), true);}
#line 1898 "parser.cpp"
    break;

  case 50:
#line 192 "gramatica.y"
                                {fdiskV->setSize(atoi((yyvsp[0].NUM)));}
#line 1904 "parser.cpp"
    break;

  case 51:
#line 193 "gramatica.y"
                         {fdiskV->setUnit((yyvsp[0].STRING));}
#line 1910 "parser.cpp"
    break;

  case 52:
#line 194 "gramatica.y"
                            {fdiskV->setType((yyvsp[0].STRING));}
#line 1916 "parser.cpp"
    break;

  case 53:
#line 195 "gramatica.y"
                           {fdiskV->setType((yyvsp[0].STRING));}
#line 1922 "parser.cpp"
    break;

  case 54:
#line 196 "gramatica.y"
                         {fdiskV->setFit((yyvsp[0].STRING));}
#line 1928 "parser.cpp"
    break;

  case 55:
#line 197 "gramatica.y"
                               {fdiskV->setDelete((yyvsp[0].STRING));}
#line 1934 "parser.cpp"
    break;

  case 56:
#line 198 "gramatica.y"
                            {fdiskV->setName((yyvsp[0].STRING), false);}
#line 1940 "parser.cpp"
    break;

  case 57:
#line 199 "gramatica.y"
                                {fdiskV->setName((yyvsp[0].STRING), true);}
#line 1946 "parser.cpp"
    break;

  case 58:
#line 200 "gramatica.y"
                               {fdiskV->setAdd(atoi((yyvsp[0].NUM)));}
#line 1952 "parser.cpp"
    break;

  case 59:
#line 201 "gramatica.y"
                              {fdiskV->setPath((yyvsp[0].STRING), false);}
#line 1958 "parser.cpp"
    break;

  case 60:
#line 202 "gramatica.y"
                                {fdiskV->setPath((yyvsp[0].STRING), true);}
#line 1964 "parser.cpp"
    break;

  case 63:
#line 211 "gramatica.y"
                            {repV->setName((yyvsp[0].STRING));}
#line 1970 "parser.cpp"
    break;

  case 64:
#line 212 "gramatica.y"
                                {repV->setPath((yyvsp[0].STRING), true);}
#line 1976 "parser.cpp"
    break;

  case 65:
#line 213 "gramatica.y"
                              {repV->setPath((yyvsp[0].STRING), false);}
#line 1982 "parser.cpp"
    break;

  case 66:
#line 214 "gramatica.y"
                            {repV->setId((yyvsp[0].STRING));}
#line 1988 "parser.cpp"
    break;

  case 67:
#line 215 "gramatica.y"
                                      {repV->setId((yyvsp[0].STRING));}
#line 1994 "parser.cpp"
    break;

  case 68:
#line 216 "gramatica.y"
                                {repV->setRuta((yyvsp[0].STRING), false);}
#line 2000 "parser.cpp"
    break;

  case 69:
#line 217 "gramatica.y"
                                  {repV->setRuta((yyvsp[0].STRING), true);}
#line 2006 "parser.cpp"
    break;

  case 72:
#line 226 "gramatica.y"
                            {mountV->setName((yyvsp[0].STRING), false);}
#line 2012 "parser.cpp"
    break;

  case 73:
#line 227 "gramatica.y"
                                {mountV->setName((yyvsp[0].STRING), true);}
#line 2018 "parser.cpp"
    break;

  case 74:
#line 228 "gramatica.y"
                              {mountV->setPath((yyvsp[0].STRING), false);}
#line 2024 "parser.cpp"
    break;

  case 75:
#line 229 "gramatica.y"
                                {mountV->setPath((yyvsp[0].STRING), true);}
#line 2030 "parser.cpp"
    break;

  case 78:
#line 238 "gramatica.y"
                                      {mkfsV->setId((yyvsp[0].STRING));}
#line 2036 "parser.cpp"
    break;

  case 79:
#line 239 "gramatica.y"
                            {mkfsV->setType((yyvsp[0].STRING));}
#line 2042 "parser.cpp"
    break;

  case 80:
#line 240 "gramatica.y"
                                 {mkfsV->setFs(atoi((yyvsp[-1].NUM))); }
#line 2048 "parser.cpp"
    break;

  case 83:
#line 249 "gramatica.y"
                                      {loginV->setId((yyvsp[0].STRING));}
#line 2054 "parser.cpp"
    break;

  case 84:
#line 250 "gramatica.y"
                           {loginV->setUsr((yyvsp[0].STRING), false);}
#line 2060 "parser.cpp"
    break;

  case 85:
#line 251 "gramatica.y"
                               {loginV->setUsr((yyvsp[0].STRING), true);}
#line 2066 "parser.cpp"
    break;

  case 86:
#line 252 "gramatica.y"
                           {loginV->setPwd((yyvsp[0].STRING),"", false); }
#line 2072 "parser.cpp"
    break;

  case 87:
#line 253 "gramatica.y"
                                  {loginV->setPwd((yyvsp[-1].NUM),(yyvsp[0].STRING), false); }
#line 2078 "parser.cpp"
    break;

  case 88:
#line 254 "gramatica.y"
                               {loginV->setPwd((yyvsp[0].NUM),"", false); }
#line 2084 "parser.cpp"
    break;

  case 89:
#line 255 "gramatica.y"
                               {loginV->setPwd((yyvsp[0].STRING),"", true); }
#line 2090 "parser.cpp"
    break;

  case 92:
#line 264 "gramatica.y"
                {mkdirV->setP();}
#line 2096 "parser.cpp"
    break;

  case 93:
#line 265 "gramatica.y"
                              {mkdirV->setPath((yyvsp[0].STRING), false);}
#line 2102 "parser.cpp"
    break;

  case 94:
#line 266 "gramatica.y"
                                {mkdirV->setPath((yyvsp[0].STRING), true);}
#line 2108 "parser.cpp"
    break;

  case 97:
#line 275 "gramatica.y"
                {mkfileV->setR();}
#line 2114 "parser.cpp"
    break;

  case 98:
#line 276 "gramatica.y"
                              {mkfileV->setPath((yyvsp[0].STRING), false);}
#line 2120 "parser.cpp"
    break;

  case 99:
#line 277 "gramatica.y"
                                {mkfileV->setPath((yyvsp[0].STRING), true);}
#line 2126 "parser.cpp"
    break;

  case 100:
#line 278 "gramatica.y"
                                {mkfileV->setSize(atoi((yyvsp[0].NUM)));}
#line 2132 "parser.cpp"
    break;

  case 101:
#line 279 "gramatica.y"
                              {mkfileV->setCont((yyvsp[0].STRING), false);}
#line 2138 "parser.cpp"
    break;

  case 102:
#line 280 "gramatica.y"
                                {mkfileV->setCont((yyvsp[0].STRING), true);}
#line 2144 "parser.cpp"
    break;

  case 105:
#line 289 "gramatica.y"
                              {renV->setPath((yyvsp[0].STRING), false);}
#line 2150 "parser.cpp"
    break;

  case 106:
#line 290 "gramatica.y"
                                {renV->setPath((yyvsp[0].STRING), true);}
#line 2156 "parser.cpp"
    break;

  case 107:
#line 291 "gramatica.y"
                            {renV->setName((yyvsp[0].STRING), false);}
#line 2162 "parser.cpp"
    break;

  case 108:
#line 292 "gramatica.y"
                                {renV->setName((yyvsp[0].STRING), true);}
#line 2168 "parser.cpp"
    break;

  case 111:
#line 301 "gramatica.y"
                              {commandsV->setPath((yyvsp[0].STRING), false);}
#line 2174 "parser.cpp"
    break;

  case 112:
#line 302 "gramatica.y"
                                {commandsV->setPath((yyvsp[0].STRING), true);}
#line 2180 "parser.cpp"
    break;

  case 113:
#line 303 "gramatica.y"
                              {commandsV->setDest((yyvsp[0].STRING), false);}
#line 2186 "parser.cpp"
    break;

  case 114:
#line 304 "gramatica.y"
                                {commandsV->setDest((yyvsp[0].STRING), true);}
#line 2192 "parser.cpp"
    break;

  case 115:
#line 305 "gramatica.y"
                               {commandsV->setUgo(atoi((yyvsp[0].NUM)));}
#line 2198 "parser.cpp"
    break;

  case 116:
#line 306 "gramatica.y"
                {commandsV->setR();}
#line 2204 "parser.cpp"
    break;


#line 2208 "parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, yylsp);
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
  return yyresult;
}
#line 308 "gramatica.y"

void yyerror(const char *s)
{
    printf("Error sintactico en la linea %i: %s\n", linea, s);
}
