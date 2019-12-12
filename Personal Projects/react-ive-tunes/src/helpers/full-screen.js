export default class FullScreenHelper {
    static enable(element) {
      if (element.requestFullscreen) {
        element.requestFullscreen();
      } else if (element.webkitRequestFullscreen) {
        element.webkitRequestFullscreen();
      } else if (element.mozRequestFullScreen) {
        element.mozRequestFullScreen();
      } else if (element.msRequestFullscreen) {
        element.msRequestFullscreen();
      }
    }
  
    static disable() {
      if (document.exitFullscreen) {
        document.exitFullscreen();
      } else if (document.webkitExitFullscreen) {
        document.webkitExitFullscreen();
      } else if (document.mozCancelFullScreen) {
        document.mozCancelFullScreen();
      } else if (document.msExitFullscreen) {
        document.msExitFullscreen();
      }
    }
  
    static get isFullScreen() {
      return document.fullscreenElement || document.mozFullScreenElement || document.webkitFullscreenElement || document.msFullscreenElement;
    }
  
    onFullscreenChange(callback) {
      document.addEventListener('fullscreenchange', callback);
      document.addEventListener('webkitfullscreenchange', callback);
      document.addEventListener('mozfullscreenchange', callback);
      document.addEventListener('MSFullscreenChange', callback);
    }
  
    dispose(callback) {
      document.removeEventListener('fullscreenchange', callback);
      document.removeEventListener('webkitfullscreenchange', callback);
      document.removeEventListener('mozfullscreenchange', callback);
      document.removeEventListener('MSFullscreenChange', callback);
    }
  }
  