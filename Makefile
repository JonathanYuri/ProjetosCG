ifeq ($(OS),Windows_NT)
RM = del /Q /F
ARG = -I"freeglut\include" -L"freeglut\lib" -lfreeglut -lopengl32
ifdef ComSpec
SHELL := $(ComSpec)
endif
ifdef COMSPEC
SHELL := $(COMSPEC)
endif
else
RM = rm -rf
ARG = -lGL -lGLU -lglut
endif

all:
	g++ main.cpp -o main.exe $(ARG)
	./main.exe

clean:
	@echo cleaning...
	-$(RM) *.exe
	@echo clean completed