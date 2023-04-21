AC_PREREQ([2.69])
AC_INIT([glengine], [0.1.0.0], [dimao8@yandex.ru])
AC_CONFIG_SRCDIR([src/glengine.cc])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([1.10 foreign subdir-objects silent-rules])
AC_CONFIG_MACRO_DIRS([m4])
AC_LANG([C++])

# Check for LibTool
LT_INIT([dlopen win32-dll])
LT_LANG([C++])

# Check for compiler
CXXFLAGS="-std=gnu++11"
AC_PROG_CXX(clang++ llvm-g++ g++)

# Check for debug option
AC_ARG_ENABLE([debug],
    [AS_HELP_STRING([--enable-debug], [Set to enable debugging, default: no])],
    [
      AS_CASE([${enableval}],
        [yes], [ac_debug=true],
        [no], [ac_debug=false],
        [AC_MSG_ERROR([Bad value ${enableval} for --enable-debug])])
    ],
    [ac_debug=false])

AM_CONDITIONAL(DEBUG, test "x${ac_debug}" = "xtrue")

# Check for documentation option
AC_ARG_ENABLE([build-docs],
    [AS_HELP_STRING([--enable-build-docs], [Set to enable build the documentation, default: yes])],
    [
      AS_CASE([${enableval}],
        [yes], [ac_build_docs=true],
        [no], [ac_build_docs=false],
        [AC_MSG_ERROR([Bad value ${enableval} for --enable-build-docs])])
    ],
    [ac_build_docs=false])
AM_CONDITIONAL([BUILD_DOC], [test "x$ac_build_docs" = "xyes"])

# Check for pdflatex
AS_IF([test "x$ac_build_docs" = "xyes"],
  [
    AC_PATH_PROG([PDFLATEX], [pdflatex])
  ])

# Check for GL
AX_CHECK_GL

# Check for GLFW3
AX_CHECK_GLFW

# Check for glm
AX_CHECK_GLM

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
