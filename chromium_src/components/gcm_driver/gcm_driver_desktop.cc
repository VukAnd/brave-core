/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "components/gcm_driver/gcm_buildflags.h"

#if !BUILDFLAG(USE_GCM_FROM_PLATFORM)
#include "brave/browser/gcm_driver/brave_gcm_channel_status.h"
#endif

namespace {

bool IsGCMEnabled() {
#if BUILDFLAG(USE_GCM_FROM_PLATFORM)
  return true;
#else
  //gcm::BraveGCMChannelStatus* gcm_channel_status =
  //    gcm::BraveGCMChannelStatus::GetForProfile(profile);
  //DCHECK(gcm_channel_status);
  //return gcm_channel_status->IsGCMEnabled();
  return false;
#endif
}

}  // namespace

#define BRAVE_GCMDRIVERDESKTOP_ENSURESTARTED \
  if (!IsGCMEnabled())                       \
    return GCMClient::GCM_DISABLED;

#include "../../../../components/gcm_driver/gcm_driver_desktop.cc"
#undef BRAVE_GCMDRIVERDESKTOP_ENSURESTARTED
