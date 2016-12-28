#pragma once

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

struct wavFileHeader {
	char ChunkID[4];
	SLint32 ChunkSize;
	char Format[4];
	char Subchunk1ID[4];
	SLint32 Subchunk1Size;
	SLint16 AudioFormat;
	SLint16 NumChannels;
	SLint32 SampleRate;
	SLint32 ByteRate;
	SLint16 BlockAlign;
	SLint16 BitsPerSample;
	char Subchunk2ID[4];
	SLint32 Subchunk2Size;
};