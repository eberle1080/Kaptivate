/*
 * device_handler_map.h
 * This file is a part of Kaptivate
 * https://github.com/FunkyTownEnterprises/Kaptivate
 *
 * Copyright (c) 2011 Ben Cable, Chris Eberle
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <vector>
#include <iostream>

namespace Kaptivate
{
    class KeyboardEvent;
    class MouseButtonEvent;
    class MouseWheelEvent;
    class MouseMoveEvent;
    class KeyboardHandler;
    class MouseHandler;
    struct KeyboardInfo;
    struct MouseInfo;

    class DeviceHandlerMap
    {
    private:
        void scanDevices();

    public:
        DeviceHandlerMap();
        ~DeviceHandlerMap();

        void handleKeyboard(HANDLE deviceID, KeyboardEvent& evt);
        void handleMouseButton(HANDLE deviceID, MouseButtonEvent& evt);
        void handleMouseWheel(HANDLE deviceID, MouseWheelEvent& evt);
        void handleMouseMove(HANDLE deviceID, MouseMoveEvent& evt);

        std::vector<KeyboardInfo> enumerateKeyboards();
        std::vector<MouseInfo> enumerateMice();

        void registerKeyboardHandler(std::string idRegex, KeyboardHandler* handler);
        void resgisterMouseHandler(std::string idRegex, MouseHandler* handler);
        void unregisterKeyboardHandler(KeyboardHandler* handler);
        void unregisterMouseHandler(MouseHandler* handler);
    };
}
