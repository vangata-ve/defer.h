.DEFAULT_GOAL := all

CC       ?= cc
CPPFLAGS ?= -Iinclude
CFLAGS   ?= -std=gnu11 -Wall -Wextra -Werror -O0

BUILD := build
EXAMPLES := hello cleanup fd mutex mmap

.PHONY: all clean

all: $(EXAMPLES:%=$(BUILD)/%)

$(BUILD):
	mkdir -p $@

$(BUILD)/%: examples/%.c | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(LDLIBS) $(LDFLAGS) -o $@

$(BUILD)/mutex: LDLIBS += -pthread
$(BUILD)/mutex: CFLAGS += -pthread

clean:
	rm -rf $(BUILD)