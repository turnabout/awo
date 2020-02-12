#include "Renderers/Stage_Renderer/_stage_renderer.h"
#include "Palette/palette.h"
#include "Config/config.h"

void update_stage_renderer_tile(Stage_Renderer* renderer, Uint8 x, Uint8 y)
{
    Stage_Tile stage_tile = renderer->stage->tiles_grid[y][x];
    Frame* frame = NULL;
    GLfloat palette_index = 0.0f;

    // Get the frame data for this tile
    if (is_tile_type_neutral(stage_tile.type)) {

        // Get neutral tile's frame
        Animation* tile_anim;
        gather_tile_data(renderer->game_data->tile, stage_tile.type, stage_tile.variation, NULL, &tile_anim);
        frame = &tile_anim->frames[0];
        palette_index = get_active_tile_palette_index(GL_FALSE);

    } else if (is_tile_type_property(stage_tile.type)) {

        // Get property tile's frame
        Frame** property_frame = get_property_type_frame(
            renderer->game_data->property,
            tile_to_property(stage_tile.type),
            get_stage_player_index_army_type(renderer->stage, (Player_Index)stage_tile.variation)
        );

        frame = *property_frame;
        palette_index = get_player_property_palette_index(stage_tile.variation);
    }

    if (frame == NULL) {
        return;
    }

    // Update the render grid(s) pixel for this tile's frame
    if (frame->height == DEFAULT_ENTITY_SIZE) {
        update_render_grid_pixel(
            renderer->grid_layers[TILE_LAYER_0],
            x,
            y,
            (vec4) { 
                frame->raw_top_left[0], 
                frame->raw_top_left[1],
                palette_index
            }
        );
    } else {
        update_render_grid_pixel(
            renderer->grid_layers[TILE_LAYER_0],
            x,
            y,
            (vec4) { 
                frame->raw_top_left[0], 
                frame->raw_top_left[1] + DEFAULT_ENTITY_SIZE,
                palette_index
            }
        );

        update_render_grid_pixel(
            renderer->grid_layers[TILE_LAYER_1],
            x,
            y,
            (vec4) { 
                frame->raw_top_left[0], 
                frame->raw_top_left[1],
                palette_index
        }
        );
    }
}
