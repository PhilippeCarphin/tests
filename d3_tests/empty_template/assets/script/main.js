d3.select("body").append("p").text("Hello world");

const svg = d3.select("body").append("svg").attr("width", 101).attr("height", 100);
svg.append("rect")
    .attr("x", 0)
    .attr("y", 0)
    .attr("width", 10)
    .attr("height", 10)
    .attr("fill", "blue");
svg.append("rect")
    .attr("x", 10)
    .attr("y", 10)
    .attr("width", 10)
    .attr("height", 10)
    .attr("fill", "blue");
svg.append("rect")
    // .attr("width", 10).attr("height", 20).attr("fill", "red")
    .attr({
        x: 20,
        y: 20,
        width: 10,
        height: 10,
        fill: red,
    });
