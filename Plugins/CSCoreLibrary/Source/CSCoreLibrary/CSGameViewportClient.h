// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "CSGameViewportClient.generated.h"

/**
 * 
 */
UCLASS()
class CSCORELIBRARY_API UCSGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()

public:
	/**
	 * Called after rendering the player views and HUDs to render menus, the console, etc.
	 * This is the last rendering call in the render loop
	 *
	 * @param Canvas        The canvas to use for rendering.
	 */
	virtual void PostRender(UCanvas* Canvas) override;

	/** Used for Fade to and from black */
	UFUNCTION(BlueprintCallable)
	virtual void Fade(const float Duration, const bool InbToBlack);
	
	/** Does the actual screen fading */
	void DrawScreenFade(UCanvas* Canvas);

private:
	// Values used by our screen fading
	
	bool bFading;
	bool bToBlack; // Fading to black will be applied even if alpha is 1
	float FadeAlpha;
	float FadeStartTime;
	float FadeDuration;
};
