////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_MEDIAELEMENT_H__
#define __APP_MEDIAELEMENT_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsApp/MediaElementApi.h>
#include <NsGui/FrameworkElement.h>
#include <NsGui/Duration.h>
#include <NsGui/TimeSpan.h>


namespace Noesis
{
class ImageSource;
struct Uri;
enum Stretch: int32_t;
enum StretchDirection: int32_t;
}

namespace NoesisApp
{

class MediaPlayer;
class MediaElement;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Specifies the states that can be applied to a MediaElement for the LoadedBehavior and
/// UnloadedBehavior properties.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum MediaState: int32_t
{
    /// The state used to control a MediaElement manually. Interactive methods like Play and Pause
    /// can be used. Media will preroll but not play when the MediaElement is assigned a valid
    /// media source.
    MediaState_Manual,
    /// The state used to play the media. Media will preroll automatically being playback when the
    /// MediaElement is assigned a valid media source.
    MediaState_Play,
    /// The state used to close the media. All media resources are released including video memory.
    MediaState_Close,
    /// The state used to pause the media. Media will preroll but remains paused when the
    /// MediaElement is assigned a valid media source.
    MediaState_Pause,
    /// The state used to stop the media. Media will preroll but not play when the MediaElement is
    /// assigned a valid media source. Media resources are not released.
    MediaState_Stop
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Arguments to be passed in media failed event
////////////////////////////////////////////////////////////////////////////////////////////////////
struct ExceptionRoutedEventArgs: public Noesis::RoutedEventArgs
{
    const char* errorException;

    ExceptionRoutedEventArgs(Noesis::BaseComponent* source, const Noesis::RoutedEvent* event,
        const char* err);
};

typedef Noesis::Delegate<void (Noesis::BaseComponent*, const ExceptionRoutedEventArgs&)>
    ExceptionRoutedEventHandler;


NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a control that contains audio and/or video.
///
/// Until the *MediaOpened* event has been raised, the *ActualWidth* and *ActualHeight* of the
/// control will report as zero as the media content is used to determine the final size and
/// location of the control. For audio only content, these properties will always be zero.
///
/// *LoadedBehavior* must be set to *Manual* in order to interactively control media with the
/// *Play*, *Pause*, and *Stop* methods.
///
/// .. code-block:: xml
///
///  <Grid
///    xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///    xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml">
///    <MediaElement Source="video.mp4"/>
///  </Grid>
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.mediaelement.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_MEDIAELEMENT_API MediaElement: public Noesis::FrameworkElement
{
public:
    MediaElement();
    ~MediaElement();

    /// Sets the creation function for MediaPlayer implementation
    typedef Noesis::Ptr<MediaPlayer> (*CreateMediaPlayerCallback)(MediaElement* owner,
        const Noesis::Uri& uri, void* user);
    static void SetCreateMediaPlayerCallback(CreateMediaPlayerCallback callback, void* user);

    /// Gets or sets a value that describes how a MediaElement fills the destination rectangle.
    /// The default is Stretch.Uniform.
    //@{
    Noesis::Stretch GetStretch() const;
    void SetStretch(Noesis::Stretch value);
    //@}

    /// Gets or sets a value that determines the restrictions on scaling that are applied to this
    /// media element. The default is StretchDirection.Both.
    //@{
    Noesis::StretchDirection GetStretchDirection() const;
    void SetStretchDirection(Noesis::StretchDirection value);
    //@}

    /// Get a value indicating whether the media is buffering.
    bool IsBuffering() const;

    /// Gets the percentage of buffering completed for streaming content, represented in a value
    /// between 0 and 1.
    float GetBufferingProgress() const;

    /// Gets the percentage of download progress for content located at a remote server,
    /// represented by a value between 0 and 1. The default is 1.
    float GetDownloadProgress() const;

    /// Gets the pixel width of the video.
    uint32_t GetNaturalVideoWidth() const;

    /// Gets the pixel height of the video.
    uint32_t GetNaturalVideoHeight() const;

    /// Gets the natural duration of the media. The default is Duration.Automatic.
    const Noesis::Duration& GetNaturalDuration() const;

    /// Gets or sets the current position of the media (seek operations).
    //@{
    const Noesis::TimeSpan& GetPosition() const;
    void SetPosition(const Noesis::TimeSpan& value);
    //@}

    /// Gets or sets the ratio of speed that media is played at.
    /// Represented by a value between 0 and the largest double value. The default is 1.0.
    //@{
    float GetSpeedRatio() const;
    void SetSpeedRatio(float value);
    //@}

    /// Gets a value indicating whether the media can be paused.
    bool CanPause() const;

    /// Gets a value that indicating whether the media has audio output.
    bool HasAudio() const;

    /// Gets a value that indicates whether the media has video output.
    bool HasVideo() const;

    /// Gets or sets the media source.
    //@{
    const Noesis::Uri& GetSource() const;
    void SetSource(const Noesis::Uri& value);
    //@}

    /// Gets or sets a value that indicates whether the media is muted.
    //@{
    bool GetIsMuted() const;
    void SetIsMuted(bool value);
    //@}

    /// Gets or sets the media's volume.
    /// Represented on a linear scale between 0 and 1. The default is 0.5.
    //@{
    float GetVolume() const;
    void SetVolume(float value);
    //@}

    /// Gets or sets the balance between the left and right speaker volumes.
    /// Represented in a range between -1 (left) and 1 (right). The default is 0.
    //@{
    float GetBalance() const;
    void SetBalance(float value);
    //@}

    /// Gets or sets a value that indicates whether the MediaElement will update frames for
    /// seek operations while paused. The default is false.
    //@{
    bool GetScrubbingEnabled() const;
    void SetScrubbingEnabled(bool value);
    //@}

    /// Gets or sets the load behavior MediaState for the media.
    /// The default value is Play.
    //@{
    MediaState GetLoadedBehavior() const;
    void SetLoadedBehavior(MediaState value);
    //@}

    /// Gets or sets the unload behavior MediaState for the media.
    /// The default value is Close.
    //@{
    MediaState GetUnloadedBehavior() const;
    void SetUnloadedBehavior(MediaState value);
    //@}

    /// Plays media from the current position.
    void Play();

    /// Pauses media playback.
    void Pause();

    /// Stops media playback.
    void Stop();

    /// Closes the underlying media.
    void Close();

    /// Events
    //@{

    /// Occurs when media loading has finished.
    RoutedEvent_<Noesis::RoutedEventHandler> BufferingStarted();

    /// Occurs when media loading has finished.
    RoutedEvent_<Noesis::RoutedEventHandler> BufferingEnded();

    /// Occurs when an error is encountered.
    RoutedEvent_<ExceptionRoutedEventHandler> MediaFailed();

    /// Occurs when media loading has finished.
    RoutedEvent_<Noesis::RoutedEventHandler> MediaOpened();

    /// Occurs when the media has ended.
    RoutedEvent_<Noesis::RoutedEventHandler> MediaEnded();

    //@}

public:
    /// Dependency properties
    //@{
    static const Noesis::DependencyProperty* BalanceProperty;
    static const Noesis::DependencyProperty* IsMutedProperty;
    static const Noesis::DependencyProperty* LoadedBehaviorProperty;
    static const Noesis::DependencyProperty* ScrubbingEnabledProperty;
    static const Noesis::DependencyProperty* SourceProperty;
    static const Noesis::DependencyProperty* StretchProperty;
    static const Noesis::DependencyProperty* StretchDirectionProperty;
    static const Noesis::DependencyProperty* UnloadedBehaviorProperty;
    static const Noesis::DependencyProperty* VolumeProperty;
    //@}

    /// Routed events
    //@{
    static const Noesis::RoutedEvent* BufferingEndedEvent;
    static const Noesis::RoutedEvent* BufferingStartedEvent;
    static const Noesis::RoutedEvent* MediaEndedEvent;
    static const Noesis::RoutedEvent* MediaFailedEvent;
    static const Noesis::RoutedEvent* MediaOpenedEvent;
    //@}

protected:
    /// From UIElement
    //@{
    void OnRender(Noesis::DrawingContext* context) override;
    //@}

    /// From FrameworkElement
    //@{
    Noesis::Size MeasureOverride(const Noesis::Size& availableSize) override;
    Noesis::Size ArrangeOverride(const Noesis::Size& finalSize) override;
    //@}

private:
    Noesis::Size MeasureArranageSize(const Noesis::Size& size);

    void SetState(MediaState state);
    void UpdateState(MediaState action, bool sourceChanged);

    void CreateMediaPlayer(const Noesis::Uri& source);
    void DestroyMediaPlayer();

    void OnTextureChanged(Noesis::Freezable* freezable, Noesis::FreezableEventReason reason);

    void OnLoaded(Noesis::BaseComponent* sender, const Noesis::RoutedEventArgs& e);
    void OnUnloaded(Noesis::BaseComponent* sender, const Noesis::RoutedEventArgs& e);

    void OnViewDestroyed(Noesis::BaseComponent* sender, const Noesis::RoutedEventArgs& e);

    void OnBufferingStarted();
    void OnBufferingEnded();
    void OnMediaOpened();
    void OnMediaEnded();
    void OnMediaFailed(const char* error);

    static void OnBalanceChanged(Noesis::DependencyObject* d,
        const Noesis::DependencyPropertyChangedEventArgs& e);
    static void OnIsMutedChanged(Noesis::DependencyObject* d,
        const Noesis::DependencyPropertyChangedEventArgs& e);
    static void OnVolumeChanged(Noesis::DependencyObject* d,
        const Noesis::DependencyPropertyChangedEventArgs& e);
    static void OnStateChanged(Noesis::DependencyObject* d,
        const Noesis::DependencyPropertyChangedEventArgs& e);
    static void OnScrubbingEnabledChanged(Noesis::DependencyObject* d,
        const Noesis::DependencyPropertyChangedEventArgs& e);

private:
    Noesis::Ptr<MediaPlayer> mPlayer;
    Noesis::Ptr<Noesis::ImageSource> mTextureSource;
    Noesis::FrameworkElement* mViewContent;
    MediaState mState;
    mutable Noesis::Duration mDuration;
    mutable Noesis::TimeSpan mPosition;
    mutable float mSpeedRatio;
    mutable bool mIsBuffering;

    NS_DECLARE_REFLECTION(MediaElement, Noesis::FrameworkElement)
};

NS_WARNING_POP

}


NS_DECLARE_REFLECTION_ENUM_EXPORT(NS_APP_MEDIAELEMENT_API, NoesisApp::MediaState)


#endif
