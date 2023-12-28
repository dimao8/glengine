AC_DEFUN([AX_CHECK_FREETYPE2],
  [
    FREETYPE2_CFLAGS=
    FREETYPE2_LIBS=
    PKG_CHECK_MODULES([FREETYPE2],
      [freetype2 >= 2.0.0],
      :,
      [AC_MSG_ERROR(*** freetype2 not found)])
  ])