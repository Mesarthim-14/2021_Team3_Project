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
 182;
 -101.58434;4.92455;201.62830;,
 -91.91051;-4.08845;38.75098;,
 -120.04465;39.68193;201.32541;,
 -120.97465;42.55968;196.49365;,
 -134.52466;43.44897;38.33849;,
 -0.46465;-26.08113;213.53912;,
 -0.46463;-40.59180;39.07569;,
 104.33855;6.55384;213.25064;,
 94.97488;-4.08845;38.75103;,
 119.10537;41.31121;212.94778;,
 120.03536;42.55968;196.49368;,
 133.58533;43.44897;38.33854;,
 -16.75467;12.15435;319.13303;,
 -0.46467;9.76406;326.11990;,
 15.82533;12.15435;319.13303;,
 15.23534;20.28700;316.08859;,
 32.00533;21.71916;304.82925;,
 21.99534;21.01910;311.72385;,
 26.06534;21.37693;308.83255;,
 42.27534;23.20919;298.62204;,
 -0.46467;15.38656;331.05185;,
 28.40534;23.08338;300.60056;,
 25.00534;22.84721;302.42416;,
 30.30533;14.31527;299.66550;,
 20.04534;22.50242;305.07480;,
 -0.46466;14.33180;302.14401;,
 16.26534;22.24232;307.10941;,
 7.57533;21.64207;311.75223;,
 -0.46467;21.08660;316.06564;,
 -7.02467;21.67678;312.75961;,
 -13.99467;22.31288;309.23807;,
 -16.87466;22.57778;307.78799;,
 -24.40466;14.35450;304.06851;,
 -20.37466;22.88551;306.02213;,
 33.72533;23.20880;299.31259;,
 41.18533;38.60096;300.57529;,
 44.31534;38.59665;299.92697;,
 -0.46467;19.40670;327.06192;,
 -0.46467;20.55992;319.56412;,
 3.80533;34.22204;327.39084;,
 3.45533;34.05423;328.73788;,
 -43.20467;23.26496;305.50314;,
 -30.38466;23.25378;304.47726;,
 -30.67467;36.63189;314.48483;,
 -32.42467;36.56702;314.80484;,
 -108.92464;47.39165;199.86951;,
 -109.17464;59.78058;215.12323;,
 -110.94463;59.77898;215.13733;,
 -82.09467;35.33727;253.38799;,
 -69.65466;35.33245;252.86780;,
 -69.75466;47.70587;266.94559;,
 -72.21467;47.70713;267.05966;,
 81.15534;35.30309;249.93954;,
 70.85534;35.30688;250.28143;,
 79.74534;50.69898;251.54414;,
 81.76534;50.70451;251.24593;,
 -101.53464;41.37423;227.32379;,
 -89.28464;41.36873;227.05984;,
 -89.29464;53.73930;241.03751;,
 -91.75464;53.73914;241.10153;,
 100.59536;41.35718;225.59955;,
 89.42536;41.35823;225.77768;,
 97.69536;56.75040;227.04028;,
 101.82536;56.75073;226.91223;,
 -62.64465;29.29401;279.44443;,
 -50.02465;29.28997;278.66824;,
 -50.53466;41.67110;292.86911;,
 -52.36466;41.66446;292.98898;,
 61.71535;29.24907;274.27951;,
 52.28535;29.26168;274.79343;,
 60.20535;44.65385;276.05606;,
 63.30534;44.65050;275.58597;,
 -111.25464;44.38883;214.29480;,
 -99.10464;44.38915;214.16672;,
 -99.35464;56.75999;228.08041;,
 -101.22463;56.76293;228.11627;,
 110.31536;44.38024;213.43268;,
 98.70536;44.38472;213.51862;,
 106.78536;59.77680;214.78128;,
 111.74536;59.77541;214.73123;,
 -91.81464;38.35966;240.35278;,
 -79.47464;38.34668;239.96704;,
 -79.64466;50.72654;253.98846;,
 -81.86466;50.72477;254.06650;,
 90.87536;38.33406;237.76648;,
 80.13536;38.33958;238.03046;,
 88.44537;53.73174;239.29303;,
 92.06536;53.72760;239.07910;,
 -72.37466;32.31643;266.40915;,
 -59.83465;32.31817;265.76883;,
 -60.41465;44.68364;279.91684;,
 -62.02465;44.68030;280.00894;,
 71.43533;32.28007;262.10641;,
 61.57535;32.28030;262.54062;,
 69.77534;47.67253;263.80331;,
 72.73534;47.67355;263.41910;,
 -52.92467;26.27949;292.47409;,
 -40.20467;26.27573;291.57010;,
 -40.45467;38.64581;305.80417;,
 -42.91467;38.65307;305.99002;,
 51.99535;26.22602;286.44662;,
 43.00535;26.23525;287.05246;,
 50.45535;41.62743;288.31583;,
 54.04534;41.61960;287.75955;,
 107.98536;47.39703;199.63528;,
 -16.17467;20.27445;316.07260;,
 -15.42467;21.90380;312.01651;,
 -11.68467;34.70452;323.53134;,
 -12.24467;34.67514;323.97641;,
 18.70533;35.34246;317.61880;,
 18.67533;35.12258;319.23782;,
 16.62534;21.88438;309.43832;,
 -29.69466;21.76660;310.78391;,
 -22.90466;22.58265;308.24399;,
 -23.02467;36.11716;317.06644;,
 -24.32467;35.44634;319.01816;,
 -8.32467;19.84063;321.56741;,
 -7.94466;21.22479;315.78970;,
 -4.25467;34.17744;327.72006;,
 -4.34467;34.10342;329.05661;,
 -22.93467;21.02361;313.43246;,
 -19.16466;22.24632;310.13406;,
 -18.09467;35.26472;320.30014;,
 -18.76467;35.21482;320.30154;,
 7.38533;19.84683;321.57529;,
 8.08533;21.22215;314.50137;,
 11.83533;34.72926;321.94003;,
 11.83533;34.64956;323.63901;,
 25.17534;22.54656;304.37540;,
 27.37534;35.90992;312.38858;,
 28.62533;36.11831;312.68265;,
 29.45534;22.87844;301.83682;,
 33.33533;36.65609;308.58774;,
 33.76534;36.61533;309.75711;,
 20.90534;22.20849;306.90591;,
 23.04533;35.58482;314.74265;,
 24.02533;35.75323;315.95053;,
 92.94536;35.28500;214.43179;,
 105.40536;45.65656;201.54358;,
 -34.60466;17.47273;290.81577;,
 -94.19464;35.67045;213.42249;,
 -103.49464;38.51374;201.33466;,
 -83.97464;32.55050;226.68857;,
 -75.09464;29.83999;238.23627;,
 -64.26466;26.53049;252.29193;,
 -54.83465;23.64773;264.53903;,
 -45.52465;20.80282;276.64084;,
 39.70535;14.52447;288.45828;,
 48.74535;20.49005;274.57687;,
 57.63535;23.47080;262.46921;,
 66.57533;26.45791;250.30530;,
 75.14536;29.33131;238.64087;,
 84.76536;32.55055;225.56403;,
 14.57538;5.69909;-11.60870;,
 -15.50462;5.69909;-11.60870;,
 7.05538;0.37026;-11.56121;,
 -0.46462;-3.72635;-11.52273;,
 -7.98462;0.37026;-11.56121;,
 -56.63461;-3.31821;24.68411;,
 -112.80461;36.51804;24.34070;,
 -0.46463;-33.90096;24.95041;,
 55.70538;-3.31821;24.68411;,
 111.87538;36.51804;24.34070;,
 -42.01462;-2.23490;10.36771;,
 -83.56462;27.22944;10.10929;,
 -0.46463;-24.86827;10.57166;,
 41.08538;-2.23490;10.36771;,
 82.63538;27.22944;10.10929;,
 -20.00462;-0.51752;-0.08349;,
 -39.54462;13.33850;-0.20559;,
 -0.46462;-11.15330;0.00718;,
 19.06538;-0.51752;-0.08349;,
 38.60538;13.33850;-0.20559;,
 107.98536;47.41122;201.25955;,
 120.03536;42.55968;196.49368;,
 102.56536;38.51374;201.33469;,
 -111.87463;41.69850;200.61578;,
 -1.58465;44.99605;199.28348;,
 -108.92464;47.41122;201.25952;,
 -120.97465;42.55968;196.49365;,
 -117.85461;44.93082;37.88818;,
 116.91538;44.28872;37.96456;;
 
 269;
 3;2,1,0;,
 3;3,1,2;,
 3;3,4,1;,
 4;1,6,5,0;,
 4;6,8,7,5;,
 3;8,9,7;,
 3;8,10,9;,
 3;8,11,10;,
 3;2,0,12;,
 4;12,0,5,13;,
 4;13,5,7,14;,
 3;7,9,14;,
 3;16,15,14;,
 3;16,17,15;,
 3;16,18,17;,
 3;14,19,16;,
 3;13,14,20;,
 3;13,20,12;,
 3;23,22,21;,
 3;23,24,22;,
 3;25,24,23;,
 3;25,26,24;,
 3;25,27,26;,
 3;25,28,27;,
 3;25,29,28;,
 3;25,30,29;,
 3;25,31,30;,
 3;32,31,25;,
 3;32,33,31;,
 4;19,36,35,34;,
 4;40,39,38,37;,
 4;44,43,42,41;,
 4;47,46,45,3;,
 4;51,50,49,48;,
 4;55,54,53,52;,
 4;59,58,57,56;,
 4;63,62,61,60;,
 4;67,66,65,64;,
 4;71,70,69,68;,
 4;75,74,73,72;,
 4;79,78,77,76;,
 4;83,82,81,80;,
 4;87,86,85,84;,
 4;91,90,89,88;,
 4;95,94,93,92;,
 4;99,98,97,96;,
 4;103,102,101,100;,
 4;72,73,46,47;,
 4;10,104,78,79;,
 4;56,57,74,75;,
 4;76,77,62,63;,
 4;80,81,58,59;,
 4;60,61,86,87;,
 4;48,49,82,83;,
 4;84,85,54,55;,
 4;88,89,50,51;,
 4;52,53,94,95;,
 4;64,65,90,91;,
 4;92,93,70,71;,
 4;96,97,66,67;,
 4;68,69,102,103;,
 4;41,42,98,99;,
 4;100,101,35,36;,
 4;108,107,106,105;,
 4;111,15,110,109;,
 4;115,114,113,112;,
 4;119,118,117,116;,
 4;123,122,121,120;,
 4;112,113,43,44;,
 4;116,117,107,108;,
 4;37,38,118,119;,
 3;12,112,41;,
 3;12,120,112;,
 3;12,105,120;,
 4;127,126,125,124;,
 4;15,111,126,127;,
 4;124,125,39,40;,
 4;130,129,128,18;,
 4;133,132,131,16;,
 4;19,34,132,133;,
 4;136,135,134,17;,
 4;134,109,110,17;,
 4;105,106,122,123;,
 4;120,121,114,115;,
 4;16,131,129,130;,
 4;18,128,135,136;,
 3;104,77,78;,
 3;104,137,77;,
 3;104,138,137;,
 3;34,131,132;,
 3;23,131,34;,
 3;23,21,131;,
 3;38,117,118;,
 3;28,117,38;,
 3;28,29,117;,
 3;139,42,32;,
 3;139,98,42;,
 3;139,97,98;,
 3;141,73,140;,
 3;141,46,73;,
 3;141,45,46;,
 3;140,57,142;,
 3;140,74,57;,
 3;140,73,74;,
 3;143,58,81;,
 3;142,58,143;,
 3;142,57,58;,
 3;143,49,144;,
 3;143,82,49;,
 3;143,81,82;,
 3;144,89,145;,
 3;144,50,89;,
 3;144,49,50;,
 3;146,90,65;,
 3;145,90,146;,
 3;145,89,90;,
 3;146,97,139;,
 3;146,66,97;,
 3;146,65,66;,
 3;113,42,43;,
 3;32,113,33;,
 3;32,42,113;,
 3;121,113,114;,
 3;31,113,121;,
 3;31,33,113;,
 3;106,121,122;,
 3;30,121,106;,
 3;30,31,121;,
 3;117,106,107;,
 3;29,106,117;,
 3;29,30,106;,
 3;125,38,39;,
 3;125,28,38;,
 3;125,27,28;,
 3;111,125,126;,
 3;111,27,125;,
 3;111,26,27;,
 3;134,111,109;,
 3;134,26,111;,
 3;134,24,26;,
 3;128,134,135;,
 3;128,24,134;,
 3;128,22,24;,
 3;131,128,129;,
 3;131,22,128;,
 3;131,21,22;,
 3;101,34,35;,
 3;147,34,101;,
 3;147,23,34;,
 3;69,101,102;,
 3;148,101,69;,
 3;148,147,101;,
 3;93,69,70;,
 3;149,69,93;,
 3;149,148,69;,
 3;53,93,94;,
 3;150,93,53;,
 3;150,149,93;,
 3;85,53,54;,
 3;151,53,85;,
 3;151,150,53;,
 3;61,85,86;,
 3;152,85,61;,
 3;152,151,85;,
 3;77,61,62;,
 3;137,61,77;,
 3;137,152,61;,
 3;47,3,72;,
 3;75,72,56;,
 3;59,56,80;,
 3;83,80,48;,
 3;51,48,88;,
 3;91,88,64;,
 3;67,64,96;,
 3;99,96,41;,
 3;44,41,112;,
 3;115,112,120;,
 3;105,123,120;,
 3;116,108,105;,
 3;119,116,37;,
 3;124,40,37;,
 3;127,124,15;,
 3;110,15,17;,
 3;136,17,18;,
 3;130,18,16;,
 3;133,16,19;,
 3;100,36,19;,
 3;103,100,68;,
 3;71,68,92;,
 3;95,92,52;,
 3;55,52,84;,
 3;87,84,60;,
 3;63,60,76;,
 3;79,76,10;,
 3;2,72,3;,
 3;12,72,2;,
 3;12,56,72;,
 3;12,80,56;,
 3;12,48,80;,
 3;12,88,48;,
 3;12,64,88;,
 3;12,96,64;,
 3;12,41,96;,
 3;20,105,12;,
 3;20,116,105;,
 3;20,37,116;,
 3;14,37,20;,
 3;14,124,37;,
 3;14,15,124;,
 3;9,19,14;,
 3;9,100,19;,
 3;9,68,100;,
 3;9,92,68;,
 3;9,52,92;,
 3;9,84,52;,
 3;9,60,84;,
 3;9,76,60;,
 3;9,10,76;,
 3;155,154,153;,
 3;156,154,155;,
 3;156,157,154;,
 4;159,158,1,4;,
 4;158,160,6,1;,
 4;160,161,8,6;,
 4;161,162,11,8;,
 4;162,159,4,11;,
 4;164,163,158,159;,
 4;163,165,160,158;,
 4;165,166,161,160;,
 4;166,167,162,161;,
 4;167,164,159,162;,
 4;169,168,163,164;,
 4;168,170,165,163;,
 4;170,171,166,165;,
 4;171,172,167,166;,
 4;172,169,164,167;,
 4;154,157,168,169;,
 4;157,156,170,168;,
 4;156,155,171,170;,
 4;155,153,172,171;,
 4;153,154,169,172;,
 4;174,173,104,10;,
 4;173,175,138,104;,
 3;25,139,32;,
 3;25,146,139;,
 3;25,145,146;,
 3;23,145,25;,
 3;23,144,145;,
 3;23,143,144;,
 3;23,142,143;,
 3;23,140,142;,
 3;147,140,23;,
 3;147,141,140;,
 3;147,176,141;,
 3;147,177,176;,
 3;148,177,147;,
 3;149,177,148;,
 3;150,177,149;,
 3;151,177,150;,
 3;137,138,177;,
 3;177,152,137;,
 3;177,151,152;,
 4;176,178,45,141;,
 4;178,179,3,45;,
 4;176,180,4,3;,
 4;181,138,10,11;,
 4;138,176,3,10;,
 4;11,4,180,181;,
 4;180,176,138,181;;
 
 MeshMaterialList {
  6;
  269;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
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
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
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
  2,
  2,
  1,
  1,
  1;;
  Material {
   0.040000;0.072000;0.176000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.784000;0.064000;0.096000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
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
    "shark_eye.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "shark_skin.png";
   }
  }
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  312;
  -0.114884;0.597827;-0.793350;,
  0.560321;-0.186794;0.806938;,
  -0.003596;-0.840641;0.541580;,
  -0.504973;-0.813860;0.287463;,
  0.522734;-0.671407;0.525320;,
  -0.618688;-0.748025;0.240176;,
  -0.005843;-0.983118;0.182877;,
  0.635931;-0.723756;0.267897;,
  0.688137;0.060909;0.723020;,
  -0.786986;0.526434;0.321745;,
  -0.808376;0.448569;-0.381200;,
  -0.004943;0.947083;-0.320950;,
  0.019668;0.940848;0.338259;,
  -0.558256;0.617188;-0.554463;,
  0.140964;-0.114805;0.983336;,
  -0.779172;0.453216;-0.432997;,
  0.474941;0.540571;-0.694416;,
  0.435689;0.700181;-0.565616;,
  0.591224;0.600077;-0.538851;,
  -0.028758;0.750825;-0.659874;,
  0.089482;-0.095135;0.991435;,
  0.600353;-0.106553;0.792605;,
  0.596533;0.591103;-0.542904;,
  -0.015614;0.748894;-0.662506;,
  0.023376;-0.088796;0.995776;,
  0.584741;-0.115184;0.803001;,
  0.493627;0.628993;-0.600583;,
  -0.042981;0.752467;-0.657226;,
  0.101636;-0.104135;0.989356;,
  0.604806;-0.141022;0.783787;,
  0.602183;0.586716;-0.541424;,
  -0.009294;0.747363;-0.664351;,
  0.008686;-0.085277;0.996319;,
  0.613763;-0.119398;0.780409;,
  0.507581;0.611319;-0.607166;,
  -0.021875;0.749470;-0.661677;,
  0.041540;-0.092079;0.994885;,
  0.588498;-0.104423;0.801727;,
  0.592501;0.605221;-0.531649;,
  -0.036470;0.751860;-0.658313;,
  0.086039;-0.100000;0.991260;,
  0.600485;-0.126256;0.789606;,
  0.579617;0.616375;-0.533035;,
  -0.046842;0.753603;-0.655658;,
  0.109480;-0.108962;0.987999;,
  0.606902;-0.150739;0.780351;,
  0.548439;0.637346;-0.541299;,
  -0.066791;0.770480;-0.633955;,
  0.495485;-0.118849;0.860447;,
  0.542283;0.626363;-0.559998;,
  0.450584;-0.112639;0.885600;,
  0.574747;0.583923;-0.573324;,
  0.458588;-0.112839;0.881456;,
  0.537150;0.631490;-0.559187;,
  0.478758;-0.097061;0.872565;,
  0.530477;0.635400;-0.561124;,
  0.478412;-0.119075;0.870025;,
  0.565041;0.603805;-0.562270;,
  0.485782;-0.128779;0.864541;,
  0.525162;0.647324;-0.552427;,
  0.489545;-0.144047;0.859998;,
  0.519824;0.647831;-0.556865;,
  0.503352;-0.145836;0.851685;,
  -0.695497;0.462451;-0.549929;,
  -0.610807;0.490646;-0.621435;,
  -0.598399;0.538031;-0.593667;,
  0.518219;0.203559;0.830670;,
  -0.959081;0.282187;-0.023112;,
  -0.664932;0.579954;0.470657;,
  -0.957923;0.286741;-0.012736;,
  0.168748;0.580761;-0.796392;,
  -0.375851;0.578907;-0.723604;,
  0.532688;-0.427514;0.730394;,
  0.155363;0.596158;-0.787691;,
  0.360660;0.717068;0.596437;,
  -0.869066;-0.046542;0.492501;,
  -0.956973;0.277684;-0.084229;,
  -0.704214;-0.108217;0.701692;,
  -0.690506;0.497510;-0.525057;,
  -0.794150;0.451933;-0.406302;,
  -0.896305;-0.027120;0.442608;,
  -0.798755;0.412212;-0.438260;,
  -0.970827;0.230479;-0.066135;,
  0.022893;0.608349;-0.793339;,
  -0.035319;0.957328;0.286837;,
  -0.475587;0.188000;-0.859344;,
  0.009256;0.999075;-0.041986;,
  0.425743;0.356880;-0.831492;,
  0.768033;0.471897;-0.432941;,
  0.751619;0.478534;-0.453953;,
  0.752924;0.481661;-0.448452;,
  0.730042;0.486770;-0.479682;,
  0.743888;0.494211;-0.449873;,
  0.747144;0.503206;-0.434234;,
  0.721954;0.508063;-0.469738;,
  0.736611;0.511984;-0.441901;,
  0.449873;-0.008006;-0.893056;,
  0.252851;0.498173;-0.829392;,
  0.130614;0.988249;-0.079393;,
  0.130029;0.988266;-0.080139;,
  -0.112411;0.990251;-0.082265;,
  -0.111491;0.990442;-0.081203;,
  -0.307554;0.500817;-0.809069;,
  -0.471555;-0.007811;-0.881802;,
  -0.472195;-0.008321;-0.881455;,
  -0.804889;0.201940;-0.558009;,
  -0.817439;0.284126;-0.501065;,
  -0.791449;0.349214;-0.501654;,
  -0.786992;0.371479;-0.492591;,
  -0.782125;0.392528;-0.483944;,
  -0.776486;0.414202;-0.474875;,
  -0.775558;0.437768;-0.454828;,
  -0.913149;-0.240538;0.329090;,
  0.000000;-0.659433;0.751764;,
  0.822397;-0.505083;0.261829;,
  -0.685707;-0.689347;-0.233682;,
  -0.475740;-0.599831;-0.643330;,
  -0.950197;-0.183992;0.251542;,
  -0.004817;-0.958783;-0.284099;,
  0.689430;-0.686979;-0.229668;,
  0.875231;-0.439244;0.202573;,
  0.487873;-0.573744;-0.657873;,
  -0.432910;-0.684130;-0.586988;,
  -0.472461;-0.596444;-0.648872;,
  -0.002163;-0.824726;-0.565528;,
  0.430074;-0.674909;-0.599612;,
  0.469964;-0.579468;-0.665845;,
  -0.395260;-0.642143;-0.656828;,
  -0.419193;-0.597108;-0.683915;,
  0.000004;-0.737317;-0.675547;,
  0.395244;-0.642087;-0.656892;,
  0.419154;-0.597054;-0.683986;,
  -0.393264;-0.639143;-0.660938;,
  -0.416850;-0.594033;-0.688012;,
  0.000035;-0.733693;-0.679481;,
  0.393313;-0.639142;-0.660911;,
  0.416881;-0.594076;-0.687957;,
  -0.334863;-0.545431;-0.768357;,
  -0.130778;-0.193208;-0.972403;,
  0.000529;-0.008277;-0.999966;,
  0.178046;-0.259784;-0.949111;,
  0.271274;-0.390511;-0.879723;,
  -0.370708;-0.928714;0.008114;,
  0.304436;-0.571039;-0.762386;,
  -0.179876;-0.944377;0.275312;,
  -0.635180;0.232584;-0.736513;,
  0.368992;-0.929340;0.013089;,
  -0.004251;0.999935;0.010557;,
  0.061300;0.998093;0.007234;,
  0.507230;0.418546;0.753350;,
  0.454460;-0.665356;0.592255;,
  -0.035974;0.943348;-0.329848;,
  0.009265;-0.054991;0.998444;,
  -0.672645;0.026043;0.739507;,
  0.063161;0.763961;-0.642164;,
  -0.407954;0.684259;-0.604453;,
  0.187955;0.962756;-0.194356;,
  -0.440442;-0.037404;0.897001;,
  0.020277;-0.051973;0.998443;,
  -0.586747;-0.034111;0.809051;,
  -0.012870;0.736162;-0.676683;,
  -0.426172;0.650797;-0.628363;,
  -0.661166;0.536196;-0.524741;,
  0.177375;0.928815;-0.325331;,
  -0.437486;-0.042257;0.898232;,
  0.028572;-0.049131;0.998384;,
  -0.584818;-0.033031;0.810492;,
  -0.024951;0.734535;-0.678112;,
  -0.430968;0.648710;-0.627249;,
  -0.676652;0.510019;-0.531058;,
  -0.432349;-0.033540;0.901082;,
  0.038424;-0.045068;0.998245;,
  -0.581980;-0.028267;0.812711;,
  -0.058929;0.732561;-0.678146;,
  -0.441323;0.654024;-0.614399;,
  -0.681949;0.501717;-0.532189;,
  -0.427697;-0.033946;0.903285;,
  0.048606;-0.043059;0.997890;,
  -0.578217;-0.018463;0.815674;,
  -0.055244;0.730971;-0.680168;,
  -0.445850;0.640485;-0.625298;,
  -0.685562;0.490269;-0.538183;,
  -0.420783;-0.016447;0.907012;,
  0.059239;-0.039203;0.997474;,
  -0.574438;-0.007408;0.818515;,
  -0.066095;0.728410;-0.681946;,
  -0.452841;0.631913;-0.628984;,
  -0.691792;0.471804;-0.546649;,
  -0.416947;-0.015421;0.908800;,
  0.068142;-0.036169;0.997020;,
  -0.573105;-0.011533;0.819401;,
  -0.070069;0.726834;-0.683229;,
  -0.458927;0.621249;-0.635166;,
  -0.697126;0.454337;-0.554610;,
  -0.413723;-0.021207;0.910156;,
  0.077445;-0.033348;0.996439;,
  -0.386882;0.003157;0.922124;,
  -0.092722;0.722924;-0.684677;,
  -0.468898;0.616295;-0.632704;,
  -0.722869;0.393070;-0.568293;,
  -0.053371;-0.276522;0.959525;,
  0.275064;-0.215156;0.937042;,
  -0.238296;-0.039181;0.970402;,
  0.863982;0.131068;0.486166;,
  0.967597;0.245677;0.058299;,
  0.735349;0.260079;0.625796;,
  -0.383686;0.349463;0.854787;,
  -0.363499;0.008109;0.931560;,
  -0.493414;0.158712;0.855192;,
  0.860927;-0.054520;0.505799;,
  0.975972;0.180029;0.122753;,
  0.839455;-0.044571;0.541598;,
  0.966769;0.160147;0.199274;,
  0.685276;0.066041;0.725283;,
  0.372809;0.699609;-0.609557;,
  -0.054656;0.662827;-0.746775;,
  -0.551283;0.411653;-0.725692;,
  0.968670;0.243202;-0.050304;,
  0.643400;-0.130333;0.754354;,
  0.768561;-0.145420;0.623030;,
  0.468757;0.529552;-0.706995;,
  0.000573;0.588258;-0.808673;,
  -0.273626;0.472357;-0.837859;,
  0.857773;0.341967;-0.383776;,
  -0.068720;0.885575;0.459385;,
  -0.238532;0.856155;0.458369;,
  0.760284;0.229554;-0.607678;,
  0.414754;0.549723;-0.725109;,
  0.416549;0.543302;-0.728910;,
  0.012167;0.988784;0.148859;,
  0.012922;0.988519;0.150541;,
  0.431595;0.464375;-0.773357;,
  -0.621278;0.441706;-0.647232;,
  0.426669;0.496528;-0.755919;,
  0.013263;0.988227;0.152417;,
  0.012145;0.988604;0.150047;,
  0.012700;0.988443;0.151060;,
  0.012026;0.988842;0.148481;,
  0.418092;0.537214;-0.732530;,
  0.013421;0.988272;0.152114;,
  0.418319;0.536848;-0.732669;,
  0.011572;0.988788;0.148877;,
  0.012426;0.988669;0.149600;,
  -0.468158;0.505991;-0.724432;,
  0.013329;0.988354;0.151588;,
  0.012774;0.988288;0.152063;,
  -0.470258;0.500919;-0.726593;,
  -0.469007;0.505422;-0.724279;,
  0.012487;0.988341;0.151744;,
  0.012778;0.988349;0.151668;,
  0.013109;0.988312;0.151882;,
  0.013205;0.988200;0.152602;,
  -0.877278;-0.008601;0.479906;,
  -0.374083;-0.366055;0.852095;,
  -0.375432;-0.312111;0.872719;,
  -0.561480;-0.275104;0.780422;,
  -0.562455;-0.265254;0.783125;,
  -0.563371;-0.255377;0.785745;,
  0.540837;-0.292790;0.788523;,
  0.557638;-0.298718;0.774472;,
  0.570076;-0.298159;0.765581;,
  0.545069;-0.299206;0.783183;,
  0.523442;-0.322719;0.788581;,
  -0.436705;-0.891634;0.119491;,
  -0.436711;-0.891630;0.119498;,
  -0.435626;-0.892329;0.118232;,
  -0.434893;-0.892797;0.117396;,
  -0.435372;-0.892485;0.117993;,
  -0.435727;-0.892245;0.118491;,
  -0.435965;-0.892083;0.118837;,
  -0.435969;-0.892080;0.118844;,
  -0.485372;0.542025;0.686019;,
  0.550310;0.588175;0.592629;,
  0.309667;0.835349;0.454200;,
  0.312155;0.833402;0.456071;,
  0.319499;0.851728;0.415308;,
  0.315524;0.830727;0.458626;,
  0.315723;0.830581;0.458752;,
  0.315547;0.830709;0.458643;,
  0.315727;0.830577;0.458756;,
  0.315395;0.830891;0.458416;,
  0.315394;0.830893;0.458414;,
  0.067001;0.972216;-0.224290;,
  -0.000371;0.975369;-0.220581;,
  0.000000;0.868312;-0.496018;,
  0.000000;0.728158;-0.685410;,
  0.000000;0.724030;-0.689769;,
  0.000056;-0.840684;-0.541526;,
  0.414347;-0.765139;-0.492828;,
  0.000000;0.830793;-0.556582;,
  -0.186043;-0.977468;0.099718;,
  0.018262;0.976299;0.215657;,
  0.018345;0.976349;0.215422;,
  0.018342;0.976369;0.215331;,
  0.018020;0.976269;0.215810;,
  0.031632;0.979890;0.197015;,
  0.017859;0.976216;0.216065;,
  0.018200;0.976331;0.215516;,
  0.018299;0.976373;0.215317;,
  0.054195;0.983707;0.171414;,
  0.011690;0.968727;0.247855;,
  0.044962;0.979607;0.195830;,
  -0.358774;-0.864668;0.351611;,
  -0.011019;0.992765;0.119565;,
  -0.009761;0.948918;0.315372;,
  0.054408;0.959639;0.275923;,
  0.054397;0.959618;0.275996;,
  0.054239;0.959574;0.276179;,
  0.054333;0.959641;0.275929;,
  0.191959;-0.976079;0.102084;,
  0.006969;-0.982364;0.186849;,
  -0.000236;-0.347092;-0.937831;;
  269;
  3;112,115,5;,
  3;117,115,112;,
  3;117,116,115;,
  4;115,118,6,5;,
  4;118,119,7,6;,
  3;119,114,7;,
  3;119,120,114;,
  3;119,121,120;,
  3;112,5,3;,
  4;3,5,6,2;,
  4;2,6,7,4;,
  3;7,114,4;,
  3;66,8,149;,
  3;150,72,150;,
  3;66,74,74;,
  3;149,1,66;,
  3;2,4,113;,
  3;2,113,3;,
  3;85,103,104;,
  3;85,102,103;,
  3;11,102,85;,
  3;11,101,102;,
  3;11,100,101;,
  3;11,86,100;,
  3;11,99,86;,
  3;11,98,99;,
  3;11,97,98;,
  3;87,97,11;,
  3;87,96,97;,
  4;1,62,14,14;,
  4;76,15,15,9;,
  4;0,73,16,0;,
  4;47,46,17,151;,
  4;19,55,18,19;,
  4;54,20,20,21;,
  4;23,51,22,23;,
  4;50,24,24,25;,
  4;27,59,26,27;,
  4;58,28,28,29;,
  4;31,49,30,31;,
  4;48,32,32,33;,
  4;35,53,34,35;,
  4;52,36,36,37;,
  4;39,57,38,39;,
  4;56,40,40,41;,
  4;43,61,42,43;,
  4;60,44,44,45;,
  4;153,152,152,152;,
  4;156,13,155,154;,
  4;159,158,158,157;,
  4;163,162,161,160;,
  4;166,165,165,164;,
  4;167,169,168,167;,
  4;172,171,171,170;,
  4;173,175,174,173;,
  4;178,177,177,176;,
  4;179,181,180,179;,
  4;184,183,183,182;,
  4;185,187,186,185;,
  4;190,189,189,188;,
  4;191,193,192,191;,
  4;196,195,195,194;,
  4;197,199,198,197;,
  4;10,10,10,10;,
  4;63,82,82,81;,
  4;65,65,64,65;,
  4;67,67,67,68;,
  4;71,83,70,71;,
  4;202,201,201,200;,
  4;203,203,203,203;,
  4;205,204,204,204;,
  3;206,202,196;,
  3;206,207,202;,
  3;206,208,207;,
  4;69,79,78,69;,
  4;8,210,210,209;,
  4;213,212,212,211;,
  4;77,77,77,77;,
  4;75,75,75,75;,
  4;214,216,215,214;,
  4;80,80,80,80;,
  4;217,217,217,217;,
  4;218,218,218,218;,
  4;219,219,219,219;,
  4;220,222,221,220;,
  4;223,223,223,223;,
  3;13,162,155;,
  3;13,111,162;,
  3;225,84,224;,
  3;216,222,215;,
  3;85,222,216;,
  3;226,226,226;,
  3;227,228,227;,
  3;86,230,229;,
  3;86,99,230;,
  3;95,16,87;,
  3;95,61,16;,
  3;95,42,61;,
  3;88,30,89;,
  3;88,46,30;,
  3;88,17,46;,
  3;89,22,90;,
  3;89,49,22;,
  3;89,30,49;,
  3;91,51,34;,
  3;90,51,91;,
  3;90,22,51;,
  3;91,18,92;,
  3;91,53,18;,
  3;91,34,53;,
  3;92,38,93;,
  3;92,55,38;,
  3;92,18,55;,
  3;94,57,26;,
  3;93,57,94;,
  3;93,38,57;,
  3;94,42,95;,
  3;94,59,42;,
  3;94,26,59;,
  3;231,16,73;,
  3;232,64,232;,
  3;87,16,231;,
  3;70,231,233;,
  3;236,235,234;,
  3;236,237,235;,
  3;238,70,83;,
  3;98,234,239;,
  3;98,236,234;,
  3;228,238,240;,
  3;99,239,230;,
  3;99,98,239;,
  3;78,15,15;,
  3;241,86,229;,
  3;241,100,86;,
  3;63,78,79;,
  3;242,100,241;,
  3;242,101,100;,
  3;243,63,81;,
  3;244,101,242;,
  3;244,245,101;,
  3;247,243,246;,
  3;248,245,244;,
  3;248,249,245;,
  3;222,247,221;,
  3;250,249,248;,
  3;250,251,249;,
  3;199,216,198;,
  3;105,216,199;,
  3;105,85,216;,
  3;193,199,192;,
  3;106,199,193;,
  3;106,105,199;,
  3;187,193,186;,
  3;107,193,187;,
  3;107,106,193;,
  3;181,187,180;,
  3;108,187,181;,
  3;108,107,187;,
  3;175,181,174;,
  3;109,181,175;,
  3;109,108,181;,
  3;169,175,168;,
  3;110,175,169;,
  3;110,109,175;,
  3;162,169,161;,
  3;111,169,162;,
  3;111,110,169;,
  3;252,117,252;,
  3;157,153,159;,
  3;164,159,166;,
  3;170,166,172;,
  3;176,172,178;,
  3;182,178,184;,
  3;188,184,190;,
  3;194,190,196;,
  3;200,196,202;,
  3;253,202,207;,
  3;208,254,207;,
  3;256,255,208;,
  3;257,256,257;,
  3;213,211,205;,
  3;209,213,8;,
  3;258,8,72;,
  3;260,72,259;,
  3;261,259,66;,
  3;262,66,1;,
  3;45,62,1;,
  3;60,45,29;,
  3;58,29,41;,
  3;56,41,21;,
  3;54,21,37;,
  3;52,37,25;,
  3;50,25,33;,
  3;48,33,120;,
  3;112,153,117;,
  3;3,153,112;,
  3;3,264,263;,
  3;3,265,264;,
  3;3,266,265;,
  3;3,267,266;,
  3;3,268,267;,
  3;3,269,268;,
  3;3,270,269;,
  3;271,208,206;,
  3;271,68,208;,
  3;271,9,68;,
  3;149,205,272;,
  3;149,213,205;,
  3;149,8,213;,
  3;114,1,4;,
  3;275,274,273;,
  3;275,276,274;,
  3;275,277,276;,
  3;275,278,277;,
  3;275,279,278;,
  3;275,280,279;,
  3;275,281,280;,
  3;275,156,163;,
  3;140,138,141;,
  3;139,138,140;,
  3;139,137,138;,
  4;123,122,115,116;,
  4;122,124,118,115;,
  4;124,125,119,118;,
  4;125,126,121,119;,
  4;284,284,283,282;,
  4;128,127,122,123;,
  4;127,129,124,122;,
  4;129,130,125,124;,
  4;130,131,126,125;,
  4;285,285,284,284;,
  4;133,132,127,128;,
  4;132,134,129,127;,
  4;134,135,130,129;,
  4;135,136,131,130;,
  4;286,286,285,285;,
  4;138,137,132,133;,
  4;137,287,134,132;,
  4;287,288,135,134;,
  4;140,141,136,135;,
  4;289,289,286,286;,
  4;142,142,142,290;,
  4;143,143,143,143;,
  3;11,292,291;,
  3;11,293,292;,
  3;11,294,293;,
  3;295,294,11;,
  3;295,296,294;,
  3;295,297,296;,
  3;295,298,297;,
  3;295,299,298;,
  3;300,299,295;,
  3;300,301,299;,
  3;302,144,302;,
  3;300,12,303;,
  3;304,12,300;,
  3;305,12,304;,
  3;306,12,305;,
  3;307,12,306;,
  3;224,84,12;,
  3;12,308,224;,
  3;12,307,308;,
  4;145,145,145,145;,
  4;146,146,309,146;,
  4;303,147,283,151;,
  4;148,84,156,282;,
  4;310,144,309,290;,
  4;121,116,311,311;,
  4;147,303,84,148;;
 }
 MeshTextureCoords {
  182;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}