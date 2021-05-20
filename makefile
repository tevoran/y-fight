CC=x86_64-w64-mingw32-g++

SRC=$(shell find src/. -name *.cpp)

CFLAGS=-mwindows -lmingw32 -o windows/y_fight.exe -Lwindows/libs -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lopengl32 -lglu32 -I src/ -Iwindows/include -static-libstdc++ -static-libgcc -pedantic -Wall 

main: $(SRC)
	$(CC) $(SRC) $(CFLAGS)


