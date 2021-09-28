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
 109;
 3869.04907;-1651.82007;-99552.18750;,
 4405.29907;-1651.82007;-95887.55859;,
 4405.29907;27142.06299;-95887.55859;,
 3869.04907;27142.06299;-99552.18750;,
 -14754.38110;27142.06299;-93083.88672;,
 -15290.63110;27142.06299;-96748.55469;,
 -14754.38110;-1651.82007;-93083.88672;,
 -15290.63110;-1651.82007;-96748.55469;,
 3157.80396;338.43399;-95168.65234;,
 -13353.21167;338.43399;-92752.57812;,
 -13353.21167;25151.80908;-92752.57812;,
 3157.80396;25151.80908;-95168.65234;,
 -15308.49121;27258.95264;18033.78662;,
 -32038.20557;27258.95264;9509.57764;,
 -30281.01318;27257.88818;7091.00342;,
 -14384.67651;27257.88818;15190.58594;,
 -45314.99512;27258.95264;-3767.21436;,
 -42896.42090;27257.88818;-5524.41162;,
 -53839.20410;27258.95264;-20496.92627;,
 -50996.00098;27257.88818;-21420.74219;,
 -56776.45020;27258.95264;-39041.95801;,
 -53786.92871;27257.88818;-39041.95801;,
 -53839.20410;27258.95264;-57587.02637;,
 -50996.00098;27257.88818;-56663.20801;,
 -45314.97559;27258.95264;-74316.75293;,
 -42896.41113;27257.88818;-72559.55566;,
 -32038.18604;27258.95264;-87593.51562;,
 -30280.99365;27257.88818;-85174.92188;,
 -15308.47778;27258.94287;-96117.77344;,
 -14384.66675;27257.87842;-93274.53125;,
 3236.54907;27258.94287;-99055.00000;,
 21781.57471;27258.95264;-96117.77344;,
 20857.76611;27257.88818;-93274.53125;,
 3236.54907;27257.87842;-96065.48828;,
 38511.28662;27258.95264;-87593.49609;,
 36754.08936;27257.88818;-85174.92188;,
 51788.05176;27258.95264;-74316.73340;,
 49369.47754;27257.88818;-72559.54590;,
 60312.26074;27258.95264;-57587.01660;,
 57469.05762;27257.88818;-56663.19824;,
 63249.50684;27258.95264;-39041.95801;,
 60259.98535;27257.88818;-39041.95801;,
 60312.26074;27258.95264;-20496.93604;,
 57469.05762;27257.88818;-21420.74707;,
 51788.05176;27258.95264;-3767.22900;,
 49369.46777;27257.88818;-5524.42627;,
 38511.28174;27258.95264;9509.54834;,
 36754.07959;27257.88818;7090.97412;,
 12509.05396;27258.95264;19502.36816;,
 12047.14844;27257.88818;16586.01318;,
 -32038.20557;-4065.14526;9509.57764;,
 -15308.49121;-4065.14526;18033.78662;,
 3236.54663;-4065.14526;-39041.95801;,
 -45314.98535;-4065.14526;-3767.21436;,
 -53839.20410;-4065.14526;-20496.92627;,
 -56776.45020;-4065.14526;-39041.95801;,
 -53839.20410;-4065.14526;-57587.02637;,
 -45314.97559;-4065.14526;-74316.75293;,
 -32038.18604;-4065.14526;-87593.49609;,
 -15308.47778;-4065.14526;-96117.77344;,
 3236.54907;-4065.14526;-99055.00000;,
 21781.57471;-4065.14526;-96117.77344;,
 38511.28662;-4065.14526;-87593.49609;,
 51788.05176;-4065.14526;-74316.73340;,
 60312.26074;-4065.14526;-57587.01660;,
 63249.50684;-4065.14526;-39041.95801;,
 60312.26074;-4065.14526;-20496.93604;,
 51788.05176;-4065.14526;-3767.22900;,
 38511.28174;-4065.14526;9509.54834;,
 12509.05396;-4065.14526;19502.36816;,
 -14384.67651;-1590.69946;15190.58594;,
 -30281.01318;-1590.69946;7091.00342;,
 3236.54663;-1589.35455;-39041.95801;,
 -42896.42090;-1590.69946;-5524.41162;,
 -50996.00098;-1590.69946;-21420.74219;,
 -53786.92871;-1590.69946;-39041.95801;,
 -50996.00098;-1590.69946;-56663.20801;,
 -42896.41113;-1590.69946;-72559.55566;,
 -30280.99365;-1590.69946;-85174.92188;,
 -14384.66675;-1590.69946;-93274.53125;,
 3236.54907;-1590.69946;-96065.48828;,
 20857.76611;-1590.69946;-93274.53125;,
 36754.08936;-1590.69946;-85174.92188;,
 49369.47754;-1590.69946;-72559.54590;,
 57469.05762;-1590.69946;-56663.19824;,
 60259.98535;-1590.69946;-39041.95801;,
 57469.05762;-1590.69946;-21420.74707;,
 49369.46777;-1590.69946;-5524.42627;,
 36754.07959;-1590.69946;7090.97412;,
 12047.14844;-1590.69946;16586.01318;,
 -32038.20557;-1589.63501;9509.57764;,
 -15308.49121;-1589.63501;18033.78662;,
 -45314.99512;-1589.63501;-3767.21436;,
 -53839.20410;-1589.63501;-20496.92627;,
 -56776.45020;-1589.63501;-39041.95801;,
 -53839.20410;-1589.63501;-57587.02637;,
 -45314.97559;-1589.63501;-74316.75293;,
 -32038.18604;-1589.63501;-87593.51562;,
 -15308.47778;-1589.63150;-96117.77344;,
 3236.54907;-1589.63150;-99055.00000;,
 21781.57471;-1589.63501;-96117.77344;,
 38511.28662;-1589.63501;-87593.49609;,
 51788.05176;-1589.63501;-74316.73340;,
 60312.26074;-1589.63501;-57587.01660;,
 63249.50684;-1589.63501;-39041.95801;,
 60312.26074;-1589.63501;-20496.93604;,
 51788.05176;-1589.63501;-3767.22900;,
 38511.28174;-1589.63501;9509.54834;,
 12509.05396;-1589.63501;19502.36816;;
 
 127;
 4;3,2,1,0;,
 4;5,4,2,3;,
 4;7,6,4,5;,
 4;0,1,6,7;,
 4;11,10,9,8;,
 4;5,3,0,7;,
 4;8,9,6,1;,
 4;9,10,4,6;,
 4;10,11,2,4;,
 4;11,8,1,2;,
 4;15,14,13,12;,
 4;14,17,16,13;,
 4;17,19,18,16;,
 4;19,21,20,18;,
 4;21,23,22,20;,
 4;23,25,24,22;,
 4;25,27,26,24;,
 4;27,29,28,26;,
 4;33,32,31,30;,
 4;32,35,34,31;,
 4;35,37,36,34;,
 4;37,39,38,36;,
 4;39,41,40,38;,
 4;41,43,42,40;,
 4;43,45,44,42;,
 4;45,47,46,44;,
 4;47,49,48,46;,
 4;49,15,12,48;,
 3;52,51,50;,
 3;52,50,53;,
 3;52,53,54;,
 3;52,54,55;,
 3;52,55,56;,
 3;52,56,57;,
 3;52,57,58;,
 3;52,58,59;,
 3;52,59,60;,
 3;52,60,61;,
 3;52,61,62;,
 3;52,62,63;,
 3;52,63,64;,
 3;52,64,65;,
 3;52,65,66;,
 3;52,66,67;,
 3;52,67,68;,
 3;52,68,69;,
 3;52,69,51;,
 3;72,71,70;,
 3;72,73,71;,
 3;72,74,73;,
 3;72,75,74;,
 3;72,76,75;,
 3;72,77,76;,
 3;72,78,77;,
 3;72,79,78;,
 3;72,80,79;,
 3;72,81,80;,
 3;72,82,81;,
 3;72,83,82;,
 3;72,84,83;,
 3;72,85,84;,
 3;72,86,85;,
 3;72,87,86;,
 3;72,88,87;,
 3;72,89,88;,
 3;72,70,89;,
 4;91,90,50,51;,
 4;90,92,53,50;,
 4;92,93,54,53;,
 4;93,94,55,54;,
 4;94,95,56,55;,
 4;95,96,57,56;,
 4;96,97,58,57;,
 4;97,98,59,58;,
 4;98,99,60,59;,
 4;99,100,61,60;,
 4;100,101,62,61;,
 4;101,102,63,62;,
 4;102,103,64,63;,
 4;103,104,65,64;,
 4;104,105,66,65;,
 4;105,106,67,66;,
 4;106,107,68,67;,
 4;107,108,69,68;,
 4;108,91,51,69;,
 4;12,13,90,91;,
 4;14,15,70,71;,
 4;13,16,92,90;,
 4;17,14,71,73;,
 4;16,18,93,92;,
 4;19,17,73,74;,
 4;18,20,94,93;,
 4;21,19,74,75;,
 4;20,22,95,94;,
 4;23,21,75,76;,
 4;22,24,96,95;,
 4;25,23,76,77;,
 4;24,26,97,96;,
 4;27,25,77,78;,
 4;26,28,98,97;,
 4;29,27,78,79;,
 4;30,31,100,99;,
 4;32,33,80,81;,
 4;31,34,101,100;,
 4;35,32,81,82;,
 4;34,36,102,101;,
 4;37,35,82,83;,
 4;36,38,103,102;,
 4;39,37,83,84;,
 4;38,40,104,103;,
 4;41,39,84,85;,
 4;40,42,105,104;,
 4;43,41,85,86;,
 4;42,44,106,105;,
 4;45,43,86,87;,
 4;44,46,107,106;,
 4;47,45,87,88;,
 4;46,48,108,107;,
 4;49,47,88,89;,
 4;48,12,91,108;,
 4;15,49,89,70;,
 3;98,30,99;,
 3;98,33,30;,
 3;98,80,33;,
 3;98,79,80;,
 3;98,29,79;,
 3;98,28,29;;
 
 MeshMaterialList {
  2;
  127;
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
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "wood.png";
   }
  }
 }
 MeshNormals {
  121;
  0.989462;0.000000;-0.144789;,
  0.000000;1.000000;0.000000;,
  -0.989463;0.000000;0.144788;,
  0.018626;-0.087918;0.995954;,
  0.267525;-0.087918;0.959531;,
  0.018626;0.087918;0.995954;,
  0.267525;0.087918;0.959531;,
  0.000000;-1.000000;0.000000;,
  -0.000006;1.000000;0.000023;,
  -0.000014;1.000000;0.000019;,
  -0.000019;1.000000;0.000014;,
  -0.000022;1.000000;0.000007;,
  -0.000024;1.000000;0.000000;,
  -0.000022;1.000000;-0.000007;,
  -0.000019;1.000000;-0.000014;,
  -0.000014;1.000000;-0.000019;,
  0.000014;1.000000;0.000104;,
  0.000019;1.000000;0.000103;,
  0.000007;1.000000;-0.000022;,
  0.000014;1.000000;-0.000019;,
  0.000019;1.000000;-0.000014;,
  0.000022;1.000000;-0.000007;,
  0.000024;1.000000;0.000000;,
  0.000022;1.000000;0.000007;,
  0.000019;1.000000;0.000014;,
  0.000013;1.000000;0.000020;,
  0.000004;1.000000;0.000024;,
  -0.000000;1.000000;-0.000001;,
  -0.259005;0.000000;0.965876;,
  -0.587785;-0.000000;0.809017;,
  -0.809017;-0.000001;0.587785;,
  -0.951057;-0.000000;0.309017;,
  -1.000000;0.000000;0.000000;,
  -0.951056;0.000000;-0.309017;,
  -0.809017;-0.000001;-0.587786;,
  -0.587786;-0.000002;-0.809017;,
  -0.309018;-0.000001;-0.951056;,
  0.000000;0.000000;-1.000000;,
  0.309018;0.000000;-0.951056;,
  0.587786;0.000000;-0.809016;,
  0.809017;0.000000;-0.587785;,
  0.951057;0.000000;-0.309017;,
  1.000000;0.000000;0.000000;,
  0.951056;0.000000;0.309017;,
  0.809017;0.000000;0.587785;,
  0.544801;0.000000;0.838565;,
  0.156435;0.000000;0.987688;,
  0.000092;1.000000;-0.000345;,
  0.000209;1.000000;-0.000288;,
  0.000288;1.000000;-0.000209;,
  0.000339;1.000000;-0.000110;,
  0.000356;1.000000;-0.000000;,
  0.000339;1.000000;0.000110;,
  0.000288;1.000000;0.000209;,
  0.000210;1.000000;0.000288;,
  0.000164;1.000000;0.000321;,
  -0.479211;0.877700;0.000312;,
  -0.000110;1.000000;0.000339;,
  -0.000209;1.000000;0.000288;,
  -0.000288;1.000000;0.000209;,
  -0.000339;1.000000;0.000110;,
  -0.000356;1.000000;-0.000000;,
  -0.000339;1.000000;-0.000110;,
  -0.000288;1.000000;-0.000209;,
  -0.000194;1.000000;-0.000299;,
  -0.000056;1.000000;-0.000356;,
  -0.144788;0.000000;-0.989463;,
  0.328060;-0.132233;0.935356;,
  -0.046296;-0.132232;0.990137;,
  -0.046296;0.132232;0.990137;,
  0.328060;0.132232;0.935356;,
  -0.259005;0.000000;0.965876;,
  -0.587785;-0.000001;0.809017;,
  -0.809017;-0.000002;0.587785;,
  -0.951056;-0.000001;0.309017;,
  -1.000000;0.000000;0.000000;,
  -0.809016;-0.000001;-0.587786;,
  -0.587786;-0.000003;-0.809017;,
  -0.309018;-0.000002;-0.951056;,
  0.000000;0.000000;-1.000000;,
  0.309018;0.000000;-0.951056;,
  0.587786;0.000000;-0.809016;,
  0.809017;0.000000;-0.587785;,
  1.000000;0.000000;0.000000;,
  0.544801;0.000000;0.838566;,
  0.156435;0.000000;0.987688;,
  -0.587785;0.000000;0.809017;,
  0.587785;0.000000;-0.809017;,
  0.259005;0.000000;-0.965876;,
  -0.809017;0.000000;0.587785;,
  0.809017;0.000000;-0.587785;,
  -0.951057;0.000000;0.309017;,
  0.951057;0.000000;-0.309017;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;-0.000000;,
  0.951057;0.000000;0.309017;,
  -0.809017;0.000000;-0.587786;,
  0.809017;0.000000;0.587786;,
  -0.587786;0.000000;-0.809017;,
  0.587785;0.000000;0.809017;,
  -0.453992;0.000000;-0.891006;,
  0.453992;0.000000;0.891006;,
  0.000000;0.000000;-1.000000;,
  -0.309018;0.000000;0.951056;,
  -0.079865;0.000000;0.996806;,
  -0.587786;0.000000;0.809017;,
  -0.809017;0.000000;0.587785;,
  -0.951057;0.000000;0.309017;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;-0.000000;,
  0.951057;0.000000;0.309017;,
  -0.951056;0.000000;-0.309017;,
  0.809017;0.000000;0.587785;,
  -0.809017;0.000000;-0.587785;,
  -0.544801;0.000000;-0.838565;,
  -0.156435;0.000000;-0.987688;,
  -0.479161;0.877727;0.000313;,
  -0.002819;0.000000;0.999996;,
  0.951058;0.000000;-0.309013;,
  0.951058;0.000000;-0.309013;,
  0.951058;0.000000;-0.309013;;
  127;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;7,7,7,7;,
  4;6,5,3,4;,
  4;66,66,66,66;,
  4;4,3,68,67;,
  4;3,5,69,68;,
  4;5,6,70,69;,
  4;6,4,67,70;,
  4;47,48,48,47;,
  4;48,49,49,48;,
  4;49,50,50,49;,
  4;50,51,51,50;,
  4;51,52,52,51;,
  4;52,53,53,52;,
  4;53,54,54,53;,
  4;54,55,55,54;,
  4;56,57,57,56;,
  4;57,58,58,57;,
  4;58,59,59,58;,
  4;59,60,60,59;,
  4;60,61,61,60;,
  4;61,62,62,61;,
  4;62,63,63,62;,
  4;63,64,64,63;,
  4;64,65,65,64;,
  4;65,47,47,65;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;27,9,8;,
  3;27,10,9;,
  3;27,11,10;,
  3;27,12,11;,
  3;27,13,12;,
  3;27,14,13;,
  3;27,15,14;,
  3;27,16,15;,
  3;27,17,16;,
  3;27,18,17;,
  3;27,19,18;,
  3;27,20,19;,
  3;27,21,20;,
  3;27,22,21;,
  3;27,23,22;,
  3;27,24,23;,
  3;27,25,24;,
  3;27,26,25;,
  3;27,8,26;,
  4;28,29,72,71;,
  4;29,30,73,72;,
  4;30,31,74,73;,
  4;31,32,75,74;,
  4;32,33,33,75;,
  4;33,34,76,33;,
  4;34,35,77,76;,
  4;35,36,78,77;,
  4;36,37,79,78;,
  4;37,38,80,79;,
  4;38,39,81,80;,
  4;39,40,82,81;,
  4;40,41,41,82;,
  4;41,42,83,41;,
  4;42,43,43,83;,
  4;43,44,44,43;,
  4;44,45,84,44;,
  4;45,46,85,84;,
  4;46,28,71,85;,
  4;28,86,29,28;,
  4;87,88,88,87;,
  4;86,89,30,29;,
  4;90,87,87,90;,
  4;89,91,31,30;,
  4;92,90,90,92;,
  4;91,93,32,31;,
  4;94,92,92,94;,
  4;93,33,33,32;,
  4;95,94,94,95;,
  4;33,96,34,33;,
  4;97,95,95,97;,
  4;96,98,35,34;,
  4;99,97,97,99;,
  4;98,100,36,35;,
  4;101,99,99,101;,
  4;102,38,38,37;,
  4;103,104,104,103;,
  4;38,39,39,38;,
  4;105,103,103,105;,
  4;39,82,40,39;,
  4;106,105,105,106;,
  4;82,41,41,40;,
  4;107,106,106,107;,
  4;41,108,42,41;,
  4;109,107,107,109;,
  4;108,110,43,42;,
  4;111,109,109,111;,
  4;110,112,44,43;,
  4;113,111,111,113;,
  4;112,84,45,44;,
  4;114,113,113,114;,
  4;84,46,46,45;,
  4;115,114,114,115;,
  4;46,28,28,46;,
  4;88,115,115,88;,
  3;36,102,37;,
  3;116,56,56;,
  3;117,104,104;,
  3;116,16,17;,
  3;119,119,118;,
  3;119,120,119;;
 }
 MeshTextureCoords {
  109;
  0.496200;0.692660;,
  0.491700;0.679010;,
  0.498800;0.862440;,
  0.503480;0.875490;,
  0.641340;0.847560;,
  0.645050;0.860820;,
  0.627360;0.663450;,
  0.630990;0.677310;,
  0.500870;0.688090;,
  0.618270;0.674690;,
  0.629890;0.833360;,
  0.507370;0.846250;,
  0.657420;0.326010;,
  0.813460;0.369700;,
  0.795760;0.384270;,
  0.648260;0.343310;,
  0.928190;0.439310;,
  0.904780;0.449710;,
  0.990930;0.524150;,
  0.965060;0.529750;,
  1.000000;0.613160;,
  0.974670;0.614070;,
  0.960540;0.696940;,
  0.938070;0.693770;,
  0.881440;0.768590;,
  0.863420;0.762180;,
  0.772960;0.823600;,
  0.760350;0.814860;,
  0.645290;0.859300;,
  0.638610;0.849130;,
  0.508070;0.874340;,
  0.370430;0.868220;,
  0.376000;0.857690;,
  0.507530;0.863570;,
  0.241370;0.841130;,
  0.252840;0.831680;,
  0.130140;0.794040;,
  0.147010;0.786540;,
  0.046430;0.728990;,
  0.067830;0.724340;,
  0.000090;0.649630;,
  0.024580;0.648720;,
  0.000000;0.561820;,
  0.025470;0.565390;,
  0.052070;0.473930;,
  0.075740;0.482330;,
  0.156390;0.396510;,
  0.175080;0.409450;,
  0.391690;0.328290;,
  0.397580;0.345440;,
  0.783660;0.153450;,
  0.637300;0.108880;,
  0.487290;0.422840;,
  0.892050;0.224690;,
  0.952260;0.311880;,
  0.962280;0.403790;,
  0.926430;0.490720;,
  0.852730;0.565370;,
  0.750710;0.622890;,
  0.630030;0.660310;,
  0.499950;0.676100;,
  0.369350;0.669670;,
  0.246990;0.641260;,
  0.141820;0.591960;,
  0.063090;0.524070;,
  0.020010;0.441580;,
  0.020720;0.350720;,
  0.070370;0.260220;,
  0.168650;0.180850;,
  0.388930;0.111190;,
  0.630310;0.142620;,
  0.769380;0.184400;,
  0.487920;0.438460;,
  0.872820;0.251320;,
  0.930810;0.333480;,
  0.941140;0.420390;,
  0.907630;0.502890;,
  0.837690;0.573960;,
  0.740300;0.628860;,
  0.624740;0.664650;,
  0.500000;0.679760;,
  0.374730;0.673600;,
  0.257500;0.646420;,
  0.157020;0.599320;,
  0.082180;0.534610;,
  0.041720;0.456220;,
  0.043210;0.370170;,
  0.091270;0.284770;,
  0.185270;0.210120;,
  0.394680;0.144790;,
  0.785870;0.169520;,
  0.638790;0.125000;,
  0.894740;0.240670;,
  0.955150;0.327720;,
  0.965100;0.419450;,
  0.928980;0.506170;,
  0.854890;0.580630;,
  0.752380;0.637980;,
  0.631180;0.675290;,
  0.500560;0.691020;,
  0.369430;0.684610;,
  0.246570;0.656290;,
  0.140950;0.607140;,
  0.061840;0.539440;,
  0.018520;0.457150;,
  0.019170;0.366490;,
  0.069000;0.276150;,
  0.167740;0.196890;,
  0.389130;0.127310;;
 }
}
