ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libglengine.la
libglengine_la_SOURCES = src/glengine.cc \
	src/application.h \
	src/application.cc \
	src/arguments.h \
	src/arguments.cc

libglengine_la_CXXFLAGS = -I$(srcdir)/include

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

TESTS = tests/t_args

check_PROGRAMS = tests/engine

tests_engine_SOURCES = tests/engine.cc
tests_engine_LDADD = -lglengine
tests_engine_CXXFLAGS = -I$(srcdir)/include
