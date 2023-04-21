AC_DEFUN([AX_CHECK_GDI],
  [
    LIBS+=-lgdi32
    AC_CHECK_HEADERS([windows.h],
      [],
      [AC_MSG_ERROR(*** There is no windows.h)])
    AC_LINK_IFELSE([AC_LANG_SOURCE(#include <windows.h>
      int main()
      {
        DeleteDC(0);
      })],
      [],
      AC_MSG_ERROR(*** There is no libgdi32))
  ])