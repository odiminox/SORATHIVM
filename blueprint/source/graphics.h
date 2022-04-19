#pragma once

#include "math.h"

struct Uv
{
    v2 data;
};

struct Material
{
    STRING name;
    u32 id;
};

struct Texture
{
    u32 id;
    i32 width;
    i32 height;
};

struct Vertex
{
    v4 colour;
    v3 pos;
    v3 normal;
};


struct Edge
{
    Vertex vert1;
    Vertex vert2;
};

struct Poly
{
    Edge edges[3];
    v3 pos;
    Uv uv;
};

struct Particle
{
    union
    {
        v4 start_colour;
        v4 colour;
    };

    v4 end_colour;

    v3 pos;
    v3 speed;
};

struct Mesh
{
    m4 trans;
    Poly* polygon_list;
    Vertex* vertex_list;
    Edge* edge_list;
    Material* mat;
    u16 id;
};