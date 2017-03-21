/*****************************************************************************
*                                                                            *
*							  作者:夏永烽                                    *
*							  QQ:1206908474                                  *
*							  邮箱:1206908474@qq.com                         *
*						      日期:2014年3月20日                             *
*                                                                            *
*****************************************************************************/

#include "stdafx.h"
#include "WavePlayer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWavePlayer::CWavePlayer()
{
	m_bIsPlaying=false;
	m_nElementID=0;
	m_nFileLength=0;
	m_strFilePath="";
	m_bSetPosPause=false;
	m_bPause=false;
	m_nVolume=0;
}

CWavePlayer::~CWavePlayer()
{

}

int CWavePlayer::GetCurrentVolume()
{
	MCI_STATUS_PARMS mciStatusParms;
	memset(&mciStatusParms,0,sizeof(MCI_STATUS_PARMS));
	mciStatusParms.dwItem = MCI_DGV_STATUS_VOLUME;
	mciSendCommand (m_nElementID, MCI_STATUS,MCI_STATUS_ITEM,(DWORD)(LPVOID) &mciStatusParms);
	return (int)mciStatusParms.dwReturn;
}

void CWavePlayer::SetVolume(int nVolume)
{
	if(nVolume>1000)
		nVolume=1000;
	if(nVolume<0)
		nVolume=0;
	MCI_DGV_SETAUDIO_PARMS mciDSP;  
    mciDSP.dwItem = MCI_DGV_SETAUDIO_VOLUME;  
    mciDSP.dwValue = nVolume;  
    DWORD dwReturn = mciSendCommand(m_nElementID, MCI_SETAUDIO, 
	MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)&mciDSP);  
	m_nVolume=nVolume;
}

int CWavePlayer::GetFileLength()
{
	if(0==m_nElementID)
		return 0;
	MCI_STATUS_PARMS mciStatusParms;
	memset(&mciStatusParms,0,sizeof(MCI_STATUS_PARMS));
	mciStatusParms.dwItem = MCI_STATUS_LENGTH;
	mciSendCommand (m_nElementID, MCI_STATUS,MCI_STATUS_ITEM,(DWORD)(LPVOID) &mciStatusParms);
	return (int)mciStatusParms.dwReturn/1000;
}

void CWavePlayer::Pause()
{
	if(m_bPause || !m_bIsPlaying)
		return;

	MCI_STATUS_PARMS mciStatusParms;
	memset(&mciStatusParms,0,sizeof(MCI_STATUS_PARMS));
	mciSendCommand (m_nElementID, MCI_PAUSE,MCI_STATUS_ITEM,(DWORD)(LPVOID) &mciStatusParms);
	m_bPause=true;
	m_bIsPlaying=false;

}


void CWavePlayer::Play()
{
	if(""==this->m_strFilePath)
		return;
	if(m_bIsPlaying || m_bPause || m_bSetPosPause)
	{
		//如果正在播放，则关闭设备，在重新打开设备并播放；
		this->Stop();

		//重新打开设备
		MCI_OPEN_PARMS mciOpen;
		memset(&mciOpen,0,sizeof(MCI_OPEN_PARMS));
		mciOpen.lpstrElementName=this->m_strFilePath;
		mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_ELEMENT,(DWORD)(LPVOID)&mciOpen);
		m_nElementID=mciOpen.wDeviceID;

		//播放文件
		MCI_PLAY_PARMS  mciPlay;
		mciPlay.dwCallback=NULL;
		mciSendCommand(m_nElementID,MCI_PLAY,MCI_NOTIFY,(DWORD)(LPVOID)&mciPlay);

	}
	else
	{
		
		MCI_OPEN_PARMS mciOpen;
		memset(&mciOpen,0,sizeof(MCI_OPEN_PARMS));
		mciOpen.lpstrElementName=this->m_strFilePath;
		mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_ELEMENT,(DWORD)(LPVOID)&mciOpen);
		m_nElementID=mciOpen.wDeviceID;


		MCI_PLAY_PARMS  mciPlay;
		mciPlay.dwCallback=NULL;
		mciSendCommand(m_nElementID,MCI_PLAY,MCI_NOTIFY,(DWORD)(LPVOID)&mciPlay);
	}
	m_bIsPlaying=true;
	m_bSetPosPause=false;
	m_bPause=false;

	//获得当前文件长度
	m_nFileLength=this->GetFileLength();
	//获得当前音量
	m_nVolume=this->GetCurrentVolume();
}

void CWavePlayer::Resume()
{
	if(m_bSetPosPause)
	{
		MCI_PLAY_PARMS mciPlayParms;
		mciPlayParms.dwCallback=NULL;
		mciSendCommand(m_nElementID,MCI_PLAY,MCI_NOTIFY,(DWORD)(LPVOID)&mciPlayParms);	
		goto SetFlag;
	}
	if(m_bPause)
	{
		MCI_GENERIC_PARMS mciResumeParms;
		memset(&mciResumeParms,0,sizeof(MCI_GENERIC_PARMS));
		mciResumeParms.dwCallback=NULL;
		mciSendCommand(m_nElementID,MCI_RESUME,0,(DWORD)(LPVOID)&mciResumeParms);
		
		goto SetFlag;
	}
	SetFlag:
	{
		m_bPause=false;
		m_bSetPosPause=false;
		m_bIsPlaying=true;
		return;
	}
}

void CWavePlayer::SetPos(int nPos,bool bPlayNow)
{
	MCI_SEEK_PARMS mciSeekParms;
	memset(&mciSeekParms,0,sizeof(MCI_SEEK_PARMS));
	mciSeekParms.dwCallback=NULL;
	mciSeekParms.dwTo=nPos*1000;
	mciSendCommand(m_nElementID,MCI_SEEK,MCI_TO | MCI_WAIT,(DWORD)(LPVOID)&mciSeekParms);
	m_bSetPosPause=true;
	if(bPlayNow)	
	{
		this->Resume();
		return;
	}
	
	m_bIsPlaying=false;
}

void CWavePlayer::Stop()
{
	if(!m_bIsPlaying)
		return;
	MCI_GENERIC_PARMS CloseParms;
	memset(&CloseParms,0,sizeof(MCI_GENERIC_PARMS));
	CloseParms.dwCallback=NULL;
	mciSendCommand(m_nElementID,MCI_CLOSE,MCI_NOTIFY,(DWORD)(LPVOID)&CloseParms);
	m_bIsPlaying=false;
	m_bPause=false;
	m_bSetPosPause=false;
}

int CWavePlayer::GetCurrentPos()
{
	MCI_STATUS_PARMS mciStatusParms;
	memset(&mciStatusParms,0,sizeof(MCI_STATUS_PARMS));
	mciStatusParms.dwItem = MCI_STATUS_POSITION;
	mciStatusParms.dwCallback=NULL;
	mciSendCommand (m_nElementID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM,(DWORD)(LPVOID) &mciStatusParms);
	return (int)mciStatusParms.dwReturn/1000;
}
