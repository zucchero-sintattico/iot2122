
/**
 * The enum of the game states.
 */
enum GameState {

    /// The welcome state.
    WELCOME,

    /// The game is waiting for the player to press the first button.
    SLEEP,

    /// The game is waiting for the player to press the second button.
    WAITING,

    /// The game is waiting for the player to release the first button.
    GAME_STARTING,

    /// The game is waiting for the player to release the second button.
    ROUND_STARTING,

    /// The game is waiting for the player to release the second button.
    MOVING_BALL,

    /// The game is waiting for the player to release the second button.
    STOPPED_BALL,

    /// The game is waiting for the player to release the second button.
    END_OF_ROUND,

    /// The game is waiting for the player to release the second button.
    END_OF_GAME
};