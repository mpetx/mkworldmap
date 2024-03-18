
CXX=g++
CFLAGS=$$(pkg-config --cflags stb)
LIBS=$$(pkg-config --libs stb)

BIN_DIR=bin
OBJ_DIR=obj
SRC_DIR=src

OBJECTS=main
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
