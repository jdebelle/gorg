import React, { Component } from 'react';

import './SearchBar.css';


class ResultList extends Component {
    constructor(props)
    {
        super(props);
    }

    render() {
        let items = [];
        for(const key in this.props.assets)
            items.push(<ResultItem key={key} asset={this.props.assets[key]}/>);
        
        return (
            <div>
                <div>RESULTS:</div>
                {items}
            </div>
        );
        
    }
}

class ResultItem extends Component
{
    render(){
        return(
            <div className="search-result-item">
                <div className="search-result-item__title">{this.props.asset.title}</div>
                <a href={this.props.asset.path}>Link</a>
                <div className="search-result-item__description">{this.props.asset.description}</div>
            </div>
        );
    }
}

export default ResultList;