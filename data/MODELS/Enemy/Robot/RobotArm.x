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
 92;
 0.02083;0.96427;-0.50000;,
 0.37439;0.96427;-0.35356;,
 0.37439;-18.60507;-0.35356;,
 0.02083;-18.60507;-0.50000;,
 0.52083;0.96427;0.00000;,
 0.52083;-18.60507;-0.00000;,
 0.37439;0.96427;0.35356;,
 0.37439;-18.60507;0.35356;,
 0.02083;0.96427;0.50000;,
 0.02083;-18.60507;0.50000;,
 -0.33272;0.96427;0.35356;,
 -0.33272;-18.60507;0.35356;,
 -0.47917;0.96427;0.00000;,
 -0.47917;-18.60507;0.00000;,
 -0.33272;0.96427;-0.35356;,
 -0.33272;-18.60507;-0.35356;,
 0.02083;0.96427;-0.50000;,
 0.02083;-18.60507;-0.50000;,
 0.02083;0.96427;0.00000;,
 0.02083;0.96427;0.00000;,
 0.02083;0.96427;0.00000;,
 0.02083;0.96427;0.00000;,
 0.02083;0.96427;0.00000;,
 0.02083;0.96427;0.00000;,
 0.02083;0.96427;0.00000;,
 0.02083;0.96427;0.00000;,
 0.02083;-19.39315;-0.00000;,
 0.02083;-19.39315;-0.00000;,
 0.02083;-19.39315;-0.00000;,
 0.02083;-19.39315;-0.00000;,
 0.02083;-19.39315;-0.00000;,
 0.02083;-19.39315;-0.00000;,
 0.02083;-19.39315;-0.00000;,
 0.02083;-19.39315;-0.00000;,
 0.06249;-26.54537;-4.00000;,
 -0.43751;-26.54537;-4.50000;,
 0.56250;-26.54537;-4.50000;,
 0.41605;-26.54537;-4.14645;,
 0.06249;-26.54537;-5.00000;,
 0.41605;-26.54537;-4.85355;,
 0.06249;-26.54537;-4.00000;,
 0.41605;-22.34665;-2.93198;,
 0.06250;-22.49494;-2.82843;,
 0.56250;-21.98864;-3.18198;,
 0.41605;-21.63063;-3.43198;,
 0.06249;-26.54537;-5.00000;,
 0.06250;-21.48233;-3.53554;,
 -0.29106;-26.54537;-4.85355;,
 -0.29106;-21.63063;-3.43198;,
 -0.43751;-26.54537;-4.50000;,
 -0.43751;-21.98864;-3.18198;,
 -0.29106;-26.54537;-4.14645;,
 -0.29106;-22.34665;-2.93198;,
 0.06249;-26.54537;-4.00000;,
 0.06250;-22.49494;-2.82843;,
 0.41605;-19.30938;-0.00000;,
 0.06250;-19.51910;-0.00000;,
 0.56250;-18.80308;-0.00000;,
 0.41605;-18.29678;-0.00000;,
 0.06250;-18.08706;-0.00000;,
 -0.29106;-18.29678;0.00000;,
 -0.43750;-18.80308;0.00000;,
 -0.29106;-19.30938;0.00000;,
 0.06250;-19.51910;-0.00000;,
 0.41605;-22.34665;2.93198;,
 0.06250;-22.49494;2.82843;,
 0.56250;-21.98864;3.18198;,
 0.41605;-21.63063;3.43198;,
 0.06250;-21.48233;3.53554;,
 -0.29106;-21.63063;3.43198;,
 -0.43751;-21.98864;3.18198;,
 -0.29106;-22.34665;2.93198;,
 0.06250;-22.49494;2.82843;,
 0.41605;-26.54537;4.14645;,
 0.06249;-26.54537;4.00000;,
 0.56250;-26.54537;4.50000;,
 0.41605;-26.54537;4.85355;,
 0.06249;-26.54537;5.00000;,
 -0.29106;-26.54537;4.85355;,
 -0.43751;-26.54537;4.50000;,
 -0.29106;-26.54537;4.14645;,
 0.06249;-26.54537;4.00000;,
 -0.43751;-26.54537;4.50000;,
 -0.29106;-26.54537;4.14645;,
 0.06249;-26.54537;5.00000;,
 -0.43751;-26.54537;4.50000;,
 -0.43751;-26.54537;4.50000;,
 -0.29106;-26.54537;4.85355;,
 -0.43751;-26.54537;4.50000;,
 -0.43751;-26.54537;-4.50000;,
 -0.29106;-26.54537;-4.14645;,
 -0.43751;-26.54537;-4.50000;;
 
 64;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,1,0;,
 3;19,4,1;,
 3;20,6,4;,
 3;21,8,6;,
 3;22,10,8;,
 3;23,12,10;,
 3;24,14,12;,
 3;25,16,14;,
 3;26,3,2;,
 3;27,2,5;,
 3;28,5,7;,
 3;29,7,9;,
 3;30,9,11;,
 3;31,11,13;,
 3;32,13,15;,
 3;33,15,17;,
 4;34,35,36,37;,
 4;35,38,39,36;,
 4;40,37,41,42;,
 4;37,36,43,41;,
 4;36,39,44,43;,
 4;39,45,46,44;,
 4;45,47,48,46;,
 4;47,49,50,48;,
 4;49,51,52,50;,
 4;51,53,54,52;,
 4;42,41,55,56;,
 4;41,43,57,55;,
 4;43,44,58,57;,
 4;44,46,59,58;,
 4;46,48,60,59;,
 4;48,50,61,60;,
 4;50,52,62,61;,
 4;52,54,63,62;,
 4;56,55,64,65;,
 4;55,57,66,64;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;59,60,69,68;,
 4;60,61,70,69;,
 4;61,62,71,70;,
 4;62,63,72,71;,
 4;65,64,73,74;,
 4;64,66,75,73;,
 4;66,67,76,75;,
 4;67,68,77,76;,
 4;68,69,78,77;,
 4;69,70,79,78;,
 4;70,71,80,79;,
 4;71,72,81,80;,
 4;74,73,82,83;,
 4;75,76,84,85;,
 3;86,73,75;,
 3;87,88,77;,
 3;89,47,45;,
 3;90,91,53;;
 
 MeshMaterialList {
  2;
  64;
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.580000;0.580000;0.580000;1.000000;;
   5.000000;
   0.500000;0.500000;0.500000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  67;
  0.000000;1.000000;0.000000;,
  -0.000005;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  -0.000005;0.000000;1.000000;,
  -0.707102;0.000000;0.707112;,
  -1.000000;0.000000;0.000000;,
  -0.707102;0.000000;-0.707112;,
  -0.000005;-0.281927;-0.959436;,
  0.678423;-0.281932;-0.678423;,
  0.959436;-0.281927;-0.000000;,
  0.678423;-0.281932;0.678423;,
  -0.000005;-0.281927;0.959436;,
  -0.678419;-0.281928;0.678428;,
  -0.959436;-0.281927;0.000000;,
  -0.678419;-0.281928;-0.678428;,
  0.746776;-0.588763;-0.309328;,
  0.000000;-1.000000;0.000000;,
  -0.696988;-0.199246;0.688846;,
  -0.696993;0.199245;-0.688841;,
  0.000003;-0.497039;0.867728;,
  0.724561;-0.341520;0.598645;,
  0.999999;0.000515;0.001612;,
  0.727940;0.348734;-0.590328;,
  0.000003;0.513185;-0.858278;,
  -0.727940;0.348734;-0.590328;,
  -0.999999;0.000515;0.001613;,
  -0.724561;-0.341519;0.598645;,
  0.000005;-0.691778;0.722110;,
  0.869362;-0.426433;0.249728;,
  0.999999;0.001020;0.000000;,
  0.868709;0.434311;-0.238154;,
  0.000005;0.719311;-0.694688;,
  -0.868711;0.434308;-0.238156;,
  -0.999999;0.001020;0.000000;,
  -0.869364;-0.426429;0.249730;,
  0.000003;-0.497039;-0.867728;,
  0.724561;-0.341520;-0.598645;,
  0.999999;0.000515;-0.001612;,
  0.727940;0.348734;0.590328;,
  0.000003;0.513185;0.858278;,
  -0.727940;0.348734;0.590328;,
  -0.999999;0.000515;-0.001613;,
  -0.724561;-0.341519;-0.598645;,
  0.000000;-0.277857;-0.960622;,
  0.696988;-0.199247;-0.688846;,
  1.000000;-0.000000;0.000000;,
  0.696993;0.199244;0.688841;,
  -0.696988;-0.199246;-0.688846;,
  -1.000000;-0.000000;0.000000;,
  0.000000;0.277856;0.960623;,
  -0.696993;0.199245;0.688841;,
  -0.309328;-0.588758;0.746780;,
  -0.597070;-0.535729;-0.597078;,
  0.000000;-0.277857;0.960622;,
  0.696988;-0.199247;0.688846;,
  1.000000;-0.000000;-0.000000;,
  0.696993;0.199244;-0.688841;,
  0.000000;0.277856;-0.960623;,
  -1.000000;-0.000000;-0.000000;,
  0.000005;-0.691778;-0.722110;,
  0.414799;-0.629458;-0.657057;,
  0.422270;0.652034;0.629714;,
  0.000005;0.719311;0.694688;,
  -0.422260;0.652037;0.629717;,
  -0.414790;-0.629461;-0.657060;;
  64;
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;17,9,10;,
  3;17,10,11;,
  3;17,11,12;,
  3;53,12,13;,
  3;53,13,14;,
  3;53,14,15;,
  3;54,15,16;,
  3;54,16,9;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;55,56,22,21;,
  4;56,57,23,22;,
  4;57,58,24,23;,
  4;58,59,25,24;,
  4;59,20,26,25;,
  4;20,60,27,26;,
  4;60,19,28,27;,
  4;19,55,21,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,25,33,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,21,29,36;,
  4;61,62,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;63,64,41,40;,
  4;64,65,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;66,61,37,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,41,51,48;,
  4;41,42,52,51;,
  4;42,43,50,52;,
  4;43,44,49,50;,
  4;44,37,45,49;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  3;18,18,18;,
  3;18,18,18;,
  3;18,18,18;,
  3;18,18,18;;
 }
 MeshTextureCoords {
  92;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.125000;0.125000;,
  0.125000;0.250000;,
  0.250000;0.250000;,
  0.250000;0.125000;,
  0.125000;0.375000;,
  0.250000;0.375000;,
  0.250000;0.000000;,
  0.375000;0.125000;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.375000;0.375000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.250000;1.000000;,
  0.375000;1.000000;,
  0.500000;0.125000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.500000;0.375000;,
  0.500000;0.500000;,
  0.500000;0.625000;,
  0.500000;0.750000;,
  0.500000;0.875000;,
  0.500000;1.000000;,
  0.625000;0.125000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.625000;0.375000;,
  0.625000;0.500000;,
  0.625000;0.625000;,
  0.625000;0.750000;,
  0.625000;0.875000;,
  0.625000;1.000000;,
  0.750000;0.125000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  0.750000;0.375000;,
  0.750000;0.500000;,
  0.750000;0.625000;,
  0.750000;0.750000;,
  0.750000;0.875000;,
  0.750000;1.000000;,
  0.875000;0.125000;,
  0.875000;0.000000;,
  0.875000;0.375000;,
  0.875000;0.250000;,
  0.875000;0.187500;,
  0.812500;0.625000;,
  0.875000;0.500000;,
  0.125000;0.562500;,
  0.187500;0.875000;,
  0.125000;1.000000;;
 }
}