AC_DEFUN([AX_CHECK_GLM],
	[
		ax_glm_path=""
		AC_ARG_WITH([glm],
			[AS_HELP_STRING([--with-glm=<path>],
				[Set alternative path to the GLM headers. You should use path with glm folder])],
			[glm_include_path="$withval"],
			[glm_include_path=""])
		GLM_CXXFLAGS=
		AS_IF([test -n "$glm_include_path"], [GLM_CXXFLAGS="-I$glm_include_path"])
		CXXFLAGS+="$GLM_CXXFLAGS"
		AC_CHECK_HEADERS([glm/glm.hpp],
			[],
			[AC_MSG_ERROR(*** There is no GLM package installed)])
	])