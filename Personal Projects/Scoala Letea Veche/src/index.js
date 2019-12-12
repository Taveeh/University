import React from 'react';
import ReactDOM from 'react-dom';
import './index.css';
import * as serviceWorker from './serviceWorker';
import 'bootstrap/dist/css/bootstrap.min.css';
import { Route, HashRouter as Router } from 'react-router-dom';
import Menu from './components/Menu/Menu';
import Home from './components/Home/Home';
import logo from './assets/logo.png';
import About from './components/About/About';
import News from './components/News/News';
import PhotoGallery from './components/Gallery/Gallery';
import { Container, Row, Col } from 'reactstrap';
import * as firebase from 'firebase/app';
import "firebase/firestore";
import { library } from '@fortawesome/fontawesome-svg-core';
import { faEnvelope } from '@fortawesome/free-solid-svg-icons';
import { faFacebookF } from '@fortawesome/free-brands-svg-icons';
import { faGlobeAmericas } from '@fortawesome/free-solid-svg-icons'; 
//import BattleRoyale from 'Fortnite';

library.add(faFacebookF, faEnvelope, faGlobeAmericas);

const config = {
    apiKey: "AIzaSyC90DQaNLq_N2RFOPnBuAFWlUQyb7Ex0Zo",
    authDomain: "scoala-letea-veche-c9945.firebaseapp.com",
    databaseURL: "https://scoala-letea-veche-c9945.firebaseio.com",
    projectId: "scoala-letea-veche-c9945",
    storageBucket: "scoala-letea-veche-c9945.appspot.com",
    messagingSenderId: "849468790038"
};
firebase.initializeApp(config);

const routing = (
    <Router>
        <div>
            <div id="outer-container">
                <Menu />
                <img src={logo} alt="Logo" id="logo" />
                <main id="page-wrap">
                    <Container>
                        <Row>
                            <Col xs="2" sm="1"></Col>
                            <Col xs="8" sm="10">
                                <div id="x-title">
                                    &#x218;coala Gimnazial&#259; <span id="x-title-span">Letea Veche</span>
                                </div>            
                            </Col>
                            <Col xs="2" sm="1"></Col>
                        </Row>
                    </Container>
                    <Route exact path="/" component={Home} />
                    <Route exact path="/despre" component={About} />
                    <Route exact path="/galerie" component={PhotoGallery} />
                    <Route exact path="/stiri" component={News} />
                </main>
            </div>
        </div>
    </Router>
);

ReactDOM.render(routing, document.getElementById('root'));

// If you want your app to work offline and load faster, you can change
// unregister() to register() below. Note this comes with some pitfalls.
// Learn more about service workers: http://bit.ly/CRA-PWA
serviceWorker.unregister();
