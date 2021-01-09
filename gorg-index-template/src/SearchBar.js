import React, { Component } from 'react';
import logo from './logo.png';
import './SearchBar.css';

import { FontAwesomeIcon } from '@fortawesome/react-fontawesome'
import { faSearch } from '@fortawesome/free-solid-svg-icons'

let FA = require('react-fontawesome');



class SearchBar extends Component {

    constructor(props)
    {
        console.log(props);
        super(props);
        this.state = {
            searchString: props.query    
        };

        this.handleChange = this.handleChange.bind(this);
        this.handleSubmit = this.handleSubmit.bind(this);
    }

    
    search(str)
    {
        this.props.history.push({
            pathname: '/',
            search: `?q=${str}`
          });
    }

    handleChange(event) 
    {    
        let stateChange = {};
        stateChange[event.target.name] = event.target.value;
        this.setState(stateChange);  
    }


    handleSubmit(event) {
        this.search(this.state.searchString);
        event.preventDefault();
    }

    render() {
        return (
            <div className="search-bar">
                <div className="search-bar__top">
                    <img className="search-bar__logo" src={logo} />
                    <div className="search-bar__main">
                        <form className="search-bar__form" onSubmit={this.handleSubmit}>
                            <input autoFocus className="search-bar__search-string" name="searchString" value={this.state.searchString} onChange={this.handleChange} />
                            <button className="search-bar__search-button" type="submit" ><FontAwesomeIcon icon={faSearch} /></button>
                        </form>
                    </div>
                </div>
            </div>
        );
    }
}

export default SearchBar;