CPPFILES := $(wildcard *.cpp)
BUILDDIR := build
OBJS := $(addprefix $(BUILDDIR)/,$(CPPFILES:%.cpp=%.o))
INCLUDEDIR := include
COMPILEFLAGS := g++ -g -Wall -std=c++20 -I $(INCLUDEDIR)

all: $(OBJS)
	$(COMPILEFLAGS) $(OBJS) -o $(BUILDDIR)/datanode.exe

clean:
	@rem Linux version:
	@rem if [-d $(BUILDDIR) ]; then
	@rem   rm -rf $(BUILDDIR)
	@rem fi
	@rem
	@rem Windows version:
	@if exist $(BUILDDIR) rmdir /s /q $(BUILDDIR)

$(BUILDDIR)/%.o : %.cpp
	$(COMPILEFLAGS) -c $< -o $@

$(OBJS): | $(BUILDDIR)

$(BUILDDIR):
	mkdir $(BUILDDIR)
