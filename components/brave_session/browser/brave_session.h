/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "crypto/hmac.h"
#include "net/base/registry_controlled_domains/registry_controlled_domain.h"
#include "third_party/blink/public/platform/web_content_settings_client.h"
#include "third_party/blink/renderer/core/dom/document.h"
#include "third_party/blink/renderer/core/frame/local_dom_window.h"
#include "third_party/blink/renderer/core/frame/local_frame.h"
#include "third_party/blink/renderer/platform/bindings/script_state.h"

namespace blink {
double GetBraveFudgeFactor(Document* document) {
  double fudge_factor;
  if (document) {
    base::StringPiece host =
        base::StringPiece(document->TopFrameOrigin()->ToUrlOrigin().host());
    std::string domain = net::registry_controlled_domains::GetDomainAndRegistry(
        host, net::registry_controlled_domains::INCLUDE_PRIVATE_REGISTRIES);
    crypto::HMAC h(crypto::HMAC::SHA256);
    uint64_t key =
        document->GetFrame()->GetDevToolsFrameToken().GetSessionToken().high();
    CHECK(h.Init(reinterpret_cast<const unsigned char*>(&key), sizeof key));
    uint8_t domainkey[32];
    CHECK(h.Sign(domain, domainkey, sizeof domainkey));
    const uint64_t* fudge = reinterpret_cast<const uint64_t*>(&domainkey);
    const double maxUInt64AsDouble = 18446744073709551615.0;
    fudge_factor = 0.99 + ((*fudge / maxUInt64AsDouble) / 100);
  } else {
    fudge_factor = 0.0;
  }
  return fudge_factor;
}
}  // namespace blink
