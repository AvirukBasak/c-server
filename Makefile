SRCEXT      := c
OBJEXT      := o
HEADEREXT   := h

# directories

SRC_DIR     := src
BUILD_DIR   := build
TARGET_DIR  := target
LIB_DIR     := lib
TEST_DIR    := tests
INCLUDE_DIR := include
DEMO_DIR    := demo

# compiler options

LIB_NAME    := server

CC          := gcc
CFLAGS      := -Wall -Ofast
CDBGFLAGS   := -Wall -g -fsanitize=address -D DEBUG
DBG         := gdb -q

INCLUDE     := -I $(INCLUDE_DIR) -I $(LIB_DIR)
LIB         := -L$(LIB_DIR) -lm

LIBRARIES   := $(shell find $(LIB_DIR)/ -name "*.a")

# targets

TARGET_NAME := lib$(LIB_NAME)
TARGET      := $(TARGET_DIR)/$(TARGET_NAME).a
DBG_TARGET  := $(TARGET_DIR)/$(TARGET_NAME)-dbg.a
HDR_TARGET  := $(TARGET_DIR)/$(TARGET_NAME).$(HEADEREXT)

SOURCES     := $(shell find $(SRC_DIR)/ -name "*."$(SRCEXT))
HEADERS     := $(shell find $(INCLUDE_DIR)/ -name "*."$(HEADEREXT))
TESTSRC     := $(shell find $(TEST_DIR)/ -name "*."$(SRCEXT))

## release build

rel: mkdirp $(HDR_TARGET) $(TARGET)

OBJECTS     := $(patsubst $(SRC_DIR)/%.$(SRCEXT), $(BUILD_DIR)/%-rel.$(OBJEXT), $(shell find $(SRC_DIR)/ -name "*."$(SRCEXT)))

$(OBJECTS): $(SOURCES) $(HEADERS)
	@cd $(SRC_DIR) && $(MAKE)

$(TARGET): $(LIBRARIES) $(OBJECTS)
	ar rcs $(TARGET) $(BUILD_DIR)/*-rel.$(OBJEXT)

## debug build

dbg: mkdirp $(HDR_TARGET) $(DBG_TARGET)

DBG_OBJECTS := $(patsubst $(SRC_DIR)/%.$(SRCEXT), $(BUILD_DIR)/%-dbg.$(OBJEXT), $(shell find $(SRC_DIR)/ -name "*."$(SRCEXT)))

$(DBG_OBJECTS): $(SOURCES) $(HEADERS)
	@cd $(SRC_DIR) && $(MAKE) dbg

$(DBG_TARGET): $(LIBRARIES) $(DBG_OBJECTS)
	ar rcs $(DBG_TARGET) $(BUILD_DIR)/*-dbg.$(OBJEXT)

## make lib headers

$(HDR_TARGET): $(INCLUDE_DIR)/$(TARGET_NAME).$(HEADEREXT)
	@cp $(INCLUDE_DIR)/$(TARGET_NAME).$(HEADEREXT) $(HDR_TARGET)
	$(info make $(HDR_TARGET))

## build libraries
$(LIBRARIES):
	@cd $(LIB_DIR) && $(MAKE)

## testing / execution

test: rel $(TESTSRC)
	@$(CC) $(CFLAGS) -I $(TARGET_DIR) $(TEST_DIR)/test.$(SRCEXT) -o $(TEST_DIR)/test-rel.out -L$(TARGET_DIR) -l$(LIB_NAME) $(LIB)
	./$(TEST_DIR)/test-rel.out

## test in debug mode in gdb
testdbg: testdbg-build
	$(DBG) $(TEST_DIR)/test-dbg.out

## find memory leaks w/ -fsanitize
testmleak: testdbg-build
	@ASAN_OPTIONS=detect_leaks=1 ./$(TEST_DIR)/test-dbg.out

testdbg-build: dbg $(TESTSRC)
	@$(CC) $(CDBGFLAGS) -I $(TARGET_DIR) $(DBG_OBJECTS) $(TEST_DIR)/test.$(SRCEXT) -o $(TEST_DIR)/test-dbg.out $(LIB)

## demo
demo-name-age: $(DEMO_DIR)/name-n-age.c dbg
	@$(CC) $(CDBGFLAGS) -I $(TARGET_DIR) $(DEMO_DIR)/name-n-age.c -o $(DEMO_DIR)/name-n-age.out -L$(TARGET_DIR) -l$(LIB_NAME)-dbg $(LIB)
	@ASAN_OPTIONS=detect_leaks=1 ./$(DEMO_DIR)/name-n-age.out

demo-say-hello: $(DEMO_DIR)/say-hello.c dbg
	@$(CC) $(CDBGFLAGS) -I $(TARGET_DIR) $(DEMO_DIR)/say-hello.c -o $(DEMO_DIR)/say-hello.out -L$(TARGET_DIR) -l$(LIB_NAME)-dbg $(LIB)
	@ASAN_OPTIONS=detect_leaks=1 ./$(DEMO_DIR)/say-hello.out

## mkdirp

mkdirp:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(TARGET_DIR)

## cleanup

clean:
	@cd $(SRC_DIR) && $(MAKE) clean
	@cd $(LIB_DIR) && $(MAKE) clean
	@rm -rf $(TEST_DIR)/*.out
	@rm -rf $(DEMO_DIR)/*.out

cleaner:
	@cd $(SRC_DIR) && $(MAKE) cleaner
	@cd $(LIB_DIR) && $(MAKE) cleaner
	@rm -rf $(TEST_DIR)/*.out
	@rm -rf $(DEMO_DIR)/*.out
	@rm -rf $(BUILD_DIR)
	@rm -rf $(TARGET_DIR)
