import React, { Component } from 'react';

import './ResultList.css';


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
            <div className="result-list">
                <div className="result-list__count">{this.props.assets.length} search results found</div>
                {items}
            </div>
        );

    }
}

class ResultItem extends Component
{
    render(){
        return(
            <div className="result-item">
                <div className="result-item__path">{this.props.asset.path}</div>
                <a className="result-item__title" href={this.props.asset.path}>{this.props.asset.title}</a>
                <div className="result-item__description">{this.props.asset.description}</div>
            </div>
        );
    }
}

export default ResultList;