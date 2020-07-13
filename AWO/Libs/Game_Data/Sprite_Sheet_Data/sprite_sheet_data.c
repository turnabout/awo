#include <stdlib.h>
#include <stb_image/stb_image.h>

#include "Config/config.h"
#include "Game_Message/game_message.h"
#include "GL_Helpers/gl_helpers.h"
#include "Game_Data/Sprite_Sheet_Data/_sprite_sheet_data.h"

Sprite_Sheet_Data* create_sprite_sheet_data()
{
    Sprite_Sheet_Data* data = malloc(sizeof(Sprite_Sheet_Data));

    if (data == NULL) {
        printe("Sprite_Sheet_Data: ran out of memory");
        return NULL;
    }

    // Load texture image
    data->buffer = stbi_load(
        SPRITE_SHEET_PATH, 
        &data->width, 
        &data->height, 
        &data->channels_amount, 
        0
    );

    if (data == NULL) {
        printe("Sprite_Sheet_Data: failed to load sprite sheet image");
        free_sprite_sheet_data(data);
    }

    return data;
}

GLuint get_sprite_sheet_GL_texture(Sprite_Sheet_Data* data)
{
    return create_texture_object(data->buffer, data->width, data->height, data->channels_amount);
}

void get_sprite_sheet_dimensions(Sprite_Sheet_Data* data, int* width, int* height)
{
    *width = data->width;
    *height = data->height;
}

void free_sprite_sheet_data(Sprite_Sheet_Data* data)
{
    if (data == NULL) {
        return;
    }

    if (data->buffer != NULL) {
        stbi_image_free(data->buffer);
    }

    free(data);
}