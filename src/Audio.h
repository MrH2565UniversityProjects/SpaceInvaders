#pragma once
#include <iostream>
using namespace std;
void PlayEffectSound(const string& filePath);
void PlaySoundFile(const string& alias, const string& filePath, bool loop = false);
void StopSoundFile(const string& alias) ;
int GetSoundFileDuration(const string& alias);
void PlayBackgroundMusic();
void StopBackgroundMusic();
void PlayNavigateSound();
void PlayShotSound();
void PlayCollisionSound();
void PlayChangeSound();
void PlayAlertSound();
void PlayGameMusic();
void StopGameMusic();