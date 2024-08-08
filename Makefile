VERSION = 0.0.1

SRC_DIR   = ./src
OBJ_DIR   = ./out
BUILD_DIR = ./build

INCL_FLAGS = -I$(SRC_DIR)/includes
CXX_FLAGS  = --std=c++20
DEBUG_PRE  = -DDEBUG

INSTALL_PATH = /usr/local


# compiler
CC = /sbin/clang++

# search for C++ source files in ./src/*.cc and ./src/**/*.cc
# Reference code: https://stackoverflow.com/a/4038459/18592727
SRC_ALL  = $(wildcard $(SRC_DIR)/*.cc) $(filter-out $(wildcard $(SRC_DIR)/tests/*.cc),$(wildcard $(SRC_DIR)/**/*.cc))

# OBJ_ALL includes all the object files, including object files of files which have a main function (for testing purposes)
OBJ_ALL  = ${subst ./src,./out,${SRC_ALL:.cc=.o}}

# LOW_MAIN, excludes: the test files (files which have a `int main` function) and the api
EXCLUDE_MAIN = $(wildcard $(OBJ_DIR)/api/*.o)
LOW_MAIN = $(filter-out $(EXCLUDE_MAIN),$(OBJ_ALL))

# LOW_LIB, excludes: the test files (files which have a `int main` function) and the lowscript entrypoint
EXCLUDE_LIB = $(OBJ_DIR)/lowscript.o
LOW_LIB = $(filter-out $(EXCLUDE_LIB),$(OBJ_ALL))

# LOW_TESTS, excludes the api, the lowscript entry_point and he test files (files which have a `int main` function)
# the tests are excluded because then, we can run the `test` rule passing which his value is already a file within a `int main` function
EXCLUDE_TESTS = $(wildcard $(OBJ_DIR)/api/*.o) $(OBJ_DIR)/lowscript.o
LOW_TESTS = $(filter-out $(EXCLUDE_TESTS),$(OBJ_ALL)) 

# just shared, a static library could be crazy in this project, the final binary would be so large!
SHARED_LIB_NAME = lowscript.so.$(VERSION)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
# this mkdir command creates the directory
# where a object file should be placed if it does not exists
# reference from: https://stackoverflow.com/a/1951111/18592727
	@mkdir -p $(@D)
	$(CC) $(DEBUG_PRE) $(INCL_FLAGS) $(CXX_FLAGS) -c $< -o $@

$(BUILD_DIR)/$(SHARED_LIB_NAME): $(LOW_LIB)
	$(CC) $< -shared -fPIC -o $@

# --- EXPLICIT INVOKATED RULES ---

# build only the objects files, without link them to a binary file
objects: $(OBJ_ALL)

# take the neccesary objects files to build the final binary
lowscript: $(LOW_MAIN)
	$(CC) $(LOW_MAIN) -o $(BUILD_DIR)/$@

lib: $(LOW_LIB)
	$(CC) $(LOW_LIB) -fPIC -shared -o $(BUILD_DIR)/$(SHARED_LIB_NAME)

# generate a binary for testing purporses at BUILD_DIR
test: $(LOW_TESTS)
# test_file is received as a cli argument
# in this way we can execute the file we wants (always that is has a `int main` function in it)
	$(CC) $(INCL_FLAGS) $(CXX_FLAGS) $^ $(SRC_DIR)/tests/$(test_file).cc -o $(BUILD_DIR)/$(test_file).out

# executes the test binary file
# we recommeds the use of test and this task combineds
run: test
	$(BUILD_DIR)/$(test_file).out

run_low: lowscript
	$(BUILD_DIR)/$(LOW_MAIN)

all: lowscript lib

echo:
	@echo $(OBJ_ALL)

# Copies the contens of $(BUILD_DIR) at /usr/local/bin and /usr/local/lib
install: all
# you can change the install path passing as cli argument the name of the variable `INSTALL_PATH`
# example of use: `make install INSTALL_PATH="~/.local/"`
# NOTE: a bin, lib and include directories will be created in the passed path if them does not already exists
# in this case the results directories would: ~/.local/bin, ~/.local/lib, ~/.local/include

# NOTE: if the `INSTALL_PATH` change, remember to add the new path to the environment variable `$PATH`

# if condition checking if the execution is as root user
# reference from: https://stackoverflow.com/a/53670257/18592727
	@if ! [ "$(shell id -u)" = 0 ]; then \
		echo "You are not root, run this target as root please"; \
		exit 1; \
	fi; \

	mkdir -p $(INSTALL_PATH)/bin && cp $(BUILD_DIR)/lowscript $(INSTALL_PATH)/bin;
	mkdir -p $(INSTALL_PATH)/include && cp $(SRC_DIR)/include/lowscript.h $(INSTALL_PATH)/include;
	mkdir -p $(INSTALL_PATH)/lib && cp $(BUILD_DIR)/$(SHARED_LIB_NAME) $(INSTALL_PATH)/lib;

# Removes the contents copied by the `install` rule
uninstall:
# NOTE: if the environtment variable is changed and new bin, lib and include directories are created, then them will not be removed
# in this way we avoid to drop another files from other active program / service. If you want, after exec `uninstall` rule, you can uninstall them manually
	@if ! [ "$(shell id -u)" = 0 ]; then \
		echo "You are not root, run this target as root please"; \
		exit 1; \
	fi; \

# delete the binary lowscript
	rm -v $(INSTALL_PATH)/bin/lowscript
# delete the directory lowscript and his contents 'lowscript.so.[version]'
	rm -rv $(INSTALL_PATH)/lib/lowscript
# delete the lowscript header file
	rm -v $(INSTALL_PATH)/include/lowscript.h

clean:
	rm -rv out/*
	rm -rv build/*
