TARGET = main.out
# TST_TARGET = tests.out

# XXX: Don't forget backslash at the end of any line except the last one
# Main
HDRS = \
	   project/include

SRCS = \
	   project/src/main.c 

.PHONY: all main test clean

# all: main test

main: $(SRCS)
	$(CC) -Wall -Wextra -Werror $(addprefix -I,$(HDRS)) -o $(TARGET) $(CFLAGS) $(SRCS) -lm

clean:
	rm -f $(TARGET) $(TST_TARGET)
