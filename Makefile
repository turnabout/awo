# TODO: Remove once project becomes CMake-only
# Project directories
AWO_DIR := AWO

# Project sources
AWO_SOURCES := $(shell find $(AWO_DIR) -name '*.c')
CGLM_SOURCES := $(shell find cglm_input -name '*.c')

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
	-IExternal/Include \
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
	-s USE_FREETYPE=1 \
	-LLibraries/Libs_Emscripten \
	-lc_hashmap
	#-print-search-dirs

hashmap:
	emcc -o External/Libs_Emscripten/c_hashmap.bc External/Libs_Emscripten/c_hashmap.c \
	-I$(AWO_DIR)/Src \
	-I$(AWO_DIR) \
	-IExternal/Include

cglm:
	emcc -o External/Libs_Emscripten/cglm.bc $(CGLM_SOURCES) \
	-IExternal/Include


test:
	emcc -o test.bc External/test.c \
	-IExternal/Include
	emcc -o Web/index.html test.bc External/Libs_Emscripten/c_hashmap.bc External/Libs_Emscripten/cglm.bc \
	-IExternal/Include
