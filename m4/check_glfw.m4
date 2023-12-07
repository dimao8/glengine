AC_DEFUN([AX_CHECK_GLFW],
  [
    AS_CASE([$host],
      [*-*-linux-*], [AX_CHECK_XLIB],
      [*-*-mingw-*], [AX_CHECK_GDI],
      [*-*-cygwin-*], [AX_CHECK_GDI])

    AC_CHECK_HEADERS([GLFW/glfw3.h],
      [],
      [AC_MSG_ERROR(*** There is no GLFW/glfw3.h)])

    ac_save_libs="$LIBS"
    LIBS="$ac_save_libs -lglfw3"
    AC_MSG_CHECKING(for -lglfw3)
    AC_LINK_IFELSE([AC_LANG_SOURCE(#include <GLFW/glfw3.h>
      int main()
      {
        glfwTerminate();
      })],
      [AC_MSG_RESULT(yes)],
      [
        AC_MSG_RESULT(no)
      ])

    LIBS="$ac_save_libs -lglfw"
    AC_MSG_CHECKING(for -lglfw)
    AC_LINK_IFELSE([AC_LANG_SOURCE(#include <GLFW/glfw3.h>
      int main()
      {
        glfwTerminate();
      })],
      [AC_MSG_RESULT(yes)],
      [
        AC_MSG_RESULT(no)
      ])
  ])