AC_DEFUN([AX_CHECK_FREETYPE2],
  [
    FREETYPE2_CFLAGS=
    FREETYPE2_LIBS=
    PKG_CHECK_MODULES([FREETYPE2],
      [freetype2],
      :,
      [AC_MSG_ERROR(*** glib2 not found)])
  ])