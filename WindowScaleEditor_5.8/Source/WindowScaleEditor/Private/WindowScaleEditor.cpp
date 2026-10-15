
#include "WindowScaleEditor.h"
#include "WindowScaleEditorSettings.h"

#include "Modules/ModuleManager.h"
#include "Interfaces/IMainFrameModule.h"
#include "Widgets/SWindow.h"
#include "ToolMenus.h"

#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SSpinBox.h"
#include "Widgets/Input/SSlider.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/Application/SlateApplication.h"

#define LOCTEXT_NAMESPACE "FWindowScaleEditorModule"

void FWindowScaleEditorModule::StartupModule()
{
    // Register the menu after ToolMenus is ready.
    UToolMenus::RegisterStartupCallback(
        FSimpleMulticastDelegate::FDelegate::CreateLambda([]()
            {
                UToolMenu* MainMenu =
                    UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu");

                FToolMenuSection& Section =
                    MainMenu->FindOrAddSection("WindowScaleSection");

                Section.AddSubMenu(
                    "WindowScaleMenu",
                    LOCTEXT("WindowScaleLabel", "Window Scale"),
                    LOCTEXT("WindowScaleTooltip", "Main editor window scaling"),
                    FNewToolMenuDelegate::CreateLambda([](UToolMenu* SubMenu)
                        {
                            FToolMenuSection& SubSection =
                                SubMenu->AddSection("WindowScaleOptions");

                            SubSection.AddEntry(
                                FToolMenuEntry::InitWidget(
                                    "WindowScaleSlider",
                                    SNew(SBox)
                                    .WidthOverride(250.0f)
                                    .Padding(10.0f)
                                    [
                                        SNew(SVerticalBox)

                                            // 1. Title and current scale value
                                            + SVerticalBox::Slot()
                                            .AutoHeight()
                                            .Padding(0.0f, 0.0f, 0.0f, 8.0f)
                                            [
                                                SNew(STextBlock)
                                                    .Text_Lambda([]()
                                                        {
                                                            const float Scale =
                                                                GetDefault<UWindowScaleEditorSettings>()->MainWindowScale;

                                                            return FText::Format(
                                                                LOCTEXT("ScaleSliderValue", "Main Window UI Scale: {0}"),
                                                                FText::AsNumber(Scale)
                                                            );
                                                        })
                                            ]

  

                                        // 2. Numeric input
                                        + SVerticalBox::Slot()
                                            .AutoHeight()
                                            .Padding(0.0f, 8.0f, 0.0f, 0.0f)
                                            [
                                                SNew(SSpinBox<float>)
                                                    .MinValue(0.5f)
                                                    .MaxValue(1.5f)
                                                    .MinSliderValue(0.5f)
                                                    .MaxSliderValue(1.5f)
                                                    .Delta(0.01f)
                                                    .Value_Lambda([]()
                                                        {
                                                            return GetDefault<UWindowScaleEditorSettings>()->MainWindowScale;
                                                        })

                                                    .OnValueChanged_Lambda([](float NewValue)
                                                        {
                                                            UWindowScaleEditorSettings* Settings =
                                                                GetMutableDefault<UWindowScaleEditorSettings>();

                                                            // Update the number without resizing the editor.
                                                            Settings->MainWindowScale =
                                                                FMath::Clamp(NewValue, 0.5f, 1.5f);
                                                        })

                                                    .OnValueCommitted_Lambda([](float NewValue, ETextCommit::Type CommitType)
                                                        {
                                                            UWindowScaleEditorSettings* Settings =
                                                                GetMutableDefault<UWindowScaleEditorSettings>();

                                                            Settings->MainWindowScale =
                                                                FMath::Clamp(NewValue, 0.5f, 1.5f);

                                                            if (FModuleManager::Get().IsModuleLoaded("MainFrame"))
                                                            {
                                                                IMainFrameModule& MainFrame =
                                                                    FModuleManager::GetModuleChecked<IMainFrameModule>("MainFrame");

                                                                TSharedPtr<SWindow> MainWindow =
                                                                    MainFrame.GetParentWindow();

                                                                if (MainWindow.IsValid())
                                                                {
                                                                    MainWindow->SetDPIScaleFactor(
                                                                        Settings->MainWindowScale);
                                                                }
                                                            }

                                                            Settings->SaveConfig();
                                                        })
                                            ]

                                        // 3. Reset button
                                        + SVerticalBox::Slot()
                                            .AutoHeight()
                                            .Padding(0.0f, 8.0f, 0.0f, 0.0f)
                                            [
                                                SNew(SButton)
                                                    .Text(LOCTEXT("ResetScale", "Reset to Default (1.0)"))
                                                    .HAlign(HAlign_Center)
                                                    .OnClicked_Lambda([]() -> FReply
                                                        {
                                                            UWindowScaleEditorSettings* Settings =
                                                                GetMutableDefault<UWindowScaleEditorSettings>();

                                                            Settings->MainWindowScale = 1.0f;

                                                            if (FModuleManager::Get().IsModuleLoaded("MainFrame"))
                                                            {
                                                                IMainFrameModule& MainFrame =
                                                                    FModuleManager::GetModuleChecked<IMainFrameModule>("MainFrame");

                                                                TSharedPtr<SWindow> MainWindow =
                                                                    MainFrame.GetParentWindow();

                                                                if (MainWindow.IsValid())
                                                                {
                                                                    MainWindow->SetDPIScaleFactor(1.0f);
                                                                }
                                                            }

                                                            Settings->SaveConfig();

                                                            return FReply::Handled();
                                                        })
                                            ]
                                    ],
                                    LOCTEXT("WindowScaleWidgetLabel", "Window Scale")
                                )
                            );
                        })
                );
            })
    );

    // Apply the saved scale when the main editor window is created.
    IMainFrameModule& MainFrame =
        FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");

    MainFrame.OnMainFrameCreationFinished().AddLambda(
        [](TSharedPtr<SWindow> MainWindow, bool bIsNewProjectWindow)
        {
            if (MainWindow.IsValid())
            {
                const UWindowScaleEditorSettings* Settings =
                    GetDefault<UWindowScaleEditorSettings>();

                MainWindow->SetDPIScaleFactor(
                    Settings->MainWindowScale);
            }
        });
}

void FWindowScaleEditorModule::ShutdownModule()
{
    if (UToolMenus::IsToolMenuUIEnabled())
    {
        UToolMenus::UnRegisterStartupCallback(this);
    }
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FWindowScaleEditorModule, WindowScaleEditor)
