# export EMCC_DEBUG=1
SOURCES := $(shell find $(SOURCEDIR) -name '*.c')

all:
	emcc -o Web/index.html $(SOURCES) \
	-Wall -lm \
	-s USE_SDL=2 \
	-s USE_SDL_IMAGE=2 \
	-s SDL2_IMAGE_FORMATS='["png"]' \
	-s USE_SDL_TTF=2 \
	-ISrc \
	-ISrc/Libraries \
	--preload-file Resources
