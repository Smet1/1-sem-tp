TARGET = main.out
# FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
# XXX: Don't forget backslash at the end of any line except the last one
HDRS = \
	    project/include

SRCS = \
		project/src/5-1.cpp

.PHONY: all clean

all: $(SRCS)
	$(CXX) -std=gnu++17 -Wall -Wextra -Werror $(addprefix -I,$(HDRS)) -o $(TARGET) $(CFLAGS) $(SRCS) $(FLAGS)

clean:
	rm -rf $(TARGET)
