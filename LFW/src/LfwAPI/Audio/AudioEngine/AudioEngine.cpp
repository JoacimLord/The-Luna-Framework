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
		m_loaderResult = ma_engine_init(NULL, &m_miniAudioEngine);
		if (m_loaderResult != MA_SUCCESS)
		{
			//Debug msg
			return;
		}


	}

	void AudioEngine::Deactivate()
	{
		//Shut down everything (even if looping wasn't enabled)
		ma_engine_uninit(&m_miniAudioEngine);
			
		//Check if device and decoder is initalized (to prevent crashes)
		if (m_deviceActive) ma_device_uninit(&m_device);
		if (m_decoderActive) ma_decoder_uninit(&m_decoder);

		m_deviceActive = false;
		m_decoderActive = false;
	}

	void AudioEngine::PlayAudioFromFile(const char* filePath)
	{
		ma_engine_play_sound(&m_miniAudioEngine, filePath, NULL);
	}

	void AudioEngine::PlayAudioFromStreamedFile(ma_engine engine, ma_sound sound, const char* filePath)
	{
		ma_sound_init_from_file(&engine, filePath, MA_SOUND_FLAG_STREAM, NULL, NULL, &sound);
		ma_sound_start(&sound);
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
		m_loaderResult = ma_decoder_init_file(filePath, NULL, &m_decoder);
		if (m_loaderResult != MA_SUCCESS) return; //& debug msg?

		m_decoderActive = true;
		m_deviceActive = true;

		ma_data_source_set_looping(&m_decoder, MA_TRUE);


		m_deviceConfig = ma_device_config_init(ma_device_type_playback);
		m_deviceConfig.playback.format = m_decoder.outputFormat;
		m_deviceConfig.playback.channels = m_decoder.outputChannels;
		m_deviceConfig.sampleRate = m_decoder.outputSampleRate;
		m_deviceConfig.dataCallback = InitLooping;
		m_deviceConfig.pUserData = &m_decoder;

		//Just in case! If null, de-activate
		if (ma_device_init(NULL, &m_deviceConfig, &m_device) != MA_SUCCESS)
		{
			ma_decoder_uninit(&m_decoder);
			m_decoderActive = false;
		}

		if (ma_device_start(&m_device) != MA_SUCCESS)
		{
			ma_device_uninit(&m_device);
			ma_decoder_uninit(&m_decoder);
			m_deviceActive = false;
			m_decoderActive = false;
		}

	}

	void AudioEngine::SetMasterVolume(int volume)
	{
		ma_engine_set_volume(&m_miniAudioEngine, volume);
	}

	void AudioEngine::SetSoundVolume(ma_sound sound, int volume)
	{
		ma_sound_set_volume(&sound, volume);
	}

	void AudioEngine::StopMasterAudio()
	{
		ma_engine_stop(&m_miniAudioEngine);
	}

	void AudioEngine::StartMasterAudio()
	{
		ma_engine_start(&m_miniAudioEngine);
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
		m_soundMap.insert(SoundMap::value_type(key, filePath));
	}

	const char* AudioEngine::GetSoundFromMap(std::string key)
	{
		return m_soundMap.at(key);
	}
}
