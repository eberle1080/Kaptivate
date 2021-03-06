/*
 * event_dispatcher.h
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

#include "stdafx.hpp"
#include "scoped_mutex.hpp"
#include "kaptivate_exceptions.hpp"

using namespace Kaptivate;

ScopedLock::ScopedLock(HANDLE mutex)
{
    hMutex = mutex;
    if(hMutex == 0 || WAIT_OBJECT_0 != WaitForSingleObject(hMutex, INFINITE))
        throw KaptivateException("Unable to aquire the lock");
}

ScopedLock::~ScopedLock()
{
    if(!ReleaseMutex(hMutex))
        throw KaptivateException("Unable to release the lock");
}

ScopedUnlock::ScopedUnlock(HANDLE mutex)
{
    hMutex = mutex;
    if(hMutex == 0 || !ReleaseMutex(hMutex))
        throw KaptivateException("Unable to release the lock");
}

ScopedUnlock::~ScopedUnlock()
{
    if(WAIT_OBJECT_0 != WaitForSingleObject(hMutex, INFINITE))
        throw KaptivateException("Unable to aquire the lock");
}

ScopedCriticalSection::ScopedCriticalSection(LPCRITICAL_SECTION criticalSection)
{
    this->criticalSection = criticalSection;
    if(this->criticalSection == NULL)
        throw KaptivateException("NULL critical section");
    EnterCriticalSection(this->criticalSection);
}

ScopedCriticalSection::~ScopedCriticalSection()
{
    LeaveCriticalSection(this->criticalSection);
}

ScopedNonCriticalSection::ScopedNonCriticalSection(LPCRITICAL_SECTION criticalSection)
{
    this->criticalSection = criticalSection;
    if(this->criticalSection == NULL)
        throw KaptivateException("NULL critical section");
    LeaveCriticalSection(this->criticalSection);
}

ScopedNonCriticalSection::~ScopedNonCriticalSection()
{
    EnterCriticalSection(this->criticalSection);
}
