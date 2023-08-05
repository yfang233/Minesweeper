#include "save.hpp"
#include<filesystem>
#include<fstream>

#include "exceptions.hpp"
using namespace std;
#define BINARY_WRITE(file,ptr) \
	file.write(reinterpret_cast<const char*>(ptr),sizeof(*(ptr)))
#define BINARY_READ(file,ptr) \
	file.read(reinterpret_cast<char*>(ptr),sizeof(*(ptr)))

namespace minesweeper
{
	struct save_info
	{
		int rows;
		int cols;
		int mine_count;
		int mine_left;
		int op_count;
		size_t recording_timepoints; // 0 for disable recording
		long long elapsed_time;
		/* map data */
		/* usermap data */
		/* recording data */
		void create_from_game(const game& g)
		{
			rows = g.rows;
			cols = g.cols;
			mine_count = g.mine_count;
			mine_left = g.mine_left;
			recording_timepoints = (g.is_recording() ? g.get_recording().data.size() : 0);
			elapsed_time = g.timer.get_elapsed_time();
		}
	};

	fstream& operator<<(fstream& file, const save_info& info)
	{
		BINARY_WRITE(file, &info.rows);
		BINARY_WRITE(file, &info.cols);
		BINARY_WRITE(file, &info.mine_count);
		BINARY_WRITE(file, &info.mine_left);
		BINARY_WRITE(file, &info.op_count);
		BINARY_WRITE(file, &info.recording_timepoints);
		BINARY_WRITE(file, &info.elapsed_time);
		return file;
	}
	fstream& operator>>(fstream& file, save_info& info)
	{
		BINARY_READ(file, &info.rows);
		BINARY_READ(file, &info.cols);
		BINARY_READ(file, &info.mine_count);
		BINARY_READ(file, &info.mine_left);
		BINARY_READ(file, &info.op_count);
		BINARY_READ(file, &info.recording_timepoints);
		BINARY_READ(file, &info.elapsed_time);
		return file;
	}

	save save::create_from_game(game* g, const char* filename)
	{
		save s = save();
		s.filename_ = filename;
		s.game_obj = g;
		s.update();
		return s;
	}

	save save::load_from_file(const char* filename)
	{
		save s = save();
		s.filename_ = filename;
		const filesystem::path p(filename);
		if (!exists(p)) throw game_exception("save doesn't exist");
		fstream file(p, ios::in | ios::binary);
		for (const uint8_t i : save_magic_num)
		{
			uint8_t buf;
			BINARY_READ(file, &buf);
			if (buf != i)throw file_corrupted_exception();
		}

		save_header result{};
		{
			BINARY_READ(file, &result.version);
			if (result.version > current_recording_version) throw file_exception("higher version file not supported");
		}

		{
			save_info info{};
			file >> info;
			auto* g = new game(info.rows, info.cols, info.mine_count);
			g->mine_left = info.mine_left;
			g->op_count = info.op_count;
			g->enable_recording_ = (info.recording_timepoints != 0);
			g->timer = gui::util::clock();
			g->timer.set_time(info.elapsed_time);

			for (int i = 0; i <= info.rows + 1; i++)
			{
				for (int j = 0; j <= info.cols + 1; j++)
				{
					BINARY_READ(file, &g->map[i][j]);
				}
			}
			for (int i = 0; i <= info.rows + 1; i++)
			{
				for (int j = 0; j <= info.cols + 1; j++)
				{
					BINARY_READ(file, &g->usermap[i][j]);
				}
			}
			if (info.recording_timepoints)
			{
				g->recording_ = new recording(*g);
				for (auto i = 0; i < info.recording_timepoints; i++)
				{
					recording_timepoint timepoint{};
					file >> timepoint;
					g->recording_->add_timepoint(timepoint);
				}
			}
			g->status = GAME_INPROGRESS;
			s.game_obj = g;
		}
		file.close();

		return s;
	}

	void save::update() const
	{
		fstream file(filename_, ios::binary | ios::out | ios::trunc);
		if (!file) throw file_exception("file creation failed");
		file.write(reinterpret_cast<const char*>(save_magic_num), sizeof(save_magic_num));
		BINARY_WRITE(file, &default_header.version);
		save_info info{};
		info.create_from_game(*game_obj);
		file << info;
		for(int x=0;x<=info.rows+1;x++)
		{
			for(int y=0;y<=info.cols+1;y++)
			{
				BINARY_WRITE(file,&game_obj->map[x][y]);
			}
		}
		for (int x = 0; x <= info.rows + 1; x++)
		{
			for (int y = 0; y <= info.cols + 1; y++)
			{
				BINARY_WRITE(file, &game_obj->usermap[x][y]);
			}
		}

		if (info.recording_timepoints == 0) return;
		for (const auto& i : game_obj->get_recording().data)
		{
			file << i;
		}
	}

	void save::create_save(const char* filename)
	{
		const filesystem::path p(filename);
		if (exists(p)) throw game_exception("save already exists");
		fstream file(filename, ios::out | ios::trunc);
		if (!file) throw game_exception("save creation failed");

		file.write(reinterpret_cast<const char*>(save_magic_num), sizeof(save_magic_num));

		file << default_header.version;
		file.close();
	}
}
