.PHONY: all clean install uninstall dvi
DIR=./3D_Viewer_v2.0#  путь установки
INSTALL_PATH = $(DIR)
OS := $(shell uname -s)

ifeq ($(OS),Linux)
	OPEN_CMD=xdg-open
else
	OPEN_CMD=open
endif

all: install 

install: uninstall
	mkdir $(DIR) && cd $(DIR) && cmake -DCMAKE_BUILD_TYPE=Release  ../src && cmake --build .

uninstall:
	rm -rf $(DIR)

dist: uninstall install
	rm -rf dist_3DViewer/
	mkdir dist_3DViewer/
	mkdir dist_3DViewer/src
ifeq ($(OS), Linux)	
	mv $(INSTALL_PATH) dist_3DViewer/src/
else
	mv $(INSTALL_PATH)/3D_Viewer.app dist_3DViewer/src/
endif	
	tar cvzf dist_3DViewer.tar.gz dist_3DViewer/
	rm -rf dist_3DViewer/
	rm -rf $(INSTALL_PATH)

run: 
ifeq ($(OS),Linux)
	cd $(INSTALL_PATH) && ./3D_Viewer
else
	cd $(INSTALL_PATH)/3D_Viewer.app/Contents/MacOS && $(OPEN_CMD) ./3D_Viewer
endif

latex_install:
ifeq ($(OS),Linux)
	sudo apt install texlive-latex-base
	sudo apt install texlive-lang-cyrillic
	sudo fmtutil-sys --all
else
	brew install --cask mactex-no-gui
endif

libs_install:
ifeq ($(OS),Linux)
	sudo apt-get install qt6-base-dev libglu1-mesa-dev freeglut3-dev mesa-common-dev
endif

dvi:
	rm -rf *.aux
	rm -rf *.dvi
	rm -rf *.log
	latex ./readme.tex
	$(OPEN_CMD) ./readme.dvi
	
clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf dist/ 
	rm -rf dist_3DViewer.tar.gz
	rm -rf *.aux
	rm -rf *.dvi
	rm -rf *.log
	rm -rf *.ini


git_add:
	git add *.tex
	git add Makefile
	git add src/CMakeLists.txt
	git add src/*.cc
	git add src/QtGifImage-master
	git add src/model/*.cc
	git add src/model/*.h
	git add src/controller/*.cc
	git add src/controller/*.h
	git add src/view/*.cc
	git add src/view/*.h
	git add src/view/*.ui