import React, { Component } from 'react';
import './Home.css';
import { Container, Row, Col } from "reactstrap";
import { Carousel } from 'react-responsive-carousel';
import "react-responsive-carousel/lib/styles/carousel.min.css";

class Home extends Component {

  componentDidMount() {
    document.body.style = 'background-color: #2a93d5;';
  }

  render() {
    return (
      <div className="Home">
        <Container>
          <Row>
            <Col xs="2" sm="1"></Col>
            <Col xs="8" sm="10">
              <div id="x-main-paragraph">&#x218;coala Letea Veche &#238;&#x219;i propune s&#259; promoveze, prin colectivul cadrelor didactice, dezvoltarea personal&#259; &#x219;i profesional&#259;, respectarea valorilor universale, asumarea &#x219;i dezvoltarea unui climat atractiv pentru educa&#539;ie eficient&#259;, recunoa&#x219;terea &#x219;i respectarea componentelor umane ale procesului educativ ca poten&#539;iale intelectuale, motiva&#539;ionale, comportamentale ce a&#x219;teapt&#259; valorificarea deplin&#259; &#238;n integrarea social&#259;.</div>
            </Col>
            <Col xs="2" sm="1"></Col>
          </Row>
          <Row>
            <Col xs="0" sm="2"></Col>
            <Col xs="12" sm="8">
              {/* <p>Meow</p><p>Meow</p> <p>Meow</p> <p>Meow</p> <p>Meow</p> <p>Meow</p> <p>Meow</p> <p>Meow</p> <p>Meow</p> <p>Meow</p> <p>Meow</p> <p>Meow</p> <p>Meow</p> <p>Meow</p> <p>Meow</p> <p>Meow</p> <p>Meow</p> <p>Meow</p> <p>Meow</p> */}
              <Carousel showArrows={true} showThumbs={false} infiniteLoop={true} autoPlay={true} interval={2000} showStatus={false} useKeyboardArrows={true} emulateTouch={true}>
                <div>
                  <img alt="poza 1" src={require("../../assets/IMG-7707.JPG")} />
                </div>
                <div>
                  <img alt="poza 2" src={require("../../assets/IMG-7706.JPG")} />
                </div>
                <div>
                  <img alt="poza 3" src={require("../../assets/IMG-7710.JPG")} />
                </div>
                <div>
                  <img alt="poza 4" src={require("../../assets/IMG-7711.JPG")} />
                </div>
              </Carousel>
            </Col>
            <Col xs="0" sm="2"></Col>
          </Row>
        </Container>
      </div>
    );
  }
}

export default Home;