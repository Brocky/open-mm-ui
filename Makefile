TARGET = MainUI

CC 	= $(CROSS_COMPILE)g++

CFLAGS = -O3 -marm -mtune=cortex-a7 -mfpu=neon-vfpv4 -mfloat-abi=hard -march=armv7ve -Wall -std=c++17
LDFLAGS = -lSDL -lSDL_ttf -lmi_sys -lmi_gfx -s -lSDL -lSDL_image

SUBDIR = system theme view
SOURCES = src
DIR_OBJ = obj

INCS = $(wildcard $(SOURCES)/*.h $(foreach fd, $(SUBDIR), $(SOURCES)/$(fd)/*.h))
CFILES = $(wildcard $(SOURCES)/*.cpp $(foreach fd, $(SUBDIR), $(SOURCES)/$(fd)/*.cpp))
OFILES = $(CFILES:cpp=o)
INC_DIRS = $(addprefix -I$(SOURCES)/,$(SUBDIR))


$(TARGET): $(OFILES)
	$(CC) $(OFILES) -o $@ $(LDFLAGS)

%.o: %.cpp $(INCS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_DIRS)

clean:
	rm -f $(TARGET) $(OFILES)