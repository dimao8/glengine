AC_DEFUN([AX_CHECK_XLIB],
[
  XLIB_CFLAGS=
  XLIB_LIBS=
  PKG_CHECK_MODULES([XLIB],
    [x11],
    :,
    [AC_MSG_ERROR(*** x11 not found)])
])
