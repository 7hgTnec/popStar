// WavePlayer.h: interface for the CWavePlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAVEPLAYER_H__2FF228B3_3A43_4F39_82C2_F977D5643B8E__INCLUDED_)
#define AFX_WAVEPLAYER_H__2FF228B3_3A43_4F39_82C2_F977D5643B8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*****************************************************************************
*                                                                            *
*							  作者:夏永烽                                    *
*							  QQ:1206908474                                  *
*							  邮箱:1206908474@qq.com                         *
*						      日期:2014年3月20日                             *
*                                                                            *
*****************************************************************************/

#include <MMSystem.h>
#include "Digitalv.h"
#pragma comment(lib, "winmm.lib")


class CWavePlayer  
{
public:
	CWavePlayer();
	virtual ~CWavePlayer();
public:
	/*成员变量*/
	CString m_strFilePath;		//当前文件的路径
	int m_nFileLength;			//当前文件的长度
	int m_nVolume;				//当前音量
	bool m_bIsPlaying;			//是否正在播放
	MCIDEVICEID m_nElementID;	//当前播放设备ID，为0时，代表没有播放
	bool m_bPause;				//已暂停
	bool m_bSetPosPause;		//因设置播放位置而暂停

public:
	/*成员函数*/
	int GetFileLength();						//获得当前文件的长度
	void Pause();								//暂停
	void SetPos(int nPos,bool bPlayNow=true);	//设置播放位置，bPlayNow表示是否立即播放
	void Stop();								//停止播放
	void Play();								//播放
	void Resume();								//暂停后恢复播放
	int GetCurrentVolume();						//获得当前音量
	void SetVolume(int nVolume);				//设置音量
	int GetCurrentPos();						//获得当前播放位置
};

#endif // !defined(AFX_WAVEPLAYER_H__2FF228B3_3A43_4F39_82C2_F977D5643B8E__INCLUDED_)
