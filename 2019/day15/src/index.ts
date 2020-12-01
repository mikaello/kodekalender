import fs = require("fs");
import stl = require("stl");
const NodeStl = require("node-stl");

const model = fs
  .readFileSync(__dirname + "/MODEL.CSV")
  .toString()
  .trim()
  .split("\n");

const facets: stl.facet[] = model.map(triangle => {
  const points = triangle.split(",").map(Number);

  const triangles: stl.triangle = [
    [points[0], points[1], points[2]],
    [points[3], points[4], points[5]],
    [points[6], points[7], points[8]]
  ];

  return { verts: triangles };
});

const stlObject = { description: "", facets };
const stlAscii = stl.fromObject(stlObject, false);

var nodeStl = new NodeStl(Buffer.from(stlAscii));

// Example answer is: 0.1666666
console.log(nodeStl.volume);
