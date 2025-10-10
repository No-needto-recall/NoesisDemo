////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/MediaElement.h>
#include <NsApp/MediaPlayer.h>
#include <NsGui/UIElementData.h>
#include <NsGui/FrameworkPropertyMetadata.h>
#include <NsGui/DrawingContext.h>
#include <NsGui/TextureSource.h>
#include <NsGui/Enums.h>
#include <NsGui/Viewbox.h>
#include <NsGui/Uri.h>
#include <NsGui/IView.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/ReflectionImplementEnum.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
static MediaElement::CreateMediaPlayerCallback gCreateMediaPlayer;
static void* gCreateMediaPlayerUser;

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::SetCreateMediaPlayerCallback(CreateMediaPlayerCallback callback, void* user)
{
    gCreateMediaPlayer = callback;
    gCreateMediaPlayerUser = user;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
ExceptionRoutedEventArgs::ExceptionRoutedEventArgs(Noesis::BaseComponent* s,
    const Noesis::RoutedEvent* e, const char* err): Noesis::RoutedEventArgs(s, e),
    errorException(err)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MediaElement::MediaElement(): mViewContent(nullptr), mState(MediaState_Close),
    mDuration(Noesis::Duration::Automatic()), mPosition(Noesis::TimeSpan::Zero()),
    mSpeedRatio(1.0f), mIsBuffering(false)
{
    Loaded() += MakeDelegate(this, &MediaElement::OnLoaded);
    Unloaded() += MakeDelegate(this, &MediaElement::OnUnloaded);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MediaElement::~MediaElement()
{
    Loaded() -= MakeDelegate(this, &MediaElement::OnLoaded);
    Unloaded() -= MakeDelegate(this, &MediaElement::OnUnloaded);

    if (mViewContent != nullptr)
    {
        mViewContent->Unloaded() -= MakeDelegate(this, &MediaElement::OnViewDestroyed);
        mViewContent = nullptr;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Stretch MediaElement::GetStretch() const
{
    return GetValue<Noesis::Stretch>(StretchProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::SetStretch(Noesis::Stretch value)
{
    SetValue<Noesis::Stretch>(StretchProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::StretchDirection MediaElement::GetStretchDirection() const
{
    return GetValue<Noesis::StretchDirection>(StretchDirectionProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::SetStretchDirection(Noesis::StretchDirection value)
{
    SetValue<Noesis::StretchDirection>(StretchDirectionProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool MediaElement::IsBuffering() const
{
    return mIsBuffering;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float MediaElement::GetBufferingProgress() const
{
    return mPlayer != nullptr ? mPlayer->GetBufferingProgress() : 0.0f;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float MediaElement::GetDownloadProgress() const
{
    return mPlayer != nullptr ? mPlayer->GetDownloadProgress() : 0.0f;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t MediaElement::GetNaturalVideoWidth() const
{
    return mPlayer != nullptr ? mPlayer->GetWidth() : 0u;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t MediaElement::GetNaturalVideoHeight() const
{
    return mPlayer != nullptr ? mPlayer->GetHeight() : 0u;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::Duration& MediaElement::GetNaturalDuration() const
{
    if (mPlayer != nullptr)
    {
        mDuration = Noesis::TimeSpan(mPlayer->GetDuration());
    }

    return mDuration;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::TimeSpan& MediaElement::GetPosition() const
{
    if (mPlayer != nullptr)
    {
        mPosition = Noesis::TimeSpan(mPlayer->GetPosition());
    }

    return mPosition;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::SetPosition(const Noesis::TimeSpan& value)
{
    mPosition = value;

    if (mPlayer != nullptr)
    {
        mPlayer->SetPosition(mPosition.GetTotalSeconds());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float MediaElement::GetSpeedRatio() const
{
    if (mPlayer != nullptr)
    {
        mSpeedRatio = mPlayer->GetSpeedRatio();
    }

    return mSpeedRatio;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::SetSpeedRatio(float value)
{
    mSpeedRatio = value;

    if (mPlayer != nullptr)
    {
        mPlayer->SetSpeedRatio(value);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool MediaElement::CanPause() const
{
    return mPlayer != nullptr ? mPlayer->CanPause() : false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool MediaElement::HasAudio() const
{
    return mPlayer != nullptr ? mPlayer->HasAudio() : false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool MediaElement::HasVideo() const
{
    return mPlayer != nullptr ? mPlayer->HasVideo() : false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::Uri& MediaElement::GetSource() const
{
    return GetValue<Noesis::Uri>(SourceProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::SetSource(const Noesis::Uri& value)
{
    SetValue<Noesis::Uri>(SourceProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool MediaElement::GetIsMuted() const
{
    return GetValue<bool>(IsMutedProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::SetIsMuted(bool value)
{
    SetValue<bool>(IsMutedProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float MediaElement::GetVolume() const
{
    return GetValue<float>(VolumeProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::SetVolume(float value)
{
    SetValue<float>(VolumeProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float MediaElement::GetBalance() const
{
    return GetValue<float>(BalanceProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::SetBalance(float value)
{
    SetValue<float>(BalanceProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool MediaElement::GetScrubbingEnabled() const
{
    return GetValue<bool>(ScrubbingEnabledProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::SetScrubbingEnabled(bool value)
{
    SetValue<bool>(ScrubbingEnabledProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MediaState MediaElement::GetLoadedBehavior() const
{
    return GetValue<MediaState>(LoadedBehaviorProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::SetLoadedBehavior(MediaState value)
{
    SetValue<MediaState>(LoadedBehaviorProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MediaState MediaElement::GetUnloadedBehavior() const
{
    return GetValue<MediaState>(UnloadedBehaviorProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::SetUnloadedBehavior(MediaState value)
{
    SetValue<MediaState>(UnloadedBehaviorProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::Play()
{
    SetState(MediaState_Play);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::Pause()
{
    SetState(MediaState_Pause);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::Stop()
{
    SetState(MediaState_Stop);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::Close()
{
    SetState(MediaState_Close);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::UIElement::RoutedEvent_<Noesis::RoutedEventHandler> MediaElement::BufferingStarted()
{
    return RoutedEvent_<Noesis::RoutedEventHandler>(this, BufferingStartedEvent);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::UIElement::RoutedEvent_<Noesis::RoutedEventHandler> MediaElement::BufferingEnded()
{
    return RoutedEvent_<Noesis::RoutedEventHandler>(this, BufferingEndedEvent);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::UIElement::RoutedEvent_<ExceptionRoutedEventHandler> MediaElement::MediaFailed()
{
    return RoutedEvent_<ExceptionRoutedEventHandler>(this, MediaFailedEvent);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::UIElement::RoutedEvent_<Noesis::RoutedEventHandler> MediaElement::MediaOpened()
{
    return RoutedEvent_<Noesis::RoutedEventHandler>(this, MediaOpenedEvent);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::UIElement::RoutedEvent_<Noesis::RoutedEventHandler> MediaElement::MediaEnded()
{
    return RoutedEvent_<Noesis::RoutedEventHandler>(this, MediaEndedEvent);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::OnRender(Noesis::DrawingContext* context)
{
    if (mTextureSource != nullptr)
    {
        context->DrawImage(mTextureSource, Noesis::Rect(mRenderSize));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Size MediaElement::MeasureOverride(const Noesis::Size& availableSize)
{
    return MeasureArranageSize(availableSize);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Size MediaElement::ArrangeOverride(const Noesis::Size& finalSize)
{
    return MeasureArranageSize(finalSize);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Size MediaElement::MeasureArranageSize(const Noesis::Size& size)
{
    Noesis::Size contentSize = Noesis::Sizei(GetNaturalVideoWidth(), GetNaturalVideoHeight());
    Noesis::Point scale = Noesis::Viewbox::GetStretchScale(contentSize, size, GetStretch(),
        GetStretchDirection());
    return Noesis::Size(contentSize.width * scale.x, contentSize.height * scale.y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::SetState(MediaState state)
{
    if (GetLoadedBehavior() != MediaState_Manual && GetUnloadedBehavior() != MediaState_Manual)
    {
        NS_ERROR("Cannot control media unless LoadedBehavior or UnloadedBehavior is set to Manual.");
        return;
    }

    UpdateState(state, false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::UpdateState(MediaState action, bool sourceChanged)
{
    MediaState stateRequested = action;

    if (IsLoaded())
    {
        MediaState loadedBehavior = GetLoadedBehavior();

        if (loadedBehavior != MediaState_Manual)
        {
            stateRequested = loadedBehavior;
        }
    }
    else
    {
        MediaState unloadedBehavior = GetUnloadedBehavior();

        if (unloadedBehavior != MediaState_Manual)
        {
            stateRequested = unloadedBehavior;
        }
    }

    if (mState != stateRequested || stateRequested == MediaState_Stop || sourceChanged)
    {
        bool opened = false;
        if (stateRequested != MediaState_Close && stateRequested != MediaState_Manual)
        {
            const Noesis::Uri& source = GetSource();
            if ((mState == MediaState_Close || sourceChanged) && !Noesis::StrIsEmpty(source.Str()))
            {
                DestroyMediaPlayer();
                CreateMediaPlayer(source);
                opened = true;
            }
        }

        if (mState != MediaState_Close || opened)
        {
            mState = stateRequested;

            switch (mState)
            {
                case MediaState_Manual:
                {
                    break; // ignore
                }
                case MediaState_Play:
                {
                    if (mPlayer != nullptr)
                    {
                        mPlayer->Play();
                    }
                    break;
                }
                case MediaState_Close:
                {
                    DestroyMediaPlayer();
                    break;
                }
                case MediaState_Pause:
                {
                    if (mPlayer != nullptr)
                    {
                        mPlayer->Pause();
                    }
                    break;
                }
                case MediaState_Stop:
                {
                    if (mPlayer != nullptr)
                    {
                        mPlayer->Stop();
                    }
                    break;
                }
                default: NS_ASSERT_UNREACHABLE;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::CreateMediaPlayer(const Noesis::Uri& source)
{
    NS_ASSERT(mPlayer == nullptr);

    if (gCreateMediaPlayer != nullptr)
    {
        mPlayer = gCreateMediaPlayer(this, source, gCreateMediaPlayerUser);

        if (mPlayer != nullptr)
        {
            mPlayer->BufferingStarted() += MakeDelegate(this, &MediaElement::OnBufferingStarted);
            mPlayer->BufferingEnded() += MakeDelegate(this, &MediaElement::OnBufferingEnded);
            mPlayer->MediaOpened() += MakeDelegate(this, &MediaElement::OnMediaOpened);
            mPlayer->MediaEnded() += MakeDelegate(this, &MediaElement::OnMediaEnded);
            mPlayer->MediaFailed() += MakeDelegate(this, &MediaElement::OnMediaFailed);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::DestroyMediaPlayer()
{
    if (mPlayer != nullptr)
    {
        mPlayer->BufferingStarted() -= MakeDelegate(this, &MediaElement::OnBufferingStarted);
        mPlayer->BufferingEnded() -= MakeDelegate(this, &MediaElement::OnBufferingEnded);
        mPlayer->MediaOpened() -= MakeDelegate(this, &MediaElement::OnMediaOpened);
        mPlayer->MediaEnded() -= MakeDelegate(this, &MediaElement::OnMediaEnded);
        mPlayer->MediaFailed() -= MakeDelegate(this, &MediaElement::OnMediaFailed);
        mPlayer.Reset();

        if (mTextureSource != nullptr)
        {
            mTextureSource->Changed() -= MakeDelegate(this, &MediaElement::OnTextureChanged);
            mTextureSource.Reset();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::MediaElement::OnTextureChanged(Noesis::Freezable*,
    Noesis::FreezableEventReason reason)
{
    if (reason == Noesis::FreezableEventReason_PropertyChanged)
    {
        InvalidateVisual();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::OnLoaded(Noesis::BaseComponent*, const Noesis::RoutedEventArgs&)
{
    mViewContent = GetView()->GetContent();
    mViewContent->Unloaded() -= MakeDelegate(this, &MediaElement::OnViewDestroyed);
    mViewContent->Unloaded() += MakeDelegate(this, &MediaElement::OnViewDestroyed);

    UpdateState(mState, false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::OnUnloaded(Noesis::BaseComponent*, const Noesis::RoutedEventArgs&)
{
    UpdateState(mState, false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::OnViewDestroyed(Noesis::BaseComponent*, const Noesis::RoutedEventArgs&)
{
    mViewContent->Unloaded() -= MakeDelegate(this, &MediaElement::OnViewDestroyed);
    mViewContent = nullptr;

    DestroyMediaPlayer();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::OnBufferingStarted()
{
    mIsBuffering = true;
    RaiseEvent(Noesis::RoutedEventArgs(this, BufferingStartedEvent));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::OnBufferingEnded()
{
    mIsBuffering = false;
    RaiseEvent(Noesis::RoutedEventArgs(this, BufferingEndedEvent));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::OnMediaOpened()
{
    mPlayer->SetVolume(GetVolume());
    mPlayer->SetBalance(GetBalance());
    mPlayer->SetIsMuted(GetIsMuted());
    mPlayer->SetScrubbingEnabled(GetScrubbingEnabled());
    mPlayer->SetPosition(mPosition.GetSeconds());
    mPlayer->SetSpeedRatio(mSpeedRatio);

    mTextureSource.Reset(mPlayer->GetTextureSource());
    if (mTextureSource != nullptr)
    {
        InitComponent(mTextureSource, true);
        mTextureSource->Changed() += MakeDelegate(this, &MediaElement::OnTextureChanged);
    }

    InvalidateMeasure();
    InvalidateRender();

    RaiseEvent(Noesis::RoutedEventArgs(this, MediaOpenedEvent));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::OnMediaEnded()
{
    RaiseEvent(Noesis::RoutedEventArgs(this, MediaEndedEvent));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::OnMediaFailed(const char* error)
{
    RaiseEvent(ExceptionRoutedEventArgs(this, MediaFailedEvent, error));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::OnBalanceChanged(Noesis::DependencyObject* d,
    const Noesis::DependencyPropertyChangedEventArgs& e)
{
    MediaElement* element = (MediaElement*)d;
    if (element->mPlayer != nullptr)
    {
        element->mPlayer->SetBalance(e.NewValue<float>());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::OnIsMutedChanged(Noesis::DependencyObject* d,
    const Noesis::DependencyPropertyChangedEventArgs& e)
{
    MediaElement* element = (MediaElement*)d;
    if (element->mPlayer != nullptr)
    {
        element->mPlayer->SetIsMuted(e.NewValue<bool>());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::OnVolumeChanged(Noesis::DependencyObject* d,
    const Noesis::DependencyPropertyChangedEventArgs& e)
{
    MediaElement* element = (MediaElement*)d;
    if (element->mPlayer != nullptr)
    {
        element->mPlayer->SetVolume(e.NewValue<float>());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::OnScrubbingEnabledChanged(Noesis::DependencyObject* d,
    const Noesis::DependencyPropertyChangedEventArgs& e)
{
    MediaElement* element = (MediaElement*)d;
    if (element->mPlayer != nullptr)
    {
        element->mPlayer->SetScrubbingEnabled(e.NewValue<bool>());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MediaElement::OnStateChanged(Noesis::DependencyObject* d,
    const Noesis::DependencyPropertyChangedEventArgs& e)
{
    MediaElement* element = (MediaElement*)d;
    element->UpdateState(element->mState, e.prop == SourceProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(MediaElement, "MediaElement")
{
    NsProp("NaturalVideoWidth", &MediaElement::GetNaturalVideoWidth);
    NsProp("NaturalVideoHeight", &MediaElement::GetNaturalVideoHeight);
    NsProp("NaturalDuration", &MediaElement::GetNaturalDuration);
    NsProp("Position", &MediaElement::GetPosition, &MediaElement::SetPosition);
    NsProp("SpeedRatio", &MediaElement::GetSpeedRatio, &MediaElement::SetSpeedRatio);
    NsProp("CanPause", &MediaElement::CanPause);
    NsProp("HasAudio", &MediaElement::HasAudio);
    NsProp("HasVideo", &MediaElement::HasVideo);

    Noesis::UIElementData* data = NsMeta<Noesis::UIElementData>(Noesis::TypeOf<SelfClass>());
    data->RegisterProperty<float>(BalanceProperty, "Balance",
        Noesis::FrameworkPropertyMetadata::Create(0.0f,
            Noesis::PropertyChangedCallback(OnBalanceChanged)));
    data->RegisterProperty<bool>(IsMutedProperty, "IsMuted",
        Noesis::FrameworkPropertyMetadata::Create(false,
            Noesis::PropertyChangedCallback(OnIsMutedChanged)));
    data->RegisterProperty<MediaState>(LoadedBehaviorProperty, "LoadedBehavior",
        Noesis::FrameworkPropertyMetadata::Create(MediaState_Play,
            Noesis::PropertyChangedCallback(OnStateChanged)));
    data->RegisterProperty<bool>(ScrubbingEnabledProperty, "ScrubbingEnabled",
        Noesis::FrameworkPropertyMetadata::Create(false,
            Noesis::PropertyChangedCallback(OnScrubbingEnabledChanged)));
    data->RegisterProperty<Noesis::Uri>(SourceProperty, "Source",
        Noesis::FrameworkPropertyMetadata::Create(Noesis::Uri(),
            Noesis::FrameworkPropertyMetadataOptions_AffectsMeasure |
            Noesis::FrameworkPropertyMetadataOptions_AffectsRender,
            Noesis::PropertyChangedCallback(OnStateChanged)));
    data->RegisterProperty<Noesis::Stretch>(StretchProperty, "Stretch",
        Noesis::FrameworkPropertyMetadata::Create(Noesis::Stretch_Uniform,
            Noesis::FrameworkPropertyMetadataOptions_AffectsMeasure));
    data->RegisterProperty<Noesis::StretchDirection>(StretchDirectionProperty, "StretchDirection",
        Noesis::FrameworkPropertyMetadata::Create(Noesis::StretchDirection_Both,
            Noesis::FrameworkPropertyMetadataOptions_AffectsMeasure));
    data->RegisterProperty<MediaState>(UnloadedBehaviorProperty, "UnloadedBehavior",
        Noesis::FrameworkPropertyMetadata::Create(MediaState_Close,
            Noesis::PropertyChangedCallback(OnStateChanged)));
    data->RegisterProperty<float>(VolumeProperty, "Volume",
        Noesis::FrameworkPropertyMetadata::Create(0.5f,
            Noesis::PropertyChangedCallback(OnVolumeChanged)));

    data->RegisterEvent(BufferingEndedEvent, "BufferingEnded", Noesis::RoutingStrategy_Bubble);
    data->RegisterEvent(BufferingStartedEvent, "BufferingStarted", Noesis::RoutingStrategy_Bubble);
    data->RegisterEvent(MediaEndedEvent, "MediaEnded", Noesis::RoutingStrategy_Bubble);
    data->RegisterEvent(MediaFailedEvent, "MediaFailed", Noesis::RoutingStrategy_Bubble);
    data->RegisterEvent(MediaOpenedEvent, "MediaOpened", Noesis::RoutingStrategy_Bubble);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_IMPLEMENT_REFLECTION_ENUM(MediaState)
{
    NsVal("Manual", MediaState_Manual);
    NsVal("Play", MediaState_Play);
    NsVal("Close", MediaState_Close);
    NsVal("Pause", MediaState_Pause);
    NsVal("Stop", MediaState_Stop);
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* MediaElement::BalanceProperty;
const Noesis::DependencyProperty* MediaElement::IsMutedProperty;
const Noesis::DependencyProperty* MediaElement::LoadedBehaviorProperty;
const Noesis::DependencyProperty* MediaElement::ScrubbingEnabledProperty;
const Noesis::DependencyProperty* MediaElement::SourceProperty;
const Noesis::DependencyProperty* MediaElement::StretchProperty;
const Noesis::DependencyProperty* MediaElement::StretchDirectionProperty;
const Noesis::DependencyProperty* MediaElement::UnloadedBehaviorProperty;
const Noesis::DependencyProperty* MediaElement::VolumeProperty;

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::RoutedEvent* MediaElement::BufferingEndedEvent;
const Noesis::RoutedEvent* MediaElement::BufferingStartedEvent;
const Noesis::RoutedEvent* MediaElement::MediaEndedEvent;
const Noesis::RoutedEvent* MediaElement::MediaFailedEvent;
const Noesis::RoutedEvent* MediaElement::MediaOpenedEvent;
