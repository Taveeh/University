import React from "react";
import { Container, Row, Col } from "reactstrap";
import Gallery from "react-photo-gallery";
import Carousel, { Modal, ModalGateway } from "react-images";
import "./Gallery.css";

const photos = [
  {
    src: `${require("../../assets/IMG-7705.JPG")}`,
    width: 4,
    height: 3
  },
  {
    src: `${require("../../assets/IMG-7706.JPG")}`,
    width: 4,
    height: 3
  },
  {
    src: `${require("../../assets/IMG-7707.JPG")}`,
    width: 4,
    height: 3
  },
  {
    src: `${require("../../assets/IMG-7708.JPG")}`,
    width: 4,
    height: 3
  },
  {
    src: `${require("../../assets/IMG-7709.JPG")}`,
    width: 4,
    height: 3
  },
  {
    src: `${require("../../assets/IMG-7710.JPG")}`,
    width: 4,
    height: 3
  },
  {
    src: `${require("../../assets/IMG-7711.JPG")}`,
    width: 4,
    height: 3
  },
  {
    src: `${require("../../assets/IMG-7712.JPG")}`,
    width: 4,
    height: 3
  },
  {
    src: `${require("../../assets/IMG-7713.JPG")}`,
    width: 4,
    height: 3
  },
  {
    src: `${require("../../assets/IMG-7714.JPG")}`,
    width: 4,
    height: 3
  },
  {
    src: `${require("../../assets/IMG-7715.JPG")}`,
    width: 3,
    height: 4
  }
];

class PhotoGallery extends React.Component {
  componentDidMount() {
    document.body.style = "background-color: #2a93d5;";
  }

  constructor() {
    super();
    this.state = {
      isCarouselOpen: false,
      currentIndex: 0
    };
    this.closeCarousel = this.closeCarousel.bind(this);
    this.openCarousel = this.openCarousel.bind(this);
  }

  openCarousel(_, obj) {
    this.setState({
      isCarouselOpen: true,
      currentIndex: obj.index
    });
  }

  closeCarousel() {
    this.setState({
      isCarouselOpen: false
    });
  }

  render() {
    return (
      <div className="Gallery">
        <Container>
          <Row>
            <Col xs="2" md="1" />
            <Col xs="8" md="10">
              <Gallery photos={photos} onClick={this.openCarousel} />
              <ModalGateway>
                {this.state.isCarouselOpen ? (
                  <Modal onClose={this.closeCarousel}>
                    <Carousel views={photos} currentIndex={this.state.currentIndex} />
                  </Modal>
                ) : null}
              </ModalGateway>
            </Col>
            <Col xs="2" md="1" />
          </Row>
        </Container>
      </div>
    );
  }
}

export default PhotoGallery;
