/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#define BRAVE_UNGUESSABLE_TOKEN_H                                        \
  UnguessableToken(const base::Token& token, const base::Token& token2); \
  static UnguessableToken Deserialize2(uint64_t high, uint64_t low,      \
                                       uint64_t high2, uint64_t low2);   \
  uint64_t GetHigh2ForSerialization() const { return token2_.high(); }   \
  uint64_t GetLow2ForSerialization() const { return token2_.low(); }     \
  base::Token GetSessionToken() const { return token2_; }                \
  void SetSessionToken(base::Token token) { token2_ = token; }

// This is split into two defines because we're defining a new field and order
// is enforced.
#define BRAVE_UNGUESSABLE_TOKEN_PRIVATE_H base::Token token2_;

#include "../../../../base/unguessable_token.h"

#undef BRAVE_UNGUESSABLE_TOKEN_H
#undef BRAVE_UNGUESSABLE_TOKEN_PRIVATE_H
