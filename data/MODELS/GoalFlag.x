xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 81;
 0.00000;9.23879;-3.82683;,
 2.70598;9.23879;-2.70598;,
 5.00000;7.07107;-5.00000;,
 0.00000;7.07107;-7.07107;,
 3.82683;9.23879;0.00000;,
 7.07107;7.07107;0.00000;,
 2.70598;9.23879;2.70598;,
 5.00000;7.07107;5.00000;,
 -0.00000;9.23879;3.82683;,
 -0.00000;7.07107;7.07107;,
 -2.70598;9.23879;2.70598;,
 -5.00000;7.07107;5.00000;,
 -3.82683;9.23879;-0.00000;,
 -7.07107;7.07107;-0.00000;,
 -2.70598;9.23879;-2.70598;,
 -5.00000;7.07107;-5.00000;,
 0.00000;9.23879;-3.82683;,
 0.00000;7.07107;-7.07107;,
 6.53281;3.82683;-6.53281;,
 0.00000;3.82683;-9.23879;,
 9.23879;3.82683;0.00000;,
 6.53281;3.82683;6.53281;,
 -0.00000;3.82683;9.23879;,
 -6.53282;3.82683;6.53281;,
 -9.23879;3.82683;-0.00000;,
 -6.53282;3.82683;-6.53281;,
 0.00000;3.82683;-9.23879;,
 7.07107;-0.00000;-7.07107;,
 0.00000;-0.00000;-10.00000;,
 10.00000;-0.00000;0.00000;,
 7.07107;-0.00000;7.07107;,
 -0.00000;-0.00000;10.00000;,
 -7.07107;-0.00000;7.07107;,
 -10.00000;-0.00000;-0.00000;,
 -7.07107;-0.00000;-7.07107;,
 0.00000;-0.00000;-10.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;189.94700;-3.82700;,
 2.70600;189.94700;-2.70600;,
 -0.00000;192.26897;-0.00000;,
 3.82700;189.94700;0.00000;,
 -0.00000;192.26897;-0.00000;,
 2.70600;189.94700;2.70600;,
 -0.00000;192.26897;-0.00000;,
 0.00000;189.94700;3.82700;,
 -0.00000;192.26897;-0.00000;,
 -2.70600;189.94700;2.70600;,
 -0.00000;192.26897;-0.00000;,
 -3.82700;189.94700;0.00000;,
 -0.00000;192.26897;-0.00000;,
 -2.70600;189.94700;-2.70600;,
 -0.00000;192.26897;-0.00000;,
 0.00000;189.94700;-3.82700;,
 -0.00000;192.26897;-0.00000;,
 1.21959;186.20741;-0.48440;,
 52.61848;186.20741;-0.48440;,
 52.61848;154.71967;-0.48440;,
 1.21959;154.71967;-0.48440;,
 52.61848;186.20741;-0.48440;,
 52.61848;186.20741;0.48440;,
 52.61848;154.71967;0.48440;,
 52.61848;154.71967;-0.48440;,
 52.61848;186.20741;0.48440;,
 1.21959;186.20741;0.48440;,
 1.21959;154.71967;0.48440;,
 52.61848;154.71967;0.48440;,
 1.21959;186.20741;0.48440;,
 1.21959;186.20741;-0.48440;,
 1.21959;154.71967;-0.48440;,
 1.21959;154.71967;0.48440;,
 52.61848;186.20741;-0.48440;,
 1.21959;186.20741;-0.48440;,
 1.21959;154.71967;-0.48440;,
 52.61848;154.71967;-0.48440;;
 
 54;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;3,2,18,19;,
 4;2,5,20,18;,
 4;5,7,21,20;,
 4;7,9,22,21;,
 4;9,11,23,22;,
 4;11,13,24,23;,
 4;13,15,25,24;,
 4;15,17,26,25;,
 4;19,18,27,28;,
 4;18,20,29,27;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;25,26,35,34;,
 3;36,28,27;,
 3;37,27,29;,
 3;38,29,30;,
 3;39,30,31;,
 3;40,31,32;,
 3;41,32,33;,
 3;42,33,34;,
 3;43,34,35;,
 4;44,45,1,0;,
 3;46,45,44;,
 4;45,47,4,1;,
 3;48,47,45;,
 4;47,49,6,4;,
 3;50,49,47;,
 4;49,51,8,6;,
 3;52,51,49;,
 4;51,53,10,8;,
 3;54,53,51;,
 4;53,55,12,10;,
 3;56,55,53;,
 4;55,57,14,12;,
 3;58,57,55;,
 4;57,59,16,14;,
 3;60,59,57;,
 4;61,62,63,64;,
 4;65,66,67,68;,
 4;69,70,71,72;,
 4;73,74,75,76;,
 4;73,66,77,78;,
 4;79,80,67,76;;
 
 MeshMaterialList {
  2;
  54;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  0,
  1,
  1;;
  Material {
   0.558431;0.558431;0.558431;1.000000;;
   5.000000;
   0.700000;0.700000;0.700000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.062745;0.109804;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  56;
  0.000000;0.483926;-0.875109;,
  0.618797;0.483922;-0.618797;,
  0.875109;0.483926;0.000000;,
  0.618797;0.483922;0.618797;,
  -0.000000;0.483926;0.875109;,
  -0.618797;0.483922;0.618797;,
  -0.875109;0.483926;0.000000;,
  -0.618797;0.483922;-0.618797;,
  -0.000000;0.709230;-0.704977;,
  0.498494;0.709230;-0.498494;,
  0.704977;0.709230;0.000000;,
  0.498494;0.709230;0.498494;,
  -0.000000;0.709230;0.704977;,
  -0.498494;0.709230;0.498494;,
  -0.704977;0.709230;0.000000;,
  -0.498494;0.709230;-0.498494;,
  -0.000000;0.384551;-0.923104;,
  0.652733;0.384551;-0.652733;,
  0.923104;0.384551;0.000000;,
  0.652733;0.384551;0.652733;,
  -0.000000;0.384551;0.923104;,
  -0.652733;0.384551;0.652733;,
  -0.923104;0.384551;0.000000;,
  -0.652733;0.384551;-0.652733;,
  -0.000000;0.195090;-0.980785;,
  0.693520;0.195090;-0.693520;,
  0.980785;0.195090;0.000000;,
  0.693520;0.195090;0.693520;,
  -0.000000;0.195090;0.980785;,
  -0.693520;0.195090;0.693520;,
  -0.980785;0.195090;0.000000;,
  -0.693520;0.195090;-0.693520;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;0.504367;-0.863490;,
  0.610583;0.504357;-0.610583;,
  0.863490;0.504367;0.000000;,
  0.610583;0.504357;0.610583;,
  0.000000;0.504367;0.863490;,
  -0.610583;0.504357;0.610583;,
  -0.863490;0.504367;-0.000000;,
  -0.610583;0.504357;-0.610583;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-1.000000;0.000000;,
  -0.000000;-1.000000;0.000000;,
  -0.000000;-1.000000;-0.000000;,
  -0.000000;-1.000000;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  54;
  4;0,1,9,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,0,8,15;,
  4;8,9,17,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,8,16,23;,
  4;16,17,25,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,16,24,31;,
  3;32,45,46;,
  3;32,46,47;,
  3;32,47,48;,
  3;32,48,49;,
  3;32,49,50;,
  3;32,50,51;,
  3;32,51,52;,
  3;32,52,45;,
  4;34,35,1,0;,
  3;33,35,34;,
  4;35,36,2,1;,
  3;33,36,35;,
  4;36,37,3,2;,
  3;33,37,36;,
  4;37,38,4,3;,
  3;33,38,37;,
  4;38,39,5,4;,
  3;33,39,38;,
  4;39,40,6,5;,
  3;33,40,39;,
  4;40,41,7,6;,
  3;33,41,40;,
  4;41,34,0,7;,
  3;33,34,41;,
  4;42,42,42,42;,
  4;43,43,43,43;,
  4;44,44,44,44;,
  4;53,53,53,53;,
  4;54,54,54,54;,
  4;55,55,55,55;;
 }
 MeshTextureCoords {
  81;
  0.000000;0.125000;,
  0.125000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.125000;,
  0.250000;0.250000;,
  0.375000;0.125000;,
  0.375000;0.250000;,
  0.500000;0.125000;,
  0.500000;0.250000;,
  0.625000;0.125000;,
  0.625000;0.250000;,
  0.750000;0.125000;,
  0.750000;0.250000;,
  0.875000;0.125000;,
  0.875000;0.250000;,
  1.000000;0.125000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.062500;0.625000;,
  0.187500;0.625000;,
  0.312500;0.625000;,
  0.437500;0.625000;,
  0.562500;0.625000;,
  0.687500;0.625000;,
  0.812500;0.625000;,
  0.937500;0.625000;,
  0.000000;0.125000;,
  0.125000;0.125000;,
  0.062500;0.000000;,
  0.250000;0.125000;,
  0.187500;0.000000;,
  0.375000;0.125000;,
  0.312500;0.000000;,
  0.500000;0.125000;,
  0.437500;0.000000;,
  0.625000;0.125000;,
  0.562500;0.000000;,
  0.750000;0.125000;,
  0.687500;0.000000;,
  0.875000;0.125000;,
  0.812500;0.000000;,
  1.000000;0.125000;,
  0.937500;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}