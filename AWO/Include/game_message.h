#pragma once

/*! @brief Different labels the game message can have.
 */
typedef enum Game_Message_Label {
    Error_Msg,
    Plain_Msg,
    Warning_Msg,
    Info_Msg,
} Game_Message_Label;

/*! @brief A message output by the game.
 */
typedef struct Game_Message {

    // The label of this game message.
    Game_Message_Label label;

    // This game message's actual message string.
    char* str;

} Game_Message;

/*! @brief Gets the next game message on the game's stack of messages.
 *
 *  @note Messages retrieved through this function must be freed using `free_game_message`.
 * 
 *  @return The next game message available, or NULL if none are found.
 */
Game_Message* get_next_game_message();

/*! @brief Frees memory allocated by the given game message.
 *  @param message The game message to free.
 */
void free_game_message(Game_Message* message);