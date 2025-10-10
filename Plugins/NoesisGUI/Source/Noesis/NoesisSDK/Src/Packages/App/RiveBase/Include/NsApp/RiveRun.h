////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_RIVERUN_H__
#define __APP_RIVERUN_H__


#include <NsCore/Noesis.h>
#include <NsCore/Delegate.h>
#include <NsGui/Animatable.h>
#include <NsApp/RiveBaseApi.h>


namespace NoesisApp
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a text run in the RiveControl scene.
///
/// Each text run is identified by a name in the rive scene. The run exposes its text and it can be
/// set directly in the XAML or bound to properties of the data context.
/// 
/// .. code-block:: xml
///
///  <noesis:RiveControl Source="player.riv">
///    <noesis:RiveControl.Runs>
///      <noesis:RiveRun RunName="PlayerName" RunText="{Binding Player.Name}"/>
///    </noesis:RiveControl.Runs>
///  </noesis:RiveControl>
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_RIVEBASE_API RiveRun: public Noesis::Animatable
{
public:
    RiveRun();
    ~RiveRun();

    /// Gets or sets the name of the run you want to interact with
    //@{
    const char* GetRunName() const;
    void SetRunName(const char* name);
    //@}

    /// Gets or sets the run text
    //@{
    const char* GetRunText() const;
    void SetRunText(const char* text);
    //@}

    /// Occurs when text has changed
    typedef void TextChangedT(const char* name, const char* text);
    Noesis::Delegate<TextChangedT>& TextChanged();

public:
    /// Dependency properties
    //@{
    static const Noesis::DependencyProperty* RunNameProperty;
    static const Noesis::DependencyProperty* RunTextProperty;
    //@}

protected:
    /// From Freezable
    //@{
    Noesis::Ptr<Noesis::Freezable> CreateInstanceCore() const override;
    //@}

private:
    Noesis::Delegate<TextChangedT> mTextChanged;

    NS_DECLARE_REFLECTION(RiveRun, Noesis::Animatable)
};

NS_WARNING_POP

}


#endif
