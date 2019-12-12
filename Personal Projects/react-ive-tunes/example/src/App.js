import React, { Component } from 'react'

import ReactIveTunes from 'react-ive-tunes'
export default class App extends Component {
  render () {
    var videos = [
      "http://192.162.137.9/vid/poke_s13/622.mp4?st=tvEG8Uee3hqI5XluLsqw1Q&e=1552516748", "http://techslides.com/demos/sample-videos/small.mp4", 
    "http://www.romanianvoice.com/sounds/arghezi/Tudor_Arghezi-Flori_de_mucigai.mp3"];
    return (
      <div style={{width: '500px', height: 'auto', position: 'fixed', left: '50%', marginLeft: '-250px', top: '50%', marginTop: '-150px', fontFamily: 'Comic Sans MS', textAlign: 'center'}}>
        <h1 style={{marginTop: '-150px', marginBottom: '100px', backgroundImage: 'linear-gradient(to right, #f22, #f2f 14.25%, #22f 28.5%, #2ff 42.75%, #2f2 57%, #2f2 71.25%, #ff2 85.5%, #f22)', color: 'black', fontSize: '25px'}}>
          ReactIve Tunes
        </h1>
        <ReactIveTunes dataSource={videos} canModifyQueue={true}/>
      </div>
    )
  }
}
