COMPILER = gcc
TARGET = getFiles
OBJECT_FILES =  ./*.o
COMPILER_FLAGS = -Wall -Wextra -pedantic-errors
SOURCE_FILES = source/*.c
TEST_CSV = ./names.csv

all: $(TARGET)

$(TARGET): object
	$(COMPILER) $(COMPILER_FLAGS) -o $@ $(OBJECT_FILES)

object:
	$(COMPILER) $(COMPILER_FLAGS) -c $(SOURCE_FILES)

run: $(TARGET)
	./$< $(TEST_CSV)
