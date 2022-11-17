CPP = g++ -std=c++17 -Wall -Werror -Wextra
GCOV = --coverage
CHECK= -lgtest
BD = build

all: clean test

test: clean
	$(CPP) model/model.cc model/affin.cc model/model_test.cc $(CHECK) -o test
	./test

build: clean 
	mkdir $(BD)
	cp model/* controller/* view/* $(BD)/
	cp Makefile $(BD)/
	cd $(BD); qmake 3D_Viewer.pro
	make -C $(BD)
	cd $(BD); rm -rf *.cpp *.h *.h *.cc *.ui *.o *.pro* Makefile *glsl *qrc
	open $(BD)

install: build
	mkdir $(HOME)/Desktop/3D_Viewer/
	cp -rf $(BD) $(HOME)/Desktop/3D_Viewer/

uninstall:
	rm -rf $(HOME)/Desktop/3D_Viewer/
	rm -rf $(BD)

dist:
	rm -rf backup_3D_Viewer
	mkdir backup_3D_Viewer
	cp Makefile model/* controller/* view/* backup_3D_Viewer/
	tar -cvzf $(HOME)/Desktop/backup_3D_Viewer.tgz backup_3D_Viewer/
	rm -rf backup_3D_Viewer/

clean: uninstall
	rm -rf ./*.o report test build* ../build* view/*.user

leaks: test
	leaks -atExit -- ./test
