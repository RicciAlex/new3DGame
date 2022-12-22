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
 86;
 -2.99994;88.45759;-0.00004;,
 -2.12126;88.45759;-2.12136;,
 -2.12126;-0.08572;-2.12136;,
 -2.99994;-0.08572;-0.00004;,
 0.00006;88.45759;-3.00004;,
 0.00006;-0.08572;-3.00004;,
 2.12138;88.45759;-2.12136;,
 2.12138;-0.08572;-2.12136;,
 3.00006;88.45759;-0.00004;,
 3.00006;-0.08572;-0.00004;,
 2.12138;88.45759;2.12128;,
 2.12138;-0.08572;2.12128;,
 0.00006;88.45759;2.99996;,
 0.00006;-0.08572;2.99996;,
 -2.12126;88.45759;2.12128;,
 -2.12126;-0.08572;2.12128;,
 -2.99994;88.45759;-0.00004;,
 -2.99994;-0.08572;-0.00004;,
 0.00006;88.45759;-0.00004;,
 0.00006;88.45759;-0.00004;,
 0.00006;88.45759;-0.00004;,
 0.00006;88.45759;-0.00004;,
 0.00006;88.45759;-0.00004;,
 0.00006;88.45759;-0.00004;,
 0.00006;88.45759;-0.00004;,
 0.00006;88.45759;-0.00004;,
 0.00006;-0.08572;-0.00004;,
 0.00006;-0.08572;-0.00004;,
 0.00006;-0.08572;-0.00004;,
 0.00006;-0.08572;-0.00004;,
 0.00006;-0.08572;-0.00004;,
 0.00006;-0.08572;-0.00004;,
 0.00006;-0.08572;-0.00004;,
 0.00006;-0.08572;-0.00004;,
 -6.74994;112.97840;-0.00004;,
 -4.77291;112.97840;-4.77301;,
 -2.65159;110.05156;-2.65169;,
 -3.74994;110.05156;-0.00004;,
 0.00006;112.97840;-6.75004;,
 0.00006;110.05156;-3.75004;,
 4.77303;112.97840;-4.77301;,
 2.65171;110.05156;-2.65169;,
 6.75006;112.97840;-0.00004;,
 3.75006;110.05156;-0.00004;,
 4.77303;112.97840;4.77293;,
 2.65171;110.05156;2.65161;,
 0.00006;112.97840;6.74996;,
 0.00006;110.05156;3.74996;,
 -4.77291;112.97840;4.77293;,
 -2.65159;110.05156;2.65161;,
 -6.74994;112.97840;-0.00004;,
 -3.74994;110.05156;-0.00004;,
 -2.65159;87.20720;-2.65169;,
 -3.74994;87.20720;-0.00004;,
 0.00006;87.20720;-3.75004;,
 2.65171;87.20720;-2.65169;,
 3.75006;87.20720;-0.00004;,
 2.65171;87.20720;2.65161;,
 0.00006;87.20720;3.74996;,
 -2.65159;87.20720;2.65161;,
 -3.74994;87.20720;-0.00004;,
 -5.30324;85.89404;-5.30334;,
 -7.49994;85.89404;-0.00004;,
 0.00006;85.89404;-7.50004;,
 5.30336;85.89404;-5.30334;,
 7.50006;85.89404;-0.00004;,
 5.30336;85.89404;5.30326;,
 0.00006;85.89404;7.49996;,
 -5.30324;85.89404;5.30326;,
 -7.49994;85.89404;-0.00004;,
 0.00006;112.97840;-0.00004;,
 0.00006;112.97840;-0.00004;,
 0.00006;112.97840;-0.00004;,
 0.00006;112.97840;-0.00004;,
 0.00006;112.97840;-0.00004;,
 0.00006;112.97840;-0.00004;,
 0.00006;112.97840;-0.00004;,
 0.00006;112.97840;-0.00004;,
 0.00006;85.89404;-0.00004;,
 0.00006;85.89404;-0.00004;,
 0.00006;85.89404;-0.00004;,
 0.00006;85.89404;-0.00004;,
 0.00006;85.89404;-0.00004;,
 0.00006;85.89404;-0.00004;,
 0.00006;85.89404;-0.00004;,
 0.00006;85.89404;-0.00004;;
 
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
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;48,50,51,49;,
 4;37,36,52,53;,
 4;36,39,54,52;,
 4;39,41,55,54;,
 4;41,43,56,55;,
 4;43,45,57,56;,
 4;45,47,58,57;,
 4;47,49,59,58;,
 4;49,51,60,59;,
 4;53,52,61,62;,
 4;52,54,63,61;,
 4;54,55,64,63;,
 4;55,56,65,64;,
 4;56,57,66,65;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;59,60,69,68;,
 3;70,35,34;,
 3;71,38,35;,
 3;72,40,38;,
 3;73,42,40;,
 3;74,44,42;,
 3;75,46,44;,
 3;76,48,46;,
 3;77,50,48;,
 3;78,62,61;,
 3;79,61,63;,
 3;80,63,64;,
 3;81,64,65;,
 3;82,65,66;,
 3;83,66,67;,
 3;84,67,68;,
 3;85,68,69;;
 
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.500000;0.500000;0.500000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Desktop\\new3DGameGitCopy\\new3DGame\\data\\TEXTURE\\Materials\\Steel.jpg";
   }
  }
  Material {
   0.800000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  41;
  0.000000;1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707107;,
  -0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  0.000000;-1.000000;-0.000000;,
  -0.698324;-0.715782;0.000000;,
  -0.493790;-0.715782;-0.493790;,
  0.000000;-0.715782;-0.698324;,
  0.493790;-0.715782;-0.493790;,
  0.698324;-0.715782;0.000000;,
  0.493790;-0.715782;0.493790;,
  0.000000;-0.715782;0.698324;,
  -0.493790;-0.715782;0.493790;,
  -0.918278;-0.395937;0.000000;,
  -0.649320;-0.395937;-0.649320;,
  0.000000;-0.395937;-0.918278;,
  0.649320;-0.395937;-0.649320;,
  0.918278;-0.395937;0.000000;,
  0.649320;-0.395937;0.649320;,
  -0.000000;-0.395937;0.918278;,
  -0.649320;-0.395937;0.649320;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707107;,
  0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  -0.000000;0.000000;1.000000;,
  -0.330498;0.943807;0.000000;,
  -0.233698;0.943807;-0.233698;,
  0.000000;0.943807;-0.330498;,
  0.233697;0.943807;-0.233698;,
  0.330498;0.943807;0.000000;,
  0.233697;0.943807;0.233698;,
  -0.000000;0.943807;0.330498;,
  -0.233698;0.943807;0.233698;;
  64;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,1,1,8;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,17,25,24;,
  4;17,10,18,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,25,8,32;,
  4;25,18,26,8;,
  4;33,34,34,33;,
  4;34,35,35,34;,
  4;35,36,36,35;,
  4;36,37,37,36;,
  4;37,38,38,37;,
  4;38,39,39,38;,
  4;39,40,40,39;,
  4;40,33,33,40;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;;
 }
 MeshTextureCoords {
  86;
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
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;0.333333;,
  0.000000;0.333333;,
  0.250000;0.000000;,
  0.250000;0.333333;,
  0.375000;0.000000;,
  0.375000;0.333333;,
  0.500000;0.000000;,
  0.500000;0.333333;,
  0.625000;0.000000;,
  0.625000;0.333333;,
  0.750000;0.000000;,
  0.750000;0.333333;,
  0.875000;0.000000;,
  0.875000;0.333333;,
  1.000000;0.000000;,
  1.000000;0.333333;,
  0.125000;0.666667;,
  0.000000;0.666667;,
  0.250000;0.666667;,
  0.375000;0.666667;,
  0.500000;0.666667;,
  0.625000;0.666667;,
  0.750000;0.666667;,
  0.875000;0.666667;,
  1.000000;0.666667;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.750000;1.000000;,
  0.875000;1.000000;,
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
  0.937500;1.000000;;
 }
}
