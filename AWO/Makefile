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
	-s EXPORTED_FUNCTIONS='["_init_AWO", "_run_AWO"]' \
	-s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' \
	-s MODULARIZE=1 \
	-s EXPORT_NAME="AWO_EM_MODULE" \
	-s ENVIRONMENT="web"


# -s MODULARIZE_INSTANCE=1 \
# -s FETCH=1 \
# -s ASMFS=1



# -s EXPORT_ES6=1 \
# -s EXPORT_ES6=1 -s MODULARIZE=
# --shell-file Web/template.html   
# -g4 
