#include "PlacementSystem.h"
#include "Board.h"
#include "Game.h"
#include "MatchConstants.h"
#include "Players.h"
#include "Stacks.h"
#include "Stones.h"
#include <check.h>

START_TEST( PlaceStone )
{
    //* SETUP
    Game game = {
        .gameSettings = {
            .boardSize = 3
        },
        .matchConstants = { .regularStoneReserves = 1, .capstoneReserves = 1 },
        .players = initPlayers( 2, game.matchConstants.regularStoneReserves, game.matchConstants.capstoneReserves ),
        .stones = initStones( 2, getTotalReserves( game.matchConstants ) ),
        .stacks = initStacks( game.gameSettings.boardSize ),
        .board = initBoard( game.gameSettings.boardSize )
    };

    //* EXECUTE
    placeStoneOnBoard(
        &game.players,
        &game.board,
        &game.stacks,
        &game.stones,
        0,
        0,
        0,
        FLAT
    );

    //* VERIFY
    ck_assert_int_eq( game.matchConstants.regularStoneReserves - game.players.regularReserves[0], 1 );

    //* CLEANUP
    deinitGame( &game );
}

END_TEST
