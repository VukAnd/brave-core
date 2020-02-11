/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_session/browser/brave_session_token.h"

#include "base/token.h"

namespace {
base::Token session_token_;
}

namespace brave_session {

base::Token GetSessionToken() {
  if (session_token_.is_zero()) {
    session_token_ = base::Token::CreateRandom();
  }
  return session_token_;
}

}  // namespace brave_session
