#include "Game_Data/Palette_Data/_palette_data.h"

Palette_Data_Row* get_palette_data_unit_row(Palette_Data* palette_data, Army_Type army, Bool done)
{
    int index = (army * 2) + done;
    return &(palette_data->buffer[index]);
}

Palette_Data_Row* get_palette_data_tile_row(Palette_Data* palette_data, Weather weather, Bool fog)
{
    int index = UNIT_PALETTE_COUNT + (weather * 2) + fog;
    return &(palette_data->buffer[index]);
}

Palette_Data_Row* get_palette_data_property_row(Palette_Data* palette_data, Army_Type army)
{
    int index = UNIT_PALETTE_COUNT + TILE_PALETTE_COUNT + army;
    return &(palette_data->buffer[index]);
}

Palette_Data_Row* get_palette_data_fog_property_row(Palette_Data* palette_data)
{
    int index = (UNIT_PALETTE_COUNT + TILE_PALETTE_COUNT + PROP_PALETTE_COUNT) - 1;
    return &(palette_data->buffer[index]);
}
