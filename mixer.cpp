// Mixer.cpp: implementation of the CMixer class.
//
//#include "stdwx.h"
#include "Mixer.h"

//CMixer::CMixer()
//{
//}

//CMixer::~CMixer()
//{

//}

//void CMixer::SetMuteValue(HMIXER hmixer ,MIXERCONTROL *mxc, bool mute)
//{
//    MIXERCONTROLDETAILS mxcd;
//    MIXERCONTROLDETAILS_BOOLEAN mxcdMute;
//    mxcdMute.fValue=mute;
//    mxcd.hwndOwner = 0;
//    mxcd.dwControlID = mxc->dwControlID;
//    mxcd.cbStruct = sizeof(mxcd);
//    mxcd.cbDetails = sizeof(mxcdMute);
//    mxcd.paDetails = &mxcdMute;
//    mxcd.cChannels = 1;
//    mxcd.cMultipleItems = 0;
////    mixerSetControlDetails((HMIXEROBJ)hmixer, &mxcd, MIXER_OBJECTF_HMIXER|MIXER_SETCONTROLDETAILSF_VALUE);
//}

//void /*WINAPI*/ CMixer::SetMute(bool vol)//设置设备静音
//{
//    MIXERCONTROL volCtrl;
//    HMIXER hmixer;
//    UINT uNum = mixerGetNumDevs();
//    for ( int id = 0; id < uNum; id++ )
//    {
//        mixerOpen(&hmixer,id,0,0,MIXER_OBJECTF_MIXER);
//        for(int i=0;i<10;i++){
//            if(GetVolumeControl(hmixer,i,MIXERCONTROL_CONTROLTYPE_MUTE,&volCtrl))
//                SetMuteValue(hmixer,&volCtrl,(bool)vol);
//        }
//        mixerClose(hmixer);
//    }
//}
//bool CMixer::GetVolumeControl(HMIXER hmixer ,long componentType,long ctrlType,MIXERCONTROL* mxc)
//{
//    MIXERLINECONTROLS mxlc;
//    MIXERLINE mxl;
//    bool exist = false;
//    mxl.cbStruct = sizeof(mxl);
//    mxl.dwComponentType = componentType;

//    if (componentType == MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE)
//    {//获取录音麦克风设备
//        mxl.dwComponentType   =   MIXERLINE_COMPONENTTYPE_DST_WAVEIN;
//        //   得到录制总线中的连接数
//        mixerGetLineInfo(   (HMIXEROBJ)hmixer,   &mxl,
//                            MIXER_OBJECTF_HMIXER   |   MIXER_GETLINEINFOF_COMPONENTTYPE   );
//        //   将连接数保存
//        DWORD   dwConnections   =   mxl.cConnections;
//        //   准备获取麦克风设备的ID
//        DWORD   dwLineID   =   0;
//        for   (   DWORD   i   =   0;   i   <   dwConnections;   i++   )
//        {
//            //   枚举每一个设备，当Source的ID等于当前的迭代记数
//            mxl.dwSource   =   i;
//            //   根据SourceID获得连接的信息
//            MMRESULT mr   =   mixerGetLineInfo(   (HMIXEROBJ)hmixer,   &mxl,
//                                                  MIXER_OBJECTF_HMIXER   |   MIXER_GETLINEINFOF_SOURCE   );
//            //   判断函数执行错误
//            if   (   mr   !=   0   )
//            {
//                break;
//            }
//            //   如果当前设备类型是麦克风，则跳出循环。
//            if   (   mxl.dwComponentType   ==
//                     MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE   )
//            {
//                exist = true;
//                break;
//            }
//        }
//    }else if(!mixerGetLineInfo((HMIXEROBJ)hmixer, &mxl, MIXER_GETLINEINFOF_COMPONENTTYPE))
//    {
//        exist = true;
//    }

//    if (exist)
//    {
//        mxlc.cbStruct = sizeof(mxlc);
//        mxlc.dwLineID = mxl.dwLineID;
//        mxlc.dwControlType = ctrlType;
//        mxlc.cControls = 1;
//        mxlc.cbmxctrl = sizeof(MIXERCONTROL);
//        mxlc.pamxctrl = mxc;
//        if(mixerGetLineControls((HMIXEROBJ)hmixer,&mxlc,MIXER_GETLINECONTROLSF_ONEBYTYPE))
//            return 0;
//        else
//            return 1;
//    }
//    return 0;
//}
