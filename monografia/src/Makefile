#
# makefile para a compilação do documento
#
# Sáb Jun 23 21:13:37 BRT 2007
#

BASE_NAME = monografia

LATEX     = latex
PDFLATEX  = pdflatex
BIBTEX    = bibtex
MAKEINDEX = makeindex

TEXFILES  = $(wildcard *.tex)

all: pdf

pdf: $(BASE_NAME).pdf
	mv $(BASE_NAME).pdf ../

$(BASE_NAME).pdf: $(BASE_NAME).tex $(TEXFILES)
	$(PDFLATEX) $<
	$(BIBTEX) $(BASE_NAME)
	$(MAKEINDEX) $(BASE_NAME)
	$(PDFLATEX) $<
	$(PDFLATEX) $<
	$(PDFLATEX) $<


clean:
	rm -f $(BASE_NAME)*.ps $(BASE_NAME)*.dvi *.log \
	      *.aux *.blg *.toc *.brf *.ilg *.ind \
	      missfont.log $(BASE_NAME)*.bbl $(BASE_NAME)*.pdf $(BASE_NAME)*.out \
		  $(BASE_NAME)*.lof $(BASE_NAME)*.lot
