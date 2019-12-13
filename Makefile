# Project directories
AWO_DIR := AWO
AWO_EMX_DIR := AWO_Emscripten_App

# Project sources
AWO_SOURCES := $(shell find $(AWO_DIR) -name '*.c')
AWO_EMX_SOURCES := $(shell find $(AWO_EMX_DIR) -name '*.c')

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
	-I$(AWO_EMX_DIR) \
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
	\
	-s USE_WEBGL2=1 \
	-s USE_GLFW=3 \
	-s USE_FREETYPE=1




# -       -ISrc \
# -       -I../Libraries/Include \
# -       -lopenal \
# -       --preload-file Resources \
        # \

#  SOLUTION_DIR=$(SolutionDir.Replace('\', '\\'));SHADERS_DIR=Shaders\\;%(PreprocessorDefinitions)

#     $(SolutionDir)AWO\Src;$(SolutionDir)Libraries\Include;%(AdditionalIncludeDirectories)


# -s FULL_ES3=1 \

# -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap", "getValue", "setValue"]' \
# -s MODULARIZE=1 \
# -s EXPORT_NAME="AWO_EM_MODULE" \

# emcc -o ./Web/index.html $(SOURCES) \
# emcc -o ./Web/index.html ./Src/main.c \

# Old
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