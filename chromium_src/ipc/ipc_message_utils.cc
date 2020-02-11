/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#define BRAVE_IPC_MESSAGE_UTILS_UNGUESSABLETOKEN_ASSERT       \
  static_assert(                                              \
      sizeof(base::UnguessableToken) == 4 * sizeof(uint64_t), \
      "base::UnguessableToken should be of size 4 * sizeof(uint64_t).");

#define BRAVE_IPC_MESSAGE_UTILS_UNGUESSABLETOKEN_WRITE           \
  ParamTraits<uint64_t>::Write(m, p.GetHigh2ForSerialization()); \
  ParamTraits<uint64_t>::Write(m, p.GetLow2ForSerialization());

#define BRAVE_IPC_MESSAGE_UTILS_UNGUESSABLETOKEN_READ                \
  uint64_t high, low;                                                \
  uint64_t high2, low2;                                              \
  if (!ParamTraits<uint64_t>::Read(m, iter, &high) ||                \
      !ParamTraits<uint64_t>::Read(m, iter, &low) ||                 \
      !ParamTraits<uint64_t>::Read(m, iter, &high2) ||               \
      !ParamTraits<uint64_t>::Read(m, iter, &low2))                  \
    return false;                                                    \
  if (high == 0 && low == 0)                                         \
    return false;                                                    \
  *r = base::UnguessableToken::Deserialize2(high, low, high2, low2); \
  return true;

#include "../../../../ipc/ipc_message_utils.cc"

#undef BRAVE_IPC_MESSAGE_UTILS_UNGUESSABLETOKEN_ASSERT
#undef BRAVE_IPC_MESSAGE_UTILS_UNGUESSABLETOKEN_WRITE
#undef BRAVE_IPC_MESSAGE_UTILS_UNGUESSABLETOKEN_READ
