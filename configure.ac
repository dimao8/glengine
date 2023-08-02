AC_PREREQ([2.69])
AC_INIT([libglengine], [0.1.0.12], [dimao8@yandex.ru])
AC_CONFIG_SRCDIR([src/engine.cc])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([1.10 foreign subdir-objects silent-rules])
AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_SUBDIRS([libpngloader libtgaloader liblitejson])
AM_SILENT_RULES([yes])
AC_LANG([C++])

# Check for LibTool
LT_INIT([dlopen win32-dll])
LT_LANG([C++])

# Check for compiler
CXXFLAGS="-std=gnu++11 -pedantic"
AC_PROG_CXX(clang++ llvm-g++ g++)

# Check for host
AC_CANONICAL_HOST

LIBS="$LIBS -ldl"

# Check for debug option
AC_ARG_ENABLE([debug],
    [AS_HELP_STRING([--enable-debug], [Set to enable debugging, default: no])],
    [
      AS_CASE([${enableval}],
        [yes],
        [
          CXXFLAGS="-g -O0 -DDEBUG"
        ],
        [no],
        [
          CXXFLAGS="-O2 -DNDEBUG"
        ],
        [AC_MSG_ERROR([Bad value ${enableval} for --enable-debug])])
    ],
    [ac_debug=false])

AM_CONDITIONAL(DEBUG, test "x${ac_debug}" = "xtrue")

# Check for documentation option
AC_ARG_ENABLE([build-docs],
    [AS_HELP_STRING([--enable-build-docs], [Set to enable build the documentation, default: no])],
    [
      AS_CASE([${enableval}],
        [yes], [ac_build_docs=yes],
        [no], [ac_build_docs=no],
        [AC_MSG_ERROR([Bad value ${enableval} for --enable-build-docs])])
    ],
    [ac_build_docs=no])
AM_CONDITIONAL([BUILD_DOC], [test "x$ac_build_docs" = "xyes"])

# Check for pdflatex
AS_IF([test "x$ac_build_docs" = "xyes"],
  [
    AC_PATH_PROG([PDFLATEX], [pdflatex])
  ])

# Check for GL
AX_CHECK_OPENGL

# Check for GLFW3
AX_CHECK_GLFW

# Check for glm
AX_CHECK_GLM

# Make symbolic links to the some files
AC_CONFIG_LINKS([tests/shader.vert:tests/shader.vert
  tests/shader.frag:tests/shader.frag
  tests/test.png:tests/test.png
  ])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
