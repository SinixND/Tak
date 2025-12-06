#ifndef IG20251123234513
#define IG20251123234513

/**
 * @brief Configuration values for a match
 * 
 * Can be set/changed by user
 */
typedef struct
{
    /// Width and height of the playable board
    int boardSize;
} GameSettings;

GameSettings getDefaultSettings( void );

#endif
