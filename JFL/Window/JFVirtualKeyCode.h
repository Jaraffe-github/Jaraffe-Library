//
//  File: JFVirtualKeyCode.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"

enum class JFVirtualKeyCode : uint32_t
{
    // Alphabetical Keys
    A = 0,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,

    // Numerical Keys
    Num0,
    Num1,
    Num2,
    Num3,
    Num4,
    Num5,
    Num6,
    Num7,
    Num8,
    Num9,

    // Symbol Keys
    Backslash,
    CloseBracket,
    Comma,
    EqualSign,
    Hyphen,
    NonUSBackslash,
    NonUSPound,
    OpenBracket,
    Period,
    Quote,
    Semicolon,
    Separator,
    Slash,
    Spacebar,

    // Modifier Keys
    CapsLock,
    LeftAlt,
    LeftControl,
    LeftShift,
    LockingCapsLock,
    LockingNumLock,
    LockingScrollLock,
    RightAlt,
    RightControl,
    RightShift,
    ScrollLock,

    // Navigation Keys
    LeftArrow,
    RightArrow,
    UpArrow,
    DownArrow,
    PageUp,
    PageDown,
    Home,
    End,
    DeleteForward,
    DeleteOrBackspace,
    Escape,
    Insert,
    Return,
    Tab,

    // Function Keys
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,

    // Keypad Keys
    keypad0,
    keypad1,
    keypad2,
    keypad3,
    keypad4,
    keypad5,
    keypad6,
    keypad7,
    keypad8,
    keypad9,
    keypadAsterisk,
    keypadComma,
    keypadEnter,
    keypadEqualSign,
    keypadEqualSignAS400,
    keypadHyphen,
    keypadNumLock,
    keypadPeriod,
    keypadPlus,
    keypadSlash,

    // Media Keys
    Pause,
    Stop,
    Mute,
    VolumeUp,
    VolumeDown,

    Max
};
