AC_DEFUN([AX_CHECK_GLFW],
  [
    AC_CHECK_HEADERS([GLFW/glfw3.h],
      [],
      [AC_MSG_ERROR(*** There is no GLFW/glfw3.h)])

    LIBS+=-lglfw
    AC_MSG_CHECKING(for -lglfw)
    AC_LINK_IFELSE([AC_LANG_SOURCE(#include <GLFW/glfw3.h>
      int main()
      {
        glfwTerminate();
      })],
      [AC_MSG_RESULT(yes)],
      [
        AC_MSG_RESULT(no)
        AC_MSG_ERROR(*** There is no libglfw)
      ])
  ])