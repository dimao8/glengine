AC_DEFUN([AX_CHECK_XLIB],
[

AC_CHECK_HEADERS([X11/Xlib.h],
                 [],
                 AC_MSG_ERROR(*** There is no <X11/xlib.h>. Please check libX11 binding installed!))

LIBS="$LIBS -lX11 -pthread"

have_xlib=no

AC_MSG_CHECKING(for -lX11)
AC_TRY_LINK([#include <X11/Xlib.h>],
            [XFree(0);],
            [have_xlib=yes],
            [have_xlib=no])
AC_MSG_RESULT([$have_xlib])

AS_IF([test "x$have_xlib" != "xyes"],
      [AC_MSG_ERROR(*** There is no <X11/xlib.h>. Please check libX11 binding installed!)])

])
