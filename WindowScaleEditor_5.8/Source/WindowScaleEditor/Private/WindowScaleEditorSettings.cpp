
#include "WindowScaleEditorSettings.h"

#include "Framework/Application/SlateApplication.h"
#include "Interfaces/IMainFrameModule.h"
#include "Modules/ModuleManager.h"
#include "Widgets/SWindow.h"

UWindowScaleEditorSettings::UWindowScaleEditorSettings()
{
    CategoryName = TEXT("Plugins");
    SectionName = TEXT("Window Scale Editor");
}

#if WITH_EDITOR
void UWindowScaleEditorSettings::PostEditChangeProperty(
    FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    if (FSlateApplication::IsInitialized() &&
        FModuleManager::Get().IsModuleLoaded("MainFrame"))
    {
        IMainFrameModule& MainFrame =
            FModuleManager::GetModuleChecked<IMainFrameModule>("MainFrame");

        TSharedPtr<SWindow> MainWindow = MainFrame.GetParentWindow();

        if (MainWindow.IsValid())
        {
            MainWindow->SetDPIScaleFactor(MainWindowScale);
        }
    }
}
#endif
