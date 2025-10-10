/// <reference path="puerts.d.ts" />
declare module "ue" {
    import {$Ref, $Nullable} from "puerts"

    import * as cpp from "cpp"

    import * as UE from "ue"

// __TYPE_DECL_START: 184D25724AFED0B5055CFA97CAEA11E0
    namespace Engine.EngineDamageTypes.DmgTypeBP_Environmental {
        class DmgTypeBP_Environmental_C extends UE.DamageType {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): DmgTypeBP_Environmental_C;
            static Load(InName: string): DmgTypeBP_Environmental_C;
        
            __tid_DmgTypeBP_Environmental_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 8857914A447B15D9E4D6258AD257E24F
    namespace Niagara.Enums.ENiagaraRandomnessMode {
        enum ENiagaraRandomnessMode { "Simulation Defaults", Determinisitic, "Non-Deterministic", ENiagaraRandomnessMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 7D85D3F9439182EB4345EDB746679AAC
    namespace ChaosVD.BP_CVD_SkySphere {
        class BP_CVD_SkySphere_C extends UE.Engine.EngineSky.BP_Sky_Sphere.BP_Sky_Sphere_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            ExecuteUbergraph_BP_CVD_SkySphere(EntryPoint: number) : void;
            Refresh() : void;
            Refresh_EditorOnly() : void;
            SetDirectionalLightSource(NewLightSource: $Nullable<UE.DirectionalLight>) : void;
            SetDirectionalLightSource_EditorOnly(NewLightSource: $Nullable<UE.DirectionalLight>) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_CVD_SkySphere_C;
            static Load(InName: string): BP_CVD_SkySphere_C;
        
            __tid_BP_CVD_SkySphere_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 4C22CF9948649CF6AC95E5A3FD4A32F8
    namespace Takes.UMG.DefaultRecordingOverlay {
        class DefaultRecordingOverlay_C extends UE.TakeRecorderOverlayWidget {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            CanvasPanel_0: UE.CanvasPanel;
            Circles: UE.Image;
            CountdownBorder: UE.Border;
            CountdownText: UE.TextBlock;
            Crosshair_H: UE.Image;
            Crosshair_V: UE.Image;
            MID_Countdown: UE.MaterialInstanceDynamic;
            ExecuteUbergraph_DefaultRecordingOverlay(EntryPoint: number) : void;
            GetCountdownText() : string;
            GetCountdownVisibility() : UE.ESlateVisibility;
            /*
             *Called by both the game and the editor.  Allows users to run initial setup for their widgets to better preview
             *the setup in the designer and since generally that same setup code is required at runtime, it's called there
             *as well.
             *
             ***WARNING**
             *This is intended purely for cosmetic updates using locally owned data, you can not safely access any game related
             *state, if you call something that doesn't expect to be run at editor time, you may crash the editor.
             *
             *In the event you save the asset with blueprint code that causes a crash on evaluation.  You can turn off
             *PreConstruct evaluation in the Widget Designer settings in the Editor Preferences.
             */
            PreConstruct(IsDesignTime: boolean) : void;
            /*
             *Ticks this widget.  Override in derived classes, but always call the parent implementation.
             *
             *@param  MyGeometry The space allotted for this widget
             *@param  InDeltaTime  Real time passed since last tick
             */
            Tick(MyGeometry: UE.Geometry, InDeltaTime: number) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): DefaultRecordingOverlay_C;
            static Load(InName: string): DefaultRecordingOverlay_C;
        
            __tid_DefaultRecordingOverlay_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 3A88DCEA49B6B94DD73CBBB8DC9BC350
    namespace Takes.Sequencer.DefaultTakeBurnIn {
        class DefaultTakeBurnIn_C extends UE.LevelSequenceBurnIn {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            Border_0: UE.Border;
            Border_3: UE.Border;
            BottomCenter: UE.TextBlock;
            BottomLeft: UE.TextBlock;
            BottomRight: UE.TextBlock;
            TopCenter: UE.TextBlock;
            TopLeft: UE.TextBlock;
            TopRight: UE.TextBlock;
            Watermark: UE.Image;
            ["Foreground Color"]: UE.LinearColor;
            ["Background Color"]: UE.LinearColor;
            Date: string;
            Options: UE.Engine.Sequencer.DefaultBurnInOptions.DefaultBurnInOptions_C;
            hh: string;
            mm: string;
            ss: string;
            ff: string;
            MasterFrame: string;
            ShotFrame: string;
            MasterName: string;
            ShotName: string;
            FocalLength: string;
            FocusDistance: string;
            Aperture: string;
            SensorWidth: string;
            SensorHeight: string;
            SensorAspectRatio: string;
            Translation: UE.Vector;
            Rotation: UE.Rotator;
            bCached: boolean;
            EngineVersion: string;
            SourceTimecode: string;
            Slate: string;
            TakeNumber: string;
            Time: string;
            CacheData() : void;
            /*
             *Called after the underlying slate widget is constructed.  Depending on how the slate object is used
             *this event may be called multiple times due to adding and removing from the hierarchy.
             *If you need a true called-once-when-created event, use OnInitialized.
             */
            Construct() : void;
            ExecuteUbergraph_DefaultTakeBurnIn(EntryPoint: number) : void;
            Get_BottomCenter_Text_0() : string;
            Get_BottomLeft_Text_0() : string;
            Get_BottomRight_Text_0() : string;
            Get_TopCenter_Text_0() : string;
            Get_TopLeft_Text_0() : string;
            Get_TopRight_Text_0() : string;
            /*
             *Get the settings class to use for this burn in
             */
            GetSettingsClass() : UE.Class;
            /*
             *Called when this burn in is receiving its settings
             */
            SetSettings(InSettings: $Nullable<UE.Object>) : void;
            /*
             *Ticks this widget.  Override in derived classes, but always call the parent implementation.
             *
             *@param  MyGeometry The space allotted for this widget
             *@param  InDeltaTime  Real time passed since last tick
             */
            Tick(MyGeometry: UE.Geometry, InDeltaTime: number) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): DefaultTakeBurnIn_C;
            static Load(InName: string): DefaultTakeBurnIn_C;
        
            __tid_DefaultTakeBurnIn_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: CFE80E3348A0A6787E23A79E8DFD77EB
    namespace AudioWidgets.SubmixEffects.SubmixEffectDelayPresetWidget {
        class SubmixEffectDelayPresetWidget_C extends UE.UserWidget {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            LargeKnobDelay: UE.AudioWidgets.AudioKnobLarge.AudioKnobLarge.AudioKnobLarge_C;
            LargeKnobDelayMax: UE.AudioWidgets.AudioKnobLarge.AudioKnobLarge.AudioKnobLarge_C;
            LargeKnobTimeInterp: UE.AudioWidgets.AudioKnobLarge.AudioKnobLarge.AudioKnobLarge_C;
            Preset: UE.SubmixEffectDelayPreset;
            BndEvt__LargeKnobDelay_K2Node_ComponentBoundEvent_0_OnControlValueChanged__DelegateSignature(NewValue: number) : void;
            BndEvt__LargeKnobDelayMax_K2Node_ComponentBoundEvent_1_OnControlValueChanged__DelegateSignature(NewValue: number) : void;
            BndEvt__LargeKnobTimeInterp_K2Node_ComponentBoundEvent_2_OnControlValueChanged__DelegateSignature(NewValue: number) : void;
            ExecuteUbergraph_SubmixEffectDelayPresetWidget(EntryPoint: number) : void;
            /*
             *Returns the class of Preset the widget supports
             */
            GetClass() : UE.Class;
            /**
             * @deprecated Unsupported super overloads.
             */
            GetClass() : Class;
            GetEditorName() : string;
            GetIconBrushName() : string;
            /*
             *Called when the preset widget is constructed
             */
            OnConstructed(Preset: $Nullable<UE.SoundEffectPreset>) : void;
            OnPresetUpdated(Selection: string) : void;
            /*
             *Called when the preset object is changed
             */
            OnPropertyChanged(Preset: $Nullable<UE.SoundEffectPreset>, PropertyName: string) : void;
            SetDelayLength(DelayLength: number) : void;
            SetDelayMaxLength(DelayLengthMax: number) : void;
            SetInterpTime(InterpTime: number) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): SubmixEffectDelayPresetWidget_C;
            static Load(InName: string): SubmixEffectDelayPresetWidget_C;
        
            __tid_SubmixEffectDelayPresetWidget_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 2D16AC744CF70657B912D8B3ABA891C8
    namespace AudioWidgets.AudioTextBox.AudioTextBox {
        class AudioTextBox_C extends UE.UserWidget {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            TextLayer01: UE.Image;
            UnitsText: UE.EditableText;
            ValueTextBox: UE.EditableText;
            UnitText: string;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): AudioTextBox_C;
            static Load(InName: string): AudioTextBox_C;
        
            __tid_AudioTextBox_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 23D9C69348557B3640888F82B45000A2
    namespace AudioWidgets.AudioKnobSmall.AudioKnobSmall {
        class AudioKnobSmall_C extends UE.UserWidget {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            Background: UE.Image;
            KnobLayer01: UE.Image;
            KnobLayer02: UE.Image;
            KnobSlider: UE.RadialSlider;
            LabelTextBox: UE.TextBlock;
            TextLayer01: UE.Image;
            UnitsText: UE.EditableText;
            ValueTextBox: UE.EditableText;
            Units: string;
            ToolTip: string;
            Label: string;
            MaxIntegralDigits: number;
            MaxFractionalDigits: number;
            DisplayMin: string;
            DisplayMax: string;
            ControlValueNormalized: number;
            ControlValueMin: number;
            ControlValueMax: number;
            OnControlValueChanged: $MulticastDelegate<(NewValue: number) => void>;
            ControlValue: number;
            BndEvt__KnobSlider_K2Node_ComponentBoundEvent_2_OnFloatValueChangedEvent__DelegateSignature(Value: number) : void;
            BndEvt__ValueTextBox_K2Node_ComponentBoundEvent_0_OnEditableTextCommittedEvent__DelegateSignature(Text: string, CommitMethod: UE.ETextCommit) : void;
            /*
             *Called after the underlying slate widget is constructed.  Depending on how the slate object is used
             *this event may be called multiple times due to adding and removing from the hierarchy.
             *If you need a true called-once-when-created event, use OnInitialized.
             */
            Construct() : void;
            ExecuteUbergraph_AudioKnobSmall(EntryPoint: number) : void;
            OnControlValueChanged__DelegateSignature(NewValue: number) : void;
            SetNewValue(NewValue: number, Normalized: boolean, UpdateText: boolean) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): AudioKnobSmall_C;
            static Load(InName: string): AudioKnobSmall_C;
        
            __tid_AudioKnobSmall_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: A2C5071A4AF428F3964DFABC0453E72E
    namespace AudioWidgets.AudioKnobLarge.AudioKnobLarge {
        class AudioKnobLarge_C extends UE.UserWidget {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            DisplayMaxTextBox: UE.TextBlock;
            DisplayMinTextBox: UE.TextBlock;
            LabelTextBox: UE.TextBlock;
            Layer00: UE.Image;
            Layer01: UE.Image;
            Layer02: UE.Image;
            Slider: UE.RadialSlider;
            UnitsText: UE.EditableText;
            ValueTextBox: UE.EditableText;
            Units: string;
            ToolTip: string;
            Label: string;
            MaxIntegralDigits: number;
            MaxFractionalDigits: number;
            DisplayMin: string;
            DisplayMax: string;
            ControlValueNormalized: number;
            ControlValueMin: number;
            ControlValueMax: number;
            OnControlValueChanged: $MulticastDelegate<(NewValue: number) => void>;
            ControlValue: number;
            BndEvt__Slider_K2Node_ComponentBoundEvent_2_OnFloatValueChangedEvent__DelegateSignature(Value: number) : void;
            BndEvt__ValueTextBox_K2Node_ComponentBoundEvent_0_OnEditableTextCommittedEvent__DelegateSignature(Text: string, CommitMethod: UE.ETextCommit) : void;
            /*
             *Called after the underlying slate widget is constructed.  Depending on how the slate object is used
             *this event may be called multiple times due to adding and removing from the hierarchy.
             *If you need a true called-once-when-created event, use OnInitialized.
             */
            Construct() : void;
            ExecuteUbergraph_AudioKnobLarge(EntryPoint: number) : void;
            OnControlValueChanged__DelegateSignature(NewValue: number) : void;
            SetNewValue(NewValue: number, Normalized: boolean, UpdateText: boolean) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): AudioKnobLarge_C;
            static Load(InName: string): AudioKnobLarge_C;
        
            __tid_AudioKnobLarge_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 319C2A4445A35F8F9D7C70842CA7EACE
    namespace AudioWidgets.AudioFader.AudioFader {
        class AudioFader_C extends UE.UserWidget {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            AudioTextBox: UE.AudioWidgets.AudioTextBox.AudioTextBox.AudioTextBox_C;
            Slider: UE.Slider;
            SliderShadow: UE.Image;
            ["Minimum Integral Digits"]: number;
            ["Maximum Integral Digits"]: number;
            ["Minimum Fractional Digits"]: number;
            ["Maximum Fractional Digits"]: number;
            OnValueChanged: $MulticastDelegate<(NewValue: number) => void>;
            LinToDbCurve: UE.CurveFloat;
            DbToLinCurve: UE.CurveFloat;
            BndEvt__Slider_K2Node_ComponentBoundEvent_0_OnFloatValueChangedEvent__DelegateSignature(Value: number) : void;
            /*
             *Called after the underlying slate widget is constructed.  Depending on how the slate object is used
             *this event may be called multiple times due to adding and removing from the hierarchy.
             *If you need a true called-once-when-created event, use OnInitialized.
             */
            Construct() : void;
            ExecuteUbergraph_AudioFader(EntryPoint: number) : void;
            GetDbValue(LinValue: number, DbValue: $Ref<number>) : void;
            GetLinValue(DbValue: number, LinValue: $Ref<number>) : void;
            OnTextCommitted(Text: string, CommitMethod: UE.ETextCommit) : void;
            OnValueChanged__DelegateSignature(NewValue: number) : void;
            SetTextValue(NewValue: number) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): AudioFader_C;
            static Load(InName: string): AudioFader_C;
        
            __tid_AudioFader_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 828F4765467D198207C0BEA8CC43FA31
    namespace AudioWidgets.AudioButtonToggle.AudioButtonToggle {
        class AudioButtonToggle_C extends UE.UserWidget {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            Button01: UE.Button;
            LeftBoxBottom: UE.Image;
            LeftBoxTop: UE.Image;
            LeftCurveBottom: UE.Image;
            LeftCurveTop: UE.Image;
            RightBoxBottom: UE.Image;
            RightBoxTop: UE.Image;
            RightCurveBottom: UE.Image;
            RightCurveTop: UE.Image;
            TextBorder: UE.Border;
            ValueText: UE.TextBlock;
            WidgetSwitchLeftBottom: UE.WidgetSwitcher;
            WidgetSwitchLeftTop: UE.WidgetSwitcher;
            WidgetSwitchRightCurveBottom: UE.WidgetSwitcher;
            WidgetSwitchRightCurveTop: UE.WidgetSwitcher;
            OnSelected: $MulticastDelegate<(Button: $Nullable<UE.AudioWidgets.AudioButtonToggle.AudioButtonToggle.AudioButtonToggle_C>) => void>;
            TextValue: string;
            TextColor: UE.SlateColor;
            TextColorSelected: UE.SlateColor;
            BackgroundColor: UE.LinearColor;
            BackgroundColorSelected: UE.LinearColor;
            OnDeselected: $MulticastDelegate<(Button: $Nullable<UE.AudioWidgets.AudioButtonToggle.AudioButtonToggle.AudioButtonToggle_C>) => void>;
            CurveTopLeft: boolean;
            CurveTopRight: boolean;
            CurveBottomLeft: boolean;
            CurveBottomRight: boolean;
            Selected: boolean;
            BndEvt__Button01_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature() : void;
            /*
             *Called after the underlying slate widget is constructed.  Depending on how the slate object is used
             *this event may be called multiple times due to adding and removing from the hierarchy.
             *If you need a true called-once-when-created event, use OnInitialized.
             */
            Construct() : void;
            ExecuteUbergraph_AudioButtonToggle(EntryPoint: number) : void;
            GetIsSelected(IsSelected: $Ref<boolean>) : void;
            OnDeselected__DelegateSignature(Button: $Nullable<UE.AudioWidgets.AudioButtonToggle.AudioButtonToggle.AudioButtonToggle_C>) : void;
            OnSelected__DelegateSignature(Button: $Nullable<UE.AudioWidgets.AudioButtonToggle.AudioButtonToggle.AudioButtonToggle_C>) : void;
            /*
             *Called by both the game and the editor.  Allows users to run initial setup for their widgets to better preview
             *the setup in the designer and since generally that same setup code is required at runtime, it's called there
             *as well.
             *
             ***WARNING**
             *This is intended purely for cosmetic updates using locally owned data, you can not safely access any game related
             *state, if you call something that doesn't expect to be run at editor time, you may crash the editor.
             *
             *In the event you save the asset with blueprint code that causes a crash on evaluation.  You can turn off
             *PreConstruct evaluation in the Widget Designer settings in the Editor Preferences.
             */
            PreConstruct(IsDesignTime: boolean) : void;
            RefreshCorners() : void;
            SetBackgroundColor(NewColor: UE.LinearColor) : void;
            SetDeselected() : void;
            SetSelected(ReportEvent: boolean) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): AudioButtonToggle_C;
            static Load(InName: string): AudioButtonToggle_C;
        
            __tid_AudioButtonToggle_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 9FA99C4A4BF83614E7D3D8A9719E0D5A
    namespace AudioWidgets.AudioButtonMatrix.AudioButtonMatrix {
        class AudioButtonMatrix_C extends UE.UserWidget {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            HorizontalButtonBox: UE.HorizontalBox;
            TitleText: UE.TextBlock;
            DisplayName: string;
            Tooltip: string;
            Values: TArray<string>;
            NumColumns: number;
            ExclusiveSelection: boolean;
            OnMultiSelectionChanged: $MulticastDelegate<(SelectedButtons: $Ref<TArray<UE.AudioWidgets.AudioButtonToggle.AudioButtonToggle.AudioButtonToggle_C>>) => void>;
            OnExclusiveSelectionChanged: $MulticastDelegate<(Selection: $Nullable<UE.AudioWidgets.AudioButtonToggle.AudioButtonToggle.AudioButtonToggle_C>) => void>;
            LastExclusive: UE.AudioWidgets.AudioButtonToggle.AudioButtonToggle.AudioButtonToggle_C;
            AddAudioButton(Text: string, ColumnIndex: number, ButtonEnabled: boolean, Button: $Ref<UE.AudioWidgets.AudioButtonToggle.AudioButtonToggle.AudioButtonToggle_C>) : void;
            /*
             *Called after the underlying slate widget is constructed.  Depending on how the slate object is used
             *this event may be called multiple times due to adding and removing from the hierarchy.
             *If you need a true called-once-when-created event, use OnInitialized.
             */
            Construct() : void;
            CreateStubButtons() : void;
            ExecuteUbergraph_AudioButtonMatrix(EntryPoint: number) : void;
            GetOrAddVerticalBox(ColumnIndex: number, MatrixColumn: $Ref<UE.AudioWidgets.AudioButtonMatrix.AudioButtonMatrixColumn.AudioButtonMatrixColumn_C>) : void;
            OnExclusiveSelectionChanged__DelegateSignature(Selection: $Nullable<UE.AudioWidgets.AudioButtonToggle.AudioButtonToggle.AudioButtonToggle_C>) : void;
            OnMultiSelectionChanged__DelegateSignature(SelectedButtons: $Ref<TArray<UE.AudioWidgets.AudioButtonToggle.AudioButtonToggle.AudioButtonToggle_C>>) : void;
            /*
             *Called by both the game and the editor.  Allows users to run initial setup for their widgets to better preview
             *the setup in the designer and since generally that same setup code is required at runtime, it's called there
             *as well.
             *
             ***WARNING**
             *This is intended purely for cosmetic updates using locally owned data, you can not safely access any game related
             *state, if you call something that doesn't expect to be run at editor time, you may crash the editor.
             *
             *In the event you save the asset with blueprint code that causes a crash on evaluation.  You can turn off
             *PreConstruct evaluation in the Widget Designer settings in the Editor Preferences.
             */
            PreConstruct(IsDesignTime: boolean) : void;
            SetButtonDeselected_EventPrivate(Button: $Nullable<UE.AudioWidgets.AudioButtonToggle.AudioButtonToggle.AudioButtonToggle_C>) : void;
            SetButtonSelected_EventPrivate(Button: $Nullable<UE.AudioWidgets.AudioButtonToggle.AudioButtonToggle.AudioButtonToggle_C>) : void;
            SetButtonSelectedPrivate(Button: $Nullable<UE.AudioWidgets.AudioButtonToggle.AudioButtonToggle.AudioButtonToggle_C>) : void;
            SetSelected(Row: number, Column: number) : void;
            SetSelectedByArrayIndex(Index: number) : void;
            SetSelectionChangedPrivate(NewSelection: $Nullable<UE.AudioWidgets.AudioButtonToggle.AudioButtonToggle.AudioButtonToggle_C>, ReportDeselected: boolean) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): AudioButtonMatrix_C;
            static Load(InName: string): AudioButtonMatrix_C;
        
            __tid_AudioButtonMatrix_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: AA9391F54A5665BD2DC8A6B335B40E97
    namespace AudioWidgets.AudioButtonMatrix.AudioButtonMatrixColumn {
        class AudioButtonMatrixColumn_C extends UE.UserWidget {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            ButtonVerticalBox: UE.VerticalBox;
            AddButton(AudioButtonToggle: $Nullable<UE.AudioWidgets.AudioButtonToggle.AudioButtonToggle.AudioButtonToggle_C>) : void;
            ClearButtons() : void;
            GetButtonAt(Index: number, Button: $Ref<UE.AudioWidgets.AudioButtonToggle.AudioButtonToggle.AudioButtonToggle_C>) : void;
            GetButtons(ChildButtons: $Ref<TArray<UE.AudioWidgets.AudioButtonToggle.AudioButtonToggle.AudioButtonToggle_C>>) : void;
            GetNumButtons(NumButtons: $Ref<number>) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): AudioButtonMatrixColumn_C;
            static Load(InName: string): AudioButtonMatrixColumn_C;
        
            __tid_AudioButtonMatrixColumn_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 94E6666941A4BFBB2F9A37A5029918C9
    namespace ChaosNiagara.ChaosDestructionListenerActor {
        class ChaosDestructionListenerActor_C extends UE.Actor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            ChaosDestructionListener: UE.ChaosDestructionListener;
            DefaultSceneRoot: UE.SceneComponent;
            BndEvt__ChaosDestructionListener_K2Node_ComponentBoundEvent_0_OnChaosCollisionEvents__DelegateSignature(CollisionEvents: TArray<UE.ChaosCollisionEventData>) : void;
            BndEvt__ChaosDestructionListener_K2Node_ComponentBoundEvent_1_OnChaosBreakingEvents__DelegateSignature(BreakingEvents: TArray<UE.ChaosBreakingEventData>) : void;
            BndEvt__ChaosDestructionListener_K2Node_ComponentBoundEvent_2_OnChaosTrailingEvents__DelegateSignature(TrailingEvents: TArray<UE.ChaosTrailingEventData>) : void;
            ExecuteUbergraph_ChaosDestructionListenerActor(EntryPoint: number) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ChaosDestructionListenerActor_C;
            static Load(InName: string): ChaosDestructionListenerActor_C;
        
            __tid_ChaosDestructionListenerActor_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 276B0C9246D8369B8C2DCB8593A5C57D
    namespace Niagara.Modules.Audio.EInitialAudioParamType {
        enum EInitialAudioParamType { Boolean, Integer, Float, EInitialAudioParamType_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: F5B1EE31479BC8636940828D98313DD5
    namespace Niagara.Functions.PivotPainter.PivotPainter16bitTextureAlphaDataTypes {
        enum PivotPainter16bitTextureAlphaDataTypes { "Number of Steps to Root", "Random 0-1", "Origin Extents (16-bit)", "Bounding Box Diameter", "Selection Order (Int as float)", "Normalized 0-1 Hierarchy Position", "Object X Width", "Object Y Depth", "Object Z Height", "Parent Index (Float - Up To 2048)", PivotPainter16bitTextureAlphaDataTypes_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 2F908B574662F43E59553DB963EFEBE8
    namespace Niagara.Functions.PivotPainter.PivotPainter8BitTextureAlphaDataTypes {
        enum PivotPainter8BitTextureAlphaDataTypes { "Normalized 0-1 Hierarchy Position", "Normalized 0-1 Value Per Element", "X Extent Divided by 2048 (2048 max)", "Y Extent Divided by 2048 (2048 max)", "Z Extent Divided by 2048 (2048 max)", PivotPainter8BitTextureAlphaDataTypes_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 809229A5405DD360F3B641BAADEB1C9F
    namespace Niagara.Functions.PivotPainter.PivotPainterTextureRGBDataTypes {
        enum PivotPainterTextureRGBDataTypes { "Pivot Position (16-bit)", "Origin Position (16-bit)", "Origin Extents (16-bit)", "X-Vector (8-bit)", "Y-Vector (8-bit)", "Z-Vector (8-bit)", PivotPainterTextureRGBDataTypes_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 86D60C8F4975B47718D755AADED0485A
    namespace Niagara.Enums.Wind.ENiagaraWindCollisionMode {
        enum ENiagaraWindCollisionMode { None, "From Collision Module", ENiagaraWindCollisionMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: D255570D4B0CE971EADAD1A462452F4F
    namespace Niagara.Enums.Wind.ENiagaraWindCombingMode {
        enum ENiagaraWindCombingMode { None, "Surface Distance", ENiagaraWindCombingMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 9EC06F03446C961A0A4C289E52E5AE75
    namespace Niagara.Enums.Wind.ENiagaraWindFrictionDistanceMode {
        enum ENiagaraWindFrictionDistanceMode { "Distance Limit", "Falloff Start / End", ENiagaraWindFrictionDistanceMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: BB44E8E04521F8B49034B78C1242DA1B
    namespace Niagara.Enums.Wind.ENiagaraWindFrictionMode {
        enum ENiagaraWindFrictionMode { None, "Surface Distance", ENiagaraWindFrictionMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: AB33653D4A1387A7047C2687A1387336
    namespace Niagara.Enums.Wind.ENiagaraWindGroundMaskMode {
        enum ENiagaraWindGroundMaskMode { "Direct Set", Landscape, ENiagaraWindGroundMaskMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 0FBB0CB34FE6BF317D997C9524195742
    namespace Niagara.Enums.Wind.ENiagaraWindOffsetMode {
        enum ENiagaraWindOffsetMode { None, "Direct Set", "Time Offset", ENiagaraWindOffsetMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 4EB20AD64DF976B93C25C1B79982133A
    namespace Niagara.Enums.Wind.ENiagaraWindTurbulenceContributionMode {
        enum ENiagaraWindTurbulenceContributionMode { "Direct Set", "Speed Range", "Speed Range Curve", ENiagaraWindTurbulenceContributionMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: D198B2DF47B93E70B33C61BC18470DF6
    namespace Niagara.Enums.Wind.ENiagaraWindTurbulenceFrequencyMode {
        enum ENiagaraWindTurbulenceFrequencyMode { Constant, Varying, ENiagaraWindTurbulenceFrequencyMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 0E8508634677C42F59DC32B083CFA7BD
    namespace Niagara.Enums.Wind.ENiagaraWindTurbulenceMode {
        enum ENiagaraWindTurbulenceMode { None, "Curl Noise", ENiagaraWindTurbulenceMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 71479B474CA61256C2017A93D1D32D59
    namespace Niagara.Enums.Utility.ENiagara_ImportanceColorMode {
        enum ENiagara_ImportanceColorMode { "RGB Luminance", "RGB Average", "RGB Max", "Individual RGBA Channel", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 9C6FBC45420E7A0D1056C3B3AAE2CB25
    namespace Niagara.Enums.Utility.ENiagara_ImportanceRejectionMode {
        enum ENiagara_ImportanceRejectionMode { "RGB Luminance", "RGB Average", "RGB Max", "R Channel", "G Channel", "B Channel", "A Channel", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 0DA9D9EF4FEEF71266AC5B9E73AD3642
    namespace Niagara.Enums.Utility.ENiagara_IntegerConversion {
        enum ENiagara_IntegerConversion { Truncate, Round, Ceil, Floor, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 18C02F2B46416CD2A93C008E38AA4E4C
    namespace Niagara.Enums.Utility.ENiagara_OrientVectorCount {
        enum ENiagara_OrientVectorCount { Facing, "Facing/Up", "Facing/Side", "Facing/Side/Up", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: E20607DE45B4BF047ACEB2ADD889886E
    namespace Niagara.Enums.Utility.ENiagara_PartitionMode {
        enum ENiagara_PartitionMode { Alternating, Sequential, "Elapsed Time", Distance, "Float Comparison", Random, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 843381994F67AF3BD9C976A00A7D0FCB
    namespace Niagara.Enums.Utility.ENiagara_SplinePointCount {
        enum ENiagara_SplinePointCount { ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 72C1A22B473A302D74FEF6A6AECF3043
    namespace Niagara.Enums.Utility.ENiagara_TimelineAuthority {
        enum ENiagara_TimelineAuthority { "Play is the Authority", "Rewind is the Authority", Pause, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: E1663A124593CA171FA64EB43A6162BB
    namespace Niagara.Enums.Utility.ENiagara_TImelineMode {
        enum ENiagara_TimelineMode { "Automatic Rewind", "Manual Rewind", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: C30DED5A49653763BC0FAD89EEB09DBF
    namespace Niagara.Enums.Utility.ENiagara_TimelineOutput {
        enum ENiagara_TimelineOutput { None, Float, Vector2D, Vector, "Linear Color", Integer, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 098FF2714C8751ED34CCF18DB5DCA388
    namespace Niagara.Enums.Utility.ENiagara_TimelineOutputMode {
        enum ENiagara_TimelineOutputMode { Array, Curve, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 34706BA14FE22171F266F5BCD1A37D2B
    namespace Niagara.Enums.Utility.ENiagara_UpdateMeshOrientationMode {
        enum ENiagara_UpdateMeshOrientationMode { "Rotation Rate", "Orient To Vector(s)", "Orient to Position", "Flight Orientation", "Rolling Orientation", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: DEE22CF74D0EB9AF43BF6394F70D63A5
    namespace Niagara.Enums.Utility.ENiagara_VelocityMode {
        enum ENiagara_VelocityMode { Linear, "From Point", "In Cone", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 785CB7E84DA96D94E1E063923F842D57
    namespace Niagara.Enums.Transforms.ENiagara_LWCConvertPosToVec {
        enum ENiagara_LWCConvertPosToVec { "Passthrough as a Non Large World Vector", "Convert to Absolute Large World Space", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 0B76169B449E853A2F02ED814DA88717
    namespace Niagara.Enums.Transforms.ENiagara_LWCConvertVecToPos {
        enum ENiagara_LWCConvertVecToPos { "Passthrough as Non Large World Position", "Interpret as a Large World Position Vector", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 180AD4744C929F7C54E5D589678A2AF6
    namespace Niagara.Enums.Transforms.ENiagara_MeshOrientationOptions {
        enum ENiagara_MeshOrientationOptions { None, Random, System, "Orient to Vector", "Orient to Matrix", "Orient to Quaternion", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 23B75B77440576217F085F97EDC5DC2D
    namespace Niagara.Enums.Transforms.ENiagara_OffsetMode {
        enum ENiagara_OffsetMode { Default, None, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: E2A4E55341D021C4EF15B0AD330DA0DE
    namespace Niagara.Enums.Transforms.ENiagara_RotationMode {
        enum ENiagara_RotationMode { Default, "Axis Angle", "Yaw / Pitch / Roll", Quaternion, Matrix, None, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: B42B3C9C4C73265F8A4E04BE47EF76A4
    namespace Niagara.Enums.Transforms.ENiagara_ScaleMode {
        enum ENiagara_ScaleMode { Default, None, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: DD95A1E64DA25126E85E87B581E0539C
    namespace Niagara.Enums.Transforms.ENiagara_TransformOrder {
        enum ENiagara_TransformOrder { "Scale / Rotate / Offset", "Scale / Offset / Rotate", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: F2AF64314ADF9FB32C9F83816582B21E
    namespace Niagara.Enums.Transforms.ENiagara_TransformType {
        enum ENiagara_TransformType { Default, "Custom Matrix", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 1B0E00314FC26F86B62855AF8716445D
    namespace Niagara.Enums.StaticMesh.ENiagara_MeshLocalBoundsCalcMethod {
        enum ENiagara_MeshLocalBoundsCalcMethod { "Minimum Bounds", "Maximum Bounds", Size, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 81258C854B086DC9F00775B86F230C51
    namespace Niagara.Enums.StaticMesh.ENiagara_StaticSamplingMode {
        enum ENiagara_StaticSamplingMode { Triangles, Sockets, Vertices, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 07E5993A4C29661A3C8F739C3A5E478A
    namespace Niagara.Enums.StaticMesh.ENiagara_StaticSocketMode {
        enum ENiagara_StaticSocketMode { "Random (All Sockets)", "Random (Filtered Sockets)", "Direct (All Sockets)", "Direct (Filtered Sockets)", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 2154C4C44C41F8B441A0B885EC53E57E
    namespace Niagara.Enums.StaticMesh.ENiagara_StaticTriangleMode {
        enum ENiagara_StaticTriangleMode { "Random (All Triangles)", "Random (Section Filter)", "Direct (All Triangles)", "Direct (Section Filter)", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: C3165ACA46E802CCD5B4F9BE367A8BE7
    namespace Niagara.Enums.StaticMesh.ENiagara_StaticVertexMode {
        enum ENiagara_StaticVertexMode { "Random Vertex", "Direct Vertex", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: EB160FC14ADA825A7C69D28F98CD45DD
    namespace Niagara.Enums.SpriteRenderer.ENiagara_AutomaticManual {
        enum ENiagara_AutomaticManual { "Automatic (From Renderer SubImage Size)", Manual, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: C56DD03A4A020847C185F99D1E07AE48
    namespace Niagara.Enums.SpriteRenderer.ENiagara_FPSPlayrate {
        enum ENiagara_FPSPlayrate { "Loops Per Second", "Frames Per Second", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 6A0D38CB4942C16492C8F88FEF61A700
    namespace Niagara.Enums.SpriteRenderer.ENiagara_ScaleSpriteSize {
        enum ENiagara_ScaleSpriteSize { Uniform, "Uniform Curve", "Non-Uniform", "Non-Uniform Curve", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: B8AFCBB94308548AB7359FB625593396
    namespace Niagara.Enums.Ribbons.ENiagara_UnsetDirectSet {
        enum ENiagara_UnsetDirectSet { Unset, "Direct Set", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 12F9B9194C39AD06FE8CCC8602076DEE
    namespace Niagara.Enums.Ribbons.ENiagara_UnsetDirectSetRandom {
        enum ENiagara_UnsetDirectSetRandom { Unset, "Direct Set", Random, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: F17252F045F8EE50921ADBB3C4A39706
    namespace Niagara.Enums.Recycle.ENiagaraRecycleAttributeMode {
        enum ENiagaraRecycleAttributeMode { "No Change", "Initial Value", Set, ENiagaraRecycleAttributeMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: EFD08724493320798887059191ECF31D
    namespace Niagara.Enums.Recycle.ENiagaraRecycleColorMode {
        enum ENiagaraRecycleColorMode { "No Change", "Initial Value", Set, "Random Range", "Random Hue/Saturation/Value", ENiagaraRecycleColorMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 180CF6A346F351F8BD3B658E8D779072
    namespace Niagara.Enums.Recycle.ENiagaraRecycleLifetimeMode {
        enum ENiagaraRecycleLifetimeMode { "No Change", "Initial Value", Set, Random, ENiagaraRecycleLifetimeMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 0323ACBE47FE21ACA4FC329FEB1720A6
    namespace Niagara.Enums.Recycle.ENiagaraRecycleMassMode {
        enum ENiagaraRecycleMassMode { "No Change", "Initial Value", Set, Random, ENiagaraRecycleMassMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 28ADAFB04E8E5F80284CD09334EFEFE7
    namespace Niagara.Enums.Recycle.ENiagaraRecycleRendererType {
        enum ENiagaraRecycleRendererType { "Set (Diameter)", Sprite, Mesh, ENiagaraRecycleRendererType_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 404D66294D073AA05BAE8D81FCD3D65F
    namespace Niagara.Enums.Recycle.ENiagaraRecycleSpriteRotationMode {
        enum ENiagaraRecycleSpriteRotationMode { "No Change", "Initial Value", Random, "Direct Angle (Degrees)", "Direct Normalized Angle (0-1)", ENiagaraRecycleSpriteRotationMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: AE4445EC413A45D7694D73B73C49C0DE
    namespace Niagara.Enums.Recycle.ENiagaraRecycleSpriteSizeMode {
        enum ENiagaraRecycleSpriteSizeMode { "No Change", "Initial Value", Uniform, "Random Uniform", "Non-Uniform", "Random Non-Uniform", ENiagaraRecycleSpriteSizeMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: A0CBC9294B787B7FB07DA0937333CEB7
    namespace Niagara.Enums.Masks.ENiagaraDebugDrawShape {
        enum ENiagaraDebugDrawShape { Sphere, Box, Plane, Slab, ENiagaraDebugDrawShape_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: D984CA7F45DDDA5F561ED088A0DA4C70
    namespace Niagara.Enums.Masks.ENiagaraRegionMaskValue {
        enum ENiagaraRegionMaskValue { Float, Vector2D, Vector, "Linear Color", ENiagaraRegionMaskValue_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 4464AD1640A4E3BDB21798AB578E7E98
    namespace Niagara.Enums.Location.ENiagaraRingDiscMode {
        enum ENiagaraRingDiscMode { Circle, Hexagon, ENiagaraRingDiscMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 899BCF0648CFD8C5A5B3038150BFA968
    namespace Niagara.Enums.Location.ENiagara_BoxPlaneMode {
        enum ENiagara_BoxPlaneMode { Box, Plane, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 78E6C4AE40AE5313F067E8BF80B05757
    namespace Niagara.Enums.Location.ENiagara_ConeMode {
        enum ENiagara_ConeMode { "Spherical Cone", "Spherical Wedge", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 09471E1F43723980DE6EE3AC58B0E067
    namespace Niagara.Enums.Location.ENiagara_CylinderMode {
        enum ENiagara_CylinderMode { Random, Direct, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 04F2F7384BB5FE3EBB3BBA9293AAEBE2
    namespace Niagara.Enums.Location.ENiagara_LocationShapes {
        enum ENiagara_LocationShapes { Sphere, Cylinder, "Box / Plane", Torus, "Ring / Disc", Cone, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 239553C2498C84D47134B6B2CCD44526
    namespace Niagara.Enums.Events.ENiagara_LocEventType {
        enum ENiagara_LocEventType { "Send Rate", "Send Per Unit Traveled", "Every Frame", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 3C9B79AC48DB9FB456163F9F57D14252
    namespace Niagara.Enums.DistanceFields.ENiagara_BoundsCalculationMethod {
        enum ENiagara_BoundsCalculationMethod { "Emitter Bounds with Padding", "Local Space Bounding Box", "World Space Bounding Box", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 4D71C0744281BDAA22E39A91728B1D66
    namespace Niagara.Enums.DistanceFields.ENiagara_GDFQueryExecutionRate {
        enum ENiagara_GDFQueryExecutionRate { "First Frame", "Every Frame", "On Demand", Never, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 41B3804D4FD2B9A5A32BCD8BBAC84F76
    namespace Niagara.Enums.DistanceFields.ENiagara_GlobalVsRigidBodyDistanceFields {
        enum ENiagara_GlobalVsRigidBodyDistanceFields { "Global Distance Field", "Global Distance field + High Quality Rigid Body SDF", "Static Distance Field Volume Texture", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 7283B335470344D1594AF4960B978CB7
    namespace Niagara.Enums.Comparison.CompareValues {
        enum CompareValues { "Return Largest", "Return Smallest", CompareValues_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 1982925641860EB2EDD01CA63CC55F5E
    namespace Niagara.Enums.Collision.SceneDepthCollisionQueryMethod {
        enum SceneDepthCollisionQueryMethod { "Scene Depth", "Custom Depth", "Partial Depth", SceneDepthCollisionQueryMethod_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: B6C9F5C245CB068D62D0199995E4B0CF
    namespace Niagara.Enums.CascadeConversion.ECascadeNiagaraOrbitChainMode {
        enum ECascadeNiagaraOrbitChainMode { Add, Scale, Link, NONE, ECascadeNiagaraOrbitChainMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 11F1905B4E2507A97BB6C4A573AA3B08
    namespace Niagara.Enums.CascadeConversion.ECascadeNiagaraTwoVectorChannels {
        enum ECascadeNiagaraTwoVectorChannels { XY, YZ, XZ, ECascadeNiagaraTwoVectorChannels_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 0A9FB2D64E103E38438DC49912AD1CCB
    namespace Niagara.Enums.Audio.PlayAudioMode {
        enum PlayAudioMode { "Direct Set", Random, "On Death", PlayAudioMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 594ED2A84ABD28DB11F013B114983AED
    namespace Niagara.Enums.Angles.ENiagara_AngleInput {
        enum ENiagara_AngleInput { Degrees, "Normalized Angle (0-1)", Radians, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 0BF5864F4BA65A357AE75DA36EC76E1A
    namespace Niagara.Enums.ENiagaraAerodynamicDragPivotMode {
        enum ENiagaraAerodynamicDragPivotMode { Random, Direct, ENiagaraAerodynamicDragPivotMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 4C48CAFF429644DDB6923F9FB807E274
    namespace Niagara.Enums.EniagaraAlternateRendererModes {
        enum EniagaraAlternateRendererModes { Sprite, Mesh, Ribbon, Light, EniagaraAlternateRendererModes_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 4F47781A46E8C8DD25B30F99AACFD65D
    namespace Niagara.Enums.ENiagaraAnimTrailWidthMode {
        enum ENiagaraAnimTrailWidthMode { Auto, Manual, ENiagaraAnimTrailWidthMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 7934153A41A0EAED77E3509C76B7C340
    namespace Niagara.Enums.ENiagaraArraySamplingMode {
        enum ENiagaraArraySamplingMode { Random, "Direct Set", Interpolate, ENiagaraArraySamplingMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 1F5858F3464BBAD5A403E5B77A797D05
    namespace Niagara.Enums.ENiagaraBoneSamplingMode {
        enum ENiagaraBoneSamplingMode { "Random (Filtered Bones)", "Random (Unfiltered Bones)", "Random (All Bones)", "Direct (Filtered Bones)", "Direct (Unfiltered Bones)", "Direct (All Bones)", ENiagaraBoneSamplingMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: DE3B4A944D41D639476C6FA4D8364FA7
    namespace Niagara.Enums.ENiagaraBoneSocketSamplingMode {
        enum ENiagaraBoneSocketSamplingMode { "Random (Filtered Bone or Sockets)", "Direct (Filtered Bone or Sockets)", ENiagaraBoneSocketSamplingMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: E1DEB41848F9412917D6EE8FC7FF9327
    namespace Niagara.Enums.ENiagaraBooleanLogicOps {
        enum ENiagaraBooleanLogicOps { "Greater Than", "Greater Than Or Equal To", "Equal To", "Not Equal To", ENiagaraBooleanLogicOps_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 64E2E2BE45F15F1DCC5322B6DD0FC8ED
    namespace Niagara.Enums.ENiagaraBooleanLogicOps_v2 {
        enum ENiagaraBooleanLogicOps_v2 { "A Greater Than B", "A Greater Than Or Equal To B", "A Equal To B", "A Not Equal To B", "A Less Than B", "A Less Than Or Equal To B", ENiagaraBooleanLogicOps_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 389F57CC41CF0A9429061BB42AA4E8B6
    namespace Niagara.Enums.ENiagaraCalculateRadiusOptions {
        enum ENiagaraCalculateRadiusOptions { Bounds, "Minimum Axis", "Maximum Axis", ENiagaraCalculateRadiusOptions_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 43B4B2524ADAC046C86F32B05BE1789F
    namespace Niagara.Enums.ENiagaraChannelCorrelation {
        enum ENiagaraChannelCorrelation { "Link RGBA", "Link RGB / Link A", "Random Individual Channels", ENiagaraChannelCorrelation_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 67FC7CE648BCDE6257447387066F5577
    namespace Niagara.Enums.ENiagaraCollisionRadiusOptions {
        enum ENiagaraCollisionRadiusOptions { Sprite, Mesh, Custom, ENiagaraCollisionRadiusOptions_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: F2D2222B48D483D09D5B8EB967336A32
    namespace Niagara.Enums.ENiagaraCoordinateSpace {
        enum ENiagaraCoordinateSpace { Simulation, World, Local, ENiagaraCoordinateSpace_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 8BE93E71405BF1F383FC03AA6EBD3BDD
    namespace Niagara.Enums.ENiagaraCurlNoiseQuality {
        enum ENiagaraCurlNoiseQuality { "Baked (Low)", "Baked (Medium)", "Baked (High)", "Evaluated (Ultra)", ENiagaraCurlNoiseQuality_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 5D13435F441DA4045FBBA985D98355F9
    namespace Niagara.Enums.ENiagaraDecalTransforms {
        enum ENiagaraDecalTransforms { Simulation, World, Local, Decal, ENiagaraDecalTransforms_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: B41B7DC041BDDABA4C991CB5C4DC0D9E
    namespace Niagara.Enums.ENiagaraDragCoefficientShapeMode {
        enum ENiagaraDragCoefficientShapeMode { Exponent, Curve, ENiagaraDragCoefficientShapeMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: BB83CC8843898D6B4CC407B33A11F302
    namespace Niagara.Enums.ENiagaraDragMethodMode {
        enum ENiagaraDragMethodMode { Linear, Aerodynamic, ENiagaraDragMethodMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: E6B7C742434AB938286D96BFE5A6418E
    namespace Niagara.Enums.ENiagaraEmitterLifeCycleMode {
        enum ENiagaraEmitterLifeCycleMode { System, Self, ENiagaraEmitterLifeCycleMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 3E73854C4D72BE2FA109E9A4E4D6AF76
    namespace Niagara.Enums.ENiagaraEmitterScalabilityMode {
        enum ENiagaraEmitterScalabilityMode { System, Self, None, ENiagaraEmitterScalabilityMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 0B36CBAC440A79A827DAA987951B5B12
    namespace Niagara.Enums.ENiagaraEmitterScalabilityMode_Limited {
        enum ENiagaraEmitterScalabilityMode_Limited { System, Self, ENiagaraEmitterScalabilityMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: A88DA06540170B98E8308980B284E056
    namespace Niagara.Enums.ENiagaraExecutionStateManagement {
        enum ENiagaraExecutionStateManagement { Awaken, "Sleep and Let Particles Finish", "Sleep and Clear Particles", "Kill Immediately", "Kill After Particles Finish", ENiagaraExecutionStateManagement_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 35A2BA3D4D25FBFB30F660921095755C
    namespace Niagara.Enums.ENiagaraExpansionMode {
        enum ENiagaraExpansionMode { Inside, Centered, Outside, ENiagaraExpansionMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 05BB123248109DC5ABFE93BD933D12BA
    namespace Niagara.Enums.ENiagaraFrictionMergeType {
        enum ENiagaraFrictionMergeType { Ignore, Average, Min, Max, ENiagaraFrictionMergeType_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 5083E4304ED8B05481BB07B66284A729
    namespace Niagara.Enums.ENiagaraGPUDepthResponseType {
        enum ENiagaraGPUDepthResponseType { Kill, Bounce, ENiagaraGPUDepthResponseType_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 9C8EE4834C3490F346C55CA05C67CBA9
    namespace Niagara.Enums.ENiagaraGridPlacementType {
        enum ENiagaraGridPlacementType { "Padding Per Cell ", "Bounding Box Size", ENiagaraGridPlacementType_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 833340CF450B2DE408173A82DAFF5D94
    namespace Niagara.Enums.ENiagaraInactiveMode {
        enum ENiagaraInactiveMode { "Complete (Let Particles Finish then Kill Emitter)", "Kill (Emitter and Particles Die Immediately)", "Continue (Emitter Deactivates But Doesn't Die Until System Does)", ENiagaraInactiveMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 928C9D4A452D8695083BE1A77C6A1BEB
    namespace Niagara.Enums.ENiagaraKillVolumeOptions {
        enum ENiagaraKillVolumeOptions { Sphere, Box, Plane, Slab, Cone, ENiagaraKillVolumeOptions_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: C2C7A8A041D9BF7A98FCA1B8587C4D05
    namespace Niagara.Enums.ENiagaraLinearColor_Channels {
        enum ENiagaraLinearColor_Channels { R, G, B, A, ENiagaraLinearColor_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 00FE367C4D719E332A6E429EA412C88C
    namespace Niagara.Enums.ENiagaraMassByVolume {
        enum ENiagaraMassByVolume { Rock, Steel, Wood, Water, Paper, Styrofoam, ENiagaraMassByVolume_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 120E7FDD41AA1390312334B7B1F551C3
    namespace Niagara.Enums.ENiagaraMassCalculationForRendererTypes {
        enum ENiagaraMassCalculationForRendererTypes { Sprite, Mesh, Ribbon, ENiagaraMassCalculationForRendererTypes_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 4C5A106840EF8917E9BA48A5B406AEEB
    namespace Niagara.Enums.ENiagaraMeshOrSprite {
        enum ENiagaraMeshOrSprite { Sprite, Mesh, ENiagaraMeshOrSprite_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: AFB3125C4B5FBBCCF509D5BEC662150C
    namespace Niagara.Enums.ENiagaraMeshSamplingMode {
        enum ENiagaraMeshSamplingMode { Random, Direct, ENiagaraMeshSamplingMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 329058674538E0C5268F01800B0AC01C
    namespace Niagara.Enums.ENiagaraMeshSurfaceSamplingMode {
        enum ENiagaraMeshSurfaceSamplingMode { Triangles, Vertices, ENiagaraMeshSurfaceSamplingMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 7AC62D184EA8180ADDA483B8089182F2
    namespace Niagara.Enums.ENiagaraMeshTransforms {
        enum ENiagaraMeshTransforms { Simulation, World, Local, Mesh, ENiagaraMeshTransforms_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 671755AA4199F6C8FB91E093ED8FAFD4
    namespace Niagara.Enums.ENiagaraMinOrMax {
        enum ENiagaraMinOrMax { Min, Max, ENiagaraMinOrMax_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 960467B94C4525748B40C6A3CE9CB49D
    namespace Niagara.Enums.ENiagaraNumericVariableTypes {
        enum ENiagaraNumericVariableTypes { Float, "Vector 2D", "Vector 3D", "Vector 4D", "Linear Color", Quaternion, ENiagaraNumericVariableTypes_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: B846FD0A4E3E2D7546B67FAABFF0D63A
    namespace Niagara.Enums.ENiagaraOrientationAxis {
        enum ENiagaraOrientationAxis { "X Axis", "Y Axis", "Z Axis", ENiagaraOrientationAxis_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 1F5CF78A480C93C54C7D2EBA95C75ECA
    namespace Niagara.Enums.ENiagaraQuaternionDerivationTechnique {
        enum ENiagaraQuaternionDerivationTechnique { "X Vector", "X And Y Vectors", "X And Z Vectors", ENiagaraQuaternionDerivationTechnique_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 97A49B82400C51F1BC4FBCA12EEB05C5
    namespace Niagara.Enums.ENiagaraRandomnessEvaluation {
        enum ENiagaraRandomnessEvaluation { "Spawn Only", "Every Frame", ENiagaraRandomnessEvaluation_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 772AB25542D24177E7B56A80ADFDE215
    namespace Engine.EditorResources.FieldNodes.Linear_Velocity_for_Cloth {
        class Linear_Velocity_for_Cloth_C extends UE.FieldSystemActor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            FieldSystemMetaDataProcessingResolution: UE.FieldSystemMetaDataProcessingResolution;
            SM_PlanarNormal_Arrow2: UE.StaticMeshComponent;
            PlaneVolumeFalloffDistance: UE.StaticMeshComponent;
            PlaneVolumeBox: UE.BoxComponent;
            PlaneVolume: UE.StaticMeshComponent;
            SM_DirectionArrow: UE.StaticMeshComponent;
            DirectionalArrowNull: UE.SphereComponent;
            SphereVolumeCol: UE.SphereComponent;
            SM_RadialArrow: UE.StaticMeshComponent;
            SM_RadialArrow4: UE.StaticMeshComponent;
            SM_RadialArrow3: UE.StaticMeshComponent;
            SM_RadialArrow2: UE.StaticMeshComponent;
            SM_RadialArrow1: UE.StaticMeshComponent;
            SM_RadialArrow5: UE.StaticMeshComponent;
            SM_PlanarNormal_Arrow1: UE.StaticMeshComponent;
            SM_DirectionArrow1: UE.StaticMeshComponent;
            SM_DirectionArrow2: UE.StaticMeshComponent;
            NoiseMaxValueText: UE.TextRenderComponent;
            NoiseMinValueText: UE.TextRenderComponent;
            TorqueValueText: UE.TextRenderComponent;
            ["Noise MinMaxTitle Text"]: UE.TextRenderComponent;
            TorqueTitleText: UE.TextRenderComponent;
            DirectionalValueText: UE.TextRenderComponent;
            DirectionalMagTitleText: UE.TextRenderComponent;
            RadialValueText: UE.TextRenderComponent;
            ["Radial Mag Title Text"]: UE.TextRenderComponent;
            StrainValueText: UE.TextRenderComponent;
            StrainTitleText: UE.TextRenderComponent;
            DelayTitleText: UE.TextRenderComponent;
            ActiveTitleText: UE.TextRenderComponent;
            DelayValueText: UE.TextRenderComponent;
            SphereVolume: UE.StaticMeshComponent;
            ActiveValueText: UE.TextRenderComponent;
            FieldTitleText: UE.TextRenderComponent;
            BoxVolume: UE.StaticMeshComponent;
            ["Field Text"]: UE.TextRenderComponent;
            BoxVolumeCol: UE.BoxComponent;
            ReturnResultsTerminal: UE.ReturnResultsTerminal;
            ["Field Active"]: boolean;
            OperatorFIeld_Input: UE.OperatorField;
            Debug: boolean;
            ActivationType: UE.Engine.EditorResources.FieldNodes._Resources.EFieldActivationType.EFieldActivationType;
            ["Field Falloff Shape"]: UE.Engine.EditorResources.FieldNodes._Resources.EFieldShapeType.EFieldShapeType;
            UseTick: boolean;
            DelayAmount: number;
            ["Use External Strain"]: boolean;
            ["Strain Magnitude"]: number;
            StrainFalloffType: UE.EFieldFalloffType;
            StrainFalloffMinMax: UE.Vector2D;
            NumStrainHits: number;
            UseRadialVector: boolean;
            ["Radial Magnitude"]: number;
            UseDirectionalVector: boolean;
            DirectionalMagnitude: number;
            UseTorque: boolean;
            TorqueMult: number;
            VelocityFieldFalloffType: UE.EFieldFalloffType;
            VelocityFalloffMinMax: UE.Vector2D;
            UseNoise: boolean;
            NoiseMinMax: UE.Vector2D;
            UseDecay: boolean;
            DecayAmount: number;
            DecayFalloffType: UE.EFieldFalloffType;
            DecayFalloffMinMax: UE.Vector2D;
            FieldVolume: UE.StaticMeshComponent;
            DecayDelay: number;
            MaxDecayAmount: number;
            RadialPositionOffset: UE.Vector;
            OverideDIrectionalVector: boolean;
            DIrectionalVectorOveride: UE.Vector;
            TorqueVectorOveride: UE.Vector;
            ["Force/Velocity Vector Switch"]: UE.Engine.EditorResources.FieldNodes._Resources.EFieldForceVel.EFieldForceVel;
            ForceMult: number;
            BoxCullingOnPlanar: boolean;
            PlanarFalloffDistOveride: number;
            ["Force Dynamic Switch"]: boolean;
            ActivateTaggedStaticAndSkeletal: boolean;
            ["Chaos Field Name"]: string;
            FieldColour: UE.LinearColor;
            ShowDebugText: boolean;
            ShowWireFrame: boolean;
            ShowSolidShapes: boolean;
            DirectionalDisplayScale: number;
            RadialDisplayScale: number;
            ["Text Vertical Offset"]: number;
            LinearPhysicsType: UE.EFieldPhysicsType;
            AngularPhysicsType: UE.EFieldPhysicsType;
            FieldFalloffType: UE.EFieldFalloffType;
            ["Field Falloff Noise"]: UE.EFieldFalloffType;
            ["Field Falloff Torque"]: UE.EFieldFalloffType;
            UseLifespan: boolean;
            FieldLifespan: number;
            UseFramesForTiming: boolean;
            FPS: number;
            ["Dynamic State"]: UE.EObjectStateTypeEnum;
            PlanarFalloffDist: number;
            TotalDecay: number;
            FalloffMinMax: UE.Vector2D;
            PlanarFalloffExtentColor: UE.LinearColor;
            DIrectionalVelocityVector: UE.Vector;
            upVector: UE.Vector;
            worldLocation: UE.Vector;
            forwardVector: UE.Vector;
            rightVector: UE.Vector;
            skel: UE.SkeletalMeshComponent;
            SimmableStaticMeshes: TArray<UE.StaticMeshActor>;
            SimmableSkelMeshes: TArray<UE.SkeletalMeshActor>;
            PulseLevel: string;
            TextDisplay: TArray<string>;
            AllText: TArray<UE.TextRenderComponent>;
            ArrowColour_Dir: UE.LinearColor;
            ArrowColour_Normal: UE.LinearColor;
            DeactivatedColour: UE.LinearColor;
            DeactivatedTextColour: UE.LinearColor;
            ["Preview Material"]: UE.MaterialInstanceDynamic;
            TimeElapsed: number;
            NoiseScaleMult: number;
            NewVar_0: UE.Transform;
            isTriggered: boolean;
            NoiseScaleBase: number;
            DestroyActor: boolean;
            FieldFalloffType_Input: UE.EFieldFalloffType;
            FalloffMinMax_Input: UE.Vector2D;
            Magnitude_Input: number;
            CalculateNoise(OutputPin: $Ref<UE.NoiseField>) : void;
            CE_Trigger() : void;
            DisplayTextSetup() : void;
            ExecuteUbergraph_Linear_Velocity_for_Cloth(EntryPoint: number) : void;
            FalloffAndCullSwitch_Main(Magnitude: number, FalloffType: UE.EFieldFalloffType, FalloffMinMax: UE.Vector2D, OperatorField: $Nullable<UE.OperatorField>, CullingField: $Ref<UE.CullingField>) : void;
            FalloffShapeSwitch(falloffType: UE.EFieldFalloffType, falloffMinMax: UE.Vector2D, OperatorFieldOut: $Ref<UE.OperatorField>) : void;
            ForceMultiplier() : void;
            InitializeFieldVariables() : void;
            MakeDynamic_EnableNonGC() : void;
            /*
             *Event when play begins for this actor.
             */
            ReceiveBeginPlay() : void;
            /*
             *Event called every frame, if ticking is enabled
             */
            ReceiveTick(DeltaSeconds: number) : void;
            SetVisibility() : void;
            /*
             *Construction script, the place to spawn components and do other setup.
             *@note Name used in CreateBlueprint function
             */
            UserConstructionScript() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Linear_Velocity_for_Cloth_C;
            static Load(InName: string): Linear_Velocity_for_Cloth_C;
        
            __tid_Linear_Velocity_for_Cloth_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: E713F1FD431FDF7F52E76E93A925A73A
    namespace Niagara.Enums.ENiagaraRegionCoordinateSpace {
        enum ENiagaraRegionCoordinateSpace { World, Local, ENiagaraRegionCoordinateSpace_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 69D069A749FE7BEF4E002FAED6D7C7F6
    namespace Engine.EditorResources.FieldNodes.Linear_Force_for_Cloth {
        class Linear_Force_for_Cloth_C extends UE.FieldSystemActor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            FieldSystemMetaDataProcessingResolution: UE.FieldSystemMetaDataProcessingResolution;
            SM_PlanarNormal_Arrow2: UE.StaticMeshComponent;
            PlaneVolumeFalloffDistance: UE.StaticMeshComponent;
            PlaneVolumeBox: UE.BoxComponent;
            PlaneVolume: UE.StaticMeshComponent;
            SM_DirectionArrow: UE.StaticMeshComponent;
            DirectionalArrowNull: UE.SphereComponent;
            SphereVolumeCol: UE.SphereComponent;
            SM_RadialArrow: UE.StaticMeshComponent;
            SM_RadialArrow4: UE.StaticMeshComponent;
            SM_RadialArrow3: UE.StaticMeshComponent;
            SM_RadialArrow2: UE.StaticMeshComponent;
            SM_RadialArrow1: UE.StaticMeshComponent;
            SM_RadialArrow5: UE.StaticMeshComponent;
            SM_PlanarNormal_Arrow1: UE.StaticMeshComponent;
            SM_DirectionArrow1: UE.StaticMeshComponent;
            SM_DirectionArrow2: UE.StaticMeshComponent;
            NoiseMaxValueText: UE.TextRenderComponent;
            NoiseMinValueText: UE.TextRenderComponent;
            TorqueValueText: UE.TextRenderComponent;
            ["Noise MinMaxTitle Text"]: UE.TextRenderComponent;
            TorqueTitleText: UE.TextRenderComponent;
            DirectionalValueText: UE.TextRenderComponent;
            DirectionalMagTitleText: UE.TextRenderComponent;
            RadialValueText: UE.TextRenderComponent;
            ["Radial Mag Title Text"]: UE.TextRenderComponent;
            StrainValueText: UE.TextRenderComponent;
            StrainTitleText: UE.TextRenderComponent;
            DelayTitleText: UE.TextRenderComponent;
            ActiveTitleText: UE.TextRenderComponent;
            DelayValueText: UE.TextRenderComponent;
            SphereVolume: UE.StaticMeshComponent;
            ActiveValueText: UE.TextRenderComponent;
            FieldTitleText: UE.TextRenderComponent;
            BoxVolume: UE.StaticMeshComponent;
            ["Field Text"]: UE.TextRenderComponent;
            BoxVolumeCol: UE.BoxComponent;
            ReturnResultsTerminal: UE.ReturnResultsTerminal;
            ["Field Active"]: boolean;
            OperatorFIeld_Input: UE.OperatorField;
            Debug: boolean;
            ActivationType: UE.Engine.EditorResources.FieldNodes._Resources.EFieldActivationType.EFieldActivationType;
            ["Field Falloff Shape"]: UE.Engine.EditorResources.FieldNodes._Resources.EFieldShapeType.EFieldShapeType;
            UseTick: boolean;
            DelayAmount: number;
            ["Use External Strain"]: boolean;
            ["Strain Magnitude"]: number;
            StrainFalloffType: UE.EFieldFalloffType;
            StrainFalloffMinMax: UE.Vector2D;
            NumStrainHits: number;
            UseRadialVector: boolean;
            ["Radial Magnitude"]: number;
            UseDirectionalVector: boolean;
            DirectionalMagnitude: number;
            UseTorque: boolean;
            TorqueMult: number;
            VelocityFieldFalloffType: UE.EFieldFalloffType;
            VelocityFalloffMinMax: UE.Vector2D;
            UseNoise: boolean;
            NoiseMinMax: UE.Vector2D;
            UseDecay: boolean;
            DecayAmount: number;
            DecayFalloffType: UE.EFieldFalloffType;
            DecayFalloffMinMax: UE.Vector2D;
            FieldVolume: UE.StaticMeshComponent;
            DecayDelay: number;
            MaxDecayAmount: number;
            RadialPositionOffset: UE.Vector;
            OverideDIrectionalVector: boolean;
            DIrectionalVectorOveride: UE.Vector;
            TorqueVectorOveride: UE.Vector;
            ["Force/Velocity Vector Switch"]: UE.Engine.EditorResources.FieldNodes._Resources.EFieldForceVel.EFieldForceVel;
            ForceMult: number;
            BoxCullingOnPlanar: boolean;
            PlanarFalloffDistOveride: number;
            ["Force Dynamic Switch"]: boolean;
            ActivateTaggedStaticAndSkeletal: boolean;
            ["Chaos Field Name"]: string;
            FieldColour: UE.LinearColor;
            ShowDebugText: boolean;
            ShowWireFrame: boolean;
            ShowSolidShapes: boolean;
            DirectionalDisplayScale: number;
            RadialDisplayScale: number;
            ["Text Vertical Offset"]: number;
            LinearPhysicsType: UE.EFieldPhysicsType;
            AngularPhysicsType: UE.EFieldPhysicsType;
            FieldFalloffType: UE.EFieldFalloffType;
            ["Field Falloff Noise"]: UE.EFieldFalloffType;
            ["Field Falloff Torque"]: UE.EFieldFalloffType;
            UseLifespan: boolean;
            FieldLifespan: number;
            UseFramesForTiming: boolean;
            FPS: number;
            ["Dynamic State"]: UE.EObjectStateTypeEnum;
            PlanarFalloffDist: number;
            TotalDecay: number;
            FalloffMinMax: UE.Vector2D;
            PlanarFalloffExtentColor: UE.LinearColor;
            DIrectionalVelocityVector: UE.Vector;
            upVector: UE.Vector;
            worldLocation: UE.Vector;
            forwardVector: UE.Vector;
            rightVector: UE.Vector;
            skel: UE.SkeletalMeshComponent;
            SimmableStaticMeshes: TArray<UE.StaticMeshActor>;
            SimmableSkelMeshes: TArray<UE.SkeletalMeshActor>;
            PulseLevel: string;
            TextDisplay: TArray<string>;
            AllText: TArray<UE.TextRenderComponent>;
            ArrowColour_Dir: UE.LinearColor;
            ArrowColour_Normal: UE.LinearColor;
            DeactivatedColour: UE.LinearColor;
            DeactivatedTextColour: UE.LinearColor;
            ["Preview Material"]: UE.MaterialInstanceDynamic;
            TimeElapsed: number;
            NoiseScaleMult: number;
            NewVar_0: UE.Transform;
            isTriggered: boolean;
            NoiseScaleBase: number;
            DestroyActor: boolean;
            FieldFalloffType_Input: UE.EFieldFalloffType;
            FalloffMinMax_Input: UE.Vector2D;
            Magnitude_Input: number;
            CalculateNoise(OutputPin: $Ref<UE.NoiseField>) : void;
            CE_Trigger() : void;
            DisplayTextSetup() : void;
            ExecuteUbergraph_Linear_Force_for_Cloth(EntryPoint: number) : void;
            FalloffAndCullSwitch_Main(Magnitude: number, FalloffType: UE.EFieldFalloffType, FalloffMinMax: UE.Vector2D, OperatorField: $Nullable<UE.OperatorField>, CullingField: $Ref<UE.CullingField>) : void;
            FalloffShapeSwitch(falloffType: UE.EFieldFalloffType, falloffMinMax: UE.Vector2D, OperatorFieldOut: $Ref<UE.OperatorField>) : void;
            ForceMultiplier() : void;
            InitializeFieldVariables() : void;
            MakeDynamic_EnableNonGC() : void;
            /*
             *Event when play begins for this actor.
             */
            ReceiveBeginPlay() : void;
            /*
             *Event called every frame, if ticking is enabled
             */
            ReceiveTick(DeltaSeconds: number) : void;
            SetVisibility() : void;
            /*
             *Construction script, the place to spawn components and do other setup.
             *@note Name used in CreateBlueprint function
             */
            UserConstructionScript() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Linear_Force_for_Cloth_C;
            static Load(InName: string): Linear_Force_for_Cloth_C;
        
            __tid_Linear_Force_for_Cloth_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: CAA5F96D4B54FB1847210EA57262DB73
    namespace Niagara.Enums.ENiagaraRegionTransformOrder {
        enum ENiagaraRegionTransformOrder { "Offset-Rotation", "Rotation-Offset", ENiagaraRegionTransformOrder_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: A8F19F6A46087E825E50A2B6A691A826
    namespace Engine.EditorResources.FieldNodes.FS_SleepDisable_Generic {
        class FS_SleepDisable_Generic_C extends UE.FieldSystemActor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            PlaneVolumeBoxCol: UE.BoxComponent;
            TresholdTitleText: UE.TextRenderComponent;
            ActiveTitleText: UE.TextRenderComponent;
            UniformScalar: UE.UniformScalar;
            ThresholdValueText: UE.TextRenderComponent;
            ActiveValueText: UE.TextRenderComponent;
            PlaneFalloff_Magnitude: UE.PlaneFalloff;
            RadialFalloff_Magnitude: UE.RadialFalloff;
            CullingField_Plane: UE.CullingField;
            RadialFalloff: UE.RadialFalloff;
            CullingField_Box: UE.CullingField;
            PlaneFalloff: UE.PlaneFalloff;
            RadialVector: UE.RadialVector;
            UniformInteger: UE.UniformInteger;
            BoxFalloff_Magnitude: UE.BoxFalloff;
            CullingField_Sphere: UE.CullingField;
            Arrow: UE.ArrowComponent;
            BoxVolume: UE.StaticMeshComponent;
            SphereVolume: UE.StaticMeshComponent;
            PlaneVolume: UE.StaticMeshComponent;
            BoxVolumeCol: UE.BoxComponent;
            SphereVolumeCol: UE.SphereComponent;
            SleepTitleText: UE.TextRenderComponent;
            ["Sleep Text"]: UE.TextRenderComponent;
            CullingField: UE.CullingField;
            BoxFalloff: UE.BoxFalloff;
            ["Field Active"]: boolean;
            Threshold: number;
            ["Field Falloff Shape"]: UE.Engine.EditorResources.FieldNodes._Resources.EFieldShapeType.EFieldShapeType;
            ["Field Behavior"]: UE.Engine.EditorResources.FieldNodes._Resources.EFieldSleepType.EFieldSleepType;
            Debug: boolean;
            FaloffType: UE.EFieldFalloffType;
            FalloffMinMax: UE.Vector2D;
            PhysicsType: UE.EFieldPhysicsType;
            Deactivated: UE.LinearColor;
            ShowDebugText: boolean;
            ShowWireFrame: boolean;
            FieldVolume: UE.StaticMeshComponent;
            DeactivatedText: UE.LinearColor;
            SleepText: string;
            DisableText: string;
            KillText: string;
            ShowSolidShapes: boolean;
            ["Sleep Colour Def"]: UE.LinearColor;
            DisableColour: UE.LinearColor;
            KillColour: UE.LinearColor;
            ["Sleep Colour"]: UE.LinearColor;
            ["Text Vertical Offset"]: number;
            TextScaleMult: number;
            ExecuteUbergraph_FS_SleepDisable_Generic(EntryPoint: number) : void;
            ["Falloff Field Switch"](Magnitude: number, FaloffType: UE.EFieldFalloffType, CullingField: $Ref<UE.CullingField>) : void;
            /*
             *Event when play begins for this actor.
             */
            ReceiveBeginPlay() : void;
            /*
             *Event called every frame, if ticking is enabled
             */
            ReceiveTick(DeltaSeconds: number) : void;
            SetFalloffVisibility() : void;
            /*
             *Construction script, the place to spawn components and do other setup.
             *@note Name used in CreateBlueprint function
             */
            UserConstructionScript() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): FS_SleepDisable_Generic_C;
            static Load(InName: string): FS_SleepDisable_Generic_C;
        
            __tid_FS_SleepDisable_Generic_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 729D522B40456DFC4C7F9F82B42AF259
    namespace Niagara.Enums.ENiagaraRestitutionMergeType {
        enum ENiagaraRestitutionMergeType { Ignore, Min, Max, Average, ENiagaraRestitutionMergeType_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 290402E54F1963D196450A8975DB54E8
    namespace Niagara.Enums.ENiagaraScaleColorMode {
        enum ENiagaraScaleColorMode { "RGB and Alpha Separately", "RGBA Together", "RGBA Linear Color Curve", ENiagaraScaleColorMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: AA46B5824B249A67BC25B58357A0A379
    namespace Niagara.Enums.ENiagaraShapeTorusMode {
        enum ENiagaraShapeTorusMode { Torus, TorusKnot, ENiagaraShapeTorusMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: FFE6C69C4E5A2E62ADF3F6875F8863AC
    namespace Niagara.Enums.ENiagaraSimulationTarget {
        enum ENiagaraSimulationTarget { "CPU Sim", "GPUCompute Sim", ENiagaraSimulationTarget_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 57D413CF427640F466EC56850F8AA6AC
    namespace Engine.EditorResources.FieldNodes.FS_MasterField {
        class FS_MasterField_C extends UE.FieldSystemActor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            FieldSystemMetaDataProcessingResolution: UE.FieldSystemMetaDataProcessingResolution;
            SM_PlanarNormal_Arrow2: UE.StaticMeshComponent;
            PlaneVolumeFalloffDistance: UE.StaticMeshComponent;
            PlaneVolumeBox: UE.BoxComponent;
            PlaneVolume: UE.StaticMeshComponent;
            SM_DirectionArrow: UE.StaticMeshComponent;
            DirectionalArrowNull: UE.SphereComponent;
            SphereVolumeCol: UE.SphereComponent;
            SM_RadialArrow: UE.StaticMeshComponent;
            SM_RadialArrow4: UE.StaticMeshComponent;
            SM_RadialArrow3: UE.StaticMeshComponent;
            SM_RadialArrow2: UE.StaticMeshComponent;
            SM_RadialArrow1: UE.StaticMeshComponent;
            SM_RadialArrow5: UE.StaticMeshComponent;
            SM_PlanarNormal_Arrow1: UE.StaticMeshComponent;
            SM_DirectionArrow1: UE.StaticMeshComponent;
            SM_DirectionArrow2: UE.StaticMeshComponent;
            NoiseMaxValueText: UE.TextRenderComponent;
            NoiseMinValueText: UE.TextRenderComponent;
            TorqueValueText: UE.TextRenderComponent;
            ["Noise MinMaxTitle Text"]: UE.TextRenderComponent;
            TorqueTitleText: UE.TextRenderComponent;
            DirectionalValueText: UE.TextRenderComponent;
            DirectionalMagTitleText: UE.TextRenderComponent;
            RadialValueText: UE.TextRenderComponent;
            ["Radial Mag Title Text"]: UE.TextRenderComponent;
            StrainValueText: UE.TextRenderComponent;
            StrainTitleText: UE.TextRenderComponent;
            DelayTitleText: UE.TextRenderComponent;
            ActiveTitleText: UE.TextRenderComponent;
            DelayValueText: UE.TextRenderComponent;
            SphereVolume: UE.StaticMeshComponent;
            ActiveValueText: UE.TextRenderComponent;
            FieldTitleText: UE.TextRenderComponent;
            BoxVolume: UE.StaticMeshComponent;
            ["Field Text"]: UE.TextRenderComponent;
            BoxVolumeCol: UE.BoxComponent;
            ReturnResultsTerminal: UE.ReturnResultsTerminal;
            ["Field Active"]: boolean;
            OperatorFIeld_Input: UE.OperatorField;
            Debug: boolean;
            ActivationType: UE.Engine.EditorResources.FieldNodes._Resources.EFieldActivationType.EFieldActivationType;
            ["Field Falloff Shape"]: UE.Engine.EditorResources.FieldNodes._Resources.EFieldShapeType.EFieldShapeType;
            UseTick: boolean;
            DelayAmount: number;
            ["Use External Strain"]: boolean;
            ["Strain Magnitude"]: number;
            StrainFalloffType: UE.EFieldFalloffType;
            StrainFalloffMinMax: UE.Vector2D;
            NumStrainHits: number;
            UseRadialVector: boolean;
            ["Radial Magnitude"]: number;
            UseDirectionalVector: boolean;
            DirectionalMagnitude: number;
            UseTorque: boolean;
            TorqueMult: number;
            VelocityFieldFalloffType: UE.EFieldFalloffType;
            VelocityFalloffMinMax: UE.Vector2D;
            UseNoise: boolean;
            NoiseMinMax: UE.Vector2D;
            UseDecay: boolean;
            DecayAmount: number;
            DecayFalloffType: UE.EFieldFalloffType;
            DecayFalloffMinMax: UE.Vector2D;
            FieldVolume: UE.StaticMeshComponent;
            DecayDelay: number;
            MaxDecayAmount: number;
            RadialPositionOffset: UE.Vector;
            OverideDIrectionalVector: boolean;
            DIrectionalVectorOveride: UE.Vector;
            TorqueVectorOveride: UE.Vector;
            ["Force/Velocity Vector Switch"]: UE.Engine.EditorResources.FieldNodes._Resources.EFieldForceVel.EFieldForceVel;
            ForceMult: number;
            BoxCullingOnPlanar: boolean;
            PlanarFalloffDistOveride: number;
            ["Force Dynamic Switch"]: boolean;
            ActivateTaggedStaticAndSkeletal: boolean;
            ["Chaos Field Name"]: string;
            FieldColour: UE.LinearColor;
            ShowDebugText: boolean;
            ShowWireFrame: boolean;
            ShowSolidShapes: boolean;
            DirectionalDisplayScale: number;
            RadialDisplayScale: number;
            ["Text Vertical Offset"]: number;
            LinearPhysicsType: UE.EFieldPhysicsType;
            AngularPhysicsType: UE.EFieldPhysicsType;
            FieldFalloffType: UE.EFieldFalloffType;
            ["Field Falloff Noise"]: UE.EFieldFalloffType;
            ["Field Falloff Torque"]: UE.EFieldFalloffType;
            UseLifespan: boolean;
            FieldLifespan: number;
            UseFramesForTiming: boolean;
            FPS: number;
            ["Dynamic State"]: UE.EObjectStateTypeEnum;
            PlanarFalloffDist: number;
            TotalDecay: number;
            FalloffMinMax: UE.Vector2D;
            PlanarFalloffExtentColor: UE.LinearColor;
            DIrectionalVelocityVector: UE.Vector;
            upVector: UE.Vector;
            worldLocation: UE.Vector;
            forwardVector: UE.Vector;
            rightVector: UE.Vector;
            skel: UE.SkeletalMeshComponent;
            SimmableStaticMeshes: TArray<UE.StaticMeshActor>;
            SimmableSkelMeshes: TArray<UE.SkeletalMeshActor>;
            PulseLevel: string;
            TextDisplay: TArray<string>;
            AllText: TArray<UE.TextRenderComponent>;
            ArrowColour_Dir: UE.LinearColor;
            ArrowColour_Normal: UE.LinearColor;
            DeactivatedColour: UE.LinearColor;
            DeactivatedTextColour: UE.LinearColor;
            ["Preview Material"]: UE.MaterialInstanceDynamic;
            TimeElapsed: number;
            NoiseScaleMult: number;
            NewVar_0: UE.Transform;
            isTriggered: boolean;
            NoiseScaleBase: number;
            DestroyActor: boolean;
            FieldFalloffType_Input: UE.EFieldFalloffType;
            FalloffMinMax_Input: UE.Vector2D;
            Magnitude_Input: number;
            CalculateNoise(OutputPin: $Ref<UE.NoiseField>) : void;
            CE_Trigger() : void;
            DisplayTextSetup() : void;
            ExecuteUbergraph_FS_MasterField(EntryPoint: number) : void;
            FalloffAndCullSwitch_Main(Magnitude: number, FalloffType: UE.EFieldFalloffType, FalloffMinMax: UE.Vector2D, OperatorField: $Nullable<UE.OperatorField>, CullingField: $Ref<UE.CullingField>) : void;
            FalloffShapeSwitch(falloffType: UE.EFieldFalloffType, falloffMinMax: UE.Vector2D, OperatorFieldOut: $Ref<UE.OperatorField>) : void;
            ForceMultiplier() : void;
            InitializeFieldVariables() : void;
            MakeDynamic_EnableNonGC() : void;
            /*
             *Event when play begins for this actor.
             */
            ReceiveBeginPlay() : void;
            /*
             *Event called every frame, if ticking is enabled
             */
            ReceiveTick(DeltaSeconds: number) : void;
            SetVisibility() : void;
            /*
             *Construction script, the place to spawn components and do other setup.
             *@note Name used in CreateBlueprint function
             */
            UserConstructionScript() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): FS_MasterField_C;
            static Load(InName: string): FS_MasterField_C;
        
            __tid_FS_MasterField_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 0A6EB7DA4215964E117EE1B0BB586B64
    namespace Niagara.Enums.ENiagaraSkeletalSpawning {
        enum ENiagaraSkeletalSpawning { Bones, Sockets, "Bones and Sockets", ENiagaraSkeletalSpawning_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: A09F24E9474B9FB09B1BACB3EB14BFBA
    namespace Engine.EditorResources.FieldNodes.FS_BombField_Prototype {
        class FS_BombField_Prototype_C extends UE.FieldSystemActor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            FieldSystemMetaDataProcessingResolution: UE.FieldSystemMetaDataProcessingResolution;
            SphereVolumeCol: UE.SphereComponent;
            bomb: UE.SphereComponent;
            bombVolume: UE.StaticMeshComponent;
            PlaneFalloff_ForceDynamic: UE.PlaneFalloff;
            RadialFalloff_ForceDynamic: UE.RadialFalloff;
            OperatorField_ForceDynamic: UE.OperatorField;
            BoxFalloff_ForceDynamic: UE.BoxFalloff;
            PlaneFalloff_InternalStrain: UE.PlaneFalloff;
            BoxFalloff_InternalStrain: UE.BoxFalloff;
            OperatorField_InternalStrain: UE.OperatorField;
            RadialFalloff_InternalStrain: UE.RadialFalloff;
            UniformIntegerFalloff: UE.UniformInteger;
            SM_PlanarNormal_Arrow2: UE.StaticMeshComponent;
            PlaneVolumeFalloffDistance: UE.StaticMeshComponent;
            PlaneVolumeBox: UE.BoxComponent;
            PlaneVolume: UE.StaticMeshComponent;
            SM_DirectionArrow: UE.StaticMeshComponent;
            DirectionalArrowNull: UE.SphereComponent;
            SM_RadialArrow: UE.StaticMeshComponent;
            SM_RadialArrow4: UE.StaticMeshComponent;
            SM_RadialArrow3: UE.StaticMeshComponent;
            SM_RadialArrow2: UE.StaticMeshComponent;
            SM_RadialArrow1: UE.StaticMeshComponent;
            SM_RadialArrow5: UE.StaticMeshComponent;
            CullingField_Plane2: UE.CullingField;
            SM_PlanarNormal_Arrow1: UE.StaticMeshComponent;
            SM_DirectionArrow1: UE.StaticMeshComponent;
            SM_DirectionArrow2: UE.StaticMeshComponent;
            NoiseMaxValueText: UE.TextRenderComponent;
            NoiseMinValueText: UE.TextRenderComponent;
            TorqueValueText: UE.TextRenderComponent;
            ["Noise MinMaxTitle Text"]: UE.TextRenderComponent;
            TorqueTitleText: UE.TextRenderComponent;
            DirectionalValueText: UE.TextRenderComponent;
            DirectionalMagTitleText: UE.TextRenderComponent;
            RadialValueText: UE.TextRenderComponent;
            ["Radial Mag Title Text"]: UE.TextRenderComponent;
            StrainValueText: UE.TextRenderComponent;
            StrainTitleText: UE.TextRenderComponent;
            DelayTitleText: UE.TextRenderComponent;
            ActiveTitleText: UE.TextRenderComponent;
            DelayValueText: UE.TextRenderComponent;
            OperatorField_FalloffSwitch_Plane: UE.OperatorField;
            OperatorField_FalloffSwitch_Sph: UE.OperatorField;
            OperatorField_FalloffSwitch_Box: UE.OperatorField;
            CullingField_Plane: UE.CullingField;
            PlaneFalloff_Magnitude: UE.PlaneFalloff;
            PlaneFalloff: UE.PlaneFalloff;
            CullingField_Box: UE.CullingField;
            BoxFalloff_Culling: UE.BoxFalloff;
            BoxFalloff: UE.BoxFalloff;
            BoxFalloff_Magnitude: UE.BoxFalloff;
            SphereVolume: UE.StaticMeshComponent;
            ActiveValueText: UE.TextRenderComponent;
            FieldTitleText: UE.TextRenderComponent;
            BoxVolume: UE.StaticMeshComponent;
            ["Field Text"]: UE.TextRenderComponent;
            BoxVolumeCol: UE.BoxComponent;
            UniformScalarDecay: UE.UniformScalar;
            OperatorFieldDecay1: UE.OperatorField;
            OperatorFieldDecay2: UE.OperatorField;
            ReturnResultsTerminal: UE.ReturnResultsTerminal;
            OperatorField_torqueC: UE.OperatorField;
            OperatorField_dirNoise: UE.OperatorField;
            OperatorField_radNoise: UE.OperatorField;
            NoiseField_Torque: UE.NoiseField;
            OperatorField_torque_A: UE.OperatorField;
            UniformScalar_torque: UE.UniformScalar;
            CullingField_DynamicState: UE.CullingField;
            UniformInteger: UE.UniformInteger;
            ["CullingField-Decay"]: UE.CullingField;
            CullingFieldSphere: UE.CullingField;
            RadialFalloffMagnitude: UE.RadialFalloff;
            RadialFalloff_cullVolume: UE.RadialFalloff;
            OperatorFieldDecay4: UE.OperatorField;
            CullingField: UE.CullingField;
            RadialFalloff: UE.RadialFalloff;
            OperatorField_torque_B: UE.OperatorField;
            UniformVector_torque: UE.UniformVector;
            RandomVector_torque: UE.RandomVector;
            NoiseField_dir: UE.NoiseField;
            NoiseField_rad: UE.NoiseField;
            UniformVector_dir: UE.UniformVector;
            RadialVector_rad: UE.RadialVector;
            ["Field Active"]: boolean;
            Debug: boolean;
            ActivationType: UE.Engine.EditorResources.FieldNodes._Resources.EFieldActivationType.EFieldActivationType;
            ["Field Falloff Shape"]: UE.Engine.EditorResources.FieldNodes._Resources.EFieldShapeType.EFieldShapeType;
            UseTick: boolean;
            DelayAmount: number;
            ["Use External Strain"]: boolean;
            ["Strain Magnitude"]: number;
            StrainFalloffType: UE.EFieldFalloffType;
            StrainFalloffMinMax: UE.Vector2D;
            NumStrainHits: number;
            UseRadialVector: boolean;
            ["Radial Magnitude"]: number;
            UseDirectionalVector: boolean;
            DirectionalMagnitude: number;
            UseTorque: boolean;
            TorqueMult: number;
            VelocityFieldFalloffType: UE.EFieldFalloffType;
            VelocityFalloffMinMax: UE.Vector2D;
            UseNoise: boolean;
            NoiseMinMax: UE.Vector2D;
            UseDecay: boolean;
            DecayAmount: number;
            DecayFalloffType: UE.EFieldFalloffType;
            DecayFalloffMinMax: UE.Vector2D;
            FieldVolume: UE.StaticMeshComponent;
            DecayDelay: number;
            MaxDecayAmount: number;
            RadialPositionOffset: UE.Vector;
            OverideDIrectionalVector: boolean;
            DIrectionalVectorOveride: UE.Vector;
            TorqueVectorOveride: UE.Vector;
            ["Force/Velocity Vector Switch"]: UE.Engine.EditorResources.FieldNodes._Resources.EFieldForceVel.EFieldForceVel;
            ForceMult: number;
            BoxCullingOnPlanar: boolean;
            PlanarFalloffDistOveride: number;
            ["Force Dynamic Switch"]: boolean;
            ActivateTaggedStaticAndSkeletal: boolean;
            ["Chaos Field Name"]: string;
            FieldColour: UE.LinearColor;
            ShowDebugText: boolean;
            ShowWireFrame: boolean;
            ShowSolidShapes: boolean;
            DirectionalDisplayScale: number;
            RadialDisplayScale: number;
            ["Text Vertical Offset"]: number;
            LinearPhysicsType: UE.EFieldPhysicsType;
            AngularPhysicsType: UE.EFieldPhysicsType;
            FieldFalloffType: UE.EFieldFalloffType;
            ["Field Falloff Noise"]: UE.EFieldFalloffType;
            ["Field Falloff Torque"]: UE.EFieldFalloffType;
            UseLifespan: boolean;
            FieldLifespan: number;
            UseFramesForTiming: boolean;
            FPS: number;
            ["Dynamic State"]: UE.EObjectStateTypeEnum;
            PlanarFalloffDist: number;
            TotalDecay: number;
            FalloffMinMax: UE.Vector2D;
            PlanarFalloffExtentColor: UE.LinearColor;
            DIrectionalVelocityVector: UE.Vector;
            upVector: UE.Vector;
            worldLocation: UE.Vector;
            forwardVector: UE.Vector;
            rightVector: UE.Vector;
            skel: UE.SkeletalMeshComponent;
            SimmableStaticMeshes: TArray<UE.StaticMeshActor>;
            SimmableSkelMeshes: TArray<UE.SkeletalMeshActor>;
            PulseLevel: string;
            TextDisplay: TArray<string>;
            AllText: TArray<UE.TextRenderComponent>;
            ArrowColour_Dir: UE.LinearColor;
            ArrowColour_Normal: UE.LinearColor;
            DeactivatedColour: UE.LinearColor;
            DeactivatedTextColour: UE.LinearColor;
            ["Preview Material"]: UE.MaterialInstanceDynamic;
            TimeElapsed: number;
            NoiseScaleMult: number;
            NewVar_0: UE.Transform;
            isTriggered: boolean;
            NoiseScaleBase: number;
            DestroyActor: boolean;
            useBomb: boolean;
            bombMinScale: number;
            bombMaxScale: number;
            bombDuration: number;
            bombSize: number;
            bombpos: UE.Vector;
            bombxloc: number;
            bombPosOrig: UE.Vector;
            bombScaleOrig: UE.Vector;
            delta: number;
            totalElapsedTime: number;
            totalDistance: number;
            oldPos: number;
            ["New Location"]: UE.Vector;
            bombExtraDistance: number;
            useBombLocationOffset: boolean;
            useBombPhysics: boolean;
            currentPos: number;
            velocity: number;
            useDynScale: boolean;
            useDynFieldPos: boolean;
            falloffMinMax_Input: UE.Vector2D;
            FieldFalloffType_Input: UE.EFieldFalloffType;
            OperatorField_Input: UE.OperatorField;
            Magnitude_Input: number;
            bombMass: number;
            useProjectile: boolean;
            projectileFired: boolean;
            projectileVelocity: number;
            oldPosVec: UE.Vector;
            currentPosVec: UE.Vector;
            velocityVec: UE.Vector;
            projectileVelocityMult: number;
            projectileMaxScale: number;
            projectileMinMaxVelRange: UE.Vector2D;
            useCCD: boolean;
            CalculateNoise(OutputPin: $Ref<UE.NoiseField>) : void;
            CE_Trigger() : void;
            DisplayTextSetup() : void;
            ExecuteUbergraph_FS_BombField_Prototype(EntryPoint: number) : void;
            FalloffAndCullingSwitch(FalloffType: UE.EFieldFalloffType, OperatorFieldIn: $Nullable<UE.OperatorField>, falloffMinMax: UE.Vector2D, CullingFieldOut: $Ref<UE.CullingField>) : void;
            FalloffAndCullSwitch_Main(Magnitude: number, FalloffType: UE.EFieldFalloffType, FalloffMinMax: UE.Vector2D, OperatorField: $Nullable<UE.OperatorField>, CullingField: $Ref<UE.CullingField>) : void;
            FalloffShapeSwitch(falloffType: UE.EFieldFalloffType, falloffMinMax: UE.Vector2D, falloffMinMax_X: number, falloffMinMax_Y: number, OperatorFieldOut: $Ref<UE.OperatorField>) : void;
            FalloffSwitch(falloffType: UE.EFieldFalloffType, falloffMinMax: UE.Vector2D, OperatorFieldOut: $Ref<UE.OperatorField>, NewParam: $Ref<UE.RadialFalloff>) : void;
            ["FalloffSwitch - Strain"](Magnitude: number, FalloffType: UE.EFieldFalloffType, CullingField: $Ref<UE.CullingField>) : void;
            FalloffSwitch_ForceDynamic(falloffType: UE.EFieldFalloffType, falloffMinMax: UE.Vector2D, OperatorFieldOut: $Ref<UE.OperatorField>) : void;
            FalloffSwitch_InternalStrain(falloffType: UE.EFieldFalloffType, falloffMinMax: UE.Vector2D, OperatorFieldOut: $Ref<UE.OperatorField>) : void;
            ForceMultiplier() : void;
            InitializeFieldVariables() : void;
            MakeDynamic_EnableNonGC() : void;
            /*
             *Event when play begins for this actor.
             */
            ReceiveBeginPlay() : void;
            /*
             *Event called every frame, if ticking is enabled
             */
            ReceiveTick(DeltaSeconds: number) : void;
            SetColliderLocation() : void;
            SetVisibility() : void;
            /*
             *Construction script, the place to spawn components and do other setup.
             *@note Name used in CreateBlueprint function
             */
            UserConstructionScript() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): FS_BombField_Prototype_C;
            static Load(InName: string): FS_BombField_Prototype_C;
        
            __tid_FS_BombField_Prototype_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 296863C84B07E4F0DF6D0C8CC847185B
    namespace Niagara.Enums.ENiagaraSkelMeshPositionSamplingMode {
        enum ENiagaraSkelMeshPositionSamplingMode { "Apply (Rigid)", "Apply (Soft)", Output, ENiagaraSkelMeshPositionSamplingMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 367B26F543D311B934640E87714E5E67
    namespace Engine.EditorResources.FieldNodes.FS_AnchorField_Generic {
        class FS_AnchorField_Generic_C extends UE.FieldSystemActor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            PlaneVolumeCol: UE.BoxComponent;
            ActiveTitleText: UE.TextRenderComponent;
            ["Anchor Title Text"]: UE.TextRenderComponent;
            ActiveValueText: UE.TextRenderComponent;
            ["Anchor Text"]: UE.TextRenderComponent;
            SphereVolume: UE.StaticMeshComponent;
            BoxVolume: UE.StaticMeshComponent;
            Arrow: UE.ArrowComponent;
            SphereVolumeCol: UE.SphereComponent;
            CullingField_Plane: UE.CullingField;
            CullingField_Sphere: UE.CullingField;
            RadialFalloff: UE.RadialFalloff;
            PlaneVolume: UE.StaticMeshComponent;
            PlaneFalloff: UE.PlaneFalloff;
            CullingField_Box: UE.CullingField;
            BoxVolumeCol: UE.BoxComponent;
            BoxFalloff: UE.BoxFalloff;
            UniformInteger: UE.UniformInteger;
            RadialVector: UE.RadialVector;
            ["Dynamic State"]: UE.EObjectStateTypeEnum;
            ["Anchor Active"]: boolean;
            ["Anchor Falloff Shape"]: UE.Engine.EditorResources.FieldNodes._Resources.EFieldShapeType.EFieldShapeType;
            Debug: boolean;
            AnchorColour: UE.LinearColor;
            Deactivated: UE.LinearColor;
            AnchorVolume: UE.StaticMeshComponent;
            AnchorTextDisplay: string;
            ViewDebugText: boolean;
            ViewWireFrame: boolean;
            ViewSolidShapes: boolean;
            TextVerticalOffset: number;
            DeactivatedText: UE.LinearColor;
            TextScaleMult: number;
            AnchorDebugSetup() : void;
            ExecuteUbergraph_FS_AnchorField_Generic(EntryPoint: number) : void;
            ["Falloff Field Switch"](UniformInt: $Nullable<UE.UniformInteger>, CullingField: $Ref<UE.CullingField>) : void;
            /*
             *Event when play begins for this actor.
             */
            ReceiveBeginPlay() : void;
            SetFalloffVisibility() : void;
            /*
             *Construction script, the place to spawn components and do other setup.
             *@note Name used in CreateBlueprint function
             */
            UserConstructionScript() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): FS_AnchorField_Generic_C;
            static Load(InName: string): FS_AnchorField_Generic_C;
        
            __tid_FS_AnchorField_Generic_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: F12BDF26411DA8BD655A219822652BBC
    namespace Niagara.Enums.ENiagaraSkelMeshTransforms {
        enum ENiagaraSkelMeshTransforms { Simulation, World, Local, "Sampled Mesh", "Mesh Particle", ENiagaraSkelMeshTransforms_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 894B68A14B6551F9B5F2699E13FAD018
    namespace Engine.EditorResources.FieldNodes.Niagara.FS_WaveScalarField {
        class FS_WaveScalarField_C extends UE.Engine.EditorResources.FieldNodes.Niagara.FS_BaseField.FS_BaseField_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            ["Enable Field"]: boolean;
            ["Physics Scalar"]: UE.EFieldScalarType;
            ["Field Magnitude"]: number;
            ["Force Physics Dynamic"]: boolean;
            ScalarField: UE.FieldNodeBase;
            ["Wave Length"]: number;
            ["Wave Period"]: number;
            ["Wave Function"]: UE.EWaveFunctionType;
            ["Wave Falloff Type"]: UE.EFieldFalloffType;
            ["Physics Type"]: UE.EFieldPhysicsType;
            ExecuteUbergraph_FS_WaveScalarField(EntryPoint: number) : void;
            /*
             *Event when play begins for this actor.
             */
            ReceiveBeginPlay() : void;
            /*
             *Event called every frame, if ticking is enabled
             */
            ReceiveTick(DeltaSeconds: number) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): FS_WaveScalarField_C;
            static Load(InName: string): FS_WaveScalarField_C;
        
            __tid_FS_WaveScalarField_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: F449D19541D88E508EE7B5B11837D71C
    namespace Niagara.Enums.ENiagaraSkelSamplingFilteringMode {
        enum ENiagaraSkelSamplingFilteringMode { All, Filtered, Unfiltered, ENiagaraSkelSamplingFilteringMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 2EA015C0421A9AB5745DA99F253302F4
    namespace Engine.EditorResources.FieldNodes.Niagara.FS_UniformVectorField {
        class FS_UniformVectorField_C extends UE.Engine.EditorResources.FieldNodes.Niagara.FS_BaseField.FS_BaseField_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            Arrow: UE.ArrowComponent;
            ["Enable Field"]: boolean;
            ["Physics Vector"]: UE.EFieldVectorType;
            ["Field Magnitude"]: number;
            ["Force Physics Dynamic"]: boolean;
            VectorField: UE.FieldNodeBase;
            ["Physics Type"]: UE.EFieldPhysicsType;
            ExecuteUbergraph_FS_UniformVectorField(EntryPoint: number) : void;
            /*
             *Event when play begins for this actor.
             */
            ReceiveBeginPlay() : void;
            /*
             *Event called every frame, if ticking is enabled
             */
            ReceiveTick(DeltaSeconds: number) : void;
            /*
             *Construction script, the place to spawn components and do other setup.
             *@note Name used in CreateBlueprint function
             */
            UserConstructionScript() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): FS_UniformVectorField_C;
            static Load(InName: string): FS_UniformVectorField_C;
        
            __tid_FS_UniformVectorField_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 706BB3E54E4837D284597996628F0BAF
    namespace Niagara.Enums.ENiagaraSkelSamplingModeFull {
        enum ENiagaraSkelSamplingModeFull { "Skeleton (Bones)", "Skeleton (Sockets)", "Skeleton (Bones and Sockets)", "Surface (Triangles)", "Surface (Vertices)", ENiagaraSkelSamplingModeFull_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 633376C440A1DB94FA35DBA64AFE04EC
    namespace Engine.EditorResources.FieldNodes.Niagara.FS_UniformScalarField {
        class FS_UniformScalarField_C extends UE.Engine.EditorResources.FieldNodes.Niagara.FS_BaseField.FS_BaseField_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            ["Enable Field"]: boolean;
            ["Physics Scalar"]: UE.EFieldScalarType;
            ["Field Magnitude"]: number;
            ["Force Physics Dynamic"]: boolean;
            ["Physics Type"]: UE.EFieldPhysicsType;
            ScalarField: UE.FieldNodeBase;
            ExecuteUbergraph_FS_UniformScalarField(EntryPoint: number) : void;
            /*
             *Event when play begins for this actor.
             */
            ReceiveBeginPlay() : void;
            /*
             *Event called every frame, if ticking is enabled
             */
            ReceiveTick(DeltaSeconds: number) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): FS_UniformScalarField_C;
            static Load(InName: string): FS_UniformScalarField_C;
        
            __tid_FS_UniformScalarField_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: B1584DE04E868EAD47D2CDB606B193DC
    namespace Niagara.Enums.ENiagaraSocketSamplingMode {
        enum ENiagaraSocketSamplingMode { "Random (Filtered Sockets)", "Direct (Filtered Sockets)", ENiagaraSocketSamplingMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 7747C34E45618A3C222DE987C2518645
    namespace Engine.EditorResources.FieldNodes.Niagara.FS_RadialField {
        class FS_RadialField_C extends UE.Engine.EditorResources.FieldNodes.Niagara.FS_BaseField.FS_BaseField_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            InnerSphere: UE.SphereComponent;
            ["Enable Field"]: boolean;
            ["Physics Vector"]: UE.EFieldVectorType;
            ["Field Magnitude"]: number;
            ["Force Physics Dynamic"]: boolean;
            VectorField: UE.FieldNodeBase;
            ["Physics Type"]: UE.EFieldPhysicsType;
            ExecuteUbergraph_FS_RadialField(EntryPoint: number) : void;
            /*
             *Event when play begins for this actor.
             */
            ReceiveBeginPlay() : void;
            /*
             *Event called every frame, if ticking is enabled
             */
            ReceiveTick(DeltaSeconds: number) : void;
            /*
             *Construction script, the place to spawn components and do other setup.
             *@note Name used in CreateBlueprint function
             */
            UserConstructionScript() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): FS_RadialField_C;
            static Load(InName: string): FS_RadialField_C;
        
            __tid_FS_RadialField_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: EB56100A4C78D1CCA6805B92E112DA28
    namespace Niagara.Enums.ENiagaraSphereDistributionMode {
        enum ENiagaraSphereDistributionMode { Random, Direct, Uniform, ENiagaraSphereDistributionMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 88B8C6E34571AFC7BC1A54A69AD7E68A
    namespace Engine.EditorResources.FieldNodes.Niagara.FS_BaseField {
        class FS_BaseField_C extends UE.FieldSystemActor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            DynamicStateCullingField: UE.CullingField;
            DynamicStateField: UE.UniformInteger;
            NoiseApplyOperatorField: UE.OperatorField;
            FalloffCullingField: UE.CullingField;
            FalloffApplyOperatorField: UE.OperatorField;
            NoiseXYOperatorField: UE.OperatorField;
            NoiseZOperatorField: UE.OperatorField;
            NoiseYOperatorField: UE.OperatorField;
            NoiseXOperatorField: UE.OperatorField;
            NoiseZDirectionField: UE.UniformVector;
            NoiseYDirectionField: UE.UniformVector;
            NoiseXDirectionField: UE.UniformVector;
            VectorNoiseField: UE.OperatorField;
            NoiseZField: UE.NoiseField;
            NoiseYField: UE.NoiseField;
            NoiseXField: UE.NoiseField;
            PlaneCullingFalloffField: UE.PlaneFalloff;
            PlaneFalloffField: UE.PlaneFalloff;
            BoxCullingFalloffField: UE.BoxFalloff;
            BoxFalloffField: UE.BoxFalloff;
            RadialCullingFalloffField: UE.RadialFalloff;
            RadialFalloffField: UE.RadialFalloff;
            Box: UE.BoxComponent;
            Sphere: UE.SphereComponent;
            ["Falloff Shape"]: UE.Engine.EditorResources.FieldNodes._Resources.EFieldShapeType.EFieldShapeType;
            ["Falloff Type"]: UE.EFieldFalloffType;
            ["Min Falloff"]: number;
            ["Max Falloff"]: number;
            ["Cull Outside Falloff"]: boolean;
            ["Noise Mode"]: UE.Engine.EditorResources.FieldNodes._Resources.EFieldNoiseCompMode.EFieldNoiseCompMode;
            ["Add Noise Gain"]: number;
            ["Mult Noise Min"]: number;
            ["Mult Noise Max"]: number;
            ["Noise Use Actor Location"]: boolean;
            ["Noise Use Actor Rotation"]: boolean;
            ["Noise Use Actor Scale"]: boolean;
            ["Noise Scale Mult"]: number;
            ["Noise Gain Range"]: UE.Vector2D;
            NoiseLocationInternal: UE.Vector;
            NoiseRotationInternal: UE.Rotator;
            NoiseScaleInternal: UE.Vector;
            NoiseScaleInternalBase: number;
            Debug: boolean;
            DynamicState: UE.EObjectStateTypeEnum;
            ApplyFalloff(FieldIn: $Nullable<UE.FieldNodeBase>, FieldOut: $Ref<UE.FieldNodeBase>) : void;
            ApplyNoise(FieldIn: $Nullable<UE.FieldNodeBase>, FieldOut: $Ref<UE.FieldNodeBase>) : void;
            BoxFalloff(BoxFalloff: $Ref<UE.FieldNodeBase>, BoxCullingFalloff: $Ref<UE.FieldNodeBase>) : void;
            ExecuteUbergraph_FS_BaseField(EntryPoint: number) : void;
            GetCullingFalloffField(CullingFalloffField: $Ref<UE.FieldNodeBase>) : void;
            GetDynamicStateField(DynamicStateField: $Ref<UE.FieldNodeBase>) : void;
            GetFalloffField(FalloffField: $Ref<UE.FieldNodeBase>) : void;
            PlaneFalloff(PlaneFalloff: $Ref<UE.FieldNodeBase>, PlaneCullingFalloff: $Ref<UE.FieldNodeBase>) : void;
            ["Radial Falloff"](RadialFalloff: $Ref<UE.FieldNodeBase>, RadialCullingFalloff: $Ref<UE.FieldNodeBase>) : void;
            /*
             *Event called every frame, if ticking is enabled
             */
            ReceiveTick(DeltaSeconds: number) : void;
            ScalarNoise(ScalarNoiseField: $Ref<UE.FieldNodeBase>) : void;
            /*
             *Construction script, the place to spawn components and do other setup.
             *@note Name used in CreateBlueprint function
             */
            UserConstructionScript() : void;
            VectorNoise(VectorNoiseField: $Ref<UE.FieldNodeBase>) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): FS_BaseField_C;
            static Load(InName: string): FS_BaseField_C;
        
            __tid_FS_BaseField_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: A122EB9F47B2FEB9EA608A92E055872A
    namespace Niagara.Enums.ENiagaraSUbUVAnimationMode {
        enum ENiagaraSUbUVAnimationMode { Linear, Random, ENiagaraSUbUVAnimationMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 5F7436634556A0B1EE1F619CDE0A6257
    namespace Niagara.Enums.ENiagaraSystemInactiveMode {
        enum ENiagaraSystemInactiveMode { "Complete (Let Emitters Finish then Kill The System)", "Kill (System and Emitters Die Immediately)", ENiagaraSystemInactiveMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: B237A81144E7F26DD3D780833E4BD91C
    namespace Niagara.Enums.ENiagaraTorusDistributionMode {
        enum ENiagaraTorusDistributionMode { Random, Direct, ENiagaraTorusDistributionMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: F04C5A284D43654C47165FB14568EA11
    namespace Niagara.Enums.ENiagaraTorusMode {
        enum ENiagaraTorusMode { Torus, TorusKnot, Ring, ENiagaraTorusMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 0EA4428C4BAC7885213E99A9EF8B956B
    namespace Niagara.Enums.ENiagaraTriangleSamplingMode {
        enum ENiagaraTriangleSamplingMode { "Random (All Triangles)", "Random (Sampling Regions)", "Direct (All Triangles)", "Direct (Sampling Regions)", ENiagaraTriangleSamplingMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 2AE883F44C017B8686D56298D47A4829
    namespace Niagara.Enums.ENiagaraVector2_Channels {
        enum ENiagaraVector2_Channels { X, Y, ENiagaraVector2_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 36B8351C4682A8667E219E8C5B6064A5
    namespace Niagara.Enums.ENiagaraVector3_Channels {
        enum ENiagaraVector3_Channels { X, Y, Z, ENiagaraVector3_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: C553B40A490861D61671F1B6A3B787EB
    namespace Engine.EditorResources.FieldNodes._Resources.EFieldSleepType {
        enum EFieldSleepType { Sleep, Disable, Kill, EFieldSleepType_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: D3CF7DA0416B78026A58EB832D06BDB1
    namespace Engine.EditorResources.FieldNodes._Resources.EFieldShapeType {
        enum EFieldShapeType { Box, Sphere, Plane, EFieldShapeType_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: F2BD617342C78011CA9A69B1A9687D07
    namespace Engine.EditorResources.FieldNodes._Resources.EFieldNoiseCompMode {
        enum EFieldNoiseCompMode { Add, Multiply, EFieldNoiseCompMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 01BF5F8342362B75F0C2EFA581CAAFE5
    namespace Engine.EditorResources.FieldNodes._Resources.EFieldForceVel {
        enum EFieldForceVel { "Use Force", "Use Velocity", EFieldForceVel_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 396BC5054C30D9BF120BB89F25CF7CE5
    namespace Engine.EditorResources.FieldNodes._Resources.EFieldActivationType {
        enum EFieldActivationType { Delay, OnTick, OnTickWithDelay, Trigger, EFieldActivationType_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: A954A4C74110E66DDBBF009E19A8F77D
    namespace Niagara.Enums.ENiagaraVector4_Channels {
        enum ENiagaraVector4_Channels { X, Y, Z, W, ENiagaraVector4_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 380BEA80449F69466FE1E3B28CE21A4B
    namespace Niagara.Enums.ENiagaraVertexFilteringMode {
        enum ENiagaraVertexFilteringMode { All, Filtered, ENiagaraVertexFilteringMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 40248BAA47914F89B98FB4824568E748
    namespace Niagara.Enums.ENiagaraVertexSamplingMode {
        enum ENiagaraVertexSamplingMode { "Random (All Vertices)", "Random (Sampling Regions)", "Direct (All Vertices)", "Direct (Sampling Regions)", ENiagaraVertexSamplingMode_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: F7FA2AAE4F5882C8410BBEAE022CD240
    namespace Niagara.Enums.ENiagara_AttributeSamplingApplyOutput {
        enum ENiagara_AttributeSamplingApplyOutput { Apply, Output, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: B868C9EE4A5576BF67304A9C5481E91C
    namespace Niagara.Enums.ENiagara_AudioParamType {
        enum ENiagara_AudioParamType { Volume, Pitch, Location, Rotation, "Boolean Parameter", "Float Parameter", "Integer Parameter", "Paused State", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 8EAA94E34C3D4EB6FA3460B13B98D605
    namespace Niagara.Enums.ENiagara_BankOnTurns {
        enum ENiagara_BankOnTurns { "Add Local Banking Rotation", "Full Orientation Update", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 5838D0BF46287EE9FA1A62B61E24D7F9
    namespace Niagara.Enums.ENiagara_CameraMeshOrientation {
        enum ENiagara_CameraMeshOrientation { "Camera Position", "Camera Plane", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 56795F5848A16CA4B969DBB309CAF90C
    namespace Niagara.Enums.ENiagara_CameraProperties {
        enum ENiagara_CameraProperties { "Camera Position", "Camera Forward Vector", "Camera Up Vector", "Camera Right Vector", "Vector To Camera", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 93D59E024446E047C225C982BBC68529
    namespace Niagara.Enums.ENiagara_CameraVectors {
        enum ENiagara_CameraVectors { "Camera Forward Vector", "Camera Up Vector", "Camera Right Vector", "Vector To Camera", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 72E842554B43E3765FA49882D97F7882
    namespace Niagara.Enums.ENiagara_CollisionType {
        enum ENiagara_CollisionType { "GPU Depth Buffer", "GPU Distance Fields", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 66689FCE4610B3B9505510A71C71F9C7
    namespace Niagara.Enums.ENiagara_ColorInitializationMode {
        enum ENiagara_ColorInitializationMode { Unset, "Direct Set", "Random Range", "Random Hue/Saturation/Value", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: EC906EBE4A2EA65677834B9E4743D403
    namespace Niagara.Enums.ENiagara_ColorInput {
        enum ENiagara_ColorInput { "Particle Color", "Chaos DI Color", "User Color", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 02421E1D405F8CFCDF2A139AA344A05D
    namespace Niagara.Enums.ENiagara_CPUCollisionType {
        enum ENiagara_CPUCollisionType { "Ray Traced", "Analytical Planes", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: D578CA05411619AF2E077285E18C31EA
    namespace Niagara.Enums.ENiagara_DirectReadApplicationMode {
        enum ENiagara_DirectReadApplicationMode { Overwrite, Add, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 8E2137DD4E1B055F5F6ABC9F1CEE66BB
    namespace Niagara.Enums.ENiagara_DirectReadParticleIDSampling {
        enum ENiagara_DirectReadParticleIDSampling { Disabled, "Apply Sampled ID as Ribbon ID", "Output Only", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: B919D84A4D4252F6DDDDD7BF1E940632
    namespace Niagara.Enums.ENiagara_DirectReadSamplingMode {
        enum ENiagara_DirectReadSamplingMode { Disabled, "Apply to Attribute", "Output Only", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 75CBA01B44C293495B39C2BC62D41E1D
    namespace Niagara.Enums.ENiagara_EmitterLocSamplingMode {
        enum ENiagara_EmitterLocSamplingMode { Random, Sequential, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ED8A135A4A2CB69F867C22AA408E785D
    namespace Niagara.Enums.ENiagara_EmitterStateOptions {
        enum ENiagara_EmitterStateOptions { Infinite, Once, Multiple, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 791DD50D4505017EF8C051A6B8B563F2
    namespace Niagara.Enums.ENiagara_FadeOperationType {
        enum ENiagara_FadeOperationType { Linear, Percentage, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 0B7CEF0A40C43D5180ADD9B5D4D00BC4
    namespace Niagara.Enums.ENiagara_Float4Channel {
        enum ENiagara_Float4Channel { R, G, B, A, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 7DDC0C6B4A24A8FBF853C39F7390149A
    namespace Niagara.Enums.ENiagara_GPUCollisionType {
        enum ENiagara_GPUCollisionType { "GPU Depth Buffer", "GPU Distance Fields", "GPU Ray Traces (Experimental)", "Analytical Planes", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 75A4FCA54B427A97913666993FDAE56D
    namespace Niagara.Enums.ENiagara_IDAttributes {
        enum ENiagara_IDAttributes { "Particles.UniqueID", "Particles.ID Index", "Particles.ID Acquire Tag", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: F99D4EF54180D43A335EA2BA7FE715C9
    namespace Niagara.Enums.ENiagara_InfiniteLoopDuration {
        enum ENiagara_InfiniteLoopDuration { Fixed, Infinite, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 8854B24240237871D0E1708E7BC0964A
    namespace Niagara.Enums.ENiagara_LifetimeInheritanceOptions {
        enum ENiagara_LifetimeInheritanceOptions { Min, Max, Overwrite, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 5EFA0D4449814A6878CF208040294840
    namespace Niagara.Enums.ENiagara_LifetimeMode {
        enum ENiagara_LifetimeMode { "Direct Set", Random, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 28AED7624FD35346A9AD9D9A60FBAA92
    namespace Niagara.Enums.ENiagara_MassInitializationMode {
        enum ENiagara_MassInitializationMode { "Unset / (Mass of 1)", "Direct Set", Random, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 6B311EC44A8BB966E82910A1546C63DA
    namespace Niagara.Enums.ENiagara_MultipleLerpCount {
        enum ENiagara_MultipleLerpCount { ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: BC6181B5448056DB486F5EB06B88C3DB
    namespace Niagara.Enums.ENiagara_PositionInitializationMode {
        enum ENiagara_PositionInitializationMode { Unset, "Direct Set", "Simulation Position", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 62984E2B436A4FF8F39A33BCFFE27635
    namespace Niagara.Enums.ENiagara_PositionInput {
        enum ENiagara_PositionInput { "Chaos DI Position", "User Position", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: DDB4EB54414C2EA54A1872AC28BB9696
    namespace Niagara.Enums.ENiagara_RotationDefinitionApproach {
        enum ENiagara_RotationDefinitionApproach { Euler, Quaternion, "Axis Angle ", "Basis Vectors", Matrix, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: C69F29F846BC7D3401C7A49983D11D00
    namespace Niagara.Enums.ENiagara_SizeScaleMode {
        enum ENiagara_SizeScaleMode { Unset, Uniform, "Random Uniform", "Non-Uniform", "Random Non-Uniform", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: EA5A50874889F2512A50448EDA08AA89
    namespace Niagara.Enums.ENiagara_SpawnBurstMode {
        enum ENiagara_SpawnBurstMode { Timed, Manual, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: A80064B440721C76444762B05503B2CF
    namespace Niagara.Enums.ENiagara_SpriteRotationMode {
        enum ENiagara_SpriteRotationMode { Unset, Random, "Direct Angle (Degrees)", "Direct Normalized Angle (0-1)", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 30A11E8E45501137D1C973BDEEF301B1
    namespace Niagara.Enums.ENiagara_SubUVLookupMode {
        enum ENiagara_SubUVLookupMode { Linear, Curve, Random, Infinite, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 7C1D99FE4EDCD40ADEB798831D4E24E6
    namespace Niagara.Enums.ENiagara_SubUVLookupModeV2 {
        enum ENiagara_SubUVLookupModeV2 { Linear, Curve, Random, "Infinite Loop", "Direct Index", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: A052419B49F3A3A241F8E98F9300956F
    namespace Niagara.Enums.ENiagara_TransformBaseOptions {
        enum ENiagara_TransformBaseOptions { "Transform Vector", "Transform Position", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 57E4041647860988F6D52581FAE993C7
    namespace Niagara.Enums.ENiagara_TransformMode {
        enum ENiagara_TransformMode { Manual, Matrix, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 2933F5D2459500FDB85E0B838C683ADB
    namespace Niagara.Enums.ENiagara_TransformOrientationMode {
        enum ENiagara_TransformOrientationMode { "Yaw/Pitch/Roll", Quaternion, Matrix, "Basis Vectors", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: E8368C344D80EE8DF0C59B80DA5E9380
    namespace Niagara.Enums.ENiagara_UVFlippingMode {
        enum ENiagara_UVFlippingMode { Unset, "Random X", "Random Y", "Random X / Y", Custom, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: CCE8047C438ECA2F75979886C1E6A9C0
    namespace Niagara.Enums.ENiagara_VelocityInput {
        enum ENiagara_VelocityInput { "Chaos DI Velocity", "User Velocity", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 427B7052435624DA0928ECBBF10D5244
    namespace Niagara.Enums.ENiagara_WaterInteractionStruct {
        class ENiagara_WaterInteractionStruct {
            constructor();
            constructor(Intersects: boolean, IntersectionCentroid: UE.Vector, IntersectionXBasisVector: UE.Vector, IntersectionYBasisVector: UE.Vector, IntersectionZBasisVector: UE.Vector, IntersectionXSize: number, IntersectionYSize: number, OcclusionDelta: number, Occludedvolume: number, FullVolume: number, VolumeXbasis: UE.Vector, VolumeYbasis: UE.Vector, VolumeZbasis: UE.Vector, VolumeLength: number, VolumeRadius: number, VolumeCentroid: UE.Vector, BoneVelocity: UE.Vector, KineticEnergy: number, Mass: number);
            Intersects: boolean;
            IntersectionCentroid: UE.Vector;
            IntersectionXBasisVector: UE.Vector;
            IntersectionYBasisVector: UE.Vector;
            ["Intersection Z BasisVector"]: UE.Vector;
            ["Intersection X Size"]: number;
            ["Intersection Y Size"]: number;
            ["Occlusion Delta"]: number;
            ["Occluded volume"]: number;
            ["Full Volume"]: number;
            ["Volume X basis"]: UE.Vector;
            ["Volume Y basis"]: UE.Vector;
            ["Volume Z basis"]: UE.Vector;
            ["Volume Length"]: number;
            ["Volume Radius"]: number;
            ["Volume Centroid"]: UE.Vector;
            ["Bone Velocity"]: UE.Vector;
            ["Kinetic Energy"]: number;
            Mass: number;
            /**
             * @deprecated use StaticStruct instead.
             */
            static StaticClass(): ScriptStruct;
            static StaticStruct(): ScriptStruct;
            __tid_ENiagara_WaterInteractionStruct_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 9B3EEEFD482607267F326F8876312E69
    namespace Niagara.Enums.ENiagara_WaveformBlendMode {
        enum ENiagara_WaveformBlendMode { Add, Subtract, Multiply, Max, Min, Interpolate, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: E7474EB24169F1C153FF8A958C44A9CF
    namespace Niagara.Enums.ENiagara_WaveformCount {
        enum ENiagara_WaveformCount { "[1] One", "[2] Two", "[3] Three", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 7354821F4708C16B44947696771530A5
    namespace Niagara.Enums.ENiagara_Waveforms {
        enum ENiagara_Waveforms { Sine, Cosine, "Compound Sin/Cos", Pendulum, Square, Pulse, Triangle, Sawtooth, Random, "Random Blend", "Random Spline", "Random Spline Smooth", "Random Spline Segmented", ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: CACD28FD4FA39F4175D65D8DDA31BE63
    namespace Niagara.Enums.ENiagara_WrapClamp {
        enum ENiagara_WrapClamp { Clamp, Wrap, ENiagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: D0F093C341CAED1C97D778B45FAE02A2
    namespace Niagara.Enums.Niagara_Units {
        enum Niagara_Units { Centimeters, Meters, Kilometers, Niagara_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: E2DDB93747635D2AAA1BFEAB993FF557
    namespace Niagara.DefaultAssets.Structs.CollisionEvent {
        class CollisionEvent {
            constructor();
            constructor(Vector1_Position_: UE.Vector, Vector2_Velocity_: UE.Vector, Vector3_CollisionNormal_: UE.Vector, Vector4_IncomingVelocity_: UE.Vector, NiagaraID_ParticleID_: UE.NiagaraID, Float1_NormalizedAge_: number, Float2_RandomNormalizedFloat_: number, Integer_NumberofCollisions_: number, LinearColor_ParticleColor_: UE.LinearColor, Boolean_LocalSpace_: boolean);
            ["Vector 1 (Position)"]: UE.Vector;
            ["Vector 2 (Velocity)"]: UE.Vector;
            ["Vector 3 (Collision Normal)"]: UE.Vector;
            ["Vector 4 (Incoming Velocity)"]: UE.Vector;
            ["NiagaraID (ParticleID)"]: UE.NiagaraID;
            ["Float 1 (NormalizedAge)"]: number;
            ["Float 2 (RandomNormalizedFloat)"]: number;
            ["Integer (Number of Collisions)"]: number;
            ["Linear Color (Particle Color)"]: UE.LinearColor;
            ["Boolean (Local Space)"]: boolean;
            /**
             * @deprecated use StaticStruct instead.
             */
            static StaticClass(): ScriptStruct;
            static StaticStruct(): ScriptStruct;
            __tid_CollisionEvent_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 178A74C342867565215B369983D94E01
    namespace Niagara.DefaultAssets.Structs.LocationEvent {
        class LocationEvent {
            constructor();
            constructor(Position: UE.Vector, Velocity: UE.Vector, Acceleration: UE.Vector, RibbonID: UE.NiagaraID, NormalizedAge: number, RandomNormalizedFloat: number);
            Position: UE.Vector;
            Velocity: UE.Vector;
            Acceleration: UE.Vector;
            RibbonID: UE.NiagaraID;
            NormalizedAge: number;
            RandomNormalizedFloat: number;
            /**
             * @deprecated use StaticStruct instead.
             */
            static StaticClass(): ScriptStruct;
            static StaticStruct(): ScriptStruct;
            __tid_LocationEvent_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 2C2122C042DB12F8E368419DB0398117
    namespace Niagara.DefaultAssets.Structs.LocationEvent_V2 {
        class LocationEvent_V2 {
            constructor();
            constructor(Vector1_Position_: UE.Vector, Vector2_Velocity_: UE.Vector, Vector3_Acceleration_: UE.Vector, NiagaraID_ParticleID_: UE.NiagaraID, Float1_NormalizedAge_: number, Float2_RandomNormalizedFloat_: number, Float3_DistanceTraveled_: number, LinearColor_ParticleColor_: UE.LinearColor, Boolean_LocalSpace_: boolean);
            ["Vector 1 (Position)"]: UE.Vector;
            ["Vector 2 (Velocity)"]: UE.Vector;
            ["Vector 3 (Acceleration)"]: UE.Vector;
            ["NiagaraID (ParticleID)"]: UE.NiagaraID;
            ["Float 1 (NormalizedAge)"]: number;
            ["Float 2 (RandomNormalizedFloat)"]: number;
            ["Float 3 (DistanceTraveled)"]: number;
            ["Linear Color (Particle Color)"]: UE.LinearColor;
            ["Boolean (Local Space)"]: boolean;
            /**
             * @deprecated use StaticStruct instead.
             */
            static StaticClass(): ScriptStruct;
            static StaticStruct(): ScriptStruct;
            __tid_LocationEvent_V2_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: E1A8FB3549BE8C569C2EC7BC4E843409
    namespace Niagara.Blueprints.NiagaraPreview {
        class NiagaraPreview_C extends UE.NiagaraPreviewBase {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            YLabel: UE.TextRenderComponent;
            XLabel: UE.TextRenderComponent;
            TextBoard: UE.StaticMeshComponent;
            Effect: UE.NiagaraComponent;
            Plinth: UE.StaticMeshComponent;
            Scene: UE.SceneComponent;
            NewVar_0: UE.TextRenderComponent;
            ExecuteUbergraph_NiagaraPreview(EntryPoint: number) : void;
            /*
             *Event when play begins for this actor.
             */
            ReceiveBeginPlay() : void;
            SetLabelText(InXAxisText: string, InYAxisText: string) : void;
            /*
             *AActor Interface End
             */
            SetSystem(InSystem: $Nullable<UE.NiagaraSystem>) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): NiagaraPreview_C;
            static Load(InName: string): NiagaraPreview_C;
        
            __tid_NiagaraPreview_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: F9914210490E7C9D85681A992BA454D4
    namespace Niagara.Blueprints.NiagaraPreviewAxisLODDistance {
        class NiagaraPreviewAxisLODDistance_C extends UE.NiagaraPreviewAxis {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            Distances: TArray<number>;
            bApplyRealDistances: boolean;
            /*
             *Applies this axis for the preview at PreviewIndex on this axis.
             */
            ApplyToPreview(PreviewComponent: $Nullable<UE.NiagaraComponent>, PreviewIndex: number, bIsXAxis: boolean, OutLabelText: $Ref<string>) : void;
            ExecuteUbergraph_NiagaraPreviewAxisLODDistance(EntryPoint: number) : void;
            /*
             *Returns the number of previews for this axis.
             */
            Num() : number;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): NiagaraPreviewAxisLODDistance_C;
            static Load(InName: string): NiagaraPreviewAxisLODDistance_C;
        
            __tid_NiagaraPreviewAxisLODDistance_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 1937CC8940AA88529DE8E685ED4ADDBF
    namespace DatasmithContent.Materials.StdDecal.BP_DecalTestPOM {
        class BP_DecalTestPOM_C extends UE.Actor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            Decal: UE.DecalComponent;
            DefaultSceneRoot: UE.SceneComponent;
            PreviousRotation: UE.Rotator;
            Decal_MD: UE.MaterialInstanceDynamic;
            DecalMaterialInstance: UE.MaterialInstance;
            AssignNewDecalMaterial() : void;
            ExecuteUbergraph_BP_DecalTestPOM(EntryPoint: number) : void;
            /*
             *Event when play begins for this actor.
             */
            ReceiveBeginPlay() : void;
            UpdateDynamicDecalMaterial(Force: boolean) : void;
            /*
             *Construction script, the place to spawn components and do other setup.
             *@note Name used in CreateBlueprint function
             */
            UserConstructionScript() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_DecalTestPOM_C;
            static Load(InName: string): BP_DecalTestPOM_C;
        
            __tid_BP_DecalTestPOM_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ECB22C2849155502668402A846E80610
    namespace DatasmithContent.Datasmith.AreaLightsStruct {
        class AreaLightsStruct {
            constructor();
            constructor(Mesh: UE.StaticMesh);
            Mesh: UE.StaticMesh;
            /**
             * @deprecated use StaticStruct instead.
             */
            static StaticClass(): ScriptStruct;
            static StaticStruct(): ScriptStruct;
            __tid_AreaLightsStruct_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 6402C85B47DCBD500C7B78ADE766EAE9
    namespace DatasmithContent.Datasmith.DatasmithActor {
        class DatasmithActor_C extends UE.Actor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            SceneRoot: UE.SceneComponent;
            /*
             *Construction script, the place to spawn components and do other setup.
             *@note Name used in CreateBlueprint function
             */
            UserConstructionScript() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): DatasmithActor_C;
            static Load(InName: string): DatasmithActor_C;
        
            __tid_DatasmithActor_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: A8D10CA24886AAFD40C09B9F2196D48B
    namespace DatasmithContent.Datasmith.DatasmithAreaLight {
        class DatasmithAreaLight_C extends UE.DatasmithAreaLightActor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            DefaultSceneRoot: UE.SceneComponent;
            IndirectIntensity: number;
            VolumetricScatteringIntensity: number;
            SpecularScale: number;
            ShadowBias: number;
            ["Cast Shadows"]: boolean;
            LightColor(Intensity: number, Color: UE.LinearColor, Emissive: $Ref<UE.LinearColor>) : void;
            /*
             *Construction script, the place to spawn components and do other setup.
             *@note Name used in CreateBlueprint function
             */
            UserConstructionScript() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): DatasmithAreaLight_C;
            static Load(InName: string): DatasmithAreaLight_C;
        
            __tid_DatasmithAreaLight_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 909EFB8B4EC4DC44EDCB759F2BC01276
    namespace DatasmithContent.Datasmith.DatasmithArealightMesh {
        class DatasmithAreaLightMesh_C extends UE.DatasmithAreaLightActor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            DefaultSceneRoot: UE.SceneComponent;
            NewVar_0: TArray<string>;
            LightColor(Intensity: number, Color: UE.LinearColor, Emissive: $Ref<UE.LinearColor>) : void;
            /*
             *Construction script, the place to spawn components and do other setup.
             *@note Name used in CreateBlueprint function
             */
            UserConstructionScript() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): DatasmithAreaLightMesh_C;
            static Load(InName: string): DatasmithAreaLightMesh_C;
        
            __tid_DatasmithAreaLightMesh_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 0878317841C0166B58BBFBB9EFA36CD8
    namespace DatasmithContent.Datasmith.DatasmithLayer {
        class DatasmithLayer_C extends UE.SceneComponent {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            EnableHierarchy: boolean;
            ExecuteUbergraph_DatasmithLayer(EntryPoint: number) : void;
            /*
             *Event called every frame if tick is enabled
             */
            ReceiveTick(DeltaSeconds: number) : void;
            UpdateChildStaticMeshVisibility(Enable: boolean, StaticMesh: $Nullable<UE.StaticMeshComponent>) : void;
            UpdateHierarchy(Enable: boolean) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): DatasmithLayer_C;
            static Load(InName: string): DatasmithLayer_C;
        
            __tid_DatasmithLayer_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 977B97E54653E3AF70B5268FE017C0CF
    namespace DatasmithContent.Datasmith.DatasmithSelector {
        class DatasmithSelector_C extends UE.DatasmithContent.Datasmith.DatasmithLayer.DatasmithLayer_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            SelectedId: number;
            ExecuteUbergraph_DatasmithSelector(EntryPoint: number) : void;
            UpdateHierarchy(Enable: boolean) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): DatasmithSelector_C;
            static Load(InName: string): DatasmithSelector_C;
        
            __tid_DatasmithSelector_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: C4ADE31B4472D8F44F1F60873DCA4F8B
    namespace DatasmithContent.Blueprints.FBXImporter.UI.AnimationSampleUI {
        class AnimationSampleUI_C extends UE.EditorUtilityWidget {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            AnimationButtonsHorizontalBox: UE.HorizontalBox;
            AnimationClipHorizontalBox: UE.HorizontalBox;
            AnimationPlayerHorizontalBox: UE.HorizontalBox;
            AnimClipCombobox: UE.ComboBoxString;
            AnimPlayButton: UE.Button;
            AnimPlayerCombobox: UE.ComboBoxString;
            AnimResetButton: UE.Button;
            ImportedSequencesHelpersNamesToObj: TMap<string, UE.DatasmithContent.Blueprints.FBXImporter.Animation.ImportedSequencesHelper.ImportedSequencesHelper_C>;
            SelectedImportedSequencesHelper: UE.DatasmithContent.Blueprints.FBXImporter.Animation.ImportedSequencesHelper.ImportedSequencesHelper_C;
            SpawnedLevelSequenceActor: UE.LevelSequenceActor;
            SelectedSequence: UE.LevelSequence;
            BndEvt__AnimClipCombobox_K2Node_ComponentBoundEvent_0_OnSelectionChangedEvent__DelegateSignature(SelectedItem: string, SelectionType: UE.ESelectInfo) : void;
            BndEvt__AnimPlayButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature() : void;
            BndEvt__AnimPlayerCombobox_K2Node_ComponentBoundEvent_0_OnSelectionChangedEvent__DelegateSignature(SelectedItem: string, SelectionType: UE.ESelectInfo) : void;
            BndEvt__AnimResetButton_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature() : void;
            /*
             *Called after the underlying slate widget is constructed.  Depending on how the slate object is used
             *this event may be called multiple times due to adding and removing from the hierarchy.
             *If you need a true called-once-when-created event, use OnInitialized.
             */
            Construct() : void;
            ExecuteUbergraph_AnimationSampleUI(EntryPoint: number) : void;
            /*
             *Returns the LevelSequenceActor for the scene. Will spawn a new one if needed. Note: This requires SelectedImportedSequencesHelper to be valid and have at least one LevelSequence
             */
            GetLevelSequenceActor(Actor: $Ref<UE.LevelSequenceActor>) : void;
            /*
             *Resets the playback position to start. Taking advantage of the fact that we set all our LevelSequences to CompletionMode 'KeepState', this will actually scrub back from the end to frame zero, properly resettting all actors.
             */
            RewindAnimationToStart(Player: $Nullable<UE.LevelSequencePlayer>) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): AnimationSampleUI_C;
            static Load(InName: string): AnimationSampleUI_C;
        
            __tid_AnimationSampleUI_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 600BED6747DF6A75AF99DD963DC99E83
    namespace DatasmithContent.Blueprints.FBXImporter.Animation.ImportedSequencesHelper {
        class ImportedSequencesHelper_C extends UE.Actor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            DefaultSceneRoot: UE.SceneComponent;
            ImportedSequences: TArray<UE.LevelSequence>;
            SampleUIClass: UE.Class;
            SceneAsset: UE.Object;
            /*
             *Add a sample UI that can be used to play imported level sequences
             */
            AddAnimationSampleUI() : void;
            /*
             *Remove the sample UI
             */
            RemoveAnimationSampleUI() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ImportedSequencesHelper_C;
            static Load(InName: string): ImportedSequencesHelper_C;
        
            __tid_ImportedSequencesHelper_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 93172B2843B7B0228C82CA9BB29E356D
    namespace ControlRigSpline.SplineFunctionLibrary.SplineFunctionLibrary {
        class SplineFunctionLibrary_C extends UE.ControlRig {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): SplineFunctionLibrary_C;
            static Load(InName: string): SplineFunctionLibrary_C;
        
            __tid_SplineFunctionLibrary_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 93172B2843B7B0228C82CA9BB29E356D
    namespace ControlRigSpline.SplineFunctionLibrary.SplineFunctionLibrary {
        class RigVMMemory_Literal extends UE.RigVMMemoryStorage {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            LocalVariableDefault__SplineIK_aim_transforms__Const: TArray<UE.Vector>;
            LocalVariableDefault__SplineIK_offset_positions__Const: TArray<UE.Vector>;
            LocalVariableDefault__SplineIK_local_spline__Const: UE.ControlRigSpline;
            LocalVariableDefault__SplineIK_template_spline__Const: UE.ControlRigSpline;
            LocalVariableDefault__SplineIK_template_transforms__Const: TArray<UE.Transform>;
            FunctionLibrary___SplineIK_MathIntLess_B__Const: number;
            FunctionLibrary___SplineIK_GetTransformItemArray_Space__Const: UE.ERigVMTransformSpace;
            FunctionLibrary___SplineIK_GetTransformItemArray_bInitial__Const: boolean;
            FunctionLibrary___SplineIK_ControlRigSplineFromPoints_1_Compression__Const: number;
            FunctionLibrary___SplineIK_FitChainToSplineCurveItemArray_1_Alignment__Const: UE.EControlRigCurveAlignment;
            FunctionLibrary___SplineIK_FitChainToSplineCurveItemArray_1_Maximum__Const: number;
            FunctionLibrary___SplineIK_FitChainToSplineCurveItemArray_1_SamplingPrecision__Const: number;
            FunctionLibrary___SplineIK_FitChainToSplineCurveItemArray_1_SecondaryAxis__Const: UE.Vector;
            FunctionLibrary___SplineIK_FitChainToSplineCurveItemArray_1_Rotations__Const: TArray<UE.RigUnit_FitChainToCurve_Rotation>;
            FunctionLibrary___SplineIK_FitChainToSplineCurveItemArray_1_RotationEaseType__Const: UE.ERigVMAnimEasingType;
            FunctionLibrary___SplineIK_FitChainToSplineCurveItemArray_1_bPropagateToChildren__Const: boolean;
            FunctionLibrary___SplineIK_FitChainToSplineCurveItemArray_1_DebugSettings__Const: UE.RigUnit_FitChainToCurve_DebugSettings;
            FunctionLibrary___SplineIK_FitChainToSplineCurveItemArray_Alignment__Const: UE.EControlRigCurveAlignment;
            FunctionLibrary___SplineIK_FitChainToSplineCurveItemArray_RotationEaseType__Const: UE.ERigVMAnimEasingType;
            FunctionLibrary___SplineIK_DrawControlRigSpline_1_Color__Const: UE.LinearColor;
            FunctionLibrary___SplineIK_DrawControlRigSpline_1_Detail__Const: number;
            FunctionLibrary___SplineIK_AimBoneMath_Primary__Const: UE.RigUnit_AimItem_Target;
            FunctionLibrary___SplineIK_AimBoneMath_Secondary__Const: UE.RigUnit_AimItem_Target;
            FunctionLibrary___SplineIK_AimBoneMath_DebugSettings__Const: UE.RigUnit_AimBone_DebugSettings;
            FunctionLibrary___SplineIK_MathIntSub_B__Const: number;
            FunctionLibrary___SplineIK_DebugTransformMutableItemSpace_2_Mode__Const: UE.ERigUnitDebugTransformMode;
            FunctionLibrary___SplineIK_DebugTransformMutableItemSpace_2_Thickness__Const: number;
            FunctionLibrary___SplineIK_DebugTransformMutableItemSpace_2_Scale__Const: number;
            FunctionLibrary___SplineIK_DebugTransformMutableItemSpace_2_Space__Const: UE.RigElementKey;
            FunctionLibrary___SplineIK_DebugTransformMutableItemSpace_2_WorldOffset__Const: UE.Transform;
            FunctionLibrary___SplineIK_ArrayGetAtIndex_2_Index__Const: number;
            FunctionLibrary___SplineIK_ParentConstraint_Filter__Const: UE.TransformFilter;
            FunctionLibrary___SplineIK_ParentConstraint_Parents__Const: TArray<UE.ConstraintParent>;
            FunctionLibrary___SplineIK_ParentConstraint_AdvancedSettings__Const: UE.RigUnit_ParentConstraint_AdvancedSettings;
            FunctionLibrary___SplineIK_ParentConstraint_1_Filter__Const: UE.TransformFilter;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): RigVMMemory_Literal;
            static Load(InName: string): RigVMMemory_Literal;
        
            __tid_RigVMMemory_Literal_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 93172B2843B7B0228C82CA9BB29E356D
    namespace ControlRigSpline.SplineFunctionLibrary.SplineFunctionLibrary {
        class RigVMMemory_Work extends UE.RigVMMemoryStorage {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            FunctionLibrary___SplineIK_Entry_Controls: TArray<UE.RigElementKey>;
            FunctionLibrary___SplineIK_Entry_Bones: TArray<UE.RigElementKey>;
            FunctionLibrary___SplineIK_Entry_debug: boolean;
            FunctionLibrary___SplineIK_Entry_Stretch: boolean;
            FunctionLibrary___SplineIK_Return_Output_Spline: UE.ControlRigSpline;
            FunctionLibrary___SplineIK_Entry_Primary_Axis: UE.Vector;
            FunctionLibrary___SplineIK_Entry_Up_Axis: UE.Vector;
            FunctionLibrary___SplineIK_Entry_Secondary_Spline_Direction: UE.Vector;
            FunctionLibrary___SplineIK_Entry_Spline_Mode: UE.ESplineType;
            FunctionLibrary___SplineIK_Entry_Samples_Per_Segment: number;
            FunctionLibrary___SplineIK_MathIntLess_Result: boolean;
            FunctionLibrary___SplineIK_ArrayGetNum_Num: number;
            FunctionLibrary___SplineIK_ControlRigSplineFromPoints_1_Spline: UE.ControlRigSpline;
            FunctionLibrary___SplineIK_RigVMFunction_MathTransformArrayToSRT_Translations: TArray<UE.Vector>;
            FunctionLibrary___SplineIK_GetTransformItemArray_Transforms: TArray<UE.Transform>;
            FunctionLibrary___SplineIK_GetTransformItemArray_CachedIndex: TArray<TArray<UE.CachedRigElement>>;
            FunctionLibrary___SplineIK_RigVMFunction_MathTransformArrayToSRT_Rotations: TArray<UE.Quat>;
            FunctionLibrary___SplineIK_RigVMFunction_MathTransformArrayToSRT_Scales: TArray<UE.Vector>;
            LocalVariable__SplineIK_template_spline: UE.ControlRigSpline;
            LocalVariable__SplineIK_template_transforms: TArray<UE.Transform>;
            LocalVariable__SplineIK_offset_positions: TArray<UE.Vector>;
            FunctionLibrary___SplineIK_DISPATCH_RigVMDispatch_ArrayGetNum_1_Num: number;
            FunctionLibrary___SplineIK_ArrayIterator_3_Index: number;
            FunctionLibrary___SplineIK_MathTransformTransformVector_1_Result: UE.Vector;
            FunctionLibrary___SplineIK_ArrayIterator_3_Element: UE.Transform;
            FunctionLibrary___SplineIK_ArrayIterator_3_Count: number;
            FunctionLibrary___SplineIK_ArrayIterator_3_Ratio: number;
            FunctionLibrary___SplineIK_ArrayIterator_3_BlockToRun: string;
            FunctionLibrary___SplineIK_FitChainToSplineCurveItemArray_1_WorkData: TArray<UE.RigUnit_FitChainToCurve_WorkData>;
            FunctionLibrary___SplineIK_FitChainToSplineCurveItemArray_WorkData: TArray<UE.RigUnit_FitChainToCurve_WorkData>;
            FunctionLibrary___SplineIK_Branch_RigVMUnitNode_BlockToRun: string;
            FunctionLibrary___SplineIK_ControlRigSplineFromPoints_Spline: UE.ControlRigSpline;
            FunctionLibrary___SplineIK_BranchNode_2_RigVMUnitNode_BlockToRun: string;
            LocalVariable__SplineIK_aim_transforms: TArray<UE.Vector>;
            FunctionLibrary___SplineIK_DISPATCH_RigVMDispatch_ArrayGetNum_Num: number;
            FunctionLibrary___SplineIK_ArrayIterator_1_Index: number;
            FunctionLibrary___SplineIK_PositionFromControlRigSpline_Position: UE.Vector;
            FunctionLibrary___SplineIK_ClosestParameterFromControlRigSpline_U: number;
            FunctionLibrary___SplineIK_GetTransform_Transform: UE.Transform;
            FunctionLibrary___SplineIK_ArrayIterator_1_Element: UE.RigElementKey;
            FunctionLibrary___SplineIK_GetTransform_CachedIndex: TArray<UE.CachedRigElement>;
            FunctionLibrary___SplineIK_ClosestParameterFromControlRigSpline_Position: UE.Vector;
            FunctionLibrary___SplineIK_ArrayIterator_1_Count: number;
            FunctionLibrary___SplineIK_ArrayIterator_1_Ratio: number;
            FunctionLibrary___SplineIK_ArrayIterator_1_BlockToRun: string;
            FunctionLibrary___SplineIK_AimBoneMath_Result: UE.Transform;
            FunctionLibrary___SplineIK_GetTransform_1_Transform: UE.Transform;
            FunctionLibrary___SplineIK_ArrayIterator_2_Element: UE.RigElementKey;
            FunctionLibrary___SplineIK_GetTransform_1_CachedIndex: TArray<UE.CachedRigElement>;
            FunctionLibrary___SplineIK_DISPATCH_RigVMDispatch_ArrayGetAtIndex_Element: UE.Vector;
            FunctionLibrary___SplineIK_ArrayIterator_2_Index: number;
            FunctionLibrary___SplineIK_AimBoneMath_Primary__IO: UE.RigUnit_AimItem_Target;
            FunctionLibrary___SplineIK_AimBoneMath_PrimaryCachedSpace: TArray<UE.CachedRigElement>;
            FunctionLibrary___SplineIK_AimBoneMath_SecondaryCachedSpace: TArray<UE.CachedRigElement>;
            FunctionLibrary___SplineIK_AimBoneMath_bIsInitialized: TArray<boolean>;
            FunctionLibrary___SplineIK_MathIntEquals_Result: boolean;
            FunctionLibrary___SplineIK_MathIntSub_Result: number;
            FunctionLibrary___SplineIK_ArrayIterator_2_Count: number;
            FunctionLibrary___SplineIK_SetTransform_CachedIndex: TArray<UE.CachedRigElement>;
            FunctionLibrary___SplineIK_BranchNode_3_RigVMUnitNode_BlockToRun: string;
            FunctionLibrary___SplineIK_ArrayIterator_2_Ratio: number;
            FunctionLibrary___SplineIK_ArrayIterator_2_BlockToRun: string;
            FunctionLibrary___SplineIK_ArrayGetAtIndex_2_Element: UE.RigElementKey;
            FunctionLibrary___SplineIK_ArrayGetAtIndex_1_Element: UE.RigElementKey;
            FunctionLibrary___SplineIK_ParentConstraint_Parents__IO: TArray<UE.ConstraintParent>;
            FunctionLibrary___SplineIK_ParentConstraint_ChildCache: TArray<UE.CachedRigElement>;
            FunctionLibrary___SplineIK_ParentConstraint_ParentCaches: TArray<TArray<UE.CachedRigElement>>;
            FunctionLibrary___SplineIK_ParentConstraint_1_Parents__IO: TArray<UE.ConstraintParent>;
            FunctionLibrary___SplineIK_ParentConstraint_1_ChildCache: TArray<UE.CachedRigElement>;
            FunctionLibrary___SplineIK_ParentConstraint_1_ParentCaches: TArray<TArray<UE.CachedRigElement>>;
            FunctionLibrary___SplineIK_Branch_1_RigVMUnitNode_BlockToRun: string;
            FunctionLibrary___SplineIK_BranchNode_4_RigVMUnitNode_BlockToRun: string;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): RigVMMemory_Work;
            static Load(InName: string): RigVMMemory_Work;
        
            __tid_RigVMMemory_Work_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: CD50DF0B46C623A86A9CF4824E6316CC
    namespace ControlRigModules.Modules.AddControl {
        class AddControl_C extends UE.ControlRig {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            ["Module Settings"]: UE.ControlRigModules.Modules.ModuleSettings.ModuleSettings;
            ["Control Name"]: string;
            ["Control Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            ["Secondary Control Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            ["Control Suffix"]: string;
            ["Null Suffix"]: string;
            ["Add Null Above"]: boolean;
            ["Add Null Below"]: boolean;
            ["Add Secondary Control"]: boolean;
            ["Attach to Skeleton"]: boolean;
            ["Orient to World"]: boolean;
            the_control: UE.RigElementKey;
            ["Parent Control"]: UE.RigElementKey;
            ["Offset Control"]: UE.Transform;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): AddControl_C;
            static Load(InName: string): AddControl_C;
        
            __tid_AddControl_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 6A3DB53F47E3C355FDDD12A704388332
    namespace ControlRigModules.Modules.Arm {
        class Arm_C extends UE.ControlRig {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            ["Module Settings"]: UE.ControlRigModules.Modules.ModuleSettings.ModuleSettings;
            ["IK Shape Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            ["PV Shape Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            ["FK Shape Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            ["Auto Determine Axis"]: boolean;
            ["Primary Axis"]: UE.Vector;
            ["Secondary Axis"]: UE.Vector;
            ["Orient IK to World"]: boolean;
            ["Offset IK Ctrl"]: UE.Transform;
            ["FK IK Default"]: boolean;
            ["Local Default"]: boolean;
            ["PV Offset Factor"]: number;
            pv_control: UE.RigElementKey;
            foot_control: UE.RigElementKey;
            follow_null: UE.RigElementKey;
            ["Finger Leaf Bones"]: TArray<UE.RigElementKey>;
            ["Shoulder Bone"]: UE.RigElementKey;
            ["Hand Bone"]: UE.RigElementKey;
            ["Elbow Bone"]: UE.RigElementKey;
            prefix: string;
            Array: TArray<UE.RigElementKey>;
            Side: string;
            ["Use Legacy PV"]: boolean;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Arm_C;
            static Load(InName: string): Arm_C;
        
            __tid_Arm_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 52A54A084958BBD47AF1EB9E0BD1A947
    namespace ControlRigModules.Modules.Chain {
        class Chain_C extends UE.ControlRig {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            ["Module Settings"]: UE.ControlRigModules.Modules.ModuleSettings.ModuleSettings;
            Debug: boolean;
            ["Control Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            ["Add Null"]: boolean;
            ["Create Control per Bone"]: boolean;
            ["Solve with SplineIK"]: boolean;
            Stretch: boolean;
            ["Spline Mode"]: UE.ESplineType;
            ["Primary Axis"]: UE.Vector;
            ["Up Axis"]: UE.Vector;
            ["Secondary Spline Direction"]: UE.Vector;
            ["Number of Controls"]: number;
            Prefix: string;
            Name: string;
            Suffix: string;
            Dynamics: boolean;
            ["Default Strength"]: number;
            ["Default Damping"]: number;
            ["Default Blend Start"]: number;
            ["Default Blend End"]: number;
            ["Default Blend Twist"]: number;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Chain_C;
            static Load(InName: string): Chain_C;
        
            __tid_Chain_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: C06385B14CDA6B8FF895008B023335BA
    namespace ControlRigModules.Modules.Finger {
        class Finger_C extends UE.ControlRig {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            ["Module Settings"]: UE.ControlRigModules.Modules.ModuleSettings.ModuleSettings;
            ["Override Control Settings"]: boolean;
            ["Control Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            ["Start Connector Default Match"]: UE.RigElementKey;
            ["Parent Control"]: UE.RigElementKey;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Finger_C;
            static Load(InName: string): Finger_C;
        
            __tid_Finger_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: B0D6814D4D6E396FEF9760BB0B00AAC4
    namespace ControlRigModules.Modules.Foot {
        class Foot_C extends UE.ControlRig {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            ["Module Settings"]: UE.ControlRigModules.Modules.ModuleSettings.ModuleSettings;
            ["Ball IK Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            ["Ball FK Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            ["Foot BK Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            ["Foot Roll Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            ["Heel IK Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            ["Tip Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Foot_C;
            static Load(InName: string): Foot_C;
        
            __tid_Foot_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: E69C1ACF4E3E41B2CDEFFB81AA155235
    namespace ControlRigModules.Modules.Leg {
        class Leg_C extends UE.ControlRig {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            ["Module Settings"]: UE.ControlRigModules.Modules.ModuleSettings.ModuleSettings;
            ["IK Shape Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            ["PV Shape Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            ["FK Shape Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            ["Auto Determine Axis"]: boolean;
            pv_control: UE.RigElementKey;
            foot_control: UE.RigElementKey;
            follow_null: UE.RigElementKey;
            effector: UE.RigElementKey;
            ["Ankle Bone"]: UE.RigElementKey;
            ["Thigh Bone"]: UE.RigElementKey;
            ["IK Null"]: UE.RigElementKey;
            prefix: string;
            RigVMFunction_MathVectorClampLength_Result: UE.Vector;
            RightSideThreshold: number;
            Subtract_1_Result: number;
            ["Foot Control"]: UE.RigElementKey;
            ["PV Ctrl"]: UE.RigElementKey;
            ["foot ik effector null"]: UE.RigElementKey;
            ["Get Side_Result"]: string;
            Unit_1_1_Result: UE.Vector;
            ["Primary Axis"]: UE.Vector;
            ["Secondary Axis"]: UE.Vector;
            ["FK IK Default"]: boolean;
            ["Orient IK to World"]: boolean;
            ["PV Offset Factor"]: number;
            ["IK Control Offset"]: UE.Transform;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Leg_C;
            static Load(InName: string): Leg_C;
        
            __tid_Leg_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: FFC6550941606D1B3B75BB9792F72FE1
    namespace ControlRigModules.Modules.ModuleSettings {
        class ModuleSettings {
            constructor();
            constructor(OverrideColor: boolean, LeftColor: UE.LinearColor, RightColor: UE.LinearColor, CenterColor: UE.LinearColor, ControlSize: number, Prefix: string, ControlSuffix: string, LeftSideSuffix: string, RightSideSuffix: string, CharacterFacingDownAxis: UE.Vector, MirrorAxis: UE.Vector, PrimaryBoneAxis: UE.Vector);
            ["Override Color"]: boolean;
            ["Left Color"]: UE.LinearColor;
            ["Right Color"]: UE.LinearColor;
            ["Center Color"]: UE.LinearColor;
            ["Control Size"]: number;
            Prefix: string;
            ["Control Suffix"]: string;
            ["Left Side Suffix"]: string;
            ["Right Side Suffix"]: string;
            ["Character Facing Down Axis"]: UE.Vector;
            ["Mirror Axis"]: UE.Vector;
            ["Primary Bone Axis"]: UE.Vector;
            /**
             * @deprecated use StaticStruct instead.
             */
            static StaticClass(): ScriptStruct;
            static StaticStruct(): ScriptStruct;
            __tid_ModuleSettings_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 017128874755E773AD3392BA4F1368E9
    namespace ControlRigModules.Modules.Neck {
        class Neck_C extends UE.ControlRig {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            ["Module Settings"]: UE.ControlRigModules.Modules.ModuleSettings.ModuleSettings;
            ["Head IK Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            ["Head FK Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            ["Neck FK Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            ["Local Spline Out"]: UE.ControlRigSpline;
            ["Template Spline Out"]: UE.ControlRigSpline;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Neck_C;
            static Load(InName: string): Neck_C;
        
            __tid_Neck_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: FA1539FC4A56F1F424AEDBA7957B401D
    namespace ControlRigModules.Modules.Piston {
        class Piston_C extends UE.ControlRig {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            ["Module Settings"]: UE.ControlRigModules.Modules.ModuleSettings.ModuleSettings;
            Debug: boolean;
            ["Add Up Vector Ctrl"]: boolean;
            ["Up Vector Axis"]: UE.Vector;
            ["Up Vector Offset Factor"]: number;
            ["Start Control Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            ["End Control Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            ["Up Control Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            ["Up Control"]: UE.RigElementKey;
            Name: string;
            Sticky: boolean;
            Reverse: boolean;
            ["As Controls"]: boolean;
            ["End Control Position"]: number;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Piston_C;
            static Load(InName: string): Piston_C;
        
            __tid_Piston_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: FBF2C89D4D348600A82C7C8226F2BE67
    namespace ControlRigModules.Modules.Shoulder {
        class Shoulder_C extends UE.ControlRig {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            ["Module Settings"]: UE.ControlRigModules.Modules.ModuleSettings.ModuleSettings;
            ["Clavicle Control Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Shoulder_C;
            static Load(InName: string): Shoulder_C;
        
            __tid_Shoulder_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 47975F8D44AF76BEAA44DC862380D148
    namespace ControlRigModules.Modules.Spine {
        class Spine_C extends UE.ControlRig {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            ["Module Settings"]: UE.ControlRigModules.Modules.ModuleSettings.ModuleSettings;
            ["Spine Control Shape Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            ["Body Control Shape Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            ["Hips Control Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            ["Chest Control Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            ["IK Primary Axis"]: UE.Vector;
            ["IK Up Axis"]: UE.Vector;
            ["IK Secondary Spline Direction"]: UE.Vector;
            ["Default FK or IK"]: boolean;
            Debug: boolean;
            Prefix: string;
            Suffix: string;
            Stretch: boolean;
            ["Body Control Adjustment"]: number;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Spine_C;
            static Load(InName: string): Spine_C;
        
            __tid_Spine_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 9D32A0094350753B595BDCB056681BE1
    namespace ControlRig.StandardFunctionLibrary.StandardFunctionLibrary {
        class StandardFunctionLibrary_C extends UE.ControlRig {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): StandardFunctionLibrary_C;
            static Load(InName: string): StandardFunctionLibrary_C;
        
            __tid_StandardFunctionLibrary_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 3C75B6A74B20A6684A88EBBF671A25CC
    namespace ControlRig.Modules.Root {
        class Root_C extends UE.ControlRig {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            ["Root Module Settings"]: UE.ControlRig.Modules.RootModuleSettings.RootModuleSettings;
            ["Root Control Name"]: string;
            ["Root Ctrl Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            ["Global Control Name"]: string;
            ["Global Control Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            ["Body Offset Control Name"]: string;
            ["Body Offset Control Settings"]: UE.RigUnit_HierarchyAddControlTransform_Settings;
            ["Generate Sockets"]: TArray<string>;
            ["Orient to World"]: boolean;
            Debug: boolean;
            ["body offset control"]: UE.RigElementKey;
            ["global control"]: UE.RigElementKey;
            ["Scale Root Controls Override"]: number;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Root_C;
            static Load(InName: string): Root_C;
        
            __tid_Root_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: FBDAA7584AF0EA9E05BDE0B778973C77
    namespace ControlRig.Modules.RootModuleSettings {
        class RootModuleSettings {
            constructor();
            constructor(LeftColor: UE.LinearColor, RightColor: UE.LinearColor, CenterColor: UE.LinearColor, ControlSize: number, Prefix: string, ControlSuffix: string, LeftSideSuffix: string, RightSideSuffix: string, CharacterFacingDownAxis: UE.Vector, MirrorAxis: UE.Vector, PrimaryBoneAxis: UE.Vector);
            ["Left Color"]: UE.LinearColor;
            ["Right Color"]: UE.LinearColor;
            ["Center Color"]: UE.LinearColor;
            ["Control Size"]: number;
            Prefix: string;
            ["Control Suffix"]: string;
            ["Left Side Suffix"]: string;
            ["Right Side Suffix"]: string;
            ["Character Facing Down Axis"]: UE.Vector;
            ["Mirror Axis"]: UE.Vector;
            ["Primary Bone Axis"]: UE.Vector;
            /**
             * @deprecated use StaticStruct instead.
             */
            static StaticClass(): ScriptStruct;
            static StaticStruct(): ScriptStruct;
            __tid_RootModuleSettings_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 5454832440510B5C7059E39506F7DD1F
    namespace Fab.Actors.GlobalFoliageActor.BP_GlobalFoliageActor_UE5 {
        class BP_GlobalFoliageActor_UE5_C extends UE.Actor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            Icon_Sock: UE.StaticMeshComponent;
            Icon_Arrow_Test: UE.StaticMeshComponent;
            Icon_Base: UE.StaticMeshComponent;
            Icon_Root: UE.StaticMeshComponent;
            ["Wind Noise Trees"]: number;
            ["Wind Strength Trees"]: number;
            ["Wind Speed Trees"]: number;
            ["Wind Tiling Trees"]: number;
            ["Season Strength"]: number;
            ["Season Brightness"]: number;
            ["Season Saturation"]: number;
            Health: number;
            ["Variation Tiling"]: number;
            ["Macro Variation Tiling"]: number;
            ["Random Color Variation Amount"]: number;
            ["Overall Color Variation Amount"]: number;
            ["Flip Wind Direction"]: boolean;
            ["Wind Speed Plants"]: number;
            ["Wind Strength Plants"]: number;
            ["Wind Tiling Plants"]: number;
            ["Wind Noise Plants"]: number;
            ExecuteUbergraph_BP_GlobalFoliageActor_UE5(EntryPoint: number) : void;
            /*
             *Event when play begins for this actor.
             */
            ReceiveBeginPlay() : void;
            /*
             *Event called every frame, if ticking is enabled
             */
            ReceiveTick(DeltaSeconds: number) : void;
            RunGlobalFoliageActor() : void;
            /*
             *Construction script, the place to spawn components and do other setup.
             *@note Name used in CreateBlueprint function
             */
            UserConstructionScript() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_GlobalFoliageActor_UE5_C;
            static Load(InName: string): BP_GlobalFoliageActor_UE5_C;
        
            __tid_BP_GlobalFoliageActor_UE5_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 673D63F0429AC28A6F72CAA5BAF13C8F
    namespace Engine.Tutorial.SubEditors.TutorialAssets.Character.TutorialCharacter {
        class TutorialCharacter_C extends UE.Character {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): TutorialCharacter_C;
            static Load(InName: string): TutorialCharacter_C;
        
            __tid_TutorialCharacter_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 5D77494845BE182F6F80FC90A2B91275
    namespace Engine.Tutorial.SubEditors.TutorialAssets.Character.TutorialTPP_AnimBlueprint {
        class AnimBlueprintGeneratedMutableData extends UE.AnimBlueprintMutableData {
            constructor();
            constructor(__FloatProperty: number);
            __FloatProperty: number;
            /**
             * @deprecated use StaticStruct instead.
             */
            static StaticClass(): ScriptStruct;
            static StaticStruct(): ScriptStruct;
            __tid_AnimBlueprintGeneratedMutableData_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 5D77494845BE182F6F80FC90A2B91275
    namespace Engine.Tutorial.SubEditors.TutorialAssets.Character.TutorialTPP_AnimBlueprint {
        class TutorialTPP_AnimBlueprint_C extends UE.AnimInstance {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            __AnimBlueprintMutables: UE.Engine.Tutorial.SubEditors.TutorialAssets.Character.TutorialTPP_AnimBlueprint.AnimBlueprintGeneratedMutableData;
            AnimBlueprintExtension_PropertyAccess: UE.AnimSubsystemInstance;
            AnimBlueprintExtension_Base: UE.AnimSubsystemInstance;
            AnimGraphNode_Root: UE.AnimNode_Root;
            AnimGraphNode_BlendSpacePlayer: UE.AnimNode_BlendSpacePlayer;
            Speed: number;
            AnimGraph(AnimGraph: $Ref<UE.PoseLink>) : void;
            /*
             *Executed when the Animation is updated
             */
            BlueprintUpdateAnimation(DeltaTimeX: number) : void;
            ExecuteUbergraph_TutorialTPP_AnimBlueprint(EntryPoint: number) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): TutorialTPP_AnimBlueprint_C;
            static Load(InName: string): TutorialTPP_AnimBlueprint_C;
        
            __tid_TutorialTPP_AnimBlueprint_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 5D77494845BE182F6F80FC90A2B91275
    namespace Engine.Tutorial.SubEditors.TutorialAssets.Character.TutorialTPP_AnimBlueprint {
        class AnimBlueprintGeneratedConstantData extends UE.AnimBlueprintConstantData {
            constructor();
            constructor(__NameProperty_7: string, __StructProperty_8: UE.AnimNodeFunctionRef, __BoolProperty_9: boolean, __FloatProperty_10: number, __FloatProperty_11: number, __BoolProperty_12: boolean, __EnumProperty_13: UE.EAnimSyncMethod, __ByteProperty_14: UE.EAnimGroupRole, __NameProperty_15: string, AnimBlueprintExtension_PropertyAccess: UE.AnimSubsystem_PropertyAccess, AnimBlueprintExtension_Base: UE.AnimSubsystem_Base, AnimGraphNode_Root: UE.AnimNodeExposedValueHandler_PropertyAccess, AnimGraphNode_BlendSpacePlayer: UE.AnimNodeExposedValueHandler_PropertyAccess);
            __NameProperty_7: string;
            __StructProperty_8: UE.AnimNodeFunctionRef;
            __BoolProperty_9: boolean;
            __FloatProperty_10: number;
            __FloatProperty_11: number;
            __BoolProperty_12: boolean;
            __EnumProperty_13: UE.EAnimSyncMethod;
            __ByteProperty_14: UE.EAnimGroupRole;
            __NameProperty_15: string;
            AnimBlueprintExtension_PropertyAccess: UE.AnimSubsystem_PropertyAccess;
            AnimBlueprintExtension_Base: UE.AnimSubsystem_Base;
            AnimGraphNode_Root: UE.AnimNodeExposedValueHandler_PropertyAccess;
            AnimGraphNode_BlendSpacePlayer: UE.AnimNodeExposedValueHandler_PropertyAccess;
            /**
             * @deprecated use StaticStruct instead.
             */
            static StaticClass(): ScriptStruct;
            static StaticStruct(): ScriptStruct;
            __tid_AnimBlueprintGeneratedConstantData_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 4205CCBB454A1F9F82B8EE8E4DBD36F7
    namespace Engine.Tutorial.SubEditors.TutorialAssets.TutorialAnimationBlueprint {
        class TutorialAnimationBlueprint_C extends UE.AnimInstance {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            AnimBlueprintExtension_PropertyAccess: UE.AnimSubsystemInstance;
            AnimBlueprintExtension_Base: UE.AnimSubsystemInstance;
            AnimGraphNode_Root: UE.AnimNode_Root;
            AnimGraphNode_StateResult: UE.AnimNode_StateResult;
            AnimGraphNode_StateMachine: UE.AnimNode_StateMachine;
            SomeBoolean: boolean;
            SomeFloat: number;
            AnimGraph(AnimGraph: $Ref<UE.PoseLink>) : void;
            /*
             *Executed when the Animation is updated
             */
            BlueprintUpdateAnimation(DeltaTimeX: number) : void;
            ExecuteUbergraph_TutorialAnimationBlueprint(EntryPoint: number) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): TutorialAnimationBlueprint_C;
            static Load(InName: string): TutorialAnimationBlueprint_C;
        
            __tid_TutorialAnimationBlueprint_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 4205CCBB454A1F9F82B8EE8E4DBD36F7
    namespace Engine.Tutorial.SubEditors.TutorialAssets.TutorialAnimationBlueprint {
        class AnimBlueprintGeneratedConstantData extends UE.AnimBlueprintConstantData {
            constructor();
            constructor(__NameProperty_11: string, __NameProperty_12: string, __NameProperty_13: string, __NameProperty_14: string, __IntProperty_15: number, __StructProperty_16: UE.AnimNodeFunctionRef, AnimBlueprintExtension_PropertyAccess: UE.AnimSubsystem_PropertyAccess, AnimBlueprintExtension_Base: UE.AnimSubsystem_Base, AnimGraphNode_Root: UE.AnimNodeExposedValueHandler_PropertyAccess, AnimGraphNode_StateResult: UE.AnimNodeExposedValueHandler_PropertyAccess, AnimGraphNode_StateMachine: UE.AnimNodeExposedValueHandler_PropertyAccess);
            __NameProperty_11: string;
            __NameProperty_12: string;
            __NameProperty_13: string;
            __NameProperty_14: string;
            __IntProperty_15: number;
            __StructProperty_16: UE.AnimNodeFunctionRef;
            AnimBlueprintExtension_PropertyAccess: UE.AnimSubsystem_PropertyAccess;
            AnimBlueprintExtension_Base: UE.AnimSubsystem_Base;
            AnimGraphNode_Root: UE.AnimNodeExposedValueHandler_PropertyAccess;
            AnimGraphNode_StateResult: UE.AnimNodeExposedValueHandler_PropertyAccess;
            AnimGraphNode_StateMachine: UE.AnimNodeExposedValueHandler_PropertyAccess;
            /**
             * @deprecated use StaticStruct instead.
             */
            static StaticClass(): ScriptStruct;
            static StaticStruct(): ScriptStruct;
            __tid_AnimBlueprintGeneratedConstantData_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 4205CCBB454A1F9F82B8EE8E4DBD36F7
    namespace Engine.Tutorial.SubEditors.TutorialAssets.TutorialAnimationBlueprint {
        class AnimBlueprintGeneratedMutableData extends UE.AnimBlueprintMutableData {
            constructor();
            /**
             * @deprecated use StaticStruct instead.
             */
            static StaticClass(): ScriptStruct;
            static StaticStruct(): ScriptStruct;
            __tid_AnimBlueprintGeneratedMutableData_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: A041618442A0D38DB2406DB180EA4B9F
    namespace Engine.Tutorial.BlueprintTutorials.TutorialAssets.Tutorial_BP_Class {
        class Tutorial_BP_Class_C extends UE.Actor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            DefaultSceneRoot: UE.SceneComponent;
            SampleVariable: boolean;
            StoredGameMode: UE.GameModeBase;
            ExecuteUbergraph_Tutorial_BP_Class(EntryPoint: number) : void;
            /*
             *Event when play begins for this actor.
             */
            ReceiveBeginPlay() : void;
            /*
             *Event called every frame, if ticking is enabled
             */
            ReceiveTick(DeltaSeconds: number) : void;
            /*
             *Construction script, the place to spawn components and do other setup.
             *@note Name used in CreateBlueprint function
             */
            UserConstructionScript() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Tutorial_BP_Class_C;
            static Load(InName: string): Tutorial_BP_Class_C;
        
            __tid_Tutorial_BP_Class_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: EDEAEC95417A6639D0C13D8E4E170BB9
    namespace Engine.Tutorial.BlueprintTutorials.TutorialAssets.Tutorial_BP_Interface {
        class Tutorial_BP_Interface_C extends UE.Interface {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            TutorialSampleFunction() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Tutorial_BP_Interface_C;
            static Load(InName: string): Tutorial_BP_Interface_C;
        
            __tid_Tutorial_BP_Interface_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: FF82B89B4554CB4C86669EB5A5E89201
    namespace Engine.Sequencer.DefaultBurnIn {
        class DefaultBurnIn_C extends UE.LevelSequenceBurnIn {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            Border_0: UE.Border;
            Border_3: UE.Border;
            BottomCenter: UE.TextBlock;
            BottomLeft: UE.TextBlock;
            BottomRight: UE.TextBlock;
            TopCenter: UE.TextBlock;
            TopLeft: UE.TextBlock;
            TopRight: UE.TextBlock;
            Watermark: UE.Image;
            ["Foreground Color"]: UE.LinearColor;
            ["Background Color"]: UE.LinearColor;
            Date: string;
            Options: UE.Engine.Sequencer.DefaultBurnInOptions.DefaultBurnInOptions_C;
            hh: string;
            mm: string;
            ss: string;
            ff: string;
            MasterFrame: string;
            ShotFrame: string;
            MasterName: string;
            ShotName: string;
            FocalLength: string;
            FocusDistance: string;
            Aperture: string;
            SensorWidth: string;
            SensorHeight: string;
            SensorAspectRatio: string;
            Translation: UE.Vector;
            Rotation: UE.Rotator;
            bCached: boolean;
            EngineVersion: string;
            SourceTimecode: string;
            CacheData() : void;
            /*
             *Called after the underlying slate widget is constructed.  Depending on how the slate object is used
             *this event may be called multiple times due to adding and removing from the hierarchy.
             *If you need a true called-once-when-created event, use OnInitialized.
             */
            Construct() : void;
            ExecuteUbergraph_DefaultBurnIn(EntryPoint: number) : void;
            Get_BottomCenter_Text_0() : string;
            Get_BottomLeft_Text_0() : string;
            Get_BottomRight_Text_0() : string;
            Get_TopCenter_Text_0() : string;
            Get_TopLeft_Text_0() : string;
            Get_TopRight_Text_0() : string;
            /*
             *Get the settings class to use for this burn in
             */
            GetSettingsClass() : UE.Class;
            /*
             *Called when this burn in is receiving its settings
             */
            SetSettings(InSettings: $Nullable<UE.Object>) : void;
            /*
             *Ticks this widget.  Override in derived classes, but always call the parent implementation.
             *
             *@param  MyGeometry The space allotted for this widget
             *@param  InDeltaTime  Real time passed since last tick
             */
            Tick(MyGeometry: UE.Geometry, InDeltaTime: number) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): DefaultBurnIn_C;
            static Load(InName: string): DefaultBurnIn_C;
        
            __tid_DefaultBurnIn_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: E25E996F43158A4796DEFDAE17844463
    namespace Engine.Sequencer.DefaultBurnInOptions {
        class DefaultBurnInOptions_C extends UE.LevelSequenceBurnInInitSettings {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            TopLeftText: string;
            TopCenterText: string;
            TopRightText: string;
            BottomLeftText: string;
            BottomCenterText: string;
            BottomRightText: string;
            Watermark: UE.Texture2D;
            WatermarkTint: UE.LinearColor;
            Font: UE.SlateFontInfo;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): DefaultBurnInOptions_C;
            static Load(InName: string): DefaultBurnInOptions_C;
        
            __tid_DefaultBurnInOptions_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: B076AEA04C61E0B4A6F249931D9A6E87
    namespace Engine.FunctionalTesting.Blueprints.AITesting_MoveGoal {
        class AITesting_MoveGoal_C extends UE.Actor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            MySpriteComponent: UE.BillboardComponent;
            CollisionBox: UE.BoxComponent;
            ObservedPawn: UE.Object;
            CurrentTest: UE.FunctionalTest;
            bStartEnabled: boolean;
            ExecuteUbergraph_AITesting_MoveGoal(EntryPoint: number) : void;
            /*
             *Event when play begins for this actor.
             */
            ReceiveBeginPlay() : void;
            SetCollisionEnabled(bShouldBeEnabled: boolean) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): AITesting_MoveGoal_C;
            static Load(InName: string): AITesting_MoveGoal_C;
        
            __tid_AITesting_MoveGoal_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: D549414D427DF9190E03438E028EF172
    namespace Engine.EditorBlueprintResources.ActorComponentMacros {
        class ActorComponentMacros_C extends UE.ActorComponent {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ActorComponentMacros_C;
            static Load(InName: string): ActorComponentMacros_C;
        
            __tid_ActorComponentMacros_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: E7FB506A4BD35DA67A771BB584DA8197
    namespace Engine.EditorBlueprintResources.ActorMacros {
        class ActorMacros_C extends UE.Actor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ActorMacros_C;
            static Load(InName: string): ActorMacros_C;
        
            __tid_ActorMacros_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 67D6697E49FB272F78CDB7BCC0894281
    namespace Engine.EditorBlueprintResources.StandardMacros {
        class StandardMacros_C extends UE.Object {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): StandardMacros_C;
            static Load(InName: string): StandardMacros_C;
        
            __tid_StandardMacros_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 8C2858A646EB2E9B1C1076BCE80C3680
    namespace Engine.ArtTools.RenderToTexture.Macros.RenderToTextureFunctionLibrary {
        class RenderToTextureFunctionLibrary_C extends UE.BlueprintFunctionLibrary {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static ["Array to HLSL Int Array"](Type: UE.Engine.ArtTools.RenderToTexture.Enums.EIntTypes.EIntTypes, VariableName: $Ref<string>, int: $Ref<TArray<number>>, int2: $Ref<TArray<UE.Vector2D>>, int3: $Ref<TArray<UE.Vector>>, int4: $Ref<TArray<UE.LinearColor>>, __WorldContext: $Nullable<UE.Object>, String: $Ref<string>) : void;
            static ["Set Canvas Material Scale and Position"](Size: UE.Vector2D, Position: UE.Vector2D, Scale: number, __WorldContext: $Nullable<UE.Object>, ScreenPosition: $Ref<UE.Vector2D>, ScreenSize: $Ref<UE.Vector2D>) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): RenderToTextureFunctionLibrary_C;
            static Load(InName: string): RenderToTextureFunctionLibrary_C;
        
            __tid_RenderToTextureFunctionLibrary_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: F886D44E4F3DEE1BB130B5B7C0D7D0F3
    namespace Engine.ArtTools.RenderToTexture.Macros.RenderToTextureMacros {
        class RenderToTextureMacros_C extends UE.Actor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): RenderToTextureMacros_C;
            static Load(InName: string): RenderToTextureMacros_C;
        
            __tid_RenderToTextureMacros_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 98665A884F1AE388294A3099C9F6C5D1
    namespace Engine.ArtTools.RenderToTexture.Enums.EFloatTypes {
        enum EFloatTypes { Float, Float2, Float3, Float4, EFloatTypes_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 917415834ED8BB644B2CF0AA1CA0855E
    namespace Engine.ArtTools.RenderToTexture.Enums.EIntTypes {
        enum EIntTypes { int, int2, int3, int4, EIntTypes_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: E6D8002949675C4E9A6390970CD0DF84
    namespace Engine.ArtTools.RenderToTexture.Enums.RenderToTexture_Enum {
        enum RenderToTexture_Enum { Material, "Unwrapped Mesh", "Depth Map", Lightmaps, "Lightmaps 2-sided", "Flipbook Mesh Animation", "Physics Ground - Tiling Physics Drop of Meshes", "Tiling Material from Hand Placed Meshes", RenderToTexture_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: CD8E94724625948C9FB6E19BC4560F4A
    namespace Engine.ArtTools.RenderToTexture.Enums.RenderToTexture_Flipbook_Enum {
        enum RenderToTexture_Flipbook_Enum { "Simple Mesh rotation", "Material Instance Interpolation", "Both Mesh rotation and Material Instance Interpolation", RenderToTexture_Flipbook_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: B5FAA1344910B53E80113D8075B18513
    namespace Engine.ArtTools.RenderToTexture.Enums.RenderToTexture_Imposter_Enum {
        enum RenderToTexture_Imposter_Enum { "Full 3D Imposter", "Single Rotation Axis", RenderToTexture_Imposter_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 313591D9408B14DEE2B4D19F2EA1342F
    namespace Engine.ArtTools.RenderToTexture.Blueprints.PhysMesh {
        class PhysMesh {
            constructor();
            constructor(SMesh: UE.StaticMesh, Transform: UE.Transform);
            SMesh: UE.StaticMesh;
            Transform: UE.Transform;
            /**
             * @deprecated use StaticStruct instead.
             */
            static StaticClass(): ScriptStruct;
            static StaticStruct(): ScriptStruct;
            __tid_PhysMesh_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: A04E9A724D45605D5C062683BA52E56B
    namespace Engine.ArtTools.RenderToTexture.Blueprints.RenderToTexture_Game {
        class RenderToTexture_Game_C extends UE.GameMode {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            DefaultSceneRoot: UE.SceneComponent;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): RenderToTexture_Game_C;
            static Load(InName: string): RenderToTexture_Game_C;
        
            __tid_RenderToTexture_Game_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 9BE3FACE43A2AC9F6C1F108D55966C37
    namespace Engine.ArtTools.RenderToTexture.Blueprints.RenderToTexture_LevelBP {
        class RenderToTexture_LevelBP_C extends UE.Pawn {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            ["BottomCollision-LargeMeshesOnly"]: UE.BoxComponent;
            ["SceneCapture Motion Position 1"]: UE.SceneCaptureComponent2D;
            TopOutline: UE.BoxComponent;
            PreviewMesh: UE.StaticMeshComponent;
            TilingPreviewCapture: UE.SceneCaptureComponent2D;
            BottomCollision: UE.BoxComponent;
            Box5: UE.BoxComponent;
            Box4: UE.BoxComponent;
            Box3: UE.BoxComponent;
            Box2: UE.BoxComponent;
            PlaneMesh: UE.StaticMeshComponent;
            Debug: UE.TextRenderComponent;
            Camera1: UE.CameraComponent;
            Root: UE.StaticMeshComponent;
            RotationArray: TArray<UE.Rotator>;
            ["Render Type"]: UE.Engine.ArtTools.RenderToTexture.Enums.RenderToTexture_Enum.RenderToTexture_Enum;
            ["Viewport size (see Tooltip)"]: number;
            ResolutionMultiplier: number;
            BaseColor: boolean;
            Specular: boolean;
            Metallic: boolean;
            Normal: boolean;
            Opacity: boolean;
            Roughness: boolean;
            AmbientOcclusion: boolean;
            MaterialAmbientOcclusion: boolean;
            ["Decal Mask"]: boolean;
            ["Lighting Only"]: boolean;
            ["Subsurface Color"]: boolean;
            ["Imposter Static Mesh"]: UE.StaticMesh;
            BufferCommands: string;
            ResCommand: string;
            SheetSize: number;
            ShotCommand: string;
            MeshScale: number;
            ["Imposter MaterialInstanceArray"]: TArray<UE.MaterialInstance>;
            MaterialColor2: UE.LinearColor;
            SectorSize: number;
            InitialOffset: UE.Vector;
            initialscale: number;
            Internalscalefactor: number;
            StaticMeshComponent: UE.StaticMeshComponent;
            LevelStaticMeshActorArray: TArray<UE.Actor>;
            ["Render to Texture Mesh"]: UE.StaticMeshActor;
            ["Use Level Meshes for Depth"]: boolean;
            LightVector: UE.Vector;
            ["Directional Light"]: UE.DirectionalLight;
            ["Opacity Mask Textures"]: TArray<UE.Texture>;
            ["Opacity Mask Channels"]: TArray<UE.LinearColor>;
            ["Frames around Z rotation"]: number;
            ["Aspect Ratio 1 by"]: number;
            ["Use Level Placed Meshes"]: boolean;
            ["Lightmap Mesh"]: UE.StaticMeshActor;
            ["Lightmap Mesh 2-sided, Side 1"]: UE.StaticMeshActor;
            ["Lightmap Mesh 2-sided, Side 2"]: UE.StaticMeshActor;
            ["Depth Map Static Mesh"]: UE.StaticMesh;
            Unwrap: boolean;
            ["Depth Material Mask Textures"]: TArray<UE.Texture2D>;
            ["Flipbook Start Rotation"]: UE.Rotator;
            ["Flipbook Rotation Axis 1"]: UE.Vector;
            ["Flipbook Rotation Axis 2"]: UE.Vector;
            ["Axis 1 Rotations"]: number;
            ["Axis 2 Rotations"]: number;
            ["Flipbook Columns (X)"]: number;
            ["Flipbook Rows (Y)"]: number;
            ["Flipbook MaterialInstance List"]: TArray<UE.MaterialInstance>;
            ["Opacity MaskTextures"]: TArray<UE.Texture>;
            ["Opacity MaskChannels"]: TArray<UE.LinearColor>;
            ["Flipbook Static Mesh"]: UE.StaticMesh;
            ["Flipbook Mesh scale"]: number;
            ["Preview Speed"]: number;
            ImposterEnum: UE.Engine.ArtTools.RenderToTexture.Enums.RenderToTexture_Imposter_Enum.RenderToTexture_Imposter_Enum;
            ["Single Rotation Axis"]: UE.Vector;
            ["Unwrap Lightmap 2sided"]: boolean;
            Unwrap2sidedMIDlistA: TArray<UE.MaterialInstanceDynamic>;
            Unwrap2sidedMIDListB: TArray<UE.MaterialInstanceDynamic>;
            ["Lightmap Unwrap Material"]: UE.MaterialInstanceConstant;
            ["Unwrap Lightmap"]: boolean;
            ["Mask Channel"]: TArray<UE.LinearColor>;
            DepthMeshInitialSize: UE.Vector;
            DepthMID: UE.MaterialInstanceDynamic;
            ["Scale XY"]: number;
            ["Scale Z"]: number;
            ["Fit Vector and scale info onto texture"]: boolean;
            TextSize: number;
            ["Text Locations"]: TArray<UE.Vector>;
            ParticleSystem: UE.ParticleSystem;
            SavedPhysMeshList: TArray<UE.Engine.ArtTools.RenderToTexture.Blueprints.PhysMesh.PhysMesh>;
            ["Simulate Physics"]: boolean;
            ["Keep Tiling Hand Placed Meshes"]: boolean;
            ["Simple Random Placement"]: boolean;
            ["PhysGround Mat"]: UE.MaterialInstanceConstant;
            ["Mesh List"]: TArray<UE.StaticMesh>;
            ["Mesh Size Min"]: number;
            ["Mesh Size Max"]: number;
            ["Size Curve"]: number;
            ["Spawn by Size"]: boolean;
            ["PhysGround Density m^2"]: number;
            Count: number;
            ["Number of Meshes"]: number;
            PhysStaticMeshes: TArray<UE.StaticMeshComponent>;
            ["Debug Displacement Depth"]: boolean;
            ["Displacement Min"]: number;
            ["Displacement Max"]: number;
            ["Kill Above Z Min"]: number;
            ["Kill Above Z Max"]: number;
            ["Copied Mesh Array"]: TArray<UE.StaticMeshComponent>;
            ["Current Component"]: UE.StaticMeshComponent;
            StaticMobilityMeshes: TArray<UE.StaticMeshComponent>;
            SavedMeshComponents: TArray<UE.StaticMeshComponent>;
            ["Material Instance"]: UE.MaterialInstance;
            ["Stadium Offsetting"]: boolean;
            ["TilingMesh List"]: TArray<UE.Engine.ArtTools.RenderToTexture.Blueprints.TilingMesh.TilingMesh>;
            SceneDepthWorldUnits: boolean;
            DisplacementMin: number;
            DisplacementMax: number;
            DebugDisplacementDepth: boolean;
            ["Custom Depth"]: boolean;
            ["Displacement Texture Height"]: number;
            ["Preview Tiling"]: boolean;
            ["Tiling Amount"]: number;
            ImposterArray: TArray<UE.Transform>;
            PreviewLocation: UE.Vector;
            ["Output Depth Maps"]: boolean;
            ImposterMeshComponents: TArray<UE.StaticMeshComponent>;
            BackgroundSheetMID: UE.MaterialInstanceDynamic;
            ["Debug Depth"]: boolean;
            ["Max Pitch/Roll"]: number;
            ["Render Motion Vectors"]: boolean;
            SceneColor: boolean;
            ["Sheet height"]: number;
            ["Background Sheet Color"]: UE.LinearColor;
            FlipbookMeshes: TArray<UE.StaticMeshComponent>;
            ["UV Layout Dilation Amount"]: number;
            OffsetVectors: TArray<UE.Vector>;
            ["Empty Spacer"]: boolean;
            CurrentRenderLoc: UE.Vector;
            ["UV Dilation Steps"]: number;
            MaterialChoice: UE.MaterialInstance;
            MVFloors: TArray<UE.StaticMeshComponent>;
            FlipbookMID: UE.MaterialInstanceDynamic;
            ["Motion Dilation Steps"]: number;
            UnwrappedMotionVectorMeshes: TArray<UE.StaticMeshComponent>;
            MotionVectorIntensityBoost: number;
            sRGB: boolean;
            ["Render MotionVectors"]: boolean;
            ["Large Mesh Sink Height"]: number;
            ["Large Mesh Size Threshold"]: number;
            ["UV DilationPass"]: boolean;
            ["MotionVector Pass"]: boolean;
            MotionVectorMaterial: UE.MaterialInstanceConstant;
            MotionVectorsApplied: UE.MaterialInstanceConstant;
            ["UV Layout DilationAmount"]: number;
            ["UV DilationSteps"]: number;
            ["Motion DilationSteps"]: number;
            ["Motion Vector IntensityBoost"]: number;
            MotionVectorsApplied_Imposter: UE.MaterialInstanceConstant;
            ["Flipbook Preview Mat"]: UE.MaterialInstanceConstant;
            ["Imposter-SingleAxis Preview Mat"]: UE.MaterialInstanceConstant;
            ["Imposter-3D Preview Mat"]: UE.MaterialInstanceConstant;
            MIDList: TArray<UE.MaterialInstanceDynamic>;
            PolyCenter: UE.Vector;
            ["Offst Phase"]: number;
            ["Dilation Phase"]: number;
            ["Ortho FOV"]: number;
            ["Indicies to Delete"]: TArray<number>;
            TilingAmount: number;
            UVIndex: number;
            ["UV Index"]: number;
            NewVar: UE.MaterialInstanceDynamic;
            ["Export images as EXR"]: boolean;
            ["Copy a mesh"](MeshComponent: $Nullable<UE.StaticMeshComponent>, OffsetVector: UE.Vector, ArraytoPlaceMeshesin: $Ref<TArray<UE.StaticMeshComponent>>) : void;
            ExecuteUbergraph_RenderToTexture_LevelBP(EntryPoint: number) : void;
            ["Find Z Bounds"](Meshes: $Ref<TArray<UE.StaticMeshComponent>>, Min: $Ref<number>, Max: $Ref<number>) : void;
            FlipBook() : void;
            ["Imposter Sprites"]() : void;
            ["Match Level Actors to Imposter Array"]() : void;
            ["New Mesh"](Mesh: $Nullable<UE.StaticMesh>, WorldPos: UE.Vector, Material: $Nullable<UE.MaterialInterface>, Scale3d: UE.Vector, MeshComp: $Ref<UE.StaticMeshComponent>) : void;
            ["Particle System Frame Dump"]() : void;
            /*
             *Event when play begins for this actor.
             */
            ReceiveBeginPlay() : void;
            ["Render Depth Map"](MID: $Ref<UE.MaterialInstanceDynamic>) : void;
            ["Render Lightmap"]() : void;
            ["Render LIghtmap 2-sided"]() : void;
            ["Render Random Tiling Physics Drop"]() : void;
            ["Render Tiling Material"]() : void;
            ["Render Tiling Material from Meshes"]() : void;
            ["Render Unwrapped Mesh To Textures"]() : void;
            ["Set Buffer Commands"]() : void;
            ["Set up MPC"]() : void;
            ["Setup Collision"](Visible: boolean) : void;
            /*
             *Construction script, the place to spawn components and do other setup.
             *@note Name used in CreateBlueprint function
             */
            UserConstructionScript() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): RenderToTexture_LevelBP_C;
            static Load(InName: string): RenderToTexture_LevelBP_C;
        
            __tid_RenderToTexture_LevelBP_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 27C138CE42C6CE63C34E8BAF375EBA07
    namespace Engine.ArtTools.RenderToTexture.Blueprints.RenderToTexture_Pawn {
        class RenderToTexture_Pawn_C extends UE.Pawn {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            Pawncam: UE.CameraComponent;
            Root: UE.StaticMeshComponent;
            BaseColor: boolean;
            Specular: boolean;
            Normal: boolean;
            Opacity: boolean;
            Roughness: boolean;
            AmbientOcclusion: boolean;
            MaterialAmbientOcclusion: boolean;
            ResolutionMultiplier: number;
            BufferCommands: string;
            ShotCommand: string;
            ["Backface SSS Meshes"]: TArray<UE.StaticMeshActor>;
            MIDArray: TArray<UE.MaterialInstanceDynamic>;
            Generator: UE.Engine.ArtTools.RenderToTexture.Blueprints.RenderToTexture_LevelBP.RenderToTexture_LevelBP_C;
            debugdepth() : void;
            ExecuteUbergraph_RenderToTexture_Pawn(EntryPoint: number) : void;
            /*
             *Event when play begins for this actor.
             */
            ReceiveBeginPlay() : void;
            renderdepth() : void;
            renderimposter() : void;
            renderlightmaps() : void;
            rendertextures() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): RenderToTexture_Pawn_C;
            static Load(InName: string): RenderToTexture_Pawn_C;
        
            __tid_RenderToTexture_Pawn_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: B118B8C74937C69B9F68058A6ED53621
    namespace Engine.ArtTools.RenderToTexture.Blueprints.TilingMesh {
        class TilingMesh {
            constructor();
            constructor(StaticMesh: UE.StaticMesh, Transform: UE.Transform, Material: UE.MaterialInstanceConstant, Visible: boolean, DisplacementTexture: UE.Texture);
            StaticMesh: UE.StaticMesh;
            Transform: UE.Transform;
            Material: UE.MaterialInstanceConstant;
            Visible: boolean;
            DisplacementTexture: UE.Texture;
            /**
             * @deprecated use StaticStruct instead.
             */
            static StaticClass(): ScriptStruct;
            static StaticStruct(): ScriptStruct;
            __tid_TilingMesh_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 203A77A04B4E5237F92EA483C4B8DDB8
    namespace Engine.EngineSky.BP_Sky_Sphere {
        class BP_Sky_Sphere_C extends UE.Actor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            SkySphereMesh: UE.StaticMeshComponent;
            Base: UE.SceneComponent;
            ["Sky material"]: UE.MaterialInstanceDynamic;
            ["Refresh material"]: boolean;
            ["Directional light actor"]: UE.DirectionalLight;
            ["Colors determined by sun position"]: boolean;
            ["Sun height"]: number;
            ["Sun brightness"]: number;
            ["Horizon Falloff"]: number;
            ["Zenith Color"]: UE.LinearColor;
            ["Horizon color"]: UE.LinearColor;
            ["Cloud color"]: UE.LinearColor;
            ["Overall Color"]: UE.LinearColor;
            ["Cloud speed"]: number;
            ["Cloud opacity"]: number;
            ["Stars brightness"]: number;
            ["Horizon color curve"]: UE.CurveLinearColor;
            ["Zenith color curve"]: UE.CurveLinearColor;
            ["Cloud color curve"]: UE.CurveLinearColor;
            RefreshMaterial() : void;
            UpdateSunDirection() : void;
            /*
             *Construction script, the place to spawn components and do other setup.
             *@note Name used in CreateBlueprint function
             */
            UserConstructionScript() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Sky_Sphere_C;
            static Load(InName: string): BP_Sky_Sphere_C;
        
            __tid_BP_Sky_Sphere_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class AchievementWriteDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): AchievementWriteDelegate__PythonCallable;
            static Load(InName: string): AchievementWriteDelegate__PythonCallable;
        
            __tid_AchievementWriteDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ActorBeginCursorOverSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ActorBeginCursorOverSignature__PythonCallable;
            static Load(InName: string): ActorBeginCursorOverSignature__PythonCallable;
        
            __tid_ActorBeginCursorOverSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ActorBeginOverlapSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ActorBeginOverlapSignature__PythonCallable;
            static Load(InName: string): ActorBeginOverlapSignature__PythonCallable;
        
            __tid_ActorBeginOverlapSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ActorBeginTouchOverSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ActorBeginTouchOverSignature__PythonCallable;
            static Load(InName: string): ActorBeginTouchOverSignature__PythonCallable;
        
            __tid_ActorBeginTouchOverSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ActorComponentActivatedSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ActorComponentActivatedSignature__PythonCallable;
            static Load(InName: string): ActorComponentActivatedSignature__PythonCallable;
        
            __tid_ActorComponentActivatedSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ActorComponentDeactivateSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ActorComponentDeactivateSignature__PythonCallable;
            static Load(InName: string): ActorComponentDeactivateSignature__PythonCallable;
        
            __tid_ActorComponentDeactivateSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ActorDestroyedSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ActorDestroyedSignature__PythonCallable;
            static Load(InName: string): ActorDestroyedSignature__PythonCallable;
        
            __tid_ActorDestroyedSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ActorEndCursorOverSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ActorEndCursorOverSignature__PythonCallable;
            static Load(InName: string): ActorEndCursorOverSignature__PythonCallable;
        
            __tid_ActorEndCursorOverSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ActorEndOverlapSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ActorEndOverlapSignature__PythonCallable;
            static Load(InName: string): ActorEndOverlapSignature__PythonCallable;
        
            __tid_ActorEndOverlapSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ActorEndPlaySignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ActorEndPlaySignature__PythonCallable;
            static Load(InName: string): ActorEndPlaySignature__PythonCallable;
        
            __tid_ActorEndPlaySignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ActorEndTouchOverSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ActorEndTouchOverSignature__PythonCallable;
            static Load(InName: string): ActorEndTouchOverSignature__PythonCallable;
        
            __tid_ActorEndTouchOverSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ActorHitSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ActorHitSignature__PythonCallable;
            static Load(InName: string): ActorHitSignature__PythonCallable;
        
            __tid_ActorHitSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ActorOnClickedSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ActorOnClickedSignature__PythonCallable;
            static Load(InName: string): ActorOnClickedSignature__PythonCallable;
        
            __tid_ActorOnClickedSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ActorOnInputTouchBeginSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ActorOnInputTouchBeginSignature__PythonCallable;
            static Load(InName: string): ActorOnInputTouchBeginSignature__PythonCallable;
        
            __tid_ActorOnInputTouchBeginSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ActorOnInputTouchEndSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ActorOnInputTouchEndSignature__PythonCallable;
            static Load(InName: string): ActorOnInputTouchEndSignature__PythonCallable;
        
            __tid_ActorOnInputTouchEndSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ActorOnReleasedSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ActorOnReleasedSignature__PythonCallable;
            static Load(InName: string): ActorOnReleasedSignature__PythonCallable;
        
            __tid_ActorOnReleasedSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ActorPerceptionForgetUpdatedDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ActorPerceptionForgetUpdatedDelegate__PythonCallable;
            static Load(InName: string): ActorPerceptionForgetUpdatedDelegate__PythonCallable;
        
            __tid_ActorPerceptionForgetUpdatedDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ActorPerceptionInfoUpdatedDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ActorPerceptionInfoUpdatedDelegate__PythonCallable;
            static Load(InName: string): ActorPerceptionInfoUpdatedDelegate__PythonCallable;
        
            __tid_ActorPerceptionInfoUpdatedDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ActorPerceptionUpdatedDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ActorPerceptionUpdatedDelegate__PythonCallable;
            static Load(InName: string): ActorPerceptionUpdatedDelegate__PythonCallable;
        
            __tid_ActorPerceptionUpdatedDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class add_controls_for_selected extends UE.ToolMenuEntryScript {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): add_controls_for_selected;
            static Load(InName: string): add_controls_for_selected;
        
            __tid_add_controls_for_selected_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        enum ControlOutputFormat { HIERARCHY, LIST, CHILD, ControlOutputFormat_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class add_controls_for_selected_options extends UE.Object {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            output_format: UE.Engine.PythonTypes.ControlOutputFormat;
            suffix: string;
            prefix: string;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): add_controls_for_selected_options;
            static Load(InName: string): add_controls_for_selected_options;
        
            __tid_add_controls_for_selected_options_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class add_null_above_selected extends UE.ToolMenuEntryScript {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): add_null_above_selected;
            static Load(InName: string): add_null_above_selected;
        
            __tid_add_null_above_selected_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class add_prefix_dialog extends UE.Object {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            prefix: string;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): add_prefix_dialog;
            static Load(InName: string): add_prefix_dialog;
        
            __tid_add_prefix_dialog_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class add_prefix_entry extends UE.ToolMenuEntryScript {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): add_prefix_entry;
            static Load(InName: string): add_prefix_entry;
        
            __tid_add_prefix_entry_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class add_suffix_dialog extends UE.Object {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            suffix: string;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): add_suffix_dialog;
            static Load(InName: string): add_suffix_dialog;
        
            __tid_add_suffix_dialog_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class add_suffix_entry extends UE.ToolMenuEntryScript {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): add_suffix_entry;
            static Load(InName: string): add_suffix_entry;
        
            __tid_add_suffix_entry_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class AdvancedCopyCompletedEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): AdvancedCopyCompletedEvent__PythonCallable;
            static Load(InName: string): AdvancedCopyCompletedEvent__PythonCallable;
        
            __tid_AdvancedCopyCompletedEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class AIMoveCompletedSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): AIMoveCompletedSignature__PythonCallable;
            static Load(InName: string): AIMoveCompletedSignature__PythonCallable;
        
            __tid_AIMoveCompletedSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class align_rotation extends UE.ToolMenuEntryScript {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): align_rotation;
            static Load(InName: string): align_rotation;
        
            __tid_align_rotation_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class align_scale extends UE.ToolMenuEntryScript {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): align_scale;
            static Load(InName: string): align_scale;
        
            __tid_align_scale_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class align_translation_all extends UE.ToolMenuEntryScript {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): align_translation_all;
            static Load(InName: string): align_translation_all;
        
            __tid_align_translation_all_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class align_translation_rotation extends UE.ToolMenuEntryScript {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): align_translation_rotation;
            static Load(InName: string): align_translation_rotation;
        
            __tid_align_translation_rotation_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class align_translation_x extends UE.ToolMenuEntryScript {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): align_translation_x;
            static Load(InName: string): align_translation_x;
        
            __tid_align_translation_x_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class align_translation_y extends UE.ToolMenuEntryScript {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): align_translation_y;
            static Load(InName: string): align_translation_y;
        
            __tid_align_translation_y_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class align_translation_z extends UE.ToolMenuEntryScript {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): align_translation_z;
            static Load(InName: string): align_translation_z;
        
            __tid_align_translation_z_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class AndroidPermissionDynamicDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): AndroidPermissionDynamicDelegate__PythonCallable;
            static Load(InName: string): AndroidPermissionDynamicDelegate__PythonCallable;
        
            __tid_AndroidPermissionDynamicDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class AnimDataModelModifiedDynamicEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): AnimDataModelModifiedDynamicEvent__PythonCallable;
            static Load(InName: string): AnimDataModelModifiedDynamicEvent__PythonCallable;
        
            __tid_AnimDataModelModifiedDynamicEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class AppleImageConversionDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): AppleImageConversionDelegate__PythonCallable;
            static Load(InName: string): AppleImageConversionDelegate__PythonCallable;
        
            __tid_AppleImageConversionDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ApplicationLifecycleComponent_ApplicationLifetimeDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ApplicationLifecycleComponent_ApplicationLifetimeDelegate__PythonCallable;
            static Load(InName: string): ApplicationLifecycleComponent_ApplicationLifetimeDelegate__PythonCallable;
        
            __tid_ApplicationLifecycleComponent_ApplicationLifetimeDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ApplicationLifecycleComponent_ApplicationStartupArgumentsDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ApplicationLifecycleComponent_ApplicationStartupArgumentsDelegate__PythonCallable;
            static Load(InName: string): ApplicationLifecycleComponent_ApplicationStartupArgumentsDelegate__PythonCallable;
        
            __tid_ApplicationLifecycleComponent_ApplicationStartupArgumentsDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ApplicationLifecycleComponent_OnLowPowerModeDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ApplicationLifecycleComponent_OnLowPowerModeDelegate__PythonCallable;
            static Load(InName: string): ApplicationLifecycleComponent_OnLowPowerModeDelegate__PythonCallable;
        
            __tid_ApplicationLifecycleComponent_OnLowPowerModeDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ApplicationLifecycleComponent_OnTemperatureChangeDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ApplicationLifecycleComponent_OnTemperatureChangeDelegate__PythonCallable;
            static Load(InName: string): ApplicationLifecycleComponent_OnTemperatureChangeDelegate__PythonCallable;
        
            __tid_ApplicationLifecycleComponent_OnTemperatureChangeDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class AsyncDelayComplete__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): AsyncDelayComplete__PythonCallable;
            static Load(InName: string): AsyncDelayComplete__PythonCallable;
        
            __tid_AsyncDelayComplete__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class AsyncEditorWaitForGameWorldEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): AsyncEditorWaitForGameWorldEvent__PythonCallable;
            static Load(InName: string): AsyncEditorWaitForGameWorldEvent__PythonCallable;
        
            __tid_AsyncEditorWaitForGameWorldEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class AsyncNiagaraCaptureSimCache_OnCaptureComplete__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): AsyncNiagaraCaptureSimCache_OnCaptureComplete__PythonCallable;
            static Load(InName: string): AsyncNiagaraCaptureSimCache_OnCaptureComplete__PythonCallable;
        
            __tid_AsyncNiagaraCaptureSimCache_OnCaptureComplete__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class AudioMeter_GetMeterChannelInfo__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): AudioMeter_GetMeterChannelInfo__PythonCallable;
            static Load(InName: string): AudioMeter_GetMeterChannelInfo__PythonCallable;
        
            __tid_AudioMeter_GetMeterChannelInfo__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class AudioOscilloscope_GetOscilloscopeAudioSamples__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): AudioOscilloscope_GetOscilloscopeAudioSamples__PythonCallable;
            static Load(InName: string): AudioOscilloscope_GetOscilloscopeAudioSamples__PythonCallable;
        
            __tid_AudioOscilloscope_GetOscilloscopeAudioSamples__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class AudioVectorscope_GetVectorscopeAudioSamples__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): AudioVectorscope_GetVectorscopeAudioSamples__PythonCallable;
            static Load(InName: string): AudioVectorscope_GetVectorscopeAudioSamples__PythonCallable;
        
            __tid_AudioVectorscope_GetVectorscopeAudioSamples__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class BlueprintFindSessionsResultDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BlueprintFindSessionsResultDelegate__PythonCallable;
            static Load(InName: string): BlueprintFindSessionsResultDelegate__PythonCallable;
        
            __tid_BlueprintFindSessionsResultDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class BreakEventSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BreakEventSignature__PythonCallable;
            static Load(InName: string): BreakEventSignature__PythonCallable;
        
            __tid_BreakEventSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class CharacterMovementUpdatedSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): CharacterMovementUpdatedSignature__PythonCallable;
            static Load(InName: string): CharacterMovementUpdatedSignature__PythonCallable;
        
            __tid_CharacterMovementUpdatedSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class CharacterReachedApexSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): CharacterReachedApexSignature__PythonCallable;
            static Load(InName: string): CharacterReachedApexSignature__PythonCallable;
        
            __tid_CharacterReachedApexSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class CollisionEventSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): CollisionEventSignature__PythonCallable;
            static Load(InName: string): CollisionEventSignature__PythonCallable;
        
            __tid_CollisionEventSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ComboBoxKey_GenerateWidgetEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ComboBoxKey_GenerateWidgetEvent__PythonCallable;
            static Load(InName: string): ComboBoxKey_GenerateWidgetEvent__PythonCallable;
        
            __tid_ComboBoxKey_GenerateWidgetEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ComboBoxKey_OnOpeningEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ComboBoxKey_OnOpeningEvent__PythonCallable;
            static Load(InName: string): ComboBoxKey_OnOpeningEvent__PythonCallable;
        
            __tid_ComboBoxKey_OnOpeningEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ComboBoxKey_OnSelectionChangedEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ComboBoxKey_OnSelectionChangedEvent__PythonCallable;
            static Load(InName: string): ComboBoxKey_OnSelectionChangedEvent__PythonCallable;
        
            __tid_ComboBoxKey_OnSelectionChangedEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ComboBoxString_OnOpeningEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ComboBoxString_OnOpeningEvent__PythonCallable;
            static Load(InName: string): ComboBoxString_OnOpeningEvent__PythonCallable;
        
            __tid_ComboBoxString_OnOpeningEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ComboBoxString_OnSelectionChangedEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ComboBoxString_OnSelectionChangedEvent__PythonCallable;
            static Load(InName: string): ComboBoxString_OnSelectionChangedEvent__PythonCallable;
        
            __tid_ComboBoxString_OnSelectionChangedEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ComponentBeginCursorOverSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ComponentBeginCursorOverSignature__PythonCallable;
            static Load(InName: string): ComponentBeginCursorOverSignature__PythonCallable;
        
            __tid_ComponentBeginCursorOverSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ComponentBeginOverlapSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ComponentBeginOverlapSignature__PythonCallable;
            static Load(InName: string): ComponentBeginOverlapSignature__PythonCallable;
        
            __tid_ComponentBeginOverlapSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ComponentBeginTouchOverSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ComponentBeginTouchOverSignature__PythonCallable;
            static Load(InName: string): ComponentBeginTouchOverSignature__PythonCallable;
        
            __tid_ComponentBeginTouchOverSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ComponentCollisionSettingsChangedSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ComponentCollisionSettingsChangedSignature__PythonCallable;
            static Load(InName: string): ComponentCollisionSettingsChangedSignature__PythonCallable;
        
            __tid_ComponentCollisionSettingsChangedSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ComponentEndCursorOverSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ComponentEndCursorOverSignature__PythonCallable;
            static Load(InName: string): ComponentEndCursorOverSignature__PythonCallable;
        
            __tid_ComponentEndCursorOverSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ComponentEndOverlapSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ComponentEndOverlapSignature__PythonCallable;
            static Load(InName: string): ComponentEndOverlapSignature__PythonCallable;
        
            __tid_ComponentEndOverlapSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ComponentEndTouchOverSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ComponentEndTouchOverSignature__PythonCallable;
            static Load(InName: string): ComponentEndTouchOverSignature__PythonCallable;
        
            __tid_ComponentEndTouchOverSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ComponentHitSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ComponentHitSignature__PythonCallable;
            static Load(InName: string): ComponentHitSignature__PythonCallable;
        
            __tid_ComponentHitSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ComponentOnClickedSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ComponentOnClickedSignature__PythonCallable;
            static Load(InName: string): ComponentOnClickedSignature__PythonCallable;
        
            __tid_ComponentOnClickedSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ComponentOnInputTouchBeginSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ComponentOnInputTouchBeginSignature__PythonCallable;
            static Load(InName: string): ComponentOnInputTouchBeginSignature__PythonCallable;
        
            __tid_ComponentOnInputTouchBeginSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ComponentOnInputTouchEndSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ComponentOnInputTouchEndSignature__PythonCallable;
            static Load(InName: string): ComponentOnInputTouchEndSignature__PythonCallable;
        
            __tid_ComponentOnInputTouchEndSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ComponentOnReleasedSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ComponentOnReleasedSignature__PythonCallable;
            static Load(InName: string): ComponentOnReleasedSignature__PythonCallable;
        
            __tid_ComponentOnReleasedSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ComponentPhysicsStateChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ComponentPhysicsStateChanged__PythonCallable;
            static Load(InName: string): ComponentPhysicsStateChanged__PythonCallable;
        
            __tid_ComponentPhysicsStateChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ComponentSleepSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ComponentSleepSignature__PythonCallable;
            static Load(InName: string): ComponentSleepSignature__PythonCallable;
        
            __tid_ComponentSleepSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ComponentWakeSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ComponentWakeSignature__PythonCallable;
            static Load(InName: string): ComponentWakeSignature__PythonCallable;
        
            __tid_ComponentWakeSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ConstraintBrokenSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ConstraintBrokenSignature__PythonCallable;
            static Load(InName: string): ConstraintBrokenSignature__PythonCallable;
        
            __tid_ConstraintBrokenSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ConstraintsManager_OnConstraintAdded__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ConstraintsManager_OnConstraintAdded__PythonCallable;
            static Load(InName: string): ConstraintsManager_OnConstraintAdded__PythonCallable;
        
            __tid_ConstraintsManager_OnConstraintAdded__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ConstraintsManager_OnConstraintRemoved__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ConstraintsManager_OnConstraintRemoved__PythonCallable;
            static Load(InName: string): ConstraintsManager_OnConstraintRemoved__PythonCallable;
        
            __tid_ConstraintsManager_OnConstraintRemoved__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ConstraintSubsystem_OnConstraintAddedToSystem__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ConstraintSubsystem_OnConstraintAddedToSystem__PythonCallable;
            static Load(InName: string): ConstraintSubsystem_OnConstraintAddedToSystem__PythonCallable;
        
            __tid_ConstraintSubsystem_OnConstraintAddedToSystem__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ConstraintSubsystem_OnConstraintRemovedFromSystem__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ConstraintSubsystem_OnConstraintRemovedFromSystem__PythonCallable;
            static Load(InName: string): ConstraintSubsystem_OnConstraintRemovedFromSystem__PythonCallable;
        
            __tid_ConstraintSubsystem_OnConstraintRemovedFromSystem__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ControlRig_OnControlSelectedBP__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ControlRig_OnControlSelectedBP__PythonCallable;
            static Load(InName: string): ControlRig_OnControlSelectedBP__PythonCallable;
        
            __tid_ControlRig_OnControlSelectedBP__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ControlRigComponentDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ControlRigComponentDelegate__PythonCallable;
            static Load(InName: string): ControlRigComponentDelegate__PythonCallable;
        
            __tid_ControlRigComponentDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class CrumblingEventSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): CrumblingEventSignature__PythonCallable;
            static Load(InName: string): CrumblingEventSignature__PythonCallable;
        
            __tid_CrumblingEventSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class CustomWidgetNavigationDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): CustomWidgetNavigationDelegate__PythonCallable;
            static Load(InName: string): CustomWidgetNavigationDelegate__PythonCallable;
        
            __tid_CustomWidgetNavigationDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class DataDrivenCVarEngineSubsystem_OnDataDrivenCVarChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): DataDrivenCVarEngineSubsystem_OnDataDrivenCVarChanged__PythonCallable;
            static Load(InName: string): DataDrivenCVarEngineSubsystem_OnDataDrivenCVarChanged__PythonCallable;
        
            __tid_DataDrivenCVarEngineSubsystem_OnDataDrivenCVarChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class DirectoryWatcherCallback__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): DirectoryWatcherCallback__PythonCallable;
            static Load(InName: string): DirectoryWatcherCallback__PythonCallable;
        
            __tid_DirectoryWatcherCallback__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class do_rename_dialog extends UE.Object {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            start_num: number;
            newName: string;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): do_rename_dialog;
            static Load(InName: string): do_rename_dialog;
        
            __tid_do_rename_dialog_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class do_rename_entry extends UE.ToolMenuEntryScript {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): do_rename_entry;
            static Load(InName: string): do_rename_entry;
        
            __tid_do_rename_entry_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class DownloadImageDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): DownloadImageDelegate__PythonCallable;
            static Load(InName: string): DownloadImageDelegate__PythonCallable;
        
            __tid_DownloadImageDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class EditableText_OnEditableTextChangedEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): EditableText_OnEditableTextChangedEvent__PythonCallable;
            static Load(InName: string): EditableText_OnEditableTextChangedEvent__PythonCallable;
        
            __tid_EditableText_OnEditableTextChangedEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class EditableText_OnEditableTextCommittedEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): EditableText_OnEditableTextCommittedEvent__PythonCallable;
            static Load(InName: string): EditableText_OnEditableTextCommittedEvent__PythonCallable;
        
            __tid_EditableText_OnEditableTextCommittedEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class EditableTextBox_OnEditableTextBoxChangedEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): EditableTextBox_OnEditableTextBoxChangedEvent__PythonCallable;
            static Load(InName: string): EditableTextBox_OnEditableTextBoxChangedEvent__PythonCallable;
        
            __tid_EditableTextBox_OnEditableTextBoxChangedEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class EditableTextBox_OnEditableTextBoxCommittedEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): EditableTextBox_OnEditableTextBoxCommittedEvent__PythonCallable;
            static Load(InName: string): EditableTextBox_OnEditableTextBoxCommittedEvent__PythonCallable;
        
            __tid_EditableTextBox_OnEditableTextBoxCommittedEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class EditorAssetSubsystem_OnExtractAssetFromFileDynamic__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): EditorAssetSubsystem_OnExtractAssetFromFileDynamic__PythonCallable;
            static Load(InName: string): EditorAssetSubsystem_OnExtractAssetFromFileDynamic__PythonCallable;
        
            __tid_EditorAssetSubsystem_OnExtractAssetFromFileDynamic__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class EmptyOnlineDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): EmptyOnlineDelegate__PythonCallable;
            static Load(InName: string): EmptyOnlineDelegate__PythonCallable;
        
            __tid_EmptyOnlineDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class EnhancedInputActionHandlerDynamicSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): EnhancedInputActionHandlerDynamicSignature__PythonCallable;
            static Load(InName: string): EnhancedInputActionHandlerDynamicSignature__PythonCallable;
        
            __tid_EnhancedInputActionHandlerDynamicSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class EnhancedInputLocalPlayerSubsystem_OnControlMappingsRebuilt__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): EnhancedInputLocalPlayerSubsystem_OnControlMappingsRebuilt__PythonCallable;
            static Load(InName: string): EnhancedInputLocalPlayerSubsystem_OnControlMappingsRebuilt__PythonCallable;
        
            __tid_EnhancedInputLocalPlayerSubsystem_OnControlMappingsRebuilt__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class EnhancedInputUserSettings_EnhancedInputUserSettingsApplied__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): EnhancedInputUserSettings_EnhancedInputUserSettingsApplied__PythonCallable;
            static Load(InName: string): EnhancedInputUserSettings_EnhancedInputUserSettingsApplied__PythonCallable;
        
            __tid_EnhancedInputUserSettings_EnhancedInputUserSettingsApplied__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class EnhancedInputUserSettings_EnhancedInputUserSettingsChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): EnhancedInputUserSettings_EnhancedInputUserSettingsChanged__PythonCallable;
            static Load(InName: string): EnhancedInputUserSettings_EnhancedInputUserSettingsChanged__PythonCallable;
        
            __tid_EnhancedInputUserSettings_EnhancedInputUserSettingsChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class EnhancedInputUserSettings_MappableKeyProfileChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): EnhancedInputUserSettings_MappableKeyProfileChanged__PythonCallable;
            static Load(InName: string): EnhancedInputUserSettings_MappableKeyProfileChanged__PythonCallable;
        
            __tid_EnhancedInputUserSettings_MappableKeyProfileChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class EnhancedInputUserSettings_MappingContextRegisteredWithSettings__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): EnhancedInputUserSettings_MappingContextRegisteredWithSettings__PythonCallable;
            static Load(InName: string): EnhancedInputUserSettings_MappingContextRegisteredWithSettings__PythonCallable;
        
            __tid_EnhancedInputUserSettings_MappingContextRegisteredWithSettings__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class EnvQueryInstanceBlueprintWrapper_EQSQueryDoneSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): EnvQueryInstanceBlueprintWrapper_EQSQueryDoneSignature__PythonCallable;
            static Load(InName: string): EnvQueryInstanceBlueprintWrapper_EQSQueryDoneSignature__PythonCallable;
        
            __tid_EnvQueryInstanceBlueprintWrapper_EQSQueryDoneSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class FieldValueChangedDynamicDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): FieldValueChangedDynamicDelegate__PythonCallable;
            static Load(InName: string): FieldValueChangedDynamicDelegate__PythonCallable;
        
            __tid_FieldValueChangedDynamicDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class FlipbookFinishedPlaySignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): FlipbookFinishedPlaySignature__PythonCallable;
            static Load(InName: string): FlipbookFinishedPlaySignature__PythonCallable;
        
            __tid_FlipbookFinishedPlaySignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ForEachActorIteratorSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ForEachActorIteratorSignature__PythonCallable;
            static Load(InName: string): ForEachActorIteratorSignature__PythonCallable;
        
            __tid_ForEachActorIteratorSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ForEachAssetIteratorSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ForEachAssetIteratorSignature__PythonCallable;
            static Load(InName: string): ForEachAssetIteratorSignature__PythonCallable;
        
            __tid_ForEachAssetIteratorSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class FunctionalTestAISpawned__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): FunctionalTestAISpawned__PythonCallable;
            static Load(InName: string): FunctionalTestAISpawned__PythonCallable;
        
            __tid_FunctionalTestAISpawned__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class FunctionalTestEventSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): FunctionalTestEventSignature__PythonCallable;
            static Load(InName: string): FunctionalTestEventSignature__PythonCallable;
        
            __tid_FunctionalTestEventSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class GameplayTask_GenericGameplayTaskDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): GameplayTask_GenericGameplayTaskDelegate__PythonCallable;
            static Load(InName: string): GameplayTask_GenericGameplayTaskDelegate__PythonCallable;
        
            __tid_GameplayTask_GenericGameplayTaskDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class GameplayTask_TimeLimitedExecution_TaskFinishDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): GameplayTask_TimeLimitedExecution_TaskFinishDelegate__PythonCallable;
            static Load(InName: string): GameplayTask_TimeLimitedExecution_TaskFinishDelegate__PythonCallable;
        
            __tid_GameplayTask_TimeLimitedExecution_TaskFinishDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class GameplayTask_WaitDelay_TaskDelayDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): GameplayTask_WaitDelay_TaskDelayDelegate__PythonCallable;
            static Load(InName: string): GameplayTask_WaitDelay_TaskDelayDelegate__PythonCallable;
        
            __tid_GameplayTask_WaitDelay_TaskDelayDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class GameplayTaskSpawnActorDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): GameplayTaskSpawnActorDelegate__PythonCallable;
            static Load(InName: string): GameplayTaskSpawnActorDelegate__PythonCallable;
        
            __tid_GameplayTaskSpawnActorDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class GeometryCollectionComponent_NotifyGeometryCollectionPhysicsLoadingStateChange__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): GeometryCollectionComponent_NotifyGeometryCollectionPhysicsLoadingStateChange__PythonCallable;
            static Load(InName: string): GeometryCollectionComponent_NotifyGeometryCollectionPhysicsLoadingStateChange__PythonCallable;
        
            __tid_GeometryCollectionComponent_NotifyGeometryCollectionPhysicsLoadingStateChange__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class GeometryCollectionComponent_NotifyGeometryCollectionPhysicsStateChange__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): GeometryCollectionComponent_NotifyGeometryCollectionPhysicsStateChange__PythonCallable;
            static Load(InName: string): GeometryCollectionComponent_NotifyGeometryCollectionPhysicsStateChange__PythonCallable;
        
            __tid_GeometryCollectionComponent_NotifyGeometryCollectionPhysicsStateChange__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class GetHighlightTextDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): GetHighlightTextDelegate__PythonCallable;
            static Load(InName: string): GetHighlightTextDelegate__PythonCallable;
        
            __tid_GetHighlightTextDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class HardwareInputDeviceChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): HardwareInputDeviceChanged__PythonCallable;
            static Load(InName: string): HardwareInputDeviceChanged__PythonCallable;
        
            __tid_HardwareInputDeviceChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class import_ik_rig_options extends UE.Object {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            create_transform_nodes_for_effectors: boolean;
            import_effectors: boolean;
            import_excluded_bones: boolean;
            import_bone_settings: boolean;
            ik_rig: UE.IKRigDefinition;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): import_ik_rig_options;
            static Load(InName: string): import_ik_rig_options;
        
            __tid_import_ik_rig_options_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ImportSubsystem_OnAssetPostImport_Dyn__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ImportSubsystem_OnAssetPostImport_Dyn__PythonCallable;
            static Load(InName: string): ImportSubsystem_OnAssetPostImport_Dyn__PythonCallable;
        
            __tid_ImportSubsystem_OnAssetPostImport_Dyn__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ImportSubsystem_OnAssetPostLODImport_Dyn__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ImportSubsystem_OnAssetPostLODImport_Dyn__PythonCallable;
            static Load(InName: string): ImportSubsystem_OnAssetPostLODImport_Dyn__PythonCallable;
        
            __tid_ImportSubsystem_OnAssetPostLODImport_Dyn__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ImportSubsystem_OnAssetPreImport_Dyn__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ImportSubsystem_OnAssetPreImport_Dyn__PythonCallable;
            static Load(InName: string): ImportSubsystem_OnAssetPreImport_Dyn__PythonCallable;
        
            __tid_ImportSubsystem_OnAssetPreImport_Dyn__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ImportSubsystem_OnAssetReimport_Dyn__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ImportSubsystem_OnAssetReimport_Dyn__PythonCallable;
            static Load(InName: string): ImportSubsystem_OnAssetReimport_Dyn__PythonCallable;
        
            __tid_ImportSubsystem_OnAssetReimport_Dyn__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class InAppPurchaseQuery2Result__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): InAppPurchaseQuery2Result__PythonCallable;
            static Load(InName: string): InAppPurchaseQuery2Result__PythonCallable;
        
            __tid_InAppPurchaseQuery2Result__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class InAppPurchaseRestoreResult2__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): InAppPurchaseRestoreResult2__PythonCallable;
            static Load(InName: string): InAppPurchaseRestoreResult2__PythonCallable;
        
            __tid_InAppPurchaseRestoreResult2__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class InAppPurchaseResult2__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): InAppPurchaseResult2__PythonCallable;
            static Load(InName: string): InAppPurchaseResult2__PythonCallable;
        
            __tid_InAppPurchaseResult2__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class InputActionHandlerDynamicSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): InputActionHandlerDynamicSignature__PythonCallable;
            static Load(InName: string): InputActionHandlerDynamicSignature__PythonCallable;
        
            __tid_InputActionHandlerDynamicSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class InputAxisHandlerDynamicSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): InputAxisHandlerDynamicSignature__PythonCallable;
            static Load(InName: string): InputAxisHandlerDynamicSignature__PythonCallable;
        
            __tid_InputAxisHandlerDynamicSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class InputDebugKeyHandlerDynamicSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): InputDebugKeyHandlerDynamicSignature__PythonCallable;
            static Load(InName: string): InputDebugKeyHandlerDynamicSignature__PythonCallable;
        
            __tid_InputDebugKeyHandlerDynamicSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class InputGestureHandlerDynamicSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): InputGestureHandlerDynamicSignature__PythonCallable;
            static Load(InName: string): InputGestureHandlerDynamicSignature__PythonCallable;
        
            __tid_InputGestureHandlerDynamicSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class InputKeySelector_OnIsSelectingKeyChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): InputKeySelector_OnIsSelectingKeyChanged__PythonCallable;
            static Load(InName: string): InputKeySelector_OnIsSelectingKeyChanged__PythonCallable;
        
            __tid_InputKeySelector_OnIsSelectingKeyChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class InputKeySelector_OnKeySelected__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): InputKeySelector_OnKeySelected__PythonCallable;
            static Load(InName: string): InputKeySelector_OnKeySelected__PythonCallable;
        
            __tid_InputKeySelector_OnKeySelected__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class InputTouchHandlerDynamicSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): InputTouchHandlerDynamicSignature__PythonCallable;
            static Load(InName: string): InputTouchHandlerDynamicSignature__PythonCallable;
        
            __tid_InputTouchHandlerDynamicSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class InputVectorAxisHandlerDynamicSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): InputVectorAxisHandlerDynamicSignature__PythonCallable;
            static Load(InName: string): InputVectorAxisHandlerDynamicSignature__PythonCallable;
        
            __tid_InputVectorAxisHandlerDynamicSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class InstancePointDamageSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): InstancePointDamageSignature__PythonCallable;
            static Load(InName: string): InstancePointDamageSignature__PythonCallable;
        
            __tid_InstancePointDamageSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class InstanceRadialDamageSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): InstanceRadialDamageSignature__PythonCallable;
            static Load(InName: string): InstanceRadialDamageSignature__PythonCallable;
        
            __tid_InstanceRadialDamageSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class InstigatedAnyDamageSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): InstigatedAnyDamageSignature__PythonCallable;
            static Load(InName: string): InstigatedAnyDamageSignature__PythonCallable;
        
            __tid_InstigatedAnyDamageSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class InterpToMovementComponent_OnInterpToResetDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): InterpToMovementComponent_OnInterpToResetDelegate__PythonCallable;
            static Load(InName: string): InterpToMovementComponent_OnInterpToResetDelegate__PythonCallable;
        
            __tid_InterpToMovementComponent_OnInterpToResetDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class InterpToMovementComponent_OnInterpToReverseDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): InterpToMovementComponent_OnInterpToReverseDelegate__PythonCallable;
            static Load(InName: string): InterpToMovementComponent_OnInterpToReverseDelegate__PythonCallable;
        
            __tid_InterpToMovementComponent_OnInterpToReverseDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class InterpToMovementComponent_OnInterpToStopDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): InterpToMovementComponent_OnInterpToStopDelegate__PythonCallable;
            static Load(InName: string): InterpToMovementComponent_OnInterpToStopDelegate__PythonCallable;
        
            __tid_InterpToMovementComponent_OnInterpToStopDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class InterpToMovementComponent_OnInterpToWaitBeginDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): InterpToMovementComponent_OnInterpToWaitBeginDelegate__PythonCallable;
            static Load(InName: string): InterpToMovementComponent_OnInterpToWaitBeginDelegate__PythonCallable;
        
            __tid_InterpToMovementComponent_OnInterpToWaitBeginDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class InterpToMovementComponent_OnInterpToWaitEndDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): InterpToMovementComponent_OnInterpToWaitEndDelegate__PythonCallable;
            static Load(InName: string): InterpToMovementComponent_OnInterpToWaitEndDelegate__PythonCallable;
        
            __tid_InterpToMovementComponent_OnInterpToWaitEndDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class IsRootComponentChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): IsRootComponentChanged__PythonCallable;
            static Load(InName: string): IsRootComponentChanged__PythonCallable;
        
            __tid_IsRootComponentChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class LandedSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): LandedSignature__PythonCallable;
            static Load(InName: string): LandedSignature__PythonCallable;
        
            __tid_LandedSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class LeaderboardQueryResult__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): LeaderboardQueryResult__PythonCallable;
            static Load(InName: string): LeaderboardQueryResult__PythonCallable;
        
            __tid_LeaderboardQueryResult__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class LevelSequenceActor_OnLevelSequenceLoaded__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): LevelSequenceActor_OnLevelSequenceLoaded__PythonCallable;
            static Load(InName: string): LevelSequenceActor_OnLevelSequenceLoaded__PythonCallable;
        
            __tid_LevelSequenceActor_OnLevelSequenceLoaded__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class LevelStreamingLoadedStatus__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): LevelStreamingLoadedStatus__PythonCallable;
            static Load(InName: string): LevelStreamingLoadedStatus__PythonCallable;
        
            __tid_LevelStreamingLoadedStatus__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class LevelStreamingVisibilityStatus__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): LevelStreamingVisibilityStatus__PythonCallable;
            static Load(InName: string): LevelStreamingVisibilityStatus__PythonCallable;
        
            __tid_LevelStreamingVisibilityStatus__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class LocationServicesData_OnLocationChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): LocationServicesData_OnLocationChanged__PythonCallable;
            static Load(InName: string): LocationServicesData_OnLocationChanged__PythonCallable;
        
            __tid_LocationServicesData_OnLocationChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class MenuAnchor_GetUserWidget__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): MenuAnchor_GetUserWidget__PythonCallable;
            static Load(InName: string): MenuAnchor_GetUserWidget__PythonCallable;
        
            __tid_MenuAnchor_GetUserWidget__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class MockDataMeshTrackerComponent_OnMockDataMeshTrackerUpdated__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): MockDataMeshTrackerComponent_OnMockDataMeshTrackerUpdated__PythonCallable;
            static Load(InName: string): MockDataMeshTrackerComponent_OnMockDataMeshTrackerUpdated__PythonCallable;
        
            __tid_MockDataMeshTrackerComponent_OnMockDataMeshTrackerUpdated__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class MovementModeChangedSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): MovementModeChangedSignature__PythonCallable;
            static Load(InName: string): MovementModeChangedSignature__PythonCallable;
        
            __tid_MovementModeChangedSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class MoveTaskCompletedSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): MoveTaskCompletedSignature__PythonCallable;
            static Load(InName: string): MoveTaskCompletedSignature__PythonCallable;
        
            __tid_MoveTaskCompletedSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class MovieSceneActorPredictionFailure__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): MovieSceneActorPredictionFailure__PythonCallable;
            static Load(InName: string): MovieSceneActorPredictionFailure__PythonCallable;
        
            __tid_MovieSceneActorPredictionFailure__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class MovieSceneActorPredictionResult__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): MovieSceneActorPredictionResult__PythonCallable;
            static Load(InName: string): MovieSceneActorPredictionResult__PythonCallable;
        
            __tid_MovieSceneActorPredictionResult__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class MultiLineEditableText_OnMultiLineEditableTextChangedEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): MultiLineEditableText_OnMultiLineEditableTextChangedEvent__PythonCallable;
            static Load(InName: string): MultiLineEditableText_OnMultiLineEditableTextChangedEvent__PythonCallable;
        
            __tid_MultiLineEditableText_OnMultiLineEditableTextChangedEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class MultiLineEditableText_OnMultiLineEditableTextCommittedEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): MultiLineEditableText_OnMultiLineEditableTextCommittedEvent__PythonCallable;
            static Load(InName: string): MultiLineEditableText_OnMultiLineEditableTextCommittedEvent__PythonCallable;
        
            __tid_MultiLineEditableText_OnMultiLineEditableTextCommittedEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class MultiLineEditableTextBox_OnMultiLineEditableTextBoxChangedEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): MultiLineEditableTextBox_OnMultiLineEditableTextBoxChangedEvent__PythonCallable;
            static Load(InName: string): MultiLineEditableTextBox_OnMultiLineEditableTextBoxChangedEvent__PythonCallable;
        
            __tid_MultiLineEditableTextBox_OnMultiLineEditableTextBoxChangedEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class MultiLineEditableTextBox_OnMultiLineEditableTextBoxCommittedEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): MultiLineEditableTextBox_OnMultiLineEditableTextBoxCommittedEvent__PythonCallable;
            static Load(InName: string): MultiLineEditableTextBox_OnMultiLineEditableTextBoxCommittedEvent__PythonCallable;
        
            __tid_MultiLineEditableTextBox_OnMultiLineEditableTextBoxCommittedEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class NiagaraClipboardFunction_OnPastedFunctionCallNode__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): NiagaraClipboardFunction_OnPastedFunctionCallNode__PythonCallable;
            static Load(InName: string): NiagaraClipboardFunction_OnPastedFunctionCallNode__PythonCallable;
        
            __tid_NiagaraClipboardFunction_OnPastedFunctionCallNode__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class NumTablesChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): NumTablesChanged__PythonCallable;
            static Load(InName: string): NumTablesChanged__PythonCallable;
        
            __tid_NumTablesChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OAISimpleDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OAISimpleDelegate__PythonCallable;
            static Load(InName: string): OAISimpleDelegate__PythonCallable;
        
            __tid_OAISimpleDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnActorReady__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnActorReady__PythonCallable;
            static Load(InName: string): OnActorReady__PythonCallable;
        
            __tid_OnActorReady__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnAllMontageInstancesEndedMCDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnAllMontageInstancesEndedMCDelegate__PythonCallable;
            static Load(InName: string): OnAllMontageInstancesEndedMCDelegate__PythonCallable;
        
            __tid_OnAllMontageInstancesEndedMCDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnAnimInitialized__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnAnimInitialized__PythonCallable;
            static Load(InName: string): OnAnimInitialized__PythonCallable;
        
            __tid_OnAnimInitialized__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnAsyncCaptureSceneComplete__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnAsyncCaptureSceneComplete__PythonCallable;
            static Load(InName: string): OnAsyncCaptureSceneComplete__PythonCallable;
        
            __tid_OnAsyncCaptureSceneComplete__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnAsyncHandleSaveGame__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnAsyncHandleSaveGame__PythonCallable;
            static Load(InName: string): OnAsyncHandleSaveGame__PythonCallable;
        
            __tid_OnAsyncHandleSaveGame__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnAudioDefaultDeviceChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnAudioDefaultDeviceChanged__PythonCallable;
            static Load(InName: string): OnAudioDefaultDeviceChanged__PythonCallable;
        
            __tid_OnAudioDefaultDeviceChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnAudioDeviceChange__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnAudioDeviceChange__PythonCallable;
            static Load(InName: string): OnAudioDeviceChange__PythonCallable;
        
            __tid_OnAudioDeviceChange__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnAudioDeviceStateChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnAudioDeviceStateChanged__PythonCallable;
            static Load(InName: string): OnAudioDeviceStateChanged__PythonCallable;
        
            __tid_OnAudioDeviceStateChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnAudioFadeChangeSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnAudioFadeChangeSignature__PythonCallable;
            static Load(InName: string): OnAudioFadeChangeSignature__PythonCallable;
        
            __tid_OnAudioFadeChangeSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnAudioFinished__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnAudioFinished__PythonCallable;
            static Load(InName: string): OnAudioFinished__PythonCallable;
        
            __tid_OnAudioFinished__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnAudioInputDevicesObtained__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnAudioInputDevicesObtained__PythonCallable;
            static Load(InName: string): OnAudioInputDevicesObtained__PythonCallable;
        
            __tid_OnAudioInputDevicesObtained__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnAudioMultiEnvelopeValue__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnAudioMultiEnvelopeValue__PythonCallable;
            static Load(InName: string): OnAudioMultiEnvelopeValue__PythonCallable;
        
            __tid_OnAudioMultiEnvelopeValue__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnAudioOutputDevicesObtained__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnAudioOutputDevicesObtained__PythonCallable;
            static Load(InName: string): OnAudioOutputDevicesObtained__PythonCallable;
        
            __tid_OnAudioOutputDevicesObtained__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnAudioPlaybackPercent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnAudioPlaybackPercent__PythonCallable;
            static Load(InName: string): OnAudioPlaybackPercent__PythonCallable;
        
            __tid_OnAudioPlaybackPercent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnAudioPlayStateChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnAudioPlayStateChanged__PythonCallable;
            static Load(InName: string): OnAudioPlayStateChanged__PythonCallable;
        
            __tid_OnAudioPlayStateChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnAudioRadialSliderValueChangedEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnAudioRadialSliderValueChangedEvent__PythonCallable;
            static Load(InName: string): OnAudioRadialSliderValueChangedEvent__PythonCallable;
        
            __tid_OnAudioRadialSliderValueChangedEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnAudioSingleEnvelopeValue__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnAudioSingleEnvelopeValue__PythonCallable;
            static Load(InName: string): OnAudioSingleEnvelopeValue__PythonCallable;
        
            __tid_OnAudioSingleEnvelopeValue__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnAudioVirtualizationChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnAudioVirtualizationChanged__PythonCallable;
            static Load(InName: string): OnAudioVirtualizationChanged__PythonCallable;
        
            __tid_OnAudioVirtualizationChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnBoneTransformsFinalized__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnBoneTransformsFinalized__PythonCallable;
            static Load(InName: string): OnBoneTransformsFinalized__PythonCallable;
        
            __tid_OnBoneTransformsFinalized__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnButtonClickedEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnButtonClickedEvent__PythonCallable;
            static Load(InName: string): OnButtonClickedEvent__PythonCallable;
        
            __tid_OnButtonClickedEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnButtonHoverEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnButtonHoverEvent__PythonCallable;
            static Load(InName: string): OnButtonHoverEvent__PythonCallable;
        
            __tid_OnButtonHoverEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnButtonPressedEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnButtonPressedEvent__PythonCallable;
            static Load(InName: string): OnButtonPressedEvent__PythonCallable;
        
            __tid_OnButtonPressedEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnButtonReleasedEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnButtonReleasedEvent__PythonCallable;
            static Load(InName: string): OnButtonReleasedEvent__PythonCallable;
        
            __tid_OnButtonReleasedEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnCanvasRenderTargetUpdate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnCanvasRenderTargetUpdate__PythonCallable;
            static Load(InName: string): OnCanvasRenderTargetUpdate__PythonCallable;
        
            __tid_OnCanvasRenderTargetUpdate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnChaosBreakEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnChaosBreakEvent__PythonCallable;
            static Load(InName: string): OnChaosBreakEvent__PythonCallable;
        
            __tid_OnChaosBreakEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnChaosBreakingEvents__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnChaosBreakingEvents__PythonCallable;
            static Load(InName: string): OnChaosBreakingEvents__PythonCallable;
        
            __tid_OnChaosBreakingEvents__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnChaosCollisionEvents__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnChaosCollisionEvents__PythonCallable;
            static Load(InName: string): OnChaosCollisionEvents__PythonCallable;
        
            __tid_OnChaosCollisionEvents__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnChaosCrumblingEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnChaosCrumblingEvent__PythonCallable;
            static Load(InName: string): OnChaosCrumblingEvent__PythonCallable;
        
            __tid_OnChaosCrumblingEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnChaosPhysicsCollision__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnChaosPhysicsCollision__PythonCallable;
            static Load(InName: string): OnChaosPhysicsCollision__PythonCallable;
        
            __tid_OnChaosPhysicsCollision__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnChaosRemovalEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnChaosRemovalEvent__PythonCallable;
            static Load(InName: string): OnChaosRemovalEvent__PythonCallable;
        
            __tid_OnChaosRemovalEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnChaosRemovalEvents__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnChaosRemovalEvents__PythonCallable;
            static Load(InName: string): OnChaosRemovalEvents__PythonCallable;
        
            __tid_OnChaosRemovalEvents__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnChaosTrailingEvents__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnChaosTrailingEvents__PythonCallable;
            static Load(InName: string): OnChaosTrailingEvents__PythonCallable;
        
            __tid_OnChaosTrailingEvents__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnCheckBoxComponentStateChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnCheckBoxComponentStateChanged__PythonCallable;
            static Load(InName: string): OnCheckBoxComponentStateChanged__PythonCallable;
        
            __tid_OnCheckBoxComponentStateChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnClaimedResourcesChangeSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnClaimedResourcesChangeSignature__PythonCallable;
            static Load(InName: string): OnClaimedResourcesChangeSignature__PythonCallable;
        
            __tid_OnClaimedResourcesChangeSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnClusterUnionAddedComponent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnClusterUnionAddedComponent__PythonCallable;
            static Load(InName: string): OnClusterUnionAddedComponent__PythonCallable;
        
            __tid_OnClusterUnionAddedComponent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnClusterUnionBoundsChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnClusterUnionBoundsChanged__PythonCallable;
            static Load(InName: string): OnClusterUnionBoundsChanged__PythonCallable;
        
            __tid_OnClusterUnionBoundsChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnClusterUnionRemovedComponent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnClusterUnionRemovedComponent__PythonCallable;
            static Load(InName: string): OnClusterUnionRemovedComponent__PythonCallable;
        
            __tid_OnClusterUnionRemovedComponent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnCompletedDeviceSwap__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnCompletedDeviceSwap__PythonCallable;
            static Load(InName: string): OnCompletedDeviceSwap__PythonCallable;
        
            __tid_OnCompletedDeviceSwap__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnConstantQResults__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnConstantQResults__PythonCallable;
            static Load(InName: string): OnConstantQResults__PythonCallable;
        
            __tid_OnConstantQResults__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnConstructEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnConstructEvent__PythonCallable;
            static Load(InName: string): OnConstructEvent__PythonCallable;
        
            __tid_OnConstructEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnContentInstallFailed__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnContentInstallFailed__PythonCallable;
            static Load(InName: string): OnContentInstallFailed__PythonCallable;
        
            __tid_OnContentInstallFailed__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnContentInstallSucceeded__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnContentInstallSucceeded__PythonCallable;
            static Load(InName: string): OnContentInstallSucceeded__PythonCallable;
        
            __tid_OnContentInstallSucceeded__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnControllerCaptureBeginEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnControllerCaptureBeginEvent__PythonCallable;
            static Load(InName: string): OnControllerCaptureBeginEvent__PythonCallable;
        
            __tid_OnControllerCaptureBeginEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnControllerCaptureBeginEventSynth2D__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnControllerCaptureBeginEventSynth2D__PythonCallable;
            static Load(InName: string): OnControllerCaptureBeginEventSynth2D__PythonCallable;
        
            __tid_OnControllerCaptureBeginEventSynth2D__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnControllerCaptureEndEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnControllerCaptureEndEvent__PythonCallable;
            static Load(InName: string): OnControllerCaptureEndEvent__PythonCallable;
        
            __tid_OnControllerCaptureEndEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnControllerCaptureEndEventSynth2D__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnControllerCaptureEndEventSynth2D__PythonCallable;
            static Load(InName: string): OnControllerCaptureEndEventSynth2D__PythonCallable;
        
            __tid_OnControllerCaptureEndEventSynth2D__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnCreateAuditionGeneratorHandleDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnCreateAuditionGeneratorHandleDelegate__PythonCallable;
            static Load(InName: string): OnCreateAuditionGeneratorHandleDelegate__PythonCallable;
        
            __tid_OnCreateAuditionGeneratorHandleDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnDataLayerInstanceRuntimeStateChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnDataLayerInstanceRuntimeStateChanged__PythonCallable;
            static Load(InName: string): OnDataLayerInstanceRuntimeStateChanged__PythonCallable;
        
            __tid_OnDataLayerInstanceRuntimeStateChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnDataLayerRuntimeStateChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnDataLayerRuntimeStateChanged__PythonCallable;
            static Load(InName: string): OnDataLayerRuntimeStateChanged__PythonCallable;
        
            __tid_OnDataLayerRuntimeStateChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnDeleteActorsBegin__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnDeleteActorsBegin__PythonCallable;
            static Load(InName: string): OnDeleteActorsBegin__PythonCallable;
        
            __tid_OnDeleteActorsBegin__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnDeleteActorsEnd__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnDeleteActorsEnd__PythonCallable;
            static Load(InName: string): OnDeleteActorsEnd__PythonCallable;
        
            __tid_OnDeleteActorsEnd__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnDragDropMulticast__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnDragDropMulticast__PythonCallable;
            static Load(InName: string): OnDragDropMulticast__PythonCallable;
        
            __tid_OnDragDropMulticast__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnDuplicateActorsBegin__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnDuplicateActorsBegin__PythonCallable;
            static Load(InName: string): OnDuplicateActorsBegin__PythonCallable;
        
            __tid_OnDuplicateActorsBegin__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnDuplicateActorsEnd__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnDuplicateActorsEnd__PythonCallable;
            static Load(InName: string): OnDuplicateActorsEnd__PythonCallable;
        
            __tid_OnDuplicateActorsEnd__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnDynamicMeshModifiedBP__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnDynamicMeshModifiedBP__PythonCallable;
            static Load(InName: string): OnDynamicMeshModifiedBP__PythonCallable;
        
            __tid_OnDynamicMeshModifiedBP__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnEditCopyActorsBegin__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnEditCopyActorsBegin__PythonCallable;
            static Load(InName: string): OnEditCopyActorsBegin__PythonCallable;
        
            __tid_OnEditCopyActorsBegin__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnEditCopyActorsEnd__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnEditCopyActorsEnd__PythonCallable;
            static Load(InName: string): OnEditCopyActorsEnd__PythonCallable;
        
            __tid_OnEditCopyActorsEnd__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnEditCutActorsBegin__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnEditCutActorsBegin__PythonCallable;
            static Load(InName: string): OnEditCutActorsBegin__PythonCallable;
        
            __tid_OnEditCutActorsBegin__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnEditCutActorsEnd__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnEditCutActorsEnd__PythonCallable;
            static Load(InName: string): OnEditCutActorsEnd__PythonCallable;
        
            __tid_OnEditCutActorsEnd__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnEditNewActorsDropped__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnEditNewActorsDropped__PythonCallable;
            static Load(InName: string): OnEditNewActorsDropped__PythonCallable;
        
            __tid_OnEditNewActorsDropped__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnEditNewActorsPlaced__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnEditNewActorsPlaced__PythonCallable;
            static Load(InName: string): OnEditNewActorsPlaced__PythonCallable;
        
            __tid_OnEditNewActorsPlaced__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnEditorUtilityPIEEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnEditorUtilityPIEEvent__PythonCallable;
            static Load(InName: string): OnEditorUtilityPIEEvent__PythonCallable;
        
            __tid_OnEditorUtilityPIEEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnEditorUtilityTaskDynamicDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnEditorUtilityTaskDynamicDelegate__PythonCallable;
            static Load(InName: string): OnEditorUtilityTaskDynamicDelegate__PythonCallable;
        
            __tid_OnEditorUtilityTaskDynamicDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnEditPasteActorsBegin__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnEditPasteActorsBegin__PythonCallable;
            static Load(InName: string): OnEditPasteActorsBegin__PythonCallable;
        
            __tid_OnEditPasteActorsBegin__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnEditPasteActorsEnd__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnEditPasteActorsEnd__PythonCallable;
            static Load(InName: string): OnEditPasteActorsEnd__PythonCallable;
        
            __tid_OnEditPasteActorsEnd__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnEnvelopeFollowerUpdate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnEnvelopeFollowerUpdate__PythonCallable;
            static Load(InName: string): OnEnvelopeFollowerUpdate__PythonCallable;
        
            __tid_OnEnvelopeFollowerUpdate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnExpandableAreaExpansionChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnExpandableAreaExpansionChanged__PythonCallable;
            static Load(InName: string): OnExpandableAreaExpansionChanged__PythonCallable;
        
            __tid_OnExpandableAreaExpansionChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnExportImageAsyncComplete__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnExportImageAsyncComplete__PythonCallable;
            static Load(InName: string): OnExportImageAsyncComplete__PythonCallable;
        
            __tid_OnExportImageAsyncComplete__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnFloatValueChangedEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnFloatValueChangedEvent__PythonCallable;
            static Load(InName: string): OnFloatValueChangedEvent__PythonCallable;
        
            __tid_OnFloatValueChangedEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnFloatValueChangedEventSynth2D__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnFloatValueChangedEventSynth2D__PythonCallable;
            static Load(InName: string): OnFloatValueChangedEventSynth2D__PythonCallable;
        
            __tid_OnFloatValueChangedEventSynth2D__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnForceFeedbackFinished__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnForceFeedbackFinished__PythonCallable;
            static Load(InName: string): OnForceFeedbackFinished__PythonCallable;
        
            __tid_OnForceFeedbackFinished__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnGameUserSettingsUINeedsUpdate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnGameUserSettingsUINeedsUpdate__PythonCallable;
            static Load(InName: string): OnGameUserSettingsUINeedsUpdate__PythonCallable;
        
            __tid_OnGameUserSettingsUINeedsUpdate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnGeometryCollectionFullyDecayedEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnGeometryCollectionFullyDecayedEvent__PythonCallable;
            static Load(InName: string): OnGeometryCollectionFullyDecayedEvent__PythonCallable;
        
            __tid_OnGeometryCollectionFullyDecayedEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnGeometryCollectionRootMovedEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnGeometryCollectionRootMovedEvent__PythonCallable;
            static Load(InName: string): OnGeometryCollectionRootMovedEvent__PythonCallable;
        
            __tid_OnGeometryCollectionRootMovedEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnGetItemChildrenDynamic__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnGetItemChildrenDynamic__PythonCallable;
            static Load(InName: string): OnGetItemChildrenDynamic__PythonCallable;
        
            __tid_OnGetItemChildrenDynamic__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnHoveredWidgetChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnHoveredWidgetChanged__PythonCallable;
            static Load(InName: string): OnHoveredWidgetChanged__PythonCallable;
        
            __tid_OnHoveredWidgetChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnImageWriteComplete__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnImageWriteComplete__PythonCallable;
            static Load(InName: string): OnImageWriteComplete__PythonCallable;
        
            __tid_OnImageWriteComplete__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnImportDoneDynamic__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnImportDoneDynamic__PythonCallable;
            static Load(InName: string): OnImportDoneDynamic__PythonCallable;
        
            __tid_OnImportDoneDynamic__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnInputAction__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnInputAction__PythonCallable;
            static Load(InName: string): OnInputAction__PythonCallable;
        
            __tid_OnInputAction__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnItemExpansionChangedDynamic__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnItemExpansionChangedDynamic__PythonCallable;
            static Load(InName: string): OnItemExpansionChangedDynamic__PythonCallable;
        
            __tid_OnItemExpansionChangedDynamic__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnItemIsHoveredChangedDynamic__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnItemIsHoveredChangedDynamic__PythonCallable;
            static Load(InName: string): OnItemIsHoveredChangedDynamic__PythonCallable;
        
            __tid_OnItemIsHoveredChangedDynamic__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnLatestConstantQResults__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnLatestConstantQResults__PythonCallable;
            static Load(InName: string): OnLatestConstantQResults__PythonCallable;
        
            __tid_OnLatestConstantQResults__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnLatestOverallLoudnessResults__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnLatestOverallLoudnessResults__PythonCallable;
            static Load(InName: string): OnLatestOverallLoudnessResults__PythonCallable;
        
            __tid_OnLatestOverallLoudnessResults__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnLatestOverallMeterResults__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnLatestOverallMeterResults__PythonCallable;
            static Load(InName: string): OnLatestOverallMeterResults__PythonCallable;
        
            __tid_OnLatestOverallMeterResults__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnLatestPerChannelLoudnessResults__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnLatestPerChannelLoudnessResults__PythonCallable;
            static Load(InName: string): OnLatestPerChannelLoudnessResults__PythonCallable;
        
            __tid_OnLatestPerChannelLoudnessResults__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnLatestPerChannelMeterResults__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnLatestPerChannelMeterResults__PythonCallable;
            static Load(InName: string): OnLatestPerChannelMeterResults__PythonCallable;
        
            __tid_OnLatestPerChannelMeterResults__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnLatestSpectrumResults__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnLatestSpectrumResults__PythonCallable;
            static Load(InName: string): OnLatestSpectrumResults__PythonCallable;
        
            __tid_OnLatestSpectrumResults__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnLeaderboardFlushed__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnLeaderboardFlushed__PythonCallable;
            static Load(InName: string): OnLeaderboardFlushed__PythonCallable;
        
            __tid_OnLeaderboardFlushed__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnLevelEditorEditorCameraMoved__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnLevelEditorEditorCameraMoved__PythonCallable;
            static Load(InName: string): OnLevelEditorEditorCameraMoved__PythonCallable;
        
            __tid_OnLevelEditorEditorCameraMoved__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnLevelEditorMapChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnLevelEditorMapChanged__PythonCallable;
            static Load(InName: string): OnLevelEditorMapChanged__PythonCallable;
        
            __tid_OnLevelEditorMapChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnLevelEditorMapOpened__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnLevelEditorMapOpened__PythonCallable;
            static Load(InName: string): OnLevelEditorMapOpened__PythonCallable;
        
            __tid_OnLevelEditorMapOpened__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnLevelEditorPostSaveWorld__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnLevelEditorPostSaveWorld__PythonCallable;
            static Load(InName: string): OnLevelEditorPostSaveWorld__PythonCallable;
        
            __tid_OnLevelEditorPostSaveWorld__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnLevelEditorPreSaveWorld__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnLevelEditorPreSaveWorld__PythonCallable;
            static Load(InName: string): OnLevelEditorPreSaveWorld__PythonCallable;
        
            __tid_OnLevelEditorPreSaveWorld__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnLevelSequencePlayerCameraCutEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnLevelSequencePlayerCameraCutEvent__PythonCallable;
            static Load(InName: string): OnLevelSequencePlayerCameraCutEvent__PythonCallable;
        
            __tid_OnLevelSequencePlayerCameraCutEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnlineConnectionResult__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnlineConnectionResult__PythonCallable;
            static Load(InName: string): OnlineConnectionResult__PythonCallable;
        
            __tid_OnlineConnectionResult__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnlineLogoutResult__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnlineLogoutResult__PythonCallable;
            static Load(InName: string): OnlineLogoutResult__PythonCallable;
        
            __tid_OnlineLogoutResult__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnlineProxyInAppCheckoutResult__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnlineProxyInAppCheckoutResult__PythonCallable;
            static Load(InName: string): OnlineProxyInAppCheckoutResult__PythonCallable;
        
            __tid_OnlineProxyInAppCheckoutResult__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnlineProxyInAppReceiptsResult__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnlineProxyInAppReceiptsResult__PythonCallable;
            static Load(InName: string): OnlineProxyInAppReceiptsResult__PythonCallable;
        
            __tid_OnlineProxyInAppReceiptsResult__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnlineShowLoginUIResult__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnlineShowLoginUIResult__PythonCallable;
            static Load(InName: string): OnlineShowLoginUIResult__PythonCallable;
        
            __tid_OnlineShowLoginUIResult__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnlineTurnBasedMatchResult__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnlineTurnBasedMatchResult__PythonCallable;
            static Load(InName: string): OnlineTurnBasedMatchResult__PythonCallable;
        
            __tid_OnlineTurnBasedMatchResult__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnListEntryGeneratedDynamic__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnListEntryGeneratedDynamic__PythonCallable;
            static Load(InName: string): OnListEntryGeneratedDynamic__PythonCallable;
        
            __tid_OnListEntryGeneratedDynamic__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnListEntryInitializedDynamic__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnListEntryInitializedDynamic__PythonCallable;
            static Load(InName: string): OnListEntryInitializedDynamic__PythonCallable;
        
            __tid_OnListEntryInitializedDynamic__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnListEntryReleasedDynamic__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnListEntryReleasedDynamic__PythonCallable;
            static Load(InName: string): OnListEntryReleasedDynamic__PythonCallable;
        
            __tid_OnListEntryReleasedDynamic__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnListItemScrolledIntoViewDynamic__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnListItemScrolledIntoViewDynamic__PythonCallable;
            static Load(InName: string): OnListItemScrolledIntoViewDynamic__PythonCallable;
        
            __tid_OnListItemScrolledIntoViewDynamic__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnListItemSelectionChangedDynamic__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnListItemSelectionChangedDynamic__PythonCallable;
            static Load(InName: string): OnListItemSelectionChangedDynamic__PythonCallable;
        
            __tid_OnListItemSelectionChangedDynamic__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnListViewScrolledDynamic__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnListViewScrolledDynamic__PythonCallable;
            static Load(InName: string): OnListViewScrolledDynamic__PythonCallable;
        
            __tid_OnListViewScrolledDynamic__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnLocalPlayerSaveGameLoaded__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnLocalPlayerSaveGameLoaded__PythonCallable;
            static Load(InName: string): OnLocalPlayerSaveGameLoaded__PythonCallable;
        
            __tid_OnLocalPlayerSaveGameLoaded__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnMainAudioOutputDeviceObtained__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnMainAudioOutputDeviceObtained__PythonCallable;
            static Load(InName: string): OnMainAudioOutputDeviceObtained__PythonCallable;
        
            __tid_OnMainAudioOutputDeviceObtained__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnMediaPlayerMediaEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnMediaPlayerMediaEvent__PythonCallable;
            static Load(InName: string): OnMediaPlayerMediaEvent__PythonCallable;
        
            __tid_OnMediaPlayerMediaEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnMediaPlayerMediaOpened__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnMediaPlayerMediaOpened__PythonCallable;
            static Load(InName: string): OnMediaPlayerMediaOpened__PythonCallable;
        
            __tid_OnMediaPlayerMediaOpened__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnMediaPlayerMediaOpenFailed__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnMediaPlayerMediaOpenFailed__PythonCallable;
            static Load(InName: string): OnMediaPlayerMediaOpenFailed__PythonCallable;
        
            __tid_OnMediaPlayerMediaOpenFailed__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnMenuOpenChangedEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnMenuOpenChangedEvent__PythonCallable;
            static Load(InName: string): OnMenuOpenChangedEvent__PythonCallable;
        
            __tid_OnMenuOpenChangedEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnMetasoundOutputValueChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnMetasoundOutputValueChanged__PythonCallable;
            static Load(InName: string): OnMetasoundOutputValueChanged__PythonCallable;
        
            __tid_OnMetasoundOutputValueChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnMetasoundOutputValueChangedMulticast__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnMetasoundOutputValueChangedMulticast__PythonCallable;
            static Load(InName: string): OnMetasoundOutputValueChangedMulticast__PythonCallable;
        
            __tid_OnMetasoundOutputValueChangedMulticast__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnMontageBlendedInEndedMCDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnMontageBlendedInEndedMCDelegate__PythonCallable;
            static Load(InName: string): OnMontageBlendedInEndedMCDelegate__PythonCallable;
        
            __tid_OnMontageBlendedInEndedMCDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnMontageBlendingOutStartedMCDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnMontageBlendingOutStartedMCDelegate__PythonCallable;
            static Load(InName: string): OnMontageBlendingOutStartedMCDelegate__PythonCallable;
        
            __tid_OnMontageBlendingOutStartedMCDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnMontageEndedMCDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnMontageEndedMCDelegate__PythonCallable;
            static Load(InName: string): OnMontageEndedMCDelegate__PythonCallable;
        
            __tid_OnMontageEndedMCDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnMontagePlayDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnMontagePlayDelegate__PythonCallable;
            static Load(InName: string): OnMontagePlayDelegate__PythonCallable;
        
            __tid_OnMontagePlayDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnMontageStartedMCDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnMontageStartedMCDelegate__PythonCallable;
            static Load(InName: string): OnMontageStartedMCDelegate__PythonCallable;
        
            __tid_OnMontageStartedMCDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnMouseCaptureBeginEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnMouseCaptureBeginEvent__PythonCallable;
            static Load(InName: string): OnMouseCaptureBeginEvent__PythonCallable;
        
            __tid_OnMouseCaptureBeginEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnMouseCaptureBeginEventSynth2D__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnMouseCaptureBeginEventSynth2D__PythonCallable;
            static Load(InName: string): OnMouseCaptureBeginEventSynth2D__PythonCallable;
        
            __tid_OnMouseCaptureBeginEventSynth2D__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnMouseCaptureEndEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnMouseCaptureEndEvent__PythonCallable;
            static Load(InName: string): OnMouseCaptureEndEvent__PythonCallable;
        
            __tid_OnMouseCaptureEndEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnMouseCaptureEndEventSynth2D__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnMouseCaptureEndEventSynth2D__PythonCallable;
            static Load(InName: string): OnMouseCaptureEndEventSynth2D__PythonCallable;
        
            __tid_OnMouseCaptureEndEventSynth2D__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnMovieSceneSequencePlayerEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnMovieSceneSequencePlayerEvent__PythonCallable;
            static Load(InName: string): OnMovieSceneSequencePlayerEvent__PythonCallable;
        
            __tid_OnMovieSceneSequencePlayerEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnNavDataGenericEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnNavDataGenericEvent__PythonCallable;
            static Load(InName: string): OnNavDataGenericEvent__PythonCallable;
        
            __tid_OnNavDataGenericEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnNavigationPathUpdated__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnNavigationPathUpdated__PythonCallable;
            static Load(InName: string): OnNavigationPathUpdated__PythonCallable;
        
            __tid_OnNavigationPathUpdated__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnNiagaraScriptCompilationComplete__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnNiagaraScriptCompilationComplete__PythonCallable;
            static Load(InName: string): OnNiagaraScriptCompilationComplete__PythonCallable;
        
            __tid_OnNiagaraScriptCompilationComplete__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnNiagaraSystemFinished__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnNiagaraSystemFinished__PythonCallable;
            static Load(InName: string): OnNiagaraSystemFinished__PythonCallable;
        
            __tid_OnNiagaraSystemFinished__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnNotifyReplaced__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnNotifyReplaced__PythonCallable;
            static Load(InName: string): OnNotifyReplaced__PythonCallable;
        
            __tid_OnNotifyReplaced__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnNotifyStateReplaced__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnNotifyStateReplaced__PythonCallable;
            static Load(InName: string): OnNotifyStateReplaced__PythonCallable;
        
            __tid_OnNotifyStateReplaced__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnObjectImportDoneDynamic__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnObjectImportDoneDynamic__PythonCallable;
            static Load(InName: string): OnObjectImportDoneDynamic__PythonCallable;
        
            __tid_OnObjectImportDoneDynamic__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnOverallLoudnessResults__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnOverallLoudnessResults__PythonCallable;
            static Load(InName: string): OnOverallLoudnessResults__PythonCallable;
        
            __tid_OnOverallLoudnessResults__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnOverallMeterResults__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnOverallMeterResults__PythonCallable;
            static Load(InName: string): OnOverallMeterResults__PythonCallable;
        
            __tid_OnOverallMeterResults__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnPawnControllerChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnPawnControllerChanged__PythonCallable;
            static Load(InName: string): OnPawnControllerChanged__PythonCallable;
        
            __tid_OnPawnControllerChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnPerChannelLoudnessResults__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnPerChannelLoudnessResults__PythonCallable;
            static Load(InName: string): OnPerChannelLoudnessResults__PythonCallable;
        
            __tid_OnPerChannelLoudnessResults__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnPerChannelMeterResults__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnPerChannelMeterResults__PythonCallable;
            static Load(InName: string): OnPerChannelMeterResults__PythonCallable;
        
            __tid_OnPerChannelMeterResults__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnPlayerStatePawnSet__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnPlayerStatePawnSet__PythonCallable;
            static Load(InName: string): OnPlayerStatePawnSet__PythonCallable;
        
            __tid_OnPlayerStatePawnSet__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnPossessedPawnChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnPossessedPawnChanged__PythonCallable;
            static Load(InName: string): OnPossessedPawnChanged__PythonCallable;
        
            __tid_OnPossessedPawnChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnPrimaryAssetBundlesChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnPrimaryAssetBundlesChanged__PythonCallable;
            static Load(InName: string): OnPrimaryAssetBundlesChanged__PythonCallable;
        
            __tid_OnPrimaryAssetBundlesChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnPrimaryAssetClassListLoaded__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnPrimaryAssetClassListLoaded__PythonCallable;
            static Load(InName: string): OnPrimaryAssetClassListLoaded__PythonCallable;
        
            __tid_OnPrimaryAssetClassListLoaded__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnPrimaryAssetClassLoaded__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnPrimaryAssetClassLoaded__PythonCallable;
            static Load(InName: string): OnPrimaryAssetClassLoaded__PythonCallable;
        
            __tid_OnPrimaryAssetClassLoaded__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnPrimaryAssetListLoaded__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnPrimaryAssetListLoaded__PythonCallable;
            static Load(InName: string): OnPrimaryAssetListLoaded__PythonCallable;
        
            __tid_OnPrimaryAssetListLoaded__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnPrimaryAssetLoaded__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnPrimaryAssetLoaded__PythonCallable;
            static Load(InName: string): OnPrimaryAssetLoaded__PythonCallable;
        
            __tid_OnPrimaryAssetLoaded__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnPropertyValueChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnPropertyValueChanged__PythonCallable;
            static Load(InName: string): OnPropertyValueChanged__PythonCallable;
        
            __tid_OnPropertyValueChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnQuartzCommandEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnQuartzCommandEvent__PythonCallable;
            static Load(InName: string): OnQuartzCommandEvent__PythonCallable;
        
            __tid_OnQuartzCommandEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnQuartzCommandEventBP__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnQuartzCommandEventBP__PythonCallable;
            static Load(InName: string): OnQuartzCommandEventBP__PythonCallable;
        
            __tid_OnQuartzCommandEventBP__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnQuartzMetronomeEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnQuartzMetronomeEvent__PythonCallable;
            static Load(InName: string): OnQuartzMetronomeEvent__PythonCallable;
        
            __tid_OnQuartzMetronomeEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnQuartzMetronomeEventBP__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnQuartzMetronomeEventBP__PythonCallable;
            static Load(InName: string): OnQuartzMetronomeEventBP__PythonCallable;
        
            __tid_OnQuartzMetronomeEventBP__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnQueueSubtitles__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnQueueSubtitles__PythonCallable;
            static Load(InName: string): OnQueueSubtitles__PythonCallable;
        
            __tid_OnQueueSubtitles__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnRenderMovieStopped__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnRenderMovieStopped__PythonCallable;
            static Load(InName: string): OnRenderMovieStopped__PythonCallable;
        
            __tid_OnRenderMovieStopped__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnRequestContentFailed__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnRequestContentFailed__PythonCallable;
            static Load(InName: string): OnRequestContentFailed__PythonCallable;
        
            __tid_OnRequestContentFailed__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnRequestContentSucceeded__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnRequestContentSucceeded__PythonCallable;
            static Load(InName: string): OnRequestContentSucceeded__PythonCallable;
        
            __tid_OnRequestContentSucceeded__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnSampleLoaded__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnSampleLoaded__PythonCallable;
            static Load(InName: string): OnSampleLoaded__PythonCallable;
        
            __tid_OnSampleLoaded__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnSamplePlaybackProgress__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnSamplePlaybackProgress__PythonCallable;
            static Load(InName: string): OnSamplePlaybackProgress__PythonCallable;
        
            __tid_OnSamplePlaybackProgress__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnScrollBarVisibilityChangedEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnScrollBarVisibilityChangedEvent__PythonCallable;
            static Load(InName: string): OnScrollBarVisibilityChangedEvent__PythonCallable;
        
            __tid_OnScrollBarVisibilityChangedEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnSoundLoadComplete__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnSoundLoadComplete__PythonCallable;
            static Load(InName: string): OnSoundLoadComplete__PythonCallable;
        
            __tid_OnSoundLoadComplete__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnSpectrumResults__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnSpectrumResults__PythonCallable;
            static Load(InName: string): OnSpectrumResults__PythonCallable;
        
            __tid_OnSpectrumResults__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnSubmixEnvelope__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnSubmixEnvelope__PythonCallable;
            static Load(InName: string): OnSubmixEnvelope__PythonCallable;
        
            __tid_OnSubmixEnvelope__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnSubmixEnvelopeBP__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnSubmixEnvelopeBP__PythonCallable;
            static Load(InName: string): OnSubmixEnvelopeBP__PythonCallable;
        
            __tid_OnSubmixEnvelopeBP__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnSubmixRecordedFileDone__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnSubmixRecordedFileDone__PythonCallable;
            static Load(InName: string): OnSubmixRecordedFileDone__PythonCallable;
        
            __tid_OnSubmixRecordedFileDone__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnSubmixSpectralAnalysis__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnSubmixSpectralAnalysis__PythonCallable;
            static Load(InName: string): OnSubmixSpectralAnalysis__PythonCallable;
        
            __tid_OnSubmixSpectralAnalysis__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnSubmixSpectralAnalysisBP__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnSubmixSpectralAnalysisBP__PythonCallable;
            static Load(InName: string): OnSubmixSpectralAnalysisBP__PythonCallable;
        
            __tid_OnSubmixSpectralAnalysisBP__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnSynthEnvelopeValue__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnSynthEnvelopeValue__PythonCallable;
            static Load(InName: string): OnSynthEnvelopeValue__PythonCallable;
        
            __tid_OnSynthEnvelopeValue__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnSystemFinished__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnSystemFinished__PythonCallable;
            static Load(InName: string): OnSystemFinished__PythonCallable;
        
            __tid_OnSystemFinished__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnTableAltered__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnTableAltered__PythonCallable;
            static Load(InName: string): OnTableAltered__PythonCallable;
        
            __tid_OnTableAltered__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnTakeRecorderCancelled__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnTakeRecorderCancelled__PythonCallable;
            static Load(InName: string): OnTakeRecorderCancelled__PythonCallable;
        
            __tid_OnTakeRecorderCancelled__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnTakeRecorderFinished__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnTakeRecorderFinished__PythonCallable;
            static Load(InName: string): OnTakeRecorderFinished__PythonCallable;
        
            __tid_OnTakeRecorderFinished__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnTakeRecorderMarkedFrameAdded__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnTakeRecorderMarkedFrameAdded__PythonCallable;
            static Load(InName: string): OnTakeRecorderMarkedFrameAdded__PythonCallable;
        
            __tid_OnTakeRecorderMarkedFrameAdded__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnTakeRecorderPanelChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnTakeRecorderPanelChanged__PythonCallable;
            static Load(InName: string): OnTakeRecorderPanelChanged__PythonCallable;
        
            __tid_OnTakeRecorderPanelChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnTakeRecorderPreInitialize__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnTakeRecorderPreInitialize__PythonCallable;
            static Load(InName: string): OnTakeRecorderPreInitialize__PythonCallable;
        
            __tid_OnTakeRecorderPreInitialize__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnTakeRecorderStarted__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnTakeRecorderStarted__PythonCallable;
            static Load(InName: string): OnTakeRecorderStarted__PythonCallable;
        
            __tid_OnTakeRecorderStarted__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnTakeRecorderStopped__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnTakeRecorderStopped__PythonCallable;
            static Load(InName: string): OnTakeRecorderStopped__PythonCallable;
        
            __tid_OnTakeRecorderStopped__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnTimelineEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnTimelineEvent__PythonCallable;
            static Load(InName: string): OnTimelineEvent__PythonCallable;
        
            __tid_OnTimelineEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnTimelineFloat__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnTimelineFloat__PythonCallable;
            static Load(InName: string): OnTimelineFloat__PythonCallable;
        
            __tid_OnTimelineFloat__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnTimelineLinearColor__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnTimelineLinearColor__PythonCallable;
            static Load(InName: string): OnTimelineLinearColor__PythonCallable;
        
            __tid_OnTimelineLinearColor__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnTimelineVector__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnTimelineVector__PythonCallable;
            static Load(InName: string): OnTimelineVector__PythonCallable;
        
            __tid_OnTimelineVector__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnUserClickedBanner__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnUserClickedBanner__PythonCallable;
            static Load(InName: string): OnUserClickedBanner__PythonCallable;
        
            __tid_OnUserClickedBanner__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnUserClosedAdvertisement__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnUserClosedAdvertisement__PythonCallable;
            static Load(InName: string): OnUserClosedAdvertisement__PythonCallable;
        
            __tid_OnUserClosedAdvertisement__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnUserInputDeviceConnectionChange__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnUserInputDeviceConnectionChange__PythonCallable;
            static Load(InName: string): OnUserInputDeviceConnectionChange__PythonCallable;
        
            __tid_OnUserInputDeviceConnectionChange__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnUserInputDevicePairingChange__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnUserInputDevicePairingChange__PythonCallable;
            static Load(InName: string): OnUserInputDevicePairingChange__PythonCallable;
        
            __tid_OnUserInputDevicePairingChange__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnUserScrolledEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnUserScrolledEvent__PythonCallable;
            static Load(InName: string): OnUserScrolledEvent__PythonCallable;
        
            __tid_OnUserScrolledEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnVisibilityChangedEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnVisibilityChangedEvent__PythonCallable;
            static Load(InName: string): OnVisibilityChangedEvent__PythonCallable;
        
            __tid_OnVisibilityChangedEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnWidgetAnimationPlaybackStatusChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnWidgetAnimationPlaybackStatusChanged__PythonCallable;
            static Load(InName: string): OnWidgetAnimationPlaybackStatusChanged__PythonCallable;
        
            __tid_OnWidgetAnimationPlaybackStatusChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ParticleBurstSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ParticleBurstSignature__PythonCallable;
            static Load(InName: string): ParticleBurstSignature__PythonCallable;
        
            __tid_ParticleBurstSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ParticleCollisionSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ParticleCollisionSignature__PythonCallable;
            static Load(InName: string): ParticleCollisionSignature__PythonCallable;
        
            __tid_ParticleCollisionSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ParticleDeathSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ParticleDeathSignature__PythonCallable;
            static Load(InName: string): ParticleDeathSignature__PythonCallable;
        
            __tid_ParticleDeathSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ParticleSpawnSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ParticleSpawnSignature__PythonCallable;
            static Load(InName: string): ParticleSpawnSignature__PythonCallable;
        
            __tid_ParticleSpawnSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class PawnControllerChangedSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): PawnControllerChangedSignature__PythonCallable;
            static Load(InName: string): PawnControllerChangedSignature__PythonCallable;
        
            __tid_PawnControllerChangedSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class PawnRestartedSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): PawnRestartedSignature__PythonCallable;
            static Load(InName: string): PawnRestartedSignature__PythonCallable;
        
            __tid_PawnRestartedSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class PawnSensingComponent_HearNoiseDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): PawnSensingComponent_HearNoiseDelegate__PythonCallable;
            static Load(InName: string): PawnSensingComponent_HearNoiseDelegate__PythonCallable;
        
            __tid_PawnSensingComponent_HearNoiseDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class PawnSensingComponent_SeePawnDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): PawnSensingComponent_SeePawnDelegate__PythonCallable;
            static Load(InName: string): PawnSensingComponent_SeePawnDelegate__PythonCallable;
        
            __tid_PawnSensingComponent_SeePawnDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class PerceptionUpdatedDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): PerceptionUpdatedDelegate__PythonCallable;
            static Load(InName: string): PerceptionUpdatedDelegate__PythonCallable;
        
            __tid_PerceptionUpdatedDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class PhysicsVolumeChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): PhysicsVolumeChanged__PythonCallable;
            static Load(InName: string): PhysicsVolumeChanged__PythonCallable;
        
            __tid_PhysicsVolumeChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class PlasticDeformationEventSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): PlasticDeformationEventSignature__PythonCallable;
            static Load(InName: string): PlasticDeformationEventSignature__PythonCallable;
        
            __tid_PlasticDeformationEventSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class PlatformEventsComponent_PlatformEventDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): PlatformEventsComponent_PlatformEventDelegate__PythonCallable;
            static Load(InName: string): PlatformEventsComponent_PlatformEventDelegate__PythonCallable;
        
            __tid_PlatformEventsComponent_PlatformEventDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class PlatformGameInstance_PlatformDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): PlatformGameInstance_PlatformDelegate__PythonCallable;
            static Load(InName: string): PlatformGameInstance_PlatformDelegate__PythonCallable;
        
            __tid_PlatformGameInstance_PlatformDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class PlatformGameInstance_PlatformFailedToRegisterForRemoteNotificationsDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): PlatformGameInstance_PlatformFailedToRegisterForRemoteNotificationsDelegate__PythonCallable;
            static Load(InName: string): PlatformGameInstance_PlatformFailedToRegisterForRemoteNotificationsDelegate__PythonCallable;
        
            __tid_PlatformGameInstance_PlatformFailedToRegisterForRemoteNotificationsDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class PlatformGameInstance_PlatformReceivedLocalNotificationDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): PlatformGameInstance_PlatformReceivedLocalNotificationDelegate__PythonCallable;
            static Load(InName: string): PlatformGameInstance_PlatformReceivedLocalNotificationDelegate__PythonCallable;
        
            __tid_PlatformGameInstance_PlatformReceivedLocalNotificationDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class PlatformGameInstance_PlatformReceivedRemoteNotificationDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): PlatformGameInstance_PlatformReceivedRemoteNotificationDelegate__PythonCallable;
            static Load(InName: string): PlatformGameInstance_PlatformReceivedRemoteNotificationDelegate__PythonCallable;
        
            __tid_PlatformGameInstance_PlatformReceivedRemoteNotificationDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class PlatformGameInstance_PlatformRegisteredForRemoteNotificationsDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): PlatformGameInstance_PlatformRegisteredForRemoteNotificationsDelegate__PythonCallable;
            static Load(InName: string): PlatformGameInstance_PlatformRegisteredForRemoteNotificationsDelegate__PythonCallable;
        
            __tid_PlatformGameInstance_PlatformRegisteredForRemoteNotificationsDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class PlatformGameInstance_PlatformRegisteredForUserNotificationsDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): PlatformGameInstance_PlatformRegisteredForUserNotificationsDelegate__PythonCallable;
            static Load(InName: string): PlatformGameInstance_PlatformRegisteredForUserNotificationsDelegate__PythonCallable;
        
            __tid_PlatformGameInstance_PlatformRegisteredForUserNotificationsDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class PlatformGameInstance_PlatformScreenOrientationChangedDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): PlatformGameInstance_PlatformScreenOrientationChangedDelegate__PythonCallable;
            static Load(InName: string): PlatformGameInstance_PlatformScreenOrientationChangedDelegate__PythonCallable;
        
            __tid_PlatformGameInstance_PlatformScreenOrientationChangedDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class PlatformGameInstance_PlatformStartupArgumentsDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): PlatformGameInstance_PlatformStartupArgumentsDelegate__PythonCallable;
            static Load(InName: string): PlatformGameInstance_PlatformStartupArgumentsDelegate__PythonCallable;
        
            __tid_PlatformGameInstance_PlatformStartupArgumentsDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class PlatformInterfaceDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): PlatformInterfaceDelegate__PythonCallable;
            static Load(InName: string): PlatformInterfaceDelegate__PythonCallable;
        
            __tid_PlatformInterfaceDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class PlayMontageAnimNotifyDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): PlayMontageAnimNotifyDelegate__PythonCallable;
            static Load(InName: string): PlayMontageAnimNotifyDelegate__PythonCallable;
        
            __tid_PlayMontageAnimNotifyDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class PostEvaluateAnimEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): PostEvaluateAnimEvent__PythonCallable;
            static Load(InName: string): PostEvaluateAnimEvent__PythonCallable;
        
            __tid_PostEvaluateAnimEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ProjectileMovementComponent_OnProjectileBounceDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ProjectileMovementComponent_OnProjectileBounceDelegate__PythonCallable;
            static Load(InName: string): ProjectileMovementComponent_OnProjectileBounceDelegate__PythonCallable;
        
            __tid_ProjectileMovementComponent_OnProjectileBounceDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ProjectileMovementComponent_OnProjectileStopDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ProjectileMovementComponent_OnProjectileStopDelegate__PythonCallable;
            static Load(InName: string): ProjectileMovementComponent_OnProjectileStopDelegate__PythonCallable;
        
            __tid_ProjectileMovementComponent_OnProjectileStopDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class PyTestDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): PyTestDelegate__PythonCallable;
            static Load(InName: string): PyTestDelegate__PythonCallable;
        
            __tid_PyTestDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class PyTestMulticastDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): PyTestMulticastDelegate__PythonCallable;
            static Load(InName: string): PyTestMulticastDelegate__PythonCallable;
        
            __tid_PyTestMulticastDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class PyTestSlateTickDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): PyTestSlateTickDelegate__PythonCallable;
            static Load(InName: string): PyTestSlateTickDelegate__PythonCallable;
        
            __tid_PyTestSlateTickDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class PyTestStructDelegate_OnNameCollisionDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): PyTestStructDelegate_OnNameCollisionDelegate__PythonCallable;
            static Load(InName: string): PyTestStructDelegate_OnNameCollisionDelegate__PythonCallable;
        
            __tid_PyTestStructDelegate_OnNameCollisionDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class PyTestVectorDelegate_OnNameCollisionDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): PyTestVectorDelegate_OnNameCollisionDelegate__PythonCallable;
            static Load(InName: string): PyTestVectorDelegate_OnNameCollisionDelegate__PythonCallable;
        
            __tid_PyTestVectorDelegate_OnNameCollisionDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class RemovalEventSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): RemovalEventSignature__PythonCallable;
            static Load(InName: string): RemovalEventSignature__PythonCallable;
        
            __tid_RemovalEventSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class RigHierarchyModifiedDynamicEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): RigHierarchyModifiedDynamicEvent__PythonCallable;
            static Load(InName: string): RigHierarchyModifiedDynamicEvent__PythonCallable;
        
            __tid_RigHierarchyModifiedDynamicEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class RigVMAssetDataFilterDynamic__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): RigVMAssetDataFilterDynamic__PythonCallable;
            static Load(InName: string): RigVMAssetDataFilterDynamic__PythonCallable;
        
            __tid_RigVMAssetDataFilterDynamic__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class RigVMBlueprintFilterDynamic__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): RigVMBlueprintFilterDynamic__PythonCallable;
            static Load(InName: string): RigVMBlueprintFilterDynamic__PythonCallable;
        
            __tid_RigVMBlueprintFilterDynamic__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class RigVMGraphModifiedDynamicEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): RigVMGraphModifiedDynamicEvent__PythonCallable;
            static Load(InName: string): RigVMGraphModifiedDynamicEvent__PythonCallable;
        
            __tid_RigVMGraphModifiedDynamicEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class RigVMNodeFilterDynamic__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): RigVMNodeFilterDynamic__PythonCallable;
            static Load(InName: string): RigVMNodeFilterDynamic__PythonCallable;
        
            __tid_RigVMNodeFilterDynamic__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class RigVMPeformUserWorkflowDynamicDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): RigVMPeformUserWorkflowDynamicDelegate__PythonCallable;
            static Load(InName: string): RigVMPeformUserWorkflowDynamicDelegate__PythonCallable;
        
            __tid_RigVMPeformUserWorkflowDynamicDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class RigVMUserWorkflowProvider__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): RigVMUserWorkflowProvider__PythonCallable;
            static Load(InName: string): RigVMUserWorkflowProvider__PythonCallable;
        
            __tid_RigVMUserWorkflowProvider__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class search_replace_entry extends UE.ToolMenuEntryScript {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): search_replace_entry;
            static Load(InName: string): search_replace_entry;
        
            __tid_search_replace_entry_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class search_replace_name_dialog extends UE.Object {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            search: string;
            replace: string;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): search_replace_name_dialog;
            static Load(InName: string): search_replace_name_dialog;
        
            __tid_search_replace_name_dialog_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class SequencerOutlinerSelectionChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): SequencerOutlinerSelectionChanged__PythonCallable;
            static Load(InName: string): SequencerOutlinerSelectionChanged__PythonCallable;
        
            __tid_SequencerOutlinerSelectionChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class set_bone_reference_pose extends UE.ToolMenuEntryScript {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): set_bone_reference_pose;
            static Load(InName: string): set_bone_reference_pose;
        
            __tid_set_bone_reference_pose_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class SimpleListItemEventDynamic__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): SimpleListItemEventDynamic__PythonCallable;
            static Load(InName: string): SimpleListItemEventDynamic__PythonCallable;
        
            __tid_SimpleListItemEventDynamic__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class SlateAccessibleWidgetData_GetText__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): SlateAccessibleWidgetData_GetText__PythonCallable;
            static Load(InName: string): SlateAccessibleWidgetData_GetText__PythonCallable;
        
            __tid_SlateAccessibleWidgetData_GetText__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class SmartLinkReachedSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): SmartLinkReachedSignature__PythonCallable;
            static Load(InName: string): SmartLinkReachedSignature__PythonCallable;
        
            __tid_SmartLinkReachedSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class SourceControl_QueryFileStateDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): SourceControl_QueryFileStateDelegate__PythonCallable;
            static Load(InName: string): SourceControl_QueryFileStateDelegate__PythonCallable;
        
            __tid_SourceControl_QueryFileStateDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class SpinBox_OnSpinBoxBeginSliderMovement__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): SpinBox_OnSpinBoxBeginSliderMovement__PythonCallable;
            static Load(InName: string): SpinBox_OnSpinBoxBeginSliderMovement__PythonCallable;
        
            __tid_SpinBox_OnSpinBoxBeginSliderMovement__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class SpinBox_OnSpinBoxValueChangedEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): SpinBox_OnSpinBoxValueChangedEvent__PythonCallable;
            static Load(InName: string): SpinBox_OnSpinBoxValueChangedEvent__PythonCallable;
        
            __tid_SpinBox_OnSpinBoxValueChangedEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class SpinBox_OnSpinBoxValueCommittedEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): SpinBox_OnSpinBoxValueCommittedEvent__PythonCallable;
            static Load(InName: string): SpinBox_OnSpinBoxValueCommittedEvent__PythonCallable;
        
            __tid_SpinBox_OnSpinBoxValueCommittedEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class SystemLibrary_OnAssetClassLoaded__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): SystemLibrary_OnAssetClassLoaded__PythonCallable;
            static Load(InName: string): SystemLibrary_OnAssetClassLoaded__PythonCallable;
        
            __tid_SystemLibrary_OnAssetClassLoaded__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class SystemLibrary_OnAssetLoaded__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): SystemLibrary_OnAssetLoaded__PythonCallable;
            static Load(InName: string): SystemLibrary_OnAssetLoaded__PythonCallable;
        
            __tid_SystemLibrary_OnAssetLoaded__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class TakeAnyDamageSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): TakeAnyDamageSignature__PythonCallable;
            static Load(InName: string): TakeAnyDamageSignature__PythonCallable;
        
            __tid_TakeAnyDamageSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class TakePointDamageSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): TakePointDamageSignature__PythonCallable;
            static Load(InName: string): TakePointDamageSignature__PythonCallable;
        
            __tid_TakePointDamageSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class TakeRadialDamageSignature__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): TakeRadialDamageSignature__PythonCallable;
            static Load(InName: string): TakeRadialDamageSignature__PythonCallable;
        
            __tid_TakeRadialDamageSignature__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class TakeRecorderCancelled__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): TakeRecorderCancelled__PythonCallable;
            static Load(InName: string): TakeRecorderCancelled__PythonCallable;
        
            __tid_TakeRecorderCancelled__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class TakeRecorderFinished__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): TakeRecorderFinished__PythonCallable;
            static Load(InName: string): TakeRecorderFinished__PythonCallable;
        
            __tid_TakeRecorderFinished__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class TakeRecorderMarkedFrameAdded__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): TakeRecorderMarkedFrameAdded__PythonCallable;
            static Load(InName: string): TakeRecorderMarkedFrameAdded__PythonCallable;
        
            __tid_TakeRecorderMarkedFrameAdded__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class TakeRecorderPreInitialize__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): TakeRecorderPreInitialize__PythonCallable;
            static Load(InName: string): TakeRecorderPreInitialize__PythonCallable;
        
            __tid_TakeRecorderPreInitialize__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class TakeRecorderStarted__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): TakeRecorderStarted__PythonCallable;
            static Load(InName: string): TakeRecorderStarted__PythonCallable;
        
            __tid_TakeRecorderStarted__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class TakeRecorderStopped__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): TakeRecorderStopped__PythonCallable;
            static Load(InName: string): TakeRecorderStopped__PythonCallable;
        
            __tid_TakeRecorderStopped__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class TakesCoreBlueprintLibrary_OnTakeRecorderSlateChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): TakesCoreBlueprintLibrary_OnTakeRecorderSlateChanged__PythonCallable;
            static Load(InName: string): TakesCoreBlueprintLibrary_OnTakeRecorderSlateChanged__PythonCallable;
        
            __tid_TakesCoreBlueprintLibrary_OnTakeRecorderSlateChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class TakesCoreBlueprintLibrary_OnTakeRecorderTakeNumberChanged__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): TakesCoreBlueprintLibrary_OnTakeRecorderTakeNumberChanged__PythonCallable;
            static Load(InName: string): TakesCoreBlueprintLibrary_OnTakeRecorderTakeNumberChanged__PythonCallable;
        
            __tid_TakesCoreBlueprintLibrary_OnTakeRecorderTakeNumberChanged__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class TimerDynamicDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): TimerDynamicDelegate__PythonCallable;
            static Load(InName: string): TimerDynamicDelegate__PythonCallable;
        
            __tid_TimerDynamicDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ToolMenuDynamicCanExecuteAction__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ToolMenuDynamicCanExecuteAction__PythonCallable;
            static Load(InName: string): ToolMenuDynamicCanExecuteAction__PythonCallable;
        
            __tid_ToolMenuDynamicCanExecuteAction__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ToolMenuDynamicExecuteAction__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ToolMenuDynamicExecuteAction__PythonCallable;
            static Load(InName: string): ToolMenuDynamicExecuteAction__PythonCallable;
        
            __tid_ToolMenuDynamicExecuteAction__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ToolMenuDynamicGetActionCheckState__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ToolMenuDynamicGetActionCheckState__PythonCallable;
            static Load(InName: string): ToolMenuDynamicGetActionCheckState__PythonCallable;
        
            __tid_ToolMenuDynamicGetActionCheckState__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ToolMenuDynamicIsActionButtonVisible__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ToolMenuDynamicIsActionButtonVisible__PythonCallable;
            static Load(InName: string): ToolMenuDynamicIsActionButtonVisible__PythonCallable;
        
            __tid_ToolMenuDynamicIsActionButtonVisible__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ToolMenuDynamicIsActionChecked__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ToolMenuDynamicIsActionChecked__PythonCallable;
            static Load(InName: string): ToolMenuDynamicIsActionChecked__PythonCallable;
        
            __tid_ToolMenuDynamicIsActionChecked__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class TypedElementSelectionSet_OnChangeDynamic__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): TypedElementSelectionSet_OnChangeDynamic__PythonCallable;
            static Load(InName: string): TypedElementSelectionSet_OnChangeDynamic__PythonCallable;
        
            __tid_TypedElementSelectionSet_OnChangeDynamic__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class TypedElementSelectionSet_OnPreChangeDynamic__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): TypedElementSelectionSet_OnPreChangeDynamic__PythonCallable;
            static Load(InName: string): TypedElementSelectionSet_OnPreChangeDynamic__PythonCallable;
        
            __tid_TypedElementSelectionSet_OnPreChangeDynamic__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class ViewportDisplayCallback__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ViewportDisplayCallback__PythonCallable;
            static Load(InName: string): ViewportDisplayCallback__PythonCallable;
        
            __tid_ViewportDisplayCallback__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class Widget_GenerateWidgetForObject__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Widget_GenerateWidgetForObject__PythonCallable;
            static Load(InName: string): Widget_GenerateWidgetForObject__PythonCallable;
        
            __tid_Widget_GenerateWidgetForObject__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class Widget_GenerateWidgetForString__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Widget_GenerateWidgetForString__PythonCallable;
            static Load(InName: string): Widget_GenerateWidgetForString__PythonCallable;
        
            __tid_Widget_GenerateWidgetForString__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class Widget_GetBool__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Widget_GetBool__PythonCallable;
            static Load(InName: string): Widget_GetBool__PythonCallable;
        
            __tid_Widget_GetBool__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class Widget_GetCheckBoxState__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Widget_GetCheckBoxState__PythonCallable;
            static Load(InName: string): Widget_GetCheckBoxState__PythonCallable;
        
            __tid_Widget_GetCheckBoxState__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class Widget_GetFloat__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Widget_GetFloat__PythonCallable;
            static Load(InName: string): Widget_GetFloat__PythonCallable;
        
            __tid_Widget_GetFloat__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class Widget_GetInt32__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Widget_GetInt32__PythonCallable;
            static Load(InName: string): Widget_GetInt32__PythonCallable;
        
            __tid_Widget_GetInt32__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class Widget_GetLinearColor__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Widget_GetLinearColor__PythonCallable;
            static Load(InName: string): Widget_GetLinearColor__PythonCallable;
        
            __tid_Widget_GetLinearColor__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class Widget_GetMouseCursor__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Widget_GetMouseCursor__PythonCallable;
            static Load(InName: string): Widget_GetMouseCursor__PythonCallable;
        
            __tid_Widget_GetMouseCursor__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class Widget_GetSlateBrush__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Widget_GetSlateBrush__PythonCallable;
            static Load(InName: string): Widget_GetSlateBrush__PythonCallable;
        
            __tid_Widget_GetSlateBrush__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class Widget_GetSlateColor__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Widget_GetSlateColor__PythonCallable;
            static Load(InName: string): Widget_GetSlateColor__PythonCallable;
        
            __tid_Widget_GetSlateColor__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class Widget_GetSlateVisibility__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Widget_GetSlateVisibility__PythonCallable;
            static Load(InName: string): Widget_GetSlateVisibility__PythonCallable;
        
            __tid_Widget_GetSlateVisibility__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class Widget_GetText__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Widget_GetText__PythonCallable;
            static Load(InName: string): Widget_GetText__PythonCallable;
        
            __tid_Widget_GetText__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class Widget_GetWidget__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Widget_GetWidget__PythonCallable;
            static Load(InName: string): Widget_GetWidget__PythonCallable;
        
            __tid_Widget_GetWidget__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class Widget_OnPointerEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Widget_OnPointerEvent__PythonCallable;
            static Load(InName: string): Widget_OnPointerEvent__PythonCallable;
        
            __tid_Widget_OnPointerEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class Widget_OnReply__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): Widget_OnReply__PythonCallable;
            static Load(InName: string): Widget_OnReply__PythonCallable;
        
            __tid_Widget_OnReply__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class WidgetAnimationDynamicEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): WidgetAnimationDynamicEvent__PythonCallable;
            static Load(InName: string): WidgetAnimationDynamicEvent__PythonCallable;
        
            __tid_WidgetAnimationDynamicEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class WidgetAnimationDynamicEvents__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): WidgetAnimationDynamicEvents__PythonCallable;
            static Load(InName: string): WidgetAnimationDynamicEvents__PythonCallable;
        
            __tid_WidgetAnimationDynamicEvents__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class WidgetAnimationResult__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): WidgetAnimationResult__PythonCallable;
            static Load(InName: string): WidgetAnimationResult__PythonCallable;
        
            __tid_WidgetAnimationResult__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class WidgetLibrary_OnGameWindowCloseButtonClickedDelegate__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): WidgetLibrary_OnGameWindowCloseButtonClickedDelegate__PythonCallable;
            static Load(InName: string): WidgetLibrary_OnGameWindowCloseButtonClickedDelegate__PythonCallable;
        
            __tid_WidgetLibrary_OnGameWindowCloseButtonClickedDelegate__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnCallTypeScript__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnCallTypeScript__PythonCallable;
            static Load(InName: string): OnCallTypeScript__PythonCallable;
        
            __tid_OnCallTypeScript__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnGameInstanceShutdown__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnGameInstanceShutdown__PythonCallable;
            static Load(InName: string): OnGameInstanceShutdown__PythonCallable;
        
            __tid_OnGameInstanceShutdown__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnNoesisCanExecuteCommand__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnNoesisCanExecuteCommand__PythonCallable;
            static Load(InName: string): OnNoesisCanExecuteCommand__PythonCallable;
        
            __tid_OnNoesisCanExecuteCommand__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnNoesisExecuteCommand__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnNoesisExecuteCommand__PythonCallable;
            static Load(InName: string): OnNoesisExecuteCommand__PythonCallable;
        
            __tid_OnNoesisExecuteCommand__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Engine.PythonTypes {
        class OnNoesisViewEvent__PythonCallable extends UE.PythonCallableForDelegate {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnNoesisViewEvent__PythonCallable;
            static Load(InName: string): OnNoesisViewEvent__PythonCallable;
        
            __tid_OnNoesisViewEvent__PythonCallable_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 9E6D26D74230B9BB81A6D0B5A7B5F57A
    namespace Game.BluePrints.GamePlay.BP_GM_Home {
        class BP_GM_Home_C extends UE.GameModeBase {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            DefaultSceneRoot: UE.SceneComponent;
            ExecuteUbergraph_BP_GM_Home(EntryPoint: number) : void;
            /*
             *Event when play begins for this actor.
             */
            ReceiveBeginPlay() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_GM_Home_C;
            static Load(InName: string): BP_GM_Home_C;
        
            __tid_BP_GM_Home_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 7177B6DE4BC5C8F69DE79887559E3CFE
    namespace Game.BluePrints.TypeScript.ViewMode.TS_ButtonsViewMode {
        class TS_ButtonsViewMode_C extends UE.Object {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            TestValue: string;
            ExitCommand() : void;
            SettingCommand() : void;
            StartCommand() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): TS_ButtonsViewMode_C;
            static Load(InName: string): TS_ButtonsViewMode_C;
        
            __tid_TS_ButtonsViewMode_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ASSOCIATION
    namespace Game.Map.L_Home {
        class L_Home_C extends UE.LevelScriptActor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            ExecuteUbergraph_L_Home(EntryPoint: number) : void;
            /*
             *Event when play begins for this actor.
             */
            ReceiveBeginPlay() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): L_Home_C;
            static Load(InName: string): L_Home_C;
        
            __tid_L_Home_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 5B356187490C93077BA1B6884FE2CBA4
    namespace Game.Blueprints.TypeScript.ViewMode.TS_NoesisViewMode {
        class TS_NoesisViewMode_C extends UE.Object {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            TestValue: string;
            StrArr: TArray<string>;
            StrMap: TMap<string, string>;
            TestFunc(param: string) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): TS_NoesisViewMode_C;
            static Load(InName: string): TS_NoesisViewMode_C;
        
            __tid_TS_NoesisViewMode_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
}
