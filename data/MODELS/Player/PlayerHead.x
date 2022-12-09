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
 133;
 0.00000;40.00000;0.00000;,
 5.41196;38.47759;-5.41196;,
 0.00000;38.47759;-7.65366;,
 0.00000;40.00000;0.00000;,
 7.65366;38.47759;0.00000;,
 0.00000;40.00000;0.00000;,
 5.41196;38.47759;5.41196;,
 0.00000;40.00000;0.00000;,
 0.00000;38.47759;7.65366;,
 0.00000;40.00000;0.00000;,
 -5.41196;38.47759;5.41196;,
 0.00000;40.00000;0.00000;,
 -7.65366;38.47759;0.00000;,
 0.00000;40.00000;0.00000;,
 -5.41196;38.47759;-5.41196;,
 0.00000;40.00000;0.00000;,
 0.00000;38.47759;-7.65366;,
 0.00000;1.52241;-7.65366;,
 5.41196;1.52241;-5.41196;,
 0.00000;-0.00001;-0.00000;,
 7.65366;1.52241;0.00000;,
 0.00000;-0.00001;-0.00000;,
 5.41196;1.52241;5.41196;,
 0.00000;-0.00001;-0.00000;,
 0.00000;1.52241;7.65366;,
 0.00000;-0.00001;-0.00000;,
 -5.41196;1.52241;5.41196;,
 0.00000;-0.00001;-0.00000;,
 -7.65366;1.52241;0.00000;,
 0.00000;-0.00001;-0.00000;,
 -5.41196;1.52241;-5.41196;,
 0.00000;-0.00001;-0.00000;,
 0.00000;1.52241;-7.65366;,
 0.00000;-0.00001;-0.00000;,
 -10.00000;34.14214;10.00000;,
 -16.14214;54.40569;0.00000;,
 -13.67758;33.82305;0.00000;,
 -13.06564;27.65367;13.06562;,
 -10.00000;34.14214;-10.00000;,
 -13.06564;27.65367;-13.06562;,
 13.67758;33.82305;0.00000;,
 16.14214;54.40569;0.00000;,
 10.00000;34.14214;10.00000;,
 13.06562;27.65367;13.06562;,
 10.00000;34.14214;-10.00000;,
 13.06562;27.65367;-13.06562;,
 0.00000;34.14214;-14.14214;,
 0.00000;34.14214;14.14214;,
 0.00000;34.14214;-14.14214;,
 0.00000;27.65367;-18.47758;,
 0.00000;27.65367;18.47758;,
 0.00000;27.65367;-18.47758;,
 14.14214;20.00000;-14.14214;,
 -0.00016;20.04530;-24.37198;,
 18.80000;23.60482;0.00000;,
 14.14214;20.00000;14.14214;,
 0.00000;20.00000;20.00000;,
 -14.14214;20.00000;14.14214;,
 -18.80000;23.60482;0.00000;,
 -14.14214;20.00000;-14.14214;,
 -0.00016;20.04530;-24.37198;,
 12.06562;12.34631;-13.06562;,
 0.00000;12.34631;-22.78564;,
 17.67758;12.34631;0.00000;,
 13.06562;12.34631;13.06562;,
 0.00000;12.34631;18.47758;,
 -13.06564;12.34631;13.06562;,
 -17.67758;12.34631;0.00000;,
 -12.06564;12.34631;-13.06562;,
 0.00000;12.34631;-22.78564;,
 10.00000;5.85785;-10.00000;,
 0.00000;5.85785;-15.21528;,
 14.14214;5.85785;0.00000;,
 10.00000;5.85785;10.00000;,
 0.00000;5.85785;14.14214;,
 -10.00000;5.85785;10.00000;,
 -14.14214;5.85785;0.00000;,
 -10.00000;5.85785;-10.00000;,
 0.00000;5.85785;-15.21528;,
 -9.10286;32.26167;-11.97400;,
 -5.80990;33.41104;-12.65787;,
 -6.86274;31.54585;-13.47945;,
 -10.72872;30.55049;-12.43067;,
 -5.80990;33.41104;-12.65787;,
 -3.06703;32.33030;-14.64308;,
 -2.27856;30.64657;-16.16739;,
 -5.67387;31.55936;-14.00517;,
 -6.26830;31.55260;-13.74231;,
 -6.72671;29.69417;-14.82675;,
 -7.32115;29.68738;-14.56388;,
 -6.13227;29.70092;-15.08961;,
 -10.72872;30.55049;-12.43067;,
 -7.18512;27.83568;-15.91119;,
 -9.92798;28.91644;-13.92598;,
 -2.27856;30.64657;-16.16739;,
 -3.89216;28.98510;-16.59506;,
 -7.18512;27.83568;-15.91119;,
 -5.80990;33.41104;-12.65787;,
 -5.80990;33.41104;-12.65787;,
 -7.18512;27.83568;-15.91119;,
 -7.18512;27.83568;-15.91119;,
 -10.72872;30.55049;-12.43067;,
 -2.27856;30.64657;-16.16739;,
 2.80895;32.40426;-14.46465;,
 5.60664;33.46538;-12.54648;,
 5.40619;31.58610;-13.84675;,
 1.95761;30.70444;-15.93632;,
 5.60664;33.46538;-12.54648;,
 8.88146;32.25349;-11.88360;,
 10.45913;30.49334;-12.32285;,
 6.60229;31.55642;-13.33836;,
 6.00425;31.57127;-13.59256;,
 6.40186;29.67720;-14.63864;,
 5.80381;29.69204;-14.89284;,
 6.99991;29.66234;-14.38445;,
 1.95761;30.70444;-15.93632;,
 6.79947;27.78308;-15.68472;,
 3.52465;28.99488;-16.34762;,
 10.45913;30.49334;-12.32285;,
 9.59715;28.84414;-13.76655;,
 6.79947;27.78308;-15.68472;,
 5.60664;33.46538;-12.54648;,
 5.60664;33.46538;-12.54648;,
 6.79947;27.78308;-15.68472;,
 6.79947;27.78308;-15.68472;,
 1.95761;30.70444;-15.93632;,
 10.45913;30.49334;-12.32285;,
 -3.00016;20.04530;-22.51903;,
 -0.00016;20.04530;-24.37198;,
 -0.00016;17.38951;-23.95637;,
 -1.00016;17.38951;-23.22828;,
 2.99984;20.04530;-22.51903;,
 0.99984;17.38951;-23.22828;;
 
 138;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 3;17,18,19;,
 3;18,20,21;,
 3;20,22,23;,
 3;22,24,25;,
 3;24,26,27;,
 3;26,28,29;,
 3;28,30,31;,
 3;30,32,33;,
 3;34,35,36;,
 3;34,36,37;,
 3;38,39,36;,
 3;38,36,35;,
 3;40,41,42;,
 3;40,42,43;,
 3;44,41,40;,
 3;44,40,45;,
 3;1,44,46;,
 3;1,46,2;,
 3;1,4,41;,
 3;1,41,44;,
 3;6,42,41;,
 3;6,41,4;,
 3;8,47,42;,
 3;8,42,6;,
 3;10,34,47;,
 3;10,47,8;,
 3;10,12,35;,
 3;10,35,34;,
 3;14,38,35;,
 3;14,35,12;,
 3;16,48,38;,
 3;16,38,14;,
 3;44,45,49;,
 3;44,49,46;,
 3;47,50,43;,
 3;47,43,42;,
 3;34,37,50;,
 3;34,50,47;,
 3;48,51,39;,
 3;48,39,38;,
 3;49,45,52;,
 3;49,52,53;,
 3;45,40,54;,
 3;45,54,52;,
 3;43,55,54;,
 3;43,54,40;,
 3;50,56,55;,
 3;50,55,43;,
 3;37,57,56;,
 3;37,56,50;,
 3;37,36,58;,
 3;37,58,57;,
 3;39,59,58;,
 3;39,58,36;,
 3;51,60,59;,
 3;51,59,39;,
 3;53,52,61;,
 3;53,61,62;,
 3;52,54,63;,
 3;52,63,61;,
 3;55,64,63;,
 3;55,63,54;,
 3;56,65,64;,
 3;56,64,55;,
 3;57,66,65;,
 3;57,65,56;,
 3;57,58,67;,
 3;57,67,66;,
 3;59,68,67;,
 3;59,67,58;,
 3;60,69,68;,
 3;60,68,59;,
 3;61,70,71;,
 3;61,71,62;,
 3;63,72,70;,
 3;63,70,61;,
 3;63,64,73;,
 3;63,73,72;,
 3;65,74,73;,
 3;65,73,64;,
 3;66,75,74;,
 3;66,74,65;,
 3;67,76,75;,
 3;67,75,66;,
 3;67,68,77;,
 3;67,77,76;,
 3;68,69,78;,
 3;68,78,77;,
 3;70,18,17;,
 3;70,17,71;,
 3;72,20,18;,
 3;72,18,70;,
 3;73,22,20;,
 3;73,20,72;,
 3;74,24,22;,
 3;74,22,73;,
 3;75,26,24;,
 3;75,24,74;,
 3;76,28,26;,
 3;76,26,75;,
 3;77,30,28;,
 3;77,28,76;,
 3;77,78,32;,
 3;77,32,30;,
 4;79,80,81,82;,
 4;83,84,85,86;,
 4;81,87,88,89;,
 4;87,86,90,88;,
 4;91,89,92,93;,
 4;90,94,95,96;,
 3;97,87,81;,
 3;98,86,87;,
 3;99,89,88;,
 3;100,88,90;,
 3;101,81,89;,
 3;102,90,86;,
 4;103,104,105,106;,
 4;107,108,109,110;,
 4;105,111,112,113;,
 4;111,110,114,112;,
 4;115,113,116,117;,
 4;114,118,119,120;,
 3;121,111,105;,
 3;122,110,111;,
 3;123,113,112;,
 3;124,112,114;,
 3;125,105,113;,
 3;126,114,110;,
 4;127,128,129,130;,
 4;128,131,132,129;;
 
 MeshMaterialList {
  4;
  138;
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
  0,
  0,
  1,
  1,
  0,
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
  2,
  2,
  3,
  3,
  2,
  2,
  3,
  3,
  3,
  3,
  2,
  2,
  2,
  2,
  3,
  3,
  2,
  2,
  3,
  3,
  3,
  3,
  2,
  2,
  1,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\StripedCat.jpg";
   }
  }
  Material {
   0.800000;0.655686;0.693333;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.476863;0.075294;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  102;
  -0.000000;1.000000;-0.000000;,
  -0.046420;0.907858;-0.416699;,
  0.084502;0.880295;-0.466841;,
  0.195091;0.980785;0.000000;,
  0.045718;0.894891;0.443937;,
  0.046420;0.907858;0.416699;,
  -0.084502;0.880295;0.466840;,
  -0.195091;0.980785;0.000000;,
  -0.045718;0.894891;-0.443937;,
  -0.017941;0.709116;-0.704863;,
  0.592704;0.512995;-0.620917;,
  0.992907;-0.118890;-0.000000;,
  0.576131;0.584031;0.571822;,
  0.017941;0.709116;0.704863;,
  -0.592704;0.512996;0.620917;,
  -0.992907;-0.118890;0.000000;,
  -0.576131;0.584032;-0.571822;,
  0.051568;0.475046;-0.878449;,
  0.722328;0.401709;-0.562914;,
  0.952021;0.306031;-0.000000;,
  0.662002;0.431036;0.613157;,
  0.009213;0.384535;0.923065;,
  -0.674651;0.369948;0.638736;,
  -0.952021;0.306032;-0.000000;,
  -0.662002;0.431036;-0.613157;,
  0.600567;0.039108;-0.798618;,
  0.776500;0.044589;-0.628538;,
  0.982591;0.185780;-0.000000;,
  0.728758;0.016246;0.684579;,
  0.000000;0.000000;1.000000;,
  -0.727916;-0.050730;0.683787;,
  -0.982591;0.185779;-0.000000;,
  -0.776502;0.044591;-0.628535;,
  0.565354;-0.433446;-0.701783;,
  0.657697;-0.404273;-0.635608;,
  0.941358;-0.337019;-0.016242;,
  0.617659;-0.346711;0.705896;,
  -0.009212;-0.384534;0.923065;,
  -0.604325;-0.420803;0.676548;,
  -0.941358;-0.337018;-0.016242;,
  -0.657697;-0.404277;-0.635606;,
  0.000000;-0.738690;-0.674045;,
  0.547305;-0.682932;-0.483797;,
  0.700335;-0.712201;-0.047961;,
  0.548633;-0.679432;0.487210;,
  -0.017941;-0.709117;0.704862;,
  -0.525538;-0.699092;0.484852;,
  -0.700335;-0.712201;0.047961;,
  -0.549370;-0.705984;-0.446966;,
  0.000000;-0.907356;-0.420363;,
  0.327474;-0.907859;-0.261827;,
  0.416699;-0.907859;0.046419;,
  0.261827;-0.907859;0.327474;,
  -0.046419;-0.907859;0.416699;,
  -0.327474;-0.907859;0.261827;,
  -0.416699;-0.907859;-0.046419;,
  -0.269132;-0.924735;-0.269132;,
  -0.000000;-1.000000;-0.000000;,
  -0.346747;0.535059;-0.770375;,
  -0.346746;0.535060;-0.770375;,
  -0.346750;0.535059;-0.770374;,
  -0.346748;0.535055;-0.770378;,
  -0.346748;0.535057;-0.770377;,
  -0.346746;0.535059;-0.770376;,
  -0.346747;0.535059;-0.770376;,
  -0.346751;0.535057;-0.770376;,
  -0.346756;0.535052;-0.770376;,
  -0.346752;0.535053;-0.770378;,
  -0.346746;0.535055;-0.770379;,
  -0.346748;0.535054;-0.770378;,
  -0.346753;0.535052;-0.770378;,
  -0.346751;0.535054;-0.770377;,
  0.347551;0.508171;-0.788017;,
  0.347553;0.508168;-0.788018;,
  0.347560;0.508173;-0.788012;,
  0.347552;0.508171;-0.788017;,
  0.347547;0.508173;-0.788018;,
  0.347549;0.508171;-0.788018;,
  0.347558;0.508172;-0.788013;,
  0.347558;0.508172;-0.788013;,
  0.347549;0.508171;-0.788018;,
  0.347552;0.508170;-0.788017;,
  0.347557;0.508170;-0.788015;,
  0.347551;0.508163;-0.788022;,
  0.347555;0.508164;-0.788020;,
  0.347559;0.508166;-0.788017;,
  -0.551575;-0.145980;-0.821252;,
  0.551575;-0.145980;-0.821252;,
  -0.828861;0.441721;0.343325;,
  -0.882503;0.470308;-0.000000;,
  -0.780163;0.540901;0.314278;,
  -0.332619;0.496498;-0.801782;,
  -0.332619;0.496498;0.801782;,
  -0.828861;0.441721;-0.343325;,
  0.828861;0.441721;-0.343324;,
  0.882503;0.470308;0.000000;,
  0.780163;0.540901;-0.314278;,
  0.332619;0.496498;0.801782;,
  0.332619;0.496498;-0.801782;,
  0.828861;0.441721;0.343324;,
  -0.600572;0.039103;-0.798614;,
  -0.565350;-0.433457;-0.701779;;
  138;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,56,57;,
  3;56,49,57;,
  3;14,15,23;,
  3;14,23,22;,
  3;16,24,23;,
  3;16,23,15;,
  3;19,11,12;,
  3;19,12,20;,
  3;10,11,19;,
  3;10,19,18;,
  3;2,10,9;,
  3;2,9,1;,
  3;88,89,90;,
  3;2,91,91;,
  3;4,92,90;,
  3;93,90,89;,
  3;5,13,12;,
  3;5,12,4;,
  3;6,14,13;,
  3;6,13,5;,
  3;94,95,96;,
  3;6,97,97;,
  3;8,98,96;,
  3;99,96,95;,
  3;1,9,16;,
  3;1,16,8;,
  3;10,18,17;,
  3;10,17,9;,
  3;13,21,20;,
  3;13,20,12;,
  3;14,22,21;,
  3;14,21,13;,
  3;9,17,24;,
  3;9,24,16;,
  3;17,18,26;,
  3;17,26,25;,
  3;18,19,27;,
  3;18,27,26;,
  3;20,28,27;,
  3;20,27,19;,
  3;21,29,28;,
  3;21,28,20;,
  3;22,30,29;,
  3;22,29,21;,
  3;22,23,31;,
  3;22,31,30;,
  3;24,32,31;,
  3;24,31,23;,
  3;17,100,32;,
  3;17,32,24;,
  3;25,26,34;,
  3;25,34,33;,
  3;26,27,35;,
  3;26,35,34;,
  3;28,36,35;,
  3;28,35,27;,
  3;29,37,36;,
  3;29,36,28;,
  3;30,38,37;,
  3;30,37,29;,
  3;30,31,39;,
  3;30,39,38;,
  3;32,40,39;,
  3;32,39,31;,
  3;100,101,40;,
  3;100,40,32;,
  3;34,42,41;,
  3;34,41,33;,
  3;35,43,42;,
  3;35,42,34;,
  3;35,36,44;,
  3;35,44,43;,
  3;37,45,44;,
  3;37,44,36;,
  3;38,46,45;,
  3;38,45,37;,
  3;39,47,46;,
  3;39,46,38;,
  3;39,40,48;,
  3;39,48,47;,
  3;40,101,41;,
  3;40,41,48;,
  3;42,50,49;,
  3;42,49,41;,
  3;43,51,50;,
  3;43,50,42;,
  3;44,52,51;,
  3;44,51,43;,
  3;45,53,52;,
  3;45,52,44;,
  3;46,54,53;,
  3;46,53,45;,
  3;47,55,54;,
  3;47,54,46;,
  3;48,56,55;,
  3;48,55,47;,
  3;48,41,49;,
  3;48,49,56;,
  4;58,59,62,61;,
  4;59,60,65,64;,
  4;62,63,67,66;,
  4;63,64,68,67;,
  4;61,66,70,69;,
  4;68,65,71,70;,
  3;59,63,62;,
  3;59,64,63;,
  3;70,66,67;,
  3;70,67,68;,
  3;61,62,66;,
  3;65,68,64;,
  4;72,73,76,75;,
  4;73,74,79,78;,
  4;76,77,81,80;,
  4;77,78,82,81;,
  4;75,80,84,83;,
  4;82,79,85,84;,
  3;73,77,76;,
  3;73,78,77;,
  3;84,80,81;,
  3;84,81,82;,
  3;75,76,80;,
  3;79,82,78;,
  4;86,86,86,86;,
  4;87,87,87,87;;
 }
 MeshTextureCoords {
  133;
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.000000;0.875000;,
  0.125000;0.875000;,
  0.062500;1.000000;,
  0.250000;0.875000;,
  0.187500;1.000000;,
  0.375000;0.875000;,
  0.312500;1.000000;,
  0.500000;0.875000;,
  0.437500;1.000000;,
  0.625000;0.875000;,
  0.562500;1.000000;,
  0.750000;0.875000;,
  0.687500;1.000000;,
  0.875000;0.875000;,
  0.812500;1.000000;,
  1.000000;0.875000;,
  0.937500;1.000000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.750000;0.375000;,
  0.625000;0.375000;,
  0.875000;0.250000;,
  0.875000;0.375000;,
  0.250000;0.375000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.375000;0.375000;,
  0.125000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.250000;,
  0.500000;0.250000;,
  1.000000;0.250000;,
  0.000000;0.375000;,
  0.500000;0.375000;,
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
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.333333;,
  0.000000;0.333333;,
  0.750000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.333333;,
  0.750000;0.333333;,
  0.500000;0.333333;,
  0.500000;0.666667;,
  0.250000;0.666667;,
  0.750000;0.666667;,
  0.000000;0.666667;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.666667;,
  1.000000;1.000000;,
  0.750000;1.000000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.333333;,
  0.000000;0.333333;,
  0.750000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.333333;,
  0.750000;0.333333;,
  0.500000;0.333333;,
  0.500000;0.666667;,
  0.250000;0.666667;,
  0.750000;0.666667;,
  0.000000;0.666667;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.666667;,
  1.000000;1.000000;,
  0.750000;1.000000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;;
 }
}
