#pragma once
#include "GUI/clock.hpp"
#include <functional>
#include "game_enums.hpp"
#include "recording.hpp"

namespace minesweeper
{
    class recording;
	class game
	{
        friend class save;
	public:
        game() = default;
        game(int rows, int cols, int mine_count);
        game(const game& preset);
        ~game();
        click_type click_handler(int clk_cols, int clk_rows, click_type type);
        bool reveal(int rows,int cols);
        void init_map() const;
        void init_usermap() const;
        bool is_recording() const;
        game& enable_recording();
        recording& get_recording() const;
        static game* load_from_recording(const char* filename);
        game& save_recording(const char* filename);
        std::function<void(int,int,block_type)> update_hook = [](int,int,block_type) {};
        std::function<void(game&)> win_hook = [](game&){};
		std::function<void(game&)> lose_hook = [](game&){};
        std::function<void(game&, int, int)> start_hook = [](game&,int,int) {};
        game_difficulty get_difficulty() const;
		/*
		Initialize map with random mines.
		The map should be cleared before this function is called.
		(blockx,blocky) is the position that you don't want to have mines in it.
		*/
        void init_mines(int blockx=-1,int blocky=-1) const;
        void fill_map() const;
        bool check() const;
        int mine_count;
        int mine_left;
        int op_count;
        int rows;
        int cols;
        game_status status;
        char** map = nullptr;
        char** usermap = nullptr;
        gui::util::clock timer;
	private:
        bool enable_recording_ = false;
        recording* recording_;
        void lose();
        void win();
        void start(int x, int y);
	};

    
}