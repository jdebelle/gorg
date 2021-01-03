import React, { Component } from 'react';

import './SearchBar.css';


class SearchBar extends Component {

    constructor(props)
    {
        super(props);
        this.queryInput = React.createRef();
    }

    render() {
        return (
            <div className="search-bar">
                <form className="search-bar__form">
                    <input className="search-bar__input" type="text" ref={this.queryInput} name="q" defaultValue={this.props.query}/>
                    <button className="search-bar__submit">Search</button>
                </form>
                
            </div>
        );
    }
}

export default SearchBar;