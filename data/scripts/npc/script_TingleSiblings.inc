@ Tingle Siblings
SCRIPT_START script_TingleSiblings
	BeginBlock
	Call sub_08064EA4
	SetAnimationState 0x0004
	DoPostScriptAction 0x0000
	DoPostScriptAction 0x000a
	EndBlock
script_0801690A:
	FacePlayerAndCheckDist
	JumpIfNot script_0801690A
	SetPlayerIdle
	FacePlayer
	Call sub_08064F28
	WaitUntilTextboxCloses
	JumpIfNot script_08016926
	GivePlayerItem 0x003d
	WaitPlayerGetItem
script_08016926:
	EnablePlayerControl
	SetGlobalFlag 0x005c
	Jump script_0801690A
	BeginBlock
	_0807E9D4
	SetAnimationState 0x0000
	DoPostScriptAction 0x000a
	EndBlock
script_0801693E:
	TriggerInteract
	SetPlayerIdle
	Wait 0x0018
	MessageFromTarget 0x0a01
	WaitUntilTextboxCloses
	Wait 0x000f
	EnablePlayerControl
	Jump script_0801693E
	.2byte 0x0000
	BeginBlock
	_0807E9D4
	SetAnimationState 0x0000
	DoPostScriptAction 0x000a
	SetAnimation 0x0000
	EndBlock
script_0801696A:
	TriggerInteract
	SetPlayerIdle
	Wait 0x0018
	MessageFromTarget 0x0a01
	WaitUntilTextboxCloses
	Wait 0x000f
	EnablePlayerControl
	Jump script_0801696A
	.2byte 0x0000