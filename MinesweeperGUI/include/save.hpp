#pragma once
#ifndef __SAVE_H_
#define __SAVE_H_

#include "game.hpp"
#include <cstdint>
namespace minesweeper
{
	constexpr uint8_t save_magic_num[] = {0x40,0x90};
	constexpr uint8_t save_version = 1;
	struct save_header
	{
		uint8_t version;
	};
	constexpr save_header default_header = save_header{save_version};

	/* save file structure:
	 * struct save_info
	 * map data
	 * usermap data
	 * recording data
	 */

	class save
	{
	public:
		static save create_from_game(game* g, const char* filename);
		static save load_from_file(const char* filename);
		void update() const;
		game* game_obj = nullptr;
	private:
		save() = default;
		std::string filename_;
		static void create_save(const char* filename);

	};
}

#endif