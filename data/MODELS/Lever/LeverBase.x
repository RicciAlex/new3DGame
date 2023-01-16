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
 59;
 0.00006;-0.08687;-15.00004;,
 -5.39394;-0.08687;-14.13304;,
 -5.20238;2.33906;-13.85823;,
 0.00006;-0.08687;-15.00004;,
 5.39413;1.87640;-13.85823;,
 5.20206;-0.08687;-13.85854;,
 0.00006;-0.08687;-15.00004;,
 2.42599;5.11556;-13.85823;,
 0.00006;-0.08687;-15.00004;,
 -1.96323;5.30720;-13.85823;,
 0.00006;-0.08687;-15.00004;,
 -5.20238;2.33906;-13.85823;,
 -9.96744;-0.08687;-10.60654;,
 -9.61279;4.39567;-10.60664;,
 9.96700;3.54080;-10.60664;,
 9.61356;-0.08687;-10.60654;,
 4.48260;9.52597;-10.60664;,
 -3.62761;9.88007;-10.60664;,
 -9.61279;4.39567;-10.60664;,
 -13.02294;-0.08687;-5.74054;,
 -12.55973;6.36985;-2.74029;,
 13.02250;5.25291;-2.74029;,
 12.55956;-0.08687;-5.74054;,
 5.85678;13.07291;-2.74029;,
 -4.73972;13.53557;-2.74029;,
 -12.55973;6.36985;-2.74029;,
 -14.09544;-0.08687;-0.00004;,
 -13.59456;6.25240;-0.00004;,
 14.09544;5.04343;-0.00004;,
 13.59456;-0.08687;-0.00004;,
 6.33933;13.50774;-0.00004;,
 -5.13024;14.00851;-0.00004;,
 -13.59456;6.25240;-0.00004;,
 -13.02294;-0.08687;5.74046;,
 -12.55973;6.36985;2.74022;,
 13.02250;5.25291;2.74021;,
 12.55956;-0.08687;5.74046;,
 5.85678;13.07291;2.74021;,
 -4.73972;13.53557;2.74022;,
 -12.55973;6.36985;2.74022;,
 -9.96744;-0.08687;10.60646;,
 -9.61279;4.39567;10.60656;,
 9.96700;3.54080;10.60656;,
 9.61356;-0.08687;10.60646;,
 4.48260;9.52597;10.60656;,
 -3.62761;9.88007;10.60656;,
 -9.61279;4.39567;10.60656;,
 -5.39394;-0.08687;13.85846;,
 -5.20238;2.33906;13.85815;,
 5.39413;1.87641;13.85815;,
 5.20206;-0.08687;13.85846;,
 2.42599;5.11556;13.85815;,
 -1.96322;5.30720;13.85815;,
 -5.20238;2.33906;13.85815;,
 0.00006;-0.08687;14.99996;,
 0.00006;-0.08687;14.99996;,
 0.00006;-0.08687;14.99996;,
 0.00006;-0.08687;14.99996;,
 0.00006;-0.08687;14.99996;;
 
 40;
 3;0,1,2;,
 3;3,4,5;,
 3;6,7,4;,
 3;8,9,7;,
 3;10,11,9;,
 4;2,1,12,13;,
 4;5,4,14,15;,
 4;4,7,16,14;,
 4;7,9,17,16;,
 4;9,11,18,17;,
 4;13,12,19,20;,
 4;15,14,21,22;,
 4;14,16,23,21;,
 4;16,17,24,23;,
 4;17,18,25,24;,
 4;20,19,26,27;,
 4;22,21,28,29;,
 4;21,23,30,28;,
 4;23,24,31,30;,
 4;24,25,32,31;,
 4;27,26,33,34;,
 4;29,28,35,36;,
 4;28,30,37,35;,
 4;30,31,38,37;,
 4;31,32,39,38;,
 4;34,33,40,41;,
 4;36,35,42,43;,
 4;35,37,44,42;,
 4;37,38,45,44;,
 4;38,39,46,45;,
 4;41,40,47,48;,
 4;43,42,49,50;,
 4;42,44,51,49;,
 4;44,45,52,51;,
 4;45,46,53,52;,
 3;48,47,54;,
 3;50,49,55;,
 3;49,51,56;,
 3;51,52,57;,
 3;52,53,58;;
 
 MeshMaterialList {
  2;
  40;
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
  0,
  1,
  1,
  1,
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
  0;;
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
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  44;
  0.016026;0.123844;-0.992172;,
  -0.332249;0.206845;-0.920231;,
  -0.385940;0.110490;-0.915883;,
  0.412428;-0.040184;-0.910104;,
  0.361301;0.119104;-0.924811;,
  0.160853;0.344950;-0.924735;,
  -0.130177;0.357657;-0.924735;,
  -0.659603;0.360988;-0.659250;,
  -0.750279;0.127639;-0.648683;,
  0.762520;-0.015771;-0.646772;,
  0.698452;0.265514;-0.664581;,
  0.318239;0.680409;-0.660126;,
  -0.257347;0.704993;-0.660876;,
  -0.822754;0.441535;-0.357942;,
  -0.919618;0.136885;-0.368193;,
  0.930396;-0.005578;-0.366513;,
  0.868006;0.338680;-0.363128;,
  0.398969;0.856826;-0.326608;,
  -0.323163;0.889018;-0.324364;,
  -0.888682;0.458525;-0.000000;,
  -0.992928;0.118717;-0.000000;,
  0.999210;-0.039746;-0.000000;,
  0.938176;0.346159;-0.000000;,
  0.420044;0.907504;-0.000000;,
  -0.339927;0.940452;-0.000000;,
  -0.822754;0.441535;0.357942;,
  -0.919618;0.136885;0.368193;,
  0.930396;-0.005578;0.366513;,
  0.868006;0.338679;0.363128;,
  0.398969;0.856826;0.326608;,
  -0.323163;0.889018;0.324364;,
  -0.658767;0.350373;0.665781;,
  -0.745732;0.104655;0.657975;,
  0.762516;-0.015770;0.646777;,
  0.698449;0.265514;0.664583;,
  0.318239;0.680410;0.660126;,
  -0.257347;0.704993;0.660876;,
  -0.341938;0.167745;0.924630;,
  -0.401364;0.031802;0.915366;,
  0.412422;-0.040182;0.910106;,
  0.361298;0.119105;0.924812;,
  0.160853;0.344951;0.924735;,
  -0.130177;0.357657;0.924735;,
  0.005992;0.102436;0.994722;;
  40;
  3;0,2,1;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,1,6;,
  4;1,2,8,7;,
  4;3,4,10,9;,
  4;4,5,11,10;,
  4;5,6,12,11;,
  4;6,1,7,12;,
  4;7,8,14,13;,
  4;9,10,16,15;,
  4;10,11,17,16;,
  4;11,12,18,17;,
  4;12,7,13,18;,
  4;13,14,20,19;,
  4;15,16,22,21;,
  4;16,17,23,22;,
  4;17,18,24,23;,
  4;18,13,19,24;,
  4;19,20,26,25;,
  4;21,22,28,27;,
  4;22,23,29,28;,
  4;23,24,30,29;,
  4;24,19,25,30;,
  4;25,26,32,31;,
  4;27,28,34,33;,
  4;28,29,35,34;,
  4;29,30,36,35;,
  4;30,25,31,36;,
  4;31,32,38,37;,
  4;33,34,40,39;,
  4;34,35,41,40;,
  4;35,36,42,41;,
  4;36,31,37,42;,
  3;37,38,43;,
  3;39,40,43;,
  3;40,41,43;,
  3;41,42,43;,
  3;42,37,43;;
 }
 MeshTextureCoords {
  59;
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.500000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.625000;0.250000;,
  0.500000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.625000;0.375000;,
  0.500000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.625000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.625000;0.625000;,
  0.500000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.625000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.625000;0.875000;,
  0.500000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}