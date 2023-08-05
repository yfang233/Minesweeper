#include "game.hpp"
#include<cassert>
#include<random>

#include "exceptions.hpp"

#define IS_REVEALED(x) (x>=0&&x<=8)

namespace minesweeper
{
	game::game(int rows, int cols, int mine_count)
	{
		assert(mine_count < rows * cols);

		map = new char*[rows + 2];
		usermap = new char*[rows + 2];
		for(int i=0;i<rows+2;i++)
		{
			map[i] = new char[cols + 2];
			usermap[i] = new char[cols + 2];
		}

		this->rows = rows;
		this->cols = cols;
		this->mine_count = mine_count;
		this->mine_left = mine_count;
		this->op_count = 0;
		this->status = GAME_READY;

		this->init_map();
		this->init_usermap();

	}

	game::game(const game& preset) : game(preset.rows,preset.cols,preset.mine_count){}

	game::~game()
	{
		if(usermap != nullptr && map != nullptr)
		{
			for (int i = 0; i < rows + 2; i++)
			{
				delete[] map[i];
				delete[] usermap[i];
			}
			delete[] map;
			delete[] usermap;
		}
	}

	void game::init_map() const
	{
		for (int i = 0; i <= cols + 1; i++) {
			map[0][i] = BARRIER;
			map[rows + 1][i] = BARRIER;
		}
		for (int i = 1; i <= rows; i++) {
			map[i][0] = BARRIER;
			map[i][cols + 1] = BARRIER;
		}
		for (int i = 1; i <= rows; i++) {
			for (int j = 1; j <= cols; j++) {
				map[i][j] = MINE0;
			}
		}
	}
	void game::init_usermap() const
	{
		for (int i = 0; i <= cols + 1; i++) {
			usermap[0][i] = BARRIER;
			usermap[rows + 1][i] = BARRIER;
		}
		for (int i = 1; i <= rows; i++) {
			usermap[i][0] = BARRIER;
			usermap[i][cols + 1] = BARRIER;
		}
		for (int i = 1; i <= rows; i++) {
			for (int j = 1; j <= cols; j++) {
				usermap[i][j] = UNKNOWN;
			}
		}
	}

	bool game::is_recording() const
	{
		return enable_recording_;
	}

	game& game::enable_recording()
	{
		if(status!=GAME_READY)
		{
			throw game_exception("you can't start recording if game already started");
		}
		enable_recording_ = true;
		return *this;
	}

	recording& game::get_recording() const
	{
		if (recording_ == nullptr)throw game_exception("recording doesn't exist");
		return *recording_;
	}

	game* game::load_from_recording(const char* filename)
	{
		auto* rec = new recording(filename);
		auto* g = new game();
		g->rows = rec->rows_;
		g->cols = rec->cols_;
		g->recording_ = rec;
		g->status = GAME_RECORDING;
		return g;
	}

	game& game::save_recording(const char* filename)
	{
		if (!enable_recording_)throw game_exception("there isn't any recording");
		if (status == GAME_READY)throw game_exception("game hasn't started yet");
		recording_->save(filename);
		return *this;
	}

	game_difficulty game::get_difficulty() const
	{
		if (rows == 9 && cols == 9 && mine_count == 10)
		{
			return DIFFICULTY_EASY;
		}
		if (rows == 16 && cols == 16 && mine_count == 40)
		{
			return DIFFICULTY_MEDIUM;
		}
		if (rows == 16 && cols == 30 && mine_count == 99)
		{
			return DIFFICULTY_HARD;
		}
		return DIFFICULTY_CUSTOM;
	}

	void game::init_mines(int blockx, int blocky) const
	{
		std::random_device dev;
		std::mt19937 generator(dev());
		std::uniform_int_distribution<std::mt19937::result_type> distributionx(1, rows);
		std::uniform_int_distribution<std::mt19937::result_type> distributiony(1, cols);
		int randx, randy;
		for(int i=0;i<mine_count;i++)
		{
			do
			{
				randx = distributionx(generator);
				randy = distributiony(generator);
			} while (map[randx][randy] == MINE || (randx == blockx && randy == blocky));
			map[randx][randy] = MINE;
		}
		fill_map();
	}

	/*
	Calculates the number of [type] around position (rows,cols)
	POSSIBLE OOB READ, PLEASE CHECK THE ARGUMENT BEFORE CALLING THIS FUNCTION
	*/
	int CalculateNum(char** map, int x, int y, block_type type) {
		int sum = 0;
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (i == 0 && j == 0) continue;
				sum += (map[x + i][y + j] == type ? 1 : 0);
			}
		}
		return sum;
	}

	void game::fill_map() const
	{
		for (int i = 1; i <= rows; i++) {
			for (int j = 1; j <= cols; j++) {
				if (map[i][j] == MINE)continue;
				map[i][j] = static_cast<block_type>(CalculateNum(map, i, j, MINE));
			}
		}
	}

	bool game::check() const
	{
		if (status != GAME_INPROGRESS)return false;
		int sum = 0;
		for (int i = 1; i <= rows; i++) {
			for (int j = 1; j <= cols; j++) {
				if (!IS_REVEALED(usermap[i][j])) sum++;
			}
		}
		return sum == mine_count;
	}

	bool game::reveal(int rows, int cols) {
		if (usermap[rows][cols] != UNKNOWN)return false;
		if (map[rows][cols] == MINE) {
			usermap[rows][cols] = BOOM;
			status = GAME_LOSE;
			update_hook(rows, cols, static_cast<block_type>(usermap[rows][cols]));
			lose();
			return true;
		}

		usermap[rows][cols] = map[rows][cols];
		update_hook(rows,cols, static_cast<block_type>(usermap[rows][cols]));

		assert(IS_REVEALED(usermap[rows][cols]));
		if (map[rows][cols] == MINE0) {
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					reveal(rows + i, cols + j);
				}
			}
		}
		return true;
	}

	click_type game::click_handler(int clk_cols, int clk_rows, click_type type) {
		assert(clk_rows > 0 && clk_cols > 0 && clk_cols <= this->cols && clk_rows <= this->rows);
		op_count++;
		auto result = CLK_INVALID;

		if(status==GAME_READY)
		{
			start(clk_rows,clk_cols);
		}

		switch (type)
		{
			//As the behavior of right click depends on the current status of the block, so we need to figure out the exact behavior
		case CLK_RIGHT:
			switch (usermap[clk_rows][clk_cols])
			{
			case UNKNOWN:
				usermap[clk_rows][clk_cols] = FLAG;
				update_hook(clk_rows, clk_cols, static_cast<block_type>(usermap[clk_rows][clk_cols]));
				mine_left--;
				result = CLK_FLAG;
				break;
			case FLAG:
				usermap[clk_rows][clk_cols] = QUESTION;
				update_hook(clk_rows, clk_cols, static_cast<block_type>(usermap[clk_rows][clk_cols]));
				mine_left++;
				result = CLK_QUESTION;
				break;
			case QUESTION:
				usermap[clk_rows][clk_cols] = UNKNOWN;
				update_hook(clk_rows, clk_cols, static_cast<block_type>(usermap[clk_rows][clk_cols]));
				result = CLK_CANCEL;
				break;
			default:
				return result;
			}
			break;

		case CLK_LEFT:
			if (usermap[clk_rows][clk_cols] != UNKNOWN) return result;
			reveal(clk_rows, clk_cols);
			result = CLK_LEFT;
			break;

		case CLK_DOUBLE:
			if (!IS_REVEALED(usermap[clk_rows][clk_cols]))return result;
			if (usermap[clk_rows][clk_cols] != CalculateNum(usermap, clk_rows, clk_cols, FLAG))return result;
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					if (map[clk_rows + i][clk_cols + j] == MINE && usermap[clk_rows + i][clk_cols + j] != FLAG) {
						usermap[clk_rows + i][clk_cols + j] = BOOM;
						update_hook(clk_rows + i, clk_cols + j, static_cast<block_type>(usermap[clk_rows + i][clk_cols + j]));
						lose();
						return result;
					}
				}
			}
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					if(reveal(clk_rows + i, clk_cols + j))
						result = CLK_DOUBLE;
				}
			}
			break;

		default:
			throw std::exception("unknown click type triggered");
			break;
		}
		if (check()) {
			status = GAME_WIN;
			win();
		}
		return result;
	}
	void game::lose()
	{
		timer.stop();
		status = GAME_LOSE;
		for(int i=1;i<=rows;i++){
			for(int j=1;j<=cols;j++){
				if(usermap[i][j]!=BOOM&&map[i][j]==MINE){
					usermap[i][j] = MINE;
					update_hook(i, j, MINE);
				}
			}
		}
		lose_hook(*this);
	}

	void game::win()
	{
		timer.stop();
		status = GAME_WIN;
		for (int i = 1; i <= rows; i++) {
			for (int j = 1; j <= cols; j++) {
				if (map[i][j] == MINE) {
					usermap[i][j] = MINE;
					update_hook(i, j, MINE);
				}
			}
		}
		win_hook(*this);
	}

	void game::start(int x, int y)
	{
		init_mines(x, y);
		timer.start();
		status = GAME_INPROGRESS;
		if(enable_recording_)
		{
			//if the game restarts, recording_ may not be nullptr and needs to be deleted
			delete recording_;
			recording_ = new recording(*this);
		}
		start_hook(*this, x, y);
	}
}
