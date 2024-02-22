CFLAGS = -g -Wall -DUSE_SYSCALL

TARGET = hellomakefile

all: $(TARGET)

$(TARGET): $(TARGET).c
	${CC} $(CFLAGS) -o $(TARGET) $(LDFLAGS) $(TARGET).c

clean:
	rm -f $(TARGET)
