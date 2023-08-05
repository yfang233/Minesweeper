#pragma once
#ifndef __GAME_ENUMS_H_
#define __GAME_ENUMS_H_

namespace minesweeper
{
    enum block_type {
        BOOM = -6,
        BARRIER,
        MINE,
        FLAG,
        QUESTION,
        UNKNOWN,
        MINE0 = 0,
        MINE1, MINE2, MINE3, MINE4, MINE5, MINE6, MINE7, MINE8
    };

    enum click_type {
        CLK_RIGHT = 0,
        CLK_LEFT,
        CLK_FLAG,
        CLK_QUESTION,
        CLK_CANCEL,
        CLK_INVALID,
        CLK_DOUBLE = 9
    };

	enum game_status{
        GAME_READY,
        GAME_INPROGRESS,
        GAME_WIN,
        GAME_LOSE,
        GAME_RECORDING, //Playing recording
        GAME_UNKNOWN
    };

    enum game_difficulty
    {
        DIFFICULTY_CUSTOM=-1,
	    DIFFICULTY_EASY=0,
        DIFFICULTY_MEDIUM,
        DIFFICULTY_HARD,
        DIFFICULTY_COUNT
    };
}

#endif