ACLOCAL_AMFLAGS = -I m4

bin_PROGRAMS = glengine
glengine_SOURCES = src/glengine.cc \
	src/application.h \
	src/application.cc

if DEBUG
	glengine_CFLAGS = -DDEBUG -g -O0
else
	glengine_CFLAGS = -DNDEBUG -O2
endif

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
