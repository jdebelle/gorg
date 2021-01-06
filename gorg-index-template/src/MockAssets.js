
// #ifdef DEBUG
const assets = [
    {
        "title": "Asset #1 - An awesome asset",
        "description": "This is the description for a given asset. It is a really long string that has many many many characters",
        "path": "./test/test.txt"
    },
    {
        "title": "Asset 2",
        "description": "This is the description for a given asset. This is a 3D model? Or is it a plane? blue",
        "path": "./test/test.txt"
    }
];
// #else
const assets = "{{asset_data}}";
// #endif



export default assets;