AC_DEFUN([AX_CHECK_GLM],
	[
		GLM_CFLAGS=
    GLM_LIBS=
    PKG_CHECK_MODULES([GLM],
      [glm],
      :,
      [AC_MSG_ERROR(*** glm not found)])
	])