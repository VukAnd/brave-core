/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

// Types
import ITheme from 'brave-ui/theme/theme-interface'
import IThemeNewTabPage from './newtab-theme'

// Theming utils
import darkTheme from 'brave-ui/theme/brave-dark'
import colors from 'brave-ui/theme/colors'

const newTabDarkTheme: ITheme & IThemeNewTabPage = {
  ...darkTheme,
  name: 'NewTab Dark',
  color: {
    ...darkTheme.color,
    contextMenuHoverBackground: colors.blurple500,
    contextMenuHoverForeground: colors.white
  }
}

export default newTabDarkTheme
