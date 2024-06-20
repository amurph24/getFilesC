COMPILER = gcc
TARGET = getFiles
OBJECT_FILES =  ./*.o
COMPILER_FLAGS = -Wall -Wextra -pedantic-errors
SOURCE_FILES = source/*.c
TEST_ARG = name
INCLUDE_PATH = -I include/
INSTALL_PATH = /usr/local

all: $(TARGET)

install: $(TARGET)
	install -m755 $(TARGET) $(INSTALL_PATH)/bin
uninstall: 
	rm -f $(INSTALL_PATH)/bin/$(TARGET)

$(TARGET): object
	$(COMPILER) $(COMPILER_FLAGS) -o $@ $(OBJECT_FILES)

object:
	$(COMPILER) $(COMPILER_FLAGS) $(INCLUDE_PATH) -c $(SOURCE_FILES)

test: $(TARGET)
	touch test/out/filler
	rm test/out/*
	@echo "\n======================================="
	@echo "executing ./$< on $(TEST_ARG)..."
	@echo "======================================="
	@./$< $(TEST_ARG)

clean:
	rm $(OBJECT_FILES) $(TARGET)
