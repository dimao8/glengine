AC_DEFUN([AX_CHECK_GDI32],
  [
    GDI32_CFLAGS=
    GDI32_LIBS=-lgdi32
    save_libs="$LIBS"
    LIBS="$LIBS $GDI32_LIBS"
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
    LIBS="$save_libs"
  ])