
/**
 * The enum of the game states.
 */
enum GameState {

    /// Print welcome message.
    WELCOME,

    /// Arduino goes in deep sleep and wait for interrupt.
    SLEEP,

    /// The led is fading and waiting for user input to start the game.
    WAITING,

    /// The game is starting, setup variables. 
    GAME_STARTING,

    /// A round is starting, setup variables and start the round.
    ROUND_STARTING,

    /// The ball is moving.
    MOVING_BALL,

    /// The ball is stopped on a led and waiting for user to press a button.
    STOPPED_BALL,

    /// The user pressed the correct button and the round is ending. 
    END_OF_ROUND,

    /// The user make an error and the game is ending.
    END_OF_GAME
};