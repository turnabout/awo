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

/*! @brief Callback function receiving messages emanated by the game message module.
 *
 *  @note The message given to the function is freed automatically after the function is done
 *  executing.
 */
typedef void (*Game_Message_CB)(Game_Message*);

/*! @brief Sets the callback handling messages emitted by the game.
 *
 *  @param[in] animation_json The JSON representing this animation and its frames.
 *  @param[in] ss_width The tiles_width of the sprite sheet this animation comes from.
 *  @param[in] ss_height The tiles_height of the sprite sheet this animation comes from.
 */
void set_game_message_callback(Game_Message_CB callback);
