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
  useExtendedSearch: false,
  keys: ['title', 'description']
}

function onlyUnique(value, index, self) {
  return self.indexOf(value) === index;
}

class Navigator
{
  constructor(routeProps)
  {
    this.props = routeProps;
    let search = queryString.parse(routeProps.location.search);

    this.query = search.q;
    if (this.query === undefined)
      this.query = '';

    this.tag = search.tag;
    if (this.tag === undefined)
      this.tag = "All";
  }

  setQuery(str)
  { 
    this.query = str;
    this.loadPage();
  }

  setTag(tag)
  {
    this.tag = tag;
    this.loadPage();
  }

  loadPage()
  {
    this.props.history.push({
      pathname: '/',
      search: `?q=${this.query}&tag=${this.tag}`
    });
  }
}

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
          let nav = new Navigator(routeProps);
          
          let tags = assets.map(a => a.tags);
          tags = [].concat.apply([], tags);
          tags = [].concat(tags.filter(onlyUnique));
          tags = ["All"].concat(tags.sort());

          let result = assets;
          if (nav.tag != "All")
            result = result.filter(a => a.tags !== undefined && a.tags.includes(nav.tag));

          const fuse = new Fuse(result, fuseOptions);
          if (nav.query != undefined && nav.query != '') {
            result = fuse.search(nav.query);
            result = result.map(e => e.item);
          }

          return (
            <div>
              <SearchBar nav={nav} tags={tags} />
              <ResultList assets={result} />
            </div>
          );
        }} />
      </HashRouter>
    );
  }
}

export default App;
