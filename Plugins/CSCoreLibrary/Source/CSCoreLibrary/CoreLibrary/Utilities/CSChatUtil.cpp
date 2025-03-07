#include "CSChatUtil.h"

bool CSChatUtil::IsWhisper(const FString& Message)
{
	const FString Lowered = Message.ToLower();
	const bool bStartsWithWhisperCommand = Lowered.StartsWith(WHISPER_COMMAND_TEMPLATE) ||
		Lowered.StartsWith(WHISPER_COMMAND_TEMPLATE_SHORTCUT);
	return bStartsWithWhisperCommand;
}

void CSChatUtil::ParseWhisperCommand(const FString& Text, const FString& Delim, TArray<FString>& Out)
{
	if (Text.IsEmpty() || Delim.IsEmpty())
	{
		return;
	}
	if (IsWhisper(Text))
	{
		Text.ParseIntoArray(Out, *Delim);
	}
}

void CSChatUtil::ExtractWhisperName(TArray<FString>& ExtractedCommands, FString& Out)
{
	if (ExtractedCommands.Num() < 2)
	{
		return;
	}
	Out = ExtractedCommands[1];
}

void CSChatUtil::ExtractWhisperMessage(TArray<FString>& ExtractedCommands, FString& Out)
{
	if (ExtractedCommands.Num() < 3)
	{
		return;
	}
	FString Appendable = "";
	int32 Size = ExtractedCommands.Num();
	for (int i = 2; i < Size; i++)
	{
		Appendable.Append(ExtractedCommands[i]).Append(" ");
	}
	// 문자열 맨 마지막 필요없는 공백 삭제
	Appendable.RemoveAt(Appendable.Len() - 1);
	Out = Appendable;
}

FString CSChatUtil::GenerateTempUsername()
{
	FString TempUsername = FText::FromString(TEXT("nickname")).ToString();
	TempUsername.AppendInt(FMath::RandRange(0, 10000));
	return TempUsername;
}
