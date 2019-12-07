# export EMCC_DEBUG=1
SOURCES := $(shell find $(SOURCEDIR) -name '*.c')
OUTPUTPATH := $(AWO_GAME_OUTPUT)

all:
	emcc -o ./Web/index.html $(SOURCES) \
	-ISrc \
	-I../Libraries/Include \
	-lopenal \
	-Wall \
	--preload-file Resources \
	-s FULL_ES3=1 \
	-s USE_GLFW=3 \
	-s USE_FREETYPE=1 \
	-s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap", "getValue", "setValue"]' \
	-s MODULARIZE=1 \
	-s EXPORT_NAME="AWO_EM_MODULE" \
	-s ENVIRONMENT="web"

# emcc -o $(OUTPUTPATH) $(SOURCES) \

# -s EXPORTED_FUNCTIONS='["_init_AWO", "_run_AWO", "_update_game_size", "_editor_get_next_tile_type", "_editor_get_next_tile_var"]' \
# -s DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=1 \
# emcc -o ./Web/index.html $(SOURCES) \
# emcc -o $(OUTPUTPATH) $(SOURCES) \
# -g4 \


# Old SDL parameters
# -s USE_SDL=2 \
# -s USE_SDL_IMAGE=2 \
# -s SDL2_IMAGE_FORMATS='["png"]' \
# -s USE_SDL_TTF=2 \
