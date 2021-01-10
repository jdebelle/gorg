import React, { Component } from 'react';
import logo from './logo.png';
import './SearchBar.css';

import { FontAwesomeIcon } from '@fortawesome/react-fontawesome'
import { faSearch } from '@fortawesome/free-solid-svg-icons'

let FA = require('react-fontawesome');

class TagBar extends Component
{
    renderTagElement(key, name)
    {
        let className = "search-bar__tag";
        if (this.props.nav.tag == name)
            className += " selected"

        return (
                <div key={key}
                    className={className}
                    onClick={() => this.props.nav.setTag(name)}>
                        {name}
                </div>
        );
    }

    render()
    {

        let tags = this.props.tags.map((tag, index) => this.renderTagElement(index, tag));

        return (
            <div className="search-bar__tag-bar">
                {tags}
            </div>
        );
    }
}

class SearchBar extends Component {

    constructor(props)
    {
        super(props);
        this.state = {
            searchString: props.nav.query    
        };

        this.handleChange = this.handleChange.bind(this);
        this.handleSubmit = this.handleSubmit.bind(this);
    }
    
    search(str)
    {
        this.props.nav.setQuery(str);
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
                <TagBar 
                    nav={this.props.nav}
                    tags={this.props.tags}/>
            </div>
        );
    }
}



export default SearchBar;