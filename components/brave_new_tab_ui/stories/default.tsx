/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import * as React from 'react'
import { storiesOf } from '@storybook/react'
import { withKnobs, select, boolean } from '@storybook/addon-knobs/react'

// Components
import NewTabPage from './default/index'
import { withThemesProvider } from 'storybook-addon-styled-component-theme'

// Themes
import newTabLightTheme from '../theme/newtab-light'
import newTabDarkTheme from '../theme/newtab-dark'
const themes = [newTabLightTheme, newTabDarkTheme]

storiesOf('New Tab/Default', module)
  .addDecorator(withThemesProvider(themes))
  .addDecorator(withKnobs)
  .add('Page', () => {
    return (
      <NewTabPage
        textDirection={select('Text direction', { ltr: 'ltr', rtl: 'rtl' } , 'ltr')}
        showBrandedWallpaper={boolean('Show branded wallpaper?', false)}
        showTopSitesNotification={boolean('Show top sites notification?', false)}
        isAdsOn={boolean('Ads on?', true)}
        isAdsSupported={boolean('Ads region supported?', true)}
      />
    )
  })
