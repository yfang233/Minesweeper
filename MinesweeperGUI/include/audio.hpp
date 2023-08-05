#pragma once
#ifndef __AUDIO_H_
#define __AUDIO_H_

#include <vector>

#include "raylib/raylib.h"

namespace minesweeper
{
	enum audio_resources
	{
		AUDIO_BGM,
		AUDIO_BOOM,
		AUDIO_CLICK,
		AUDIO_COUNT
	};
	
	class audio
	{
	public:
		static audio& get_instance();
		void play(audio_resources res) const;
		bool is_ready() const;
	private:
		audio();
		~audio();
		audio(const audio&) = default;
		audio& operator=(const audio&) = default;
		std::vector<Sound> audio_data_ = std::vector<Sound>(AUDIO_COUNT);
	};
}

#endif