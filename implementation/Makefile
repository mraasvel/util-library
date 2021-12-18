NAME := catch.out

# Lib settings
LNAME = util
LDIR := ..
LPATH := $(LDIR)/lib$(LNAME).a

# Compilation
CXX := clang++
CXXFLAGS := -Wall -Wextra -Werror -std=c++11
LFLAGS := -L$(LDIR) -l$(LNAME)
IFLAGS := -I$(LDIR)

SDIR := tests
ODIR := obj/catch
DDIR := dep/catch

SRC := $(shell find $(SDIR) -name "*.cpp" -type f)
OBJ := $(patsubst $(SDIR)/%.cpp,$(ODIR)/$(SUBDIR)%.o,$(SRC))
DEP := $(patsubst $(SDIR)/%.cpp,$(DDIR)/$(SUBDIR)%.d,$(SRC))

.PHONY: all library
all: library
	@$(MAKE) $(NAME) -j8
library:
	@$(MAKE) -C $(LDIR)

.PHONY: run
run:
	@$(MAKE) all
	@./catch.out

# Compilation
$(NAME): $(OBJ) $(LPATH)
	@echo Compiling $@
	@$(CXX) -o $@ $(OBJ) $(LFLAGS)
$(OBJ): $(ODIR)/$(SUBDIR)%.o: $(SDIR)/%.cpp Makefile
	@echo Compiling $@
	@mkdir -p $(@D)
	@$(CXX) -c -o $@ $< $(CXXFLAGS) $(IFLAGS)
$(DDIR)/$(SUBDIR)%.d: $(SDIR)/%.cpp
	@mkdir -p $(@D)
	@$(CXX) $< -MM -MF $@ -MT $(ODIR)/$(SUBDIR)$*.o $(CXXFLAGS) $(IFLAGS)

# Library
$(LPATH):
	@$(MAKE) -C $(LDIR)

# Cleanup
.PHONY: clean fclean re
clean:
	@$(RM) -r $(ODIR)
	@$(RM) -r $(DDIR)
fclean: clean
	@$(RM) $(NAME)
re: fclean
	@$(MAKE) all

-include $(DEP)
