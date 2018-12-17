TARGET = main.out
# FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
# XXX: Don't forget backslash at the end of any line except the last one
HDRS = \
	    project/include

SRCS = \
		project/src/2.cpp

.PHONY: all clean

all: $(SRCS)
	$(CXX) -std=gnu++17  $(addprefix -I,$(HDRS)) -o $(TARGET) $(CFLAGS) $(SRCS) $(FLAGS)

clean:
	rm -rf $(TARGET)
