# rule format is the following
# target: dependencies... (space separated list)
#	rule to make target (shell-interpreted commands)

### project related vars
EXTERNLIBPATH	="C:/Program Files/SDL2-2.0.22/x86_64-w64-mingw32"
SDL2_IMAGE_PATH	="C:/Program Files/SDL2_image"

INCLUDEDIRS		=Class $(EXTERNLIBPATH)/include $(SDL2_IMAGE_PATH)/include
SOURCEDIR		=Class
OBJECTDIR		=.obj
DEPENDENCYDIR	=.dep

CPPFILES		=$(wildcard $(SOURCEDIR)/*.cpp) $(wildcard $(SOURCEDIR)/TinyXML/*.cpp)
OBJECTS			=$(patsubst $(SOURCEDIR)/%.cpp,$(OBJECTDIR)/%.o,$(CPPFILES))
DEPFILES		=$(patsubst $(SOURCEDIR)/%.cpp,$(DEPENDENCYDIR)/%.d,$(CPPFILES))

LIBPATH			=-L"$(EXTERNLIBPATH)/lib" -L"$(SDL2_IMAGE_PATH)/lib/x64"
LIBS			=-lSDL2main -lSDL2 -lSDL2_image
LDFLAGS			=-w -Wall -lmingw32

#-Wl,-subsystem,windows
# flag used for release version, to remove the console window - add to $LDFLAGS instead of -Wall

PROGRAM =Minesweeper.exe

### compiler and linker related vars
CC ="g++"
# -g generated debugging info
# -Wall all compiler warnings, -Wfatal-errors on the errors that abort compilation
# O2 recommended optimization level
# -MP -MD are used for detecting changes in header files
CFLAGS =-g -Wfatal-errors -O2
# -MMD
# -MF tells the compiler where to store the generated .d files
# $* matches % from the rule
DEPFLAGS =-MMD -MF $(DEPENDENCYDIR)/$*.d

# -o specifies the name of the executable
all: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROGRAM) $(LIBPATH) $(LDFLAGS) $(LIBS)

# -c only compiles the given files, doesn't link them
# $@ is the target, $^ contains all the prerequisites, $< contains only the first prerequisite
./$(OBJECTDIR)/%.o: ./$(SOURCEDIR)/%.cpp ./$(DEPENDENCYDIR)/%.d | $(DEPENDENCYDIR) $(OBJECTDIR)
	$(CC) $(CFLAGS) $(foreach inc, $(INCLUDEDIRS), -I$(inc)) $(DEPFLAGS) -c $< -o $@

# if any of the header files changes, the cpp files including them should be rebuilt
# compiler generates dependency information in .d files.
./$(DEPENDENCYDIR)/%.d:
	
include $(DEPFILES)

# if these directories do not exist, create them.
# mkdir creates a dir with the given path, i.e. name
$(OBJECTDIR):
	mkdir $(OBJECTDIR)
$(DEPENDENCYDIR):
	mkdir $(DEPENDENCYDIR)

run: $(PROGRAM)
	$(PROGRAM)

# rmdir removes a dir tree. /S - removes everything, including the dir itself, /Q quiet mode, no prompts
# del deletes a file. /F = force delete, /Q = quiet mode, no prompts
clean:
	-rmdir /S /Q $(OBJECTDIR)
	-rmdir /S /Q $(DEPENDENCYDIR)
	-del /F /Q $(PROGRAM)