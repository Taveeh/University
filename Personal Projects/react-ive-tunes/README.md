# react-ive-tunes

> Have you got a new album? Want to see people&#x27;s REACTions on it? Try ReactIveTunes NOW

[![NPM](https://img.shields.io/npm/v/react-ive-tunes.svg)](https://www.npmjs.com/package/react-ive-tunes) [![JavaScript Style Guide](https://img.shields.io/badge/code_style-standard-brightgreen.svg)](https://standardjs.com)

## Features
All the buttons you need:
- play/pause
- mute
- volume
- remove
- add
- previous
- next
- fullscreen

## How to implement

Pass an array of strings to the `dataSource` attribute, strings which represent direct links to video/audio files.
The `canModifyQueue` attribute shows/hides the add and remove buttons.

## Install

```bash
npm install --save react-ive-tunes
```

## Usage

```jsx
import React, { Component } from 'react'

import ReactIveTunes from 'react-ive-tunes'

class Example extends Component {
  var videos = ["link1", "link2", "link3"];
  render () {
    return (
      <ReactIveTunes dataSource={videos} canModifyQueue={true} />
    )
  }
}
```

## License

MIT © [tomadimitrie](https://github.com/tomadimitrie) ; [taveeh](https://github.com/taveeh)
