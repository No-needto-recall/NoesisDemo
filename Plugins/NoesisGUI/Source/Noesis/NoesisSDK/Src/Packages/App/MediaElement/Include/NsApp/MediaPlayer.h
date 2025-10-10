////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_MEDIAPLAYER_H__
#define __APP_MEDIAPLAYER_H__


#include <NsCore/Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/Delegate.h>
#include <NsApp/MediaElementApi.h>


namespace Noesis
{
class ImageSource;
}

namespace NoesisApp
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Abstract class for the implementation of audio/video in a MediaElement.
///
/// Each platform must provide an implementation for this class and pass it to MediaElement by 
/// calling *MediaElement::SetCreateMediaPlayerCallback*.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_MEDIAELEMENT_API MediaPlayer: public Noesis::BaseComponent
{
public:
    MediaPlayer();
    MediaPlayer(const MediaPlayer&) = delete;
    MediaPlayer& operator=(const MediaPlayer&) = delete;

    /// Gets the pixel width of the video
    /// \prop
    virtual uint32_t GetWidth() const;

    /// Gets the pixel height of the video
    /// \prop
    virtual uint32_t GetHeight() const;

    /// Gets a value indicating whether the media can be paused
    /// \prop
    virtual bool CanPause() const;

    /// Gets a value that indicating whether the media has audio output
    virtual bool HasAudio() const;

    /// Gets a value that indicates whether the media has video output
    virtual bool HasVideo() const;

    /// Gets the percentage of buffering completed for streaming content, represented in a value
    /// between 0 and 1
    /// \prop
    virtual float GetBufferingProgress() const;

    /// Gets the percentage of download progress for content located at a remote server,
    /// represented by a value between 0 and 1. The default is 1
    /// \prop
    virtual float GetDownloadProgress() const;

    /// Gets the duration in seconds of the media
    /// \prop
    virtual double GetDuration() const;

    /// Gets or sets the current position in seconds of the media
    /// \prop
    //@{
    virtual double GetPosition() const;
    virtual void SetPosition(double position);
    //@}

    /// Gets or sets the ratio of speed that media is played at, represented by a value between 0
    /// and the largest float. The default is 1
    /// \prop
    //@{
    virtual float GetSpeedRatio() const;
    virtual void SetSpeedRatio(float speedRatio);
    //@}

    /// Gets or sets the media's volume, represented on a linear scale between 0 and 1. The default
    /// is 0.5
    /// \prop
    //@{
    virtual float GetVolume() const;
    virtual void SetVolume(float volume);
    //@}

    /// Gets or sets the balance between the left and right speaker volumes, represented in a range
    /// between -1 and 1. The default is 0
    /// \prop
    //@{
    virtual float GetBalance() const;
    virtual void SetBalance(float balance);
    //@}

    /// Gets or sets a value that indicates whether the media is muted. The default is false
    /// \prop
    //@{
    virtual bool GetIsMuted() const;
    virtual void SetIsMuted(bool muted);
    //@}

    /// Gets or sets a value that indicates whether the media player will update frames for seek
    /// operations while paused. The default is false
    /// \prop
    //@{
    virtual bool GetScrubbingEnabled() const;
    virtual void SetScrubbingEnabled(bool scrubbing);
    //@}

    /// Starts or resumes media playback
    virtual void Play();

    /// Pauses media playback
    virtual void Pause();

    /// Stops media playback and moves position to the begining
    virtual void Stop();

    /// Gets the texture source for rendering the video
    virtual Noesis::ImageSource* GetTextureSource() const = 0;

    typedef void BufferingStartedT();
    typedef void BufferingEndedT();
    typedef void MediaFailedT(const char* error);
    typedef void MediaOpenedT();
    typedef void MediaEndedT();

    /// Occurs when buffering has started
    Noesis::Delegate<BufferingStartedT>& BufferingStarted();

    /// Occurs when buffering has finished
    Noesis::Delegate<BufferingEndedT>& BufferingEnded();

    /// Occurs when an error is encountered
    Noesis::Delegate<MediaFailedT>& MediaFailed();

    /// Occurs when the media is opened
    Noesis::Delegate<MediaOpenedT>& MediaOpened();

    /// Occurs when the media has finished playback
    Noesis::Delegate<MediaEndedT>& MediaEnded();

protected:
    Noesis::Delegate<BufferingStartedT> mBufferingStarted;
    Noesis::Delegate<BufferingEndedT> mBufferingEnded;
    Noesis::Delegate<MediaFailedT> mMediaFailed;
    Noesis::Delegate<MediaOpenedT> mMediaOpened;
    Noesis::Delegate<MediaEndedT> mMediaEnded;
};

NS_WARNING_POP

}


#endif
