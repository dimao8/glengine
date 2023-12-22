AC_DEFUN([AX_CHECK_GLFW3],
  [
    GLFW3_CFLAGS=
    GLFW3_LIBS=
    PKG_CHECK_MODULES([GLFW3],
      [glfw3],
      :,
      [AC_MSG_ERROR(*** glfw3 not found)])
  ])