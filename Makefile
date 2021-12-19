NAME := libutil.a
HNAME := libutil.hpp
HSCRIPT := create_header.py

PDIR := implementation

SDIR := $(PDIR)/src
ODIR := $(PDIR)/obj
DDIR := $(PDIR)/dep

# Files
SRC := $(shell find $(SDIR) -name "*.cpp" -type f)
OBJ := $(patsubst $(SDIR)/%.cpp,$(ODIR)/$(SUBDIR)%.o,$(SRC))
DEP := $(patsubst $(SDIR)/%.cpp,$(DDIR)/$(SUBDIR)%.d,$(SRC))
HDF := $(shell find $(SDIR) -name "*.hpp" -type f)

# Compilation
CXX = clang++
IFLAGS = -I.
CXXFLAGS = -Wall -Wextra -Werror -std=c++11 -pedantic
PY := python3

all: $(NAME) $(HNAME)

# Compilation
$(NAME): $(OBJ)
	@echo Creating $@
	@ar rcs $@ $(OBJ)
$(OBJ): $(ODIR)/$(SUBDIR)%.o: $(SDIR)/%.cpp Makefile
	@mkdir -p $(@D)
	@$(CXX) -c -o $@ $< $(CXXFLAGS) $(IFLAGS)
$(DDIR)/$(SUBDIR)%.d: $(SDIR)/%.cpp
	@mkdir -p $(@D)
	@$(CXX) $< -MM -MF $@ -MT $(ODIR)/$(SUBDIR)$*.o $(CXXFLAGS) $(IFLAGS)

# Make header file using script
$(HNAME): $(HDF) $(HSCRIPT)
	@$(PY) $(HSCRIPT) $(HDF)


# Cleanup
.PHONY: clean fclean re cleanall
clean:
	@echo Cleaning
	@$(RM) -r $(ODIR)
	@$(RM) -r $(DDIR)
fclean: clean
	@$(RM) $(HNAME)
	@$(RM) $(NAME)
re: fclean
	@$(MAKE) all

-include $(DEP)
