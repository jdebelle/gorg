import React, { Component } from 'react';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome'
import { faClipboard } from '@fortawesome/free-solid-svg-icons'

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
                <div className="result-item__path">
                    <p>{this.props.asset.path}</p>
                    <a className="result-item__copy" onClick={() => {navigator.clipboard.writeText(this.props.asset.path);}}><FontAwesomeIcon icon={faClipboard} /></a>
                </div>
                <a className="result-item__title" href={this.props.asset.path}>{this.props.asset.title}</a>
                <div className="result-item__description">{this.props.asset.description}</div>
            </div>
        );
    }
}

export default ResultList;