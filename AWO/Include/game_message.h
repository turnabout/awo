#pragma once

#define GAME_MSG_MAX_LEN 500

/*! @brief Different labels the game message can have.
 */
typedef enum Game_Message_Label {
    Error_Message,
    Plain_Message,
    Warning_Message,
    Info_Message,
} Game_Message_Label;

/*! @brief A message output by the game.
 */
typedef struct Game_Message {

    // The label of this game message.
    Game_Message_Label label;

    // This game message's actual message string.
    char str[GAME_MSG_MAX_LEN];

} Game_Message;

/*! @brief Gets the next game message on the game's stack of messages.
 *  @return The next game message available, or NULL if none are found.
 */
Game_Message* get_next_game_message();