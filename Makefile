CC = gcc
CFLAGS = -Wall
LDFLAGS =
OBJFILES = info.o utilities.o reporte.o els.o
TARGET = els
all = $(TARGET)

$(TARGET): $(OBJFILES)
		$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
		rm -f $(OBJFILES) $(TARGET) *~