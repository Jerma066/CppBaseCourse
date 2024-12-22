SRC_DIR  = src
GEN_DIR  = gen
TMP_DIR  = tmp
CXX      = g++
LEX      = flex
BISON    = bison
TEST     = test.sh

BIN_DIR  = bin
BIN_NAME = paracl
CXXFLAGS = -Wall -Werror

all : BIN_DIR  := $(BIN_DIR)/release
all : CXXFLAGS += -O3
all : build

debug : BIN_DIR  := $(BIN_DIR)/debug
debug : CXXFLAGS += -g -fsanitize=address
debug : build

clean :
	rm -fr $(BIN_DIR) $(GEN_DIR) $(TMP_DIR)

paracl-lexer:
	mkdir -p $(GEN_DIR)
	$(LEX) --header-file=$(GEN_DIR)/paracl-lexer.h -o $(GEN_DIR)/paracl-lexer.cpp $(SRC_DIR)/paracl-lexer.l

paracl-grammar: paracl-lexer
	mkdir -p $(GEN_DIR)
	$(BISON) $(SRC_DIR)/paracl-grammar.y --defines=$(GEN_DIR)/paracl-grammar.h -o $(GEN_DIR)/paracl-grammar.cpp

mk_dir:
	mkdir -p $(BIN_DIR)

build : mk_dir paracl-grammar paracl-lexer
	$(CXX) $(SRC_DIR)/*.cpp $(GEN_DIR)/*.cpp -I $(GEN_DIR)  -o $(BIN_DIR)/$(BIN_NAME)

test : BIN_DIR  := $(BIN_DIR)/debug
test : debug
	bash ./$(TEST) ./$(BIN_DIR)/$(BIN_NAME)
