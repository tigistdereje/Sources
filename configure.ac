AC_INIT([singular], [4.0.3], [singular@mathematik.uni-kl.de])
AC_DEFINE([VERSION_DATE],["Jan 2016"],[release date])

_AC_SRCDIRS(["$ac_dir"])

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])

AC_CONFIG_SRCDIR([Singular/tesths.cc])

AC_CONFIG_HEADER([_config.h])
# Add pre'prefixed config
AX_PREFIX_CONFIG_H([singularconfig.h],[],[_config.h])

dnl Apparently, this is required for using an AC_CHECK_HEADER within AS_IF(...), at least on Cygwin.
AC_USE_SYSTEM_EXTENSIONS

AM_MAINTAINER_MODE([enable])
AM_INIT_AUTOMAKE([-Wall foreign subdir-objects]) # -Wno-extra-portability -Werror silent-rules

m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

dnl Check if build env is sane
AM_SANITY_CHECK


SING_RESET_FLAGS()
SING_CHECK_SET_ARGS()

#!
# AC_PROG_CC
# AC_PROG_CXX
AC_PROG_CPP
AC_PROG_CXXCPP
AM_PROG_CC_C_O
### AM_PROG_LEX
AC_PROG_LN_S
AC_PROG_INSTALL
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])

AC_HEADER_STDC
AC_CHECK_HEADERS(unistd.h iostream.h sys/time.h sys/times.h asm/sigcontext.h)

AC_CHECK_FUNCS(readlink getcwd getwd setenv putenv qsort_r)

AC_CHECK_PROGS([DOXYGEN], [doxygen])
if test -z "$DOXYGEN";
   then AC_MSG_WARN([Doxygen not found - continuing without Doxygen support])
fi
AM_CONDITIONAL([HAVE_DOXYGEN], [test -n "$DOXYGEN"])

LT_INIT

link_all_deplibs=yes
link_all_deplibs_CXX=yes

# Checks for libraries.

# This test for -lpthread etc has to come before AX_PTHREAD,
# because libtool tends to ignore -pthread in linking shared C++-libs
# see https://gcc.gnu.org/bugzilla/show_bug.cgi?id=25460
# (happens with ubuntu 14.04)
AC_SEARCH_LIBS(sem_wait,[rt pthreads pthread],[],[
  AC_MSG_ERROR([sem_wait not found in rt,pthreads,pthread])
])

AX_PTHREAD([], [
  AC_MSG_ERROR([Pthread library not found. Please set PTHREAD_CFLAGS and PTHREAD_LIBS correctly for your setup])
])

AC_MSG_CHECKING([Found Pthread, PTHREAD_CC:])
AC_MSG_RESULT(${PTHREAD_CC:-unset})
AC_MSG_CHECKING([               PTHREAD_CFLAGS:])
AC_MSG_RESULT(${PTHREAD_CFLAGS:-unset})
AC_MSG_CHECKING([               PTHREAD_LIBS:])
AC_MSG_RESULT(${PTHREAD_LIBS:-unset})

# Set the correct PTHREAD flags and, if needed, change the compiler to one that is pthread-enabled.
CC="$PTHREAD_CC"
CFLAGS="$CFLAGS $PTHREAD_CFLAGS"
LDFLAGS="$LDFLAGS $PTHREAD_LDFLAGS"

AC_SUBST(PTHREAD_CFLAGS)
AC_SUBST(PTHREAD_LDFLAGS)
AC_SUBST(PTHREAD_LIBS)
AC_SUBST(CC)


AC_CHECK_LIB(rt,clock_gettime)

LB_CHECK_GMP(4.0,,AC_MSG_ERROR([Unable to find GMP on your machine: please use --with-gmp=PATH_TO_DIR_CONTAINING_LIB_AND_INCLUDE (see also ./configure --help if you do not understand what we are talking about)]))
LB_CHECK_NTL(5.0,,AC_MSG_WARN([Unable to find NTL (which is strongly recommended) on your machine: please use --with-ntl=PATH_TO_DIR_CONTAINING_LIB_AND_INCLUDE (see also ./configure --help if you do not understand what we are talking about)]))
LB_CHECK_FLINT(2.3,,AC_MSG_WARN([Unable to find FLINT (which is strongly recommended) on your machine: please use --with-flint=PATH_TO_DIR_CONTAINING_LIB_AND_INCLUDE (see also ./configure --help if you do not understand what we are talking about)]))

AC_CONFIG_GOOGLE_PERFTOOLS()

AX_PYTHON_DEFAULT()
AX_PYTHON_WITH_VERSION([2.4])

LB_CHECK_MATHICGB

AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC

# check for cpu properties
AC_CHECK_SIZEOF(long,4)
SING_CHECK_CPU

#check for host:
AC_CANONICAL_HOST

case $host_os in
  *cygwin* ) AX_APPEND_LINK_FLAGS([-Wl,-Bdynamic]);;
esac

PKG_REQUIRE="$PKG_REQUIRE"
AC_SUBST(PKG_REQUIRE)

SING_USE_OMALLOC()
SING_USE_RESOURCES()
SING_USE_FACTORY()

SING_CHECK_P_PROCS
SING_CHECK_READLINE
SING_CHECK_DBM

SING_CHECK_GFANLIB
SING_CHECK_POLYMAKE

SING_CHECK_PLURAL

SING_BUILTIN_MODULES

AC_ARG_ENABLE(countedref, AS_HELP_STRING([--enable-countedref], [Enable autoloading of reference counted types]),
[if test "x$enableval" = "xyes"; then
ENABLE_COUNTEDREF_AUTOLOAD=yes
fi], ENABLE_COUNTEDREF_AUTOLOAD=no)

if test x"${ENABLE_COUNTEDREF_AUTOLOAD}" == xyes; then
  AC_DEFINE([SI_COUNTEDREF_AUTOLOAD],1,[Enable autoloading of reference counted types])
  AC_SUBST(SI_COUNTEDREF_AUTOLOAD)
fi

dnl AC_CONFIG_FILES conditionalization requires using AM_COND_IF, however
dnl AM_COND_IF is new to Automake 1.11.  To use it on new Automake without
dnl requiring same, a fallback implementation for older Autoconf is provided.
dnl Note that disabling of AC_CONFIG_FILES requires Automake 1.11, this code
dnl is correct only in terms of m4sh generated script.
m4_ifndef([AM_COND_IF], [AC_DEFUN([AM_COND_IF], [
if test -z "$$1_TRUE"; then :
  m4_n([$2])[]dnl
m4_ifval([$3],
[else
    $3
])dnl
fi[]dnl
])])


AC_DEFINE_UNQUOTED([CC],"$CC",[CC])
AC_DEFINE_UNQUOTED([CXX],"$CXX",[CXX])
AC_DEFINE_UNQUOTED([CFLAGS],"$CFLAGS",[CFLAGS])
AC_DEFINE_UNQUOTED([CXXFLAGS],"$CXXFLAGS",[CXXFLAGS])
AC_DEFINE_UNQUOTED([DEFS],"$DEFS",[DEFS])
AC_DEFINE_UNQUOTED([CPPFLAGS],"$CPPFLAGS",[CPPFLAGS])
AC_DEFINE_UNQUOTED([LDFLAGS],"$LDFLAGS",[LDFLAGS])
AC_DEFINE_UNQUOTED([LIBS],"$LIBS",[LIBS])
AC_DEFINE_UNQUOTED([AC_CONFIGURE_ARGS],"$ac_configure_args",[ac_configure_args])
# AC_DEFINE_UNQUOTED([AC_CT_CC], "$ac_ct_CC",[ac_ct_CC])

AC_DEFINE_UNQUOTED([NTL_CFLAGS],"$NTL_CFLAGS",[NTL_CFLAGS])
AC_DEFINE_UNQUOTED([NTL_LIBS],"$NTL_LIBS",[NTL_LIBS])

AC_DEFINE_UNQUOTED([GMP_CFLAGS],"$GMP_CFLAGS",[GMP_CFLAGS])
AC_DEFINE_UNQUOTED([GMP_LIBS],"$GMP_LIBS",[GMP_LIBS])

AC_DEFINE_UNQUOTED([FLINT_CFLAGS],"$FLINT_CFLAGS",[FLINT_CFLAGS])
AC_DEFINE_UNQUOTED([FLINT_LIBS],"$FLINT_LIBS",[FLINT_LIBS])

##### SEE http://www.gnu.org/prep/standards/html_node/Directory-Variables.html

AX_RECURSIVE_EVAL([[$]prefix], [config_prefix])
AX_NORMALIZE_PATH([config_prefix],['/'])
AC_DEFINE_UNQUOTED([PREFIX],"$config_prefix",[prefix])

AX_RECURSIVE_EVAL([[$]exec_prefix], [config_exec_prefix])
AX_NORMALIZE_PATH([config_exec_prefix],['/'])
AC_DEFINE_UNQUOTED([EXEC_PREFIX],"$config_exec_prefix",[exec_prefix])

AX_RECURSIVE_EVAL([[$]libexecdir], [config_libexecdir])
AX_NORMALIZE_PATH([config_libexecdir],['/'])
AC_DEFINE_UNQUOTED([LIBEXEC_DIR],"$config_libexecdir",[libexecdir])

AX_RECURSIVE_EVAL([[$]libdir], [config_libdir])
AX_NORMALIZE_PATH([config_libdir],['/'])
AC_DEFINE_UNQUOTED([LIB_DIR],"$config_libdir",[libdir])

AX_RECURSIVE_EVAL([[$]bindir], [config_bindir])
AX_NORMALIZE_PATH([config_bindir],['/'])
AC_DEFINE_UNQUOTED([BIN_DIR],"$config_bindir",[bindir])

AX_RECURSIVE_EVAL([[$]datadir], [config_datadir])
AX_NORMALIZE_PATH([config_datadir],['/'])
AC_DEFINE_UNQUOTED([DATA_DIR],"$config_datadir",[datadir])
AC_SUBST(DATA_DIR)

AX_RECURSIVE_EVAL([[$]docdir], [config_docdir])
AX_NORMALIZE_PATH([config_docdir],['/'])
AC_DEFINE_UNQUOTED([DOC_DIR],"$config_docdir",[docdir])
AC_SUBST(DOC_DIR)

SING_SHOW_FLAGS([Compiler/linker flags: ])


## AM_COND_IF([HAVE_DOXYGEN], [AC_CONFIG_FILES([dox/Doxyfile])])

AC_CONFIG_FILES([dox/Makefile])

AC_CONFIG_SUBDIRS([resources])
AC_CONFIG_SUBDIRS([omalloc])

if test "x$ENABLE_FACTORY" = xyes; then
 AC_CONFIG_SUBDIRS([factory])
fi

AC_CONFIG_SUBDIRS([libpolys])

AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([kernel/Makefile])
AC_CONFIG_FILES([kernel/numeric/Makefile])
AC_CONFIG_FILES([kernel/fglm/Makefile])
AC_CONFIG_FILES([kernel/groebner_walk/Makefile])
AC_CONFIG_FILES([kernel/combinatorics/Makefile])
AC_CONFIG_FILES([kernel/spectrum/Makefile])
AC_CONFIG_FILES([kernel/linear_algebra/Makefile])
AC_CONFIG_FILES([kernel/maps/Makefile])
AC_CONFIG_FILES([kernel/GBEngine/Makefile])
AC_CONFIG_FILES([kernel/oswrapper/Makefile])

AC_CONFIG_SUBDIRS([gfanlib])

AC_CONFIG_FILES([Singular/dyn_modules/Makefile])
AC_CONFIG_FILES([Singular/dyn_modules/bigintm/Makefile])
AC_CONFIG_FILES([Singular/dyn_modules/Order/Makefile])
AC_CONFIG_FILES([Singular/dyn_modules/syzextra/Makefile])
AC_CONFIG_FILES([Singular/dyn_modules/gfanlib/Makefile])
AC_CONFIG_FILES([Singular/dyn_modules/polymake/Makefile])
AC_CONFIG_FILES([Singular/dyn_modules/customstd/Makefile])
AC_CONFIG_FILES([Singular/dyn_modules/pyobject/Makefile])
AC_CONFIG_FILES([Singular/dyn_modules/singmathic/Makefile])
AC_CONFIG_FILES([Singular/dyn_modules/staticdemo/Makefile])

AC_CONFIG_FILES([Singular/Makefile])

AC_CONFIG_FILES([IntegerProgramming/Makefile])

AC_CONFIG_FILES([libsingular-config Singular.pc])

AC_CONFIG_FILES([emacs/Makefile])

AC_CONFIG_FILES([redhat/Makefile])
AC_CONFIG_FILES([redhat/singular.spec])
AC_CONFIG_FILES([desktop/Makefile desktop/Singular.desktop desktop/Singular-manual.desktop])

AC_OUTPUT
