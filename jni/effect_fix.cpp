#include "org_fmod_example_EffectUtils.h"
#include "inc/fmod.hpp"
#include <stdlib.h>
#include <unistd.h>
#include <android/log.h>
#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"renzhenming",FORMAT,##__VA_ARGS__)
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"renzhenming",FORMAT,##__VA_ARGS__)

#define MODE_NORMAL 0
#define MODE_LUOLI 1
#define MODE_DASHU 2
#define MODE_JINGSONG 3
#define MODE_GAOGUAI 4
#define MODE_KONGLING 5

using namespace FMOD;

JNIEXPORT void JNICALL Java_org_fmod_example_EffectUtils_fix
  (JNIEnv *env, jclass jcls, jstring path_jstr, jint type){

	System            *system;
	FMOD_RESULT       result;
	Sound             *sound;
	Channel 		  *channel;
	DSP			      *dsp;
	float		      frequency = 0;
	bool isPlaying = true;
	const char *media_path = env->GetStringUTFChars(path_jstr,NULL);
	try {
			//初始化
			result = System_Create(&system);
			result = system->init(32, FMOD_INIT_NORMAL, NULL);
			//创建声音

			//这里进坑了，写作下边的样子是无法播放的，正确的方式是第二行 因为sound如果是null,那么，播放的时候的sound也就是null,怎么播放呢
			//result = system->createSound(media_path, FMOD_DEFAULT, 0, NULL);
			LOGI("%s",media_path);
			system->createSound(media_path, FMOD_DEFAULT, NULL, &sound);
			switch(type){
				case MODE_NORMAL:
					//原生播放
					result = system->playSound(sound, 0, false, &channel);
					break;

				case MODE_LUOLI:
					//dsp -- 音效
					//FMOD_DSP_TYPE_PITCHSHIFT 提升或者降低音调用的一种音效
					system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT,&dsp);
					//设置音调的参数
					dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH,2);
					//播放(播放和添加channel的顺序必须是先播放，再添加，否则音效无法生效)
					//猜测原因
					//playSound之后并不是立即播放，而是在system->update();之后开始播放，
					//playSound的作用是创造了一个sound载体一个channel载体，然后在这个载体基础上添加一系列的效果，所以，只能现有载体
					//效果才有放置的位置，所以需要先play再添加
					result = system->playSound(sound, 0, false, &channel);
					//添加到channel
					channel->addDSP(0,dsp);

					break;
				case MODE_DASHU:
					//dsp -- 音效
					//FMOD_DSP_TYPE_PITCHSHIFT 提升或者降低音调用的一种音效
					system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT,&dsp);
					//设置音调的参数
					dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH,0.6);
					//播放(播放和添加channel的顺序必须是先播放，再添加，否则音效无法生效)
					result = system->playSound(sound, 0, false, &channel);
					//添加到channel
					channel->addDSP(0,dsp);

					break;
				case MODE_GAOGUAI:
					//提高说话的速度
					result = system->playSound(sound, 0, false, &channel);
					channel->getFrequency(&frequency);\
					frequency = frequency*1.5;
					channel->setFrequency(frequency);
					break;
				case MODE_KONGLING:
					system->createDSPByType(FMOD_DSP_TYPE_ECHO,&dsp);
					dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY,300);
					dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK,2);
					result = system->playSound(sound, 0, false, &channel);
					channel->addDSP(0,dsp);
					break;
				case MODE_JINGSONG:
					//紧张
					system->createDSPByType(FMOD_DSP_TYPE_ECHO,&dsp);
					dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW,0.5);
					result = system->playSound(sound, 0, false, &channel);
					channel->addDSP(0,dsp);
					break;
				default:
					break;
			}
			while(isPlaying){
				channel->isPlaying(&isPlaying);
				//<unistd.h>
				//单位微秒，不断的睡眠保证声音播放完成之后再释放资源
				usleep(1000*1000);
			}
			LOGI("%s","播放完成");
			system->update();
	} catch(...){
		LOGE("%s","发生异常");
		goto end;
	}
	goto end;

	end:
	env->ReleaseStringUTFChars(path_jstr,media_path);
	result = sound->release();
	system->close();
	system->release();
}
