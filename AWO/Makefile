# export EMCC_DEBUG=1
SOURCES := $(shell find $(SOURCEDIR) -name '*.c')
OUTPUTPATH := $(AWO_GAME_OUTPUT)

all:
	emcc -o $(OUTPUTPATH) $(SOURCES) \
	-ISrc \
	-ISrc/Libraries \
	-Wall \
	--preload-file Resources \
	-s USE_SDL=2 \
	-s USE_SDL_IMAGE=2 \
	-s SDL2_IMAGE_FORMATS='["png"]' \
	-s USE_SDL_TTF=2 \
	-s EXPORTED_FUNCTIONS='["_init_AWO", "_run_AWO", "_update_game_size"]' \
	-s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' \
	-s MODULARIZE=1 \
	-s EXPORT_NAME="AWO_EM_MODULE" \
	-s ENVIRONMENT="web"

# -s DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=1 \
# emcc -o ./Web/index.html $(SOURCES) \
# emcc -o $(OUTPUTPATH) $(SOURCES) \
# -g4 \
