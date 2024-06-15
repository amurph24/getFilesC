COMPILER = gcc
TARGET = getFiles
OBJECT_FILES =  ./*.o
COMPILER_FLAGS = -Wall -Wextra -pedantic-errors
SOURCE_FILES = source/*.c
TEST_CSV = names.csv
INCLUDE_PATH = -I include/

all: $(TARGET)

$(TARGET): object
	$(COMPILER) $(COMPILER_FLAGS) -o $@ $(OBJECT_FILES)

object:
	$(COMPILER) $(COMPILER_FLAGS) $(INCLUDE_PATH) -c $(SOURCE_FILES)

run: $(TARGET)
	@echo "\n======================================="
	@echo "executing ./$< on $(TEST_CSV)..."
	@echo "======================================="
	@./$< $(TEST_CSV)

clean:
	rm $(OBJECT_FILES) $(TARGET)
