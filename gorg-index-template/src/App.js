import './App.css';
import SearchBar from './SearchBar.js';
import ResultList from './ResultList.js';
import Fuse from 'fuse.js';
import queryString from 'query-string';

import assets from './Assets.js';

import { HashRouter, Route, Link } from "react-router-dom";
import { Component } from 'react';


const fuseOptions = 
{
  includeScore: true,
  ignoreLocation: true,
  useExtendedSearch: true,
  keys: ['title', 'description']
}

const fuse = new Fuse(assets, fuseOptions);

class App extends Component
{
  componentDidMount()
  {
    document.title = "Gorg Index"
  }

  render()
  {
    return (
      <HashRouter>
        <Route exact path="/" render={routeProps => {
          const query = queryString.parse(routeProps.location.search);

          let result = assets;
          if (query.q != undefined && query.q != '') {
            result = fuse.search(query.q);
            result = result.map(e => e.item);
          }

          return (
            <div>
              <SearchBar {...routeProps} query={query.q} history={routeProps.history} />
              <ResultList assets={result} />
            </div>
          );
        }} />
      </HashRouter>
    );
  }
}

export default App;
