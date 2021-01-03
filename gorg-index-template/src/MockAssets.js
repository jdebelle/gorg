
// #ifdef DEBUG
const assets = [
    {
        "title": "Asset 1",
        "description": "This is the description for a given asset."
    },
    {
        "title": "Asset 2",
        "description": "This is the description for a given asset.",
        "path": "./test/test.txt"
    }
];
// #else
const assets = "{{asset_data}}";
// #endif



export default assets;