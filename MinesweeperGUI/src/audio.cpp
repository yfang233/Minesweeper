#include "audio.hpp"
#include<unordered_map>
#include "GUI/dir.hpp"
namespace minesweeper
{
	const std::unordered_map<int, const char*> audio_filenames = {
		{AUDIO_BGM,"assets/audio/bgm.mp3"},
		{AUDIO_BOOM,"assets/audio/boom.mp3"},
		{AUDIO_CLICK,"assets/audio/click.wav"}
	};
	audio::audio()
	{
		InitAudioDevice();
		for(int i=0;i<AUDIO_COUNT;i++)
		{
			audio_data_[i] = LoadSound(gui::util::dir::rel_to_abs(audio_filenames.find(i)->second).c_str());
		}
	}
	
	audio::~audio()
	{
		for (const auto& i : audio_data_)
		{
			UnloadSound(i);
		}
		CloseAudioDevice();
	}

	audio& audio::get_instance()
	{
		static audio instance;
		return instance;
	}

	void audio::play(audio_resources res) const
	{
		PlaySound(audio_data_[res]);
	}

	bool audio::is_ready() const
	{
		auto result = IsAudioDeviceReady();
		for (const auto& i : audio_data_)
		{
			result = result && IsSoundReady(i);
		}
		return result;
	}
}
