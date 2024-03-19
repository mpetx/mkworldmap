
CXX=g++
CFLAGS=$$(pkg-config --cflags stb) -std=c++20
LIBS=$$(pkg-config --libs stb)

BIN_DIR=bin
OBJ_DIR=obj
SRC_DIR=src

OBJECTS=main earth_texture projection image_creator
ALL=$(addprefix $(BIN_DIR)/, mkworldmap)

.PHONY: all
all: $(ALL)

$(BIN_DIR)/mkworldmap: $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(OBJECTS)))
	-@mkdir -p $(@D)
	$(CXX) $(LIBS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cxx
	-@mkdir -p $(@D)
	$(CXX) $(CFLAGS) -c -o $@ $^

.PHONY: clean
clean:
	-@rm -rf $(BIN_DIR) $(OBJ_DIR)
