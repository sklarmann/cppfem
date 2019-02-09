/*
 * GaussPoints.h
 *
 *  Created on: 12.08.2016
 *      Author: klari
 */

#pragma once

#include <vector>

namespace FEMProject {
	template<typename prec>
	void triangleGP(std::vector<prec> &xsi, std::vector<prec> &eta, std::vector<prec> &weight, const unsigned char &order) {

		xsi.clear();
		eta.clear();
		weight.clear();
		if (order <= 1) {
			xsi.push_back(-1.0 / 3.0); eta.push_back(-1.0 / 3.0); weight.push_back(2.000000000000000);
		}
		else if (order <= 2) {
			xsi.push_back((prec)-2.0 / (prec)3.0); eta.push_back((prec)-2.0 / (prec) 3.0); weight.push_back((prec)2.0 / (prec) 3.0);
			xsi.push_back((prec)-2.0 / (prec)3.0); eta.push_back((prec) 1.0 / (prec) 3.0); weight.push_back((prec)2.0 / (prec) 3.0);
			xsi.push_back((prec) 1.0 / (prec)3.0); eta.push_back((prec)-2.0 / (prec) 3.0); weight.push_back((prec)2.0 / (prec) 3.0);
		}
		else if (order <= 3) {
			xsi.push_back(-0.333333333333333); eta.push_back(-0.333333333333333); weight.push_back(-1.125000000000000);
			xsi.push_back(-0.600000000000000); eta.push_back(-0.600000000000000); weight.push_back(1.041666666666667);
			xsi.push_back(-0.600000000000000); eta.push_back(0.200000000000000); weight.push_back(1.041666666666667);
			xsi.push_back(0.200000000000000); eta.push_back(-0.600000000000000); weight.push_back(1.041666666666667);
		}
		else if (order <= 4) {
			xsi.push_back(-0.108103018168070); eta.push_back(-0.108103018168070); weight.push_back(0.446763179356022);
			xsi.push_back(-0.108103018168070); eta.push_back(-0.783793963663860); weight.push_back(0.446763179356022);
			xsi.push_back(-0.783793963663860); eta.push_back(-0.108103018168070); weight.push_back(0.446763179356022);
			xsi.push_back(-0.816847572980458); eta.push_back(-0.816847572980458); weight.push_back(0.219903487310644);
			xsi.push_back(-0.816847572980458); eta.push_back(0.633695145960918); weight.push_back(0.219903487310644);
			xsi.push_back(0.633695145960918); eta.push_back(-0.816847572980458); weight.push_back(0.219903487310644);
		}
		else if (order <= 5) {
			xsi.push_back(-0.333333333333333); eta.push_back(-0.333333333333333); weight.push_back(0.450000000000000);
			xsi.push_back(-0.059715871789770); eta.push_back(-0.059715871789770); weight.push_back(0.264788305577012);
			xsi.push_back(-0.059715871789770); eta.push_back(-0.880568256420460); weight.push_back(0.264788305577012);
			xsi.push_back(-0.880568256420460); eta.push_back(-0.059715871789770); weight.push_back(0.264788305577012);
			xsi.push_back(-0.797426985353088); eta.push_back(-0.797426985353088); weight.push_back(0.251878361089654);
			xsi.push_back(-0.797426985353088); eta.push_back(0.594853970706174); weight.push_back(0.251878361089654);
			xsi.push_back(0.594853970706174); eta.push_back(-0.797426985353088); weight.push_back(0.251878361089654);
		}
		else if (order <= 6) {
			xsi.push_back(-0.501426509658180); eta.push_back(-0.501426509658180); weight.push_back(0.233572551452758);
			xsi.push_back(-0.501426509658180); eta.push_back(0.002853019316358); weight.push_back(0.233572551452758);
			xsi.push_back(0.002853019316358); eta.push_back(-0.501426509658180); weight.push_back(0.233572551452758);
			xsi.push_back(-0.873821971016996); eta.push_back(-0.873821971016996); weight.push_back(0.101689812740414);
			xsi.push_back(-0.873821971016996); eta.push_back(0.747643942033992); weight.push_back(0.101689812740414);
			xsi.push_back(0.747643942033992); eta.push_back(-0.873821971016996); weight.push_back(0.101689812740414);
			xsi.push_back(-0.379295097932432); eta.push_back(0.273004998242798); weight.push_back(0.165702151236748);
			xsi.push_back(0.273004998242798); eta.push_back(-0.893709900310366); weight.push_back(0.165702151236748);
			xsi.push_back(-0.893709900310366); eta.push_back(-0.379295097932432); weight.push_back(0.165702151236748);
			xsi.push_back(-0.379295097932432); eta.push_back(-0.893709900310366); weight.push_back(0.165702151236748);
			xsi.push_back(0.273004998242798); eta.push_back(-0.379295097932432); weight.push_back(0.165702151236748);
			xsi.push_back(-0.893709900310366); eta.push_back(0.273004998242798); weight.push_back(0.165702151236748);
		}
		else if (order <= 7) {
			xsi.push_back(-0.333333333333333); eta.push_back(-0.333333333333333); weight.push_back(-0.299140088935364);
			xsi.push_back(-0.479308067841920); eta.push_back(-0.479308067841920); weight.push_back(0.351230514866416);
			xsi.push_back(-0.479308067841920); eta.push_back(-0.041383864316160); weight.push_back(0.351230514866416);
			xsi.push_back(-0.041383864316160); eta.push_back(-0.479308067841920); weight.push_back(0.351230514866416);
			xsi.push_back(-0.869739794195568); eta.push_back(-0.869739794195568); weight.push_back(0.106694471217676);
			xsi.push_back(-0.869739794195568); eta.push_back(0.739479588391136); weight.push_back(0.106694471217676);
			xsi.push_back(0.739479588391136); eta.push_back(-0.869739794195568); weight.push_back(0.106694471217676);
			xsi.push_back(-0.374269007990252); eta.push_back(0.276888377139620); weight.push_back(0.154227521780514);
			xsi.push_back(0.276888377139620); eta.push_back(-0.902619369149368); weight.push_back(0.154227521780514);
			xsi.push_back(-0.902619369149368); eta.push_back(-0.374269007990252); weight.push_back(0.154227521780514);
			xsi.push_back(-0.374269007990252); eta.push_back(-0.902619369149368); weight.push_back(0.154227521780514);
			xsi.push_back(0.276888377139620); eta.push_back(-0.374269007990252); weight.push_back(0.154227521780514);
			xsi.push_back(-0.902619369149368); eta.push_back(0.276888377139620); weight.push_back(0.154227521780514);
		}
		else if (order <= 8) {
			xsi.push_back(-0.333333333333333); eta.push_back(-0.333333333333333); weight.push_back(0.288631215355574);
			xsi.push_back(-0.081414823414554); eta.push_back(-0.081414823414554); weight.push_back(0.190183268534570);
			xsi.push_back(-0.081414823414554); eta.push_back(-0.837170353170892); weight.push_back(0.190183268534570);
			xsi.push_back(-0.837170353170892); eta.push_back(-0.081414823414554); weight.push_back(0.190183268534570);
			xsi.push_back(-0.658861384496480); eta.push_back(-0.658861384496480); weight.push_back(0.206434741069436);
			xsi.push_back(-0.658861384496480); eta.push_back(0.317722768992960); weight.push_back(0.206434741069436);
			xsi.push_back(0.317722768992960); eta.push_back(-0.658861384496480); weight.push_back(0.206434741069436);
			xsi.push_back(-0.898905543365938); eta.push_back(-0.898905543365938); weight.push_back(0.064916995246396);
			xsi.push_back(-0.898905543365938); eta.push_back(0.797811086731876); weight.push_back(0.064916995246395);
			xsi.push_back(0.797811086731876); eta.push_back(-0.898905543365938); weight.push_back(0.064916995246396);
			xsi.push_back(-0.473774340730724); eta.push_back(0.456984785910808); weight.push_back(0.054460628348870);
			xsi.push_back(0.456984785910808); eta.push_back(-0.983210445180084); weight.push_back(0.054460628348870);
			xsi.push_back(-0.983210445180084); eta.push_back(-0.473774340730724); weight.push_back(0.054460628348870);
			xsi.push_back(-0.473774340730724); eta.push_back(-0.983210445180084); weight.push_back(0.054460628348870);
			xsi.push_back(0.456984785910808); eta.push_back(-0.473774340730724); weight.push_back(0.054460628348870);
			xsi.push_back(-0.983210445180084); eta.push_back(0.456984785910808); weight.push_back(0.054460628348870);
		}
		else if (order <= 9) {
			xsi.push_back(-0.333333333333333); eta.push_back(-0.333333333333333); weight.push_back(0.194271592565598);
			xsi.push_back(-0.020634961602524); eta.push_back(-0.020634961602524); weight.push_back(0.062669400454278);
			xsi.push_back(-0.020634961602524); eta.push_back(-0.958730076794950); weight.push_back(0.062669400454278);
			xsi.push_back(-0.958730076794950); eta.push_back(-0.020634961602524); weight.push_back(0.062669400454278);
			xsi.push_back(-0.125820817014126); eta.push_back(-0.125820817014126); weight.push_back(0.155655082009548);
			xsi.push_back(-0.125820817014126); eta.push_back(-0.748358365971746); weight.push_back(0.155655082009548);
			xsi.push_back(-0.748358365971746); eta.push_back(-0.125820817014126); weight.push_back(0.155655082009548);
			xsi.push_back(-0.623592928761934); eta.push_back(-0.623592928761934); weight.push_back(0.159295477854420);
			xsi.push_back(-0.623592928761934); eta.push_back(0.247185857523870); weight.push_back(0.159295477854420);
			xsi.push_back(0.247185857523870); eta.push_back(-0.623592928761934); weight.push_back(0.159295477854420);
			xsi.push_back(-0.910540973211094); eta.push_back(-0.910540973211094); weight.push_back(0.051155351317396);
			xsi.push_back(-0.910540973211094); eta.push_back(0.821081946422190); weight.push_back(0.051155351317396);
			xsi.push_back(0.821081946422190); eta.push_back(-0.910540973211094); weight.push_back(0.051155351317396);
			xsi.push_back(-0.556074021678468); eta.push_back(0.482397197568996); weight.push_back(0.086567078754578);
			xsi.push_back(0.482397197568996); eta.push_back(-0.926323175890528); weight.push_back(0.086567078754578);
			xsi.push_back(-0.926323175890528); eta.push_back(-0.556074021678468); weight.push_back(0.086567078754578);
			xsi.push_back(-0.556074021678468); eta.push_back(-0.926323175890528); weight.push_back(0.086567078754578);
			xsi.push_back(0.482397197568996); eta.push_back(-0.556074021678468); weight.push_back(0.086567078754578);
			xsi.push_back(-0.926323175890528); eta.push_back(0.482397197568996); weight.push_back(0.086567078754578);
		}
		else if (order <= 10) {
			xsi.push_back(-0.333333333333333); eta.push_back(-0.333333333333333); weight.push_back(0.181635980765508);
			xsi.push_back(-0.028844733232686); eta.push_back(-0.028844733232686); weight.push_back(0.073451915512934);
			xsi.push_back(-0.028844733232686); eta.push_back(-0.942310533534630); weight.push_back(0.073451915512934);
			xsi.push_back(-0.942310533534630); eta.push_back(-0.028844733232686); weight.push_back(0.073451915512934);
			xsi.push_back(-0.781036849029926); eta.push_back(-0.781036849029926); weight.push_back(0.090642118871056);
			xsi.push_back(-0.781036849029926); eta.push_back(0.562073698059852); weight.push_back(0.090642118871056);
			xsi.push_back(0.562073698059852); eta.push_back(-0.781036849029926); weight.push_back(0.090642118871056);
			xsi.push_back(-0.384120322471758); eta.push_back(0.100705883641998); weight.push_back(0.145515833690840);
			xsi.push_back(0.100705883641998); eta.push_back(-0.716585561170240); weight.push_back(0.145515833690840);
			xsi.push_back(-0.716585561170240); eta.push_back(-0.384120322471758); weight.push_back(0.145515833690840);
			xsi.push_back(-0.384120322471758); eta.push_back(-0.716585561170240); weight.push_back(0.145515833690840);
			xsi.push_back(0.100705883641998); eta.push_back(-0.384120322471758); weight.push_back(0.145515833690840);
			xsi.push_back(-0.716585561170240); eta.push_back(0.100705883641998); weight.push_back(0.145515833690840);
			xsi.push_back(-0.506654878720194); eta.push_back(0.456647809194822); weight.push_back(0.056654485062114);
			xsi.push_back(0.456647809194822); eta.push_back(-0.949992930474628); weight.push_back(0.056654485062114);
			xsi.push_back(-0.949992930474628); eta.push_back(-0.506654878720194); weight.push_back(0.056654485062114);
			xsi.push_back(-0.506654878720194); eta.push_back(-0.949992930474628); weight.push_back(0.056654485062114);
			xsi.push_back(0.456647809194822); eta.push_back(-0.506654878720194); weight.push_back(0.056654485062114);
			xsi.push_back(-0.949992930474628); eta.push_back(0.456647809194822); weight.push_back(0.056654485062114);
			xsi.push_back(-0.866393497975600); eta.push_back(0.847311867175000); weight.push_back(0.018843333927466);
			xsi.push_back(0.847311867175000); eta.push_back(-0.980918369199402); weight.push_back(0.018843333927466);
			xsi.push_back(-0.980918369199402); eta.push_back(-0.866393497975600); weight.push_back(0.018843333927466);
			xsi.push_back(-0.866393497975600); eta.push_back(-0.980918369199402); weight.push_back(0.018843333927466);
			xsi.push_back(0.847311867175000); eta.push_back(-0.866393497975600); weight.push_back(0.018843333927466);
			xsi.push_back(-0.980918369199402); eta.push_back(0.847311867175000); weight.push_back(0.018843333927466);
		}
		else if (order <= 11) {
			xsi.push_back(0.069222096541516); eta.push_back(0.069222096541516); weight.push_back(0.001854012657922);
			xsi.push_back(0.069222096541516); eta.push_back(-1.138444193083034); weight.push_back(0.001854012657922);
			xsi.push_back(-1.138444193083034); eta.push_back(0.069222096541516); weight.push_back(0.001854012657922);
			xsi.push_back(-0.202061394068290); eta.push_back(-0.202061394068290); weight.push_back(0.154299069829626);
			xsi.push_back(-0.202061394068290); eta.push_back(-0.595877211863420); weight.push_back(0.154299069829626);
			xsi.push_back(-0.595877211863420); eta.push_back(-0.202061394068290); weight.push_back(0.154299069829626);
			xsi.push_back(-0.593380199137436); eta.push_back(-0.593380199137436); weight.push_back(0.118645954761548);
			xsi.push_back(-0.593380199137436); eta.push_back(0.186760398274870); weight.push_back(0.118645954761548);
			xsi.push_back(0.186760398274870); eta.push_back(-0.593380199137436); weight.push_back(0.118645954761548);
			xsi.push_back(-0.761298175434838); eta.push_back(-0.761298175434838); weight.push_back(0.072369081006836);
			xsi.push_back(-0.761298175434838); eta.push_back(0.522596350869674); weight.push_back(0.072369081006836);
			xsi.push_back(0.522596350869674); eta.push_back(-0.761298175434838); weight.push_back(0.072369081006836);
			xsi.push_back(-0.935270103777448); eta.push_back(-0.935270103777448); weight.push_back(0.027319462005356);
			xsi.push_back(-0.935270103777448); eta.push_back(0.870540207554896); weight.push_back(0.027319462005356);
			xsi.push_back(0.870540207554896); eta.push_back(-0.935270103777448); weight.push_back(0.027319462005356);
			xsi.push_back(-0.286758703477414); eta.push_back(0.186402426856426); weight.push_back(0.104674223924408);
			xsi.push_back(0.186402426856426); eta.push_back(-0.899643723379010); weight.push_back(0.104674223924408);
			xsi.push_back(-0.899643723379010); eta.push_back(-0.286758703477414); weight.push_back(0.104674223924408);
			xsi.push_back(-0.286758703477414); eta.push_back(-0.899643723379010); weight.push_back(0.104674223924408);
			xsi.push_back(0.186402426856426); eta.push_back(-0.286758703477414); weight.push_back(0.104674223924408);
			xsi.push_back(-0.899643723379010); eta.push_back(0.186402426856426); weight.push_back(0.104674223924408);
			xsi.push_back(-0.657022039391916); eta.push_back(0.614978006319584); weight.push_back(0.041415319278282);
			xsi.push_back(0.614978006319584); eta.push_back(-0.957955966927668); weight.push_back(0.041415319278282);
			xsi.push_back(-0.957955966927668); eta.push_back(-0.657022039391916); weight.push_back(0.041415319278282);
			xsi.push_back(-0.657022039391916); eta.push_back(-0.957955966927668); weight.push_back(0.041415319278282);
			xsi.push_back(0.614978006319584); eta.push_back(-0.657022039391916); weight.push_back(0.041415319278282);
			xsi.push_back(-0.957955966927668); eta.push_back(0.614978006319584); weight.push_back(0.041415319278282);
		}
		else if (order <= 12) {
			xsi.push_back(-0.023565220452390); eta.push_back(-0.023565220452390); weight.push_back(0.051462132880910);
			xsi.push_back(-0.023565220452390); eta.push_back(-0.952869559095220); weight.push_back(0.051462132880910);
			xsi.push_back(-0.952869559095220); eta.push_back(-0.023565220452390); weight.push_back(0.051462132880910);
			xsi.push_back(-0.120551215411080); eta.push_back(-0.120551215411080); weight.push_back(0.087385089076076);
			xsi.push_back(-0.120551215411080); eta.push_back(-0.758897569177842); weight.push_back(0.087385089076076);
			xsi.push_back(-0.758897569177842); eta.push_back(-0.120551215411080); weight.push_back(0.087385089076076);
			xsi.push_back(-0.457579229975768); eta.push_back(-0.457579229975768); weight.push_back(0.125716448435770);
			xsi.push_back(-0.457579229975768); eta.push_back(-0.084841540048464); weight.push_back(0.125716448435770);
			xsi.push_back(-0.084841540048464); eta.push_back(-0.457579229975768); weight.push_back(0.125716448435770);
			xsi.push_back(-0.744847708916828); eta.push_back(-0.744847708916828); weight.push_back(0.069592225861418);
			xsi.push_back(-0.744847708916828); eta.push_back(0.489695417833656); weight.push_back(0.069592225861418);
			xsi.push_back(0.489695417833656); eta.push_back(-0.744847708916828); weight.push_back(0.069592225861418);
			xsi.push_back(-0.957365299093580); eta.push_back(-0.957365299093580); weight.push_back(0.012332522103118);
			xsi.push_back(-0.957365299093580); eta.push_back(0.914730598187158); weight.push_back(0.012332522103118);
			xsi.push_back(0.914730598187158); eta.push_back(-0.957365299093580); weight.push_back(0.012332522103118);
			xsi.push_back(-0.448573460628972); eta.push_back(0.217886471559576); weight.push_back(0.080743115532762);
			xsi.push_back(0.217886471559576); eta.push_back(-0.769313010930604); weight.push_back(0.080743115532762);
			xsi.push_back(-0.769313010930604); eta.push_back(-0.448573460628972); weight.push_back(0.080743115532762);
			xsi.push_back(-0.448573460628972); eta.push_back(-0.769313010930604); weight.push_back(0.080743115532762);
			xsi.push_back(0.217886471559576); eta.push_back(-0.448573460628972); weight.push_back(0.080743115532762);
			xsi.push_back(-0.769313010930604); eta.push_back(0.217886471559576); weight.push_back(0.080743115532762);
			xsi.push_back(-0.437348838020120); eta.push_back(0.391672173575606); weight.push_back(0.044713546404606);
			xsi.push_back(0.391672173575606); eta.push_back(-0.954323335555486); weight.push_back(0.044713546404606);
			xsi.push_back(-0.954323335555486); eta.push_back(-0.437348838020120); weight.push_back(0.044713546404606);
			xsi.push_back(-0.437348838020120); eta.push_back(-0.954323335555486); weight.push_back(0.044713546404606);
			xsi.push_back(0.391672173575606); eta.push_back(-0.437348838020120); weight.push_back(0.044713546404606);
			xsi.push_back(-0.954323335555486); eta.push_back(0.391672173575606); weight.push_back(0.044713546404606);
			xsi.push_back(-0.767496168184806); eta.push_back(0.716028067088146); weight.push_back(0.034632462217318);
			xsi.push_back(0.716028067088146); eta.push_back(-0.948531898903340); weight.push_back(0.034632462217318);
			xsi.push_back(-0.948531898903340); eta.push_back(-0.767496168184806); weight.push_back(0.034632462217318);
			xsi.push_back(-0.767496168184806); eta.push_back(-0.948531898903340); weight.push_back(0.034632462217318);
			xsi.push_back(0.716028067088146); eta.push_back(-0.767496168184806); weight.push_back(0.034632462217318);
			xsi.push_back(-0.948531898903340); eta.push_back(0.716028067088146); weight.push_back(0.034632462217318);
		}
		else if (order <= 13) {
			xsi.push_back(-0.333333333333333); eta.push_back(-0.333333333333333); weight.push_back(0.105041846801604);
			xsi.push_back(-0.009903630120590); eta.push_back(-0.009903630120590); weight.push_back(0.022560290418660);
			xsi.push_back(-0.009903630120590); eta.push_back(-0.980192739758818); weight.push_back(0.022560290418660);
			xsi.push_back(-0.980192739758818); eta.push_back(-0.009903630120590); weight.push_back(0.022560290418660);
			xsi.push_back(-0.062566729780852); eta.push_back(-0.062566729780852); weight.push_back(0.062847036724908);
			xsi.push_back(-0.062566729780852); eta.push_back(-0.874866540438296); weight.push_back(0.062847036724908);
			xsi.push_back(-0.874866540438296); eta.push_back(-0.062566729780852); weight.push_back(0.062847036724908);
			xsi.push_back(-0.170957326397446); eta.push_back(-0.170957326397446); weight.push_back(0.094145005008388);
			xsi.push_back(-0.170957326397446); eta.push_back(-0.658085347205106); weight.push_back(0.094145005008388);
			xsi.push_back(-0.658085347205106); eta.push_back(-0.170957326397446); weight.push_back(0.094145005008388);
			xsi.push_back(-0.541200855914338); eta.push_back(-0.541200855914338); weight.push_back(0.094727173072710);
			xsi.push_back(-0.541200855914338); eta.push_back(0.082401711828674); weight.push_back(0.094727173072710);
			xsi.push_back(0.082401711828674); eta.push_back(-0.541200855914338); weight.push_back(0.094727173072710);
			xsi.push_back(-0.771151009607340); eta.push_back(-0.771151009607340); weight.push_back(0.062335058091588);
			xsi.push_back(-0.771151009607340); eta.push_back(0.542302019214680); weight.push_back(0.062335058091588);
			xsi.push_back(0.542302019214680); eta.push_back(-0.771151009607340); weight.push_back(0.062335058091588);
			xsi.push_back(-0.950377217273082); eta.push_back(-0.950377217273082); weight.push_back(0.015951542930148);
			xsi.push_back(-0.950377217273082); eta.push_back(0.900754434546164); weight.push_back(0.015951542930148);
			xsi.push_back(0.900754434546164); eta.push_back(-0.950377217273082); weight.push_back(0.015951542930148);
			xsi.push_back(-0.462410005882478); eta.push_back(0.272702349123320); weight.push_back(0.073696805457464);
			xsi.push_back(0.272702349123320); eta.push_back(-0.810292343240842); weight.push_back(0.073696805457464);
			xsi.push_back(-0.810292343240842); eta.push_back(-0.462410005882478); weight.push_back(0.073696805457464);
			xsi.push_back(-0.462410005882478); eta.push_back(-0.810292343240842); weight.push_back(0.073696805457464);
			xsi.push_back(0.272702349123320); eta.push_back(-0.462410005882478); weight.push_back(0.073696805457464);
			xsi.push_back(-0.810292343240842); eta.push_back(0.272702349123320); weight.push_back(0.073696805457464);
			xsi.push_back(-0.416539866531424); eta.push_back(0.380338319973810); weight.push_back(0.034802926607644);
			xsi.push_back(0.380338319973810); eta.push_back(-0.963798453442386); weight.push_back(0.034802926607644);
			xsi.push_back(-0.963798453442386); eta.push_back(-0.416539866531424); weight.push_back(0.034802926607644);
			xsi.push_back(-0.416539866531424); eta.push_back(-0.963798453442386); weight.push_back(0.034802926607644);
			xsi.push_back(0.380338319973810); eta.push_back(-0.416539866531424); weight.push_back(0.034802926607644);
			xsi.push_back(-0.963798453442386); eta.push_back(0.380338319973810); weight.push_back(0.034802926607644);
			xsi.push_back(-0.747285229016662); eta.push_back(0.702819075668482); weight.push_back(0.031043573678090);
			xsi.push_back(0.702819075668482); eta.push_back(-0.955533846651820); weight.push_back(0.031043573678090);
			xsi.push_back(-0.955533846651820); eta.push_back(-0.747285229016662); weight.push_back(0.031043573678090);
			xsi.push_back(-0.747285229016662); eta.push_back(-0.955533846651820); weight.push_back(0.031043573678090);
			xsi.push_back(0.702819075668482); eta.push_back(-0.747285229016662); weight.push_back(0.031043573678090);
			xsi.push_back(-0.955533846651820); eta.push_back(0.702819075668482); weight.push_back(0.031043573678090);
		}
		else if (order <= 14) {
			xsi.push_back(-0.022072179275642); eta.push_back(-0.022072179275642); weight.push_back(0.043767162738858);
			xsi.push_back(-0.022072179275642); eta.push_back(-0.955855641448714); weight.push_back(0.043767162738858);
			xsi.push_back(-0.955855641448714); eta.push_back(-0.022072179275642); weight.push_back(0.043767162738858);
			xsi.push_back(-0.164710561319092); eta.push_back(-0.164710561319092); weight.push_back(0.065576707088250);
			xsi.push_back(-0.164710561319092); eta.push_back(-0.670578877361816); weight.push_back(0.065576707088250);
			xsi.push_back(-0.670578877361816); eta.push_back(-0.164710561319092); weight.push_back(0.065576707088250);
			xsi.push_back(-0.453044943382322); eta.push_back(-0.453044943382322); weight.push_back(0.103548209014584);
			xsi.push_back(-0.453044943382322); eta.push_back(-0.093910113235354); weight.push_back(0.103548209014584);
			xsi.push_back(-0.093910113235354); eta.push_back(-0.453044943382322); weight.push_back(0.103548209014584);
			xsi.push_back(-0.645588935174914); eta.push_back(-0.645588935174914); weight.push_back(0.084325177473986);
			xsi.push_back(-0.645588935174914); eta.push_back(0.291177870349826); weight.push_back(0.084325177473986);
			xsi.push_back(0.291177870349826); eta.push_back(-0.645588935174914); weight.push_back(0.084325177473986);
			xsi.push_back(-0.876400233818254); eta.push_back(-0.876400233818254); weight.push_back(0.028867399339554);
			xsi.push_back(-0.876400233818254); eta.push_back(0.752800467636510); weight.push_back(0.028867399339554);
			xsi.push_back(0.752800467636510); eta.push_back(-0.876400233818254); weight.push_back(0.028867399339554);
			xsi.push_back(-0.961218077502598); eta.push_back(-0.961218077502598); weight.push_back(0.009846807204800);
			xsi.push_back(-0.961218077502598); eta.push_back(0.922436155005196); weight.push_back(0.009846807204800);
			xsi.push_back(0.922436155005196); eta.push_back(-0.961218077502598); weight.push_back(0.009846807204800);
			xsi.push_back(-0.655466624357288); eta.push_back(0.541217109549992); weight.push_back(0.049331506425128);
			xsi.push_back(0.541217109549992); eta.push_back(-0.885750485192704); weight.push_back(0.049331506425128);
			xsi.push_back(-0.885750485192704); eta.push_back(-0.655466624357288); weight.push_back(0.049331506425128);
			xsi.push_back(-0.655466624357288); eta.push_back(-0.885750485192704); weight.push_back(0.049331506425128);
			xsi.push_back(0.541217109549992); eta.push_back(-0.655466624357288); weight.push_back(0.049331506425128);
			xsi.push_back(-0.885750485192704); eta.push_back(0.541217109549992); weight.push_back(0.049331506425128);
			xsi.push_back(-0.326277080407310); eta.push_back(0.140444581693366); weight.push_back(0.077143021574122);
			xsi.push_back(0.140444581693366); eta.push_back(-0.814167501286056); weight.push_back(0.077143021574122);
			xsi.push_back(-0.814167501286056); eta.push_back(-0.326277080407310); weight.push_back(0.077143021574122);
			xsi.push_back(-0.326277080407310); eta.push_back(-0.814167501286056); weight.push_back(0.077143021574122);
			xsi.push_back(0.140444581693366); eta.push_back(-0.326277080407310); weight.push_back(0.077143021574122);
			xsi.push_back(-0.814167501286056); eta.push_back(0.140444581693366); weight.push_back(0.077143021574122);
			xsi.push_back(-0.403254235727484); eta.push_back(0.373960335616176); weight.push_back(0.028872616227068);
			xsi.push_back(0.373960335616176); eta.push_back(-0.970706099888692); weight.push_back(0.028872616227068);
			xsi.push_back(-0.970706099888692); eta.push_back(-0.403254235727484); weight.push_back(0.028872616227068);
			xsi.push_back(-0.403254235727484); eta.push_back(-0.970706099888692); weight.push_back(0.028872616227068);
			xsi.push_back(0.373960335616176); eta.push_back(-0.403254235727484); weight.push_back(0.028872616227068);
			xsi.push_back(-0.970706099888692); eta.push_back(0.373960335616176); weight.push_back(0.028872616227068);
			xsi.push_back(-0.762051004606086); eta.push_back(0.759514342740342); weight.push_back(0.010020457677002);
			xsi.push_back(0.759514342740342); eta.push_back(-0.997463338134256); weight.push_back(0.010020457677002);
			xsi.push_back(-0.997463338134256); eta.push_back(-0.762051004606086); weight.push_back(0.010020457677002);
			xsi.push_back(-0.762051004606086); eta.push_back(-0.997463338134256); weight.push_back(0.010020457677002);
			xsi.push_back(0.759514342740342); eta.push_back(-0.762051004606086); weight.push_back(0.010020457677002);
			xsi.push_back(-0.997463338134256); eta.push_back(0.759514342740342); weight.push_back(0.010020457677002);
		}
		else if (order <= 15) {
			xsi.push_back(0.013945833716486); eta.push_back(0.013945833716486); weight.push_back(0.003833751285698);
			xsi.push_back(0.013945833716486); eta.push_back(-1.027891667432972); weight.push_back(0.003833751285698);
			xsi.push_back(-1.027891667432972); eta.push_back(0.013945833716486); weight.push_back(0.003833751285698);
			xsi.push_back(-0.137187291433954); eta.push_back(-0.137187291433954); weight.push_back(0.088498054542290);
			xsi.push_back(-0.137187291433954); eta.push_back(-0.725625417132090); weight.push_back(0.088498054542290);
			xsi.push_back(-0.725625417132090); eta.push_back(-0.137187291433954); weight.push_back(0.088498054542290);
			xsi.push_back(-0.444612710305712); eta.push_back(-0.444612710305712); weight.push_back(0.102373097437704);
			xsi.push_back(-0.444612710305712); eta.push_back(-0.110774579388578); weight.push_back(0.102373097437704);
			xsi.push_back(-0.110774579388578); eta.push_back(-0.444612710305712); weight.push_back(0.102373097437704);
			xsi.push_back(-0.747070217917492); eta.push_back(-0.747070217917492); weight.push_back(0.047375471741376);
			xsi.push_back(-0.747070217917492); eta.push_back(0.494140435834984); weight.push_back(0.047375471741376);
			xsi.push_back(0.494140435834984); eta.push_back(-0.747070217917492); weight.push_back(0.047375471741376);
			xsi.push_back(-0.858383228050628); eta.push_back(-0.858383228050628); weight.push_back(0.026579551380042);
			xsi.push_back(-0.858383228050628); eta.push_back(0.716766456101256); weight.push_back(0.026579551380042);
			xsi.push_back(0.716766456101256); eta.push_back(-0.858383228050628); weight.push_back(0.026579551380042);
			xsi.push_back(-0.962069659517854); eta.push_back(-0.962069659517854); weight.push_back(0.009497833216384);
			xsi.push_back(-0.962069659517854); eta.push_back(0.924139319035706); weight.push_back(0.009497833216384);
			xsi.push_back(0.924139319035706); eta.push_back(-0.962069659517854); weight.push_back(0.009497833216384);
			xsi.push_back(-0.477377257719826); eta.push_back(0.209908933786582); weight.push_back(0.077100145199186);
			xsi.push_back(0.209908933786582); eta.push_back(-0.732531676066758); weight.push_back(0.077100145199186);
			xsi.push_back(-0.732531676066758); eta.push_back(-0.477377257719826); weight.push_back(0.077100145199186);
			xsi.push_back(-0.477377257719826); eta.push_back(-0.732531676066758); weight.push_back(0.077100145199186);
			xsi.push_back(0.209908933786582); eta.push_back(-0.477377257719826); weight.push_back(0.077100145199186);
			xsi.push_back(-0.732531676066758); eta.push_back(0.209908933786582); weight.push_back(0.077100145199186);
			xsi.push_back(-0.223906465819462); eta.push_back(0.151173111025628); weight.push_back(0.054431628641248);
			xsi.push_back(0.151173111025628); eta.push_back(-0.927266645206166); weight.push_back(0.054431628641248);
			xsi.push_back(-0.927266645206166); eta.push_back(-0.223906465819462); weight.push_back(0.054431628641248);
			xsi.push_back(-0.223906465819462); eta.push_back(-0.927266645206166); weight.push_back(0.054431628641248);
			xsi.push_back(0.151173111025628); eta.push_back(-0.223906465819462); weight.push_back(0.054431628641248);
			xsi.push_back(-0.927266645206166); eta.push_back(0.151173111025628); weight.push_back(0.054431628641248);
			xsi.push_back(-0.428575559900168); eta.push_back(0.448925326153310); weight.push_back(0.004364154733594);
			xsi.push_back(0.448925326153310); eta.push_back(-1.020349766253142); weight.push_back(0.004364154733594);
			xsi.push_back(-1.020349766253142); eta.push_back(-0.428575559900168); weight.push_back(0.004364154733594);
			xsi.push_back(-0.428575559900168); eta.push_back(-1.020349766253142); weight.push_back(0.004364154733594);
			xsi.push_back(0.448925326153310); eta.push_back(-0.428575559900168); weight.push_back(0.004364154733594);
			xsi.push_back(-1.020349766253142); eta.push_back(0.448925326153310); weight.push_back(0.004364154733594);
			xsi.push_back(-0.568800671855432); eta.push_back(0.495112932103676); weight.push_back(0.043010639695462);
			xsi.push_back(0.495112932103676); eta.push_back(-0.926312260248244); weight.push_back(0.043010639695462);
			xsi.push_back(-0.926312260248244); eta.push_back(-0.568800671855432); weight.push_back(0.043010639695462);
			xsi.push_back(-0.568800671855432); eta.push_back(-0.926312260248244); weight.push_back(0.043010639695462);
			xsi.push_back(0.495112932103676); eta.push_back(-0.568800671855432); weight.push_back(0.043010639695462);
			xsi.push_back(-0.926312260248244); eta.push_back(0.495112932103676); weight.push_back(0.043010639695462);
			xsi.push_back(-0.792848766847228); eta.push_back(0.767929148184832); weight.push_back(0.015347885262098);
			xsi.push_back(0.767929148184832); eta.push_back(-0.975080381337602); weight.push_back(0.015347885262098);
			xsi.push_back(-0.975080381337602); eta.push_back(-0.792848766847228); weight.push_back(0.015347885262098);
			xsi.push_back(-0.792848766847228); eta.push_back(-0.975080381337602); weight.push_back(0.015347885262098);
			xsi.push_back(0.767929148184832); eta.push_back(-0.792848766847228); weight.push_back(0.015347885262098);
			xsi.push_back(-0.975080381337602); eta.push_back(0.767929148184832); weight.push_back(0.015347885262098);
		}
		else if (order <= 16) {
			xsi.push_back(-0.333333333333333); eta.push_back(-0.333333333333333); weight.push_back(0.093751394855284);
			xsi.push_back(-0.005238916103124); eta.push_back(-0.005238916103124); weight.push_back(0.012811757157170);
			xsi.push_back(-0.005238916103124); eta.push_back(-0.989522167793754); weight.push_back(0.012811757157170);
			xsi.push_back(-0.989522167793754); eta.push_back(-0.005238916103124); weight.push_back(0.012811757157170);
			xsi.push_back(-0.173061122901296); eta.push_back(-0.173061122901296); weight.push_back(0.083420593478774);
			xsi.push_back(-0.173061122901296); eta.push_back(-0.653877754197410); weight.push_back(0.083420593478774);
			xsi.push_back(-0.653877754197410); eta.push_back(-0.173061122901296); weight.push_back(0.083420593478774);
			xsi.push_back(-0.059082801866018); eta.push_back(-0.059082801866018); weight.push_back(0.053782968500128);
			xsi.push_back(-0.059082801866018); eta.push_back(-0.881834396267966); weight.push_back(0.053782968500128);
			xsi.push_back(-0.881834396267966); eta.push_back(-0.059082801866018); weight.push_back(0.053782968500128);
			xsi.push_back(-0.518892500060958); eta.push_back(-0.518892500060958); weight.push_back(0.084265045523300);
			xsi.push_back(-0.518892500060958); eta.push_back(0.037785000121916); weight.push_back(0.084265045523300);
			xsi.push_back(0.037785000121916); eta.push_back(-0.518892500060958); weight.push_back(0.084265045523300);
			xsi.push_back(-0.704068411554854); eta.push_back(-0.704068411554854); weight.push_back(0.060000533685546);
			xsi.push_back(-0.704068411554854); eta.push_back(0.408136823109708); weight.push_back(0.060000533685546);
			xsi.push_back(0.408136823109708); eta.push_back(-0.704068411554854); weight.push_back(0.060000533685546);
			xsi.push_back(-0.849069624685052); eta.push_back(-0.849069624685052); weight.push_back(0.028400197850048);
			xsi.push_back(-0.849069624685052); eta.push_back(0.698139249370104); weight.push_back(0.028400197850048);
			xsi.push_back(0.698139249370104); eta.push_back(-0.849069624685052); weight.push_back(0.028400197850048);
			xsi.push_back(-0.966807194753950); eta.push_back(-0.966807194753950); weight.push_back(0.007164924702546);
			xsi.push_back(-0.966807194753950); eta.push_back(0.933614389507900); weight.push_back(0.007164924702546);
			xsi.push_back(0.933614389507900); eta.push_back(-0.966807194753950); weight.push_back(0.007164924702546);
			xsi.push_back(-0.406888806840226); eta.push_back(0.199737422349722); weight.push_back(0.065546294921254);
			xsi.push_back(0.199737422349722); eta.push_back(-0.792848615509496); weight.push_back(0.065546294921254);
			xsi.push_back(-0.792848615509496); eta.push_back(-0.406888806840226); weight.push_back(0.065546294921254);
			xsi.push_back(-0.406888806840226); eta.push_back(-0.792848615509496); weight.push_back(0.065546294921254);
			xsi.push_back(0.199737422349722); eta.push_back(-0.406888806840226); weight.push_back(0.065546294921254);
			xsi.push_back(-0.792848615509496); eta.push_back(0.199737422349722); weight.push_back(0.065546294921254);
			xsi.push_back(-0.324553873193842); eta.push_back(0.284387049883010); weight.push_back(0.030596612496882);
			xsi.push_back(0.284387049883010); eta.push_back(-0.959833176689168); weight.push_back(0.030596612496882);
			xsi.push_back(-0.959833176689168); eta.push_back(-0.324553873193842); weight.push_back(0.030596612496882);
			xsi.push_back(-0.324553873193842); eta.push_back(-0.959833176689168); weight.push_back(0.030596612496882);
			xsi.push_back(0.284387049883010); eta.push_back(-0.324553873193842); weight.push_back(0.030596612496882);
			xsi.push_back(-0.959833176689168); eta.push_back(0.284387049883010); weight.push_back(0.030596612496882);
			xsi.push_back(-0.590503436714376); eta.push_back(0.599185441942654); weight.push_back(0.004772488385678);
			xsi.push_back(0.599185441942654); eta.push_back(-1.008682005228278); weight.push_back(0.004772488385678);
			xsi.push_back(-1.008682005228278); eta.push_back(-0.590503436714376); weight.push_back(0.004772488385678);
			xsi.push_back(-0.590503436714376); eta.push_back(-1.008682005228278); weight.push_back(0.004772488385678);
			xsi.push_back(0.599185441942654); eta.push_back(-0.590503436714376); weight.push_back(0.004772488385678);
			xsi.push_back(-1.008682005228278); eta.push_back(0.599185441942654); weight.push_back(0.004772488385678);
			xsi.push_back(-0.621283015738754); eta.push_back(0.537399442802736); weight.push_back(0.038169585511798);
			xsi.push_back(0.537399442802736); eta.push_back(-0.916116427063980); weight.push_back(0.038169585511798);
			xsi.push_back(-0.916116427063980); eta.push_back(-0.621283015738754); weight.push_back(0.038169585511798);
			xsi.push_back(-0.621283015738754); eta.push_back(-0.916116427063980); weight.push_back(0.038169585511798);
			xsi.push_back(0.537399442802736); eta.push_back(-0.621283015738754); weight.push_back(0.038169585511798);
			xsi.push_back(-0.916116427063980); eta.push_back(0.537399442802736); weight.push_back(0.038169585511798);
			xsi.push_back(-0.829432768634686); eta.push_back(0.800798128173322); weight.push_back(0.013700109093084);
			xsi.push_back(0.800798128173322); eta.push_back(-0.971365359538638); weight.push_back(0.013700109093084);
			xsi.push_back(-0.971365359538638); eta.push_back(-0.829432768634686); weight.push_back(0.013700109093084);
			xsi.push_back(-0.829432768634686); eta.push_back(-0.971365359538638); weight.push_back(0.013700109093084);
			xsi.push_back(0.800798128173322); eta.push_back(-0.829432768634686); weight.push_back(0.013700109093084);
			xsi.push_back(-0.971365359538638); eta.push_back(0.800798128173322); weight.push_back(0.013700109093084);
		}
		else if (order <= 17) {
			xsi.push_back(-0.333333333333333); eta.push_back(-0.333333333333333); weight.push_back(0.066874398581606);
			xsi.push_back(-0.005658918886452); eta.push_back(-0.005658918886452); weight.push_back(0.010186830881014);
			xsi.push_back(-0.005658918886452); eta.push_back(-0.988682162227096); weight.push_back(0.010186830881014);
			xsi.push_back(-0.988682162227096); eta.push_back(-0.005658918886452); weight.push_back(0.010186830881014);
			xsi.push_back(-0.035647354750750); eta.push_back(-0.035647354750750); weight.push_back(0.029341729055276);
			xsi.push_back(-0.035647354750750); eta.push_back(-0.928705290498498); weight.push_back(0.029341729055276);
			xsi.push_back(-0.928705290498498); eta.push_back(-0.035647354750750); weight.push_back(0.029341729055276);
			xsi.push_back(-0.099520061958436); eta.push_back(-0.099520061958436); weight.push_back(0.048701756707344);
			xsi.push_back(-0.099520061958436); eta.push_back(-0.800959876083126); weight.push_back(0.048701756707344);
			xsi.push_back(-0.800959876083126); eta.push_back(-0.099520061958436); weight.push_back(0.048701756707344);
			xsi.push_back(-0.199467521245206); eta.push_back(-0.199467521245206); weight.push_back(0.062215101737938);
			xsi.push_back(-0.199467521245206); eta.push_back(-0.601064957509588); weight.push_back(0.062215101737938);
			xsi.push_back(-0.601064957509588); eta.push_back(-0.199467521245206); weight.push_back(0.062215101737938);
			xsi.push_back(-0.495717464058094); eta.push_back(-0.495717464058094); weight.push_back(0.062514222437240);
			xsi.push_back(-0.495717464058094); eta.push_back(-0.008565071883810); weight.push_back(0.062514222437240);
			xsi.push_back(-0.008565071883810); eta.push_back(-0.495717464058094); weight.push_back(0.062514222437240);
			xsi.push_back(-0.675905990683078); eta.push_back(-0.675905990683078); weight.push_back(0.049631308679330);
			xsi.push_back(-0.675905990683078); eta.push_back(0.351811981366154); weight.push_back(0.049631308679330);
			xsi.push_back(0.351811981366154); eta.push_back(-0.675905990683078); weight.push_back(0.049631308679330);
			xsi.push_back(-0.848248235478508); eta.push_back(-0.848248235478508); weight.push_back(0.028112146141114);
			xsi.push_back(-0.848248235478508); eta.push_back(0.696496470957016); weight.push_back(0.028112146141114);
			xsi.push_back(0.696496470957016); eta.push_back(-0.848248235478508); weight.push_back(0.028112146141114);
			xsi.push_back(-0.968690546064356); eta.push_back(-0.968690546064356); weight.push_back(0.006389352347558);
			xsi.push_back(-0.968690546064356); eta.push_back(0.937381092128712); weight.push_back(0.006389352347558);
			xsi.push_back(0.937381092128712); eta.push_back(-0.968690546064356); weight.push_back(0.006389352347558);
			xsi.push_back(-0.331360265272684); eta.push_back(0.310986407618846); weight.push_back(0.016239310637986);
			xsi.push_back(0.310986407618846); eta.push_back(-0.979626142346162); weight.push_back(0.016239310637986);
			xsi.push_back(-0.979626142346162); eta.push_back(-0.331360265272684); weight.push_back(0.016239310637986);
			xsi.push_back(-0.331360265272684); eta.push_back(-0.979626142346162); weight.push_back(0.016239310637986);
			xsi.push_back(0.310986407618846); eta.push_back(-0.331360265272684); weight.push_back(0.016239310637986);
			xsi.push_back(-0.979626142346162); eta.push_back(0.310986407618846); weight.push_back(0.016239310637986);
			xsi.push_back(-0.415556924406112); eta.push_back(0.144675181064040); weight.push_back(0.053611484566326);
			xsi.push_back(0.144675181064040); eta.push_back(-0.729118256657928); weight.push_back(0.053611484566326);
			xsi.push_back(-0.729118256657928); eta.push_back(-0.415556924406112); weight.push_back(0.053611484566326);
			xsi.push_back(-0.415556924406112); eta.push_back(-0.729118256657928); weight.push_back(0.053611484566326);
			xsi.push_back(0.144675181064040); eta.push_back(-0.415556924406112); weight.push_back(0.053611484566326);
			xsi.push_back(-0.729118256657928); eta.push_back(0.144675181064040); weight.push_back(0.053611484566326);
			xsi.push_back(-0.360850229153620); eta.push_back(0.252002380572456); weight.push_back(0.036919986421644);
			xsi.push_back(0.252002380572456); eta.push_back(-0.891152151418834); weight.push_back(0.036919986421644);
			xsi.push_back(-0.891152151418834); eta.push_back(-0.360850229153620); weight.push_back(0.036919986421644);
			xsi.push_back(-0.360850229153620); eta.push_back(-0.891152151418834); weight.push_back(0.036919986421644);
			xsi.push_back(0.252002380572456); eta.push_back(-0.360850229153620); weight.push_back(0.036919986421644);
			xsi.push_back(-0.891152151418834); eta.push_back(0.252002380572456); weight.push_back(0.036919986421644);
			xsi.push_back(-0.618591551615416); eta.push_back(0.592854429948142); weight.push_back(0.016953737068656);
			xsi.push_back(0.592854429948142); eta.push_back(-0.974262878332726); weight.push_back(0.016953737068656);
			xsi.push_back(-0.974262878332726); eta.push_back(-0.618591551615416); weight.push_back(0.016953737068656);
			xsi.push_back(-0.618591551615416); eta.push_back(-0.974262878332726); weight.push_back(0.016953737068656);
			xsi.push_back(0.592854429948142); eta.push_back(-0.618591551615416); weight.push_back(0.016953737068656);
			xsi.push_back(-0.974262878332726); eta.push_back(0.592854429948142); weight.push_back(0.016953737068656);
			xsi.push_back(-0.639033576702508); eta.push_back(0.504702011875458); weight.push_back(0.036585593540050);
			xsi.push_back(0.504702011875458); eta.push_back(-0.865668435172952); weight.push_back(0.036585593540050);
			xsi.push_back(-0.865668435172952); eta.push_back(-0.639033576702508); weight.push_back(0.036585593540050);
			xsi.push_back(-0.639033576702508); eta.push_back(-0.865668435172952); weight.push_back(0.036585593540050);
			xsi.push_back(0.504702011875458); eta.push_back(-0.639033576702508); weight.push_back(0.036585593540050);
			xsi.push_back(-0.865668435172952); eta.push_back(0.504702011875458); weight.push_back(0.036585593540050);
			xsi.push_back(-0.838577372640872); eta.push_back(0.809251008191216); weight.push_back(0.013331264008330);
			xsi.push_back(0.809251008191216); eta.push_back(-0.970673635550344); weight.push_back(0.013331264008330);
			xsi.push_back(-0.970673635550344); eta.push_back(-0.838577372640872); weight.push_back(0.013331264008330);
			xsi.push_back(-0.838577372640872); eta.push_back(-0.970673635550344); weight.push_back(0.013331264008330);
			xsi.push_back(0.809251008191216); eta.push_back(-0.838577372640872); weight.push_back(0.013331264008330);
			xsi.push_back(-0.970673635550344); eta.push_back(0.809251008191216); weight.push_back(0.013331264008330);
		}


	}

}
