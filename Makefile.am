ACLOCAL_AMFLAGS = -I m4

SUBDIRS = libpngloader libtgaloader liblitejson

lib_LTLIBRARIES = libglengine.la
libglengine_la_SOURCES = src/engine.cc \
	src/application.cc \
	src/arguments.cc \
	src/logger.cc \
	src/opengl.h \
	src/opengl.cc \
	src/image.cc \
	src/color.cc \
	src/shader.cc \
	src/shaderprogram.cc

include_HEADERS = include/gle/application.h \
	include/gle/arguments.h \
	include/gle/engine.h \
	include/gle/logger.h \
	include/gle/image.h \
	include/gle/color.h \
	include/gle/shader.h \
	include/gle/shaderprogram.h

libglengine_la_CXXFLAGS = -I$(srcdir)/include -I$(srcdir)/libpngloader/include -I$(srcdir)/libtgaloader/include -I$(srcdir)/liblitejson/include
libglengine_la_LIBADD = -L$(builddir)/libpngloader -lpngloader -L$(builddir)/libtgaloader -ltgaloader -L$(builddir)/liblitejson -llitejson

CLEANFILES =
SUFFIXES =

# Documents
if BUILD_DOC
dist_doc_DATA = doc/glengine.tex

SUFFIXES += .tex .aux .pdf
DOCDIR = doc
DOCNAME = $(DOCDIR)/glengine
DOCPDF = $(DOCNAME).pdf
DOCSRC = $(DOCNAME).tex
DOCAUX = $(DOCNAME).aux
doc_DATA = $(DOCPDF)
PDFLATEXOPTS = --output-directory=$(DOCDIR)
CLEANFILES += $(DOCPDF) $(DOCNAME).log $(DOCNAME).aux $(DOCNAME).toc \
	$(DOCNAME).out $(DOCNAME).idx $(DOCNAME).ilg $(DOCNAME).ind $(DOCNAME).btmp

%.pdf : %.aux
	@echo === Making PDF: $@ from $^ ===
	$(MKDIR_P) $(DOCDIR)
	$(PDFLATEX) $(PDFLATEXOPTS) $(srcdir)/$(DOCSRC)
	@while ( grep "Rerun to " \
		$(DOCNAME).log ); do \
			echo '** Re-running LaTeX **';      \
			$(PDFLATEX) $(PDFLATEXOPTS) $(srcdir)/$(DOCSRC); \
	done
	if [ -f $(DOCNAME).idx]; then \
		echo === Making index ===; \
		makeindex $(DOCNAME); \
	fi
	$(PDFLATEX) $(PDFLATEXOPTS) $(srcdir)/$(DOCSRC)

%.aux : %.tex
	@echo === Making $@ file from $^ ===
	$(MKDIR_P) $(DOCDIR)
	$(PDFLATEX) $(PDFLATEXOPTS) $(srcdir)/$(DOCSRC)
endif

# Tests
TESTS = tests/t_args

check_PROGRAMS = tests/app

tests_app_SOURCES = tests/app.cc
tests_app_LDADD = -lglengine
tests_app_CXXFLAGS = -I$(srcdir)/include
