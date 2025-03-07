#pragma once
#define WHISPER_COMMAND_TEMPLATE_SHORTCUT "/w"
#define WHISPER_COMMAND_TEMPLATE "/whisper"

/**
 * @author 남대영
 */
class CSCORELIBRARY_API CSChatUtil
{
public:
	/**
	 * @param Message 전송할 메시지
	 *
	 * 채팅 메시지를 전송할 때 커맨드인지 구분합니다.
	 */
	static bool IsWhisper(const FString& Message);

	/**
	 * @param Text 메시지 전체 텍스트입니다. e.g) /w username Hello World!
	 * @param Delim 커맨드를 구분할 델리미터입니다.
	 * @param Out 결과를 내보낼 Array입니다.
	 *
	 * 채팅 메시지를 파싱합니다.
	 */
	static void ParseWhisperCommand(const FString& Text, const FString& Delim, TArray<FString>& Out);

	/**
	 * @param ExtractedCommands 파싱된 커맨드
	 * @param Out 결과값
	 *
	 * 파싱된 커맨드에서 귓속말 대상을 반환합니다.
	 */
	static void ExtractWhisperName(TArray<FString>& ExtractedCommands, FString& Out);

	/**
	 * @param ExtractedCommands 파싱된 커맨드
	 * @param Out 결과값
	 *
	 * 파싱된 커맨드에서 귓속말 메시지를 만들어서 반환합니다.
	 */
	static void ExtractWhisperMessage(TArray<FString>& ExtractedCommands, FString& Out);

	/**
	 * 랜덤한 유저 이름을 생성합니다.
	 */
	static FString GenerateTempUsername();

private:
	CSChatUtil() {}
};
