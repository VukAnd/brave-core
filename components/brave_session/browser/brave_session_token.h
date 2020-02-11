/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef COMPONENTS_BRAVE_SESSION_BRAVE_SESSION_TOKEN_H_
#define COMPONENTS_BRAVE_SESSION_BRAVE_SESSION_TOKEN_H_

namespace base {
class Token;
}

namespace brave_session {

base::Token GetSessionToken();

}  // namespace brave_session

#endif  // COMPONENTS_BRAVE_SESSION_BRAVE_SESSION_TOKEN_H_
