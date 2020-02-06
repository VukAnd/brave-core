/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/browser/ui/webui/settings/brave_about_handler.h"
#include "chrome/browser/ui/webui/settings/about_handler.h"

#if defined(OS_MACOSX)
#include "brave/browser/ui/webui/settings/brave_settings_import_data_handler.h"
#endif

#define AboutHandler BraveAboutHandler

#if defined(OS_MACOSX)
#define ImportDataHandler BraveImportDataHandler
#endif

#include "../../../../../../../chrome/browser/ui/webui/settings/settings_ui.cc"
#undef AboutHandler

#if defined(OS_MACOSX)
#undef ImportDataHandler
#endif
