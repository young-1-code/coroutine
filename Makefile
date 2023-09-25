TARGET = mainApp
CFLGAS = -g -Wall
LDFLAGS =
SRCS = $(wildcard *.c)

$(TARGET): $(SRCS)
	$(CC) $(CFLGAS) -o $@ $^

.PHONY:clean
clean:
	@rm $(TARGET)