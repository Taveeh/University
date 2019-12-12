import React from "react";
import { Container, Row, Col } from "reactstrap";
import "./News.css";
import * as firebase from "firebase/app";
import "firebase/firestore";
import Carousel, { Modal, ModalGateway } from "react-images";

class AndreeaEsca {
  title = "";
  body = "";
  id = "";
  images = "";

  constructor(title, body, id, images) {
    this.title = title;
    this.body = body;
    this.id = id;
    this.images = images;
  }
}

class BusuDeLaVreme extends React.Component {
  title = this.props.observator.title;
  images = this.props.observator.images;
  body = this.props.observator.body;
  longBody = this.props.observator.body;
  buttonTitle = "Citește mai mult";
  wasPressed = false;
  shouldShowButton = false;

  constructor(props) {
    super(props);
    if (this.body.length > 191) {
      this.body = this.body.substring(0, 190) + "...";
      this.shouldShowButton = true;
    }
    if (this.images && this.images.length > 0) {
      this.shouldShowButton = true;
    }
    this.state = {
      title: this.title,
      body: this.body,
      buttonTitle: this.buttonTitle,
      images: this.images,
      isCarouselOpen: false,
      currentIndex: 0
    };
    this.closeCarousel = this.closeCarousel.bind(this);
    this.openCarousel = this.openCarousel.bind(this);
  }

  openCarousel(index) {
    this.setState({
      isCarouselOpen: true,
      currentIndex: index
    });
  }

  closeCarousel() {
    this.setState({
      isCarouselOpen: false
    });
  }

  readMore() {
    this.wasPressed = !this.wasPressed;
    this.setState({
      body: this.wasPressed ? this.longBody : this.body,
      buttonTitle: this.wasPressed ? "Citește mai puțin" : "Citește mai mult"
    });
  }

  render() {
    return (
      <div key={this.props.observator.id} id="newsOuterDiv">
        <div id="chenarTitlu">
          <p>{this.state.title}</p>
        </div>
        <div id="chenarText">
          <p>{this.state.body}</p>
        </div>
        {this.wasPressed && this.state.images && this.state.images.length > 0 && (
          <div id="images">
            {this.state.images.map((image, index) => (
              <img
                src={image}
                key={index}
                alt=""
                className="news-image"
                onClick={() => this.openCarousel(index)}
              />
            ))}
          </div>
        )}
        {this.shouldShowButton && (
          <button id="button" color="primary" onClick={() => this.readMore()}>
            {this.state.buttonTitle}
          </button>
        )}
        <ModalGateway>
          {this.state.isCarouselOpen ? (
            <Modal onClose={this.closeCarousel}>
              <Carousel
                views={this.state.images.map(image => ({ src: image }))}
                currentIndex={this.state.currentIndex}
              />
            </Modal>
          ) : null}
        </ModalGateway>
      </div>
    );
  }
}

class News extends React.Component {
  constructor(props) {
    super(props);
    const db = firebase.firestore();
    this.state = {
      stirileProTv: []
    };
    db.collection("news")
      .get()
      .then(snapshot => {
        const documents = snapshot.docs;
        const data = documents
          .map(
            doc =>
              new AndreeaEsca(
                doc.data().title,
                doc.data().body,
                doc.id,
                doc.data().images
              )
          )
          .map(function(d) {
            return <BusuDeLaVreme observator={d} key={d.id} />;
          });
        this.setState({
          stirileProTv: data
        });
      });
  }

  componentDidMount() {
    document.body.style = "background-color: #2a93d5";
  }

  render() {
    return (
      <div className="News">
        <Container>
          <Row>
            <Col xs="1" md="0" />
            <Col xs="10" md="12">
              {this.state.stirileProTv}
            </Col>
            <Col xs="1" md="0" />
          </Row>
        </Container>
      </div>
    );
  }
}

export default News;
