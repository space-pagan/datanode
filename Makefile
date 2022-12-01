CPPFILES := $(wildcard *.cpp)
BUILDDIR := build
OBJS := $(addprefix $(BUILDDIR)/,$(CPPFILES:%.cpp=%.o))
INCLUDEDIR := include
COMPILEFLAGS := g++ -g -Wall -std=c++20 -I $(INCLUDEDIR)

ifeq ($(OS),Windows_NT)
	DELETECMD := rmdir /s /q $(BUILDDIR)
	SUPPRESSERRORCMD := > nul 2> nul
	TARGET := datanode.exe
else
	DELETECMD := rm -rf $(BUILDDIR)
	SUPPRESSERRORCMD := > /dev/null
	TARGET := datanode
endif

all: $(OBJS)
	$(COMPILEFLAGS) $(OBJS) -o $(BUILDDIR)/$(TARGET)

clean:
	$(shell $(DELETECMD)$(SUPPRESSERRORCMD))
	@echo $(DELETECMD)

$(BUILDDIR)/%.o : %.cpp
	$(COMPILEFLAGS) -c $< -o $@

$(OBJS): | $(BUILDDIR)

$(BUILDDIR):
	mkdir $(BUILDDIR)
