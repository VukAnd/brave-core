/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#define BRAVE_REALTIMEANALYSER_H                                             \
  void SetFudgeFactor(double fudge_factor) { fudge_factor_ = fudge_factor; } \
                                                                             \
 private:                                                                    \
  double fudge_factor_;

#include "../../../../third_party/blink/renderer/modules/webaudio/realtime_analyser.h"

#undef BRAVE_REALTIMEANALYSER_H
