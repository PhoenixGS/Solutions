#include <cstdio>
#include <iostream>

typedef long long ll;

const ll M = 1000000007;

ll f[1005];

ll calc(ll x)
{
	ll tmp = f[x / 1000000];
	for (int i = (x / 1000000) * 1000000 + 1; i <= x; i++)
	{
		tmp = tmp * i % M;
	}
	return tmp;
}

int main()
{
	f[0] = 1;
	f[1] = 641102369;
	f[2] = 578095319;
	f[3] = 5832229;
	f[4] = 259081142;
	f[5] = 974067448;
	f[6] = 316220877;
	f[7] = 690120224;
	f[8] = 251368199;
	f[9] = 980250487;
	f[10] = 682498929;
	f[11] = 134623568;
	f[12] = 95936601;
	f[13] = 933097914;
	f[14] = 167332441;
	f[15] = 598816162;
	f[16] = 336060741;
	f[17] = 248744620;
	f[18] = 626497524;
	f[19] = 288843364;
	f[20] = 491101308;
	f[21] = 245341950;
	f[22] = 565768255;
	f[23] = 246899319;
	f[24] = 968999;
	f[25] = 586350670;
	f[26] = 638587686;
	f[27] = 881746146;
	f[28] = 19426633;
	f[29] = 850500036;
	f[30] = 76479948;
	f[31] = 268124147;
	f[32] = 842267748;
	f[33] = 886294336;
	f[34] = 485348706;
	f[35] = 463847391;
	f[36] = 544075857;
	f[37] = 898187927;
	f[38] = 798967520;
	f[39] = 82926604;
	f[40] = 723816384;
	f[41] = 156530778;
	f[42] = 721996174;
	f[43] = 299085602;
	f[44] = 323604647;
	f[45] = 172827403;
	f[46] = 398699886;
	f[47] = 530389102;
	f[48] = 294587621;
	f[49] = 813805606;
	f[50] = 67347853;
	f[51] = 497478507;
	f[52] = 196447201;
	f[53] = 722054885;
	f[54] = 228338256;
	f[55] = 407719831;
	f[56] = 762479457;
	f[57] = 746536789;
	f[58] = 811667359;
	f[59] = 778773518;
	f[60] = 27368307;
	f[61] = 438371670;
	f[62] = 59469516;
	f[63] = 5974669;
	f[64] = 766196482;
	f[65] = 606322308;
	f[66] = 86609485;
	f[67] = 889750731;
	f[68] = 340941507;
	f[69] = 371263376;
	f[70] = 625544428;
	f[71] = 788878910;
	f[72] = 808412394;
	f[73] = 996952918;
	f[74] = 585237443;
	f[75] = 1669644;
	f[76] = 361786913;
	f[77] = 480748381;
	f[78] = 595143852;
	f[79] = 837229828;
	f[80] = 199888908;
	f[81] = 526807168;
	f[82] = 579691190;
	f[83] = 145404005;
	f[84] = 459188207;
	f[85] = 534491822;
	f[86] = 439729802;
	f[87] = 840398449;
	f[88] = 899297830;
	f[89] = 235861787;
	f[90] = 888050723;
	f[91] = 656116726;
	f[92] = 736550105;
	f[93] = 440902696;
	f[94] = 85990869;
	f[95] = 884343068;
	f[96] = 56305184;
	f[97] = 973478770;
	f[98] = 168891766;
	f[99] = 804805577;
	f[100] = 927880474;
	f[101] = 876297919;
	f[102] = 934814019;
	f[103] = 676405347;
	f[104] = 567277637;
	f[105] = 112249297;
	f[106] = 44930135;
	f[107] = 39417871;
	f[108] = 47401357;
	f[109] = 108819476;
	f[110] = 281863274;
	f[111] = 60168088;
	f[112] = 692636218;
	f[113] = 432775082;
	f[114] = 14235602;
	f[115] = 770511792;
	f[116] = 400295761;
	f[117] = 697066277;
	f[118] = 421835306;
	f[119] = 220108638;
	f[120] = 661224977;
	f[121] = 261799937;
	f[122] = 168203998;
	f[123] = 802214249;
	f[124] = 544064410;
	f[125] = 935080803;
	f[126] = 583967898;
	f[127] = 211768084;
	f[128] = 751231582;
	f[129] = 972424306;
	f[130] = 623534362;
	f[131] = 335160196;
	f[132] = 243276029;
	f[133] = 554749550;
	f[134] = 60050552;
	f[135] = 797848181;
	f[136] = 395891998;
	f[137] = 172428290;
	f[138] = 159554990;
	f[139] = 887420150;
	f[140] = 970055531;
	f[141] = 250388809;
	f[142] = 487998999;
	f[143] = 856259313;
	f[144] = 82104855;
	f[145] = 232253360;
	f[146] = 513365505;
	f[147] = 244109365;
	f[148] = 1559745;
	f[149] = 695345956;
	f[150] = 261384175;
	f[151] = 849009131;
	f[152] = 323214113;
	f[153] = 747664143;
	f[154] = 444090941;
	f[155] = 659224434;
	f[156] = 80729842;
	f[157] = 570033864;
	f[158] = 664989237;
	f[159] = 827348878;
	f[160] = 195888993;
	f[161] = 576798521;
	f[162] = 457882808;
	f[163] = 731551699;
	f[164] = 212938473;
	f[165] = 509096183;
	f[166] = 827544702;
	f[167] = 678320208;
	f[168] = 677711203;
	f[169] = 289752035;
	f[170] = 66404266;
	f[171] = 555972231;
	f[172] = 195290384;
	f[173] = 97136305;
	f[174] = 349551356;
	f[175] = 785113347;
	f[176] = 83489485;
	f[177] = 66247239;
	f[178] = 52167191;
	f[179] = 307390891;
	f[180] = 547665832;
	f[181] = 143066173;
	f[182] = 350016754;
	f[183] = 917404120;
	f[184] = 296269301;
	f[185] = 996122673;
	f[186] = 23015220;
	f[187] = 602139210;
	f[188] = 748566338;
	f[189] = 187348575;
	f[190] = 109838563;
	f[191] = 574053420;
	f[192] = 105574531;
	f[193] = 304173654;
	f[194] = 542432219;
	f[195] = 34538816;
	f[196] = 325636655;
	f[197] = 437843114;
	f[198] = 630621321;
	f[199] = 26853683;
	f[200] = 933245637;
	f[201] = 616368450;
	f[202] = 238971581;
	f[203] = 511371690;
	f[204] = 557301633;
	f[205] = 911398531;
	f[206] = 848952161;
	f[207] = 958992544;
	f[208] = 925152039;
	f[209] = 914456118;
	f[210] = 724691727;
	f[211] = 636817583;
	f[212] = 238087006;
	f[213] = 946237212;
	f[214] = 910291942;
	f[215] = 114985663;
	f[216] = 492237273;
	f[217] = 450387329;
	f[218] = 834860913;
	f[219] = 763017204;
	f[220] = 368925948;
	f[221] = 475812562;
	f[222] = 740594930;
	f[223] = 45060610;
	f[224] = 806047532;
	f[225] = 464456846;
	f[226] = 172115341;
	f[227] = 75307702;
	f[228] = 116261993;
	f[229] = 562519302;
	f[230] = 268838846;
	f[231] = 173784895;
	f[232] = 243624360;
	f[233] = 61570384;
	f[234] = 481661251;
	f[235] = 938269070;
	f[236] = 95182730;
	f[237] = 91068149;
	f[238] = 115435332;
	f[239] = 495022305;
	f[240] = 136026497;
	f[241] = 506496856;
	f[242] = 710729672;
	f[243] = 113570024;
	f[244] = 366384665;
	f[245] = 564758715;
	f[246] = 270239666;
	f[247] = 277118392;
	f[248] = 79874094;
	f[249] = 702807165;
	f[250] = 112390913;
	f[251] = 730341625;
	f[252] = 103056890;
	f[253] = 677948390;
	f[254] = 339464594;
	f[255] = 167240465;
	f[256] = 108312174;
	f[257] = 839079953;
	f[258] = 479334442;
	f[259] = 271788964;
	f[260] = 135498044;
	f[261] = 277717575;
	f[262] = 591048681;
	f[263] = 811637561;
	f[264] = 353339603;
	f[265] = 889410460;
	f[266] = 839849206;
	f[267] = 192345193;
	f[268] = 736265527;
	f[269] = 316439118;
	f[270] = 217544623;
	f[271] = 788132977;
	f[272] = 618898635;
	f[273] = 183011467;
	f[274] = 380858207;
	f[275] = 996097969;
	f[276] = 898554793;
	f[277] = 335353644;
	f[278] = 54062950;
	f[279] = 611251733;
	f[280] = 419363534;
	f[281] = 965429853;
	f[282] = 160398980;
	f[283] = 151319402;
	f[284] = 990918946;
	f[285] = 607730875;
	f[286] = 450718279;
	f[287] = 173539388;
	f[288] = 648991369;
	f[289] = 970937898;
	f[290] = 500780548;
	f[291] = 780122909;
	f[292] = 39052406;
	f[293] = 276894233;
	f[294] = 460373282;
	f[295] = 651081062;
	f[296] = 461415770;
	f[297] = 358700839;
	f[298] = 643638805;
	f[299] = 560006119;
	f[300] = 668123525;
	f[301] = 686692315;
	f[302] = 673464765;
	f[303] = 957633609;
	f[304] = 199866123;
	f[305] = 563432246;
	f[306] = 841799766;
	f[307] = 385330357;
	f[308] = 504962686;
	f[309] = 954061253;
	f[310] = 128487469;
	f[311] = 685707545;
	f[312] = 299172297;
	f[313] = 717975101;
	f[314] = 577786541;
	f[315] = 318951960;
	f[316] = 773206631;
	f[317] = 306832604;
	f[318] = 204355779;
	f[319] = 573592106;
	f[320] = 30977140;
	f[321] = 450398100;
	f[322] = 363172638;
	f[323] = 258379324;
	f[324] = 472935553;
	f[325] = 93940075;
	f[326] = 587220627;
	f[327] = 776264326;
	f[328] = 793270300;
	f[329] = 291733496;
	f[330] = 522049725;
	f[331] = 579995261;
	f[332] = 335416359;
	f[333] = 142946099;
	f[334] = 472012302;
	f[335] = 559947225;
	f[336] = 332139472;
	f[337] = 499377092;
	f[338] = 464599136;
	f[339] = 164752359;
	f[340] = 309058615;
	f[341] = 86117128;
	f[342] = 580204973;
	f[343] = 563781682;
	f[344] = 954840109;
	f[345] = 624577416;
	f[346] = 895609896;
	f[347] = 888287558;
	f[348] = 836813268;
	f[349] = 926036911;
	f[350] = 386027524;
	f[351] = 184419613;
	f[352] = 724205533;
	f[353] = 403351886;
	f[354] = 715247054;
	f[355] = 716986954;
	f[356] = 830567832;
	f[357] = 383388563;
	f[358] = 68409439;
	f[359] = 6734065;
	f[360] = 189239124;
	f[361] = 68322490;
	f[362] = 943653305;
	f[363] = 405755338;
	f[364] = 811056092;
	f[365] = 179518046;
	f[366] = 825132993;
	f[367] = 343807435;
	f[368] = 985084650;
	f[369] = 868553027;
	f[370] = 148528617;
	f[371] = 160684257;
	f[372] = 882148737;
	f[373] = 591915968;
	f[374] = 701445829;
	f[375] = 529726489;
	f[376] = 302177126;
	f[377] = 974886682;
	f[378] = 241107368;
	f[379] = 798830099;
	f[380] = 940567523;
	f[381] = 11633075;
	f[382] = 325334066;
	f[383] = 346091869;
	f[384] = 115312728;
	f[385] = 473718967;
	f[386] = 218129285;
	f[387] = 878471898;
	f[388] = 180002392;
	f[389] = 699739374;
	f[390] = 917084264;
	f[391] = 856859395;
	f[392] = 435327356;
	f[393] = 808651347;
	f[394] = 421623838;
	f[395] = 105419548;
	f[396] = 59883031;
	f[397] = 322487421;
	f[398] = 79716267;
	f[399] = 715317963;
	f[400] = 429277690;
	f[401] = 398078032;
	f[402] = 316486674;
	f[403] = 384843585;
	f[404] = 940338439;
	f[405] = 937409008;
	f[406] = 940524812;
	f[407] = 947549662;
	f[408] = 833550543;
	f[409] = 593524514;
	f[410] = 996164327;
	f[411] = 987314628;
	f[412] = 697611981;
	f[413] = 636177449;
	f[414] = 274192146;
	f[415] = 418537348;
	f[416] = 925347821;
	f[417] = 952831975;
	f[418] = 893732627;
	f[419] = 1277567;
	f[420] = 358655417;
	f[421] = 141866945;
	f[422] = 581830879;
	f[423] = 987597705;
	f[424] = 347046911;
	f[425] = 775305697;
	f[426] = 125354499;
	f[427] = 951540811;
	f[428] = 247662371;
	f[429] = 343043237;
	f[430] = 568392357;
	f[431] = 997474832;
	f[432] = 209244402;
	f[433] = 380480118;
	f[434] = 149586983;
	f[435] = 392838702;
	f[436] = 309134554;
	f[437] = 990779998;
	f[438] = 263053337;
	f[439] = 325362513;
	f[440] = 780072518;
	f[441] = 551028176;
	f[442] = 990826116;
	f[443] = 989944961;
	f[444] = 155569943;
	f[445] = 596737944;
	f[446] = 711553356;
	f[447] = 268844715;
	f[448] = 451373308;
	f[449] = 379404150;
	f[450] = 462639908;
	f[451] = 961812918;
	f[452] = 654611901;
	f[453] = 382776490;
	f[454] = 41815820;
	f[455] = 843321396;
	f[456] = 675258797;
	f[457] = 845583555;
	f[458] = 934281721;
	f[459] = 741114145;
	f[460] = 275105629;
	f[461] = 666247477;
	f[462] = 325912072;
	f[463] = 526131620;
	f[464] = 252551589;
	f[465] = 432030917;
	f[466] = 554917439;
	f[467] = 818036959;
	f[468] = 754363835;
	f[469] = 795190182;
	f[470] = 909210595;
	f[471] = 278704903;
	f[472] = 719566487;
	f[473] = 628514947;
	f[474] = 424989675;
	f[475] = 321685608;
	f[476] = 50590510;
	f[477] = 832069712;
	f[478] = 198768464;
	f[479] = 702004730;
	f[480] = 99199382;
	f[481] = 707469729;
	f[482] = 747407118;
	f[483] = 302020341;
	f[484] = 497196934;
	f[485] = 5003231;
	f[486] = 726997875;
	f[487] = 382617671;
	f[488] = 296229203;
	f[489] = 183888367;
	f[490] = 703397904;
	f[491] = 552133875;
	f[492] = 732868367;
	f[493] = 350095207;
	f[494] = 26031303;
	f[495] = 863250534;
	f[496] = 216665960;
	f[497] = 561745549;
	f[498] = 352946234;
	f[499] = 784139777;
	f[500] = 733333339;
	f[501] = 503105966;
	f[502] = 459878625;
	f[503] = 803187381;
	f[504] = 16634739;
	f[505] = 180898306;
	f[506] = 68718097;
	f[507] = 985594252;
	f[508] = 404206040;
	f[509] = 749724532;
	f[510] = 97830135;
	f[511] = 611751357;
	f[512] = 31131935;
	f[513] = 662741752;
	f[514] = 864326453;
	f[515] = 864869025;
	f[516] = 167831173;
	f[517] = 559214642;
	f[518] = 718498895;
	f[519] = 91352335;
	f[520] = 608823837;
	f[521] = 473379392;
	f[522] = 385388084;
	f[523] = 152267158;
	f[524] = 681756977;
	f[525] = 46819124;
	f[526] = 313132653;
	f[527] = 56547945;
	f[528] = 442795120;
	f[529] = 796616594;
	f[530] = 256141983;
	f[531] = 152028387;
	f[532] = 636578562;
	f[533] = 385377759;
	f[534] = 553033642;
	f[535] = 491415383;
	f[536] = 919273670;
	f[537] = 996049638;
	f[538] = 326686486;
	f[539] = 160150665;
	f[540] = 141827977;
	f[541] = 540818053;
	f[542] = 693305776;
	f[543] = 593938674;
	f[544] = 186576440;
	f[545] = 688809790;
	f[546] = 565456578;
	f[547] = 749296077;
	f[548] = 519397500;
	f[549] = 551096742;
	f[550] = 696628828;
	f[551] = 775025061;
	f[552] = 370732451;
	f[553] = 164246193;
	f[554] = 915265013;
	f[555] = 457469634;
	f[556] = 923043932;
	f[557] = 912368644;
	f[558] = 777901604;
	f[559] = 464118005;
	f[560] = 637939935;
	f[561] = 956856710;
	f[562] = 490676632;
	f[563] = 453019482;
	f[564] = 462528877;
	f[565] = 502297454;
	f[566] = 798895521;
	f[567] = 100498586;
	f[568] = 699767918;
	f[569] = 849974789;
	f[570] = 811575797;
	f[571] = 438952959;
	f[572] = 606870929;
	f[573] = 907720182;
	f[574] = 179111720;
	f[575] = 48053248;
	f[576] = 508038818;
	f[577] = 811944661;
	f[578] = 752550134;
	f[579] = 401382061;
	f[580] = 848924691;
	f[581] = 764368449;
	f[582] = 34629406;
	f[583] = 529840945;
	f[584] = 435904287;
	f[585] = 26011548;
	f[586] = 208184231;
	f[587] = 446477394;
	f[588] = 206330671;
	f[589] = 366033520;
	f[590] = 131772368;
	f[591] = 185646898;
	f[592] = 648711554;
	f[593] = 472759660;
	f[594] = 523696723;
	f[595] = 271198437;
	f[596] = 25058942;
	f[597] = 859369491;
	f[598] = 817928963;
	f[599] = 330711333;
	f[600] = 724464507;
	f[601] = 437605233;
	f[602] = 701453022;
	f[603] = 626663115;
	f[604] = 281230685;
	f[605] = 510650790;
	f[606] = 596949867;
	f[607] = 295726547;
	f[608] = 303076380;
	f[609] = 465070856;
	f[610] = 272814771;
	f[611] = 538771609;
	f[612] = 48824684;
	f[613] = 951279549;
	f[614] = 939889684;
	f[615] = 564188856;
	f[616] = 48527183;
	f[617] = 201307702;
	f[618] = 484458461;
	f[619] = 861754542;
	f[620] = 326159309;
	f[621] = 181594759;
	f[622] = 668422905;
	f[623] = 286273596;
	f[624] = 965656187;
	f[625] = 44135644;
	f[626] = 359960756;
	f[627] = 936229527;
	f[628] = 407934361;
	f[629] = 267193060;
	f[630] = 456152084;
	f[631] = 459116722;
	f[632] = 124804049;
	f[633] = 262322489;
	f[634] = 920251227;
	f[635] = 816929577;
	f[636] = 483924582;
	f[637] = 151834896;
	f[638] = 167087470;
	f[639] = 490222511;
	f[640] = 903466878;
	f[641] = 361583925;
	f[642] = 368114731;
	f[643] = 339383292;
	f[644] = 388728584;
	f[645] = 218107212;
	f[646] = 249153339;
	f[647] = 909458706;
	f[648] = 322908524;
	f[649] = 202649964;
	f[650] = 92255682;
	f[651] = 573074791;
	f[652] = 15570863;
	f[653] = 94331513;
	f[654] = 744158074;
	f[655] = 196345098;
	f[656] = 334326205;
	f[657] = 9416035;
	f[658] = 98349682;
	f[659] = 882121662;
	f[660] = 769795511;
	f[661] = 231988936;
	f[662] = 888146074;
	f[663] = 137603545;
	f[664] = 582627184;
	f[665] = 407518072;
	f[666] = 919419361;
	f[667] = 909433461;
	f[668] = 986708498;
	f[669] = 310317874;
	f[670] = 373745190;
	f[671] = 263645931;
	f[672] = 256853930;
	f[673] = 876379959;
	f[674] = 702823274;
	f[675] = 147050765;
	f[676] = 308186532;
	f[677] = 175504139;
	f[678] = 180350107;
	f[679] = 797736554;
	f[680] = 606241871;
	f[681] = 384547635;
	f[682] = 273712630;
	f[683] = 586444655;
	f[684] = 682189174;
	f[685] = 666493603;
	f[686] = 946867127;
	f[687] = 819114541;
	f[688] = 502371023;
	f[689] = 261970285;
	f[690] = 825871994;
	f[691] = 126925175;
	f[692] = 701506133;
	f[693] = 314738056;
	f[694] = 341779962;
	f[695] = 561011609;
	f[696] = 815463367;
	f[697] = 46765164;
	f[698] = 49187570;
	f[699] = 188054995;
	f[700] = 957939114;
	f[701] = 64814326;
	f[702] = 933376898;
	f[703] = 329837066;
	f[704] = 338121343;
	f[705] = 765215899;
	f[706] = 869630152;
	f[707] = 978119194;
	f[708] = 632627667;
	f[709] = 975266085;
	f[710] = 435887178;
	f[711] = 282092463;
	f[712] = 129621197;
	f[713] = 758245605;
	f[714] = 827722926;
	f[715] = 201339230;
	f[716] = 918513230;
	f[717] = 322096036;
	f[718] = 547838438;
	f[719] = 985546115;
	f[720] = 852304035;
	f[721] = 593090119;
	f[722] = 689189630;
	f[723] = 555842733;
	f[724] = 567033437;
	f[725] = 469928208;
	f[726] = 212842957;
	f[727] = 117842065;
	f[728] = 404149413;
	f[729] = 155133422;
	f[730] = 663307737;
	f[731] = 208761293;
	f[732] = 206282795;
	f[733] = 717946122;
	f[734] = 488906585;
	f[735] = 414236650;
	f[736] = 280700600;
	f[737] = 962670136;
	f[738] = 534279149;
	f[739] = 214569244;
	f[740] = 375297772;
	f[741] = 811053196;
	f[742] = 922377372;
	f[743] = 289594327;
	f[744] = 219932130;
	f[745] = 211487466;
	f[746] = 701050258;
	f[747] = 398782410;
	f[748] = 863002719;
	f[749] = 27236531;
	f[750] = 217598709;
	f[751] = 375472836;
	f[752] = 810551911;
	f[753] = 178598958;
	f[754] = 247844667;
	f[755] = 676526196;
	f[756] = 812283640;
	f[757] = 863066876;
	f[758] = 857241854;
	f[759] = 113917835;
	f[760] = 624148346;
	f[761] = 726089763;
	f[762] = 564827277;
	f[763] = 826300950;
	f[764] = 478982047;
	f[765] = 439411911;
	f[766] = 454039189;
	f[767] = 633292726;
	f[768] = 48562889;
	f[769] = 802100365;
	f[770] = 671734977;
	f[771] = 945204804;
	f[772] = 508831870;
	f[773] = 398781902;
	f[774] = 897162044;
	f[775] = 644050694;
	f[776] = 892168027;
	f[777] = 828883117;
	f[778] = 277714559;
	f[779] = 713448377;
	f[780] = 624500515;
	f[781] = 590098114;
	f[782] = 808691930;
	f[783] = 514359662;
	f[784] = 895205045;
	f[785] = 715264908;
	f[786] = 628829100;
	f[787] = 484492064;
	f[788] = 919717789;
	f[789] = 513196123;
	f[790] = 748510389;
	f[791] = 403652653;
	f[792] = 574455974;
	f[793] = 77123823;
	f[794] = 172096141;
	f[795] = 819801784;
	f[796] = 581418893;
	f[797] = 15655126;
	f[798] = 15391652;
	f[799] = 875641535;
	f[800] = 203191898;
	f[801] = 264582598;
	f[802] = 880691101;
	f[803] = 907800444;
	f[804] = 986598821;
	f[805] = 340030191;
	f[806] = 264688936;
	f[807] = 369832433;
	f[808] = 785804644;
	f[809] = 842065079;
	f[810] = 423951674;
	f[811] = 663560047;
	f[812] = 696623384;
	f[813] = 496709826;
	f[814] = 161960209;
	f[815] = 331910086;
	f[816] = 541120825;
	f[817] = 951524114;
	f[818] = 841656666;
	f[819] = 162683802;
	f[820] = 629786193;
	f[821] = 190395535;
	f[822] = 269571439;
	f[823] = 832671304;
	f[824] = 76770272;
	f[825] = 341080135;
	f[826] = 421943723;
	f[827] = 494210290;
	f[828] = 751040886;
	f[829] = 317076664;
	f[830] = 672850561;
	f[831] = 72482816;
	f[832] = 493689107;
	f[833] = 135625240;
	f[834] = 100228913;
	f[835] = 684748812;
	f[836] = 639655136;
	f[837] = 906233141;
	f[838] = 929893103;
	f[839] = 277813439;
	f[840] = 814362881;
	f[841] = 562608724;
	f[842] = 406024012;
	f[843] = 885537778;
	f[844] = 10065330;
	f[845] = 60625018;
	f[846] = 983737173;
	f[847] = 60517502;
	f[848] = 551060742;
	f[849] = 804930491;
	f[850] = 823845496;
	f[851] = 727416538;
	f[852] = 946421040;
	f[853] = 678171399;
	f[854] = 842203531;
	f[855] = 175638827;
	f[856] = 894247956;
	f[857] = 538609927;
	f[858] = 885362182;
	f[859] = 946464959;
	f[860] = 116667533;
	f[861] = 749816133;
	f[862] = 241427979;
	f[863] = 871117927;
	f[864] = 281804989;
	f[865] = 163928347;
	f[866] = 563796647;
	f[867] = 640266394;
	f[868] = 774625892;
	f[869] = 59342705;
	f[870] = 256473217;
	f[871] = 674115061;
	f[872] = 918860977;
	f[873] = 322633051;
	f[874] = 753513874;
	f[875] = 393556719;
	f[876] = 304644842;
	f[877] = 767372800;
	f[878] = 161362528;
	f[879] = 754787150;
	f[880] = 627655552;
	f[881] = 677395736;
	f[882] = 799289297;
	f[883] = 846650652;
	f[884] = 816701166;
	f[885] = 687265514;
	f[886] = 787113234;
	f[887] = 358757251;
	f[888] = 701220427;
	f[889] = 607715125;
	f[890] = 245795606;
	f[891] = 600624983;
	f[892] = 10475577;
	f[893] = 728620948;
	f[894] = 759404319;
	f[895] = 36292292;
	f[896] = 491466901;
	f[897] = 22556579;
	f[898] = 114495791;
	f[899] = 647630109;
	f[900] = 586445753;
	f[901] = 482254337;
	f[902] = 718623833;
	f[903] = 763514207;
	f[904] = 66547751;
	f[905] = 953634340;
	f[906] = 351472920;
	f[907] = 308474522;
	f[908] = 494166907;
	f[909] = 634359666;
	f[910] = 172114298;
	f[911] = 865440961;
	f[912] = 364380585;
	f[913] = 921648059;
	f[914] = 965683742;
	f[915] = 260466949;
	f[916] = 117483873;
	f[917] = 962540888;
	f[918] = 237120480;
	f[919] = 620531822;
	f[920] = 193781724;
	f[921] = 213092254;
	f[922] = 107141741;
	f[923] = 602742426;
	f[924] = 793307102;
	f[925] = 756154604;
	f[926] = 236455213;
	f[927] = 362928234;
	f[928] = 14162538;
	f[929] = 753042874;
	f[930] = 778983779;
	f[931] = 25977209;
	f[932] = 49389215;
	f[933] = 698308420;
	f[934] = 859637374;
	f[935] = 49031023;
	f[936] = 713258160;
	f[937] = 737331920;
	f[938] = 923333660;
	f[939] = 804861409;
	f[940] = 83868974;
	f[941] = 682873215;
	f[942] = 217298111;
	f[943] = 883278906;
	f[944] = 176966527;
	f[945] = 954913;
	f[946] = 105359006;
	f[947] = 390019735;
	f[948] = 10430738;
	f[949] = 706334445;
	f[950] = 315103615;
	f[951] = 567473423;
	f[952] = 708233401;
	f[953] = 48160594;
	f[954] = 946149627;
	f[955] = 346966053;
	f[956] = 281329488;
	f[957] = 462880311;
	f[958] = 31503476;
	f[959] = 185438078;
	f[960] = 965785236;
	f[961] = 992656683;
	f[962] = 916291845;
	f[963] = 881482632;
	f[964] = 899946391;
	f[965] = 321900901;
	f[966] = 512634493;
	f[967] = 303338827;
	f[968] = 121000338;
	f[969] = 967284733;
	f[970] = 492741665;
	f[971] = 152233223;
	f[972] = 165393390;
	f[973] = 680128316;
	f[974] = 917041303;
	f[975] = 532702135;
	f[976] = 741626808;
	f[977] = 496442755;
	f[978] = 536841269;
	f[979] = 131384366;
	f[980] = 377329025;
	f[981] = 301196854;
	f[982] = 859917803;
	f[983] = 676511002;
	f[984] = 373451745;
	f[985] = 847645126;
	f[986] = 823495900;
	f[987] = 576368335;
	f[988] = 73146164;
	f[989] = 954958912;
	f[990] = 847549272;
	f[991] = 241289571;
	f[992] = 646654592;
	f[993] = 216046746;
	f[994] = 205951465;
	f[995] = 3258987;
	f[996] = 780882948;
	f[997] = 822439091;
	f[998] = 598245292;
	f[999] = 869544707;
	f[1000] = 698611116;
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	ll l = 1;
	ll r = n;
	ll k1 = m;
	ll k2 = n - m;
	ll ans = 1;
	ll cnt = 0;
	while (l <= r)
	{
		ll mid = (l + r) >> 1;
		if (mid <= k)
		{
			ans = ans * k1 % M;
			k1--;
			l = mid + 1;
		}
		else
		{
			ans = ans * k2 % M;
			k2--;
			r = mid - 1;
		}
		cnt++;
	}
	ans = ans * calc(n - cnt) % M;
	std::cout << ans << std::endl;
	return 0;
}
