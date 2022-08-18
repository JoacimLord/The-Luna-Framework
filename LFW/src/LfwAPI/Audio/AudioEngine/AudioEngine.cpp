#include "LFWpch.h"
#include "AudioEngine.h"

namespace LFW {

	//API
	//AudioEngine engine;
	//engine.LoadSound(filePath);
	//engine.PlaySound(filePath);

	AudioEngine::AudioEngine()
	{
		//Init
		Init();
	}

	AudioEngine::~AudioEngine()
	{
		Deactivate();
	}

	void AudioEngine::Init()
	{
		m_LoaderResult = ma_engine_init(NULL, &m_MiniAudioEngine);
		if (m_LoaderResult != MA_SUCCESS)
		{
			//Debug msg
			return;
		}
	}

	void AudioEngine::Deactivate()
	{
		//Shut down everything (even if looping wasn't enabled)
		ma_engine_uninit(&m_MiniAudioEngine);
		ma_device_uninit(&m_Device);
		ma_decoder_uninit(&m_Decoder);
	}

	void AudioEngine::PlayAudioFromFile(const char* filePath)
	{
		ma_engine_play_sound(&m_MiniAudioEngine, filePath, NULL);
	}

	void AudioEngine::PlayAudioFromStreamedFile(ma_engine engine, ma_sound sound, const char* filePath)
	{
		ma_sound_init_from_file(&engine, filePath, MA_SOUND_FLAG_STREAM, NULL, NULL, &sound);
	}

	// This function is specified outside of the scope of the AudioEngine class and
	// is used as a callback by miniaudio for enabling the looping of sounds and shouldn't be used outside of this specific use-case.
	void InitLooping(ma_device* device, void* output, const void* input, ma_uint32 frameCount)
	{
		ma_decoder* decoder = (ma_decoder*)device->pUserData;
		if (decoder == NULL)
		{
			//Debugmsg
			return;
		}

		ma_data_source_read_pcm_frames(decoder, output, frameCount, NULL);
		(void)input;
	}

	void AudioEngine::PlayAudioWithLooping(const char* filePath)
	{
		m_LoaderResult = ma_decoder_init_file(filePath, NULL, &m_Decoder);
		if (m_LoaderResult != MA_SUCCESS) return; //& debug msg?

		ma_data_source_set_looping(&m_Decoder, MA_TRUE);


		m_DeviceConfig = ma_device_config_init(ma_device_type_playback);
		m_DeviceConfig.playback.format = m_Decoder.outputFormat;
		m_DeviceConfig.playback.channels = m_Decoder.outputChannels;
		m_DeviceConfig.sampleRate = m_Decoder.outputSampleRate;
		m_DeviceConfig.dataCallback = InitLooping;
		m_DeviceConfig.pUserData = &m_Decoder;

		//Just in case! If null, de-activate
		if (ma_device_init(NULL, &m_DeviceConfig, &m_Device) != MA_SUCCESS)
		{
			ma_decoder_uninit(&m_Decoder);
		}

		if (ma_device_start(&m_Device) != MA_SUCCESS)
		{
			ma_device_uninit(&m_Device);
			ma_decoder_uninit(&m_Decoder);
		}

	}

	void AudioEngine::SetMasterVolume(int volume)
	{
		ma_engine_set_volume(&m_MiniAudioEngine, volume);
	}

	void AudioEngine::SetSoundVolume(ma_sound sound, int volume)
	{
		ma_sound_set_volume(&sound, volume);
	}

	void AudioEngine::SetFadeTimer(ma_sound& sound, float startingTime, float endingTime, float fadeLengthInMilliSeconds)
	{
		ma_sound_set_fade_in_milliseconds(&sound, startingTime, endingTime, fadeLengthInMilliSeconds);
	}

	void AudioEngine::SetSoundListenerPosition(float x, float y, float z)
	{
		//TODO
	}

	void AudioEngine::SetEngineListenerPosition(float x, float y, float z)
	{
		//TODO
	}

	void AudioEngine::AddSoundToMap(std::string key, const char* filePath)
	{
		m_SoundMap.insert(SoundMap::value_type(key, filePath));
	}

	const char* AudioEngine::GetSoundFromMap(std::string key)
	{
		return m_SoundMap.at(key);
	}
}
