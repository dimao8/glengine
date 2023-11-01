ACLOCAL_AMFLAGS = -I m4

SUBDIRS = libpngloader libtgaloader liblitejson

lib_LTLIBRARIES = libglengine.la
libglengine_la_SOURCES = src/application.h \
	src/application.cc \
	src/attribute.h \
	src/attribute.cc \
	src/arguments.h \
	src/arguments.cc \
	src/buffer.h \
	src/buffer.cc \
	src/camera.h \
	src/camera.cc \
	src/color.h \
	src/color.cc \
	src/image.h \
	src/image.cc \
	src/light.h \
	src/light.cc \
	src/logger.h \
	src/logger.cc \
	src/mesh.h \
	src/mesh.cc \
	src/opengl.h \
	src/opengl.cc \
	src/scene.h \
	src/scene.cc \
	src/scenenode.h \
	src/scenenode.cc \
	src/shader.h \
	src/shader.cc \
	src/shaderprogram.h \
	src/shaderprogram.cc \
	src/uuid.h \
	src/uuid.cc \
	src/vertexarray.h \
	src/vertexarray.cc

gle_includedir = $(includedir)/gle
gle_include_HEADERS =

libglengine_la_CXXFLAGS = -I$(srcdir)/include \
	-I$(srcdir)/libpngloader/include -I$(srcdir)/libtgaloader/include \
	-I$(srcdir)/liblitejson/include
libglengine_la_LIBADD = -L$(builddir)/libpngloader -lpngloader \
	-L$(builddir)/libtgaloader -ltgaloader -L$(builddir)/liblitejson -llitejson

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
