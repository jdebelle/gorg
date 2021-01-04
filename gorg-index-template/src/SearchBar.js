import React, { Component } from 'react';
import { useHistory } from "react-router-dom";

import './SearchBar.css';


class SearchBar extends Component {

    constructor(props)
    {
        super(props);
        this.state = {
            searchString: 'search here!'    
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
                <form className="search-bar__form" onSubmit={this.handleSubmit}>
                    <input className="search-bar__input" name="searchString" value={this.state.searchString} onChange={this.handleChange} />
                    <input type="submit" value="Submit" />
                </form>
                
            </div>
        );
    }
}

export default SearchBar;