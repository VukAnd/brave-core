/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BAT_ADS_INTERNAL_URI_HELPER_H_
#define BAT_ADS_INTERNAL_URI_HELPER_H_

#include <string>

namespace helper {

class Uri {
 public:
  static std::string GetUri(
      const std::string& url);

  static std::string GetValueForKeyInQuery(
      const std::string& url,
      const std::string& key);

  static bool MatchWildcard(
      const std::string& url,
      const std::string& pattern);
};

}  // namespace helper

#endif  // BAT_ADS_INTERNAL_URI_HELPER_H_
