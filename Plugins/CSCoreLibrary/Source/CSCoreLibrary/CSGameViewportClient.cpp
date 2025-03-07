// Fill out your copyright notice in the Description page of Project Settings.


#include "CSGameViewportClient.h"
#include "Engine/Canvas.h"

void UCSGameViewportClient::PostRender(UCanvas* Canvas)
{
	Super::PostRender(Canvas);

	DrawScreenFade(Canvas);
}

void UCSGameViewportClient::Fade(const float Duration, const bool InbToBlack)
{
	if (World)
	{
		bFading = true;
		bToBlack = InbToBlack;
		FadeDuration = Duration;
		FadeStartTime = World->GetTimeSeconds();
	}
}

void UCSGameViewportClient::DrawScreenFade(UCanvas* Canvas)
{
	if (bFading)
	{
		if (World)
		{
			const float Time = World->GetTimeSeconds();
			const float Alpha = FMath::Clamp((Time - FadeStartTime) / FadeDuration, 0.f, 1.f);

			// Make sure that we stay black in a fade to black
			if (Alpha == 1.f && !bToBlack)
			{
				bFading = false;
			}
			else
			{
				FColor OldColor = Canvas->DrawColor;
				FLinearColor FadeColor = FLinearColor::Black;
				FadeColor.A = bToBlack ? Alpha : 1 - Alpha;
				Canvas->DrawColor = FadeColor.ToFColor(true); // TheJamsh: "4.10 cannot convert directly to FColor, so need to use FLinearColor::ToFColor() :)
				Canvas->DrawTile(Canvas->DefaultTexture, 0, 0, Canvas->ClipX, Canvas->ClipY, 0, 0, Canvas->DefaultTexture->GetSizeX(), Canvas->DefaultTexture->GetSizeY());
				Canvas->DrawColor = OldColor;
			}
		}
	}
}
