import React, { Component } from 'react';
import * as Rx from 'rxjs';
import FullScreenHelper from './helpers/full-screen';
import styles from './styles.module.css';

export default class ReactIveTunes extends Component {

  videos$ = new Rx.Subject();
  videoArray = [];
  timer = null;
  previousVolume = 100;
  hoverTimeout = null;

  constructor(props) {
    super(props);
    this.videos$.subscribe((item) => {
      this.videoArray.push(item);
    });
    for (var i = 0; i < props.dataSource.length; ++i) {
      this.videos$.next(props.dataSource[i]);
    }
    this.videoRef = React.createRef();
    this.audioRef = React.createRef();
    this.divRef = React.createRef();
    this.inputRef = React.createRef();
    this.state = {
      isMuted: false,
      currentIndex: 0,
      isPlaying: false,
      isHovered: false,
      currentTime: 0,
      totalTime: 0,
      sliderValue: 1,
      volumeValue: 100,
      isLoaded: false
    }
  }

  componentDidMount = () => {
    this.timer = setInterval(() => {
      const currentVideo = this.videoArray[this.state.currentIndex];
      const sliderValue = Math.floor(this.audioRef.current.currentTime / (this.audioRef.current.duration + 1) * 100);
      this.setState({
        totalTime: this.audioRef.current.duration,
        currentTime: this.audioRef.current.currentTime,
        sliderValue: isNaN(sliderValue) ? 1 : sliderValue
      });
    }, 500);
    this.divRef.current.addEventListener('mousemove', e => {
      clearTimeout(this.hoverTimeout);
      this.hoverTimeout = setTimeout(() => {
        this.setState({
          isHovered: false
        });
      }, 2000);
      const pos = this.getMousePos(this.divRef.current, e);
      var y = this.state.isVolumeHovered ? 100 : 30;
      if (pos.x > 60 && pos.x < 90 && pos.y > 0 && pos.y < y) {
        this.onVolumeHover();
      } else {
        this.onVolumeNoHover();
        this.onHover();
      }
    });
    setInterval(() => {
      const currentVideo = this.videoArray[this.state.currentIndex];
      this.setState({
        isLoaded: this.audioRef.current.readyState === 4,
        isPlaying: !!!!!this.audioRef.current.paused
      });
    }, 250);
  }

  getMousePos(canvas, evt) {
    var rect = canvas.getBoundingClientRect(), root = document.documentElement;
    var mouseX = evt.clientX - rect.left - root.scrollLeft;
    var mouseY = evt.clientY - rect.top - root.scrollTop;
    return {
      x: mouseX,
      y: canvas.clientHeight - mouseY
    };
  }

  addVideo = () => {
    var result = prompt("Enter video link:");
    this.videos$.next(result);
  }

  removeVideo = () => {
    var flag = false;
    if (this.state.currentIndex === this.videoArray.length - 1) {
      this.setState({
        currentIndex: this.state.currentIndex - 1
      });
      flag = true;
    } else {
      this.forceUpdate();
    }
    this.videoArray.splice(flag ? this.state.currentIndex + 1 : this.state.currentIndex, 1);
    this.videoRef.current.load();
    this.audioRef.current.load();
  }

  playPause = e => {
    e.preventDefault();
    const currentVideo = this.videoArray[this.state.currentIndex];
    if (this.audioRef.current.paused) {
      this.audioRef.current.play();
    } else {
      this.audioRef.current.pause();
    }
    if (this.videoRef.current.paused) {
      this.videoRef.current.play();
    } else {
      this.videoRef.current.pause();
    }
  }

  mute = e => {
    e.preventDefault();
    const flag = this.state.isMuted;
    if (!flag) {
      this.previousVolume = this.state.volumeValue;
    }
    this.setState({
      isMuted: !flag,
      volumeValue: flag ? this.previousVolume : 0
    });
  }

  previous = e => {
    e.preventDefault();
    if (this.state.currentIndex > 0) {
      this.setState({
        currentIndex: this.state.currentIndex - 1
      });
      this.videoRef.current.load();
      this.audioRef.current.load();
    }
  }

  next = e => {
    e.preventDefault();
    if (this.state.currentIndex != this.videoArray.length - 1) {
      this.setState({
        currentIndex: this.state.currentIndex + 1
      });
      this.videoRef.current.load();
      this.audioRef.current.load();
    }
  }

  fullscreen = e => {
    e.preventDefault();
    if (FullScreenHelper.isFullScreen) {
      FullScreenHelper.disable();
    } else {
      FullScreenHelper.enable(this.divRef.current);
    }
  }

  onHover = () => {
    this.setState({
      isHovered: true
    });
  }

  onNoHover = e => {
    e.preventDefault();
    this.setState({
      isHovered: false
    });
  }

  onSliderChange = e => {
    e.preventDefault();
    this.setState({
      sliderValue: event.target.value
    });
    const currentVideo = this.videoArray[this.state.currentIndex];
    if (e.target.value == 1) {
      this.audioRef.current.currentTime = 0;
      this.videoRef.current.currentTime = 0;
    } else {
      this.audioRef.current.currentTime = Math.floor(event.target.value * this.state.totalTime / 100);
      this.videoRef.current.currentTime = Math.floor(event.target.value * this.state.totalTime / 100);
    }
  }

  renderCurrentTime = () => {
    const timeInSeconds = Math.floor(this.state.currentTime);
    return this.formatTime(timeInSeconds);
  }

  renderTotalTime = () => {
    const timeInSeconds = Math.floor(this.state.totalTime);
    return this.formatTime(timeInSeconds);
  }

  formatTime = time => {
    if (isNaN(time)) {
      return "00:00";
    }
    var formattedTime = "";
    if (time / 60 < 10) {
      formattedTime += 0;
    }
    formattedTime += Math.floor(time / 60);
    formattedTime += ":";
    const seconds = time - Math.floor(time / 60) * 60;
    if (seconds < 10) {
      formattedTime += 0;
    }
    formattedTime += seconds;
    return formattedTime;
  }

  onVolumeHover = () => {
    this.setState({
      isVolumeHovered: true
    });
  }

  onVolumeNoHover = () => {
    this.setState({
      isVolumeHovered: false
    });
  }

  doNothing = () => {

  }

  onVolumeChange = e => {
    e.preventDefault();
    this.setState({
      volumeValue: event.target.value
    });
    if (e.target.value == 1) {
      this.audioRef.current.volume = 0;
    } else {
      this.audioRef.current.volume = event.target.value / 100;
    }
  }

  isAudio = file => {
    return file.includes('.mp3') || file.includes('.ogg') || file.includes('.wav');
  }

  isVideo = file => {
    return file.includes('.mp4') || file.includes('.webm');
  }

  render() {
    const currentVideo = this.videoArray[this.state.currentIndex];
    return (
      <div>
        <div ref={this.divRef} className={styles.videoContainer} onMouseLeave={this.onNoHover} style={{ backgroundColor: 'black' }}>
          <div className={styles.spinnerContainer} style={{ display: this.state.isLoaded ? 'none' : 'block' }}>
            <div className={styles.spinner}><div></div><div></div><div></div><div></div><div></div><div></div><div></div><div></div><div></div></div>
          </div>
          <video width="100%" height="auto" ref={this.videoRef} muted={true} loop>
            <source src={this.isAudio(currentVideo) ? require('../assets/Music.mp4') : currentVideo}></source>
          </video>
          <audio ref={this.audioRef} style={{ opacity: 0 }} muted={this.state.isMuted}>
            <source src={currentVideo} />
          </audio>
          <div style={{ display: this.state.isHovered ? 'block' : 'none' }} className={styles.controlBar}></div>
          <input style={{ display: this.state.isHovered ? 'block' : 'none' }} type="range" min="1" max="100" value={this.state.sliderValue} className={styles.progressBar} onInput={this.onSliderChange} onChange={this.doNothing} />
          <div style={{ display: this.state.isHovered ? 'block' : 'none' }}>
            <div className={styles.playPauseContainer}>
              <img src={this.state.isPlaying ? require('../assets/pause.png') : require('../assets/play.png')} className={styles.playPauseButton} onClick={this.playPause} />
            </div>
            <div className={styles.muteContainer}>
              <img src={require('../assets/mute.png')} className={styles.muteButton} onClick={this.mute} />
            </div>
            <div className={styles.volumeButtonContainer}>
              <img src={this.state.isVolumeHovered ? require('../assets/nothing.png') : require('../assets/volume.png')} className={styles.volumeButton} />
            </div>
            <div className={styles.volumeContainer} style={{ display: this.state.isVolumeHovered ? 'block' : 'none' }}>
              <input type="range" min="1" max="100" value={this.state.volumeValue} className={styles.volumeBar} onInput={this.onVolumeChange} onChange={this.doNothing} />
            </div>
            <div className={styles.timeContainer}>
              <div className={styles.time}>
                {this.renderCurrentTime()} - {this.renderTotalTime()}
              </div>
            </div>
            {this.props.canModifyQueue && <div className={styles.uploadContainer}>
              <img src={require('../assets/add.png')} className={styles.uploadButton} onClick={this.addVideo} />
            </div>}
            {this.props.canModifyQueue && <div className={styles.removeContainer}>
              <img src={require('../assets/remove.png')} className={styles.removeButton} onClick={this.removeVideo} />
            </div>}
            <div className={styles.previousContainer}>
              <img src={require('../assets/previous.png')} className={styles.previousButton} onClick={this.previous} />
            </div>
            <div className={styles.nextContainer}>
              <img src={require('../assets/next.png')} className={styles.nextButton} onClick={this.next} />
            </div>
            <div className={styles.fullscreenContainer}>
              <img src={FullScreenHelper.isFullScreen ? require('../assets/smallscreen.png') : require('../assets/fullscreen.png')} className={styles.fullscreenButton} onClick={this.fullscreen} />
            </div>
          </div>
        </div>
      </div>
    )
  }
}
