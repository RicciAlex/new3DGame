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
 198;
 -11.17438;5.00000;-2.75838;,
 -6.17438;5.00000;-2.75838;,
 -6.17438;5.00000;2.24162;,
 -16.17438;0.00000;7.24162;,
 -1.17438;5.00000;-2.75838;,
 3.82562;0.00000;7.24162;,
 -16.17438;0.00000;-12.75838;,
 -6.17438;5.00000;-7.75838;,
 3.82562;0.00000;-12.75838;,
 -6.17438;20.00000;-2.75838;,
 -6.17438;5.00000;-7.75838;,
 -16.17438;0.00000;-12.75838;,
 -6.17438;20.00000;-2.75838;,
 3.82562;0.00000;-12.75838;,
 3.82562;0.00000;7.24162;,
 -16.17438;0.00000;-12.75838;,
 -11.17438;5.00000;-2.75838;,
 -1.17438;5.00000;-2.75838;,
 3.82562;0.00000;-12.75838;,
 -16.17438;0.00000;7.24162;,
 -6.17438;20.00000;-2.75838;,
 -16.17438;0.00000;7.24162;,
 8.37741;5.00000;11.34173;,
 13.37741;5.00000;11.34173;,
 13.37741;5.00000;16.34173;,
 3.37741;0.00000;21.34173;,
 18.37741;5.00000;11.34173;,
 23.37742;0.00000;21.34173;,
 3.37741;0.00000;1.34173;,
 13.37741;5.00000;6.34173;,
 23.37742;0.00000;1.34173;,
 13.37741;20.00000;11.34173;,
 13.37741;5.00000;6.34173;,
 3.37741;0.00000;1.34173;,
 13.37741;20.00000;11.34173;,
 23.37742;0.00000;1.34173;,
 23.37742;0.00000;21.34173;,
 3.37741;0.00000;1.34173;,
 8.37741;5.00000;11.34173;,
 18.37741;5.00000;11.34173;,
 23.37742;0.00000;1.34173;,
 3.37741;0.00000;21.34173;,
 13.37741;20.00000;11.34173;,
 3.37741;0.00000;21.34173;,
 -41.30226;5.00000;-10.41732;,
 -36.30225;5.00000;-10.41732;,
 -36.30225;5.00000;-5.41732;,
 -46.30225;0.00000;-0.41732;,
 -31.30226;5.00000;-10.41732;,
 -26.30227;0.00000;-0.41732;,
 -46.30225;0.00000;-20.41732;,
 -36.30225;5.00000;-15.41732;,
 -26.30227;0.00000;-20.41732;,
 -36.30225;20.00000;-10.41732;,
 -36.30225;5.00000;-15.41732;,
 -46.30225;0.00000;-20.41732;,
 -36.30225;20.00000;-10.41732;,
 -26.30227;0.00000;-20.41732;,
 -26.30227;0.00000;-0.41732;,
 -46.30225;0.00000;-20.41732;,
 -41.30226;5.00000;-10.41732;,
 -31.30226;5.00000;-10.41732;,
 -26.30227;0.00000;-20.41732;,
 -46.30225;0.00000;-0.41732;,
 -36.30225;20.00000;-10.41732;,
 -46.30225;0.00000;-0.41732;,
 0.23336;5.00000;-32.39363;,
 5.23336;5.00000;-32.39363;,
 5.23336;5.00000;-27.39363;,
 -4.76664;0.00000;-22.39363;,
 10.23336;5.00000;-32.39363;,
 15.23336;0.00000;-22.39363;,
 -4.76664;0.00000;-42.39363;,
 5.23336;5.00000;-37.39363;,
 15.23336;0.00000;-42.39363;,
 5.23336;20.00000;-32.39363;,
 5.23336;5.00000;-37.39363;,
 -4.76664;0.00000;-42.39363;,
 5.23336;20.00000;-32.39363;,
 15.23336;0.00000;-42.39363;,
 15.23336;0.00000;-22.39363;,
 -4.76664;0.00000;-42.39363;,
 0.23336;5.00000;-32.39363;,
 10.23336;5.00000;-32.39363;,
 15.23336;0.00000;-42.39363;,
 -4.76664;0.00000;-22.39363;,
 5.23336;20.00000;-32.39363;,
 -4.76664;0.00000;-22.39363;,
 -31.20879;5.00000;-50.84093;,
 -26.20880;5.00000;-50.84093;,
 -26.20880;5.00000;-45.84093;,
 -36.20880;0.00000;-40.84093;,
 -21.20880;5.00000;-50.84093;,
 -16.20880;0.00000;-40.84093;,
 -36.20880;0.00000;-60.84094;,
 -26.20880;5.00000;-55.84093;,
 -16.20880;0.00000;-60.84094;,
 -26.20880;20.00000;-50.84093;,
 -26.20880;5.00000;-55.84093;,
 -36.20880;0.00000;-60.84094;,
 -26.20880;20.00000;-50.84093;,
 -16.20880;0.00000;-60.84094;,
 -16.20880;0.00000;-40.84093;,
 -36.20880;0.00000;-60.84094;,
 -31.20879;5.00000;-50.84093;,
 -21.20880;5.00000;-50.84093;,
 -16.20880;0.00000;-60.84094;,
 -36.20880;0.00000;-40.84093;,
 -26.20880;20.00000;-50.84093;,
 -36.20880;0.00000;-40.84093;,
 -41.30226;5.00000;24.90295;,
 -36.30225;5.00000;24.90295;,
 -36.30225;5.00000;29.90295;,
 -46.30225;0.00000;34.90294;,
 -31.30226;5.00000;24.90295;,
 -26.30227;0.00000;34.90294;,
 -46.30225;0.00000;14.90295;,
 -36.30225;5.00000;19.90295;,
 -26.30227;0.00000;14.90295;,
 -36.30225;20.00000;24.90295;,
 -36.30225;5.00000;19.90295;,
 -46.30225;0.00000;14.90295;,
 -36.30225;20.00000;24.90295;,
 -26.30227;0.00000;14.90295;,
 -26.30227;0.00000;34.90294;,
 -46.30225;0.00000;14.90295;,
 -41.30226;5.00000;24.90295;,
 -31.30226;5.00000;24.90295;,
 -26.30227;0.00000;14.90295;,
 -46.30225;0.00000;34.90294;,
 -36.30225;20.00000;24.90295;,
 -46.30225;0.00000;34.90294;,
 29.06990;5.00000;-18.87350;,
 34.06990;5.00000;-18.87350;,
 34.06990;5.00000;-13.87350;,
 24.06990;0.00000;-8.87350;,
 39.06990;5.00000;-18.87350;,
 44.06991;0.00000;-8.87350;,
 24.06990;0.00000;-28.87350;,
 34.06990;5.00000;-23.87350;,
 44.06991;0.00000;-28.87350;,
 34.06990;20.00000;-18.87350;,
 34.06990;5.00000;-23.87350;,
 24.06990;0.00000;-28.87350;,
 34.06990;20.00000;-18.87350;,
 44.06991;0.00000;-28.87350;,
 44.06991;0.00000;-8.87350;,
 24.06990;0.00000;-28.87350;,
 29.06990;5.00000;-18.87350;,
 39.06990;5.00000;-18.87350;,
 44.06991;0.00000;-28.87350;,
 24.06990;0.00000;-8.87350;,
 34.06990;20.00000;-18.87350;,
 24.06990;0.00000;-8.87350;,
 25.76717;5.00000;-54.64287;,
 30.76717;5.00000;-54.64287;,
 30.76717;5.00000;-49.64287;,
 20.76716;0.00000;-44.64287;,
 35.76717;5.00000;-54.64287;,
 40.76718;0.00000;-44.64287;,
 20.76716;0.00000;-64.64288;,
 30.76717;5.00000;-59.64288;,
 40.76718;0.00000;-64.64288;,
 30.76717;20.00000;-54.64287;,
 30.76717;5.00000;-59.64288;,
 20.76716;0.00000;-64.64288;,
 30.76717;20.00000;-54.64287;,
 40.76718;0.00000;-64.64288;,
 40.76718;0.00000;-44.64287;,
 20.76716;0.00000;-64.64288;,
 25.76717;5.00000;-54.64287;,
 35.76717;5.00000;-54.64287;,
 40.76718;0.00000;-64.64288;,
 20.76716;0.00000;-44.64287;,
 30.76717;20.00000;-54.64287;,
 20.76716;0.00000;-44.64287;,
 22.86861;5.00000;43.60935;,
 27.86863;5.00000;43.60935;,
 27.86863;5.00000;48.60936;,
 17.86862;0.00000;53.60934;,
 32.86863;5.00000;43.60935;,
 37.86863;0.00000;53.60934;,
 17.86862;0.00000;33.60937;,
 27.86863;5.00000;38.60937;,
 37.86863;0.00000;33.60937;,
 27.86863;20.00000;43.60935;,
 27.86863;5.00000;38.60937;,
 17.86862;0.00000;33.60937;,
 27.86863;20.00000;43.60935;,
 37.86863;0.00000;33.60937;,
 37.86863;0.00000;53.60934;,
 17.86862;0.00000;33.60937;,
 22.86861;5.00000;43.60935;,
 32.86863;5.00000;43.60935;,
 37.86863;0.00000;33.60937;,
 17.86862;0.00000;53.60934;,
 27.86863;20.00000;43.60935;,
 17.86862;0.00000;53.60934;;
 
 108;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;6,7,1,0;,
 4;7,8,4,1;,
 3;9,10,11;,
 3;12,13,10;,
 3;9,2,14;,
 3;12,15,16;,
 3;9,17,18;,
 3;12,5,17;,
 3;19,2,20;,
 3;21,20,16;,
 4;22,23,24,25;,
 4;23,26,27,24;,
 4;28,29,23,22;,
 4;29,30,26,23;,
 3;31,32,33;,
 3;34,35,32;,
 3;31,24,36;,
 3;34,37,38;,
 3;31,39,40;,
 3;34,27,39;,
 3;41,24,42;,
 3;43,42,38;,
 4;44,45,46,47;,
 4;45,48,49,46;,
 4;50,51,45,44;,
 4;51,52,48,45;,
 3;53,54,55;,
 3;56,57,54;,
 3;53,46,58;,
 3;56,59,60;,
 3;53,61,62;,
 3;56,49,61;,
 3;63,46,64;,
 3;65,64,60;,
 4;66,67,68,69;,
 4;67,70,71,68;,
 4;72,73,67,66;,
 4;73,74,70,67;,
 3;75,76,77;,
 3;78,79,76;,
 3;75,68,80;,
 3;78,81,82;,
 3;75,83,84;,
 3;78,71,83;,
 3;85,68,86;,
 3;87,86,82;,
 4;88,89,90,91;,
 4;89,92,93,90;,
 4;94,95,89,88;,
 4;95,96,92,89;,
 3;97,98,99;,
 3;100,101,98;,
 3;97,90,102;,
 3;100,103,104;,
 3;97,105,106;,
 3;100,93,105;,
 3;107,90,108;,
 3;109,108,104;,
 4;110,111,112,113;,
 4;111,114,115,112;,
 4;116,117,111,110;,
 4;117,118,114,111;,
 3;119,120,121;,
 3;122,123,120;,
 3;119,112,124;,
 3;122,125,126;,
 3;119,127,128;,
 3;122,115,127;,
 3;129,112,130;,
 3;131,130,126;,
 4;132,133,134,135;,
 4;133,136,137,134;,
 4;138,139,133,132;,
 4;139,140,136,133;,
 3;141,142,143;,
 3;144,145,142;,
 3;141,134,146;,
 3;144,147,148;,
 3;141,149,150;,
 3;144,137,149;,
 3;151,134,152;,
 3;153,152,148;,
 4;154,155,156,157;,
 4;155,158,159,156;,
 4;160,161,155,154;,
 4;161,162,158,155;,
 3;163,164,165;,
 3;166,167,164;,
 3;163,156,168;,
 3;166,169,170;,
 3;163,171,172;,
 3;166,159,171;,
 3;173,156,174;,
 3;175,174,170;,
 4;176,177,178,179;,
 4;177,180,181,178;,
 4;182,183,177,176;,
 4;183,184,180,177;,
 3;185,186,187;,
 3;188,189,186;,
 3;185,178,190;,
 3;188,191,192;,
 3;185,193,194;,
 3;188,181,193;,
 3;195,178,196;,
 3;197,196,192;;
 
 MeshMaterialList {
  1;
  108;
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
   0.524000;0.524000;0.524000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  198;
  0.154488;-0.975842;0.154488;,
  0.000000;-0.987699;0.156365;,
  -0.000000;0.316228;-0.948683;,
  -0.154488;-0.975842;0.154488;,
  -0.156365;-0.987699;0.000000;,
  -0.154488;-0.975842;-0.154488;,
  0.000000;-0.987699;-0.156365;,
  0.154488;-0.975842;-0.154488;,
  0.156365;-0.987699;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.301511;0.301511;-0.904534;,
  -0.301511;0.301511;-0.904534;,
  -0.666667;0.333333;0.666667;,
  -0.000000;0.316228;0.948683;,
  -0.301511;0.301511;0.904534;,
  -0.904534;0.301511;0.301511;,
  -0.948683;0.316228;0.000000;,
  0.948683;0.316228;0.000000;,
  0.904534;0.301511;0.301511;,
  0.904534;0.301511;-0.301511;,
  0.301511;0.301511;0.904534;,
  -0.904534;0.301511;-0.301511;,
  0.154488;-0.975842;0.154488;,
  0.000000;-0.987699;0.156365;,
  0.000000;0.316228;-0.948683;,
  -0.154488;-0.975842;0.154488;,
  -0.156365;-0.987699;0.000000;,
  -0.154488;-0.975842;-0.154488;,
  0.000000;-0.987699;-0.156365;,
  0.154488;-0.975842;-0.154488;,
  0.156365;-0.987699;-0.000000;,
  0.000000;-1.000000;0.000000;,
  0.301511;0.301511;-0.904534;,
  -0.301511;0.301511;-0.904534;,
  -0.666667;0.333333;0.666667;,
  0.000000;0.316228;0.948683;,
  -0.301511;0.301511;0.904534;,
  -0.904534;0.301511;0.301511;,
  -0.948683;0.316228;0.000000;,
  0.948683;0.316228;0.000000;,
  0.904534;0.301511;0.301512;,
  0.904534;0.301511;-0.301512;,
  0.301511;0.301511;0.904534;,
  -0.904534;0.301511;-0.301511;,
  0.154488;-0.975842;0.154488;,
  -0.000000;-0.987699;0.156365;,
  -0.000000;0.316228;-0.948683;,
  -0.154488;-0.975842;0.154488;,
  -0.156365;-0.987699;0.000000;,
  -0.154488;-0.975842;-0.154488;,
  -0.000000;-0.987699;-0.156365;,
  0.154488;-0.975842;-0.154488;,
  0.156365;-0.987699;0.000000;,
  -0.000000;-1.000000;0.000000;,
  0.301511;0.301511;-0.904534;,
  -0.301512;0.301511;-0.904534;,
  -0.666667;0.333334;0.666666;,
  -0.000000;0.316228;0.948683;,
  -0.301512;0.301511;0.904534;,
  -0.904534;0.301512;0.301510;,
  -0.948683;0.316228;0.000000;,
  0.948684;0.316227;0.000000;,
  0.904534;0.301511;0.301511;,
  0.904534;0.301511;-0.301511;,
  0.301511;0.301511;0.904534;,
  -0.904534;0.301512;-0.301510;,
  0.154488;-0.975842;0.154488;,
  0.000000;-0.987699;0.156365;,
  0.000000;0.316228;-0.948683;,
  -0.154488;-0.975842;0.154488;,
  -0.156365;-0.987699;0.000000;,
  -0.154488;-0.975842;-0.154488;,
  0.000000;-0.987699;-0.156365;,
  0.154488;-0.975842;-0.154488;,
  0.156365;-0.987699;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.301511;0.301511;-0.904534;,
  -0.301511;0.301511;-0.904534;,
  -0.666667;0.333333;0.666667;,
  0.000000;0.316228;0.948683;,
  -0.301511;0.301511;0.904534;,
  -0.904534;0.301511;0.301511;,
  -0.948683;0.316228;0.000000;,
  0.948683;0.316228;0.000000;,
  0.904534;0.301511;0.301511;,
  0.904534;0.301511;-0.301511;,
  0.301511;0.301511;0.904534;,
  -0.904534;0.301511;-0.301511;,
  0.154488;-0.975842;0.154487;,
  0.000000;-0.987699;0.156365;,
  0.000000;0.316228;-0.948683;,
  -0.154488;-0.975842;0.154488;,
  -0.156365;-0.987699;-0.000000;,
  -0.154488;-0.975842;-0.154488;,
  0.000000;-0.987699;-0.156365;,
  0.154488;-0.975842;-0.154488;,
  0.156365;-0.987699;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.301512;0.301511;-0.904534;,
  -0.301512;0.301511;-0.904534;,
  -0.666666;0.333333;0.666667;,
  0.000000;0.316228;0.948683;,
  -0.301511;0.301511;0.904534;,
  -0.904534;0.301511;0.301512;,
  -0.948684;0.316227;-0.000000;,
  0.948683;0.316228;-0.000000;,
  0.904534;0.301511;0.301511;,
  0.904534;0.301511;-0.301511;,
  0.301511;0.301511;0.904534;,
  -0.904534;0.301511;-0.301513;,
  0.154488;-0.975842;0.154488;,
  -0.000000;-0.987699;0.156365;,
  -0.000000;0.316228;-0.948683;,
  -0.154488;-0.975842;0.154488;,
  -0.156365;-0.987699;-0.000000;,
  -0.154488;-0.975842;-0.154488;,
  -0.000000;-0.987699;-0.156365;,
  0.154488;-0.975842;-0.154488;,
  0.156365;-0.987699;-0.000000;,
  -0.000000;-1.000000;-0.000000;,
  0.301511;0.301511;-0.904534;,
  -0.301512;0.301511;-0.904534;,
  -0.666667;0.333334;0.666666;,
  -0.000000;0.316228;0.948683;,
  -0.301511;0.301511;0.904534;,
  -0.904534;0.301512;0.301510;,
  -0.948683;0.316228;-0.000000;,
  0.948684;0.316227;-0.000000;,
  0.904534;0.301511;0.301511;,
  0.904534;0.301511;-0.301511;,
  0.301510;0.301512;0.904534;,
  -0.904534;0.301512;-0.301510;,
  0.154488;-0.975842;0.154488;,
  0.000000;-0.987699;0.156365;,
  0.000000;0.316228;-0.948683;,
  -0.154488;-0.975842;0.154488;,
  -0.156365;-0.987699;0.000000;,
  -0.154488;-0.975842;-0.154488;,
  0.000000;-0.987699;-0.156365;,
  0.154488;-0.975842;-0.154488;,
  0.156365;-0.987699;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.301511;0.301511;-0.904534;,
  -0.301511;0.301511;-0.904534;,
  -0.666667;0.333333;0.666667;,
  0.000000;0.316228;0.948683;,
  -0.301511;0.301511;0.904534;,
  -0.904534;0.301511;0.301511;,
  -0.948683;0.316228;0.000000;,
  0.948683;0.316228;0.000000;,
  0.904534;0.301511;0.301512;,
  0.904534;0.301511;-0.301512;,
  0.301511;0.301511;0.904534;,
  -0.904534;0.301511;-0.301511;,
  0.154488;-0.975842;0.154488;,
  0.000000;-0.987699;0.156365;,
  0.000000;0.316228;-0.948683;,
  -0.154488;-0.975842;0.154488;,
  -0.156365;-0.987699;-0.000000;,
  -0.154488;-0.975842;-0.154488;,
  0.000000;-0.987699;-0.156365;,
  0.154488;-0.975842;-0.154488;,
  0.156365;-0.987699;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.301511;0.301512;-0.904534;,
  -0.301511;0.301512;-0.904534;,
  -0.666666;0.333333;0.666667;,
  0.000000;0.316228;0.948683;,
  -0.301511;0.301511;0.904534;,
  -0.904534;0.301511;0.301512;,
  -0.948683;0.316228;-0.000000;,
  0.948683;0.316228;-0.000000;,
  0.904534;0.301511;0.301512;,
  0.904534;0.301511;-0.301512;,
  0.301511;0.301511;0.904534;,
  -0.904534;0.301511;-0.301512;,
  0.154487;-0.975842;0.154489;,
  -0.000000;-0.987699;0.156366;,
  -0.000000;0.316227;-0.948684;,
  -0.154488;-0.975842;0.154488;,
  -0.156365;-0.987699;0.000000;,
  -0.154488;-0.975842;-0.154488;,
  -0.000000;-0.987699;-0.156365;,
  0.154488;-0.975842;-0.154488;,
  0.156365;-0.987699;0.000000;,
  -0.000000;-1.000000;0.000000;,
  0.301512;0.301510;-0.904534;,
  -0.301512;0.301510;-0.904534;,
  -0.666666;0.333335;0.666667;,
  -0.000000;0.316228;0.948683;,
  -0.301509;0.301512;0.904535;,
  -0.904534;0.301513;0.301510;,
  -0.948683;0.316229;0.000000;,
  0.948683;0.316228;0.000000;,
  0.904534;0.301511;0.301512;,
  0.904534;0.301511;-0.301512;,
  0.301509;0.301512;0.904535;,
  -0.904534;0.301513;-0.301510;;
  108;
  4;8,9,6,7;,
  4;9,4,5,6;,
  4;0,1,9,8;,
  4;1,3,4,9;,
  3;2,2,10;,
  3;2,11,2;,
  3;12,13,14;,
  3;12,15,16;,
  3;17,17,18;,
  3;17,19,17;,
  3;20,13,20;,
  3;21,21,16;,
  4;30,31,28,29;,
  4;31,26,27,28;,
  4;22,23,31,30;,
  4;23,25,26,31;,
  3;24,24,32;,
  3;24,33,24;,
  3;34,35,36;,
  3;34,37,38;,
  3;39,39,40;,
  3;39,41,39;,
  3;42,35,42;,
  3;43,43,38;,
  4;52,53,50,51;,
  4;53,48,49,50;,
  4;44,45,53,52;,
  4;45,47,48,53;,
  3;46,46,54;,
  3;46,55,46;,
  3;56,57,58;,
  3;56,59,60;,
  3;61,61,62;,
  3;61,63,61;,
  3;64,57,64;,
  3;65,65,60;,
  4;74,75,72,73;,
  4;75,70,71,72;,
  4;66,67,75,74;,
  4;67,69,70,75;,
  3;68,68,76;,
  3;68,77,68;,
  3;78,79,80;,
  3;78,81,82;,
  3;83,83,84;,
  3;83,85,83;,
  3;86,79,86;,
  3;87,87,82;,
  4;96,97,94,95;,
  4;97,92,93,94;,
  4;88,89,97,96;,
  4;89,91,92,97;,
  3;90,90,98;,
  3;90,99,90;,
  3;100,101,102;,
  3;100,103,104;,
  3;105,105,106;,
  3;105,107,105;,
  3;108,101,108;,
  3;109,109,104;,
  4;118,119,116,117;,
  4;119,114,115,116;,
  4;110,111,119,118;,
  4;111,113,114,119;,
  3;112,112,120;,
  3;112,121,112;,
  3;122,123,124;,
  3;122,125,126;,
  3;127,127,128;,
  3;127,129,127;,
  3;130,123,130;,
  3;131,131,126;,
  4;140,141,138,139;,
  4;141,136,137,138;,
  4;132,133,141,140;,
  4;133,135,136,141;,
  3;134,134,142;,
  3;134,143,134;,
  3;144,145,146;,
  3;144,147,148;,
  3;149,149,150;,
  3;149,151,149;,
  3;152,145,152;,
  3;153,153,148;,
  4;162,163,160,161;,
  4;163,158,159,160;,
  4;154,155,163,162;,
  4;155,157,158,163;,
  3;156,156,164;,
  3;156,165,156;,
  3;166,167,168;,
  3;166,169,170;,
  3;171,171,172;,
  3;171,173,171;,
  3;174,167,174;,
  3;175,175,170;,
  4;184,185,182,183;,
  4;185,180,181,182;,
  4;176,177,185,184;,
  4;177,179,180,185;,
  3;178,178,186;,
  3;178,187,178;,
  3;188,189,190;,
  3;188,191,192;,
  3;193,193,194;,
  3;193,195,193;,
  3;196,189,196;,
  3;197,197,192;;
 }
 MeshTextureCoords {
  198;
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.250000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.750000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.750000;,
  0.500000;0.500000;,
  0.000000;0.750000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.250000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.750000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.750000;,
  0.500000;0.500000;,
  0.000000;0.750000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.250000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.750000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.750000;,
  0.500000;0.500000;,
  0.000000;0.750000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.250000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.750000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.750000;,
  0.500000;0.500000;,
  0.000000;0.750000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.250000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.750000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.750000;,
  0.500000;0.500000;,
  0.000000;0.750000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.250000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.750000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.750000;,
  0.500000;0.500000;,
  0.000000;0.750000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.250000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.750000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.750000;,
  0.500000;0.500000;,
  0.000000;0.750000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.250000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.750000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.750000;,
  0.500000;0.500000;,
  0.000000;0.750000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.250000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.750000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.750000;,
  0.500000;0.500000;,
  0.000000;0.750000;;
 }
}