AC_DEFUN([AX_CHECK_OPENGL],
	[
dnl Check for GL/gl.h
		AC_CHECK_HEADERS([GL/gl.h],
			[],
			[AC_MSG_ERROR(*** There is no GL/gl.h)])

dnl Check for libraries
		ax_has_libgl=no
		ac_save_libs="$LIBS"
		LIBS="$ac_save_libs -lgl"
		AC_MSG_CHECKING([for -lgl])
		AC_LINK_IFELSE([AC_LANG_SOURCE(#include <GL/gl.h>
			int main(void)
			{
				glEnd();
			})],
			[
				ax_has_libgl=yes
			])
		AC_MSG_RESULT($ax_has_libgl)
		AS_IF([test "x$ax_has_libgl" != "xyes"],
			[
				LIBS="$ac_save_libs -lGL"
				AC_MSG_CHECKING([for -lGL])
				AC_LINK_IFELSE([AC_LANG_SOURCE(#include <GL/gl.h>
					int main(void)
					{
						glEnd();
					})],
					[
						ax_has_libgl=yes
					]
					)
				AC_MSG_RESULT($ax_has_libgl)
			])
		AS_IF([test "x$ax_has_libgl" != "xyes"],
			[
				LIBS="$ac_save_libs -lopengl32"
				AC_MSG_CHECKING([for -lopengl32])
				AC_LINK_IFELSE([AC_LANG_SOURCE(#include <GL/gl.h>
					int main(void)
					{
						glEnd();
					})],
					[
						ax_has_libgl=yes
					]
					)
				AC_MSG_RESULT($ax_has_libgl)
			])
	])