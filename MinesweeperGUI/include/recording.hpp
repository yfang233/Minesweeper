#pragma once
#ifndef __RECORDING_H_
#define __RECORDING_H_

#include<vector>
#include "game.hpp"
#include <cstdint>
#include<list>
#include<fstream>
namespace minesweeper
{
	constexpr uint8_t recording_magic_num[]={ 0x30,0x50 };
	constexpr uint8_t current_recording_version = 1;
	class game;

	// As the recording only needs to show the usermap at every timepoint, there is no need for storing the game map. Just store the status change at every timepoint is enough.

	struct recording_timepoint
	{
		long long timepoint;
		int rows;
		int cols;
		char type; //stores block_type
	};

	/* recording file structure:
	 * magic_num    version    recording_timepoint
	 * recording_timepoint  ......
	 */
	std::fstream& operator>>(std::fstream& file, recording_timepoint& point);
	std::fstream& operator<<(std::fstream& file, const recording_timepoint& point);
	class recording
	{
	friend class game;
	public:
		explicit recording(const game& g);
		explicit recording(const char* filename);
		~recording();
		void add_timepoint(recording_timepoint timepoint);
		void save(const char* filename) const;
		std::list<recording_timepoint> data = std::list<recording_timepoint>();
	private:
		int rows_;
		int cols_;
		char** map;
	};
}

#endif