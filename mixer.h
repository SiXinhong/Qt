// Mixer.h: interface for the CMixer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIXER_H__7369BAA5_012E_467E_AD1E_A383E4474C58__INCLUDED_)
#define AFX_MIXER_H__7369BAA5_012E_467E_AD1E_A383E4474C58__INCLUDED_
#define WIN32_LEAN_AND_MEAN

#include "windows.h"
#include <mmsystem.h>
#if _MSC_VER > 1000
#pragma once
#endif

class CMixer
{
public:
CMixer();
virtual ~CMixer();

void SetMute(bool vol);     //设置设备静音

private:
void SetMuteValue(HMIXER hmixer ,MIXERCONTROL *mxc, bool mute);
bool GetVolumeControl(HMIXER hmixer ,long componentType,long ctrlType,MIXERCONTROL* mxc);
};

#endif
