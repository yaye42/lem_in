/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_ants_dispenser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:24:18 by yaye              #+#    #+#             */
/*   Updated: 2020/06/27 14:24:21 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

end(Qo_1)->Osn2->An_2->Slp1->Ic_8->K_l4->Bcg7->Wtt1->Zwq6->Rmm6->Gid7->Ipt7->Kz_1->Eoe8->Qos3->X_i5->Mlj0->Wgq2->Xt_7->I_a1->Oaa7->Wgc4->Dye9->Zfj7->Zig7->Ibc1->Wdh2->Kby1->Uqe3->Zph2->F_r3->Usr7->Phb8->Ivn0->Kvf7->Wop1->F_f3->Ktu7->P_m5->Wam1->Far1->Uv_3->Csx3->Xon9->Erw8->Ywg7->Ksg8->Ckx9->Tek6->Rdw6->Vmj3->Rca3->Quo3->Poz1->Dcs9->Tmz3->Hpd3->Fld4->Mtl9->X_m5->S_d2->H_q5->T_k8->Gdr4->Auh6->Nrv1->Zf_9->Gmk8->Um_1->Ywq2->Wqc2->Ifc3->Fwf7->Mqe0->Mkz0->Kis8->Ycb2->B_u3->Rmt2->Qhk5->Ubu0->start
		 ->Osn2->An_2->Slp1->Ic_8->K_l4->Bcg7->Wtt1->Zwq6->Rmm6->Gid7->Ipt7->Kz_1->Eoe8->Qos3->X_i5->Mlj0->Wgq2->Xt_7->I_a1->Oaa7->Wgc4->Dye9->Zfj7->Zig7->Ibc1->Wdh2->Kby1->Uqe3->Zph2->F_r3->Usr7->Phb8->Ivn0->Kvf7->Wop1->F_f3->Ktu7->P_m5->Wam1->Far1->Uv_3->Csx3->Xon9->Erw8->Ywg7->Ksg8->Ckx9->Tek6->Rdw6->Vmj3->Rca3->Quo3->Poz1->Dcs9->Tmz3->Hpd3->Fld4->Mtl9->X_m5->S_d2->H_q5->T_k8->Gdr4->Auh6->Nrv1->Zf_9->Gmk8->Um_1->Ywq2->Wqc2->Ifc3->Fwf7->Mqe0->Mkz0->Kis8->Ycb2->B_u3->Rmt2->Qhk5->Ubu0->start
end(Qo_1)->Uvd2->Bxk9->Zmu7->Mio1->Uzg6->Hfo1->Rbz2->Xd_1->Wbk5->Udl9->Vb_9->Dqo9->T_w0->S_r7->Nig0->E_c0->K_b2->Hfh0->Gqs1->Zpl5->Kqf1->Zau9->B_w3->Zzm5->Qv_4->Mho3->Imp7->Wgs2->Pee9->Xpc0->Rm_5->Dhv4->Kq_3->Sss6->Fr_6->Aac6->Vhv1->Dwr2->Pv_7->Qrw4->Ygq2->Uxd3->Peb1->Gcq9->Atz9->Khi7->Bph3->N_x0->Qxs4->Sd_9->Muh9->Tp_7->Mcr3->Rvc4->Juu6->Jwl2->O__4->Jiq0->Xkq6->Zrw5->Fow4->Rth5->Aov9->Wwr5->Bxe2->Owh7->Knd1->Uoy5->Ptq6->Cak0->Og_7->Q_s0->Gwa0->Bfr9->I_t8->Ysg6->Goj6->Hgt9->Pyw5->Sm_6->N_v3->Zgs1->Trj7->Smr1



void 	send_ant(t_farm *f, t_room *room)
{
	room->ants++;
	room->len++;
	ft_printf(" L%d-%s", room->len, room->name);
	if (room == f->end)
		return ;
}

void	lem_in(t_farm *f)
{
	int		i;
	int		k;
	t_room	*p;

	i = 0;
	k = 0;
	while (f->start->links[i])
	{
		if (f->start->links[i]->epath)
		{
			p = f->start->links[i];
			while (p->ants != 0 && p != end)
				p = p->spath;
			if (p->ants != 0 && p != end)
			{
				p->ants--;
				p->len++;
				if (k == 0)
					k++;
				else
					ft_printf(" ");
				ft_printf("L%d-%s", p->len, p->name);
				if (p->level == 0)
					p->level = 1;
				else
					send_ant(f, p->spath);
			}
		}
		i = i + 1;
	}
}



lenght: 13 	ants: 0
start(Jbq9)->V_c2->Cgd0->Yfe0->Hlx6->C_e1->Zyn5->Tga7->Tfe7->Krm1->Amd8->Ylm5->Wpt0->end(Qo_1)

lenght: 26 	ants: 0
start(Jbq9)->Edq3->T_a8->Zbo7->A_i5->Zmn4->Xdp8->Dvi1->Jnx6->Zdy5->Zfa9->Wib6->Ftg7->Ack0->Sxm8->Mtc6->Joq7->E_i2->Bq_7->Ggv0->Obf5->Dxc3->S_h1->Gj_3->Gwm7->H_u1->end(Qo_1)

lenght: 46 	ants: 0
start(Jbq9)->Kqq3->Vzr8->O_t8->Fjm8->Wxu3->Bgt7->Djc0->Kqj5->Puu5->Ffx9->F_o9->Mjg8->Cnb0->Rnh9->Kpx6->Qrr4->Yey7->Fdw3->Cck2->Esp5->Uue5->Znp5->Dmi1->Ud_8->Cbx4->Ia_5->Emm3->Oto1->Ms_9->Q_f2->Pix2->Xsn9->Rp_3->Gkm4->Sbe2->Otz9->Wts9->Ydm3->T_o7->Arc8->Ygs3->Scb4->Xcx8->Xdh3->Kow7->end(Qo_1)

lenght: 48 	ants: 0
start(Jbq9)->Esm6->Yob5->Qxf2->Bjh3->Ygu4->Fbo2->Y_z9->Xt_1->X_k5->Bzl9->K_x7->Flm4->Dxh9->Czb8->Kuy9->G_r1->Sku7->Rzi0->Zch7->Cgh8->Yzr8->Own0->Jfk0->Oym2->Gb_2->Ybw5->Fon5->Dvh2->Ham9->Xvo5->Gaa9->Hux1->Klp0->I_p3->Nmk1->Zay2->Tdy8->Dsg5->Od_1->Dwg2->Cxw2->Exd1->Ytc5->Qzf5->Cjs9->Idk7->Rla4->end(Qo_1)

lenght: 51 	ants: 0
start(Jbq9)->Gab5->Vle1->Nva0->Frj0->Yom4->Prn9->Kei3->Dym4->Om_0->F__9->Aa_9->Wgn9->Onb1->Hbu2->Doy2->Ajp0->Uwy0->Ibb5->Uyf9->Iyd7->Wnv8->Xhu5->Rlg5->Zn_8->Aiy0->Pr_5->Xw_5->Bqk5->Vx_3->Uz_6->Eta7->Hgi2->Wdt3->Enr1->Evd4->Wvk5->Ayd1->Eot2->Gqg0->Sne8->Abl7->Bny3->Msq8->Ubh1->Okl8->Xvr0->Zfw9->Oez1->Zeo1->Ogj3->end(Qo_1)

lenght: 53 	ants: 0
start(Jbq9)->Mbl2->Ghn8->Rvh7->Ysg7->Ayg0->H_g1->Ifl3->Khu6->Adv4->Zgd9->Tyw1->Usk5->Xnm4->Zek3->Nsp4->Xxq3->Kgh5->Fwg8->Aco0->Sir8->Ezl8->J_b0->Dxw2->O_u1->Gth7->Fky0->Zc_8->Stf5->Wd_7->Kgy9->Q_x0->Vtm3->Pp_0->Paz1->Ou_3->Qxr3->Rsq9->Jle0->Emw7->Gkm8->Jq_5->Q_d8->Yhi4->Fgv6->Oys5->Guc1->Qwl3->Fgu7->Khn8->Slp1->An_2->Osn2->end(Qo_1)

lenght: 58 	ants: 0
start(Jbq9)->Fpu6->Squ3->Skf4->Ioo0->Rae6->Bio2->Zlv2->Tsc7->Clv5->Hzm7->Ui_9->Fmz7->Ohz0->Qfb7->Ha_6->Jao5->H_q3->Jkq7->R_p4->Ddi2->Mnh5->Ybf4->X_g9->Mio4->Btq4->Wjk7->Xly7->Ksw3->Qxy5->Mob6->S_e1->Igj4->Txx5->As_9->Huy6->Rua3->Pvl4->Gjg5->Apx5->Seo7->Ans8->Naf9->M_w2->Xkg5->Amp7->Izb5->Pp_8->Nbn8->Kx_3->Yjv0->Zpi4->Anq2->N_v2->Epx6->Kum5->Yeu5->Yfw1->end(Qo_1)

lenght: 58 	ants: 0
start(Jbq9)->Ph_0->Gcw0->Ysi1->Jdh8->Jzu9->Ejb7->B_z4->I_z2->Fej5->E_b3->Pp_3->Gev7->Yp_1->Nle3->Jtd6->Zrl0->Xbf9->Dce7->Qya1->Ur_3->Hiq5->Gah6->Shk5->Bvx6->Cyp5->Fye5->Vns4->Ihv8->Wbc8->A_c6->Dhi2->Huo2->Kan0->Wjj7->Tga1->Zlm4->Ada2->Puq5->Gm_4->Rmf4->Uqv1->M_j7->Vjk6->Rar5->Qfa7->Ssu2->W_b1->Cii2->Vbf1->I_p1->Kdw7->Bba4->M_d4->Gmd5->Rnn3->Cbj8->H_j8->end(Qo_1)

lenght: 60 	ants: 0
start(Jbq9)->R_u6->Fdj9->Xqo7->Kaf6->Ocb6->Thg2->Rso7->Mmq4->Zjo5->Hxb1->Odo4->Pjv4->Fsy0->Opt1->Vxs3->Gke0->Sfk2->Olr1->Ctx8->Cwd8->Yov0->Hty4->Odr1->Kwv9->W_f1->Kc_3->Prw5->Znx5->Ymv4->Keh3->Hii4->Tdl2->Cah1->Jru1->Knh5->Kjz0->Aat1->Jdz4->Zyc2->Yfj2->Kme5->Fpx2->Zt_0->Fxr0->O_h3->Ytj1->Dij5->N_r8->Ffn4->X_b7->Sip5->Yow2->Mhe6->Ggf0->Etk1->Ysy1->Zwx9->Nx_0->Sti5->end(Qo_1)

lenght: 87 	ants: 0
start(Jbq9)->Ypa6->Wdb7->V_n6->Gcq0->Aos3->Oti6->Bkm5->Idu2->B_s4->Jwy2->Bvj3->E_m5->Ppg1->Fod7->Hxo0->Bg_6->Afq7->Qoo8->Ux_0->Grm9->Wuq4->Oxp1->Dou2->Odq2->Pyq3->Tiw7->Bza3->Ewn1->Ghu4->Fke7->Uqi0->Z_v9->Edi6->Yov5->Ntx6->Hux3->Nq_9->Jqk4->T__4->Fzq6->Kpl5->Umj8->Cvs4->Zaq9->Plr1->Wgj3->Xtt0->Amo9->Ahn9->Xao0->Oac7->Crk5->J_n4->Td_4->Q_t2->Eer2->Kzs6->Hm_1->Ble1->Qdk3->M_t8->Pnz9->Brk9->Xjy9->Y_k3->Yxe2->Bxx1->Mfp4->Jgj5->Ecd0->Rph8->Tqo5->Cqh7->Vzm4->Wxp2->Y_w4->I_d2->Oxn3->Hao3->Khr5->K_l8->Ium9->Kev3->Wep3->Gzd7->Dxl4->end(Qo_1)

lenght: 87 	ants: 0
start(Jbq9)->Tss6->Btz4->Dpu1->Tvr5->Muc4->Vwy7->Cjr0->Jzn1->Dsw4->Tqz1->Otf4->Nsh3->Nss8->Abu6->Wdk0->Afg9->Iuq2->A_w6->Zir5->Wvo1->Tjl7->Gcz3->Zn_2->Oqa7->Wzi1->Wil6->Xds3->Vsn5->Jnk4->Rve3->Qoe2->Epw7->Zph0->Au_5->Nao4->K_j7->Dp_0->Njo0->Peo2->Ybx9->Mq_7->Xbb4->T_p3->Jqc8->Tcx5->Roo9->Rtr6->Plt5->Zf_5->Evr6->Aap8->Ooi2->F_b4->Raj2->Rbu7->Dqo5->Oix9->Nzt9->Cmo5->Cgm2->Raa4->Qy_4->Tgm4->Ngn0->Xxw7->Jki1->Szh9->Xgs3->Mro7->Akf5->Xje7->F_o3->T_b1->Jxx4->Mve9->Xvr4->Pax1->Khp8->Tuw2->Zsm6->Shr3->Xxb9->Xel7->Flt4->Oaa5->Be_0->end(Qo_1)

lenght: 91 	ants: 0
start(Jbq9)->Nkd0->Dfk4->Nwa3->Swf5->D_s2->T_q8->U_j4->Zvs4->Wgl1->Rhy0->Uug2->Rbp0->Hzw3->Qjm3->Hzb0->Hew2->Yak0->Ang9->Pmy4->Whp3->Qvp1->Aa_6->Pto8->Hzv5->Sfc6->Uxw6->Edn4->Gko3->Jxe5->Bno1->Kn_9->Mti2->Ano3->Pnk8->Yxu5->Pyg1->Btl2->Ajv5->Oyq3->Wut2->Jau0->Es_5->Qwu9->Gdo8->Grd6->Cvm5->Bcc1->Gxj5->Xpw4->Szv4->Cj_7->Dew7->Pxt4->Kjb2->Jcu7->Qug6->Qro9->Xqb6->Wph6->Ek_9->Dkv4->Ama2->F_q1->Erj9->Zij1->By_2->Wpf3->Bgx5->Tma2->Alu3->A_a6->Kby9->Vjv8->Ptm0->Mvz4->Hjw8->Hql6->Pax7->Mgg8->Djx3->Xom5->Tyh5->Ymz0->Twg8->Qey0->Wp_4->Hp_1->Vds6->Tet8->Hn_4->end(Qo_1)

lenght: 114 	ants: 0
start(Jbq9)->Mrv6->X_j2->Seh4->Fkl3->Flt6->Mfp1->Opz1->Jj_6->Um_8->Ivb6->Gmm6->Ehi1->Nkn7->Ard2->Cc_8->Zdk2->Utg0->D_n9->Tsm0->G_u8->Rrg7->Jvn4->Kli1->Rgj4->Bra0->Ys_1->Qmn5->B_c1->Ef_3->Twx0->Cll6->Mty5->Plg7->Ms_6->Kt_8->Ppz5->Jbm9->Ugw2->Sew5->Qdp9->Eyw3->Sty1->Pfr4->Yjy3->Roa7->D_w8->Cra6->Syr3->Fmv3->E_i8->Pw_3->Vod2->Cti6->Qy_6->S_z9->Naf0->Brg3->Czh4->Rbw9->Hzo8->Fyc8->Fjn3->Rme9->Ry_1->Wob0->Nz_7->Fg_2->Qib6->Uov8->Iij0->Ehg6->Sef3->Fli1->Vap2->Kqf9->Fqc6->Eqb5->N_d0->H_n2->Hne9->Nry4->Yoz1->Tuq3->Ngi9->Qdc7->Jza2->Ili3->Mem1->Apt4->Phl0->Avw5->Kch0->Rie4->Bof5->Jzz0->Ess5->Nvj7->Pov7->Rgn5->Zdz9->Ujt3->Znq8->Acp6->Oin7->Tux9->Snr2->D_l9->Zny2->Zie8->Eou9->Ywk4->Sbr9->Irr8->end(Qo_1)

lenght: 145 	ants: 0
start(Jbq9)->F_v5->Jah0->R_a7->Ijw3->Bvy6->Bti2->Dpq5->Jut2->Izp1->Qra9->You0->Khe4->T_v0->B_r5->W_x9->Zkg6->Qcr9->Fmh8->Nqp0->Hck6->M_s1->Rbd8->Rnw0->Jqg2->Ztr7->T_r2->Aoh2->S_t8->Cer4->Q_r3->Zvp9->Gkt8->Emv2->D_w3->Ivr4->Xap1->Oyu1->Xe_2->Vno0->Y_u8->Xrk4->Yap1->Ipe3->Zmf0->Vql5->Omv1->Sld7->Jyu2->X_b2->Tsy7->Rrt6->Yll7->Mra9->Rpc4->Tit6->Y_b9->Hwp9->Uu_3->Mxx5->D__1->Uzi9->Gkl1->Qlt3->Giq0->Uy_2->Zxb3->Wwo4->Ytv8->Hic9->Ahr9->Mrs8->Ulo3->Ukc2->J_i7->Szh7->Ipo7->Jph3->Ern7->Oxy5->Mxz4->Pd_1->Zfw0->Dho2->V_x4->Jj_1->Dmq2->Xy_7->E_t3->Sdv3->Fmm8->Zth4->Tsv2->Yw_3->Nlg2->Kpr6->Azs4->B_p8->Elz0->Ync7->Cye6->Bys0->Pnd0->Afw4->Wk_7->Pcs1->Gzh0->Vjz6->Udw4->Uu_9->Nal2->Qak6->No_1->Eng3->Nvl4->Aj_4->Hoe7->Jbc4->Fjw3->Ac_0->Ky_8->Hyg3->Xmi6->W__6->Ysu1->Bog3->Kpj8->Wbg5->Crj1->Wtb6->Zmg6->Thc8->P__0->Hhy1->Cfo0->Mrs3->Xnw6->Wdl6->Mxy8->Dif4->Cll3->Fkp1->Tub7->S_c3->Ikj1->end(Qo_1)




