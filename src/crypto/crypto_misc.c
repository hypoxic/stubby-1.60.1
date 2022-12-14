/*
 * Copyright (c) 2007, Cameron Rich
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, 
 *   this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice, 
 *   this list of conditions and the following disclaimer in the documentation 
 *   and/or other materials provided with the distribution.
 * * Neither the name of the axTLS project nor the names of its contributors 
 *   may be used to endorse or promote products derived from this software 
 *   without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifdef CONFIG_RSA_SIGNATURE

/**
 * Some misc. routines to help things out
 */

#include "asm/utils.h"
#include "string.h"
#include "crypto/crypto.h"
#if 0
#include "crypto_misc.h"
#ifdef CONFIG_WIN32_USE_CRYPTO_LIB
#include "wincrypt.h"
#endif

#ifndef WIN32
static int rng_fd = -1;
#elif defined(CONFIG_WIN32_USE_CRYPTO_LIB)
static HCRYPTPROV gCryptProv;
#endif

/* change to processor registers as appropriate */
#define ENTROPY_POOL_SIZE 32
#define ENTROPY_COUNTER1 ((((uint64_t)tv.tv_sec)<<32) | tv.tv_usec)
#define ENTROPY_COUNTER2 rand()
static uint8_t entropy_pool[ENTROPY_POOL_SIZE];

const char * const unsupported_str = "Error: Feature not supported\n";

#endif
#endif

