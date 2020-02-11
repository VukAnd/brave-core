/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "base/unguessable_token.h"

#include "base/format_macros.h"
#include "base/no_destructor.h"
#include "base/rand_util.h"
#include "base/strings/stringprintf.h"

namespace base {

UnguessableToken::UnguessableToken(const base::Token& token) : token_(token) {}

// static
UnguessableToken UnguessableToken::Create() {
  return UnguessableToken(Token::CreateRandom(), Token::CreateRandom());
}

UnguessableToken::UnguessableToken(const base::Token& token,
                                   const base::Token& token2)
    : token_(token), token2_(token2) {}

// static
const UnguessableToken& UnguessableToken::Null() {
  static const NoDestructor<UnguessableToken> null_token;
  return *null_token;
}

// static
UnguessableToken UnguessableToken::Deserialize(uint64_t high, uint64_t low) {
  // Receiving a zeroed out UnguessableToken from another process means that it
  // was never initialized via Create(). Treat this case as a security issue.
  DCHECK(!(high == 0 && low == 0));
  return UnguessableToken(Token{high, low}, Token());
}

// static
UnguessableToken UnguessableToken::Deserialize2(uint64_t high,
                                                uint64_t low,
                                                uint64_t high2,
                                                uint64_t low2) {
  DCHECK(!(high == 0 && low == 0));
  base::Token token = Token{high, low};
  base::Token token2 = Token{high2, low2};
  return UnguessableToken(token, token2);
}

std::ostream& operator<<(std::ostream& out, const UnguessableToken& token) {
  return out << "(" << token.ToString() << ")";
}

}  // namespace base
