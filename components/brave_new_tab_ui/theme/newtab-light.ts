/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

// Types
import ITheme from 'brave-ui/theme/theme-interface'
import IThemeNewTabPage from './newtab-theme'

// Theming utils
import lightTheme from 'brave-ui/theme/brave-default'
import colors from 'brave-ui/theme/colors'

const newtabLightTheme: ITheme & IThemeNewTabPage = {
  ...lightTheme,
  name: 'NewTab Light',
  color: {
    ...lightTheme.color,
    contextMenuHoverBackground: colors.blurple200,
    contextMenuHoverForeground: colors.neutral800
  }
}

export default newtabLightTheme
