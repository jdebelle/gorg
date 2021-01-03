import logo from './logo.svg';
import './App.css';
import SearchBar from './SearchBar.js';
import ResultList from './ResultList.js';
import Fuse from 'fuse.js';
import queryString from 'query-string';

import assets from './Assets.js';

import { BrowserRouter, Route, Link } from "react-router-dom";


const fuseOptions = 
{
  includeScore: true,
  keys: ['title', 'description']
}

const fuse = new Fuse(assets, fuseOptions);

function App() {
  return (
    <BrowserRouter>
        <Route exact path="/" render={routeProps => {
          console.log(routeProps);
          const query = queryString.parse(routeProps.location.search);

          let result = assets;
          if(query.q != undefined && query.q != '')
          {
            result = fuse.search(query.q);
            result = result.map(e => e.item);
          }
          console.log(result);

          return(
            <div>
              <SearchBar query={query.q}/>
              <ResultList assets={result} />
            </div>
          );
        }}/>
    </BrowserRouter>
  );
}

export default App;
