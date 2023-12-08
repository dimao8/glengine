AC_DEFUN([AX_CHECK_GLIB],
  [
    GIO_CFLAGS=
    GIO_LIBS=
    pkg-config --exists glib-2.0
    AS_IF([test "$?" = "0"],
      [
        GLIB_CFLAGS=`pkg-config --cflags glib-2.0`
        GLIB_LIBS=`pkg-config --libs glib-2.0`
      ],
      [
        AC_MSG_ERROR(*** libglib-2.0 not found)
      ])

      AC_SUBST(GLIB_CFLAGS)
      AC_SUBST(GLIB_LIBS)
  ])