@ Lon Lon Ranch Talon you have the key
SCRIPT_START script_TalonGotKey
	BeginBlock
	SetEntitySpeed 0x00c0
	SetAction 0x0001
	DoPostScriptAction 0x000b
	SetPlayerIdle
	Call sub_0807FBC4
	EndBlock
	Wait 0x000a
	DoPostScriptAction 0x0004
	SetSyncFlag 0x00000008
	StartPlayerScript script_PlayerGiveKey
	_0807EDD4 0x0140, 0x0298
	FacePlayer
	WaitForSyncFlagAndClear 0x00000004
	FacePlayer
	Wait 0x003c
	PlaySound SFX_TASK_COMPLETE
	_0807F088 0x0037
	WaitPlayerGetItem 
	FaceAwayFromPlayer 
	MessageFromTarget 0x200c
	WaitUntilTextboxCloses
	Wait 0x0014
	_0807EDD4 0x0158, 0x0290
	Wait 0x000a
	_0807EDD4 0x0158, 0x0288
	Wait 0x0014
	SetSyncFlag 0x00000010
	_0807EDD4 0x0158, 0x0280
	Wait 0x000a
	DoPostScriptAction 0x0008
	SetSyncFlag 0x00000010
	SetSyncFlag 0x00000008
	DoPostScriptAction 0x0006
SCRIPT_END