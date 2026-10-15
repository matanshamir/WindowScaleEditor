
#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "WindowScaleEditorSettings.generated.h"

UCLASS(Config = EditorPerProjectUserSettings, defaultconfig,
    meta = (DisplayName = "Window Scale Editor"))
    class WINDOWSCALEEDITOR_API UWindowScaleEditorSettings : public UDeveloperSettings
{
    GENERATED_BODY()

public:
    UWindowScaleEditorSettings();

    UPROPERTY(Config, EditAnywhere, Category = "Window Scaling",
        meta = (ClampMin = "0.5", ClampMax = "1.5",
            UIMin = "0.5", UIMax = "1.5",
            Delta = "0.01",
            DisplayName = "Main Window UI Scale"))
    float MainWindowScale = 1.0f;

#if WITH_EDITOR
    virtual void PostEditChangeProperty(
        FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
