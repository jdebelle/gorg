$('document').ready(function()
{
    $('.search__button').click(search);
});


function search()
{
    assets.forEach(function(asset) 
    {
        $(".search__results").append($("<li></li>").text(asset.title))
    });
}




