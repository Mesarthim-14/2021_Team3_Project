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
 275;
 0.00000;3757.39288;17.98500;,
 0.00000;3703.13812;-775.17899;,
 213.99300;3703.13812;-745.76599;,
 412.11498;3703.13812;-659.71001;,
 579.67300;3703.13812;-523.39100;,
 704.23798;3703.13812;-346.92200;,
 776.57402;3703.13812;-143.38900;,
 791.31500;3703.13812;72.11300;,
 747.36702;3703.13812;283.59900;,
 647.99103;3703.13812;475.38700;,
 500.55599;3703.13812;633.25100;,
 315.99800;3703.13812;745.48401;,
 108.00300;3703.13812;803.76198;,
 -108.00200;3703.13812;803.76198;,
 -315.99701;3703.13812;745.48401;,
 -500.55599;3703.13812;633.25199;,
 -647.99103;3703.13812;475.38700;,
 -747.36702;3703.13812;283.60001;,
 -791.31500;3703.13812;72.11300;,
 -776.57402;3703.13812;-143.38800;,
 -704.23897;3703.13812;-346.92101;,
 -579.67300;3703.13812;-523.39100;,
 -412.11601;3703.13812;-659.70901;,
 -213.99401;3703.13812;-745.76599;,
 0.00000;3541.38489;-1553.56705;,
 424.00002;3541.38489;-1495.29099;,
 213.99300;3703.13812;-745.76599;,
 424.00002;3541.38489;-1495.29099;,
 816.55403;3541.38489;-1324.77997;,
 412.11498;3703.13812;-659.71001;,
 1148.54698;3541.38489;-1054.68300;,
 579.67300;3703.13812;-523.39100;,
 1395.35904;3541.38489;-705.03098;,
 704.23798;3703.13812;-346.92200;,
 1538.68195;3541.38489;-301.75699;,
 776.57402;3703.13812;-143.38900;,
 1567.88895;3541.38489;125.23200;,
 791.31500;3703.13812;72.11300;,
 1480.81299;3541.38489;544.26601;,
 747.36702;3703.13812;283.59900;,
 1283.91205;3541.38489;924.26903;,
 647.99103;3703.13812;475.38700;,
 991.78802;3541.38489;1237.05597;,
 500.55599;3703.13812;633.25100;,
 626.10901;3541.38489;1459.43100;,
 315.99800;3703.13812;745.48401;,
 213.99401;3541.38489;1574.90005;,
 108.00300;3703.13812;803.76198;,
 -213.99200;3541.38489;1574.90097;,
 -626.10802;3541.38489;1459.43100;,
 -991.78703;3541.38489;1237.05704;,
 -1283.91098;3541.38489;924.26903;,
 -1480.81207;3541.38489;544.26701;,
 -1567.88895;3541.38489;125.23300;,
 -1538.68301;3541.38489;-301.75600;,
 -1395.35904;3541.38489;-705.03098;,
 -1148.54797;3541.38489;-1054.68300;,
 -816.55502;3541.38489;-1324.77905;,
 -424.00101;3541.38489;-1495.29007;,
 0.00000;3275.15289;-2302.68097;,
 626.10802;3275.15289;-2216.62399;,
 626.10802;3275.15289;-2216.62399;,
 1205.78102;3275.15289;-1964.83704;,
 1696.02707;3275.15289;-1565.99304;,
 2060.48599;3275.15289;-1049.67201;,
 2272.12708;3275.15289;-454.16801;,
 2315.25696;3275.15289;176.35300;,
 2186.67404;3275.15289;795.12901;,
 1895.91507;3275.15289;1356.26801;,
 1464.54498;3275.15289;1818.15201;,
 924.55704;3275.15289;2146.52695;,
 315.99800;3275.15289;2317.03796;,
 -315.99600;3275.15289;2317.03796;,
 -924.55498;3275.15289;2146.52695;,
 -1464.54300;3275.15289;1818.15308;,
 -1895.91400;3275.15289;1356.26907;,
 -2186.67297;3275.15289;795.13000;,
 -2315.25696;3275.15289;176.35401;,
 -2272.12708;3275.15289;-454.16698;,
 -2060.48599;3275.15289;-1049.67102;,
 -1696.02798;3275.15289;-1565.99106;,
 -1205.78201;3275.15289;-1964.83704;,
 -626.11000;3275.15289;-2216.62399;,
 0.00000;2909.39301;-3008.56415;,
 816.55403;2909.39301;-2896.33209;,
 816.55403;2909.39301;-2896.33209;,
 1572.54700;2909.39301;-2567.95807;,
 2211.91193;2909.39301;-2047.79495;,
 2687.22992;2909.39301;-1374.42505;,
 2963.24707;2909.39301;-597.78500;,
 3019.49402;2909.39301;224.52400;,
 2851.79993;2909.39301;1031.51497;,
 2472.60101;2909.39301;1763.33603;,
 1910.01999;2909.39301;2365.71396;,
 1205.78201;2909.39301;2793.97186;,
 412.11601;2909.39301;3016.34613;,
 -412.11399;2909.39301;3016.34613;,
 -1205.77904;2909.39301;2793.97308;,
 -1910.01801;2909.39301;2365.71503;,
 -2472.60101;2909.39301;1763.33801;,
 -2851.79993;2909.39301;1031.51703;,
 -3019.49402;2909.39301;224.52600;,
 -2963.24799;2909.39301;-597.78301;,
 -2687.22992;2909.39301;-1374.42307;,
 -2211.91299;2909.39301;-2047.79495;,
 -1572.54898;2909.39301;-2567.95685;,
 -816.55502;2909.39301;-2896.33209;,
 0.00000;2450.92499;-3658.07190;,
 991.78802;2450.92499;-3521.75110;,
 991.78802;2450.92499;-3521.75110;,
 1910.01999;2450.92499;-3122.90802;,
 2686.59393;2450.92499;-2491.11694;,
 3263.91510;2450.92499;-1673.24005;,
 3599.16809;2450.92499;-729.92996;,
 3667.48596;2450.92499;268.84800;,
 3463.80493;2450.92499;1249.02100;,
 3003.22601;2450.92499;2137.89398;,
 2319.91501;2450.92499;2869.54315;,
 1464.54605;2450.92499;3389.70490;,
 500.55801;2450.92499;3659.80286;,
 -500.55500;2450.92499;3659.80286;,
 -1464.54300;2450.92499;3389.70612;,
 -2319.91302;2450.92499;2869.54407;,
 -3003.22601;2450.92499;2137.89597;,
 -3463.80402;2450.92499;1249.02298;,
 -3667.48596;2450.92499;268.85000;,
 -3599.16809;2450.92499;-729.92897;,
 -3263.91510;2450.92499;-1673.23807;,
 -2686.59485;2450.92499;-2491.11603;,
 -1910.02197;2450.92499;-3122.90710;,
 -991.79100;2450.92499;-3521.75110;,
 0.00000;1908.28094;-4239.09698;,
 1148.54698;1908.28094;-4081.23199;,
 1148.54698;1908.28094;-4081.23199;,
 2211.91193;1908.28094;-3619.34906;,
 3111.22894;1908.28094;-2887.69989;,
 3779.80103;1908.28094;-1940.54901;,
 4168.04291;1908.28094;-848.14400;,
 4247.15790;1908.28094;308.49800;,
 4011.28204;1908.28094;1443.59497;,
 3477.90985;1908.28094;2472.96005;,
 2686.59485;1908.28094;3320.25085;,
 1696.02798;1908.28094;3922.62909;,
 579.67400;1908.28094;4235.41687;,
 -579.67098;1908.28094;4235.41687;,
 -1696.02402;1908.28094;3922.63092;,
 -2686.59088;1908.28094;3320.25208;,
 -3477.90710;1908.28094;2472.96295;,
 -4011.28113;1908.28094;1443.59695;,
 -4247.15790;1908.28094;308.50100;,
 -4168.04291;1908.28094;-848.14201;,
 -3779.80286;1908.28094;-1940.54703;,
 -3111.22986;1908.28094;-2887.69806;,
 -2211.91406;1908.28094;-3619.34814;,
 -1148.55003;1908.28094;-4081.23108;,
 0.00000;1291.57700;-4740.82306;,
 1283.91098;1291.57700;-4564.35303;,
 1283.91098;1291.57700;-4564.35303;,
 2472.60101;1291.57700;-4048.03314;,
 3477.90894;1291.57700;-3230.15503;,
 4225.27588;1291.57700;-2171.37604;,
 4659.27185;1291.57700;-950.22301;,
 4747.71515;1291.57700;342.73701;,
 4484.03900;1291.57700;1611.61301;,
 3887.80396;1291.57700;2762.29492;,
 3003.22693;1291.57700;3709.44611;,
 1895.91507;1291.57700;4382.81799;,
 647.99301;1291.57700;4732.46887;,
 -647.98897;1291.57700;4732.47009;,
 -1895.91293;1291.57700;4382.81799;,
 -3003.22510;1291.57700;3709.44794;,
 -3887.80304;1291.57700;2762.29889;,
 -4484.03900;1291.57700;1611.61499;,
 -4747.71515;1291.57700;342.73998;,
 -4659.27399;1291.57700;-950.22102;,
 -4225.27710;1291.57700;-2171.37405;,
 -3477.91107;1291.57700;-3230.15289;,
 -2472.60300;1291.57700;-4048.03192;,
 -1283.91403;1291.57700;-4564.35211;,
 0.00000;612.30000;-5153.90198;,
 1395.35904;612.30000;-4962.11304;,
 1395.35904;612.30000;-4962.11304;,
 2687.22992;612.30000;-4400.97504;,
 3779.80103;612.30000;-3512.10205;,
 4592.04193;612.30000;-2361.41907;,
 5063.71185;612.30000;-1034.26697;,
 5159.82788;612.30000;370.92701;,
 4873.26691;612.30000;1749.94400;,
 4225.27588;612.30000;3000.51086;,
 3263.91510;612.30000;4029.87488;,
 2060.48599;612.30000;4761.69800;,
 704.24004;612.30000;5141.70105;,
 -704.23599;612.30000;5141.70105;,
 -2060.48294;612.30000;4761.70013;,
 -3263.91296;612.30000;4029.87610;,
 -4225.27496;612.30000;3000.51300;,
 -4873.26599;612.30000;1749.94705;,
 -5159.82788;612.30000;370.92999;,
 -5063.71307;612.30000;-1034.26300;,
 -4592.04498;612.30000;-2361.41602;,
 -3779.80408;612.30000;-3512.09808;,
 -2687.23297;612.30000;-4400.97504;,
 -1395.36194;612.30000;-4962.11304;,
 0.00000;-116.89900;-5470.63721;,
 1480.81207;-116.89900;-5267.10388;,
 1480.81207;-116.89900;-5267.10388;,
 2851.79993;-116.89900;-4671.60187;,
 4011.28204;-116.89900;-3728.29193;,
 4873.26691;-116.89900;-2507.13806;,
 5373.82202;-116.89900;-1098.70796;,
 5475.82886;-116.89900;392.54200;,
 5171.71509;-116.89900;1856.01196;,
 4484.03992;-116.89900;3183.16589;,
 3463.80493;-116.89900;4275.57098;,
 2186.67404;-116.89900;5052.21191;,
 747.36900;-116.89900;5455.48584;,
 -747.36504;-116.89900;5455.48706;,
 -2186.67099;-116.89900;5052.21313;,
 -3463.80188;-116.89900;4275.57190;,
 -4484.03809;-116.89900;3183.16803;,
 -5171.71326;-116.89900;1856.01501;,
 -5475.82825;-116.89900;392.54398;,
 -5373.82324;-116.89900;-1098.70499;,
 -4873.26691;-116.89900;-2507.13501;,
 -4011.28601;-116.89900;-3728.28888;,
 -2851.80298;-116.89900;-4671.59912;,
 -1480.81696;-116.89900;-5267.10327;,
 0.00000;-882.43500;-5685.13123;,
 1538.68195;-882.43500;-5473.64380;,
 1538.68195;-882.43500;-5473.64380;,
 2963.24799;-882.43500;-4854.86908;,
 4168.04291;-882.43500;-3874.69391;,
 5063.71307;-882.43500;-2605.81909;,
 5583.82996;-882.43500;-1142.34802;,
 5689.81995;-882.43500;407.17899;,
 5373.82324;-882.43500;1927.84195;,
 4659.27490;-882.43500;3306.85913;,
 3599.16809;-882.43500;4441.95587;,
 2272.12799;-882.43500;5248.94714;,
 776.57600;-882.43500;5667.98218;,
 -776.57097;-882.43500;5667.98523;,
 -2272.12494;-882.43500;5248.95020;,
 -3599.16504;-882.43500;4441.95801;,
 -4659.27185;-882.43500;3306.86005;,
 -5373.82202;-882.43500;1927.84500;,
 -5689.81873;-882.43500;407.18201;,
 -5583.83118;-882.43500;-1142.34497;,
 -5063.71399;-882.43500;-2605.81604;,
 -4168.04504;-882.43500;-3874.69208;,
 -2963.25195;-882.43500;-4854.86511;,
 -1538.68607;-882.43500;-5473.64319;,
 0.00000;-1670.04700;-5793.38684;,
 1567.88895;-1670.04700;-5577.88208;,
 1567.88895;-1670.04700;-5577.88208;,
 3019.49402;-1670.04700;-4947.36206;,
 4247.15790;-1670.04700;-3948.58490;,
 5159.82788;-1670.04700;-2655.62286;,
 5689.81873;-1670.04700;-1164.37302;,
 5797.82288;-1670.04700;414.56699;,
 5475.82886;-1670.04700;1964.09393;,
 4747.71606;-1670.04700;3369.28711;,
 3667.48688;-1670.04700;4525.92987;,
 2315.25803;-1670.04700;5348.23792;,
 791.31699;-1670.04700;5775.22705;,
 -791.31203;-1670.04700;5775.22888;,
 -2315.25406;-1670.04700;5348.23975;,
 -3667.48413;-1670.04700;4525.93201;,
 -4747.71210;-1670.04700;3369.28986;,
 -5475.82703;-1670.04700;1964.09698;,
 -5797.82288;-1670.04700;414.57001;,
 -5689.81995;-1670.04700;-1164.36996;,
 -5159.83093;-1670.04700;-2655.62103;,
 -4247.16095;-1670.04700;-3948.58185;,
 -3019.49707;-1670.04700;-4947.36115;,
 -1567.89307;-1670.04700;-5577.88208;;
 
 253;
 3;0,1,2;,
 3;0,2,3;,
 3;0,3,4;,
 3;0,4,5;,
 3;0,5,6;,
 3;0,6,7;,
 3;0,7,8;,
 3;0,8,9;,
 3;0,9,10;,
 3;0,10,11;,
 3;0,11,12;,
 3;0,12,13;,
 3;0,13,14;,
 3;0,14,15;,
 3;0,15,16;,
 3;0,16,17;,
 3;0,17,18;,
 3;0,18,19;,
 3;0,19,20;,
 3;0,20,21;,
 3;0,21,22;,
 3;0,22,23;,
 3;0,23,1;,
 4;1,24,25,2;,
 4;26,27,28,29;,
 4;29,28,30,31;,
 4;31,30,32,33;,
 4;33,32,34,35;,
 4;35,34,36,37;,
 4;37,36,38,39;,
 4;39,38,40,41;,
 4;41,40,42,43;,
 4;43,42,44,45;,
 4;45,44,46,47;,
 4;47,46,48,13;,
 4;13,48,49,14;,
 4;14,49,50,15;,
 4;15,50,51,16;,
 4;16,51,52,17;,
 4;17,52,53,18;,
 4;18,53,54,19;,
 4;19,54,55,20;,
 4;20,55,56,21;,
 4;21,56,57,22;,
 4;22,57,58,23;,
 4;23,58,24,1;,
 4;24,59,60,25;,
 4;27,61,62,28;,
 4;28,62,63,30;,
 4;30,63,64,32;,
 4;32,64,65,34;,
 4;34,65,66,36;,
 4;36,66,67,38;,
 4;38,67,68,40;,
 4;40,68,69,42;,
 4;42,69,70,44;,
 4;44,70,71,46;,
 4;46,71,72,48;,
 4;48,72,73,49;,
 4;49,73,74,50;,
 4;50,74,75,51;,
 4;51,75,76,52;,
 4;52,76,77,53;,
 4;53,77,78,54;,
 4;54,78,79,55;,
 4;55,79,80,56;,
 4;56,80,81,57;,
 4;57,81,82,58;,
 4;58,82,59,24;,
 4;59,83,84,60;,
 4;61,85,86,62;,
 4;62,86,87,63;,
 4;63,87,88,64;,
 4;64,88,89,65;,
 4;65,89,90,66;,
 4;66,90,91,67;,
 4;67,91,92,68;,
 4;68,92,93,69;,
 4;69,93,94,70;,
 4;70,94,95,71;,
 4;71,95,96,72;,
 4;72,96,97,73;,
 4;73,97,98,74;,
 4;74,98,99,75;,
 4;75,99,100,76;,
 4;76,100,101,77;,
 4;77,101,102,78;,
 4;78,102,103,79;,
 4;79,103,104,80;,
 4;80,104,105,81;,
 4;81,105,106,82;,
 4;82,106,83,59;,
 4;83,107,108,84;,
 4;85,109,110,86;,
 4;86,110,111,87;,
 4;87,111,112,88;,
 4;88,112,113,89;,
 4;89,113,114,90;,
 4;90,114,115,91;,
 4;91,115,116,92;,
 4;92,116,117,93;,
 4;93,117,118,94;,
 4;94,118,119,95;,
 4;95,119,120,96;,
 4;96,120,121,97;,
 4;97,121,122,98;,
 4;98,122,123,99;,
 4;99,123,124,100;,
 4;100,124,125,101;,
 4;101,125,126,102;,
 4;102,126,127,103;,
 4;103,127,128,104;,
 4;104,128,129,105;,
 4;105,129,130,106;,
 4;106,130,107,83;,
 4;107,131,132,108;,
 4;109,133,134,110;,
 4;110,134,135,111;,
 4;111,135,136,112;,
 4;112,136,137,113;,
 4;113,137,138,114;,
 4;114,138,139,115;,
 4;115,139,140,116;,
 4;116,140,141,117;,
 4;117,141,142,118;,
 4;118,142,143,119;,
 4;119,143,144,120;,
 4;120,144,145,121;,
 4;121,145,146,122;,
 4;122,146,147,123;,
 4;123,147,148,124;,
 4;124,148,149,125;,
 4;125,149,150,126;,
 4;126,150,151,127;,
 4;127,151,152,128;,
 4;128,152,153,129;,
 4;129,153,154,130;,
 4;130,154,131,107;,
 4;131,155,156,132;,
 4;133,157,158,134;,
 4;134,158,159,135;,
 4;135,159,160,136;,
 4;136,160,161,137;,
 4;137,161,162,138;,
 4;138,162,163,139;,
 4;139,163,164,140;,
 4;140,164,165,141;,
 4;141,165,166,142;,
 4;142,166,167,143;,
 4;143,167,168,144;,
 4;144,168,169,145;,
 4;145,169,170,146;,
 4;146,170,171,147;,
 4;147,171,172,148;,
 4;148,172,173,149;,
 4;149,173,174,150;,
 4;150,174,175,151;,
 4;151,175,176,152;,
 4;152,176,177,153;,
 4;153,177,178,154;,
 4;154,178,155,131;,
 4;155,179,180,156;,
 4;157,181,182,158;,
 4;158,182,183,159;,
 4;159,183,184,160;,
 4;160,184,185,161;,
 4;161,185,186,162;,
 4;162,186,187,163;,
 4;163,187,188,164;,
 4;164,188,189,165;,
 4;165,189,190,166;,
 4;166,190,191,167;,
 4;167,191,192,168;,
 4;168,192,193,169;,
 4;169,193,194,170;,
 4;170,194,195,171;,
 4;171,195,196,172;,
 4;172,196,197,173;,
 4;173,197,198,174;,
 4;174,198,199,175;,
 4;175,199,200,176;,
 4;176,200,201,177;,
 4;177,201,202,178;,
 4;178,202,179,155;,
 4;179,203,204,180;,
 4;181,205,206,182;,
 4;182,206,207,183;,
 4;183,207,208,184;,
 4;184,208,209,185;,
 4;185,209,210,186;,
 4;186,210,211,187;,
 4;187,211,212,188;,
 4;188,212,213,189;,
 4;189,213,214,190;,
 4;190,214,215,191;,
 4;191,215,216,192;,
 4;192,216,217,193;,
 4;193,217,218,194;,
 4;194,218,219,195;,
 4;195,219,220,196;,
 4;196,220,221,197;,
 4;197,221,222,198;,
 4;198,222,223,199;,
 4;199,223,224,200;,
 4;200,224,225,201;,
 4;201,225,226,202;,
 4;202,226,203,179;,
 4;203,227,228,204;,
 4;205,229,230,206;,
 4;206,230,231,207;,
 4;207,231,232,208;,
 4;208,232,233,209;,
 4;209,233,234,210;,
 4;210,234,235,211;,
 4;211,235,236,212;,
 4;212,236,237,213;,
 4;213,237,238,214;,
 4;214,238,239,215;,
 4;215,239,240,216;,
 4;216,240,241,217;,
 4;217,241,242,218;,
 4;218,242,243,219;,
 4;219,243,244,220;,
 4;220,244,245,221;,
 4;221,245,246,222;,
 4;222,246,247,223;,
 4;223,247,248,224;,
 4;224,248,249,225;,
 4;225,249,250,226;,
 4;226,250,227,203;,
 4;227,251,252,228;,
 4;229,253,254,230;,
 4;230,254,255,231;,
 4;231,255,256,232;,
 4;232,256,257,233;,
 4;233,257,258,234;,
 4;234,258,259,235;,
 4;235,259,260,236;,
 4;236,260,261,237;,
 4;237,261,262,238;,
 4;238,262,263,239;,
 4;239,263,264,240;,
 4;240,264,265,241;,
 4;241,265,266,242;,
 4;242,266,267,243;,
 4;243,267,268,244;,
 4;244,268,269,245;,
 4;245,269,270,246;,
 4;246,270,271,247;,
 4;247,271,272,248;,
 4;248,272,273,249;,
 4;249,273,274,250;,
 4;250,274,251,227;;
 
 MeshMaterialList {
  1;
  253;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;1.000000;1.000000;;
   TextureFilename {
    "sky.jpg";
   }
  }
 }
 MeshNormals {
  254;
  -0.000000;-1.000000;-0.000000;,
  0.000000;-0.990687;0.136157;,
  -0.036735;-0.990687;0.131108;,
  -0.070745;-0.990687;0.116335;,
  -0.099508;-0.990687;0.092934;,
  -0.120892;-0.990687;0.062641;,
  -0.133309;-0.990687;0.027702;,
  -0.135839;-0.990687;-0.009292;,
  -0.128295;-0.990687;-0.045596;,
  -0.111236;-0.990687;-0.078519;,
  -0.085927;-0.990687;-0.105618;,
  -0.054245;-0.990687;-0.124884;,
  -0.018540;-0.990687;-0.134889;,
  0.018540;-0.990687;-0.134889;,
  0.054245;-0.990687;-0.124885;,
  0.085927;-0.990687;-0.105618;,
  0.111236;-0.990687;-0.078519;,
  0.128295;-0.990687;-0.045596;,
  0.135839;-0.990687;-0.009292;,
  0.133309;-0.990687;0.027702;,
  0.120892;-0.990687;0.062641;,
  0.099508;-0.990687;0.092934;,
  0.070745;-0.990687;0.116335;,
  0.036735;-0.990687;0.131108;,
  0.000000;-0.962924;0.269774;,
  -0.072784;-0.962924;0.259771;,
  -0.140171;-0.962924;0.230500;,
  -0.197161;-0.962924;0.184135;,
  -0.239529;-0.962924;0.124114;,
  -0.264132;-0.962924;0.054887;,
  -0.269145;-0.962924;-0.018410;,
  -0.254198;-0.962924;-0.090342;,
  -0.220397;-0.962924;-0.155574;,
  -0.170251;-0.962924;-0.209267;,
  -0.107479;-0.962924;-0.247440;,
  -0.036734;-0.962924;-0.267261;,
  0.036734;-0.962924;-0.267261;,
  0.107478;-0.962924;-0.247440;,
  0.170251;-0.962924;-0.209267;,
  0.220397;-0.962924;-0.155574;,
  0.254198;-0.962924;-0.090342;,
  0.269145;-0.962924;-0.018410;,
  0.264132;-0.962924;0.054887;,
  0.239529;-0.962924;0.124114;,
  0.197161;-0.962924;0.184135;,
  0.140171;-0.962924;0.230500;,
  0.072784;-0.962924;0.259770;,
  0.000000;-0.917225;0.398370;,
  -0.107479;-0.917225;0.383598;,
  -0.206987;-0.917225;0.340375;,
  -0.291143;-0.917225;0.271909;,
  -0.353707;-0.917225;0.183276;,
  -0.390038;-0.917225;0.081051;,
  -0.397442;-0.917225;-0.027186;,
  -0.375369;-0.917225;-0.133406;,
  -0.325457;-0.917225;-0.229732;,
  -0.251407;-0.917225;-0.309020;,
  -0.158711;-0.917225;-0.365389;,
  -0.054245;-0.917225;-0.394660;,
  0.054245;-0.917225;-0.394660;,
  0.158711;-0.917225;-0.365390;,
  0.251406;-0.917225;-0.309020;,
  0.325456;-0.917225;-0.229732;,
  0.375369;-0.917225;-0.133406;,
  0.397442;-0.917225;-0.027186;,
  0.390038;-0.917225;0.081051;,
  0.353707;-0.917225;0.183276;,
  0.291144;-0.917225;0.271909;,
  0.206987;-0.917225;0.340375;,
  0.107479;-0.917225;0.383598;,
  -0.000000;-0.854440;0.519549;,
  -0.140173;-0.854440;0.500283;,
  -0.269950;-0.854440;0.443913;,
  -0.379706;-0.854440;0.354620;,
  -0.461300;-0.854440;0.239027;,
  -0.508683;-0.854440;0.105705;,
  -0.518338;-0.854440;-0.035455;,
  -0.489551;-0.854440;-0.173987;,
  -0.424457;-0.854440;-0.299614;,
  -0.327882;-0.854440;-0.403020;,
  -0.206989;-0.854440;-0.476537;,
  -0.070745;-0.854440;-0.514710;,
  0.070745;-0.854440;-0.514710;,
  0.206989;-0.854440;-0.476537;,
  0.327881;-0.854440;-0.403021;,
  0.424456;-0.854440;-0.299614;,
  0.489551;-0.854440;-0.173987;,
  0.518338;-0.854440;-0.035455;,
  0.508683;-0.854440;0.105705;,
  0.461301;-0.854440;0.239027;,
  0.379706;-0.854440;0.354620;,
  0.269950;-0.854440;0.443913;,
  0.140173;-0.854440;0.500283;,
  -0.000000;-0.775738;0.631055;,
  -0.170257;-0.775738;0.607653;,
  -0.327886;-0.775738;0.539185;,
  -0.461197;-0.775738;0.430728;,
  -0.560304;-0.775738;0.290326;,
  -0.617855;-0.775739;0.128392;,
  -0.629583;-0.775738;-0.043065;,
  -0.594618;-0.775738;-0.211327;,
  -0.515553;-0.775738;-0.363917;,
  -0.398251;-0.775738;-0.489516;,
  -0.251413;-0.775738;-0.578810;,
  -0.085929;-0.775738;-0.625177;,
  0.085928;-0.775738;-0.625177;,
  0.251413;-0.775738;-0.578811;,
  0.398251;-0.775738;-0.489517;,
  0.515553;-0.775738;-0.363917;,
  0.594618;-0.775738;-0.211328;,
  0.629584;-0.775738;-0.043065;,
  0.617855;-0.775739;0.128392;,
  0.560304;-0.775739;0.290326;,
  0.461198;-0.775738;0.430728;,
  0.327886;-0.775738;0.539185;,
  0.170257;-0.775738;0.607653;,
  0.000000;-0.682584;0.730807;,
  -0.197169;-0.682584;0.703707;,
  -0.379715;-0.682584;0.624416;,
  -0.534100;-0.682584;0.498814;,
  -0.648873;-0.682584;0.336219;,
  -0.715522;-0.682584;0.148687;,
  -0.729104;-0.682584;-0.049872;,
  -0.688611;-0.682584;-0.244732;,
  -0.597048;-0.682584;-0.421442;,
  -0.461204;-0.682584;-0.566895;,
  -0.291155;-0.682584;-0.670305;,
  -0.099512;-0.682584;-0.724001;,
  0.099511;-0.682584;-0.724001;,
  0.291154;-0.682584;-0.670305;,
  0.461203;-0.682584;-0.566896;,
  0.597047;-0.682584;-0.421443;,
  0.688611;-0.682584;-0.244733;,
  0.729103;-0.682584;-0.049873;,
  0.715522;-0.682584;0.148687;,
  0.648873;-0.682584;0.336219;,
  0.534100;-0.682584;0.498814;,
  0.379716;-0.682584;0.624416;,
  0.197170;-0.682584;0.703707;,
  0.000000;-0.576715;0.816946;,
  -0.220409;-0.576714;0.786651;,
  -0.424472;-0.576714;0.698015;,
  -0.597054;-0.576714;0.557609;,
  -0.725355;-0.576714;0.375848;,
  -0.799859;-0.576714;0.166213;,
  -0.815042;-0.576714;-0.055750;,
  -0.769776;-0.576714;-0.273578;,
  -0.667420;-0.576714;-0.471117;,
  -0.515565;-0.576714;-0.633714;,
  -0.325472;-0.576714;-0.749312;,
  -0.111241;-0.576714;-0.809337;,
  0.111240;-0.576714;-0.809337;,
  0.325472;-0.576714;-0.749312;,
  0.515564;-0.576714;-0.633715;,
  0.667420;-0.576714;-0.471117;,
  0.769776;-0.576714;-0.273579;,
  0.815042;-0.576714;-0.055751;,
  0.799859;-0.576714;0.166212;,
  0.725354;-0.576714;0.375848;,
  0.597054;-0.576714;0.557609;,
  0.424472;-0.576714;0.698014;,
  0.220409;-0.576715;0.786651;,
  -0.000000;-0.460097;0.887869;,
  -0.239544;-0.460097;0.854944;,
  -0.461322;-0.460097;0.758612;,
  -0.648887;-0.460097;0.606018;,
  -0.788326;-0.460097;0.408477;,
  -0.869298;-0.460097;0.180642;,
  -0.885799;-0.460097;-0.060590;,
  -0.836604;-0.460097;-0.297329;,
  -0.725362;-0.460097;-0.512016;,
  -0.560323;-0.460097;-0.688730;,
  -0.353728;-0.460097;-0.814363;,
  -0.120898;-0.460097;-0.879599;,
  0.120898;-0.460097;-0.879599;,
  0.353728;-0.460097;-0.814363;,
  0.560323;-0.460097;-0.688730;,
  0.725362;-0.460096;-0.512017;,
  0.836604;-0.460096;-0.297329;,
  0.885799;-0.460097;-0.060591;,
  0.869298;-0.460097;0.180641;,
  0.788326;-0.460096;0.408477;,
  0.648887;-0.460097;0.606017;,
  0.461323;-0.460097;0.758612;,
  0.239544;-0.460097;0.854944;,
  -0.000000;-0.334906;0.942252;,
  -0.254216;-0.334906;0.907310;,
  -0.489579;-0.334906;0.805078;,
  -0.688632;-0.334906;0.643137;,
  -0.836611;-0.334906;0.433497;,
  -0.922544;-0.334906;0.191707;,
  -0.940055;-0.334906;-0.064301;,
  -0.887847;-0.334906;-0.315541;,
  -0.769791;-0.334906;-0.543378;,
  -0.594644;-0.334906;-0.730915;,
  -0.375394;-0.334905;-0.864244;,
  -0.128304;-0.334906;-0.933475;,
  0.128303;-0.334906;-0.933475;,
  0.375394;-0.334906;-0.864244;,
  0.594644;-0.334905;-0.730915;,
  0.769791;-0.334905;-0.543379;,
  0.887847;-0.334905;-0.315541;,
  0.940055;-0.334905;-0.064302;,
  0.922544;-0.334905;0.191706;,
  0.836612;-0.334905;0.433497;,
  0.688632;-0.334905;0.643136;,
  0.489579;-0.334905;0.805078;,
  0.254217;-0.334905;0.907310;,
  -0.000000;-0.203473;0.979081;,
  -0.264153;-0.203472;0.942774;,
  -0.508714;-0.203472;0.836546;,
  -0.715548;-0.203472;0.668274;,
  -0.869311;-0.203472;0.450441;,
  -0.958602;-0.203472;0.199200;,
  -0.976798;-0.203472;-0.066814;,
  -0.922549;-0.203473;-0.327874;,
  -0.799879;-0.203473;-0.564617;,
  -0.617886;-0.203473;-0.759484;,
  -0.390067;-0.203472;-0.898024;,
  -0.133319;-0.203472;-0.969961;,
  0.133317;-0.203473;-0.969962;,
  0.390067;-0.203473;-0.898024;,
  0.617886;-0.203473;-0.759484;,
  0.799879;-0.203473;-0.564617;,
  0.922549;-0.203473;-0.327875;,
  0.976798;-0.203473;-0.066815;,
  0.958602;-0.203473;0.199199;,
  0.869311;-0.203473;0.450440;,
  0.715548;-0.203473;0.668274;,
  0.508715;-0.203473;0.836545;,
  0.264153;-0.203473;0.942773;,
  -0.000000;-0.136166;0.990686;,
  -0.267284;-0.136165;0.953949;,
  -0.514744;-0.136165;0.846462;,
  -0.724029;-0.136165;0.676196;,
  -0.879616;-0.136164;0.455780;,
  -0.969965;-0.136165;0.201561;,
  -0.988376;-0.136167;-0.067606;,
  -0.933485;-0.136168;-0.331760;,
  -0.809361;-0.136167;-0.571309;,
  -0.625210;-0.136166;-0.768486;,
  -0.394691;-0.136165;-0.908668;,
  -0.134899;-0.136164;-0.981459;,
  0.134898;-0.136164;-0.981459;,
  0.394691;-0.136164;-0.908669;,
  0.625210;-0.136166;-0.768486;,
  0.809360;-0.136167;-0.571310;,
  0.933484;-0.136168;-0.331761;,
  0.988376;-0.136167;-0.067607;,
  0.969965;-0.136166;0.201560;,
  0.879616;-0.136166;0.455779;,
  0.724029;-0.136166;0.676195;,
  0.514745;-0.136166;0.846461;,
  0.267285;-0.136166;0.953948;;
  253;
  3;0,1,2;,
  3;0,2,3;,
  3;0,3,4;,
  3;0,4,5;,
  3;0,5,6;,
  3;0,6,7;,
  3;0,7,8;,
  3;0,8,9;,
  3;0,9,10;,
  3;0,10,11;,
  3;0,11,12;,
  3;0,12,13;,
  3;0,13,14;,
  3;0,14,15;,
  3;0,15,16;,
  3;0,16,17;,
  3;0,17,18;,
  3;0,18,19;,
  3;0,19,20;,
  3;0,20,21;,
  3;0,21,22;,
  3;0,22,23;,
  3;0,23,1;,
  4;1,24,25,2;,
  4;2,25,26,3;,
  4;3,26,27,4;,
  4;4,27,28,5;,
  4;5,28,29,6;,
  4;6,29,30,7;,
  4;7,30,31,8;,
  4;8,31,32,9;,
  4;9,32,33,10;,
  4;10,33,34,11;,
  4;11,34,35,12;,
  4;12,35,36,13;,
  4;13,36,37,14;,
  4;14,37,38,15;,
  4;15,38,39,16;,
  4;16,39,40,17;,
  4;17,40,41,18;,
  4;18,41,42,19;,
  4;19,42,43,20;,
  4;20,43,44,21;,
  4;21,44,45,22;,
  4;22,45,46,23;,
  4;23,46,24,1;,
  4;24,47,48,25;,
  4;25,48,49,26;,
  4;26,49,50,27;,
  4;27,50,51,28;,
  4;28,51,52,29;,
  4;29,52,53,30;,
  4;30,53,54,31;,
  4;31,54,55,32;,
  4;32,55,56,33;,
  4;33,56,57,34;,
  4;34,57,58,35;,
  4;35,58,59,36;,
  4;36,59,60,37;,
  4;37,60,61,38;,
  4;38,61,62,39;,
  4;39,62,63,40;,
  4;40,63,64,41;,
  4;41,64,65,42;,
  4;42,65,66,43;,
  4;43,66,67,44;,
  4;44,67,68,45;,
  4;45,68,69,46;,
  4;46,69,47,24;,
  4;47,70,71,48;,
  4;48,71,72,49;,
  4;49,72,73,50;,
  4;50,73,74,51;,
  4;51,74,75,52;,
  4;52,75,76,53;,
  4;53,76,77,54;,
  4;54,77,78,55;,
  4;55,78,79,56;,
  4;56,79,80,57;,
  4;57,80,81,58;,
  4;58,81,82,59;,
  4;59,82,83,60;,
  4;60,83,84,61;,
  4;61,84,85,62;,
  4;62,85,86,63;,
  4;63,86,87,64;,
  4;64,87,88,65;,
  4;65,88,89,66;,
  4;66,89,90,67;,
  4;67,90,91,68;,
  4;68,91,92,69;,
  4;69,92,70,47;,
  4;70,93,94,71;,
  4;71,94,95,72;,
  4;72,95,96,73;,
  4;73,96,97,74;,
  4;74,97,98,75;,
  4;75,98,99,76;,
  4;76,99,100,77;,
  4;77,100,101,78;,
  4;78,101,102,79;,
  4;79,102,103,80;,
  4;80,103,104,81;,
  4;81,104,105,82;,
  4;82,105,106,83;,
  4;83,106,107,84;,
  4;84,107,108,85;,
  4;85,108,109,86;,
  4;86,109,110,87;,
  4;87,110,111,88;,
  4;88,111,112,89;,
  4;89,112,113,90;,
  4;90,113,114,91;,
  4;91,114,115,92;,
  4;92,115,93,70;,
  4;93,116,117,94;,
  4;94,117,118,95;,
  4;95,118,119,96;,
  4;96,119,120,97;,
  4;97,120,121,98;,
  4;98,121,122,99;,
  4;99,122,123,100;,
  4;100,123,124,101;,
  4;101,124,125,102;,
  4;102,125,126,103;,
  4;103,126,127,104;,
  4;104,127,128,105;,
  4;105,128,129,106;,
  4;106,129,130,107;,
  4;107,130,131,108;,
  4;108,131,132,109;,
  4;109,132,133,110;,
  4;110,133,134,111;,
  4;111,134,135,112;,
  4;112,135,136,113;,
  4;113,136,137,114;,
  4;114,137,138,115;,
  4;115,138,116,93;,
  4;116,139,140,117;,
  4;117,140,141,118;,
  4;118,141,142,119;,
  4;119,142,143,120;,
  4;120,143,144,121;,
  4;121,144,145,122;,
  4;122,145,146,123;,
  4;123,146,147,124;,
  4;124,147,148,125;,
  4;125,148,149,126;,
  4;126,149,150,127;,
  4;127,150,151,128;,
  4;128,151,152,129;,
  4;129,152,153,130;,
  4;130,153,154,131;,
  4;131,154,155,132;,
  4;132,155,156,133;,
  4;133,156,157,134;,
  4;134,157,158,135;,
  4;135,158,159,136;,
  4;136,159,160,137;,
  4;137,160,161,138;,
  4;138,161,139,116;,
  4;139,162,163,140;,
  4;140,163,164,141;,
  4;141,164,165,142;,
  4;142,165,166,143;,
  4;143,166,167,144;,
  4;144,167,168,145;,
  4;145,168,169,146;,
  4;146,169,170,147;,
  4;147,170,171,148;,
  4;148,171,172,149;,
  4;149,172,173,150;,
  4;150,173,174,151;,
  4;151,174,175,152;,
  4;152,175,176,153;,
  4;153,176,177,154;,
  4;154,177,178,155;,
  4;155,178,179,156;,
  4;156,179,180,157;,
  4;157,180,181,158;,
  4;158,181,182,159;,
  4;159,182,183,160;,
  4;160,183,184,161;,
  4;161,184,162,139;,
  4;162,185,186,163;,
  4;163,186,187,164;,
  4;164,187,188,165;,
  4;165,188,189,166;,
  4;166,189,190,167;,
  4;167,190,191,168;,
  4;168,191,192,169;,
  4;169,192,193,170;,
  4;170,193,194,171;,
  4;171,194,195,172;,
  4;172,195,196,173;,
  4;173,196,197,174;,
  4;174,197,198,175;,
  4;175,198,199,176;,
  4;176,199,200,177;,
  4;177,200,201,178;,
  4;178,201,202,179;,
  4;179,202,203,180;,
  4;180,203,204,181;,
  4;181,204,205,182;,
  4;182,205,206,183;,
  4;183,206,207,184;,
  4;184,207,185,162;,
  4;185,208,209,186;,
  4;186,209,210,187;,
  4;187,210,211,188;,
  4;188,211,212,189;,
  4;189,212,213,190;,
  4;190,213,214,191;,
  4;191,214,215,192;,
  4;192,215,216,193;,
  4;193,216,217,194;,
  4;194,217,218,195;,
  4;195,218,219,196;,
  4;196,219,220,197;,
  4;197,220,221,198;,
  4;198,221,222,199;,
  4;199,222,223,200;,
  4;200,223,224,201;,
  4;201,224,225,202;,
  4;202,225,226,203;,
  4;203,226,227,204;,
  4;204,227,228,205;,
  4;205,228,229,206;,
  4;206,229,230,207;,
  4;207,230,208,185;,
  4;208,231,232,209;,
  4;209,232,233,210;,
  4;210,233,234,211;,
  4;211,234,235,212;,
  4;212,235,236,213;,
  4;213,236,237,214;,
  4;214,237,238,215;,
  4;215,238,239,216;,
  4;216,239,240,217;,
  4;217,240,241,218;,
  4;218,241,242,219;,
  4;219,242,243,220;,
  4;220,243,244,221;,
  4;221,244,245,222;,
  4;222,245,246,223;,
  4;223,246,247,224;,
  4;224,247,248,225;,
  4;225,248,249,226;,
  4;226,249,250,227;,
  4;227,250,251,228;,
  4;228,251,252,229;,
  4;229,252,253,230;,
  4;230,253,231,208;;
 }
 MeshTextureCoords {
  275;
  0.983047;0.075800;,
  0.992299;0.158686;,
  1.016056;0.156482;,
  1.039922;0.151787;,
  1.063994;0.144581;,
  1.088406;0.134845;,
  1.113364;0.122585;,
  1.139223;0.107857;,
  1.166655;0.090806;,
  1.197152;0.071724;,
  1.234747;0.051168;,
  1.294675;0.030445;,
  1.454689;0.016051;,
  0.650197;0.026215;,
  0.721118;0.046542;,
  0.761515;0.067298;,
  0.793068;0.086765;,
  0.821001;0.104295;,
  0.847131;0.119551;,
  0.872249;0.132362;,
  0.896760;0.142655;,
  0.920893;0.150417;,
  0.944795;0.155662;,
  0.968570;0.158414;,
  0.994987;0.231514;,
  1.025723;0.229322;,
  0.016056;0.156482;,
  0.025723;0.229322;,
  0.056861;0.224640;,
  0.039922;0.151787;,
  0.088740;0.217421;,
  0.063994;0.144581;,
  0.121793;0.207627;,
  0.088406;0.134845;,
  0.156612;0.195275;,
  0.113364;0.122585;,
  0.194043;0.180530;,
  0.139223;0.107857;,
  0.235334;0.163853;,
  0.166655;0.090806;,
  0.282287;0.146244;,
  0.197152;0.071724;,
  0.337210;0.129555;,
  0.234747;0.051168;,
  0.401914;0.116706;,
  0.294675;0.030445;,
  0.474794;0.111125;,
  0.454689;0.016051;,
  0.548666;0.114744;,
  0.615502;0.126276;,
  0.672484;0.142406;,
  0.720984;0.160007;,
  0.763345;0.176999;,
  0.801501;0.192224;,
  0.836811;0.205125;,
  0.870195;0.215487;,
  0.902292;0.223270;,
  0.933561;0.228506;,
  0.964359;0.231244;,
  0.996248;0.294847;,
  1.030232;0.293092;,
  0.030232;0.293092;,
  0.064663;0.289346;,
  0.099903;0.283574;,
  0.136377;0.275755;,
  0.174607;0.265934;,
  0.215240;0.254306;,
  0.259052;0.241355;,
  0.306871;0.228028;,
  0.359323;0.215871;,
  0.416299;0.206932;,
  0.476358;0.203188;,
  0.536757;0.205605;,
  0.594589;0.213551;,
  0.648085;0.225186;,
  0.696885;0.238409;,
  0.741510;0.251544;,
  0.782772;0.263518;,
  0.821471;0.273761;,
  0.858283;0.282028;,
  0.893755;0.288250;,
  0.928332;0.292440;,
  0.962386;0.294630;,
  0.996966;0.350308;,
  1.032792;0.349051;,
  0.032792;0.349051;,
  0.069053;0.346370;,
  0.106088;0.342250;,
  0.144278;0.336690;,
  0.184054;0.329745;,
  0.225897;0.321589;,
  0.270310;0.312603;,
  0.317720;0.303486;,
  0.368301;0.295304;,
  0.421714;0.289383;,
  0.476925;0.286930;,
  0.532329;0.288512;,
  0.586252;0.293759;,
  0.637508;0.301560;,
  0.685615;0.310576;,
  0.730657;0.319663;,
  0.773023;0.328044;,
  0.813211;0.335276;,
  0.851711;0.341149;,
  0.888966;0.345587;,
  0.925367;0.348584;,
  0.961261;0.350153;,
  0.997421;0.399595;,
  1.034406;0.398790;,
  0.034406;0.398790;,
  0.071803;0.397076;,
  0.109924;0.394451;,
  0.149107;0.390927;,
  0.189714;0.386555;,
  0.232123;0.381465;,
  0.276686;0.375918;,
  0.323651;0.370357;,
  0.373038;0.365429;,
  0.424492;0.361900;,
  0.477213;0.360449;,
  0.530067;0.361384;,
  0.581884;0.364505;,
  0.631772;0.369192;,
  0.679280;0.374675;,
  0.724356;0.380271;,
  0.767211;0.385489;,
  0.808182;0.390034;,
  0.847647;0.393751;,
  0.885972;0.396576;,
  0.923500;0.398491;,
  0.960550;0.399496;,
  0.997726;0.444137;,
  1.035487;0.443714;,
  0.035487;0.443714;,
  0.073635;0.442817;,
  0.112462;0.441448;,
  0.152270;0.439621;,
  0.193374;0.437371;,
  0.236085;0.434775;,
  0.280669;0.431976;,
  0.327283;0.429203;,
  0.375885;0.426773;,
  0.426137;0.425050;,
  0.477382;0.424345;,
  0.528731;0.424799;,
  0.579269;0.426320;,
  0.628275;0.428626;,
  0.675339;0.431353;,
  0.720362;0.434170;,
  0.763464;0.436825;,
  0.804897;0.439160;,
  0.844963;0.441085;,
  0.883979;0.442556;,
  0.922252;0.443557;,
  0.960073;0.444084;,
  0.997937;0.485041;,
  1.036232;0.484935;,
  0.036232;0.484935;,
  0.074895;0.484710;,
  0.114198;0.484369;,
  0.154419;0.483915;,
  0.195840;0.483361;,
  0.238726;0.482727;,
  0.283292;0.482051;,
  0.329645;0.481388;,
  0.377715;0.480813;,
  0.427186;0.480409;,
  0.477490;0.480245;,
  0.527880;0.480351;,
  0.577592;0.480707;,
  0.626006;0.481251;,
  0.672751;0.481901;,
  0.717706;0.482580;,
  0.760946;0.483227;,
  0.802668;0.483801;,
  0.843130;0.484278;,
  0.882610;0.484645;,
  0.921391;0.484896;,
  0.959744;0.485028;,
  0.998083;0.523144;,
  1.036749;0.523298;,
  0.036749;0.523298;,
  0.075767;0.523622;,
  0.115395;0.524114;,
  0.155894;0.524763;,
  0.197522;0.525551;,
  0.240515;0.526445;,
  0.285054;0.527390;,
  0.331219;0.528306;,
  0.378925;0.529094;,
  0.427876;0.529643;,
  0.477560;0.529865;,
  0.527321;0.529722;,
  0.576484;0.529239;,
  0.624497;0.528495;,
  0.671016;0.527597;,
  0.715911;0.526651;,
  0.759231;0.525740;,
  0.801141;0.524926;,
  0.841867;0.524244;,
  0.881664;0.523716;,
  0.920794;0.523355;,
  0.959516;0.523163;,
  0.998182;0.559071;,
  1.037098;0.559438;,
  0.037098;0.559438;,
  0.076354;0.560211;,
  0.116200;0.561379;,
  0.156883;0.562913;,
  0.198644;0.564764;,
  0.241702;0.566847;,
  0.286218;0.569031;,
  0.332253;0.571131;,
  0.379717;0.572919;,
  0.428326;0.574159;,
  0.477606;0.574659;,
  0.526956;0.574337;,
  0.575760;0.573247;,
  0.623507;0.571560;,
  0.669870;0.569508;,
  0.714720;0.567325;,
  0.758088;0.565206;,
  0.800118;0.563295;,
  0.841018;0.561686;,
  0.881026;0.560435;,
  0.920391;0.559573;,
  0.959361;0.559116;,
  0.998243;0.593290;,
  1.037314;0.593833;,
  0.037314;0.593833;,
  0.076718;0.594974;,
  0.116698;0.596692;,
  0.157493;0.598940;,
  0.199336;0.601636;,
  0.242431;0.604651;,
  0.286930;0.607787;,
  0.332884;0.610780;,
  0.380198;0.613310;,
  0.428599;0.615054;,
  0.477634;0.615755;,
  0.526735;0.615304;,
  0.575320;0.613772;,
  0.622904;0.611388;,
  0.669171;0.608469;,
  0.713990;0.605339;,
  0.757384;0.602279;,
  0.799487;0.599499;,
  0.840493;0.597144;,
  0.880631;0.595304;,
  0.920141;0.594033;,
  0.959265;0.593358;,
  0.998272;0.626159;,
  1.037418;0.626846;,
  0.037418;0.626846;,
  0.076893;0.628291;,
  0.116936;0.630459;,
  0.157785;0.633285;,
  0.199665;0.636658;,
  0.242779;0.640406;,
  0.287269;0.644280;,
  0.333183;0.647953;,
  0.380426;0.651039;,
  0.428728;0.653156;,
  0.477647;0.654006;,
  0.526631;0.653460;,
  0.575112;0.651601;,
  0.622617;0.648697;,
  0.668838;0.645119;,
  0.713642;0.641258;,
  0.757049;0.637458;,
  0.799185;0.633985;,
  0.840242;0.631028;,
  0.880442;0.628708;,
  0.920022;0.627100;,
  0.959219;0.626244;;
 }
}