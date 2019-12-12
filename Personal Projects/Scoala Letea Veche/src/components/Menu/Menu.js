import React from 'react';
import { Container, Row, Col } from 'reactstrap';
import './Menu.css';
import { bubble as SideMenu } from 'react-burger-menu';
import { Link } from 'react-router-dom';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';

class Menu extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            menuOpen: false
        };
    }

    handleStateChange(state) {
        this.setState({
            menuOpen: state.isOpen
        });
    }

    closeMenu() {
        this.setState({
            menuOpen: false
        });
    }

    render() {
        return (
            <div className="Menu">
                <SideMenu isOpen={this.state.menuOpen} onStateChange={(state) => this.handleStateChange(state)} width={'250px'} pageWrapId={'page-wrap'} outerContainerId={'outer-container'}>
                    <Container>
                        <Row>
                            <Col>
                                <Link onClick={() => this.closeMenu()} to="/" style={{ textDecoration: 'none' }}>
                                    <div className="menu-item x-button">Acasă</div>
                                </Link>
                            </Col>
                        </Row>
                        <Row>
                            <Col>
                                <Link onClick={() => this.closeMenu()} to="/despre" style={{ textDecoration: 'none' }}>
                                    <div className="menu-item x-button">Despre</div>
                                </Link>
                            </Col>
                        </Row>
                        <Row>
                            <Col>
                                <Link onClick={() => this.closeMenu()} to="/galerie" style={{ textDecoration: 'none' }}>
                                    <div className="menu-item x-button">Galerie</div>
                                </Link>
                            </Col>
                        </Row>
                        <Row>
                            <Col>
                                <Link onClick={() => this.closeMenu()} to="/stiri" style={{ textDecoration: 'none' }}>
                                    <div className="menu-item x-button">Știri</div>
                                </Link>
                            </Col>
                        </Row>
                        <Row style={{ marginTop: '15px', width: '250px' }}>
                            <Col style={{ textAlign: 'center' }}>
                                <a href='https://facebook.com/taveeeh'>
                                    <FontAwesomeIcon style={{ color: 'white' }} icon={['fab', 'facebook-f']} />
                                </a>
                            </Col>
                            <Col style={{ textAlign: 'center' }}>
                                <a href='mailto:meow@cats.com'>
                                    <FontAwesomeIcon style={{ color: 'white' }} icon='envelope' />
                                </a>
                            </Col>
                            <Col style={{textAlign: 'center'}}>
                                <a href='https://goo.gl/maps/nUwC9amr3p42'>
                                    <FontAwesomeIcon style={{ color: 'white'}} icon='globe-americas' />
                                </a>
                            </Col>
                        </Row>
                    </Container>
                </SideMenu>
            </div>
        );
    }
}

export default Menu;