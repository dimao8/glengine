AC_DEFUN([AX_CHECK_GLIB],
  [
    GLIB_CFLAGS=
    GLIB_LIBS=
    PKG_CHECK_MODULES([GLIB],
      [glib-2.0],
      :,
      [AC_MSG_ERROR(*** glib2 not found)])
  ])