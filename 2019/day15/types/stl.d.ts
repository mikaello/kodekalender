declare module 'stl-back' {
    type point = [number, number, number];
    type triangle = [point, point, point]
    type facet = { normal: point, verts: triangle };

    type stlFile = { description: string, facets: facet[] }

    function fromObject(file: stlFile, createBinary?: boolean): string;
    function facetNormal(facet: facet): point;
}
