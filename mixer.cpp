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

//void /*WINAPI*/ CMixer::SetMute(bool vol)//�����豸����
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
//    {//��ȡ¼����˷��豸
//        mxl.dwComponentType   =   MIXERLINE_COMPONENTTYPE_DST_WAVEIN;
//        //   �õ�¼�������е�������
//        mixerGetLineInfo(   (HMIXEROBJ)hmixer,   &mxl,
//                            MIXER_OBJECTF_HMIXER   |   MIXER_GETLINEINFOF_COMPONENTTYPE   );
//        //   ������������
//        DWORD   dwConnections   =   mxl.cConnections;
//        //   ׼����ȡ��˷��豸��ID
//        DWORD   dwLineID   =   0;
//        for   (   DWORD   i   =   0;   i   <   dwConnections;   i++   )
//        {
//            //   ö��ÿһ���豸����Source��ID���ڵ�ǰ�ĵ�������
//            mxl.dwSource   =   i;
//            //   ����SourceID������ӵ���Ϣ
//            MMRESULT mr   =   mixerGetLineInfo(   (HMIXEROBJ)hmixer,   &mxl,
//                                                  MIXER_OBJECTF_HMIXER   |   MIXER_GETLINEINFOF_SOURCE   );
//            //   �жϺ���ִ�д���
//            if   (   mr   !=   0   )
//            {
//                break;
//            }
//            //   �����ǰ�豸��������˷磬������ѭ����
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
