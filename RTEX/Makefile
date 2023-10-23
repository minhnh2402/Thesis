INC_DIR := Inc
SRC_DIR := Src
BUILD_DIR := Build
TARGET := main

INC_FILES := $(wildcard $(INC_DIR)/*.hpp)
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

CXX ?= g++
CFLAGS := -I$(INC_DIR)


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_FILES)
	$(CXX) $(CFLAGS) -c $< -o $@ -lhidapi-hidraw

$(TARGET): $(OBJ_FILES)
	$(CXX) $^ -o $@ -lhidapi-hidraw

all: $(TARGET)

run:
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)



