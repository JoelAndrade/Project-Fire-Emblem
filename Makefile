all:
	windres -i images/icon/exe_icon.rc -O coff -o images/icon/exe_icon.res

	g++ \
	main.cpp debug.cpp \
	utilities/file/*.cpp utilities/SDL2/*.cpp \
	mode/title_screen/*.cpp mode/main_menu/*.cpp mode/level_1/*.cpp \
	save/*.cpp \
	-g \
	-I src/include -I utilities/SDL2 -I utilities/file -I classes/character_classes \
	-L src/lib \
	-o main \
	-l mingw32 -l SDL2main -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

	g++ \
	-mwindows -static-libgcc -static-libstdc++ \
	main.cpp debug.cpp \
	utilities/file/*.cpp utilities/SDL2/*.cpp mode/level_1/*.cpp \
	mode/title_screen/*.cpp mode/main_menu/*.cpp \
	save/*.cpp \
	-I src/include -I utilities/SDL2 -I utilities/file -I classes/character_classes \
	-L src/lib \
	-o game images/icon/exe_icon.res \
	-l mingw32 -l SDL2main -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer