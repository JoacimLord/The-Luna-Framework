#pragma once
#include "LfwAPI/Audio/MiniAudio/miniaudio.h"


// AudioEngine
/*
	This is my own API over the library "miniaudio".
	The API is heavily WIP but currently works fine for simple audio solutions within the framework.
*/

namespace LFW {

	typedef std::unordered_map<std::string, const char*> SoundMap;

	class AudioEngine
	{
	public:

		//Init() is called here
		AudioEngine();

		//Deactivate() is called here
		~AudioEngine();

		//Instantiates the sound engine
		void Init();

		//Shutdown of the sound egine
		void Deactivate();

		//Plays audio from filepath
		void PlayAudioFromFile(const char* filePath);

		//Streams audio from filepath
		void PlayAudioFromStreamedFile(ma_engine engine, ma_sound sound, const char* filePath);

		//Play audio with looping enabled
		void PlayAudioWithLooping(const char* filePath);

		//Controls volume of the whole engine
		void SetMasterVolume(int volume);

		//Controls volume of a single sound instance
		void SetSoundVolume(ma_sound sound, int volume);

		//Sets a fade timer for the beginning of an audio file
		void SetFadeTimer(ma_sound& sound, float startingTime, float endingTime, float fadeLengthInMilliSeconds);

		//Sets the position of an audio listener for a specific sound source
		void SetSoundListenerPosition(float x, float y, float z);

		//Sets the position of an audio listener for the sound engine
		void SetEngineListenerPosition(float x, float y, float z);

		//Adds a sounds filepath to an unordered_map with a specified key value
		void AddSoundToMap(std::string key, const char* filePath);

		//Gets a sounds filepath with a specified key value
		const char* GetSoundFromMap(std::string key);

	private:
		//Not needed?
		const char* m_FilePath;

		//Stores specified filepaths to sound files in an unordered_map
		SoundMap m_SoundMap;

		//miniaudio objects
		ma_result m_LoaderResult;
		ma_engine m_MiniAudioEngine;
		ma_decoder m_Decoder;
		ma_device_config m_DeviceConfig;
		ma_device m_Device;
	};
}
