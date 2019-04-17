#include <stdio.h>
#include <math.h>

int defense(int b, int t, int s, double max, double min);
int cp_total(int a, int b, int h, int A, int B, int H);
int stamina(int h, int base);
int main(void)
{
    int b,t,s,h,a,st,base,cp = 0;
    int total_b,total_h,total_all = 0;
    double magnification_max,magnification_min = 0;
    
    FILE *fp;
    char *fname = "bangi_cp.csv";
    ///  防\御補正率   ///
    magnification_max = 0.625;
    magnification_min = 0.375;
    ///  原作種族値  ///
    h = 100;
    b = 110;
    t = 100;
    s = 61;
    ///  原作種族値HP平均  ///
    st = 138;
    ///  pokego種族値  ///
    a = 251;
    ///  基礎HP補正値  ///
    base = 50;

    fp = fopen(fname, "w");
    if (fp == NULL){
        printf("%sファイルが開けません\n",fname);
        return -1;
    }   

    int i,j,k,A = 15, B = 15, H = 15;
    for(i = A; i > 9; i--) {
            for(j = B; j > 9; j--) {
                    for(k = H; k > 9; k--) {

                        total_b = defense(b,t,s,magnification_max,magnification_min);

                        total_h = stamina(h,base);

                        cp = cp_total(total_h,a,total_b,i,j,k);

                        fprintf(fp, "攻撃 = %d , 防御 = %d , HP = %d , 防御種族値 = %d , HP種族値 = %d, CP = %d\n",i, j, k, total_b, total_h, cp);
                   }
            }
    }
/*          
    while(magnification_max > 0.4) {          
          ///  防御計算  ///
          total_b = defense(b,t,s,magnification_max,magnification_min);
          ///  HP計算  ///
          total_h = stamina(h,base);
          ///  CP計算  ///
          cp = cp_total(total_h,a,total_b);

          fprintf(fp, "補正値max = %lf , 補正値min = %lf , HP = %d , 防御力 = %d , CP = %d\n",magnification_max,magnification_min,total_h,total_b,cp );

          /// 防御補正率調整   ///
          magnification_max = magnification_max - 0.001;
          magnification_min = magnification_min + 0.001;
    }
*/

/*
    printf("\n");
    printf("###  補正値  ###\n");
    printf("倍率max = "); scanf("%lf",&magnification_max);
    printf("倍率min = "); scanf("%lf",&magnification_min);
    printf("\n");

    printf("###  防御力計算  ###\n");
    printf("防御　 = "); scanf("%d",&b);
    printf("特防 　= "); scanf("%d",&t);
    printf("素早さ = "); scanf("%d",&s);
    printf("\n");
    
    total_b = defense(b,t,s,magnification_max,magnification_min);

    printf("###  CP計算   ###\n");
    printf("HP     = "); scanf("%d",&h);
    printf("攻撃力 = "); scanf("%d",&a);
    printf("防御力 = %d\n",total_b);
    printf("\n");

    cp = cp_total(h,a,total_b);

    printf("### TL40_CP  ###\n");
    printf("CP = %d\n\n",cp); 
*/
    return 0;
}

/// 防御値   ///
int defense(int b, int t, int s, double max, double min)
{
    double step1,step3,step2_1,step4_1;
    int step2,step4;

    if(b < t) {
       step1 = (t * max) + (b * min);
       step2_1 = step1 * 2.0 - ((int)step1 * 2); 
       if(step2_1 >= 0.5)
          step2 = ((int)step1 * 2) + 1;
       else
          step2 = (int)step1 * 2;
       step3 = ((s - 75) / 500.0) + 1.0; 
       step4_1 = step2 * step3;
       if (step4_1 - (int)step4_1 >= 0.5) {
           step4 = (int)step4_1 + 1;
       }
       else
           step4 = (int)step4_1;
    }
    else {
       step1 = (b * max) + (t * min);
       if(step2_1 >= 0.5)
          step2 = ((int)step1 * 2) + 1;
       else
          step2 = (int)step1 * 2;
       step3 = ((s - 75) / 500.0) + 1.0;
       step4_1 = step2 * step3;
       if (step4_1 - (int)step4_1 >= 0.5) {
           step4 = (int)step4_1 + 1;
       }
       else
           step4 = (int)step4_1;
    }
    return step4;
}

///  CP  ///
int cp_total(int h, int a, int b ,int A, int B, int H)
{
    double step1_h,step1_b,step2;
    int step1_a,step3;
    step1_h = sqrt(h + H);
    step1_b = sqrt(b + B);
    step1_a = a + A;

    step2 = step1_h * step1_b * step1_a;
    step3 = (step2 * 0.6245741058) / 10.0;

    return step3;
}

///  HP  ///
int stamina(int h, int base)
{
    int total_h = h * 1.75 + base;
    return total_h;
}






