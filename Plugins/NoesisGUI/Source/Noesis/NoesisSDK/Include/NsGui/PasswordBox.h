////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_PASSWORDBOX_H__
#define __GUI_PASSWORDBOX_H__


#include <NsCore/Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Control.h>


namespace Noesis
{

class PasswordBoxTextContainer;
struct CanExecuteRoutedEventArgs;
struct ExecutedRoutedEventArgs;

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a control designed for entering and handling passwords.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.passwordbox.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API PasswordBox: public Control
{
public:
    PasswordBox();
    ~PasswordBox();

    /// Selects the entire contents of the PasswordBox
    void SelectAll();

    /// Gets or sets the brush that is used to paint the caret of the PasswordBox
    //@{
    Brush* GetCaretBrush() const;
    void SetCaretBrush(Brush* brush);
    //@}

    /// Gets or sets the maximum length for passwords to be handled by this PasswordBox
    //@{
    int GetMaxLength() const;
    void SetMaxLength(int length);
    //@}

    /// Gets or sets the masking character for the PasswordBox
    //@{
    uint32_t GetPasswordChar() const;
    void SetPasswordChar(uint32_t value);
    //@}

    /// Gets or sets the password currently held by the PasswordBox.
    //@{
    const char* GetPassword() const;
    void SetPassword(const char* password);
    //@}

    /// Gets or sets the placeholder text
    //@{
    const char* GetPlaceholder() const;
    void SetPlaceholder(const char* text);
    //@}

    /// Gets or sets the brush that highlights selected text
    //@{
    Brush* GetSelectionBrush() const;
    void SetSelectionBrush(Brush* selectionBrush);
    //@}

    /// Gets or sets the opacity of the *SelectionBrush*.
    /// If *SelectionOpacity* is set to 0, the *SelectionBrush* is transparent and is not visible.
    /// If *SelectionOpacity* is set to 1.0 or greater, the *SelectionBrush* is opaque and the
    /// selected text is not visible.
    //@{
    float GetSelectionOpacity() const;
    void SetSelectionOpacity(float selectionOpacity);
    //@}

    /// Gets or sets the duration in milliseconds that the last character typed in the PasswordBox
    /// remains visible before it is converted into the corresponding *PasswordChar*
    //@{
    uint32_t GetShowLastCharacterDuration() const;
    void SetShowLastCharacterDuration(uint32_t duration);
    //@}

    /// Removes the caret until control gets focused again
    void HideCaret();

    /// Occurs when password changes
    UIElement::RoutedEvent_<RoutedEventHandler> PasswordChanged();

public:
    static const DependencyProperty* CaretBrushProperty;
    static const DependencyProperty* MaxLengthProperty;
    static const DependencyProperty* PasswordCharProperty;
    static const DependencyProperty* PlaceholderProperty;
    static const DependencyProperty* SelectionBrushProperty;
    static const DependencyProperty* SelectionOpacityProperty;
    static const DependencyProperty* ShowLastCharacterDurationProperty;

    static const RoutedEvent* PasswordChangedEvent;

protected:
    // From DependencyObject
    //@{
    bool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args) override;
    //@}

    // From UIElement
    //@{
    void OnKeyDown(const KeyEventArgs& e) override;
    void OnTextInput(const TextCompositionEventArgs& e) override;
    void OnGotKeyboardFocus(const KeyboardFocusChangedEventArgs& e) override;
    void OnLostKeyboardFocus(const KeyboardFocusChangedEventArgs& e) override;
    void OnMouseLeftButtonDown(const MouseButtonEventArgs& e) override;
    void OnMouseLeftButtonUp(const MouseButtonEventArgs& e) override;
    void OnMouseMove(const MouseEventArgs& e) override;
    void OnTouchDown(const TouchEventArgs& e) override;
    void OnTapped(const TappedEventArgs& e) override;
    void OnDoubleTapped(const DoubleTappedEventArgs& e) override;
    //@}

    // From Control
    //@{
    void OnTemplateChanged(FrameworkTemplate* oldTemplate, FrameworkElement* oldRoot,
        FrameworkTemplate* newTemplate, FrameworkElement* newRoot) override;
    void OnMouseDoubleClick(const MouseButtonEventArgs& e) override;
    void OnIsFocusEngagedChanged(bool engaged) override;
    void UpdateVisualStates() override;
    //@}

private:
    void CancelTimer();
    uint32_t OnTimerElapsed();

private:
    Ptr<FrameworkElement> mContentHost;
    PasswordBoxTextContainer* mTextContainer;

    String mPassword;

    uint32_t mLastCharIndex;
    uint32_t mTimerId;

    union Flags
    {
        struct
        {
            bool mouseDown : 1;
            bool caretDisabled : 1;
            bool showLastChar : 1;
        } f;

        uint8_t all;
    };

    mutable Flags mFlags;

    NS_DECLARE_REFLECTION(PasswordBox, Control)
};

NS_WARNING_POP

}


#endif
