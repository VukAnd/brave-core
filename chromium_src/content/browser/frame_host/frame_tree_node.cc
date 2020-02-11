/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_session/browser/brave_session_token.h"

#define BRAVE_FRAMETREENODE_CONSTRUCTOR                                 \
  devtools_frame_token_.SetSessionToken(brave_session::GetSessionToken());

#include "../../../../../content/browser/frame_host/frame_tree_node.cc"

#undef BRAVE_FRAMETREENODE_CONSTRUCTOR
