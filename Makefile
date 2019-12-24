# Project directories
AWO_DIR := AWO

# Project sources
AWO_SOURCES := $(shell find $(AWO_DIR) -name '*.c')

# Output path (environment variable)
OUTPUTPATH := $(AWO_GAME_OUTPUT)

all:
	emcc -o $(OUTPUTPATH) $(AWO_SOURCES) $(AWO_EMX_SOURCES) \
	\
	-D SOLUTION_DIR='""' \
	-D SHADERS_DIR='"Shaders_ES/"' \
	\
	-Wall \
	\
	-I$(AWO_DIR)/Src \
	-I$(AWO_DIR) \
	-ILibraries/Include \
	\
	-lopenal \
	\
	--preload-file $(AWO_DIR)/Resources \
	\
	-s ENVIRONMENT="web" \
	-s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap", "getValue", "setValue"]' \
	-s MODULARIZE=1 \
	-s EXPORT_NAME="AWO_EM_MODULE" \
	-s ALLOW_MEMORY_GROWTH=1 \
	--no-heap-copy \
	\
	-s USE_WEBGL2=1 \
	-s USE_GLFW=3 \
	-s USE_FREETYPE=1
