# Project directories
CC      = gcc
SRC_DIR = AWO
TARGET  = awo
SOURCES = $(shell find $(SRC_DIR) -name '*.c')
OBJECTS = $(SOURCES:.c=.o)

define CFLAGS
	-Wall \
	-IAWO/Include \
	-IExternal/Include \
	--debug
endef

# Build
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Compile
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(TARGET) $(OBJECTS)

#all:
#	emcc -o "./out/index.html" $(SOURCES) $(AWO_EMX_SOURCES) \
#	\
#	-D SOLUTION_DIR='""' \
#	-D SHADERS_DIR='"Shaders_ES/"' \
#	\
#	-Wall \
#	\
#	-IAWO \
#	-IAWO/Include \
#	-IExternal/Include \
#	\
#	-lopenal \
#	\
#	--preload-file $(SRC_DIR)/Resources \
#	\
#	-s ENVIRONMENT="web" \
#	-s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap", "getValue", "setValue"]' \
#	-s MODULARIZE=1 \
#	-s EXPORT_NAME="AWO_EM_MODULE" \
#	-s ALLOW_MEMORY_GROWTH=1 \
#	--no-heap-copy \
#	\
#	-s USE_WEBGL2=1 \
#	-s USE_GLFW=3 \
#	-s USE_FREETYPE=1 \
#	-LLibraries/Libs_Emscripten \
#	-lc_hashmap
#
#em-cli:
#	docker run \
#		-it \
#		--rm \
#		--name em-cli \
#		--volume $(PWD):/src \
#		--user $(id -u):$(id -g) \
#		emscripten/emsdk \
#			/bin/bash
#
#hashmap:
#	emcc -o External/Libs_Emscripten/c_hashmap.bc External/Libs_Emscripten/c_hashmap.c \
#	-I$(SRC_DIR)/Src \
#	-I$(SRC_DIR) \
#	-IExternal/Include
#
#cglm:
#	emcc -o External/Libs_Emscripten/cglm.bc $(CGLM_SOURCES) \
#	-IExternal/Include
#
#
#test:
#	emcc -o test.bc External/test.c \
#	IExternal/Include
#	emcc -o Web/index.html test.bc External/Libs_Emscripten/c_hashmap.bc External/Libs_Emscripten/cglm.bc \
#	-IExternal/Include
