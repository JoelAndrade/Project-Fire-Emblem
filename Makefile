all:
	windres -i images/icon/exe_icon.rc -O coff -o images/icon/exe_icon.res

	g++ \
	main.cpp \
	utilities/file/*.cpp utilities/SDL2/*.cpp \
	mode/title_screen/*.cpp mode/main_menu/*.cpp \
	save/*.cpp \
	-g \
	-I src/include -I utilities/SDL2 -I utilities/file \
	-L src/lib \
	-o main \
	-l mingw32 -l SDL2main -l SDL2 -l SDL2_image -l SDL2_ttf

	g++ \
	-mwindows -static-libgcc -static-libstdc++ \
	main.cpp \
	utilities/file/*.cpp utilities/SDL2/*.cpp \
	mode/title_screen/*.cpp mode/main_menu/*.cpp \
	save/*.cpp \
	-I src/include -I utilities/SDL2 -I utilities/file \
	-L src/lib \
	-o game images/icon/exe_icon.res \
	-l mingw32 -l SDL2main -l SDL2 -l SDL2_image -l SDL2_ttf