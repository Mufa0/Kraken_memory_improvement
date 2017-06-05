CC = g++

 # compiler flags:
 #  -g    adds debugging information to the executable file
 #  -Wall turns on most, but not all, compiler warnings
 CFLAGS  = -g -Wall

 # the build target executable:
 TARGET = databaseSplit

 all: $(TARGET)

 $(TARGET): $(TARGET).cpp
	 $(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp -l sqlite3

 clean:
	 $(RM) $(TARGET)
