/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#define BRAVE_ANALYSERHANDLER_CONSTRUCTOR_PARAMS                       \
  AnalyserHandler::AnalyserHandler(AudioNode& node, float sample_rate, \
                                   double fudge_factor)

#define BRAVE_ANALYSERHANDLER_CONSTRUCTOR \
  analyser_.SetFudgeFactor(fudge_factor);

#define BRAVE_ANALYSERHANDLER_CREATE \
float sample_rate, \
  double fudge_factor) {             \
    return base::AdoptRef(new AnalyserHandler(node, sample_rate, fudge_factor));

#define BRAVE_ANALYSERNODE_CONSTRUCTOR                                   \
  fudge_factor_ =                                                        \
      AnalyserNode::GetFudgeFactor(To<Document>(GetExecutionContext())); \
  LOG(INFO) << "fudge factor = " << fudge_factor_;                       \
  SetHandler(                                                            \
      AnalyserHandler::Create(*this, context.sampleRate(), fudge_factor_));

#include "../../../../third_party/blink/renderer/modules/webaudio/analyser_node.cc"

#undef BRAVE_ANALYSERHANDLER_CONSTRUCTOR_PARAMS
#undef BRAVE_ANALYSERHANDLER_CONSTRUCTOR
#undef BRAVE_ANALYSERHANDLER_CREATE
#undef BRAVE_ANALYSERNODE_CONSTRUCTOR
